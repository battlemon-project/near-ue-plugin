// Fill out your copyright notice in the Description page of Project Settings.

#include "NearAuth.h"
#include <Kismet/GameplayStatics.h>
#include "NearPlugin.h"
#include "Json.h"
#include "Misc/Paths.h"
#include "NearAuthSaveGame.h"

#define REDIRECT "https://game.battlemon.com/near"

#define NEAR_MAINNET_RPC_URL "https://rpc.mainnet.near.org"
#define NEAR_TESTNET_RPC_URL "https://rpc.testnet.near.org"



UNearAuth::UNearAuth()
{
	freeClient();
}

UNearAuth::~UNearAuth()
{
	freeClient();
}


void UNearAuth::TimerAuthRegist()
{
//	MainClient::client->AuthServiceClient();
//	if (MainClient::client->IsValidAccount())
//	{
//		GetWorld()->GetTimerManager().ClearAllTimersForObject(this);
//
//		MainClient::client->saveKey(GET_CHARPTR(FPaths::ProjectSavedDir()));
//		saveAccountId();
//		if(ResultNearRegist_Delegate.IsBound())
//			ResultNearRegist_Delegate.Broadcast(true);
//	}
//	if (ResultNearRegist_Delegate.IsBound())
//		ResultNearRegist_Delegate.Broadcast(false);
}
FString UNearAuth::getAccountID()
{
	return FString((const TYPE_CHAR*)MainClient::client->GetAccount());
}
void UNearAuth::OnResponseReceived()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UNearAuth::OnGetRequest);
	Request->SetURL("https://api.battlemon.com/rest/contracts");
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UNearAuth::OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	UKismetSystemLibrary::LaunchURL(FString(FString("https://wallet.") + FString(WEBTYPE_T) + ".near.org/login?title=rndname&contract_id=" + ResponseObj->GetStringField("nft_contract_id") + "&success_url=" + REDIRECT + "&public_key=" + FString(MainClient::client->GetPublicKey())));
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UNearAuth::TimerAuthRegist, 1.0f, true, 1.0f);
	
	if (MainClient::client->AuthServiceClient(Type_Call_gRPC::Type_gRPC_Auth::REGISTRATION))
		MainClient::client->saveKey(GET_CHARPTR(FPaths::ProjectSavedDir()));
}


void UNearAuth::PostResponseReceived()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();

	TSharedRef<FJsonObject> RequestObj = MakeShared<FJsonObject>();
	Request->SetContentAsString(//"{\"jsonrpc\": \"2.0\",\"id\" : \"dontcare\",\"method\" : \"query\",\"params\" : {\"request_type\": \"view_access_key\",\"finality\" : \"final\",\"account_id\" : \"" + AccountID + "\",\"public_key\" : \"" + "ed25519:8EzUSbgEYKkMwvTgPZ6fcpE6keY85YPdbAjjzuU4dcuU" + "\"}}");
		FString("{") +
			"\"jsonrpc\": \"2.0\"," +
			"\"id\" : \"dontcare\"," +
			"\"method\" : \"query\"," +
			"\"params\" : {" +
				"\"request_type\": \"view_access_key\"," +
				"\"finality\" : \"final\"," +
				"\"account_id\" : \"" + "dsbgfnghcjhgds.testnet" /*AccountID */ + "\"," +
				"\"public_key\" : \"" + "ed25519:8EzUSbgEYKkMwvTgPZ6fcpE6keY85YPdbAjjzuU4dcuU\"" /*MainClient::client->GetPublicKey() + "\""*/ +
			"}" +
		"}"
	); 
	FString RequestBody;
	TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&RequestBody);
	FJsonSerializer::Serialize(RequestObj, Writer);
	Request->SetContentAsString(FString());
	Request->OnProcessRequestComplete().BindUObject(this, &UNearAuth::OnPOSTRequest);
	Request->SetURL(NEAR_TESTNET_RPC_URL);
	Request->SetVerb("POST");
	Request->SetHeader("Content-Type", "application/json");
	Request->SetContentAsString(RequestBody);
	Request->ProcessRequest();
}

