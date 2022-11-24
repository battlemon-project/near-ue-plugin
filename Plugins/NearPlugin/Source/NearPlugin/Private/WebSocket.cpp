// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket.h"


DEFINE_LOG_CATEGORY(WebSocketLog);

ModelUpdates::Update& operator<<(ModelUpdates::Update& Request, const FUUpdate& RequestUE)
{
	Request.id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.id);
	Request.message = (TYPE_CHAR*)GET_CHARPTR(RequestUE.message);
	Request.timestamp = RequestUE.timestamp;
	return Request;
}

ModelUpdates::UpdateCase& operator<<(ModelUpdates::UpdateCase& Request, const FUUpdateCase& RequestUE)
{
	switch (RequestUE)
	{
	case FUUpdateCase::ROOM_NEED_ACCEPT:
		Request = ModelUpdates::UpdateCase::ROOM_NEED_ACCEPT;
		break;
	case FUUpdateCase::ROOM_ACCEPTING_CANCELED:
		Request = ModelUpdates::UpdateCase::ROOM_ACCEPTING_CANCELED;
		break;
	case FUUpdateCase::ROOM_FOUND:
		Request = ModelUpdates::UpdateCase::ROOM_FOUND;
		break;
	case FUUpdateCase::ROOM_TEAMMATES:
		Request = ModelUpdates::UpdateCase::ROOM_TEAMMATES;
		break;
	case FUUpdateCase::ROOM_READY:
		Request = ModelUpdates::UpdateCase::ROOM_READY;
		break;
	default:
		Request = ModelUpdates::UpdateCase::DEFAULT;
		break;
	}
	return Request;
}

ModelUpdates::RoomNeedAccept& operator<<(ModelUpdates::RoomNeedAccept& Request, const FURoomNeedAccept& RequestUE)
{
	Request.manual_accept = RequestUE.manual_accept;
	Request.time_to_accept = RequestUE.time_to_accept;
	return Request;
}

ModelItems::OutfitKind& operator<<(ModelItems::OutfitKind& Request, const FUOutfitKind& RequestUE)
{
	switch (RequestUE)
	{
	case FUOutfitKind::Cap:
		Request = ModelItems::OutfitKind::CAP;
		break;
	case FUOutfitKind::Cloth:
		Request = ModelItems::OutfitKind::CLOTH;
		break;
	case FUOutfitKind::Fire_ARM:
		Request = ModelItems::OutfitKind::FIRE_ARM;
		break;
	case FUOutfitKind::Cold_ARM:
		Request = ModelItems::OutfitKind::COLD_ARM;
		break;
	case FUOutfitKind::Back:
		Request = ModelItems::OutfitKind::BACK;
		break;
	default:
		Request = ModelItems::OutfitKind::DEFAULT;
		break;
	}
	return Request;
}

ModelItems::OutfitModel& operator<<(ModelItems::OutfitModel& Request, const FUOutfitModel& RequestUE)
{
	Request.flavour = (TYPE_CHAR*)GET_CHARPTR(RequestUE.flavour);
	Request.token_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.token_id);
	Request.kind << RequestUE.kind;
	return Request;
}

ModelItems::LemonModel& operator<<(ModelItems::LemonModel& Request, const FULemonModel& RequestUE)
{

	Request.exo = (TYPE_CHAR*)GET_CHARPTR(RequestUE.exo);
	Request.eyes = (TYPE_CHAR*)GET_CHARPTR(RequestUE.eyes);
	Request.head = (TYPE_CHAR*)GET_CHARPTR(RequestUE.head);
	Request.teeth = (TYPE_CHAR*)GET_CHARPTR(RequestUE.teeth);
	Request.face = (TYPE_CHAR*)GET_CHARPTR(RequestUE.face);
	Request.cap << RequestUE.cap;
	Request.cloth << RequestUE.cloth;
	Request.fire_arm << RequestUE.fire_arm;
	Request.cold_arm << RequestUE.cold_arm;
	Request.back << RequestUE.back;
	return Request;
}

