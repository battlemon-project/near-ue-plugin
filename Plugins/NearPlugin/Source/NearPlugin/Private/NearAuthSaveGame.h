// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "NearAuthSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class UNearAuthSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category = ".NearAuth")
	FString AccountId;

	UNearAuthSaveGame();
};
