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
struct FUDedicatedServerIsReadyRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString ott;

	FUDedicatedServerIsReadyRequest& operator=(const game::battlemon::mm::internal::DedicatedServerIsReadyRequest& grpcDedicatedServerIsReadyRequest);

};


USTRUCT(BlueprintType)
struct FUCreateRoomRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	TArray<FString> user_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString prev_room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString ott;

	FUCreateRoomRequest& operator=(const game::battlemon::mm::internal::CreateRoomRequest& grpcCreateRoomRequest);

};


USTRUCT(BlueprintType)
struct FURoomPlayerInfo 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FUItem lemon;

	FURoomPlayerInfo& operator=(const game::battlemon::mm::internal::RoomPlayerInfo& grpcRoomPlayerInfo);

};


USTRUCT(BlueprintType)
struct FURoomInfoResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	TArray<FURoomPlayerInfo> players;

	FURoomInfoResponse& operator=(const game::battlemon::mm::internal::RoomInfoResponse& grpcRoomInfoResponse);

};


USTRUCT(BlueprintType)
struct FURoomInfoRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString ott;

	FURoomInfoRequest& operator=(const game::battlemon::mm::internal::RoomInfoRequest& grpcRoomInfoRequest);

};


USTRUCT(BlueprintType)
struct FUInternalPlayerResult 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	int32 place;

	FUInternalPlayerResult& operator=(const game::battlemon::mm::internal::InternalPlayerResult& grpcInternalPlayerResult);

};


USTRUCT(BlueprintType)
struct FUSaveBattleResultRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	TArray<FUInternalPlayerResult> results;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString ott;

	FUSaveBattleResultRequest& operator=(const game::battlemon::mm::internal::SaveBattleResultRequest& grpcSaveBattleResultRequest);

};


USTRUCT(BlueprintType)
struct FUInternalUserLeftBattleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalMmProto")
	bool is_accident;

	FUInternalUserLeftBattleRequest& operator=(const game::battlemon::mm::internal::InternalUserLeftBattleRequest& grpcInternalUserLeftBattleRequest);

};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCreateRoomWithPlayersDelegate, const FURoomInfoResponse&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDedicatedServerIsReadyDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetRoomInfoDelegate, const FURoomInfoResponse&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaveBattleResultDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUserLeftBattleDelegate, const FUEmpty&, Response); 



class RPC_InternalMMService : public gRPC_Stub<game::battlemon::mm::internal::InternalMMService, game::battlemon::mm::internal::InternalMMService::Stub>
{
	void* Delegate;
	void* out;
public:
	RPC_InternalMMService(const bool& ssl, FString& url, void* _Delegate, void* _out);
	~RPC_InternalMMService();

	game::battlemon::common::Empty UserLeftBattle(grpc::ClientContext* context, const game::battlemon::mm::internal::InternalUserLeftBattleRequest* request);
	game::battlemon::common::Empty SaveBattleResult(grpc::ClientContext* context, const game::battlemon::mm::internal::SaveBattleResultRequest* request);
	game::battlemon::mm::internal::RoomInfoResponse GetRoomInfo(grpc::ClientContext* context, const game::battlemon::mm::internal::RoomInfoRequest* request);
	game::battlemon::mm::internal::RoomInfoResponse CreateRoomWithPlayers(grpc::ClientContext* context, const game::battlemon::mm::internal::CreateRoomRequest* request);
	game::battlemon::common::Empty DedicatedServerIsReady(grpc::ClientContext* context, const game::battlemon::mm::internal::DedicatedServerIsReadyRequest* request);
	
};

enum class InternalMMServiceRPC
{
	UserLeftBattle,
	SaveBattleResult,
	GetRoomInfo,
	CreateRoomWithPlayers,
	DedicatedServerIsReady,
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UInternalMMService : public UObject
{
	GENERATED_BODY()

	void free_RPC_InternalMMService();
	static RPC_InternalMMService* _RPC_InternalMMService;
	InternalMMServiceRPC rpc;

public:
	UInternalMMService();
	~UInternalMMService();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | InternalMMService", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Crypto| InternalMMService", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalMMService")
	FCreateRoomWithPlayersDelegate CreateRoomWithPlayersDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalMMService")
	FDedicatedServerIsReadyDelegate DedicatedServerIsReadyDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalMMService")
	FGetRoomInfoDelegate GetRoomInfoDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalMMService")
	FSaveBattleResultDelegate SaveBattleResultDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalMMService")
	FUserLeftBattleDelegate UserLeftBattleDelegate;

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalMMService")
	void UserLeftBattle(TMap<FString, FString> context, FUInternalUserLeftBattleRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalMMService")
	void SaveBattleResult(TMap<FString, FString> context, FUSaveBattleResultRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalMMService")
	void GetRoomInfo(TMap<FString, FString> context, FURoomInfoRequest inp, FURoomInfoResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalMMService")
	void CreateRoomWithPlayers(TMap<FString, FString> context, FUCreateRoomRequest inp, FURoomInfoResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalMMService")
	void DedicatedServerIsReady(TMap<FString, FString> context, FUDedicatedServerIsReadyRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalMMService")
	FString GetError();
};



game::battlemon::mm::internal::DedicatedServerIsReadyRequest &operator<<(game::battlemon::mm::internal::DedicatedServerIsReadyRequest &grpcDedicatedServerIsReadyRequest, const FUDedicatedServerIsReadyRequest &UE);

game::battlemon::mm::internal::CreateRoomRequest &operator<<(game::battlemon::mm::internal::CreateRoomRequest &grpcCreateRoomRequest, const FUCreateRoomRequest &UE);

game::battlemon::mm::internal::RoomPlayerInfo &operator<<(game::battlemon::mm::internal::RoomPlayerInfo &grpcRoomPlayerInfo, const FURoomPlayerInfo &UE);

game::battlemon::mm::internal::RoomInfoResponse &operator<<(game::battlemon::mm::internal::RoomInfoResponse &grpcRoomInfoResponse, const FURoomInfoResponse &UE);

game::battlemon::mm::internal::RoomInfoRequest &operator<<(game::battlemon::mm::internal::RoomInfoRequest &grpcRoomInfoRequest, const FURoomInfoRequest &UE);

game::battlemon::mm::internal::InternalPlayerResult &operator<<(game::battlemon::mm::internal::InternalPlayerResult &grpcInternalPlayerResult, const FUInternalPlayerResult &UE);

game::battlemon::mm::internal::SaveBattleResultRequest &operator<<(game::battlemon::mm::internal::SaveBattleResultRequest &grpcSaveBattleResultRequest, const FUSaveBattleResultRequest &UE);

game::battlemon::mm::internal::InternalUserLeftBattleRequest &operator<<(game::battlemon::mm::internal::InternalUserLeftBattleRequest &grpcInternalUserLeftBattleRequest, const FUInternalUserLeftBattleRequest &UE);

