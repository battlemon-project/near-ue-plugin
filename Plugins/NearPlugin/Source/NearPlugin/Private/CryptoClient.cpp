// Fill out your copyright notice in the Description page of Project Settings.


#include "CryptoClient.h"
#include <Kismet/GameplayStatics.h>
#include "NearAuthSaveGame.h"


#if defined(__unix__)
#define CONV_FSTRING_TO_CHAR(str) TCHAR_TO_UTF8(*str)
#define CONV_CHAR_TO_FSTRING(str)  UTF8_TO_TCHAR(str)
#else
#define CONV_FSTRING_TO_CHAR(str) TCHAR_TO_ANSI(*str)
#define CONV_CHAR_TO_FSTRING(str) UTF8_TO_TCHAR(str)
#endif


DataClient UCryptoClient::data;

UCryptoClient::UCryptoClient() 
{
}

UCryptoClient::~UCryptoClient()
{
}


//FString UCryptoClient::GetPublicKey_Base58()
//{
//	return FString(data.keyPair.GetPubKey58().c_str());
//}

//FString UCryptoClient::GetSing()
//{
//	return CONV_CHAR_TO_FSTRING(data.keyPair.GetSign().c_str());
//}

FString UCryptoClient::GetWalletAddress()
{
	return data.session.wallet_address;
}

FUSuiSession UCryptoClient::GetSuiSession()
{
	return data.session;
}

//void UCryptoClient::SetSing(FString _sing)
//{
//	std::string signl = CONV_FSTRING_TO_CHAR(_sing);
//	data.keyPair.SetSign(signl);
//}

bool UCryptoClient::IsValidAccount()
{
	return !data.session.wallet_address.IsEmpty();
}
/*
bool UCryptoClient::IsValidKeys()
{
	return data.keyPair.IsValid();
}

FString UCryptoClient::SignAMessage(FString Message)
{
	FString MessageOUT = CONV_CHAR_TO_FSTRING(data.keyPair.MessageSigning(CONV_FSTRING_TO_CHAR(Message)));
	return MessageOUT;
}

void UCryptoClient::CreateNewKey()
{
	TYPE_CHAR* plug;
	data.keyPair.GeneratingKeys(plug, nullptr);
}

void UCryptoClient::SaveData()
{
	data.keyPair.SaveKeys(TYPE_STRING(*data.accountID), TYPE_STRING(*FPaths::ProjectSavedDir()));
	data.keyPair.SaveSign(TYPE_STRING(*data.accountID), TYPE_STRING(*FPaths::ProjectSavedDir()), data.keyPair.GetSign().c_str());
}

void UCryptoClient::LoadData(FString AccountsId)
{
	data.accountID = AccountsId;
	data.keyPair.LoadKeys(*data.accountID, *FPaths::ProjectSavedDir());
	data.keyPair.LoadSign(*data.accountID, *FPaths::ProjectSavedDir());
}
*/
void UCryptoClient::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountsIds.Insert(data.accountID, 0);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "UCryptoClient", 0);
	
//	SaveData();
}

void UCryptoClient::loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid)
{
	bIsValid = false;
	if (!UGameplayStatics::DoesSaveGameExist("UCryptoClient", 0))
		return;
	const UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("UCryptoClient", 0));
	AccountsIds = SaveGameInstance->AccountsIds;
	if (AccountsIds.Num() < 0)
		return;
	bIsValid = true;
}

void UCryptoClient::SuiAuthorization(FString AccountID)
{
	counter = 0;
	data.accountID = AccountID;
	UKismetSystemLibrary::LaunchURL(FString("https://promo.battlemon.com/game?client_id=") + data.accountID);

	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(AuthTimer, this, &UCryptoClient::TimerAuth, 1.0f, true, 5.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Set timer World not exist!"));
}

void UCryptoClient::GuestAuthorization()
{
	AuthService->GuestAuth(TMap<FString, FString>(), FUGuestAuthRequest(), data.session.session);
}

void UCryptoClient::TimerAuth()
{
	if (!data.session.session.jwt.IsEmpty())
	{
		ClearTimer();
		UE_LOG(LogTemp, Error, TEXT("success SuiAuth()!"));
		return;
	}
	if (counter > 30)
	{
		ClearTimer();
		UE_LOG(LogTemp, Error, TEXT("time is up SuiAuth(). call GuestAuthorization()!"));
		GuestAuthorization();
		return;
	}
	counter++;

	FUSuiAuthRequest inp;
	inp.client_id = data.accountID;
	AuthService->SuiAuth(TMap<FString, FString>(), inp, data.session);
}

UWorld* UCryptoClient::GetWorld() const
{
	if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
}

void UCryptoClient::ClearTimer()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Clear timer World not exist!"));
}
