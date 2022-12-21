#pragma once
#include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/items.grpc.pb.h>
#include <protocol/common.grpc.pb.h>

#include "GrpcEnd.h"

#include "common.h"


#include "items.generated.h"



UENUM(BlueprintType)
enum class FUModelCase : uint8
{	
	Default UMETA(DisplayName = "Default"),
	kLemon UMETA(DisplayName = "kLemon"),
	kOutfit UMETA(DisplayName = "kOutfit")
};

UENUM(BlueprintType)
enum class FUOutfitKind : uint8
{	
	Default UMETA(DisplayName = "Default"),
	CAP UMETA(DisplayName = "CAP"),
	CLOTH UMETA(DisplayName = "CLOTH"),
	FIRE_ARM UMETA(DisplayName = "FIRE_ARM"),
	COLD_ARM UMETA(DisplayName = "COLD_ARM"),
	BACK UMETA(DisplayName = "BACK")
};

UENUM(BlueprintType)
enum class FUWeaponBundleItemType : uint8
{	
	Default UMETA(DisplayName = "Default"),
	BUNDLE_ITEM_PRIMARY UMETA(DisplayName = "BUNDLE_ITEM_PRIMARY"),
	BUNDLE_ITEM_SECONDARY UMETA(DisplayName = "BUNDLE_ITEM_SECONDARY"),
	BUNDLE_ITEM_MELEE UMETA(DisplayName = "BUNDLE_ITEM_MELEE"),
	BUNDLE_ITEM_TACTICAL UMETA(DisplayName = "BUNDLE_ITEM_TACTICAL"),
	BUNDLE_ITEM_MILITARY UMETA(DisplayName = "BUNDLE_ITEM_MILITARY"),
	BUNDLE_ITEM_PERK UMETA(DisplayName = "BUNDLE_ITEM_PERK")
};

UENUM(BlueprintType)
enum class FUWeaponBundleSlotType : uint8
{	
	Default UMETA(DisplayName = "Default"),
	BUNDLE_SLOT_PRIMARY UMETA(DisplayName = "BUNDLE_SLOT_PRIMARY"),
	BUNDLE_SLOT_SECONDARY UMETA(DisplayName = "BUNDLE_SLOT_SECONDARY"),
	BUNDLE_SLOT_MELEE UMETA(DisplayName = "BUNDLE_SLOT_MELEE"),
	BUNDLE_SLOT_TACTICAL_ONE UMETA(DisplayName = "BUNDLE_SLOT_TACTICAL_ONE"),
	BUNDLE_SLOT_TACTICAL_TWO UMETA(DisplayName = "BUNDLE_SLOT_TACTICAL_TWO"),
	BUNDLE_SLOT_MILITARY_ONE UMETA(DisplayName = "BUNDLE_SLOT_MILITARY_ONE"),
	BUNDLE_SLOT_MILITARY_TWO UMETA(DisplayName = "BUNDLE_SLOT_MILITARY_TWO"),
	BUNDLE_SLOT_PERK_ONE UMETA(DisplayName = "BUNDLE_SLOT_PERK_ONE"),
	BUNDLE_SLOT_PERK_TWO UMETA(DisplayName = "BUNDLE_SLOT_PERK_TWO")
};



USTRUCT(BlueprintType)
struct FUItemsRequest 
{
	GENERATED_BODY()
	

	FUItemsRequest& operator=(const game::battlemon::items::ItemsRequest& grpcItemsRequest);

};

USTRUCT(BlueprintType)
struct FUOutfitModel 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString flavour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitKind kind;

	FUOutfitModel& operator=(const game::battlemon::items::OutfitModel& grpcOutfitModel);

};

USTRUCT(BlueprintType)
struct FUWeaponBundleItem 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUWeaponBundleItemType item_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUWeaponBundleSlotType slot_type;

	FUWeaponBundleItem& operator=(const game::battlemon::items::WeaponBundleItem& grpcWeaponBundleItem);

};

USTRUCT(BlueprintType)
struct FUWeaponBundle 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	TArray<FUWeaponBundleItem> items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	int32 level;

	FUWeaponBundle& operator=(const game::battlemon::items::WeaponBundle& grpcWeaponBundle);

};


USTRUCT(BlueprintType)
struct FULemonModel 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitModel cap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitModel cloth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString exo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString eyes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString head;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString teeth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString face;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitModel fire_arm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitModel cold_arm;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitModel back;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	TArray<FUWeaponBundle> attached_bundles;

	FULemonModel& operator=(const game::battlemon::items::LemonModel& grpcLemonModel);

};


USTRUCT(BlueprintType)
struct FUItem 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString token_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString media;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString owner_id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	bool in_fight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUModelCase model_case;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FULemonModel lemon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FUOutfitModel outfit;

	FUItem& operator=(const game::battlemon::items::Item& grpcItem);

};

