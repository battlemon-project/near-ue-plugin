#pragma once
 #include "gRPC_Base.h"

#include "GrpcBegin.h"

#include <protocol/items.grpc.pb.h>
#include <protocol/common.grpc.pb.h>

#include "GrpcEnd.h"

#include "common.h"


#include "items.generated.h"



UENUM(BlueprintType)
enum class FUItemCase : uint8
{	
	Default UMETA(DisplayName = "Default"),
	kNft UMETA(DisplayName = "kNft"),
	kNonNft UMETA(DisplayName = "kNonNft")
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
struct FUDetachBundleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString lemon_id;

	FUDetachBundleRequest& operator=(const game::battlemon::items::DetachBundleRequest& grpcDetachBundleRequest);

};


USTRUCT(BlueprintType)
struct FUAttachBundleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString lemon_id;

	FUAttachBundleRequest& operator=(const game::battlemon::items::AttachBundleRequest& grpcAttachBundleRequest);

};


USTRUCT(BlueprintType)
struct FUWeaponBundleItem 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FUWeaponBundleItemType item_type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString skin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FUWeaponBundleSlotType slot_type;

	FUWeaponBundleItem& operator=(const game::battlemon::items::WeaponBundleItem& grpcWeaponBundleItem);

};


USTRUCT(BlueprintType)
struct FUEditBundleRequest 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUWeaponBundleItem> items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString title;

	FUEditBundleRequest& operator=(const game::battlemon::items::EditBundleRequest& grpcEditBundleRequest);

};


USTRUCT(BlueprintType)
struct FUWeaponBundle 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int32 bundle_num;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUWeaponBundleItem> items;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int32 level;

	FUWeaponBundle& operator=(const game::battlemon::items::WeaponBundle& grpcWeaponBundle);

};


USTRUCT(BlueprintType)
struct FUGetBundlesResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUWeaponBundle> bundles;

	FUGetBundlesResponse& operator=(const game::battlemon::items::GetBundlesResponse& grpcGetBundlesResponse);

};


USTRUCT(BlueprintType)
struct FUGetBundlesRequest 
{
	GENERATED_BODY()
	

	FUGetBundlesRequest& operator=(const game::battlemon::items::GetBundlesRequest& grpcGetBundlesRequest);

};


USTRUCT(BlueprintType)
struct FUNonNftItem 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int32 level;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUWeaponBundle> attached_bundles;

	FUNonNftItem& operator=(const game::battlemon::items::NonNftItem& grpcNonNftItem);

};





USTRUCT(BlueprintType)
struct FUTrait 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString flavour;

	FUTrait& operator=(const game::battlemon::items::Trait& grpcTrait);

};


USTRUCT(BlueprintType)
struct FUNftItem 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString id;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString type;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString owner;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FString url;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUTrait> traits;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	int64 created_at;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUWeaponBundle> attached_bundles;

	FUNftItem& operator=(const game::battlemon::items::NftItem& grpcNftItem);

};

USTRUCT(BlueprintType)
struct FUItem 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FUItemCase item_case;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FUNftItem nft;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	FUNonNftItem non_nft;

	FUItem& operator=(const game::battlemon::items::Item& grpcItem);

};

USTRUCT(BlueprintType)
struct FUItemsResponse 
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ".Crypto | itemsProto")
	TArray<FUItem> items;

	FUItemsResponse& operator=(const game::battlemon::items::ItemsResponse& grpcItemsResponse);

};


USTRUCT(BlueprintType)
struct FUItemsRequest 
{
	GENERATED_BODY()
	

	FUItemsRequest& operator=(const game::battlemon::items::ItemsRequest& grpcItemsRequest);

};




DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttachBundleDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDetachBundleDelegate, const FUEmpty&, Response); 
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEditBundleDelegate, const FUWeaponBundle&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetBundlesDelegate, const FUGetBundlesResponse&, Response);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetItemsDelegate, const FUItemsResponse&, Response);



class RPC_ItemsService : public gRPC_Stub<game::battlemon::items::ItemsService, game::battlemon::items::ItemsService::Stub>
{
	void* Delegate;
	void* out;
public:
	RPC_ItemsService(const bool& ssl, FString& url, void* _Delegate, void* _out);
	~RPC_ItemsService();

	game::battlemon::items::ItemsResponse GetItems(grpc::ClientContext* context, const game::battlemon::items::ItemsRequest* request);
	game::battlemon::items::GetBundlesResponse GetBundles(grpc::ClientContext* context, const game::battlemon::items::GetBundlesRequest* request);
	game::battlemon::items::WeaponBundle EditBundle(grpc::ClientContext* context, const game::battlemon::items::EditBundleRequest* request);
	game::battlemon::common::Empty AttachBundle(grpc::ClientContext* context, const game::battlemon::items::AttachBundleRequest* request);
	game::battlemon::common::Empty DetachBundle(grpc::ClientContext* context, const game::battlemon::items::DetachBundleRequest* request);
	
};