void UNearAuth::OnPOSTRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	TSharedPtr<FJsonObject> ResponseObj;
	TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
	FJsonSerializer::Deserialize(Reader, ResponseObj);

	UE_LOG(LogTemp, Display, TEXT("Response: %s"), *Response->GetContentAsString());
}

void UNearAuth::RegistrationAccount(bool MainNet)
{
	freeClient();
	MainClient::client = new Client(GET_CHARPTR(FPaths::ProjectSavedDir()), (MainNet ? WEBTYPE_M : WEBTYPE_T), Type_Call_gRPC::Type_gRPC_Auth::REGISTRATION);
	OnResponseReceived();
}


bool UNearAuth::AuthorizedAccount(FString AccountID)
{
	freeClient();
	MainClient::client = new Client(GET_CHARPTR(FPaths::ProjectSavedDir()), GET_CHARPTR(AccountID), Type_Call_gRPC::Type_gRPC_Auth::AUTHORIZATION);
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UNearAuth::TimerAuthRegist, 1.0f, true, 1.0f);
	return MainClient::client->AuthServiceClient(Type_Call_gRPC::Type_gRPC_Auth::AUTHORIZATION);
	//return MainClient::client->IsValidAccount();
}

void UNearAuth::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountsIds.Insert(FString(MainClient::client->GetAccount()), 0);
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

bool UNearAuth::CheckAccountKey(FString AccountName)
{
	size_t res = 0;
	res = FNearPluginModule::_AuthorizedRust((const char*)MainClient::client->GetPublicKey(), MainClient::client->GetAccount(), RPC_RUST);
	return res == 10;
}


FString UNearAuth::GetError()
{
	if (MainClient::client->GetError() != nullptr)
		return FString(MainClient::client->GetError());

	return "OK";
}

void UNearAuth::freeClient()
{
	if (MainClient::client != nullptr)
	{
		delete MainClient::client;
		MainClient::client = nullptr;
	}
}

bool UNearAuth::ClientIsValid()
{
	return MainClient::client->IsValidAccount();
}

void UNearItems::freegRPC_Item()
{
	if (gRPC_Item != nullptr)
	{
		delete gRPC_Item;
		gRPC_Item = nullptr;
	}
}

UNearItems::UNearItems():gRPC_Item(nullptr)
{
}

UNearItems::~UNearItems()
{
}



///items.proto

void  UNearItems::Call_gRPC(void* messeng, Type_Call_gRPC::Type_gRPCItem Type_gRPC)
{
	if (MainClient::client != nullptr)
	{
		if (gRPC_Item == nullptr)
			gRPC_Item = new gRPC_ResponseItem(&MainClient::client, messeng, Type_gRPC);
		else
		{
			if (gRPC_Item->GetCall_gRPC() != Type_gRPC)
			{
				freegRPC_Item();
				gRPC_Item = new gRPC_ResponseItem(&MainClient::client, messeng, Type_gRPC);
			}
		}
	}
}

