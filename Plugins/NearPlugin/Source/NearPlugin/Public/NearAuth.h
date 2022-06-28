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
public:

	static Client* client;

	UNearAuth();
	~UNearAuth();

	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static bool RegistrationAccount(FString networkType, FString& AccountId);
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static bool AuthorizedAccount(FString AccountId);
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static void saveAccountId();
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static void loadAccountId(FString& AccountId, bool& bIsValid);
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static bool ClientIsValid();
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static int VerifySing();

	UFUNCTION(BlueprintCallable, Category = ".NearAuthDebug")
	static void CheckDLL();
	UFUNCTION(BlueprintCallable, Category = ".NearAuthDebug")
	static FString GetError();
};
