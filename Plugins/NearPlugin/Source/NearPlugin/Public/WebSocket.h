// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <WebSockets/Public/IWebSocket.h>
#include <WebSockets/Public/WebSocketsModule.h>
#include "NearAuth.h"
#include "Misc/Base64.h"
#include <include/gRPCResponse.h>

#include "WebSocket.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(WebSocketLog, Error, All);
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWebSocketMessageDelegate, const FString&, MessageString);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWebSocketConnectedDelegate);

USTRUCT(BlueprintType)
struct FUUpdate 
{
    GENERATED_BODY()

    FString id; // update id
    int64 timestamp; // millisec
    FString message; //UpdateMessage's bytes in base64

    FUUpdate& operator=(const ModelUpdates::Update& update);
};

USTRUCT(BlueprintType)
struct FURoomNeedAccept
{
    GENERATED_BODY()

    bool manual_accept;
    int time_to_accept;

    FURoomNeedAccept& operator=(const ModelUpdates::RoomNeedAccept& RNA);
};

UENUM(BlueprintType)
enum class FUUpdateCase : uint8
{
    NONE UMETA(DisplayName = "NONE"),
    ROOM_NEED_ACCEPT UMETA(DisplayName = "ROOM_NEED_ACCEPT"),
    ROOM_ACCEPTING_CANCELED UMETA(DisplayName = "ROOM_ACCEPTING_CANCELED"),
    ROOM_FOUND UMETA(DisplayName = "ROOM_FOUND"),
    ROOM_TEAMMATES UMETA(DisplayName = "ROOM_TEAMMATES"),
    ROOM_READY UMETA(DisplayName = "ROOM_READY"),
    BUNDLE_ITEM_PERK UMETA(DisplayName = "BUNDLE_ITEM_PERK"),
    DEFAULT UMETA(DisplayName = "DEFAULT")
};

USTRUCT(BlueprintType)
struct FURoomPlayer
{
    GENERATED_BODY()

    FString near_id;
    FUItem lemon;

    FURoomPlayer& operator=(const ModelUpdates::RoomPlayer& RP);
};

USTRUCT(BlueprintType)
struct FURoomInfo
{
    GENERATED_BODY()

    FString room_id;
    FString server_ip;
    TArray<FURoomPlayer> players;

    FURoomInfo& operator=(const ModelUpdates::RoomInfo& RI);
};

USTRUCT(BlueprintType)
struct FUUpdateMessage 
{
    GENERATED_BODY()

    FUUpdateCase update;
    FURoomNeedAccept room_need_accept;
    //common.Empty room_accepting_canceled;
    FURoomInfo roomInfo;

    FUUpdateMessage& operator=(const ModelUpdates::UpdateMessage& UM);
};

enum class TypeMessage
{
    SIGN,
    UPDATE,
    UPDATEMESSAGE,
    ROOMNEEDACCEPT,
    ROOMINFO,
    ROOMPLAYER
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoomInfoDelegate, const FURoomInfo&, Room_Info);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRoomNeedAcceptDelegate, const FURoomNeedAccept&, Room_Need_Accept);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FURoomPlayerDelegate, const FURoomPlayer&, Room_Player);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUUpdateMessageDelegate, const FUUpdateMessage&, Update_Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUUpdateDelegate, const FUUpdate&, Update);

UCLASS(BlueprintType)
class NEARPLUGIN_API UWebSocket : public UObject
{

	GENERATED_BODY()
	TSharedPtr<IWebSocket> WebSocket;
    ModelUpdates::MessageData Base64Decode(const FString& Source, TArray<uint8> &Dest);
    TypeMessage TMessage;
    FUUpdate update;
    FUUpdateMessage updateMessage;
    FURoomNeedAccept roomNeedAccept;
    FURoomInfo roomInfo;
    FURoomPlayer roomPlayer;

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
    FRoomInfoDelegate OnRoomInfoEvent;
    UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
    FRoomNeedAcceptDelegate OnRoomNeedAcceptEvent;
    UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
    FURoomPlayerDelegate OnRoomPlayerEvent;
    UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
    FUUpdateMessageDelegate OnUpdateMessageEvent;
    UPROPERTY(BlueprintAssignable, Category = ".Near | WebSocet")
    FUUpdateDelegate OnUpdateEvent;

    UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Proto | Update")
    void WriteUpdate(FUUpdate message,FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

    UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Proto | Update")
    void WriteUpdateMessage(FUUpdateMessage message, FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

    UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Proto | Update")
    void WriteRoomNeedAccept(FURoomNeedAccept message, FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

    UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Proto | Update")
    void WriteRoomInfo(FURoomInfo message, FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");

    UFUNCTION(BlueprintCallable, Category = ".Near | WebSocet | Proto | Update")
    void WriteRoomPlayer(FURoomPlayer message, FString Address = "wss://0n64i8m4o8.execute-api.us-east-1.amazonaws.com/test");
};
