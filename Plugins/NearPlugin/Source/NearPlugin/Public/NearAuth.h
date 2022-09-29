// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Http.h"
#include <include/Client.h>
#include "NearAuth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResultNearReg_Delegate);

#if PLATFORM_WINDOWS
#define WEBTYPE_M "mainnet"
#define WEBTYPE_T "testnet"
#define RPC_RUST "testnet"
#define GET_CHARPTR(inp) TCHAR_TO_ANSI(*inp)
#else
#define WEBTYPE_M u"mainnet"
#define WEBTYPE_T u"testnet"
#define RPC_RUST "https://rpc.testnet.near.org"
#define GET_CHARPTR(inp) *inp
#endif
/**
 * 
 */

UENUM(BlueprintType)
enum class FUOutfitKind : uint8
{
	Cap UMETA( DisplayName = "CAP"),
	Cloth UMETA(DisplayName = "CLOTH"),
	Fire_ARM UMETA( DisplayName = "FIRE_ARM"),
	Cold_ARM UMETA( DisplayName = "COLD_ARM"),
	Back UMETA( DisplayName = "BACK"),
	Default UMETA( DisplayName = "DEFAULT")
};

USTRUCT(BlueprintType)
struct FUOutfitModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString flavour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitKind kind;
};

USTRUCT(BlueprintType)
struct FULemonModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel cap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel cloth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString exo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString eyes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString head;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString teeth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString face;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel fire_arm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel cold_arm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel back;
};


USTRUCT(BlueprintType)
struct FUItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString media;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString owner_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FULemonModel lemon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel outfit;
};

USTRUCT(BlueprintType)
struct FUPlayerItemsClient
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString near_id;				//	PlayerItems
	//UPROPERTY(BlueprintReadWrite)
	//TMap<FString, TArray<FString>> nft_ids; //	PlayerItems = <near_id, repeated string nft_ids> 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	TArray<FString> nft_idsArr;
};


UCLASS(Blueprintable)
class NEARPLUGIN_API UNearAuth : public	UObject
{
	GENERATED_BODY()


	static void freeClient();
	void saveAccountId();


	void OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnPOSTRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnResponseReceived();
	bool CheckAccountKey(FString AccountName);
	FTimerHandle TimerHandle;
	void TimerAuthRegist();

public:

	static Client* client;

	UNearAuth();
	~UNearAuth();


	UFUNCTION(BlueprintCallable, Category = ".Near | Client")
	FString getAccountID();

	UPROPERTY(BlueprintAssignable, Category = ".Near | Registration")
	FResultNearReg_Delegate ResultNearRegist_Delegate;


	UFUNCTION(BlueprintCallable, Category = ".Near | Registration")
	void RegistrationAccount(bool MainNet = false);

	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool AuthorizedAccount(FString AccountID);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool ClientIsValid();

	UFUNCTION(BlueprintCallable, Category = ".Near | ItemsProto")
	TArray<FUPlayerItemsClient> getPlayerItems(FString room_id, TArray<FString> near_ids);

	UFUNCTION(BlueprintCallable, Category = ".Near | ItemsProto")
	void setMyItems(FString room_id, TArray<FString> nft_ids);

	UFUNCTION(BlueprintCallable, Category = ".Near | ItemsProto")
	TArray<FUItem> getItems();
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	void PostResponseReceived();														//не работает
};