ModelItems::Item& operator<<(ModelItems::Item& Request, const FUItem& RequestUE)
{
	Request.token_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.token_id);
	Request.media = (TYPE_CHAR*)GET_CHARPTR(RequestUE.media);
	Request.owner_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.owner_id);

	switch (RequestUE.model)
	{
	case FUModel::LEMON:
		Request.lemon << RequestUE.lemon;
		Request.model = ModelItems::Model::LEMON;
		break;
	case FUModel::OUTFIT_MODEL:
		Request.outfit << RequestUE.outfit;
		Request.model = ModelItems::Model::OUTFIT_MODEL;
		break;
	case FUModel::DEFAULT:
	default:
		Request.model = ModelItems::Model::DEFAULT;
		break;
	}

	return Request;
}

ModelUpdates::RoomInfo& operator<<(ModelUpdates::RoomInfo& Request, const FURoomInfo& RequestUE)
{
	Request.room_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.room_id);
	Request.server_ip = (TYPE_CHAR*)GET_CHARPTR(RequestUE.server_ip);
	int size = RequestUE.players.Num();
	ModelUpdates::RoomPlayer* players = Request.players.getObjectPtr();

	for (int i = 0; i < size; i++)
	{
		players[i].near_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.players[i].near_id);
		players[i].lemon = new ModelItems::Item();
		*players[i].lemon << RequestUE.players[i].lemon;
	}

	return Request;
}

ModelUpdates::UpdateMessage& operator<<(ModelUpdates::UpdateMessage& Request, const FUUpdateMessage& RequestUE)
{
	switch (RequestUE.update)
	{
	case FUUpdateCase::NONE:
		break;
	case FUUpdateCase::ROOM_NEED_ACCEPT:
	{
		ModelUpdates::RoomNeedAccept* room_need_accept;
		Request.CreateOneof(room_need_accept);
		*room_need_accept << RequestUE.room_need_accept;
	}
	break;
	case FUUpdateCase::ROOM_ACCEPTING_CANCELED:
		break;
	case FUUpdateCase::ROOM_FOUND:
	{
		ModelUpdates::RoomInfo* roomInfo;
		Request.CreateOneof(roomInfo, RequestUE.roomInfo.players.Num());
		*roomInfo << RequestUE.roomInfo;
	}
	break;
	case FUUpdateCase::ROOM_TEAMMATES:
	{
		ModelUpdates::RoomInfo* roomInfo;
		Request.CreateOneof(roomInfo, RequestUE.roomInfo.players.Num());
		*roomInfo << RequestUE.roomInfo;
	}
	break;
	case FUUpdateCase::ROOM_READY:
	{
		ModelUpdates::RoomInfo* roomInfo;
		Request.CreateOneof(roomInfo, RequestUE.roomInfo.players.Num());
		*roomInfo << RequestUE.roomInfo;
	}
	break;
	case FUUpdateCase::BUNDLE_ITEM_PERK:
		break;
	case FUUpdateCase::DEFAULT:
		break;
	default:
		break;
	}
	//Request.room_accepting_canceled = RequestUE.room_accepting_canceled;
	return Request;
}

ModelUpdates::RoomPlayer& operator<<(ModelUpdates::RoomPlayer& Request, const FURoomPlayer& RequestUE)
{
	Request.lemon = new ModelItems::Item();
	*Request.lemon << RequestUE.lemon;
	Request.near_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.near_id);
	return Request;
}

FUUpdate& FUUpdate::operator=(const ModelUpdates::Update& update)
{
	this->id = FString(update.id);
	this->message = FString(update.message);
	this->timestamp = update.timestamp;

	return *this;
}

FURoomNeedAccept& FURoomNeedAccept::operator=(const ModelUpdates::RoomNeedAccept& RNA)
{
	this->manual_accept = RNA.manual_accept;
	this->time_to_accept = RNA.time_to_accept;

	return *this;
}

FURoomPlayer& FURoomPlayer::operator=(const ModelUpdates::RoomPlayer& RP)
{
	this->lemon = *RP.lemon;
	this->near_id = FString(RP.near_id);

	return *this;
}

FURoomInfo& FURoomInfo::operator=(const ModelUpdates::RoomInfo& RI)
{
	this->room_id = FString(RI.room_id);
	this->server_ip = FString(RI.server_ip);
	ModelUpdates::RoomPlayer* ptr = RI.players.getObjectPtr();
	for (size_t i = 0; i < RI.players.getSize(); i++)
	{
		FURoomPlayer player;
		player = ptr[i];

		this->players.Add(player);
	}

	return *this;
}

