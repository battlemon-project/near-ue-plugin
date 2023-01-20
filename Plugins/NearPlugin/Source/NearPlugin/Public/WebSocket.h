// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Array.h"
#include <WebSockets/Public/IWebSocket.h>
#include <WebSockets/Public/WebSocketsModule.h>
#include "Misc/Base64.h"

#include"updates.h"

#include "WebSocket.generated.h"


/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(WebSocketLog, Error, All);
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageDelegate, const FString&, MessageString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketConnectedDelegate);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateMessageDelegate, const FUUpdateMessage&, Update_Message);

UCLASS(BlueprintType)
class NEARPLUGIN_API UWebSocket : public UObject
{

	GENERATED_BODY()
	TSharedPtr<IWebSocket> WebSocket;
    void Base64Decode(const FString& Source, TArray<uint8> &Dest);
	FUUpdateMessage updateMessage;

public:

	UWebSocket();
	~UWebSocket();


	UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Verify")
	void CreateWebSocet(FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

	UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Verify")
	bool IsConnected();

    UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Verify")
    void CloseConnection();

	UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
	FWebSocketMessageDelegate OnMessageEvent;
	UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
	FWebSocketConnectedDelegate OnConnectedEvent;
	UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
	FWebSocketMessageDelegate OnErrorEvent;

    UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
    FUpdateMessageDelegate OnUpdateMessageEvent;
};
