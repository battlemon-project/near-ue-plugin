#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/common.grpc.pb.h>

#include "GrpcEnd.h"



#include "common.generated.h"



UENUM(BlueprintType)
enum class FUSortOrder : uint8
{	
	Default UMETA(DisplayName = "Default"),
	ASC UMETA(DisplayName = "ASC"),
	DESC UMETA(DisplayName = "DESC")
};

UENUM(BlueprintType)
enum class FUStatus : uint8
{	
	Default UMETA(DisplayName = "Default"),
	OK UMETA(DisplayName = "OK"),
	SYSTEM_ERROR UMETA(DisplayName = "SYSTEM_ERROR")
};

UENUM(BlueprintType)
enum class FUServiceStatus : uint8
{	
	Default UMETA(DisplayName = "Default"),
	SUCCESS UMETA(DisplayName = "SUCCESS"),
	INTERNAL_ERROR UMETA(DisplayName = "INTERNAL_ERROR"),
	BAD_REQUEST UMETA(DisplayName = "BAD_REQUEST")
};

UENUM(BlueprintType)
enum class FURarity : uint8
{	
	Default UMETA(DisplayName = "Default"),
	COMMON UMETA(DisplayName = "COMMON"),
	RARE UMETA(DisplayName = "RARE"),
	EPIC UMETA(DisplayName = "EPIC"),
	LEGENDARY UMETA(DisplayName = "LEGENDARY")
};

UENUM(BlueprintType)
enum class FUFaction : uint8
{	
	Default UMETA(DisplayName = "Default"),
	FIRST UMETA(DisplayName = "FIRST")
};



USTRUCT(BlueprintType)
struct FUResultStatus 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | commonProto")
	FUStatus status;

	FUResultStatus& operator=(const game::battlemon::common::ResultStatus& grpcResultStatus);

};


USTRUCT(BlueprintType)
struct FUResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | commonProto")
	FUServiceStatus status;

	FUResponse& operator=(const game::battlemon::common::Response& grpcResponse);

};


USTRUCT(BlueprintType)
struct FUEmpty 
{
	GENERATED_BODY()
	

	FUEmpty& operator=(const game::battlemon::common::Empty& grpcEmpty);

};


FUSortOrder& operator<<(FUSortOrder &UE, const game::battlemon::common::SortOrder& grpc);

FUStatus& operator<<(FUStatus &UE, const game::battlemon::common::Status& grpc);

FUServiceStatus& operator<<(FUServiceStatus &UE, const game::battlemon::common::ServiceStatus& grpc);

FURarity& operator<<(FURarity &UE, const game::battlemon::common::Rarity& grpc);

FUFaction& operator<<(FUFaction &UE, const game::battlemon::common::Faction& grpc);

game::battlemon::common::SortOrder& operator<<(game::battlemon::common::SortOrder & grpc, const FUSortOrder &UE); 

game::battlemon::common::Status& operator<<(game::battlemon::common::Status & grpc, const FUStatus &UE); 

game::battlemon::common::ServiceStatus& operator<<(game::battlemon::common::ServiceStatus & grpc, const FUServiceStatus &UE); 

game::battlemon::common::Rarity& operator<<(game::battlemon::common::Rarity & grpc, const FURarity &UE); 

game::battlemon::common::Faction& operator<<(game::battlemon::common::Faction & grpc, const FUFaction &UE); 

game::battlemon::common::ResultStatus &operator<<(game::battlemon::common::ResultStatus &grpcResultStatus, const FUResultStatus &UE);

game::battlemon::common::Response &operator<<(game::battlemon::common::Response &grpcResponse, const FUResponse &UE);

game::battlemon::common::Empty &operator<<(game::battlemon::common::Empty &grpcEmpty, const FUEmpty &UE);

