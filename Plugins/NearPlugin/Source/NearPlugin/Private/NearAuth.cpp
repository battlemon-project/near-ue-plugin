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

bool UNearAuth::RegistrationAccount(FString networkType, FString& AccountId)
{
	freeClient();
	const char* network = TCHAR_TO_ANSI(*networkType);
	client = new Client(network, TypeInp::REGISTRATION);
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
	const char* Account = TCHAR_TO_ANSI(*AccountID);

	client = new Client(Account, TypeInp::AUTHORIZATION);
	
	if (client->IsValidAccount())
		saveAccountId();
	
	return client->IsValidAccount();
}

void UNearAuth::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountsIds.Insert(FString(client->GetAccount()),0);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "NearAuth", 0);
}

void UNearAuth::loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid)
{
	bIsValid = false;
	if (!UGameplayStatics::DoesSaveGameExist("NearAuth", 0))
		return;

	const UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("NearAuth", 0));
	AccountsIds = SaveGameInstance->AccountsIds;

	if (AccountsIds.Num()<0)
		return;

	bIsValid = true;
}

void UNearAuth::CheckDLL()
{
	size_t res = 0;
	if(client->IsValidAccount())
		res = FNearPluginModule::_AuthorizedRust((const char*)client->GetPublicKey(), client->GetAccount(), "testnet");
	if (res == 10)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Success!"));
	}
}

FString UNearAuth::GetError()
{
	if(client->GetError() != nullptr)
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