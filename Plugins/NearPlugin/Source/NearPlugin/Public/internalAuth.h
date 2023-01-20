#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/internalAuth.grpc.pb.h>

#include "GrpcEnd.h"



#include "internalAuth.generated.h"



UENUM(BlueprintType)
enum class FUInternalVerifyJwtStatus : uint8
{	
	Default UMETA(DisplayName = "Default"),
	OK UMETA(DisplayName = "OK"),
	EXPIRED UMETA(DisplayName = "EXPIRED"),
	INVALID UMETA(DisplayName = "INVALID")
};

UENUM(BlueprintType)
enum class FUInteranalAccountType : uint8
{	
	Default UMETA(DisplayName = "Default"),
	GUEST UMETA(DisplayName = "GUEST"),
	SUI UMETA(DisplayName = "SUI")
};



USTRUCT(BlueprintType)
struct FUInternalAccountInfo 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	FUInteranalAccountType type;

	FUInternalAccountInfo& operator=(const game::battlemon::auth::internal::InternalAccountInfo& grpcInternalAccountInfo);

};


USTRUCT(BlueprintType)
struct FUInternalAccountsInfoResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	TArray<FUInternalAccountInfo> accounts;

	FUInternalAccountsInfoResponse& operator=(const game::battlemon::auth::internal::InternalAccountsInfoResponse& grpcInternalAccountsInfoResponse);

};


USTRUCT(BlueprintType)
struct FUInternalAccountsInfoRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	TArray<FString> user_ids;

	FUInternalAccountsInfoRequest& operator=(const game::battlemon::auth::internal::InternalAccountsInfoRequest& grpcInternalAccountsInfoRequest);

};


USTRUCT(BlueprintType)
struct FUInternalVerifyJwtResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	FUInternalVerifyJwtStatus status;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	FUInternalAccountInfo account;

	FUInternalVerifyJwtResponse& operator=(const game::battlemon::auth::internal::InternalVerifyJwtResponse& grpcInternalVerifyJwtResponse);

};


USTRUCT(BlueprintType)
struct FUInternalVerifyJwtRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | internalAuthProto")
	FString jwt;

	FUInternalVerifyJwtRequest& operator=(const game::battlemon::auth::internal::InternalVerifyJwtRequest& grpcInternalVerifyJwtRequest);

};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInternalGetAccountsInfoDelegate, const FUInternalAccountsInfoResponse&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInternalVerifyJwtDelegate, const FUInternalVerifyJwtResponse&, Response);



class RPC_InternalAuthService : public gRPC_Stub<game::battlemon::auth::internal::InternalAuthService, game::battlemon::auth::internal::InternalAuthService::Stub>
{
	void* Delegate;
	void* out;
public:
	RPC_InternalAuthService(const bool& ssl, FString& url, void* _Delegate, void* _out);
	~RPC_InternalAuthService();

	game::battlemon::auth::internal::InternalVerifyJwtResponse InternalVerifyJwt(grpc::ClientContext* context, const game::battlemon::auth::internal::InternalVerifyJwtRequest* request);
	game::battlemon::auth::internal::InternalAccountsInfoResponse InternalGetAccountsInfo(grpc::ClientContext* context, const game::battlemon::auth::internal::InternalAccountsInfoRequest* request);
	
};

enum class InternalAuthServiceRPC
{
	InternalVerifyJwt,
	InternalGetAccountsInfo,
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UInternalAuthService : public UObject
{
	GENERATED_BODY()

	void free_RPC_InternalAuthService();
	static RPC_InternalAuthService* _RPC_InternalAuthService;
	InternalAuthServiceRPC rpc;

public:
	UInternalAuthService();
	~UInternalAuthService();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | InternalAuthService", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Crypto| InternalAuthService", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalAuthService")
	FInternalGetAccountsInfoDelegate InternalGetAccountsInfoDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | InternalAuthService")
	FInternalVerifyJwtDelegate InternalVerifyJwtDelegate;

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalAuthService")
	void InternalVerifyJwt(TMap<FString, FString> context, FUInternalVerifyJwtRequest inp, FUInternalVerifyJwtResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalAuthService")
	void InternalGetAccountsInfo(TMap<FString, FString> context, FUInternalAccountsInfoRequest inp, FUInternalAccountsInfoResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | InternalAuthService")
	FString GetError();
};



FUInternalVerifyJwtStatus& operator<<(FUInternalVerifyJwtStatus &UE, const game::battlemon::auth::internal::InternalVerifyJwtStatus& grpc);

FUInteranalAccountType& operator<<(FUInteranalAccountType &UE, const game::battlemon::auth::internal::InteranalAccountType& grpc);

game::battlemon::auth::internal::InternalVerifyJwtStatus& operator<<(game::battlemon::auth::internal::InternalVerifyJwtStatus & grpc, const FUInternalVerifyJwtStatus &UE); 

game::battlemon::auth::internal::InteranalAccountType& operator<<(game::battlemon::auth::internal::InteranalAccountType & grpc, const FUInteranalAccountType &UE); 

game::battlemon::auth::internal::InternalAccountInfo &operator<<(game::battlemon::auth::internal::InternalAccountInfo &grpcInternalAccountInfo, const FUInternalAccountInfo &UE);

game::battlemon::auth::internal::InternalAccountsInfoResponse &operator<<(game::battlemon::auth::internal::InternalAccountsInfoResponse &grpcInternalAccountsInfoResponse, const FUInternalAccountsInfoResponse &UE);

game::battlemon::auth::internal::InternalAccountsInfoRequest &operator<<(game::battlemon::auth::internal::InternalAccountsInfoRequest &grpcInternalAccountsInfoRequest, const FUInternalAccountsInfoRequest &UE);

game::battlemon::auth::internal::InternalVerifyJwtResponse &operator<<(game::battlemon::auth::internal::InternalVerifyJwtResponse &grpcInternalVerifyJwtResponse, const FUInternalVerifyJwtResponse &UE);

game::battlemon::auth::internal::InternalVerifyJwtRequest &operator<<(game::battlemon::auth::internal::InternalVerifyJwtRequest &grpcInternalVerifyJwtRequest, const FUInternalVerifyJwtRequest &UE);

