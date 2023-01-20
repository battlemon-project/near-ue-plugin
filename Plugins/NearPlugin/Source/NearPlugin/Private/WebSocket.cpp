// Fill out your copyright notice in the Description page of Project Settings.

#include "WebSocket.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include <CryptoClient.h>

DEFINE_LOG_CATEGORY(WebSocketLog);


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
		if (!UCryptoClient::GetWalletAddress().IsEmpty())
		{
			UHeaders.Add("wallet_address", UCryptoClient::GetWalletAddress());
		//	UHeaders.Add("sign", UCryptoClient::GetSing());
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
