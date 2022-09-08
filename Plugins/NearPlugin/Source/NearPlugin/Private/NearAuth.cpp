// Fill out your copyright notice in the Description page of Project Settings.

#include "NearAuth.h"
#include <Kismet/GameplayStatics.h>
#include "NearPlugin.h"
#include "Misc/Paths.h"
#include "NearAuthSaveGame.h"


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

Client* UNearAuth::client = nullptr;

UNearAuth::UNearAuth()
{
}

UNearAuth::~UNearAuth()
{
	freeClient();
}

bool UNearAuth::RegistrationAccount(FString& AccountId, bool MainNet)
{
	freeClient();

	client = new Client(GET_CHARPTR(FPaths::ProjectSavedDir()), (MainNet) ? WEBTYPE_M : WEBTYPE_T, TypeInp::REGISTRATION);

	if (client->IsValidAccount())
	{
		AccountId = FString(client->GetAccount());
		saveAccountId();
	}
	return client->IsValidAccount();
}

bool UNearAuth::AuthorizedAccount(FString AccountID)
{
	freeClient();

	client = new Client(GET_CHARPTR(FPaths::ProjectSavedDir()), GET_CHARPTR(AccountID), TypeInp::AUTHORIZATION);

	if (client->IsValidAccount())
		saveAccountId();

	return client->IsValidAccount();
}

void UNearAuth::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountsIds.Insert(FString(client->GetAccount()), 0);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "NearAuth", 0);
}

void UNearAuth::loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid)
{
	bIsValid = false;
	if (!UGameplayStatics::DoesSaveGameExist("NearAuth", 0))
		return;

	const UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("NearAuth", 0));
	AccountsIds = SaveGameInstance->AccountsIds;

	if (AccountsIds.Num() < 0)
		return;

	bIsValid = true;
}

FString UNearAuth::CheckDLL()
{
	size_t res = 0;
	if (client != nullptr)
	{
		if (client->IsValidAccount())
		{
			if (FNearPluginModule::_AuthorizedRust != nullptr)
				res = FNearPluginModule::_AuthorizedRust((const char*)client->GetPublicKey(), client->GetAccount(), RPC_RUST);
			else
			{
				return FNearPluginModule::path;
			}
		}
	}
 	if (res == 10)
	{
		return "Success" + FNearPluginModule::path;
	}
	return FNearPluginModule::path + " error";
}

TArray<FUPlayerItemsClient> UNearAuth::getPlayerItems(FString room_id, TArray<FString> near_ids)
{
	if (client != nullptr)
	{
		TYPE_CHAR* chr_near_ids = new TYPE_CHAR[near_ids.Num()];
		for (size_t i = 0; i < near_ids.Num(); i++)
		{
			chr_near_ids[i] = GET_CHARPTR(near_ids[i]);
		}

		PlayerItemsClient pic = client->gRPC_getPlayerItems(GET_CHARPTR(room_id), near_ids.Num(), (const TYPE_CHAR*)chr_near_ids);
		delete chr_near_ids;

		TArray<FUPlayerItemsClient> upicArry;

		for (size_t i = 0; i < pic.players_items_size; i++)
		{
			//if (pic.near_id[i] != nullptr)
			//{
			//	upic.near_id.Add(pic.near_id[i]);
			//}
			FUPlayerItemsClient upic;
			for (size_t j = 0; j < pic.nft_ids_size; j++)
			{
				upic.nft_idsArr.Add(pic.items[i][j]);
			}
			if (pic.near_id[i] != nullptr)
			{
				upic.near_id = pic.near_id[i];
			}
		}
		return upicArry;
	}

	return TArray<FUPlayerItemsClient>();
}