USTRUCT(BlueprintType)
struct FUItemsResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	TArray<FUItem> items;

	FUItemsResponse& operator=(const game::battlemon::items::ItemsResponse& grpcItemsResponse);

};


USTRUCT(BlueprintType)
struct FUGetBundlesRequest 
{
	GENERATED_BODY()
	

	FUGetBundlesRequest& operator=(const game::battlemon::items::GetBundlesRequest& grpcGetBundlesRequest);

};


USTRUCT(BlueprintType)
struct FUGetBundlesResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	TArray<FUWeaponBundle> bundles;

	FUGetBundlesResponse& operator=(const game::battlemon::items::GetBundlesResponse& grpcGetBundlesResponse);

};


USTRUCT(BlueprintType)
struct FUEditBundleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	TArray<FUWeaponBundleItem> items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString title;

	FUEditBundleRequest& operator=(const game::battlemon::items::EditBundleRequest& grpcEditBundleRequest);

};


USTRUCT(BlueprintType)
struct FUAttachBundleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString lemon_id;

	FUAttachBundleRequest& operator=(const game::battlemon::items::AttachBundleRequest& grpcAttachBundleRequest);

};


USTRUCT(BlueprintType)
struct FUDetachBundleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Near | itemsProto")
	FString lemon_id;

	FUDetachBundleRequest& operator=(const game::battlemon::items::DetachBundleRequest& grpcDetachBundleRequest);

};


FUModelCase& operator<<(FUModelCase &UE, const game::battlemon::items::Item::ModelCase& grpc);

FUOutfitKind& operator<<(FUOutfitKind &UE, const game::battlemon::items::OutfitKind& grpc);

FUWeaponBundleItemType& operator<<(FUWeaponBundleItemType &UE, const game::battlemon::items::WeaponBundleItemType& grpc);

FUWeaponBundleSlotType& operator<<(FUWeaponBundleSlotType &UE, const game::battlemon::items::WeaponBundleSlotType& grpc);

game::battlemon::items::Item::ModelCase& operator<<(game::battlemon::items::Item::ModelCase & grpc, const FUModelCase &UE); 

game::battlemon::items::OutfitKind& operator<<(game::battlemon::items::OutfitKind & grpc, const FUOutfitKind &UE); 

game::battlemon::items::WeaponBundleItemType& operator<<(game::battlemon::items::WeaponBundleItemType & grpc, const FUWeaponBundleItemType &UE); 

game::battlemon::items::WeaponBundleSlotType& operator<<(game::battlemon::items::WeaponBundleSlotType & grpc, const FUWeaponBundleSlotType &UE); 

game::battlemon::items::ItemsRequest &operator<<(game::battlemon::items::ItemsRequest &grpcItemsRequest, const FUItemsRequest &UE);

game::battlemon::items::ItemsResponse &operator<<(game::battlemon::items::ItemsResponse &grpcItemsResponse, const FUItemsResponse &UE);

game::battlemon::items::Item &operator<<(game::battlemon::items::Item &grpcItem, const FUItem &UE);

game::battlemon::items::LemonModel &operator<<(game::battlemon::items::LemonModel &grpcLemonModel, const FULemonModel &UE);

game::battlemon::items::OutfitModel &operator<<(game::battlemon::items::OutfitModel &grpcOutfitModel, const FUOutfitModel &UE);

game::battlemon::items::WeaponBundle &operator<<(game::battlemon::items::WeaponBundle &grpcWeaponBundle, const FUWeaponBundle &UE);

game::battlemon::items::WeaponBundleItem &operator<<(game::battlemon::items::WeaponBundleItem &grpcWeaponBundleItem, const FUWeaponBundleItem &UE);

game::battlemon::items::GetBundlesRequest &operator<<(game::battlemon::items::GetBundlesRequest &grpcGetBundlesRequest, const FUGetBundlesRequest &UE);

game::battlemon::items::GetBundlesResponse &operator<<(game::battlemon::items::GetBundlesResponse &grpcGetBundlesResponse, const FUGetBundlesResponse &UE);

game::battlemon::items::EditBundleRequest &operator<<(game::battlemon::items::EditBundleRequest &grpcEditBundleRequest, const FUEditBundleRequest &UE);

game::battlemon::items::AttachBundleRequest &operator<<(game::battlemon::items::AttachBundleRequest &grpcAttachBundleRequest, const FUAttachBundleRequest &UE);

game::battlemon::items::DetachBundleRequest &operator<<(game::battlemon::items::DetachBundleRequest &grpcDetachBundleRequest, const FUDetachBundleRequest &UE);