TArray<FUWeaponBundleItem>& operator<<(TArray<FUWeaponBundleItem>& WeaponBundleIUE, const ObjectList<ModelItems::WeaponBundleItem>& WeaponBundleIResponse)
{

	for (int i = 0; i < WeaponBundleIResponse.getSize(); i++)
	{
		FUWeaponBundleItem FUEWBI;
		switch (WeaponBundleIResponse.getObject(i).item_type)
		{
		case ModelItems::WeaponBundleItemType::NONE:
			FUEWBI.item_type = FUWeaponBundleItemType::NONE;
			break;
		case ModelItems::WeaponBundleItemType::BUNDLE_ITEM_PRIMARY:
			FUEWBI.item_type = FUWeaponBundleItemType::BUNDLE_ITEM_PRIMARY;
			break;
		case ModelItems::WeaponBundleItemType::BUNDLE_ITEM_SECONDARY:
			FUEWBI.item_type = FUWeaponBundleItemType::BUNDLE_ITEM_SECONDARY;
			break;
		case ModelItems::WeaponBundleItemType::BUNDLE_ITEM_MELEE:
			FUEWBI.item_type = FUWeaponBundleItemType::BUNDLE_ITEM_MELEE;
			break;
		case ModelItems::WeaponBundleItemType::BUNDLE_ITEM_TACTICAL:
			FUEWBI.item_type = FUWeaponBundleItemType::BUNDLE_ITEM_TACTICAL;
			break;
		case ModelItems::WeaponBundleItemType::BUNDLE_ITEM_MILITARY:
			FUEWBI.item_type = FUWeaponBundleItemType::BUNDLE_ITEM_MILITARY;
			break;
		case ModelItems::WeaponBundleItemType::BUNDLE_ITEM_PERK:
			FUEWBI.item_type = FUWeaponBundleItemType::BUNDLE_ITEM_PERK;
			break;
		default:
			FUEWBI.item_type = FUWeaponBundleItemType::Default;
			break;
		}

		switch (WeaponBundleIResponse.getObject(i).slot_type)
		{
		case ModelItems::WeaponBundleSlotType::NONE:
			FUEWBI.slot_type = FUWeaponBundleSlotType::NONE;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_PRIMARY:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_PRIMARY;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_SECONDARY:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_SECONDARY;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_MELEE:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_MELEE;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE;
			break;
		case ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO:
			FUEWBI.slot_type = FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO;
			break;
		default:
			FUEWBI.slot_type = FUWeaponBundleSlotType::Default;
			break;
		}

		FUEWBI.skin = FString(WeaponBundleIResponse.getObject(i).skin);
		WeaponBundleIUE.Add(FUEWBI);
	}

	return WeaponBundleIUE;
}

TArray<FUWeaponBundle>& operator<<(TArray<FUWeaponBundle>& WeaponBundleUE, const ObjectList<ModelItems::WeaponBundle>& WeaponBundleResponse)
{

	for (int i = 0; i < WeaponBundleResponse.getSize(); i++)
	{
		FUWeaponBundle FUEWB;
		FUEWB.bundle_num = WeaponBundleResponse.getObject(i).bundle_num;
		FUEWB.level = WeaponBundleResponse.getObject(i).level;
		FUEWB.title = FString(WeaponBundleResponse.getObject(i).title);
		FUEWB.items << WeaponBundleResponse.getObject(i).WeaponList;
		WeaponBundleUE.Add(FUEWB);
	}

	return WeaponBundleUE;
}

TArray<FUWeaponBundle> UNearItems::GetBundlesArray()
{
	TArray<FUWeaponBundle> WeaponBundles;
	Call_gRPC(nullptr, Type_Call_gRPC::Type_gRPCItem::GET_BUNDLES);
	WeaponBundles << gRPC_Item->gRPC_GetBundlesArray();
	return WeaponBundles;
}

FUWeaponBundle& operator<<(FUWeaponBundle& WeaponBundleUE, const ModelItems::WeaponBundle& WeaponBundleResponse)
{
	WeaponBundleUE.bundle_num = WeaponBundleResponse.bundle_num;
	WeaponBundleUE.level = WeaponBundleResponse.level;
	WeaponBundleUE.title = FString(WeaponBundleResponse.title);
	WeaponBundleUE.items << WeaponBundleResponse.WeaponList;
	return WeaponBundleUE;
}

FUWeaponBundle UNearItems::GetBundle(int index)
{
	FUWeaponBundle WeaponBundles;
	Call_gRPC(nullptr, Type_Call_gRPC::Type_gRPCItem::GET_BUNDLES);
	WeaponBundles << gRPC_Item->gRPC_GetBundle(index);

	return WeaponBundles;

}