FUUpdateMessage& FUUpdateMessage::operator=(const ModelUpdates::UpdateMessage& UM)
{
	switch (UM.get_update())
	{
	case ModelUpdates::UpdateCase::ROOM_NEED_ACCEPT:
	{
		this->update = FUUpdateCase::ROOM_NEED_ACCEPT;
		ModelUpdates::RoomNeedAccept RNA = UM.getRoomNeedAccept();
		this->room_need_accept.manual_accept = RNA.manual_accept;
		this->room_need_accept.time_to_accept = RNA.time_to_accept;
	}
		break;
	case ModelUpdates::UpdateCase::ROOM_ACCEPTING_CANCELED:
		this->update = FUUpdateCase::ROOM_ACCEPTING_CANCELED;
		break;
	case ModelUpdates::UpdateCase::ROOM_FOUND:
		this->update = FUUpdateCase::ROOM_FOUND;
		this->roomInfo = UM.get_RoomInfo();
		break;
	case ModelUpdates::UpdateCase::ROOM_TEAMMATES:
		this->update = FUUpdateCase::ROOM_TEAMMATES;
		this->roomInfo = UM.get_RoomInfo();
		break;
	case ModelUpdates::UpdateCase::ROOM_READY:
		this->update = FUUpdateCase::ROOM_READY;
		this->roomInfo = UM.get_RoomInfo();
		break;
	case ModelUpdates::UpdateCase::DEFAULT:
		this->update = FUUpdateCase::DEFAULT;
		break;
	default:
		break;
	}
	return *this;
}


