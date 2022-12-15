// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "gRPC_Base.h"
#include "GrpcBegin.h"

#include <protocol/common.grpc.pb.h>
#include <protocol/items.grpc.pb.h>
#include <protocol/internalMm.grpc.pb.h>
#include <protocol/mm.grpc.pb.h>
#include <protocol/updates.grpc.pb.h>


#include "GrpcEnd.h"

#include "Runtime/Core/Public/Async/ParallelFor.h"


#include "ModelProto.generated.h"

/**
 *      items.proto
 */

UENUM(BlueprintType)
enum class FUModel : uint8
{
    kLemon UMETA(DisplayName = "LEMON"),
    kOutfit UMETA(DisplayName = "OUTFIT_MODEL"),
    MODEL_NOT_SET UMETA(DisplayName = "DEFAULT")
};

UENUM(BlueprintType)
enum class FUOutfitKind : uint8
{
    CAP UMETA(DisplayName = "CAP"),
    CLOTH UMETA(DisplayName = "CLOTH"),
    FIRE_ARM UMETA(DisplayName = "FIRE_ARM"),
    COLD_ARM UMETA(DisplayName = "COLD_ARM"),
    BACK UMETA(DisplayName = "BACK"),
    Default UMETA(DisplayName = "DEFAULT")
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

    FUOutfitModel& operator=(const game::battlemon::items::OutfitModel& outfitModel);
};

UENUM(BlueprintType)
enum class FUWeaponBundleItemType : uint8
{
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

    FUWeaponBundleItem& operator=(const game::battlemon::items::WeaponBundleItem& weaponBundleItem);
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

    FUWeaponBundle& operator=(const game::battlemon::items::WeaponBundle& weaponBundle);
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

    FULemonModel& operator=(const game::battlemon::items::LemonModel& lemonModel);
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
    FUModel model;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    FULemonModel lemon;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    FUOutfitModel outfit;

    FUItem& operator=(const game::battlemon::items::Item& item);
};

USTRUCT(BlueprintType)
struct FUItemsResponse
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    TArray<FUItem> items;

    FUItemsResponse& operator=(const game::battlemon::items::ItemsResponse& itemR);
};


USTRUCT(BlueprintType)
struct FUGetBundlesResponse
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    TArray<FUWeaponBundle> bundles;
    FUGetBundlesResponse& operator=(const game::battlemon::items::GetBundlesResponse& weaponBundleResponse);
};

USTRUCT(BlueprintType)
struct FUEditBundleRequest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    int32 bundle_num;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    TArray<FUWeaponBundleItem> items;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    FString title;

    FUEditBundleRequest& operator=(const game::battlemon::items::EditBundleRequest& editBundleRequest);
};

USTRUCT(BlueprintType)
struct FUAttachBundleRequest 
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    int32 bundle_num;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | ItemsProto")
    FString lemon_id;

    FUAttachBundleRequest& operator=(const game::battlemon::items::AttachBundleRequest& attachBundleRequest);
};

USTRUCT(BlueprintType)
struct FUDetachBundleRequest :public FUAttachBundleRequest
{
    GENERATED_BODY()

    FUDetachBundleRequest& operator=(const game::battlemon::items::DetachBundleRequest& detachBundleRequest);
};

//items. massange end

//mm.massange
UENUM(BlueprintType)
enum class FUMatchType : uint8
{
    DEATH_MATCH UMETA(DisplayName = "DEATH_MATCH"),
    CATCH_THE_FLAG UMETA(DisplayName = "CATCH_THE_FLAG"),
    DEFAULT UMETA(DisplayName = "DEFAULT")
};

UENUM(BlueprintType)
enum class FUMatchMode : uint8
{
    NONE UMETA(DisplayName = "NONE"),
    EQUIPMENT UMETA(DisplayName = "EQUIPMENT"),
    REALISM UMETA(DisplayName = "REALISM"),
    DEFAULT UMETA(DisplayName = "DEFAULT")
};


UENUM(BlueprintType)
enum class FRegion : uint8
{
    DEFAULT UMETA(DisplayName = "DEFAULT"),
    US UMETA(DisplayName = "US"),
    EU UMETA(DisplayName = "EU")
};

USTRUCT(BlueprintType)
struct FUGameMode
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
    FUMatchType match_type;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
    FUMatchMode match_mode;

    FUGameMode& operator=(const game::battlemon::mm::GameMode& gameMode);
};

USTRUCT(BlueprintType)
struct FUSearchGameRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
    FUGameMode game_mode;
    FRegion region;

    FUSearchGameRequest& operator=(const game::battlemon::mm::SearchGameRequest& searchGameRequest);
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
    DEFAULT UMETA(DisplayName = "DEFAULT")
};

USTRUCT(BlueprintType)
struct FUSearchGameResponse
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
    FUSearchGameResponseStatus status;

    FUSearchGameResponse& operator=(const game::battlemon::mm::SearchGameResponse& searchGameResponse);
};

