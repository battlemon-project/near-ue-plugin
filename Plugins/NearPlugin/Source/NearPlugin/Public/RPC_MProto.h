// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModelProto.h"
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

/**
 * 
 */

class gRPC_ClientItems : public gRPC_Stub<game::battlemon::items::ItemsService, game::battlemon::items::ItemsService::Stub>
{

public:
	gRPC_ClientItems(const bool& ssl, FString& url);

	game::battlemon::items::ItemsResponse CallRPC_GetItems();
	game::battlemon::items::GetBundlesResponse CallRPC_GetBundles();
	game::battlemon::items::WeaponBundle CallRPC_EditBundle(game::battlemon::items::EditBundleRequest& request);
	bool CallRPC_AttachBundle(game::battlemon::items::AttachBundleRequest& request);
	bool CallRPC_DetachBundle(game::battlemon::items::DetachBundleRequest& request);
};


class gRPC_ClientMM : public gRPC_Stub<game::battlemon::mm::MMService, game::battlemon::mm::MMService::Stub>
{

public:
	gRPC_ClientMM(const bool& ssl, FString& url);
	game::battlemon::mm::SearchGameResponse CallRPC_SearchGame(game::battlemon::mm::SearchGameRequest& Request);
	bool CallRPC_AcceptGame(game::battlemon::mm::AcceptGameRequest& Request);
	bool CallRPC_CancelSearch();
};

class gRPC_ClientInternalMM : public gRPC_Stub<game::battlemon::mm::internal::InternalMMService, game::battlemon::mm::internal::InternalMMService::Stub>
{
public:
	gRPC_ClientInternalMM(const bool& ssl, FString& url);
	bool CallRPC_UserLeftBattle(game::battlemon::mm::internal::InternalUserLeftBattleRequest& Request);
	bool CallRPC_SaveBattleResult(game::battlemon::mm::internal::SaveBattleResultRequest& Request);
	game::battlemon::mm::internal::RoomInfoResponse CallRPC_GetRoomInfo(game::battlemon::mm::internal::RoomInfoRequest& Request);
	game::battlemon::mm::internal::RoomInfoResponse CallRPC_CreateRoomWithPlayers(game::battlemon::mm::internal::CreateRoomRequest& Request);
	bool CallRPC_DedicatedServerIsReady(game::battlemon::mm::internal::DedicatedServerIsReadyRequest& Request);
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearItems : public UObject
{
	GENERATED_BODY()
	static gRPC_ClientItems* gRPC_Item;
	void freegRPC_Item();

public:

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UNearItems();
	~UNearItems();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	void GetItems(FUItemsResponse &out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	void GetBundles(FUGetBundlesResponse& out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	void EditBundle(FUEditBundleRequest request, FUWeaponBundle& out);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool AttachBundle(FUAttachBundleRequest request);
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool DetachBundle(FUDetachBundleRequest request);

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

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UNearMM();
	~UNearMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	void SearchGame(FUSearchGameRequest Request, FUSearchGameResponse& out);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool AcceptGame(FUAcceptGameRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool CancelSearch();

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearInternalMM : public UObject
{
	GENERATED_BODY()
	gRPC_ClientInternalMM* gRPC_InternalMM;

	void freegRPC_InternalMM();

public:

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UNearInternalMM();
	~UNearInternalMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool UserLeftBattle(FUInternalUserLeftBattleRequest Request);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool SaveBattleResult(FUSaveBattleResultRequest Request);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	void GetRoomInfo(FURoomInfoRequest Request, FURoomInfoResponse& out);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	void CreateRoomWithPlayers(FUCreateRoomRequest Request, FURoomInfoResponse& out);
	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool DedicatedServerIsReady(FUDedicatedServerIsReadyRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};