FUWeaponBundle UNearItems::GetEditBundle(FUEditBundleRequest request)
{
	FUWeaponBundle WB;
	if (MainClient::client != nullptr)
	{
		freegRPC_Item();
		ModelItems::WeaponBundleItem* itm = new ModelItems::WeaponBundleItem[request.items.Num()];

		for (int i = 0; i < request.items.Num(); i++)
		{
			switch (request.items[i].item_type)
			{
			case FUWeaponBundleItemType::NONE:
				itm[i].item_type = ModelItems::WeaponBundleItemType::NONE;
				break;
			case FUWeaponBundleItemType::BUNDLE_ITEM_PRIMARY:
				itm[i].item_type = ModelItems::WeaponBundleItemType::BUNDLE_ITEM_PRIMARY;
				break;
			case FUWeaponBundleItemType::BUNDLE_ITEM_SECONDARY:
				itm[i].item_type = ModelItems::WeaponBundleItemType::BUNDLE_ITEM_SECONDARY;
				break;
			case FUWeaponBundleItemType::BUNDLE_ITEM_MELEE:
				itm[i].item_type = ModelItems::WeaponBundleItemType::BUNDLE_ITEM_MELEE;
				break;
			case FUWeaponBundleItemType::BUNDLE_ITEM_TACTICAL:
				itm[i].item_type = ModelItems::WeaponBundleItemType::BUNDLE_ITEM_TACTICAL;
				break;
			case FUWeaponBundleItemType::BUNDLE_ITEM_MILITARY:
				itm[i].item_type = ModelItems::WeaponBundleItemType::BUNDLE_ITEM_MILITARY;
				break;
			case FUWeaponBundleItemType::BUNDLE_ITEM_PERK:
				itm[i].item_type = ModelItems::WeaponBundleItemType::BUNDLE_ITEM_PERK;
				break;
			default:
				itm[i].item_type = ModelItems::WeaponBundleItemType::NONE;
				break;
			}

			switch (request.items[i].slot_type)
			{
			case FUWeaponBundleSlotType::NONE:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::NONE;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_PRIMARY:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_PRIMARY;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_SECONDARY:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_SECONDARY;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_MELEE:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_MELEE;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE;
				break;
			case FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO;
				break;
			default:
				itm[i].slot_type = ModelItems::WeaponBundleSlotType::NONE;
				break;
			}
			itm[i].skin = (TYPE_CHAR*)GET_CHARPTR(request.items[i].skin);
		}

		ObjectList<ModelItems::WeaponBundleItem> items(itm, request.items.Num());
		ModelItems::EditBundleRequest EBR(request.bundle_num, GET_CHARPTR(request.title), &items);

		Call_gRPC(&EBR, Type_Call_gRPC::Type_gRPCItem::EDIT_BUNDLE);
		delete[] itm;
		itm = nullptr;

		WB << gRPC_Item->gRPC_EditBundle();
	}
	return WB;
}

bool UNearItems::GetAttachBundle(FUAttachBundleRequest Request)
{
	ModelItems::AttachBundleRequest messeng(Request.bundle_num, GET_CHARPTR(Request.lemon_id));
	Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPCItem::ATTACH_BUNDLE);
	if (gRPC_Item != nullptr)
	{
		return gRPC_Item->gRPC_AttachBundle();
	}
	return false;
}

bool UNearItems::GetDetachBundle(FUDetachBundleRequest Request)
{
	ModelItems::DetachBundleRequest messeng(Request.bundle_num, GET_CHARPTR(Request.lemon_id));
	Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPCItem::DETACH_BUNDLE);
	if (gRPC_Item != nullptr)
	{
		return gRPC_Item->gRPC_DetachBundle();
	}
	return false;
}

TArray<FUWeaponBundle> UNearItems::GetCopyBundlesArray()
{
	TArray<FUWeaponBundle> FUWB;
	Call_gRPC(nullptr, Type_Call_gRPC::Type_gRPCItem::GET_BUNDLES);
	if (gRPC_Item != nullptr)
		FUWB << gRPC_Item->gRPC_CopyDataBundles();

	return FUWB;
}

