#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalItems.grpc.pb.h>
#include <protocol/items.grpc.pb.h>
#include <protocol/common.grpc.pb.h>

#include "GrpcEnd.h"

#include "items.h"
#include "common.h"


#include "internalItems.generated.h"





USTRUCT(BlueprintType)
struct FUInternalRemoveUserItemsRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	FString user_id;

	FUInternalRemoveUserItemsRequest& operator=(const game::battlemon::items::internal::InternalRemoveUserItemsRequest& grpcInternalRemoveUserItemsRequest);

};


USTRUCT(BlueprintType)
struct FUInternalInitUserItemsRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	FString user_id;

	FUInternalInitUserItemsRequest& operator=(const game::battlemon::items::internal::InternalInitUserItemsRequest& grpcInternalInitUserItemsRequest);

};


USTRUCT(BlueprintType)
struct FUInternalUserLemon 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	FUItem lemon;

	FUInternalUserLemon& operator=(const game::battlemon::items::internal::InternalUserLemon& grpcInternalUserLemon);

};


USTRUCT(BlueprintType)
struct FUInternalLemonsInfoResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	TArray<FUInternalUserLemon> user_lemons;

	FUInternalLemonsInfoResponse& operator=(const game::battlemon::items::internal::InternalLemonsInfoResponse& grpcInternalLemonsInfoResponse);

};


USTRUCT(BlueprintType)
struct FUInternalUserLemonID 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	FString user_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	FString lemon_id;

	FUInternalUserLemonID& operator=(const game::battlemon::items::internal::InternalUserLemonID& grpcInternalUserLemonID);

};


USTRUCT(BlueprintType)
struct FUInternalLemonsInfoRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalItemsProto")
	TArray<FUInternalUserLemonID> user_lemonids;

	FUInternalLemonsInfoRequest& operator=(const game::battlemon::items::internal::InternalLemonsInfoRequest& grpcInternalLemonsInfoRequest);

};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInternalGetLemonsInfoDelegate, const FUInternalLemonsInfoResponse&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInternalInitUserItemsDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInternalRemoveUserItemsDelegate, const FUEmpty&, Response); 



class RPC_InternalItemsService : public gRPC_Stub<game::battlemon::items::internal::InternalItemsService, game::battlemon::items::internal::InternalItemsService::Stub>
{
	void* Delegate;
	void* out;
public:
	RPC_InternalItemsService(const bool& ssl, FString& url, void* _Delegate, void* _out);
	~RPC_InternalItemsService();

	game::battlemon::items::internal::InternalLemonsInfoResponse InternalGetLemonsInfo(grpc::ClientContext* context, const game::battlemon::items::internal::InternalLemonsInfoRequest* request);
	game::battlemon::common::Empty InternalInitUserItems(grpc::ClientContext* context, const game::battlemon::items::internal::InternalInitUserItemsRequest* request);
	game::battlemon::common::Empty InternalRemoveUserItems(grpc::ClientContext* context, const game::battlemon::items::internal::InternalRemoveUserItemsRequest* request);
	
};

enum class InternalItemsServiceRPC
{
	InternalGetLemonsInfo,
	InternalInitUserItems,
	InternalRemoveUserItems,
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UInternalItemsService : public UObject
{
	GENERATED_BODY()

	void free_RPC_InternalItemsService();
	static RPC_InternalItemsService* _RPC_InternalItemsService;
	InternalItemsServiceRPC rpc;

public:
	UInternalItemsService();
	~UInternalItemsService();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | InternalItemsService", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Crypto| InternalItemsService", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalItemsService")
	FInternalGetLemonsInfoDelegate InternalGetLemonsInfoDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalItemsService")
	FInternalInitUserItemsDelegate InternalInitUserItemsDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalItemsService")
	FInternalRemoveUserItemsDelegate InternalRemoveUserItemsDelegate;

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalItemsService")
	void InternalGetLemonsInfo(TMap<FString, FString> context, FUInternalLemonsInfoRequest inp, FUInternalLemonsInfoResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalItemsService")
	void InternalInitUserItems(TMap<FString, FString> context, FUInternalInitUserItemsRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalItemsService")
	void InternalRemoveUserItems(TMap<FString, FString> context, FUInternalRemoveUserItemsRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalItemsService")
	FString GetError();
};



game::battlemon::items::internal::InternalRemoveUserItemsRequest &operator<<(game::battlemon::items::internal::InternalRemoveUserItemsRequest &grpcInternalRemoveUserItemsRequest, const FUInternalRemoveUserItemsRequest &UE);

game::battlemon::items::internal::InternalInitUserItemsRequest &operator<<(game::battlemon::items::internal::InternalInitUserItemsRequest &grpcInternalInitUserItemsRequest, const FUInternalInitUserItemsRequest &UE);

game::battlemon::items::internal::InternalUserLemon &operator<<(game::battlemon::items::internal::InternalUserLemon &grpcInternalUserLemon, const FUInternalUserLemon &UE);

game::battlemon::items::internal::InternalLemonsInfoResponse &operator<<(game::battlemon::items::internal::InternalLemonsInfoResponse &grpcInternalLemonsInfoResponse, const FUInternalLemonsInfoResponse &UE);

game::battlemon::items::internal::InternalUserLemonID &operator<<(game::battlemon::items::internal::InternalUserLemonID &grpcInternalUserLemonID, const FUInternalUserLemonID &UE);

game::battlemon::items::internal::InternalLemonsInfoRequest &operator<<(game::battlemon::items::internal::InternalLemonsInfoRequest &grpcInternalLemonsInfoRequest, const FUInternalLemonsInfoRequest &UE);

