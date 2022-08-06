// Fill out your copyright notice in the Description page of Project Settings.

#include "NearAuth.h"
#include <Kismet/GameplayStatics.h>
#include "NearPlugin.h"
#include "NearAuthSaveGame.h"


#ifdef PLATFORM_WINDOWS
#define TCHAR_TO_P TCHAR_TO_ANSI
#elif PLATFORM_MAC
#define TCHAR_TO_P TCHAR_TO_UTF16
#elif PLATFORM_LINUX
#define TCHAR_TO_P TCHAR_TO_ANSI
#else
#error "Unknown platform"
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

	const char* network;
	if (MainNet)
		network = "mainnet";
	else
		network = "testnet";

	client = new Client(TCHAR_TO_P(FApp::GetProjectName()), network, TypeInp::REGISTRATION);
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
	const char* Account = TCHAR_TO_P(*AccountID);

	client = new Client(TCHAR_TO_P(FApp::GetProjectName()), Account, TypeInp::AUTHORIZATION);

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
				res = FNearPluginModule::_AuthorizedRust((const char*)client->GetPublicKey(), client->GetAccount(), "testnet");
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