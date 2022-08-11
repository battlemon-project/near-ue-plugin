// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <include/Client.h>
#include "NearAuth.generated.h"
/**
 * 
 */


UCLASS()
class NEARPLUGIN_API UNearAuth : public UObject
{
	GENERATED_BODY()

	static void freeClient();
	static void saveAccountId();

public:
	static Client* client;

	UNearAuth();
	~UNearAuth();


	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static bool RegistrationAccount(FString& AccountId, bool MainNet = false);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static bool AuthorizedAccount(FString AccountId);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	static bool ClientIsValid();
	
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	static FString CheckDLL();
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Debug")
	static FString GetError();
};