FUOutfitKind& operator<<(FUOutfitKind& OutfitKindUE, const ModelItems::OutfitKind& OutfitKindResponse)
{
	switch (OutfitKindResponse)
	{
	case ModelItems::OutfitKind::CAP:
		OutfitKindUE = FUOutfitKind::Cap;
		break;
	case ModelItems::OutfitKind::CLOTH:
		OutfitKindUE = FUOutfitKind::Cloth;
		break;
	case ModelItems::OutfitKind::FIRE_ARM:
		OutfitKindUE = FUOutfitKind::Fire_ARM;
		break;
	case ModelItems::OutfitKind::COLD_ARM:
		OutfitKindUE = FUOutfitKind::Cold_ARM;
		break;
	case ModelItems::OutfitKind::BACK:
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
	OutfitModellUE.flavour = FString((const TYPE_CHAR*)OutfitModelResponse.flavour);
	OutfitModellUE.token_id = FString((const TYPE_CHAR*)OutfitModelResponse.token_id);
	OutfitModellUE.kind << OutfitModelResponse.kind;
	return OutfitModellUE;
}

FULemonModel& operator<<(FULemonModel& LemonModelUE, const ModelItems::LemonModel& LemonModelResponse)
{

	LemonModelUE.exo = FString((const TYPE_CHAR*)LemonModelResponse.exo);
	LemonModelUE.eyes = FString((const TYPE_CHAR*)LemonModelResponse.eyes);
	LemonModelUE.head = FString((const TYPE_CHAR*)LemonModelResponse.head);
	LemonModelUE.teeth = FString((const TYPE_CHAR*)LemonModelResponse.teeth);
	LemonModelUE.face = FString((const TYPE_CHAR*)LemonModelResponse.face);
	LemonModelUE.cap << LemonModelResponse.cap;
	LemonModelUE.cloth << LemonModelResponse.cloth;
	LemonModelUE.fire_arm << LemonModelResponse.fire_arm;
	LemonModelUE.cold_arm << LemonModelResponse.cold_arm;
	LemonModelUE.back << LemonModelResponse.back;
	return LemonModelUE;
}

FUItem& operator<<(FUItem& itemsUE, const ModelItems::Item& itemResponse)
{
	itemsUE.token_id = FString((const TYPE_CHAR*)itemResponse.token_id);
	itemsUE.media = FString((const TYPE_CHAR*)itemResponse.media);
	itemsUE.owner_id = FString((const TYPE_CHAR*)itemResponse.owner_id);

	switch (itemResponse.model)
	{
	case ModelItems::Model::LEMON:
		itemsUE.lemon << itemResponse.lemon;
		itemsUE.model = FUModel::LEMON;
		break;
	case ModelItems::Model::OUTFIT_MODEL:
		itemsUE.outfit << itemResponse.outfit;
		itemsUE.model = FUModel::OUTFIT_MODEL;
		break;
	case ModelItems::Model::DEFAULT:
	default:
		itemsUE.model = FUModel::DEFAULT;
		break;
	}

	return itemsUE;
}

TArray<FUItem>& operator<<(TArray<FUItem>& itemsAUE, const ObjectList<ModelItems::Item>& itemAResponse)
{
	for (int i = 0; i < itemAResponse.getSize(); i++)
	{
		FUItem FUI;
		FUI.in_fight = itemAResponse.getObject(i).in_fight;
		FUI.lemon << itemAResponse.getObject(i).lemon;

		FUI.media = FString(itemAResponse.getObject(i).media);
		FUI.outfit << itemAResponse.getObject(i).outfit;
		FUI.owner_id = FString(itemAResponse.getObject(i).owner_id);
		FUI.token_id = FString(itemAResponse.getObject(i).token_id);
		itemsAUE.Add(FUI);
	}

	return itemsAUE;
}

TArray<FUItem> UNearItems::GetItemsArry()
{
	TArray<FUItem> FUItemList;
	Call_gRPC(nullptr, Type_Call_gRPC::Type_gRPCItem::GET_ITEMS);
	ObjectList<ModelItems::Item> IA = gRPC_Item->gRPC_GetItemsArray();
	for (size_t i = 0; i < IA.getSize(); i++)
	{
		FUItem uItem;
		uItem << IA.getObject(i);
		FUItemList.Add(uItem);
	}
	return FUItemList;
}

TArray<FUItem> UNearItems::GetCopyDataItems()
{
	TArray<FUItem> uItemA;
	Call_gRPC(nullptr, Type_Call_gRPC::Type_gRPCItem::GET_ITEMS);
	uItemA << gRPC_Item->gRPC_CopyDataItems();

	return uItemA;
}

FUItem UNearItems::GetItem(int index)
{
	FUItem uItem;
	Call_gRPC(nullptr, Type_Call_gRPC::Type_gRPCItem::GET_ITEMS);
	uItem << gRPC_Item->gRPC_GetItem(index);

	return uItem;
}

ModelMM::GameMode& operator<<(ModelMM::GameMode& Request, const FUGameMode& RequestUE)
{

	switch (RequestUE.match_mode)
	{
	case FUMatchMode::NONE:
		Request.match_mode = ModelMM::MatchMode::NONE;
		break;
	case FUMatchMode::EQUIPMENT:
		Request.match_mode = ModelMM::MatchMode::EQUIPMENT;
		break; 
	case FUMatchMode::REALISM:
		Request.match_mode = ModelMM::MatchMode::REALISM;
			break;
	case FUMatchMode::Default:
	default:
		Request.match_mode = ModelMM::MatchMode::DEFAULT;
		break;
	}

	switch (RequestUE.match_type)
	{
	case FUMatchType::DEATH_MATCH:
		Request.match_type = ModelMM::MatchType::DEATH_MATCH;
		break;
	case FUMatchType::CATCH_THE_FLAG:
		Request.match_type = ModelMM::MatchType::CATCH_THE_FLAG;
		break;
	case FUMatchType::Default:
	default:
		Request.match_type = ModelMM::MatchType::DEFAULT;
		break;
	}
	//Request.game_mode.match_mode
	return Request;
}

void UNearMM::freegRPC_MM()
{
	if (gRPC_MM != nullptr)
	{
		delete gRPC_MM;
		gRPC_MM = nullptr;
	}
}

UNearMM::UNearMM():gRPC_MM(nullptr)
{
}

UNearMM::~UNearMM()
{
	freegRPC_MM();
}

FUSearchGameResponse UNearMM::SearchGame(FUSearchGameRequest Request)
{
	FUSearchGameResponse USearchGameResponse;
	USearchGameResponse.status = FUSearchGameResponseStatus::Default;

	if (MainClient::client != nullptr)
	{
		ModelMM::GameMode game_mode;
		game_mode << Request.game_mode;
		ModelMM::SearchGameRequest SearchGameRequest(&game_mode);

		freegRPC_MM();
		gRPC_MM = new gRPC_ResponseMM(&MainClient::client, &SearchGameRequest, Type_Call_gRPC::Type_gRPC_MM::SEARCH_GAME);


		switch (gRPC_MM->getResponse_SearchGame().status)
		{
		case ModelMM::SearchGameResponseStatus::OK:
			USearchGameResponse.status = FUSearchGameResponseStatus::OK;
			break;
		case ModelMM::SearchGameResponseStatus::NFT_ERROR:
			USearchGameResponse.status =  FUSearchGameResponseStatus::NFT_ERROR;
			break;
		case ModelMM::SearchGameResponseStatus::ALREADY_IN_QUEUE:
			USearchGameResponse.status =  FUSearchGameResponseStatus::ALREADY_IN_QUEUE;
			break;
		case ModelMM::SearchGameResponseStatus::ALREADY_IN_BATTLE:
			USearchGameResponse.status =  FUSearchGameResponseStatus::ALREADY_IN_BATTLE;
			break;
		case ModelMM::SearchGameResponseStatus::GAMEMODE_ERROR:
			USearchGameResponse.status =  FUSearchGameResponseStatus::GAMEMODE_ERROR;
			break;
		case ModelMM::SearchGameResponseStatus::INVALID_REQUEST:
			USearchGameResponse.status =  FUSearchGameResponseStatus::INVALID_REQUEST;
			break;
		case ModelMM::SearchGameResponseStatus::INTERNAL_ERROR:
			USearchGameResponse.status =  FUSearchGameResponseStatus::INTERNAL_ERROR;
			break;
		default:
			USearchGameResponse.status =  FUSearchGameResponseStatus::Default;
			break;
		}
	}
	
	return USearchGameResponse;
}


bool UNearMM::AcceptGame(FUAcceptGameRequest Request)
{
	if (MainClient::client != nullptr)
	{
		freegRPC_MM();

		ModelMM::AcceptGameRequest inRequest(GET_CHARPTR(Request.lemon_id));
		gRPC_MM = new gRPC_ResponseMM(&MainClient::client, &inRequest, Type_Call_gRPC::Type_gRPC_MM::ACCEPT_GAME);


		return gRPC_MM->getResponse_AcceptGame();
	}
	return false;
}

bool UNearMM::CancelSearch()
{
	if (MainClient::client != nullptr)
	{
		freegRPC_MM();

		gRPC_MM = new gRPC_ResponseMM(&MainClient::client, nullptr, Type_Call_gRPC::Type_gRPC_MM::CANCEL_SEARCH);

		return gRPC_MM->getResponse_CancelSearch();
	}
	return false;
}

///InternalMM.proto

void UNearInternalMM::freegRPC_InternalMM()
{
	if (gRPC_InternalMM != nullptr)
	{
		delete gRPC_InternalMM;
		gRPC_InternalMM = nullptr;
	}
}

bool UNearInternalMM::Call_gRPC(void* messeng, Type_Call_gRPC::Type_gRPC_InternalMM Type_gRPC)
{
	if (MainClient::client != nullptr)
	{
		if (gRPC_InternalMM == nullptr)
		{
			gRPC_InternalMM = new gRPC_ResponseInternalMM(&MainClient::client, messeng, Type_gRPC);
		}
		else
		{
			if (gRPC_InternalMM->GetCall_gRPC() != Type_gRPC)
			{
				freegRPC_InternalMM();
				gRPC_InternalMM = new gRPC_ResponseInternalMM(&MainClient::client, messeng, Type_gRPC);
			}
		}
		return true;
	}
	return false;
}

UNearInternalMM::UNearInternalMM(): gRPC_InternalMM(nullptr)
{
}

UNearInternalMM::~UNearInternalMM()
{
	freegRPC_InternalMM();
}

bool UNearInternalMM::UserLeftBattle(FUInternalUserLeftBattleRequest Request)
{
	ModelInternalMM::InternalUserLeftBattleRequest messeng(GET_CHARPTR(Request.near_id), GET_CHARPTR(Request.room_id));
	if (Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPC_InternalMM::USER_LEFT_BATTLE))
		return gRPC_InternalMM->getResponse_UserLeftBattle();

	return false;
}

