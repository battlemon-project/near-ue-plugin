// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Engine/World.h"
#include "Http.h"
#include "Engine/EngineTypes.h"
#include <include/Client.h>
#include <include/gRPCResponse.h>
#include "NearAuth.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResultNearAuth_Delegate, const FString&, Result);

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

class MainClient
{
public:
	static Client* client;
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearAuth : public	UObject
{
	GENERATED_BODY()

	virtual UWorld* GetWorld() const override;

	static void freeClient();
	void saveAccountId();


	void OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	//void OnPOSTRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnResponseReceived();
	bool CheckAccountKey(FString AccountName);
	FTimerHandle NearAuthTimer;
	void TimerAuthRegist();

	

public:

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UNearAuth();
	~UNearAuth();

	UFUNCTION(BlueprintCallable, Category = ".Near | Client")
	FString getAccountID();

	UPROPERTY(BlueprintAssignable, Category = ".Near | Registration")
	FResultNearAuth_Delegate ResultNearRegist_Delegate;

	UFUNCTION(BlueprintCallable, Category = ".Near | Registration")
	void RegistrationAccount(bool MainNet = false);



	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void AuthorizedAccount(FString AccountID);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool ClientIsValid();

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();

	//UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	//void PostResponseReceived();														//�� ��������
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

	FUWeaponBundleItem& operator=(const ModelItems::WeaponBundleItem& weaponBundleItem);
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

	FUWeaponBundle& operator=(const ModelItems::WeaponBundle& weaponBundle);
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

	FUOutfitModel& operator=(const ModelItems::OutfitModel& outfitModel);
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

	FULemonModel& operator=(const ModelItems::LemonModel& LemonM);
};

enum class FUModel : uint8
{
	LEMON UMETA(DisplayName = "LEMON"),
	OUTFIT_MODEL UMETA(DisplayName = "OUTFIT_MODEL"),
	DEFAULT UMETA(DisplayName = "DEFAULT")
};


USTRUCT(BlueprintType)
struct FUItem
{
	GENERATED_BODY()
	FUModel model;
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

	FUItem& operator=(const ModelItems::Item& item);
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

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

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
	bool GetAttachBundle(FUAttachBundleRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	bool GetDetachBundle(FUDetachBundleRequest Request);



	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	TArray<FUItem> GetItemsArry();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	TArray<FUItem> GetCopyDataItems();

	UFUNCTION(BlueprintCallable, Category = ".NearItems | ItemsProto")
	FUItem GetItem(int index);

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
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

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UNearMM();
	~UNearMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	FUSearchGameResponse SearchGame(FUSearchGameRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool AcceptGame(FUAcceptGameRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | MMProto")
	bool CancelSearch();

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};


///InternalMM.proto

USTRUCT(BlueprintType)
struct FUInternalUserLeftBattleRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString room_id;
};

USTRUCT(BlueprintType)
struct FUInternalPlayerResult
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	int place;
};

USTRUCT(BlueprintType)
struct FUSaveBattleResultRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	TArray<FUInternalPlayerResult> results;
};


USTRUCT(BlueprintType)
struct FURoomInfoRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString room_id;
};

USTRUCT(BlueprintType)
struct FURoomPlayerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString near_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FUItem lemon;
};

USTRUCT(BlueprintType)
struct FURoomInfoResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString room_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	TArray<FURoomPlayerInfo> players;
};


USTRUCT(BlueprintType)
struct FUCreateRoomRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FUGameMode mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	TArray<FString> near_ids;
};

USTRUCT(BlueprintType)
struct FUDedicatedServerIsReadyRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto | Request")
	FString room_id;
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearInternalMM : public	UObject
{
	GENERATED_BODY()
	gRPC_ResponseInternalMM* gRPC_InternalMM;

	void freegRPC_InternalMM();
	bool Call_gRPC(void* messeng, Type_Call_gRPC::Type_gRPC_InternalMM Type_gRPC);

	

public:

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UNearInternalMM();
	~UNearInternalMM();

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	FString GetEnvironmentVariable(FString VarName);

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool UserLeftBattle(FUInternalUserLeftBattleRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool SaveBattleResult(FUSaveBattleResultRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	FURoomInfoResponse GetRoomInfo(FURoomInfoRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	FURoomInfoResponse CreateRoomWithPlayers(FUCreateRoomRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | InternalMMProto")
	bool DedicatedServerIsReady(FUDedicatedServerIsReadyRequest Request);

	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	FString GetError();
};
