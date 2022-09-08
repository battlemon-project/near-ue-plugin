// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <include/Client.h>
#include "NearAuth.generated.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString flavour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitKind kind;
};

USTRUCT(BlueprintType)
struct FULemonModel
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitModel cap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitModel cloth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString exo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString eyes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString head;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString teeth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString face;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitModel fire_arm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitModel cold_arm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitModel back;
};


USTRUCT(BlueprintType)
struct FUItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString media;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString owner_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FULemonModel lemon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUOutfitModel outfit;
};

USTRUCT(BlueprintType)
struct FUPlayerItemsClient
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString near_id;				//	PlayerItems
	//UPROPERTY(BlueprintReadWrite)
	//TMap<FString, TArray<FString>> nft_ids; //	PlayerItems = <near_id, repeated string nft_ids> 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> nft_idsArr;
};

UCLASS()
class NEARPLUGIN_API UNearAuth : public UObject
{
	GENERATED_BODY()

	static void freeClient();
	static void saveAccountId();

public:
	static Client* client;

	UNearAuth();
	~UNearAuth();


	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static bool RegistrationAccount(FString& AccountId, bool MainNet = false);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static bool AuthorizedAccount(FString AccountId);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static bool ClientIsValid();

	UFUNCTION(BlueprintCallable, Category = ".Near | ItemsProto")
	static TArray<FUPlayerItemsClient> getPlayerItems(FString room_id, TArray<FString> near_ids);

	UFUNCTION(BlueprintCallable, Category = ".Near | ItemsProto")
	static void setMyItems(FString room_id, TArray<FString> nft_ids);

	UFUNCTION(BlueprintCallable, Category = ".Near | ItemsProto")
	static TArray<FUItem> getItems();
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	static FString CheckDLL();
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	static FString GetError();
};