ObjectList<ModelInternalMM::InternalPlayerResult>& operator<<(ObjectList<ModelInternalMM::InternalPlayerResult>& Request, const TArray<FUInternalPlayerResult>& RequestUE)
{
	for (size_t i = 0; i < RequestUE.Num(); i++)
	{
		Request[i].near_id = GET_CHARPTR(RequestUE[i].near_id);
		Request[i].place = &RequestUE[i].place;
	}
	return Request;
}

bool UNearInternalMM::SaveBattleResult(FUSaveBattleResultRequest Request)
{
	ObjectList<ModelInternalMM::InternalPlayerResult> results;
	results << Request.results;

	ModelInternalMM::SaveBattleResultRequest messeng(GET_CHARPTR(Request.room_id), &results);
	if (Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPC_InternalMM::USER_LEFT_BATTLE))
		return gRPC_InternalMM->getResponse_SaveBattleResult();

	return false;
}

FUGameMode& operator<<(FUGameMode& toUE, const ModelMM::GameMode& from)
{

	switch (from.match_mode)
	{
	case ModelMM::MatchMode::NONE:
		toUE.match_mode = FUMatchMode::NONE;
		break;
	case ModelMM::MatchMode::EQUIPMENT:
		toUE.match_mode = FUMatchMode::EQUIPMENT;
		break;
	case ModelMM::MatchMode::REALISM:
		toUE.match_mode = FUMatchMode::REALISM;
		break;
	case ModelMM::MatchMode::DEFAULT:
	default:
		toUE.match_mode = FUMatchMode::Default;
		break;
	}

	switch (from.match_type)
	{
	case ModelMM::MatchType::DEATH_MATCH:
		toUE.match_type = FUMatchType::DEATH_MATCH;
		break;
	case ModelMM::MatchType::CATCH_THE_FLAG:
		toUE.match_type = FUMatchType::CATCH_THE_FLAG;
		break;
	case ModelMM::MatchType::DEFAULT:
	default:
		toUE.match_type = FUMatchType::Default;
		break;
	}
	return toUE;
}


