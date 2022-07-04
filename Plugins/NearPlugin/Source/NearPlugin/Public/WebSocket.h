// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <WebSockets/Public/IWebSocket.h>
#include <WebSockets/Public/WebSocketsModule.h>

#include "WebSocket.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageDelegate, const FString&, MessageString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketConnectedDelegate);


UCLASS(BlueprintType)
class NEARPLUGIN_API UWebSocket : public UObject
{

	GENERATED_BODY()
	TSharedPtr<IWebSocket> WebSocket;

public:

	UWebSocket();
	~UWebSocket();
	void CreateWebSocet(FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

	UFUNCTION(BlueprintCallable, Category = ".Near | Verify")
	bool IsConnected();

	UFUNCTION(BlueprintCallable, Category = ".Near | Verify")
	void VerifySing();

	UPROPERTY(BlueprintAssignable, Category = ".Near | Verify")
	FWebSocketMessageDelegate OnMessageEvent;
	UPROPERTY(BlueprintAssignable, Category = ".Near | Verify")
	FWebSocketConnectedDelegate OnConnectedEvent;
	UPROPERTY(BlueprintAssignable, Category = ".Near | Verify")
	FWebSocketMessageDelegate OnErrorEvent;
};