USTRUCT(BlueprintType)
struct FUAcceptGameRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | MMProto")
    FString lemon_id;

    FUAcceptGameRequest& operator=(const game::battlemon::mm::AcceptGameRequest& acceptGameRequest);
};

//mm.massange end

//InternalMM.massange
USTRUCT(BlueprintType)
struct FUInternalUserLeftBattleRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString near_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString room_id;

    FUInternalUserLeftBattleRequest& operator=(const game::battlemon::mm::internal::InternalUserLeftBattleRequest& internalUserLeftBattleRequest);
};

USTRUCT(BlueprintType)
struct FUInternalPlayerResult
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString near_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    int place;

    FUInternalPlayerResult& operator=(const game::battlemon::mm::internal::InternalPlayerResult& internalPlayerResult);
};

USTRUCT(BlueprintType)
struct FUSaveBattleResultRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString room_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    TArray<FUInternalPlayerResult> results;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString ott;

    FUSaveBattleResultRequest& operator=(const game::battlemon::mm::internal::SaveBattleResultRequest& saveBattleResultRequest);
};

USTRUCT(BlueprintType)
struct FURoomInfoRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString room_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString ott;

    FURoomInfoRequest& operator=(const game::battlemon::mm::internal::RoomInfoRequest& roomInfoRequest);
};

USTRUCT(BlueprintType)
struct FURoomPlayerInfo
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString near_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FUItem lemon;

    FURoomPlayerInfo& operator=(const game::battlemon::mm::internal::RoomPlayerInfo& roomPlayerInfo);
};

USTRUCT(BlueprintType)
struct FURoomInfoResponse
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString room_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FUGameMode mode;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    TArray<FURoomPlayerInfo> players;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString ott;

    FURoomInfoResponse& operator=(const game::battlemon::mm::internal::RoomInfoResponse& roomInfoResponse);
};

USTRUCT(BlueprintType)
struct FUCreateRoomRequest
{
    GENERATED_BODY()
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FUGameMode mode;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    TArray<FString> near_ids;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString prev_room_id;

    FUCreateRoomRequest& operator=(const game::battlemon::mm::internal::CreateRoomRequest& createRoomRequest);
};

USTRUCT(BlueprintType)
struct FUDedicatedServerIsReadyRequest
{
    GENERATED_BODY()
        
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString room_id;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | InternalMMProto")
    FString ott;

    FUDedicatedServerIsReadyRequest& operator=(const game::battlemon::mm::internal::DedicatedServerIsReadyRequest& dedicatedServerIsReadyRequest);
};
//InternalMM.massange end







FUWeaponBundleItemType& operator<<(FUWeaponBundleItemType& FU, const game::battlemon::items::WeaponBundleItemType& weaponBundleItemType);

game::battlemon::items::WeaponBundleItemType& operator<<(game::battlemon::items::WeaponBundleItemType& weaponBundleItemType, const FUWeaponBundleItemType& FU);

game::battlemon::items::WeaponBundleSlotType& operator<<(game::battlemon::items::WeaponBundleSlotType& weaponBundleSlotType, const FUWeaponBundleSlotType& FU);

FUWeaponBundleSlotType& operator<<(FUWeaponBundleSlotType& FU, const game::battlemon::items::WeaponBundleSlotType& weaponBundleSlotType);

FUOutfitKind& operator<<(FUOutfitKind& FU, const game::battlemon::items::OutfitKind& outfitKind);

game::battlemon::items::OutfitKind& operator<<(game::battlemon::items::OutfitKind& outfitKind, const FUOutfitKind& FU);

FUModel& operator<<(FUModel& FU, const game::battlemon::items::Item::ModelCase& modelCase);

FUMatchType& operator<<(FUMatchType& FU, const game::battlemon::mm::MatchType& matchType);

game::battlemon::mm::MatchType& operator<<(game::battlemon::mm::MatchType& matchType, const FUMatchType& FU);

FUMatchMode& operator<<(FUMatchMode& FU, const game::battlemon::mm::MatchMode& matchMode);

game::battlemon::mm::MatchMode& operator<<(game::battlemon::mm::MatchMode& matchMode, const FUMatchMode& FU);

game::battlemon::mm::SearchGameResponseStatus& operator<<(game::battlemon::mm::SearchGameResponseStatus& searchGameResponseStatus, const FUSearchGameResponseStatus& FU);

FUSearchGameResponseStatus& operator<<(FUSearchGameResponseStatus& FU, const game::battlemon::mm::SearchGameResponseStatus& searchGameResponseStatus);

FRegion& operator<<(FRegion& FU, const game::battlemon::mm::Region& region);
game::battlemon::mm::Region& operator<<(game::battlemon::mm::Region& region, const  FRegion& FU);