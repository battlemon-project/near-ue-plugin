// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Http.h"
#include <include/Client.h>
#include <include/gRPCResponse.h>
#include "NearAuth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResultNearAuth_Delegate, bool, Result);

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

namespace MainClient
{
	Client* client = nullptr;
}

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
	//FTimerHandle TimerHandle;
	void TimerAuthRegist();

public:


	UNearAuth();
	~UNearAuth();


	UFUNCTION(BlueprintCallable, Category = ".Near | Client")
	FString getAccountID();

	//UPROPERTY(BlueprintAssignable, Category = ".Near | Registration")
	//FResultNearAuth_Delegate ResultNearRegist_Delegate;

	UFUNCTION(BlueprintCallable, Category = ".Near | Registration")
	void RegistrationAccount(bool MainNet = false);



	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool AuthorizedAccount(FString AccountID);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool ClientIsValid();



	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	void PostResponseReceived();														//не работает
};



///items.proto

UENUM(BlueprintType)
enum class FUOutfitKind : uint8
{
	Cap UMETA(DisplayName = "CAP"),
	Cloth UMETA(DisplayName = "CLOTH"),
	Fire_ARM UMETA(DisplayName = "FIRE_ARM"),
	Cold_ARM UMETA(DisplayName = "COLD_ARM"),
	Back UMETA(DisplayName = "BACK"),
	Default UMETA(DisplayName = "DEFAULT")
};


UENUM(BlueprintType)
enum class FUWeaponBundleItemType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	BUNDLE_ITEM_PRIMARY UMETA(DisplayName = "BUNDLE_ITEM_PRIMARY"),
	BUNDLE_ITEM_SECONDARY UMETA(DisplayName = "BUNDLE_ITEM_SECONDARY"),
	BUNDLE_ITEM_MELEE UMETA(DisplayName = "BUNDLE_ITEM_MELEE"),
	BUNDLE_ITEM_TACTICAL UMETA(DisplayName = "BUNDLE_ITEM_TACTICAL"),
	BUNDLE_ITEM_MILITARY UMETA(DisplayName = "BUNDLE_ITEM_MILITARY"),
	BUNDLE_ITEM_PERK UMETA(DisplayName = "BUNDLE_ITEM_PERK"),
	Default UMETA(DisplayName = "DEFAULT")
};

UENUM(BlueprintType)
enum class FUWeaponBundleSlotType : uint8
{
	NONE UMETA(DisplayName = "NONE"),
	BUNDLE_SLOT_PRIMARY UMETA(DisplayName = "BUNDLE_SLOT_PRIMARY"),
	BUNDLE_SLOT_SECONDARY UMETA(DisplayName = "BUNDLE_SLOT_SECONDARY"),
	BUNDLE_SLOT_MELEE UMETA(DisplayName = "BUNDLE_SLOT_MELEE"),
	BUNDLE_SLOT_TACTICAL_ONE UMETA(DisplayName = "BUNDLE_SLOT_TACTICAL_ONE"),
	BUNDLE_SLOT_TACTICAL_TWO UMETA(DisplayName = "BUNDLE_SLOT_TACTICAL_TWO"),
	BUNDLE_SLOT_MILITARY_ONE UMETA(DisplayName = "BUNDLE_SLOT_MILITARY_ONE"),
	BUNDLE_SLOT_MILITARY_TWO UMETA(DisplayName = "BUNDLE_SLOT_MILITARY_TWO"),
	BUNDLE_SLOT_PERK_ONE UMETA(DisplayName = "BUNDLE_SLOT_PERK_ONE"),
	BUNDLE_SLOT_PERK_TWO UMETA(DisplayName = "BUNDLE_SLOT_PERK_TWO"),
	Default UMETA(DisplayName = "DEFAULT")
};

USTRUCT(BlueprintType)
struct FUWeaponBundleItem
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUWeaponBundleItemType item_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUWeaponBundleSlotType slot_type;
};

