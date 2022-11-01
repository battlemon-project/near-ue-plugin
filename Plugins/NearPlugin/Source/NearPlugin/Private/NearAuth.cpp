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
	//return MainClient::client->AuthServiceClient();
	return MainClient::client->IsValidAccount();
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

UNearItems::UNearItems()
{
}




///items.proto

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

TArray<FUItem> UNearItems::getCopyItems()
{
	//TArray<FUItem> FUItemList;
	//if (MainClient::client != nullptr)
	//{
	//	ItemsList ItemList(MainClient::client->gRPC_CopyItems());
	//	FUItem uItem;
	//	for (size_t i = 0; i < ItemList.size; i++)
	//	{
	//		uItem << ItemList.getItem(i);
	//		FUItemList.Add(uItem);
	//	}
	//
	//	return FUItemList;
	//}
	return TArray<FUItem>();
}

TArray<FUItem> UNearItems::getItemsPtr()
{
	//TArray<FUItem> FUItemList;
	//if (MainClient::client != nullptr)
	//{
	//	ItemsList ItemList(MainClient::client->gRPC_GetItems());
	//	FUItem uItem;
	//	for (size_t i = 0; i < ItemList.size; i++)
	//	{
	//		uItem << ItemList.getItem(i);
	//		FUItemList.Add(uItem);
	//	}
	//
	//	return FUItemList;
	//}
	return TArray<FUItem>();
}

FUItem UNearItems::getItem(int index)
{
	FUItem uItem;
	//if (MainClient::client != nullptr)
	//{
	//	uItem << MainClient::client->gRPC_GetItem(index);
	//}

	return uItem;
}




ModelMM::SearchGameRequest& operator<<(ModelMM::SearchGameRequest& Request, const FUSearchGameRequest& RequestUE)
{

	switch (RequestUE.game_mode.match_mode)
	{
	case FUMatchMode::NONE:
		Request.game_mode.match_mode = ModelMM::MatchMode::NONE;
		break;
	case FUMatchMode::EQUIPMENT:
		Request.game_mode.match_mode = ModelMM::MatchMode::EQUIPMENT;
		break; 
	case FUMatchMode::REALISM:
		Request.game_mode.match_mode = ModelMM::MatchMode::REALISM;
			break;
	case FUMatchMode::Default:
	default:
		Request.game_mode.match_mode = ModelMM::MatchMode::DEFAULT;
		break;
	}

	switch (RequestUE.game_mode.match_type)
	{
	case FUMatchType::DEATH_MATCH:
		Request.game_mode.match_type = ModelMM::MatchType::DEATH_MATCH;
		break;
	case FUMatchType::CATCH_THE_FLAG:
		Request.game_mode.match_type = ModelMM::MatchType::CATCH_THE_FLAG;
		break;
	case FUMatchType::Default:
	default:
		Request.game_mode.match_type = ModelMM::MatchType::DEFAULT;
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

FUSearchGameResponse UNearMM::SearchGame(FUSearchGameRequest Request)
{
	FUSearchGameResponse USearchGameResponse;
	USearchGameResponse.status = FUSearchGameResponseStatus::Default;

	if (MainClient::client != nullptr)
	{
		ModelMM::SearchGameRequest SearchGameRequest;
		SearchGameRequest << Request;

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

ModelMM::AcceptGameRequest& operator<<(ModelMM::AcceptGameRequest& Request, const FUAcceptGameRequest& RequestUE)
{
	Request.lemon_id = GET_CHARPTR(RequestUE.lemon_id);
	return Request;
}

bool UNearMM::AcceptGame(FUAcceptGameRequest Request)
{
	if (MainClient::client != nullptr)
	{
		freegRPC_MM();

		ModelMM::AcceptGameRequest inRequest;
		inRequest << Request;
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