void UNearAuth::setMyItems(FString room_id, TArray<FString> nft_ids)
{
	if (client != nullptr)
	{
		TYPE_CHAR* chr_nft_ids = new TYPE_CHAR[nft_ids.Num()];
		for (int i = 0; i < nft_ids.Num(); i++)
		{
			//chr_nft_ids[i] = new char[nft_ids[i].Len() + 1];
			chr_nft_ids[i] = GET_CHARPTR(nft_ids[i]);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %s"), *FString(chr_nft_ids[i])));
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %s, y: %s, z: %s"), *FString(chr_nft_ids[0]), *FString(chr_nft_ids[1]), *FString(chr_nft_ids[2])));
		chr_nft_ids[0] = GET_CHARPTR(nft_ids[0]);
		chr_nft_ids[1] = GET_CHARPTR(nft_ids[1]);
		chr_nft_ids[2] = GET_CHARPTR(nft_ids[2]);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %s, y: %s, z: %s"), *FString(chr_nft_ids[0]), *FString(chr_nft_ids[1]), *FString(chr_nft_ids[2])));
		client->gRPC_SetMyItems(GET_CHARPTR(room_id), nft_ids.Num(), (const TYPE_CHAR*)chr_nft_ids);
		for (size_t i = 0; i < nft_ids.Num(); i++)
		{
			delete chr_nft_ids[i];
		}
		delete chr_nft_ids;
	}
}

FUOutfitKind& operator<<(FUOutfitKind& OutfitKindUE, const ModelItems::OutfitKind& OutfitKindResponse)
{
	switch (OutfitKindResponse)
	{
	case 0:
		OutfitKindUE = FUOutfitKind::Cap;
		break;
	case 1:
		OutfitKindUE = FUOutfitKind::Cloth;
		break;
	case 2:
		OutfitKindUE = FUOutfitKind::Fire_ARM;
		break;
	case 3:
		OutfitKindUE = FUOutfitKind::Cold_ARM;
		break;
	case 4:
		OutfitKindUE = FUOutfitKind::Back;
		break;
	default:
		OutfitKindUE = FUOutfitKind::Default;
		break;
	}
	return OutfitKindUE;
}

FUOutfitModel& operator<<(FUOutfitModel& OutfitModellUE, const ModelItems::OutfitModel& OutfitModelResponse)
{
	OutfitModellUE.flavour = OutfitModelResponse.flavour;
	OutfitModellUE.token_id = OutfitModelResponse.token_id;
	OutfitModellUE.kind << OutfitModelResponse.kind;
	return OutfitModellUE;
}

FULemonModel& operator<<(FULemonModel& LemonModelUE, const ModelItems::LemonModel& LemonModelResponse)
{

	LemonModelUE.exo = LemonModelResponse.exo;
	LemonModelUE.eyes = LemonModelResponse.eyes;
	LemonModelUE.head = LemonModelResponse.head;
	LemonModelUE.teeth = LemonModelResponse.teeth;
	LemonModelUE.face = LemonModelResponse.face;
	LemonModelUE.cap << LemonModelResponse.cap;
	LemonModelUE.cloth << LemonModelResponse.cloth;
	LemonModelUE.fire_arm << LemonModelResponse.fire_arm;
	LemonModelUE.cold_arm << LemonModelResponse.cold_arm;
	LemonModelUE.back << LemonModelResponse.back;
	return LemonModelUE;
}

FUItem& operator<<(FUItem& itemsUE, const ModelItems::Item& itemResponse)
{
	itemsUE.token_id = itemResponse.token_id;
	itemsUE.media = itemResponse.media;
	itemsUE.owner_id = itemResponse.owner_id;
	itemsUE.lemon << itemResponse.lemon;
	itemsUE.outfit << itemResponse.outfit;
	return itemsUE;
}

TArray<FUItem> UNearAuth::getItems()
{
	TArray<FUItem> FUItemList;
	if (client != nullptr)
	{
		ItemsList ItemList(client->gRPC_GetItems());
		FUItem uItem;
		for (size_t i = 0; i < ItemList.size; i++)
		{
			uItem << ItemList.getItem(i);
			FUItemList.Add(uItem);
		}

		return FUItemList;
	}
	return TArray<FUItem>();
}

FString UNearAuth::GetError()
{
	if (client->GetError() != nullptr)
		return FString(client->GetError());

	return "OK";
}

void UNearAuth::freeClient()
{
	if (client != nullptr)
	{
		delete client;
		client = nullptr;
	}
}

bool UNearAuth::ClientIsValid()
{
	return client->IsValidAccount();
}