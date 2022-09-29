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

Client* UNearAuth::client = nullptr;

UNearAuth::UNearAuth()
{
}

UNearAuth::~UNearAuth()
{
	freeClient();
}


void UNearAuth::TimerAuthRegist()
{
	if (client->AuthServiceClient())
	{
		client->saveKey(GET_CHARPTR(FPaths::ProjectSavedDir()));
		saveAccountId();

		ResultNearRegist_Delegate.Broadcast(FString(client->GetAccount()), true);
		return;
	}
	ResultNearRegist_Delegate.Broadcast("NULL", false);
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

	UKismetSystemLibrary::LaunchURL(FString(FString("https://wallet.") + FString(WEBTYPE_T) + ".near.org/login?title=rndname&contract_id=" + ResponseObj->GetStringField("nft_contract_id") + "&success_url=" + REDIRECT + "&public_key=" + FString(client->GetPublicKey())));
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
				"\"public_key\" : \"" + "ed25519:8EzUSbgEYKkMwvTgPZ6fcpE6keY85YPdbAjjzuU4dcuU\"" /*client->GetPublicKey() + "\""*/ +
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
	client = new Client(GET_CHARPTR(FPaths::ProjectSavedDir()), (MainNet ? WEBTYPE_M : WEBTYPE_T), TypeInp::REGISTRATION);
	OnResponseReceived();
}


bool UNearAuth::AuthorizedAccount(FString AccountID)
{
	freeClient();
	client = new Client(GET_CHARPTR(FPaths::ProjectSavedDir()), GET_CHARPTR(AccountID), TypeInp::AUTHORIZATION);
	return client->AuthServiceClient();
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

bool UNearAuth::CheckAccountKey(FString AccountName)
{
	size_t res = 0;
	res = FNearPluginModule::_AuthorizedRust((const char*)client->GetPublicKey(), client->GetAccount(), RPC_RUST);
	return res == 10;
}

TArray<FUPlayerItemsClient> Trash0(FString room_id, TArray<FString> near_ids, Client* client)
{
	PlayerItemsClient pic;
	TYPE_CHAR** chr_near_ids = new TYPE_CHAR*[near_ids.Num()];
	for (int i = 0; i < near_ids.Num();)
	{
		chr_near_ids[i] = new TYPE_CHAR[near_ids[i].Len() + 1];
		const TYPE_CHAR* chr = GET_CHARPTR(near_ids[i]);
		for (int j = 0; j <= near_ids[i].Len(); j++)
		{
			chr_near_ids[i][j] = chr[j];
		}
		i++;
		if (i == near_ids.Num())
		{
			client->gRPC_getPlayerItems(GET_CHARPTR(room_id), near_ids.Num(), (const TYPE_CHAR**)chr_near_ids, pic);

			TArray<FUPlayerItemsClient> upicArry;

			for (size_t c = 0; c < pic.players_items_size; c++)
			{
				FUPlayerItemsClient upic;
				for (size_t j = 0; j < pic.nft_ids_size; j++)
				{
					upic.nft_idsArr.Add(FString(pic.items[c][j]));
				}
				if (pic.near_id[c] != nullptr)
				{
					upic.near_id = pic.near_id[c];
				}
				upicArry.Add(upic);
			}
			for (int j = 0; j < near_ids.Num(); j++)
				delete[]chr_near_ids[j];
			delete[] chr_near_ids;
			return upicArry;
		}
	}
	return TArray<FUPlayerItemsClient>();
}

TArray<FUPlayerItemsClient> UNearAuth::getPlayerItems(FString room_id, TArray<FString> near_ids)
{
	if (client != nullptr)
	{

		return Trash0(room_id, near_ids, client);									//костыль
		/*
		PlayerItemsClient pic;
		TYPE_CHAR** chr_near_ids = new TYPE_CHAR*[near_ids.Num()];
		for (size_t i = 0; i < near_ids.Num(); i++)
		{
			FString str = near_ids[i];
			chr_near_ids[i] = GET_CHARPTR(near_ids[i]);
		}
		GEngine->AddOnScreenDebugMessage(-1, 40.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %s, y: %s, z: %s"), *FString(chr_near_ids[0]), *FString(chr_near_ids[1]), *FString(chr_near_ids[2])));
		client->gRPC_getPlayerItems(GET_CHARPTR(room_id), near_ids.Num(), (const TYPE_CHAR**)chr_near_ids, pic);
		delete chr_near_ids;

		TArray<FUPlayerItemsClient> upicArry;

		for (size_t i = 0; i < pic.players_items_size; i++)
		{
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
		return upicArry;*/
	}

	return TArray<FUPlayerItemsClient>();
}

void Trash1(FString room_id, TArray<FString> nft_ids, Client *client)
{
	TYPE_CHAR** chr_nft_ids = new TYPE_CHAR*[nft_ids.Num()];
	for (int i = 0; i < nft_ids.Num();)
	{
		chr_nft_ids[i] = new TYPE_CHAR[nft_ids[i].Len() + 1];
		const TYPE_CHAR* chr = GET_CHARPTR(nft_ids[i]);
		for (int j = 0; j <= nft_ids[i].Len(); j++)
		{
			chr_nft_ids[i][j] = chr[j];
		}
		i++;
		if (i == nft_ids.Num())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 40.f, FColor::Red, FString::Printf(TEXT("Some variable values: x: %s, y: %s, z: %s"), *FString(chr_nft_ids[0]), *FString(chr_nft_ids[1]), *FString(chr_nft_ids[2])));
			client->gRPC_SetMyItems(GET_CHARPTR(room_id), nft_ids.Num(), (const TYPE_CHAR**)chr_nft_ids);


			for (int j = 0; j < nft_ids.Num(); j++)
				delete[]chr_nft_ids[j];
			delete[] chr_nft_ids;
		}
	}

}

void UNearAuth::setMyItems(FString room_id, TArray<FString> nft_ids)
{
	if (client != nullptr)
	{
		Trash1(room_id, nft_ids, client);									//костыль

		/*
		TYPE_CHAR** chr_nft_ids = new TYPE_CHAR*[nft_ids.Num()];
		for (int i = 0; i < nft_ids.Num(); i++)						<================================		криво работающий цикл
		{
			chr_nft_ids[i] = GET_CHARPTR(nft_ids[i]);
		}
																	<================================		результат		chr_nft_ids[0] = chr_nft_ids[1] = chr_nft_ids[2] = ... = nft_ids[nft_ids.Num() - 1]
		client->gRPC_SetMyItems(GET_CHARPTR(room_id), nft_ids.Num(), (const TYPE_CHAR**)chr_nft_ids);
		delete[] chr_nft_ids;
		*/
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