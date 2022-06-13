// Fill out your copyright notice in the Description page of Project Settings.


#include "NearAuth.h"
#include <Kismet/GameplayStatics.h>
#include "NearPlugin.h"
#include "NearAuthSaveGame.h"

Client* UNearAuth::client = nullptr;
UNearAuth::UNearAuth()
{
}

UNearAuth::~UNearAuth()
{
	if (client != nullptr)
		delete client;
}

bool UNearAuth::RegistrationAccount(FString networkType)
{
	if (client != nullptr)
		delete client;

	const char* network = TCHAR_TO_ANSI(*networkType);
	client = new Client(network);
	return client->IsValidAccount();
}

bool UNearAuth::AuthorizedAccount(FString AccountID, FString networkType)
{
	if (client != nullptr)
		delete client;
	const char* Account = TCHAR_TO_ANSI(*AccountID);
	const char* network = TCHAR_TO_ANSI(*networkType);

	client = new Client(Account, network);

	FString rpcURL = "https://rpc." + networkType + ".near.org";
	const char* rpcURLchr = TCHAR_TO_ANSI(*rpcURL);

	size_t result = FNearPluginModule::_AuthorizedRust(client->GetPublicKey(), client->GetAccount(), rpcURLchr);
	return result == 10;
	/*
	switch (result)
	{
	case :

		break;
	default:
		break;
	}*/
}

void UNearAuth::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountId = FString(client->GetAccount());
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "NearAuth", 0);
}

void UNearAuth::loadAccountId(FString& AccountId, FString networkType, bool& bIsValid)
{
	
	if (!UGameplayStatics::DoesSaveGameExist("NearAuth", 0))
		return;

	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("NearAuth", 0));
	AccountId = SaveGameInstance->AccountId;

	if (AccountId.IsEmpty())
		return;

	bIsValid = AuthorizedAccount(AccountId, networkType);
}