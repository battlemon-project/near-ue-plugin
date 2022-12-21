#pragma once
#include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalAuth.grpc.pb.h>

#include "GrpcEnd.h"



#include "internalAuth.generated.h"



UENUM(BlueprintType)
enum class FUInternalVerifySignStatus : uint8
{	
	Default UMETA(DisplayName = "Default"),
	OK UMETA(DisplayName = "OK"),
	EXPIRED UMETA(DisplayName = "EXPIRED"),
	INVALID_SIGN UMETA(DisplayName = "INVALID_SIGN"),
	PK_NOT_FOUND UMETA(DisplayName = "PK_NOT_FOUND"),
	PK_NOT_VERIFIED UMETA(DisplayName = "PK_NOT_VERIFIED")
};



USTRUCT(BlueprintType)
struct FUInternalVerifySignRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalAuthProto")
	FString near_account_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalAuthProto")
	FString sign;

	FUInternalVerifySignRequest& operator=(const game::battlemon::auth::internal::InternalVerifySignRequest& grpcInternalVerifySignRequest);

};


USTRUCT(BlueprintType)
struct FUInternalVerifySignResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | internalAuthProto")
	FUInternalVerifySignStatus status;

	FUInternalVerifySignResponse& operator=(const game::battlemon::auth::internal::InternalVerifySignResponse& grpcInternalVerifySignResponse);

};


FUInternalVerifySignStatus& operator<<(FUInternalVerifySignStatus &UE, const game::battlemon::auth::internal::InternalVerifySignStatus& grpc);

game::battlemon::auth::internal::InternalVerifySignStatus& operator<<(game::battlemon::auth::internal::InternalVerifySignStatus & grpc, const FUInternalVerifySignStatus &UE); 

game::battlemon::auth::internal::InternalVerifySignRequest &operator<<(game::battlemon::auth::internal::InternalVerifySignRequest &grpcInternalVerifySignRequest, const FUInternalVerifySignRequest &UE);

game::battlemon::auth::internal::InternalVerifySignResponse &operator<<(game::battlemon::auth::internal::InternalVerifySignResponse &grpcInternalVerifySignResponse, const FUInternalVerifySignResponse &UE);

