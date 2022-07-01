// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "NearAuth.generated.h"
/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogNearAuth, Log, All);

UCLASS()
class NEARPLUGIN_API UNearAuth : public UObject
{
	GENERATED_BODY()

	static void freeClient();
	static void saveAccountId();
public:
	

	UNearAuth();
	~UNearAuth();

	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static bool RegistrationAccount(FString networkType, FString& AccountId);
	
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static bool AuthorizedAccount(FString AccountId);
	
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static bool ClientIsValid();
	
	UFUNCTION(BlueprintCallable, Category = ".NearAuth")
	static FString VerifySing();
	
	UFUNCTION(BlueprintCallable, Category = ".NearAuthDebug")
	static FString CheckDLL();
	
	UFUNCTION(BlueprintCallable, Category = ".NearAuthDebug")
	static FString GetError();
};
