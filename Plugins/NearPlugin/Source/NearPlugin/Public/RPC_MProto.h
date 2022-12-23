// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "items.h"
#include "mm.h"
#include "internalMm.h"
#include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/common.grpc.pb.h>
#include <protocol/items.grpc.pb.h>
#include <protocol/internalMm.grpc.pb.h>
#include <protocol/mm.grpc.pb.h>
#include <protocol/updates.grpc.pb.h>

#include "GrpcEnd.h"

#include "UObject/NoExportTypes.h"
#include "RPC_MProto.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStructResultDelegate);

/**
 * 
 */


class gRPC_ClientItems : public gRPC_Stub<game::battlemon::items::ItemsService, game::battlemon::items::ItemsService::Stub>
{
public:
	gRPC_ClientItems(const bool& ssl, FString& url);
	game::battlemon::items::ItemsResponse CallRPC_GetItems();
	game::battlemon::items::GetBundlesResponse CallRPC_GetBundles();
	game::battlemon::items::WeaponBundle CallRPC_EditBundle(game::battlemon::items::EditBundleRequest* request);
	bool CallRPC_AttachBundle(game::battlemon::items::AttachBundleRequest* request);
	bool CallRPC_DetachBundle(game::battlemon::items::DetachBundleRequest* request);
};


class gRPC_ClientMM : public gRPC_Stub<game::battlemon::mm::MMService, game::battlemon::mm::MMService::Stub>
{
public:
	gRPC_ClientMM(const bool& ssl, FString& url);
	game::battlemon::mm::SearchGameResponse CallRPC_SearchGame(game::battlemon::mm::SearchGameRequest* Request);
	bool CallRPC_AcceptGame(game::battlemon::mm::AcceptGameRequest* Request);
	bool CallRPC_CancelSearch();
};


class gRPC_ClientInternalMM : public gRPC_Stub<game::battlemon::mm::internal::InternalMMService, game::battlemon::mm::internal::InternalMMService::Stub>
{
public:
	gRPC_ClientInternalMM(const bool& ssl, FString& url);
	bool CallRPC_UserLeftBattle(game::battlemon::mm::internal::InternalUserLeftBattleRequest* Request);
	bool CallRPC_SaveBattleResult(game::battlemon::mm::internal::SaveBattleResultRequest* Request);
	game::battlemon::mm::internal::RoomInfoResponse CallRPC_GetRoomInfo(game::battlemon::mm::internal::RoomInfoRequest* Request);
	game::battlemon::mm::internal::RoomInfoResponse CallRPC_CreateRoomWithPlayers(game::battlemon::mm::internal::CreateRoomRequest* Request);
	bool CallRPC_DedicatedServerIsReady(game::battlemon::mm::internal::DedicatedServerIsReadyRequest* Request);
};


UCLASS(Blueprintable)
class NEARPLUGIN_API UNearItems : public UObject
{
	GENERATED_BODY()
	static gRPC_ClientItems* gRPC_Item;
	void freegRPC_Item();

public:

	UPROPERTY(BlueprintReadWrite, Category = ".Near| ItemsProto", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| ItemsProto", meta = (ExposeOnSpawn = true))
	bool ssl = true;


	UPROPERTY(BlueprintAssignable, Category = ".Near | ItemsProto")
	FStructResultDelegate structResultDelegate;

	UNearItems();
	~UNearItems();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	void GetItems(FUItemsResponse &out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	void GetBundles(FUGetBundlesResponse& out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	void EditBundle(FUEditBundleRequest Request, FUWeaponBundle& out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool AttachBundle(FUAttachBundleRequest Request, bool& out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool DetachBundle(FUDetachBundleRequest Request, bool& out);

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearMM : public	UObject
{
	GENERATED_BODY()
	static gRPC_ClientMM* gRPC_MM;

	void freegRPC_MM();

public:

	UPROPERTY(BlueprintReadWrite, Category = ".Near| MMProto", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| MMProto", meta = (ExposeOnSpawn = true))
	bool ssl = true;
	
	UPROPERTY(BlueprintAssignable, Category = ".Near | MMProto")
	FStructResultDelegate structResultDelegate;

	UNearMM();
	~UNearMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	void SearchGame(FUSearchGameRequest Request, FUSearchGameResponse& out);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool AcceptGame(FUAcceptGameRequest Request, bool& out);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool CancelSearch(bool& out);

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearInternalMM : public UObject
{
	GENERATED_BODY()
	static gRPC_ClientInternalMM* gRPC_InternalMM;

	void freegRPC_InternalMM();

public:

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	FString GetEnvironmentVariable(FString VarName);

	UPROPERTY(BlueprintReadWrite, Category = ".Near| InternalMMProto", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| InternalMMProto", meta = (ExposeOnSpawn = true))
	bool ssl = true;
	
	UPROPERTY(BlueprintAssignable, Category = ".Near | InternalMMProto")
	FStructResultDelegate structResultDelegate;

	UNearInternalMM();
	~UNearInternalMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool UserLeftBattle(FUInternalUserLeftBattleRequest Request, bool& out);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool SaveBattleResult(FUSaveBattleResultRequest Request, bool& out);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	void GetRoomInfo(FURoomInfoRequest Request, FURoomInfoResponse& out);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	void CreateRoomWithPlayers(FUCreateRoomRequest Request, FURoomInfoResponse& out);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool DedicatedServerIsReady(FUDedicatedServerIsReadyRequest Request, bool& out);

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};