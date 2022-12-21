#pragma once
#include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/auth.grpc.pb.h>

#include "GrpcEnd.h"



#include "auth.generated.h"





USTRUCT(BlueprintType)
struct FUSendCodeRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | authProto")
	FString public_key;

	FUSendCodeRequest& operator=(const game::battlemon::auth::SendCodeRequest& grpcSendCodeRequest);

};


USTRUCT(BlueprintType)
struct FUSendCodeResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | authProto")
	FString code;

	FUSendCodeResponse& operator=(const game::battlemon::auth::SendCodeResponse& grpcSendCodeResponse);

};


USTRUCT(BlueprintType)
struct FUVerifyCodeRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | authProto")
	FString public_key;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | authProto")
	FString sign;

	FUVerifyCodeRequest& operator=(const game::battlemon::auth::VerifyCodeRequest& grpcVerifyCodeRequest);

};


USTRUCT(BlueprintType)
struct FUVerifyCodeResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | authProto")
	FString near_account_id;

	FUVerifyCodeResponse& operator=(const game::battlemon::auth::VerifyCodeResponse& grpcVerifyCodeResponse);

};


game::battlemon::auth::SendCodeRequest &operator<<(game::battlemon::auth::SendCodeRequest &grpcSendCodeRequest, const FUSendCodeRequest &UE);

game::battlemon::auth::SendCodeResponse &operator<<(game::battlemon::auth::SendCodeResponse &grpcSendCodeResponse, const FUSendCodeResponse &UE);

game::battlemon::auth::VerifyCodeRequest &operator<<(game::battlemon::auth::VerifyCodeRequest &grpcVerifyCodeRequest, const FUVerifyCodeRequest &UE);

game::battlemon::auth::VerifyCodeResponse &operator<<(game::battlemon::auth::VerifyCodeResponse &grpcVerifyCodeResponse, const FUVerifyCodeResponse &UE);