TArray<FURoomPlayerInfo>& operator<<(TArray<FURoomPlayerInfo>& toUE, const ObjectList<ModelInternalMM::RoomPlayerInfo>& from)
{
	ModelInternalMM::RoomPlayerInfo * roomPlayerInfoPtr = from.getObjectPtr();
	for (int i = 0; i < from.getSize(); i++)
	{
		FURoomPlayerInfo roomPlayerInfo;
		roomPlayerInfo.lemon << roomPlayerInfoPtr[i].lemon;
		roomPlayerInfo.near_id = FString(roomPlayerInfoPtr[i].near_id);
		toUE.Add(roomPlayerInfo);
	}
	return toUE;
}

FURoomInfoResponse& operator<<(FURoomInfoResponse& toUE, const ModelInternalMM::RoomInfoResponse& from)
{
	toUE.room_id = FString(from.room_id);
	toUE.mode << from.mode;
	toUE.players << from.players;
	return toUE;
}

FURoomInfoResponse UNearInternalMM::GetRoomInfo(FURoomInfoRequest Request)
{
	//RoomInfoResponse
	ModelInternalMM::RoomInfoRequest messeng(GET_CHARPTR(Request.room_id));
	FURoomInfoResponse Response;
	if (Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPC_InternalMM::GET_ROOM_INFO))
	{
		Response << gRPC_InternalMM->getResponse_GetRoomInfo();
		return Response;
	}
	return Response;
}

FURoomInfoResponse UNearInternalMM::CreateRoomWithPlayers(FUCreateRoomRequest Request)
{
	FURoomInfoResponse Response;

	ModelMM::GameMode mode;
	mode << Request.mode;

	ObjectList<const TYPE_CHAR*> near_ids(Request.near_ids.Num());
	for (int i = 0; i < Request.near_ids.Num(); i++)
	{
		near_ids[i] = GET_CHARPTR(Request.near_ids[i]);
	}

	ModelInternalMM::CreateRoomRequest messeng(&mode, &near_ids);
	if (Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPC_InternalMM::GET_ROOM_INFO))
	{
		Response << gRPC_InternalMM->getResponse_CreateRoomWithPlayers();
		return Response;
	}
	return Response;
}

bool UNearInternalMM::DedicatedServerIsReady(FUDedicatedServerIsReadyRequest Request)
{
	ModelInternalMM::DedicatedServerIsReadyRequest messeng(GET_CHARPTR(Request.room_id));
	if (Call_gRPC(&messeng, Type_Call_gRPC::Type_gRPC_InternalMM::DEDICATED_SERVER_IS_READY))
		return gRPC_InternalMM->getResponse_DedicatedServerIsReady();

	return false;
}
