// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket.h"
#include "NearAuth.h"

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
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(Address, "wss", UHeaders);

		WebSocket->OnMessage().AddLambda([&](FString MessageText)
			{
				UE_LOG(WebSocketLog, All, TEXT("Received message: %s"), *MessageText);
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
	return WebSocket->IsConnected();
}

