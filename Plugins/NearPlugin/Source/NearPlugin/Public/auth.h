#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/auth.grpc.pb.h>

#include "GrpcEnd.h"



#include "auth.generated.h"





USTRUCT(BlueprintType)
struct FUWalletAddressResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | authProto")
	FString wallet_address;

	FUWalletAddressResponse& operator=(const game::battlemon::auth::WalletAddressResponse& grpcWalletAddressResponse);

};


USTRUCT(BlueprintType)
struct FUWalletAddressRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | authProto")
	FString client_id;

	FUWalletAddressRequest& operator=(const game::battlemon::auth::WalletAddressRequest& grpcWalletAddressRequest);

};


USTRUCT(BlueprintType)
struct FUSession 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | authProto")
	FString jwt;

	FUSession& operator=(const game::battlemon::auth::Session& grpcSession);

};


USTRUCT(BlueprintType)
struct FUSuiSession 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | authProto")
	FUSession session;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | authProto")
	FString wallet_address;

	FUSuiSession& operator=(const game::battlemon::auth::SuiSession& grpcSuiSession);

};


USTRUCT(BlueprintType)
struct FUGuestAuthRequest 
{
	GENERATED_BODY()
	

	FUGuestAuthRequest& operator=(const game::battlemon::auth::GuestAuthRequest& grpcGuestAuthRequest);

};


USTRUCT(BlueprintType)
struct FUSuiAuthRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | authProto")
	FString client_id;

	FUSuiAuthRequest& operator=(const game::battlemon::auth::SuiAuthRequest& grpcSuiAuthRequest);

};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetWalletAddressDelegate, const FUWalletAddressResponse&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGuestAuthDelegate, const FUSession&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSuiAuthDelegate, const FUSuiSession&, Response);



class RPC_AuthService : public gRPC_Stub<game::battlemon::auth::AuthService, game::battlemon::auth::AuthService::Stub>
{
	void* Delegate;
	void* out;
public:
	RPC_AuthService(const bool& ssl, FString& url, void* _Delegate, void* _out);
	~RPC_AuthService();

	game::battlemon::auth::SuiSession SuiAuth(grpc::ClientContext* context, const game::battlemon::auth::SuiAuthRequest* request);
	game::battlemon::auth::Session GuestAuth(grpc::ClientContext* context, const game::battlemon::auth::GuestAuthRequest* request);
	game::battlemon::auth::WalletAddressResponse GetWalletAddress(grpc::ClientContext* context, const game::battlemon::auth::WalletAddressRequest* request);
	
};

enum class AuthServiceRPC
{
	SuiAuth,
	GuestAuth,
	GetWalletAddress,
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UAuthService : public UObject
{
	GENERATED_BODY()

	void free_RPC_AuthService();
	static RPC_AuthService* _RPC_AuthService;
	AuthServiceRPC rpc;

public:
	UAuthService();
	~UAuthService();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | AuthService", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Crypto| AuthService", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UPROPERTY(BlueprintAssignable, Category = ".Crypto | AuthService")
	FGetWalletAddressDelegate GetWalletAddressDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | AuthService")
	FGuestAuthDelegate GuestAuthDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | AuthService")
	FSuiAuthDelegate SuiAuthDelegate;

	UFUNCTION(BlueprintCallable, Category = ".Crypto | AuthService")
	void SuiAuth(TMap<FString, FString> context, FUSuiAuthRequest inp, FUSuiSession &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | AuthService")
	void GuestAuth(TMap<FString, FString> context, FUGuestAuthRequest inp, FUSession &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | AuthService")
	void GetWalletAddress(TMap<FString, FString> context, FUWalletAddressRequest inp, FUWalletAddressResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | AuthService")
	FString GetError();
};



game::battlemon::auth::WalletAddressResponse &operator<<(game::battlemon::auth::WalletAddressResponse &grpcWalletAddressResponse, const FUWalletAddressResponse &UE);

game::battlemon::auth::WalletAddressRequest &operator<<(game::battlemon::auth::WalletAddressRequest &grpcWalletAddressRequest, const FUWalletAddressRequest &UE);

game::battlemon::auth::Session &operator<<(game::battlemon::auth::Session &grpcSession, const FUSession &UE);

game::battlemon::auth::SuiSession &operator<<(game::battlemon::auth::SuiSession &grpcSuiSession, const FUSuiSession &UE);

game::battlemon::auth::GuestAuthRequest &operator<<(game::battlemon::auth::GuestAuthRequest &grpcGuestAuthRequest, const FUGuestAuthRequest &UE);

game::battlemon::auth::SuiAuthRequest &operator<<(game::battlemon::auth::SuiAuthRequest &grpcSuiAuthRequest, const FUSuiAuthRequest &UE);

