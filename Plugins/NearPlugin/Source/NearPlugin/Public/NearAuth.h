#pragma once
#include "CoreMinimal.h"
#include <Key/Client.h>
#include "gRPC_Auth.h"
#include "Engine/World.h"
#include "Http.h"
#include "Engine/EngineTypes.h"

#include "UObject/NoExportTypes.h"
#include "Async/AsyncWork.h"
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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStructResultDelegate);

class FMAsyncAuthTask;

UCLASS(Blueprintable)
class NEARPLUGIN_API UNearAuth : public UObject
{
	GENERATED_BODY()
	virtual UWorld* GetWorld() const override;
	static gRPC_ClientAuth* grpcClient;
	FAsyncTask<FMAsyncAuthTask>* AsyncAuthTask;
	TypeClient typeClient;
	static void freeClient();
	void saveAccountId();
	
	void OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);
	void OnResponseReceived();
	bool CheckAccountKey(FString AccountName);
	FTimerHandle NearAuthTimer;
	void TimerAuth();
	void ClearTimer();
	void SetAccount(game::battlemon::auth::VerifyCodeResponse& _accountID);
	void CVerifyCode(game::battlemon::auth::VerifyCodeRequest& Request, game::battlemon::auth::VerifyCodeResponse& VerifyCodeResponse, game::battlemon::auth::SendCodeResponse& CodeResponse);
	void CSignMessage(game::battlemon::auth::SendCodeResponse& CodeResponse);
	void BadKeyCreateNew();
    bool BadKey;
    bool webT;
	static FString accountID;
public:

	void TryAuth();
	static Client* client;
	UPROPERTY(BlueprintReadWrite, Category = ".Near| Client", meta = (ExposeOnSpawn = true))
	FString URL;
	
	UPROPERTY(BlueprintAssignable, Category = ".Near | MMProto")
	FStructResultDelegate structResultDelegate;

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
    void AuthorizedAccount(FString AccountID, FString URL_Success, FString URL_Contract, bool MainNet = false);

	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	void loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid);
	
	UFUNCTION(BlueprintCallable, Category = ".Near | Auth")
	bool ClientIsValid();
	
};

class FMAsyncAuthTask :public FNonAbandonableTask
{
	friend class FAsyncTask<FMAsyncAuthTask>;

	UNearAuth* service;
	FStructResultDelegate* structResultDelegate;

public:
    FMAsyncAuthTask() :service(nullptr), structResultDelegate(nullptr) {};
    ~FMAsyncAuthTask()
    {
		service = nullptr; structResultDelegate = nullptr;
    };

	void SetData(UNearAuth* _service, FStructResultDelegate* _structResultDelegate)
	{
		service = _service;
		structResultDelegate = _structResultDelegate;
	};

protected:
    void DoWork()
    {
        if (service != nullptr)
        {
			service->TryAuth();
            if (structResultDelegate->IsBound())
                structResultDelegate->Broadcast();
        }
    }

	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMAsyncAuthTask, STATGROUP_ThreadPoolAsyncTasks);
	}
};