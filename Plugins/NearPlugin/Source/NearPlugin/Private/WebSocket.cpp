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
		if (UNearAuth::client != nullptr)
		{
			UHeaders.Add("near_id", UNearAuth::client->GetAccount());

			FString buff = UNearAuth::client->GetSing();
			//FString dsf = "\n";
			//FString sing = buff.Replace(*buff, *dsf);
			FString sing;
			char* chr = (char*)UNearAuth::client->GetSing();
			while (*chr != '\0')
			{
				if (*chr != '\n')
					sing += *chr;
				chr++;
			}


			UHeaders.Add("sign", sing);
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "client == nullptr");
			return;
		}
		WebSocket = FWebSocketsModule::Get().CreateWebSocket(Address, "wss", UHeaders);

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

