// Fill out your copyright notice in the Description page of Project Settings.


#include "UClient.h"
#include <Kismet/GameplayStatics.h>
//#include "NearAuthSaveGame.h"

v_dllHandle NearRust;
AuthorizedRust _AuthorizedRust;

Client* UClient::client = nullptr;
//bool UClient::autoAuthorized = false;


UClient::UClient()
{
	LoadDLL();
}

UClient::~UClient()
{
	/*if (autoAuthorized)
		saveAccountId();*/

	if (client != nullptr)
	{
		delete client;
		client = nullptr;
	}
	FreeDLL();
}

bool UClient::LoadDLL()
{
	FreeDLL();
#ifdef PLATFORM_WINDOWS
	FString NearAuthPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectContentDir()) + TEXT("/third_party/bin/near_lib.dll");
	if (FPaths::FileExists(NearAuthPath))
	{
		NearRust = FPlatformProcess::GetDllHandle(*NearAuthPath);
		if (NearRust != nullptr)
		{
			FString procName = "authorized";
			_AuthorizedRust = (AuthorizedRust)FPlatformProcess::GetDllExport(NearRust, *procName);
			if (_AuthorizedRust != nullptr)
				return true;
		}
	}
	return false;
#endif
}


void UClient::FreeDLL()
{
	if (NearRust != nullptr)
	{
		if (_AuthorizedRust != nullptr)
		{
			_AuthorizedRust = nullptr;
		}
		FPlatformProcess::FreeDllHandle(NearRust);
		NearRust = nullptr;
	}
}

bool UClient::RegistrationAccount(const char* networkType)
{
	if (client != nullptr)
		delete client;
	client = new Client(networkType);

	if (NearRust == nullptr)
		LoadDLL();

	size_t result = 0;
	if (!client->IsValidAccount())
	{
		FString rpcURL = "https://rpc." + FString(networkType) + ".near.org";
		const char* rpcURLchr = TCHAR_TO_ANSI(*rpcURL);
		result = _AuthorizedRust(client->GetPublicKey(), client->GetAccount(), rpcURLchr);
	}

	return client->IsValidAccount();
}

bool UClient::AuthorizedAccount(const char* AccountID, const char* networkType)
{
	if(client != nullptr)
		delete client;
	client = new Client(AccountID, networkType);

	if (NearRust == nullptr)
		LoadDLL();

	FString rpcURL = "https://rpc." + FString(networkType) + ".near.org";
	const char* rpcURLchr = TCHAR_TO_ANSI(*rpcURL);

	size_t result = _AuthorizedRust(client->GetPublicKey(), AccountID, rpcURLchr);
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

void UClient::saveAccountId()
{
	//FString filename = "A_ID";
	/*UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountId = FString(_GetPlayerAccountId(StartNearAuthObject));
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "NearAuth", 0);*/

}

void UClient::loadAccountId(const char* networkType)
{
	/*
	if (!UGameplayStatics::DoesSaveGameExist("NearAuth", 0))
		return;

	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("NearAuth", 0));
	AccountId = SaveGameInstance->AccountId;

	if (AccountId.IsEmpty())
		return;

	const char* id = TCHAR_TO_ANSI(*AccountId);
	_LoadPlayerAccountId(StartNearAuthObject, id);

	bIsValid = true;*/
}