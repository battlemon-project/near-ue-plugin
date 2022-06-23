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
	freeClient();
}

bool UNearAuth::RegistrationAccount(FString networkType)
{
	freeClient();
	const char* network = TCHAR_TO_ANSI(*networkType);
	client = new Client(network, UNearAuth::rewriteKey);
	return client->IsValidAccount();
}

bool UNearAuth::AuthorizedAccount(FString AccountID, FString networkType)
{
	freeClient();
	const char* Account = TCHAR_TO_ANSI(*AccountID);
	const char* network = TCHAR_TO_ANSI(*networkType);

	client = new Client(Account, network, UNearAuth::rewriteKey);

	return client->IsValidAccount();
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

void UNearAuth::CheckDLL()
{
	size_t res = FNearPluginModule::_AuthorizedRust((const char*)client->GetPublicKey(), client->GetAccount(), "testnet");
	if (res == 10)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success!"));
	}
}

void UNearAuth::freeClient()
{
	if (client != nullptr)
	{
		delete client;
		client = nullptr;
	}
}

bool UNearAuth::rewriteKey(const char* pach)
{
	if (true)
	{
		return true;
	}
	return false;
}
