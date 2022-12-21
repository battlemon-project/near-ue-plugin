#pragma once
#include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalMm.grpc.pb.h>
#include <protocol/mm.grpc.pb.h>
#include <protocol/common.grpc.pb.h>
#include <protocol/items.grpc.pb.h>

#include "GrpcEnd.h"

#include "mm.h"
#include "common.h"
#include "items.h"


#include "internalMm.generated.h"





USTRUCT(BlueprintType)
struct FUInternalUserLeftBattleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	bool is_accident;

	FUInternalUserLeftBattleRequest& operator=(const game::battlemon::mm::internal::InternalUserLeftBattleRequest& grpcInternalUserLeftBattleRequest);

};

USTRUCT(BlueprintType)
struct FUInternalPlayerResult 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	int32 place;

	FUInternalPlayerResult& operator=(const game::battlemon::mm::internal::InternalPlayerResult& grpcInternalPlayerResult);

};

USTRUCT(BlueprintType)
struct FUSaveBattleResultRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	TArray<FUInternalPlayerResult> results;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString ott;

	FUSaveBattleResultRequest& operator=(const game::battlemon::mm::internal::SaveBattleResultRequest& grpcSaveBattleResultRequest);

};



USTRUCT(BlueprintType)
struct FURoomInfoRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString ott;

	FURoomInfoRequest& operator=(const game::battlemon::mm::internal::RoomInfoRequest& grpcRoomInfoRequest);

};

USTRUCT(BlueprintType)
struct FURoomPlayerInfo 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FUItem lemon;

	FURoomPlayerInfo& operator=(const game::battlemon::mm::internal::RoomPlayerInfo& grpcRoomPlayerInfo);

};

USTRUCT(BlueprintType)
struct FURoomInfoResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	TArray<FURoomPlayerInfo> players;

	FURoomInfoResponse& operator=(const game::battlemon::mm::internal::RoomInfoResponse& grpcRoomInfoResponse);

};


USTRUCT(BlueprintType)
struct FUCreateRoomRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	TArray<FString> near_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString prev_room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString ott;

	FUCreateRoomRequest& operator=(const game::battlemon::mm::internal::CreateRoomRequest& grpcCreateRoomRequest);

};


USTRUCT(BlueprintType)
struct FUDedicatedServerIsReadyRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalMmProto")
	FString ott;

	FUDedicatedServerIsReadyRequest& operator=(const game::battlemon::mm::internal::DedicatedServerIsReadyRequest& grpcDedicatedServerIsReadyRequest);

};


game::battlemon::mm::internal::InternalUserLeftBattleRequest &operator<<(game::battlemon::mm::internal::InternalUserLeftBattleRequest &grpcInternalUserLeftBattleRequest, const FUInternalUserLeftBattleRequest &UE);

game::battlemon::mm::internal::SaveBattleResultRequest &operator<<(game::battlemon::mm::internal::SaveBattleResultRequest &grpcSaveBattleResultRequest, const FUSaveBattleResultRequest &UE);

game::battlemon::mm::internal::InternalPlayerResult &operator<<(game::battlemon::mm::internal::InternalPlayerResult &grpcInternalPlayerResult, const FUInternalPlayerResult &UE);

game::battlemon::mm::internal::RoomInfoRequest &operator<<(game::battlemon::mm::internal::RoomInfoRequest &grpcRoomInfoRequest, const FURoomInfoRequest &UE);

game::battlemon::mm::internal::RoomInfoResponse &operator<<(game::battlemon::mm::internal::RoomInfoResponse &grpcRoomInfoResponse, const FURoomInfoResponse &UE);

game::battlemon::mm::internal::RoomPlayerInfo &operator<<(game::battlemon::mm::internal::RoomPlayerInfo &grpcRoomPlayerInfo, const FURoomPlayerInfo &UE);

game::battlemon::mm::internal::CreateRoomRequest &operator<<(game::battlemon::mm::internal::CreateRoomRequest &grpcCreateRoomRequest, const FUCreateRoomRequest &UE);

game::battlemon::mm::internal::DedicatedServerIsReadyRequest &operator<<(game::battlemon::mm::internal::DedicatedServerIsReadyRequest &grpcDedicatedServerIsReadyRequest, const FUDedicatedServerIsReadyRequest &UE);

