#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/mm.grpc.pb.h>
#include <protocol/common.grpc.pb.h>

#include "GrpcEnd.h"

#include "common.h"


#include "mm.generated.h"



UENUM(BlueprintType)
enum class FUMatchType : uint8
{	
	Default UMETA(DisplayName = "Default"),
	DEATH_MATCH UMETA(DisplayName = "DEATH_MATCH"),
	CATCH_THE_FLAG UMETA(DisplayName = "CATCH_THE_FLAG")
};

UENUM(BlueprintType)
enum class FUMatchMode : uint8
{	
	Default UMETA(DisplayName = "Default"),
	NONE UMETA(DisplayName = "NONE"),
	EQUIPMENT UMETA(DisplayName = "EQUIPMENT"),
	REALISM UMETA(DisplayName = "REALISM")
};

UENUM(BlueprintType)
enum class FURegion : uint8
{	
	Default UMETA(DisplayName = "Default"),
	US UMETA(DisplayName = "US"),
	EU UMETA(DisplayName = "EU")
};

UENUM(BlueprintType)
enum class FUSearchGameResponseStatus : uint8
{	
	Default UMETA(DisplayName = "Default"),
	OK UMETA(DisplayName = "OK"),
	NFT_ERROR UMETA(DisplayName = "NFT_ERROR"),
	ALREADY_IN_QUEUE UMETA(DisplayName = "ALREADY_IN_QUEUE"),
	ALREADY_IN_BATTLE UMETA(DisplayName = "ALREADY_IN_BATTLE"),
	GAMEMODE_ERROR UMETA(DisplayName = "GAMEMODE_ERROR"),
	INVALID_REQUEST UMETA(DisplayName = "INVALID_REQUEST"),
	INTERNAL_ERROR UMETA(DisplayName = "INTERNAL_ERROR")
};



USTRUCT(BlueprintType)
struct FUCancelSearchRequest 
{
	GENERATED_BODY()
	

	FUCancelSearchRequest& operator=(const game::battlemon::mm::CancelSearchRequest& grpcCancelSearchRequest);

};


USTRUCT(BlueprintType)
struct FUAcceptGameRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | mmProto")
	FString lemon_id;

	FUAcceptGameRequest& operator=(const game::battlemon::mm::AcceptGameRequest& grpcAcceptGameRequest);

};


USTRUCT(BlueprintType)
struct FUSearchGameResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | mmProto")
	FUSearchGameResponseStatus status;

	FUSearchGameResponse& operator=(const game::battlemon::mm::SearchGameResponse& grpcSearchGameResponse);

};


USTRUCT(BlueprintType)
struct FUGameMode 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | mmProto")
	FUMatchType match_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | mmProto")
	FUMatchMode match_mode;

	FUGameMode& operator=(const game::battlemon::mm::GameMode& grpcGameMode);

};


USTRUCT(BlueprintType)
struct FUSearchGameRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | mmProto")
	FUGameMode game_mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | mmProto")
	FURegion region;

	FUSearchGameRequest& operator=(const game::battlemon::mm::SearchGameRequest& grpcSearchGameRequest);

};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAcceptGameDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCancelSearchDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSearchGameDelegate, const FUSearchGameResponse&, Response);



class RPC_MMService : public gRPC_Stub<game::battlemon::mm::MMService, game::battlemon::mm::MMService::Stub>
{
	void* Delegate;
	void* out;
public:
	RPC_MMService(const bool& ssl, FString& url, void* _Delegate, void* _out);
	~RPC_MMService();

	game::battlemon::mm::SearchGameResponse SearchGame(grpc::ClientContext* context, const game::battlemon::mm::SearchGameRequest* request);
	game::battlemon::common::Empty AcceptGame(grpc::ClientContext* context, const game::battlemon::mm::AcceptGameRequest* request);
	game::battlemon::common::Empty CancelSearch(grpc::ClientContext* context, const game::battlemon::mm::CancelSearchRequest* request);
	
};

enum class MMServiceRPC
{
	SearchGame,
	AcceptGame,
	CancelSearch,
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UMMService : public UObject
{
	GENERATED_BODY()

	void free_RPC_MMService();
	static RPC_MMService* _RPC_MMService;
	MMServiceRPC rpc;

public:
	UMMService();
	~UMMService();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | MMService", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Crypto| MMService", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UPROPERTY(BlueprintAssignable, Category = ".Crypto | MMService")
	FAcceptGameDelegate AcceptGameDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | MMService")
	FCancelSearchDelegate CancelSearchDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | MMService")
	FSearchGameDelegate SearchGameDelegate;

	UFUNCTION(BlueprintCallable, Category = ".Crypto | MMService")
	void SearchGame(TMap<FString, FString> context, FUSearchGameRequest inp, FUSearchGameResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | MMService")
	void AcceptGame(TMap<FString, FString> context, FUAcceptGameRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | MMService")
	void CancelSearch(TMap<FString, FString> context, FUCancelSearchRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | MMService")
	FString GetError();
};



FUMatchType& operator<<(FUMatchType &UE, const game::battlemon::mm::MatchType& grpc);

FUMatchMode& operator<<(FUMatchMode &UE, const game::battlemon::mm::MatchMode& grpc);

FURegion& operator<<(FURegion &UE, const game::battlemon::mm::Region& grpc);

FUSearchGameResponseStatus& operator<<(FUSearchGameResponseStatus &UE, const game::battlemon::mm::SearchGameResponseStatus& grpc);

game::battlemon::mm::MatchType& operator<<(game::battlemon::mm::MatchType & grpc, const FUMatchType &UE); 

game::battlemon::mm::MatchMode& operator<<(game::battlemon::mm::MatchMode & grpc, const FUMatchMode &UE); 

game::battlemon::mm::Region& operator<<(game::battlemon::mm::Region & grpc, const FURegion &UE); 

game::battlemon::mm::SearchGameResponseStatus& operator<<(game::battlemon::mm::SearchGameResponseStatus & grpc, const FUSearchGameResponseStatus &UE); 

game::battlemon::mm::CancelSearchRequest &operator<<(game::battlemon::mm::CancelSearchRequest &grpcCancelSearchRequest, const FUCancelSearchRequest &UE);

game::battlemon::mm::AcceptGameRequest &operator<<(game::battlemon::mm::AcceptGameRequest &grpcAcceptGameRequest, const FUAcceptGameRequest &UE);

game::battlemon::mm::SearchGameResponse &operator<<(game::battlemon::mm::SearchGameResponse &grpcSearchGameResponse, const FUSearchGameResponse &UE);

game::battlemon::mm::GameMode &operator<<(game::battlemon::mm::GameMode &grpcGameMode, const FUGameMode &UE);

game::battlemon::mm::SearchGameRequest &operator<<(game::battlemon::mm::SearchGameRequest &grpcSearchGameRequest, const FUSearchGameRequest &UE);

