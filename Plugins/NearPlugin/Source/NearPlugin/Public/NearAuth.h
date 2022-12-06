// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include <Key/Client.h>

#include "gRPC_Auth.h"
#include "Engine/World.h"
#include "Http.h"
#include "Engine/EngineTypes.h"

#include "UObject/NoExportTypes.h"
#include "NearAuth.generated.h"

#if PLATFORM_WINDOWS
#define WEBTYPE_M L"mainnet"
#define WEBTYPE_T L"testnet"
#define RPC_RUST L"testnet"
#else
#define WEBTYPE_M u"mainnet"
#define WEBTYPE_T u"testnet"
#define RPC_RUST "https://rpc.testnet.near.org"
#endif

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResultNearAuth_Delegate, const FString&, Result);

/**
 * 
 */
UCLASS(Blueprintable)
class NEARPLUGIN_API UNearAuth : public UObject
{
	GENERATED_BODY()
	virtual UWorld* GetWorld() const override;
	
	TypeClient typeClient;
	static void freeClient();
	void saveAccountId();
	
	
	void OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnResponseReceived();
	bool CheckAccountKey(FString AccountName);
	FTimerHandle NearAuthTimer;
	void TimerAuth();
	void ClearTimer();
	void SetAccount(game::battlemon::auth::VerifyCodeResponse& _accountID, FString& signatureMessage);
	game::battlemon::auth::VerifyCodeResponse CVerifyCode(gRPC_ClientAuth& grpcClient);
	FString CSignMessage(gRPC_ClientAuth& grpcClient);
	static FString accountID;

public:
	static Client* client;

	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;

	FString URLContract;
	FString URL_Redirect;

	UNearAuth();
	~UNearAuth();
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Client")
	FString getAccountID();
	
	UPROPERTY(BlueprintAssignable, Category = ".Near | Registration")
	FResultNearAuth_Delegate ResultNearRegist_Delegate;
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Registration")
	void RegistrationAccount(FString URL_Success, FString URL_Contract, bool MainNet = false);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void AuthorizedAccount(FString AccountID);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool ClientIsValid();
	
};
