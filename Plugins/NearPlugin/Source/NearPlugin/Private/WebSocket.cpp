// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket.h"
#include "NearAuth.h"

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
		if (client != nullptr)
		{
			UHeaders.Add("near_id", client->GetAccount());
			FString sing = client->GetSing();
			sing = sing.Replace(*sing, TEXT("\n"));
			UHeaders.Add("sign", sing);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "client == nullptr");
			return;
		}
		WebSocket = FWebSocketsModule::Get().CreateWebSocket("wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test", "wss", UHeaders);

		WebSocket->OnMessage().AddLambda([&](FString MessageText)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Cyan, "Received message: " + MessageText);
				OnMessageEvent.Broadcast(MessageText);
			});

		WebSocket->OnConnected().AddLambda([&]()
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, "Successfully connected");
				OnConnectedEvent.Broadcast();
			});
		WebSocket->OnConnectionError().AddLambda([&](FString error)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, error);
				OnErrorEvent.Broadcast(error);
			});
	}
	WebSocket->Connect();
}

bool UWebSocket::IsConnected()
{
	return WebSocket->IsConnected();
}