USTRUCT(BlueprintType)
struct FUWeaponBundle
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	TArray<FUWeaponBundleItem> items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	int32 level;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	TArray<FUWeaponBundle> attached_bundles;
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
	bool in_fight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FULemonModel lemon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FUOutfitModel outfit;
};

USTRUCT(BlueprintType)
struct FUItemsResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	TArray<FUItem> items;
};

USTRUCT(BlueprintType)
struct FUGetBundlesResponse
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	TArray<FUWeaponBundle> bundles;
};

USTRUCT(BlueprintType)
struct FUEditBundleRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	TArray<FUWeaponBundleItem> items;// changes only
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString title;
};

USTRUCT(BlueprintType)
struct FUAttachBundleRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString lemon_id;
};

USTRUCT(BlueprintType)
struct FUDetachBundleRequest
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
	FString lemon_id;
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearItems : public UObject
{
	GENERATED_BODY()
	gRPC_ResponseItem* gRPC_Item;
	TArray<FUItem> ItemsPtr;
	void freegRPC_Item();
	void Call_gRPC(void* messeng, Type_Call_gRPC::Type_gRPCItem Type_gRPC);

public:
	UNearItems();
	~UNearItems();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	TArray<FUWeaponBundle> GetBundlesArray();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	FUWeaponBundle GetBundle(int index);

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	TArray<FUWeaponBundle> GetCopyBundlesArray();
	
	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	FUWeaponBundle GetEditBundle(FUEditBundleRequest request);

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool GetAttachBundle();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool GetDetachBundle();



	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	TArray<FUItem> GetItemsArry();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	TArray<FUItem> GetCopyDataItems();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	FUItem GetItem(int index);
};


///	MM.proto

UENUM(BlueprintType)
enum class FUMatchType : uint8
{
	DEATH_MATCH  UMETA(DisplayName = "DEATH_MATCH "),
	CATCH_THE_FLAG UMETA(DisplayName = "CATCH_THE_FLAG"),
	Default UMETA(DisplayName = "DEFAULT")
};

UENUM(BlueprintType)
enum class FUMatchMode : uint8
{
	NONE  UMETA(DisplayName = "NONE "),
	EQUIPMENT UMETA(DisplayName = "EQUIPMENT"),
	REALISM UMETA(DisplayName = "REALISM"),
	Default UMETA(DisplayName = "DEFAULT")
};


UENUM(BlueprintType)
enum class FUSearchGameResponseStatus : uint8
{
	OK UMETA(DisplayName = "OK"),
	NFT_ERROR UMETA(DisplayName = "NFT_ERROR"),
	ALREADY_IN_QUEUE UMETA(DisplayName = "ALREADY_IN_QUEUE"),
	ALREADY_IN_BATTLE UMETA(DisplayName = "ALREADY_IN_BATTLE"),
	GAMEMODE_ERROR UMETA(DisplayName = "GAMEMODE_ERROR"),
	INVALID_REQUEST UMETA(DisplayName = "INVALID_REQUEST"),
	INTERNAL_ERROR UMETA(DisplayName = "INTERNAL_ERROR"),
	Default UMETA(DisplayName = "DEFAULT")
};


USTRUCT(BlueprintType)
struct FUGameMode
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
	FUMatchType match_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
	FUMatchMode match_mode;
};


USTRUCT(BlueprintType)
struct FUSearchGameRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto | Request")
	FUGameMode game_mode;
};

USTRUCT(BlueprintType)
struct FUSearchGameResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto | Response")
	FUSearchGameResponseStatus status;
};

USTRUCT(BlueprintType)
struct FUAcceptGameRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto | Request")
	FString lemon_id;
};




UCLASS(Blueprintable)
class NEARPLUGIN_API UNearMM : public	UObject
{
	GENERATED_BODY()
	gRPC_ResponseMM* gRPC_MM;

	void freegRPC_MM();

public:
	UNearMM();
	~UNearMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	FUSearchGameResponse SearchGame(FUSearchGameRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool AcceptGame(FUAcceptGameRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool CancelSearch();
};
