// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket.h"
#include "NearAuth.h"

DEFINE_LOG_CATEGORY(WebSocketLog);

FUUpdate& FUUpdate::operator=(const game::battlemon::updates::Update& update)
{
	this->id = CONV_CHAR_TO_FSTRING(update.id().c_str());
	this->message = CONV_CHAR_TO_FSTRING(update.message().c_str());
	this->timestamp = update.timestamp();

	return *this;
}

FURoomNeedAccept& FURoomNeedAccept::operator=(const game::battlemon::updates::RoomNeedAccept& RNA)
{
	this->manual_accept = RNA.manual_accept();
	this->time_to_accept = RNA.time_to_accept();

	return *this;
}

FURoomPlayer& FURoomPlayer::operator=(const game::battlemon::updates::RoomPlayer& RP)
{
	this->lemon = RP.lemon();
	this->near_id = CONV_CHAR_TO_FSTRING(RP.near_id().c_str());

	return *this;
}

FURoomInfo& FURoomInfo::operator=(const game::battlemon::updates::RoomInfo& RI)
{
	this->room_id = CONV_CHAR_TO_FSTRING(RI.room_id().c_str());
	this->server_ip = CONV_CHAR_TO_FSTRING(RI.server_ip().c_str());

	int size = RI.players().size();
	players.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			players[Idx] = RI.players().Get(Idx);
		});

	return *this;
}

FUUpdateMessage& FUUpdateMessage::operator=(const game::battlemon::updates::UpdateMessage& UM)
{
	switch (UM.update_case())
	{
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomNeedAccept:
		this->update = FUUpdateCase::ROOM_NEED_ACCEPT;
		this->room_need_accept = UM.room_need_accept();
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomAcceptingCanceled:
		this->update = FUUpdateCase::ROOM_ACCEPTING_CANCELED;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomFound:
		this->update = FUUpdateCase::ROOM_FOUND;
		this->roomInfo = UM.room_found();
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomTeammates:
		this->update = FUUpdateCase::ROOM_TEAMMATES;
		this->roomInfo = UM.room_teammates();
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomReady:
		this->update = FUUpdateCase::ROOM_READY;
		this->roomInfo = UM.room_ready();
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kUserIsAlreadyInLine:
		this->update = FUUpdateCase::ROOM_READY;
		this->roomInfo = UM.user_is_already_in_battle();
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kUserIsAlreadyInBattle:
		this->update = FUUpdateCase::USER_IS_ALREADY_IN_LINE;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kUserOutOfLine:
		this->update = FUUpdateCase::USER_OUT_OF_LINE;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::UPDATE_NOT_SET:
	default:
		this->update = FUUpdateCase::DEFAULT;
		break;
	}
	return *this;
}


void UWebSocket::Base64Decode(const FString& Source, TArray<uint8>& Dest)
{
	FBase64::Decode(Source, Dest);
	
	game::battlemon::updates::UpdateMessage um;
	um.ParsePartialFromArray((void*)Dest.GetData(), Dest.Num());
	updateMessage = um;
	OnUpdateMessageEvent.Broadcast(updateMessage);
}

UWebSocket::UWebSocket()
{
}
UWebSocket::~UWebSocket()
{

}

void UWebSocket::CreateWebSocet(FString Address)
{
	{
		if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
		{
			FModuleManager::Get().LoadModule("WebSockets");
		}
		TMap<FString, FString> UHeaders;
		if (UNearAuth::client != nullptr)
		{
			UHeaders.Add("near_id", UNearAuth::client->GetAccount());
			FString sign = CONV_CHAR_TO_FSTRING(UNearAuth::client->GetSing());
			UHeaders.Add("sign", sign);
		}
		else
		{

			OnErrorEvent.Broadcast("client == nullptr");
			UE_LOG(WebSocketLog, Display, TEXT("client == nullptr"));
			return;
		}

		TArray<FString> Protocols;
		Protocols.Add("wss");
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(Address, Protocols, UHeaders);

		WebSocket->OnMessage().AddLambda([&](FString MessageText)
			{
				if (OnUpdateMessageEvent.IsBound())
				{
					FString MessageRead;
					TArray<uint8> Dest;
					TSharedPtr<FJsonObject> JsonObject;
					TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageText);
					if (FJsonSerializer::Deserialize(Reader, JsonObject))
					{
						FString Response = JsonObject->GetStringField("message");
						Base64Decode(Response, Dest);
					}
				}
				if(OnMessageEvent.IsBound())
					OnMessageEvent.Broadcast(MessageText);
			});

		WebSocket->OnConnected().AddLambda([&]()
			{
			UE_LOG(WebSocketLog, All, TEXT("Successfully connected"));
				
				OnConnectedEvent.Broadcast();
			});
		WebSocket->OnConnectionError().AddLambda([&](FString error)
			{
				UE_LOG(WebSocketLog, All, TEXT("Received message: %s"), *error);
				OnErrorEvent.Broadcast(error);
			});
	}
	WebSocket->Connect();
}

bool UWebSocket::IsConnected()
{
	if(WebSocket.IsValid())
		return WebSocket->IsConnected();
	else
		return false;
}

void UWebSocket::CloseConnection()
{
	if(WebSocket.IsValid() && WebSocket->IsConnected())
		WebSocket->Close();
}
