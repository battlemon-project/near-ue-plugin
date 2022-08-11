// Fill out your copyright notice in the Description page of Project Settings.

#include "NearAuth.h"
#include <Kismet/GameplayStatics.h>
#include "NearPlugin.h"
#include "Misc/Paths.h"
#include "NearAuthSaveGame.h"


#if PLATFORM_WINDOWS
#define WEBTYPE_M "mainnet"
#define WEBTYPE_T "testnet"
#define GET_CHARPTR(inp) TCHAR_TO_ANSI(*inp)
#else
#define WEBTYPE_M u"mainnet";
#define WEBTYPE_T u"testnet"
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