ModelUpdates::MessageData UWebSocket::Base64Decode(const FString& Source, TArray<uint8>& Dest)
{
	FBase64::Decode(Source, Dest);

	TCheckedPointerIterator<uint8, int32>iterator(Dest.begin());
	ModelUpdates::MessageData message_data((void*)&(*iterator), Dest.Num());

	switch (TMessage)
	{
	case TypeMessage::SIGN:
		break;
	case TypeMessage::UPDATE:
		if (OnUpdateEvent.IsBound())
		{
			gRPC_ResponseUptate ResponseUptate(&MainClient::client, message_data, ModelUpdates::Type_Updates_Message::UPDATE);
			ModelUpdates::Update read;
			ResponseUptate.readUpdate(read);
			update = read;
			OnUpdateEvent.Broadcast(update);
		}
		break;
	case TypeMessage::UPDATEMESSAGE:
		if (OnUpdateMessageEvent.IsBound())
		{
			gRPC_ResponseUptate ResponseUptate(&MainClient::client, message_data, ModelUpdates::Type_Updates_Message::UPDATE_MESSAGE);
			ModelUpdates::UpdateMessage read;
			ResponseUptate.readUpdateMessage(read);
			updateMessage = read;
			OnUpdateMessageEvent.Broadcast(updateMessage);
		}
		break;
	case TypeMessage::ROOMNEEDACCEPT:
		if (OnRoomNeedAcceptEvent.IsBound())
		{
			gRPC_ResponseUptate ResponseUptate(&MainClient::client, message_data, ModelUpdates::Type_Updates_Message::ROOM_NEED_ACCEPT);
			ModelUpdates::RoomNeedAccept read;
			ResponseUptate.readRoomNeedAccept(read);
			roomNeedAccept = read;
			OnRoomNeedAcceptEvent.Broadcast(roomNeedAccept);
		}
		break;
	case TypeMessage::ROOMINFO:
		if (OnRoomInfoEvent.IsBound())
		{
			gRPC_ResponseUptate ResponseUptate(&MainClient::client, message_data, ModelUpdates::Type_Updates_Message::ROOM_INFO);
			ModelUpdates::RoomInfo read;
			ResponseUptate.readRoomInfo(read);
			roomInfo = read;
			OnRoomInfoEvent.Broadcast(roomInfo);
		}
		break;
	case TypeMessage::ROOMPLAYER:
		if (OnRoomPlayerEvent.IsBound())
		{
			gRPC_ResponseUptate ResponseUptate(&MainClient::client, message_data, ModelUpdates::Type_Updates_Message::ROOM_PLAYER);
			ModelUpdates::RoomPlayer read;
			ResponseUptate.readRoomPlayer(read);
			roomPlayer = read;
			OnRoomPlayerEvent.Broadcast(roomPlayer);
		}
		
		break;
	default:
		break;
	}
	return message_data;
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
		if (MainClient::client != nullptr)
		{
			UHeaders.Add("near_id", MainClient::client->GetAccount());
			FString sign = MainClient::client->GetSing();
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
				FString MessageRead;
				TArray<uint8> Dest;

				TSharedPtr<FJsonObject> JsonObject;
				TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(MessageText);
				if (FJsonSerializer::Deserialize(Reader, JsonObject))
				{

					switch (TMessage)
					{
					case TypeMessage::SIGN:
						UE_LOG(WebSocketLog, All, TEXT("Received message: %s"), *MessageText);
						MessageRead = MessageText;
						break;
					case TypeMessage::UPDATE:
					case TypeMessage::UPDATEMESSAGE:
					case TypeMessage::ROOMNEEDACCEPT:
					case TypeMessage::ROOMINFO:
					case TypeMessage::ROOMPLAYER:
					default:
						FString Response = JsonObject->GetStringField("message");
						Base64Decode(MessageText, Dest);
						break;
					}
					//You can then use general JSON methods
				}

				

				OnMessageEvent.Broadcast(MessageRead);
			});

		WebSocket->OnRawMessage().AddLambda([&](const void* Data, SIZE_T Size, SIZE_T BytesRemaining) 
			{
				ModelUpdates::MessageData MessageData;
				MessageData.Data = (void*)Data;
				MessageData.ByteSize = Size;


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
	return WebSocket->IsConnected();
}

void UWebSocket::CloseConnection()
{
	if(WebSocket->IsConnected())
		WebSocket->Close();
}

void UWebSocket::WriteUpdate(FUUpdate message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		gRPC_ResponseUptate uptate(&MainClient::client, ModelUpdates::Type_Updates_Message::UPDATE);
		ModelUpdates::Update Request;
		Request << message;
		const ModelUpdates::MessageData mdata = uptate.writeUpdate(Request);
		TMessage = TypeMessage::UPDATE;
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

void UWebSocket::WriteUpdateMessage(FUUpdateMessage message, FString Address)
{

	if (WebSocket->IsConnected())
	{
		gRPC_ResponseUptate uptate(&MainClient::client, ModelUpdates::Type_Updates_Message::UPDATE_MESSAGE);
		ModelUpdates::UpdateCase updateCase;
		updateCase << message.update;
		ModelUpdates::UpdateMessage Request(updateCase);
		Request << message;
		const ModelUpdates::MessageData mdata = uptate.writeUpdateMessage(Request);
		TMessage = TypeMessage::UPDATEMESSAGE;
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

void UWebSocket::WriteRoomNeedAccept(FURoomNeedAccept message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		ModelUpdates::RoomNeedAccept Request;
		Request << message;
		gRPC_ResponseUptate uptate(&MainClient::client, ModelUpdates::Type_Updates_Message::ROOM_NEED_ACCEPT);
		const ModelUpdates::MessageData mdata = uptate.writeRoomNeedAccept(Request);
		TMessage = TypeMessage::ROOMNEEDACCEPT;
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

void UWebSocket::WriteRoomInfo(FURoomInfo message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		ModelUpdates::RoomInfo Request(message.players.Num());
		Request << message;

		gRPC_ResponseUptate uptate(&MainClient::client, ModelUpdates::Type_Updates_Message::ROOM_INFO);
		const ModelUpdates::MessageData mdata = uptate.writeRoomInfo(Request);
		TMessage = TypeMessage::ROOMINFO;
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

void UWebSocket::WriteRoomPlayer(FURoomPlayer message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		ModelUpdates::RoomPlayer Request;
		Request << message;
		gRPC_ResponseUptate uptate(&MainClient::client, ModelUpdates::Type_Updates_Message::ROOM_PLAYER);
		const ModelUpdates::MessageData mdata = uptate.writeRoomPlayer(Request);
		TMessage = TypeMessage::ROOMPLAYER;
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

