// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

//#include "GrpcBegin.h"
#include"auth.h"
//#include "GrpcEnd.h"

#include "Http.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"


#include "UObject/NoExportTypes.h"
#include "CryptoClient.generated.h"

struct DataClient
{
	FUSuiSession session;
	FString accountID;
};

/**
 * 
 */
UCLASS(Blueprintable)
class NEARPLUGIN_API UCryptoClient : public UObject
{
	GENERATED_BODY()
		
	static DataClient data;
	virtual UWorld* GetWorld() const override;
	void TimerAuth();
	void ClearTimer();

	int counter;
	FTimerHandle AuthTimer;
	//void SaveData();

public:
	UCryptoClient();
	~UCryptoClient();

	UPROPERTY(BlueprintReadWrite, Category = ".Crypto | Client", meta = (ExposeOnSpawn = true))
	UAuthService* AuthService;
	
	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//void LoadData(FString AccountsId);
	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	void saveAccountId();

	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//static FString GetPublicKey_Base58();
	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//static FString GetSing();
	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	static FString GetWalletAddress();
	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	static FUSuiSession GetSuiSession();

	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//void SetSing(FString _sing);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	bool IsValidAccount();
	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//bool IsValidKeys();


	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//void CreateNewKey();
	//UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	//FString SignAMessage(FString Message);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	void SuiAuthorization(FString AccountID);

	UFUNCTION(BlueprintCallable, Category = ".Crypto | Client")
	void GuestAuthorization();
};
