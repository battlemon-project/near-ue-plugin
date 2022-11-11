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
DECLARE_LOG_CATEGORY_EXTERN(WebSocketLog, Error, All);
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageDelegate, const FString&, MessageString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketConnectedDelegate);
/*
USTRUCT(BlueprintType)
struct FUUpdate 
{
    GENERATED_BODY()

    FString id; // update id
    int64 timestamp; // millisec
    FString message; //UpdateMessage's bytes in base64
};

USTRUCT(BlueprintType)
struct FURoomNeedAccept
{
    GENERATED_BODY()

    bool manual_accept;
    int time_to_accept;
};


USTRUCT(BlueprintType)
struct FURoomPlayer
{
    GENERATED_BODY()

    FString near_id;
    FUItem lemon;
};

USTRUCT(BlueprintType)
struct FURoomInfo
{
    GENERATED_BODY()

    FString room_id;
    FString server_ip;
    TArray<FURoomPlayer> players;
};

USTRUCT(BlueprintType)
struct FUUpdateMessage 
{
    GENERATED_BODY()

    FURoomNeedAccept room_need_accept;
    //common.Empty room_accepting_canceled = 2;
    FURoomInfo room_found;
    FURoomInfo room_teammates;
    FURoomInfo room_ready;
};
*/



UCLASS(BlueprintType)
class NEARPLUGIN_API UWebSocket : public UObject
{

	GENERATED_BODY()
	TSharedPtr<IWebSocket> WebSocket;

public:

	UWebSocket();
	~UWebSocket();


	UFUNCTION(BlueprintCallable, Category = ".Near | Verify")
	void CreateWebSocet(FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

	UFUNCTION(BlueprintCallable, Category = ".Near | Verify")
	bool IsConnected();

	UPROPERTY(BlueprintAssignable, Category = ".Near | Verify")
	FWebSocketMessageDelegate OnMessageEvent;
	UPROPERTY(BlueprintAssignable, Category = ".Near | Verify")
	FWebSocketConnectedDelegate OnConnectedEvent;
	UPROPERTY(BlueprintAssignable, Category = ".Near | Verify")
	FWebSocketMessageDelegate OnErrorEvent;
};
