// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket.h"


DEFINE_LOG_CATEGORY(WebSocketLog);

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
				UE_LOG(WebSocketLog, All, TEXT("Received message: %s"), *MessageText);
				OnMessageEvent.Broadcast(MessageText);
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

ModelUpdates::Update& operator<<(ModelUpdates::Update& Request, const FUUpdate& RequestUE)
{
	Request.id = GET_CHARPTR(RequestUE.id);
	Request.message = GET_CHARPTR(RequestUE.message);
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

ModelUpdates::RoomInfo& operator<<(ModelUpdates::RoomInfo& Request, const FURoomInfo& RequestUE)
{
	Request.room_id = GET_CHARPTR(RequestUE.room_id);
	Request.server_ip = GET_CHARPTR(RequestUE.server_ip);

	//for (int i = 0; i < RequestUE.players.Num(); i++)
	//{
	//	Request.players = RequestUE.players;
	//}

	return Request;
}

ModelUpdates::UpdateMessage& operator<<(ModelUpdates::UpdateMessage& Request, const FUUpdateMessage& RequestUE)
{
	
	Request.update << RequestUE.update;
	Request.room_need_accept << RequestUE.room_need_accept;
	//Request.room_accepting_canceled = RequestUE.room_accepting_canceled;
	Request.room_found << RequestUE.room_found;
	Request.room_teammates << RequestUE.room_teammates;
	Request.room_ready << RequestUE.room_ready;
	return Request;
}

void UWebSocket::WriteUpdate(FUUpdate message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		gRPC_ResponseUptate uptate;
		ModelUpdates::Update Request;
		Request << message;
		const ModelUpdates::MessageData mdata = uptate.writeUpdate(Request);
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
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

void UWebSocket::WriteUpdateMessage(FUUpdateMessage message, FString Address)
{

	if (WebSocket->IsConnected())
	{
		gRPC_ResponseUptate uptate;
		ModelUpdates::UpdateMessage Request;
		Request << message;
		ObjectList<ModelUpdates::RoomPlayer> players[3] = { message.room_found.players.Num() ,message.room_teammates.players.Num(), message.room_ready.players.Num() };
		for (int i = 0; i < 3; i++)
		{
			TArray<FURoomPlayer>* playersPtr = nullptr;
			switch (i)
			{
			case 0:
				playersPtr = &message.room_found.players;
				break;
			case 1:
				playersPtr = &message.room_teammates.players;
				break;
			case 2:
				playersPtr = &message.room_ready.players;
				break;
			}

			for (int j = 0; j < playersPtr->Num(); j++)
			{
				players[i].getObjectPtr()->lemon << (*playersPtr)[j].lemon;
				players[i].getObjectPtr()->near_id = (TYPE_CHAR*)GET_CHARPTR((*playersPtr)[j].near_id);
			}
		}
		Request.room_found.players = &players[0];
		Request.room_teammates.players = &players[1];
		Request.room_ready.players = &players[2];

		const ModelUpdates::MessageData mdata = uptate.writeUpdateMessage(Request);
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

void UWebSocket::WriteRoomNeedAccept(FURoomNeedAccept message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		ModelUpdates::RoomNeedAccept Request;
		Request << message;
		gRPC_ResponseUptate uptate;
		const ModelUpdates::MessageData mdata = uptate.writeRoomNeedAccept(Request);
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

void UWebSocket::WriteRoomInfo(FURoomInfo message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		ModelUpdates::RoomInfo Request;
		Request << message;
		ObjectList<ModelUpdates::RoomPlayer> players(message.players.Num());
		Request.players = &players;
		for (int i = 0; i < message.players.Num(); i++)
		{
			players.getObjectPtr()[i].lemon << message.players[i].lemon;
			players.getObjectPtr()[i].near_id = (TYPE_CHAR*)GET_CHARPTR(message.players[i].near_id);
		}

		gRPC_ResponseUptate uptate;
		const ModelUpdates::MessageData mdata = uptate.writeRoomInfo(Request);
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

ModelUpdates::RoomPlayer& operator<<(ModelUpdates::RoomPlayer& Request, const FURoomPlayer& RequestUE)
{
	Request.lemon << RequestUE.lemon;
	Request.near_id = (TYPE_CHAR*)GET_CHARPTR(RequestUE.near_id);
	return Request;
}

void UWebSocket::WriteRoomPlayer(FURoomPlayer message, FString Address)
{
	if (WebSocket->IsConnected())
	{
		ModelUpdates::RoomPlayer Request;
		Request << message;
		gRPC_ResponseUptate uptate;
		const ModelUpdates::MessageData mdata = uptate.writeRoomPlayer(Request);
		WebSocket->Send(mdata.Data, mdata.ByteSize, true);
	}
}

