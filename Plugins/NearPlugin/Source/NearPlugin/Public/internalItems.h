#pragma once
#include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalItems.grpc.pb.h>
#include <protocol/items.grpc.pb.h>

#include "GrpcEnd.h"

#include "items.h"


#include "internalItems.generated.h"





USTRUCT(BlueprintType)
struct FUIsOwnerRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	TArray<FString> nft_ids;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	FString near_id;

	FUIsOwnerRequest& operator=(const game::battlemon::items::internal::IsOwnerRequest& grpcIsOwnerRequest);

};


USTRUCT(BlueprintType)
struct FUIsOwnerResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	bool result;

	FUIsOwnerResponse& operator=(const game::battlemon::items::internal::IsOwnerResponse& grpcIsOwnerResponse);

};

USTRUCT(BlueprintType)
struct FUInternalUserLemonID 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	FString lemon_id;

	FUInternalUserLemonID& operator=(const game::battlemon::items::internal::InternalUserLemonID& grpcInternalUserLemonID);

};

USTRUCT(BlueprintType)
struct FUInternalLemonsInfoRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	TArray<FUInternalUserLemonID> users_lemonids;

	FUInternalLemonsInfoRequest& operator=(const game::battlemon::items::internal::InternalLemonsInfoRequest& grpcInternalLemonsInfoRequest);

};

USTRUCT(BlueprintType)
struct FUInternalUserLemon 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	FUItem lemon;

	FUInternalUserLemon& operator=(const game::battlemon::items::internal::InternalUserLemon& grpcInternalUserLemon);

};

USTRUCT(BlueprintType)
struct FUInternalLemonsInfoResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalItemsProto")
	TArray<FUInternalUserLemon> users_lemons;

	FUInternalLemonsInfoResponse& operator=(const game::battlemon::items::internal::InternalLemonsInfoResponse& grpcInternalLemonsInfoResponse);

};





game::battlemon::items::internal::IsOwnerRequest &operator<<(game::battlemon::items::internal::IsOwnerRequest &grpcIsOwnerRequest, const FUIsOwnerRequest &UE);

game::battlemon::items::internal::IsOwnerResponse &operator<<(game::battlemon::items::internal::IsOwnerResponse &grpcIsOwnerResponse, const FUIsOwnerResponse &UE);

game::battlemon::items::internal::InternalLemonsInfoRequest &operator<<(game::battlemon::items::internal::InternalLemonsInfoRequest &grpcInternalLemonsInfoRequest, const FUInternalLemonsInfoRequest &UE);

game::battlemon::items::internal::InternalUserLemonID &operator<<(game::battlemon::items::internal::InternalUserLemonID &grpcInternalUserLemonID, const FUInternalUserLemonID &UE);

game::battlemon::items::internal::InternalLemonsInfoResponse &operator<<(game::battlemon::items::internal::InternalLemonsInfoResponse &grpcInternalLemonsInfoResponse, const FUInternalLemonsInfoResponse &UE);

game::battlemon::items::internal::InternalUserLemon &operator<<(game::battlemon::items::internal::InternalUserLemon &grpcInternalUserLemon, const FUInternalUserLemon &UE);