enum class ItemsServiceRPC
{
	GetItems,
	GetBundles,
	EditBundle,
	AttachBundle,
	DetachBundle,
};

UCLASS(Blueprintable)
class NEARPLUGIN_API UItemsService : public UObject
{
	GENERATED_BODY()

	void free_RPC_ItemsService();
	static RPC_ItemsService* _RPC_ItemsService;
	ItemsServiceRPC rpc;

public:
	UItemsService();
	~UItemsService();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | ItemsService", meta = (ExposeOnSpawn = true))
	FString URL;
	UPROPERTY(BlueprintReadWrite, Category = ".Crypto| ItemsService", meta = (ExposeOnSpawn = true))
	bool ssl = true;

	UPROPERTY(BlueprintAssignable, Category = ".Crypto | ItemsService")
	FAttachBundleDelegate AttachBundleDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | ItemsService")
	FDetachBundleDelegate DetachBundleDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | ItemsService")
	FEditBundleDelegate EditBundleDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | ItemsService")
	FGetBundlesDelegate GetBundlesDelegate;
	UPROPERTY(BlueprintAssignable, Category = ".Crypto | ItemsService")
	FGetItemsDelegate GetItemsDelegate;

	UFUNCTION(BlueprintCallable, Category = ".Crypto | ItemsService")
	void GetItems(TMap<FString, FString> context, FUItemsRequest inp, FUItemsResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | ItemsService")
	void GetBundles(TMap<FString, FString> context, FUGetBundlesRequest inp, FUGetBundlesResponse &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | ItemsService")
	void EditBundle(TMap<FString, FString> context, FUEditBundleRequest inp, FUWeaponBundle &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | ItemsService")
	void AttachBundle(TMap<FString, FString> context, FUAttachBundleRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | ItemsService")
	void DetachBundle(TMap<FString, FString> context, FUDetachBundleRequest inp, FUEmpty &out);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | ItemsService")
	FString GetError();
};



FUItemCase& operator<<(FUItemCase &UE, const game::battlemon::items::Item::ItemCase& grpc);

FUWeaponBundleItemType& operator<<(FUWeaponBundleItemType &UE, const game::battlemon::items::WeaponBundleItemType& grpc);

FUWeaponBundleSlotType& operator<<(FUWeaponBundleSlotType &UE, const game::battlemon::items::WeaponBundleSlotType& grpc);

game::battlemon::items::Item::ItemCase& operator<<(game::battlemon::items::Item::ItemCase & grpc, const FUItemCase &UE); 

game::battlemon::items::WeaponBundleItemType& operator<<(game::battlemon::items::WeaponBundleItemType & grpc, const FUWeaponBundleItemType &UE); 

game::battlemon::items::WeaponBundleSlotType& operator<<(game::battlemon::items::WeaponBundleSlotType & grpc, const FUWeaponBundleSlotType &UE); 

game::battlemon::items::DetachBundleRequest &operator<<(game::battlemon::items::DetachBundleRequest &grpcDetachBundleRequest, const FUDetachBundleRequest &UE);

game::battlemon::items::AttachBundleRequest &operator<<(game::battlemon::items::AttachBundleRequest &grpcAttachBundleRequest, const FUAttachBundleRequest &UE);

game::battlemon::items::WeaponBundleItem &operator<<(game::battlemon::items::WeaponBundleItem &grpcWeaponBundleItem, const FUWeaponBundleItem &UE);

game::battlemon::items::EditBundleRequest &operator<<(game::battlemon::items::EditBundleRequest &grpcEditBundleRequest, const FUEditBundleRequest &UE);

game::battlemon::items::WeaponBundle &operator<<(game::battlemon::items::WeaponBundle &grpcWeaponBundle, const FUWeaponBundle &UE);

game::battlemon::items::GetBundlesResponse &operator<<(game::battlemon::items::GetBundlesResponse &grpcGetBundlesResponse, const FUGetBundlesResponse &UE);

game::battlemon::items::GetBundlesRequest &operator<<(game::battlemon::items::GetBundlesRequest &grpcGetBundlesRequest, const FUGetBundlesRequest &UE);

game::battlemon::items::NonNftItem &operator<<(game::battlemon::items::NonNftItem &grpcNonNftItem, const FUNonNftItem &UE);

game::battlemon::items::Item &operator<<(game::battlemon::items::Item &grpcItem, const FUItem &UE);

game::battlemon::items::Trait &operator<<(game::battlemon::items::Trait &grpcTrait, const FUTrait &UE);

game::battlemon::items::NftItem &operator<<(game::battlemon::items::NftItem &grpcNftItem, const FUNftItem &UE);

game::battlemon::items::ItemsResponse &operator<<(game::battlemon::items::ItemsResponse &grpcItemsResponse, const FUItemsResponse &UE);

game::battlemon::items::ItemsRequest &operator<<(game::battlemon::items::ItemsRequest &grpcItemsRequest, const FUItemsRequest &UE);

