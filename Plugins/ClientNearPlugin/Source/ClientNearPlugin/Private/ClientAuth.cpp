// Fill out your copyright notice in the Description page of Project Settings.

#include "ClientAuth.h"
#include <Kismet/GameplayStatics.h>
#include "ClientNearPlugin.h"
#include "TimerManager.h"
#include "Misc/Paths.h"
#include "NearAuthSaveGame.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "AsyncTask.h"
#if PLATFORM_UNIX
#include "Unix/UnixPlatformMisc.h"
#endif

Client* UClientNear::client = nullptr;
FString UClientNear::accountID = "";
gRPC_ClientAuth* UClientNear::grpcClient = nullptr;

UClientNear::UClientNear() :AsyncAuthTask(nullptr), BadKey(true)
{
}

UClientNear::~UClientNear()
{
}
FString UClientNear::getAccountID()
{
	return FString(client->GetAccount());
}

void UClientNear::RegistrationAccount(FString URL_Success, FString URL_Contract, bool MainNet)
{
	URLContract = URL_Contract;
	URL_Redirect = URL_Success;
	webT = MainNet;
	freeClient();
	typeClient = TypeClient::NEW;
	client = new Client(nullptr, nullptr, typeClient);
	OnResponseReceived();
}

void UClientNear::AuthorizedAccount(FString AccountID, FString URL_Success, FString URL_Contract, bool MainNet)
{
	URLContract = URL_Contract;
	URL_Redirect = URL_Success;
	webT = MainNet;
	freeClient();
	FString Paths = FPaths::ProjectSavedDir();
	typeClient = TypeClient::OLD;
	client = new Client(*Paths, *AccountID, typeClient);
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(NearAuthTimer, this, &UClientNear::TimerAuth, 1.0f, true, 1.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Set timer World not exist!"));
}

void UClientNear::loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid)
{
	bIsValid = false;
	if (!UGameplayStatics::DoesSaveGameExist("UClientNear", 0))
		return;
	const UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("UClientNear", 0));
	AccountsIds = SaveGameInstance->AccountsIds;
	if (AccountsIds.Num() < 0)
		return;
	bIsValid = true;
}

bool UClientNear::ClientIsValid()
{
	return client->IsValidAccount();
}

UWorld* UClientNear::GetWorld() const
{
	if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
}

void UClientNear::freeClient()
{
	
	if (client != nullptr)
		delete client;
	client = nullptr;
}

void UClientNear::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountsIds.Insert(FString(client->GetAccount()), 0);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "UNearAuth", 0);
}

void UClientNear::OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	FString fullURL = FString("https://wallet.") + FString(webT ? WEBTYPE_M : WEBTYPE_T) + ".near.org/login?title=rndname";
	if (!URLContract.IsEmpty())
	{
		TSharedPtr<FJsonObject> ResponseObj;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
		FJsonSerializer::Deserialize(Reader, ResponseObj);
		if(ResponseObj->HasField("nft_contract_id"))
			fullURL += "&contract_id=" + ResponseObj->GetStringField("nft_contract_id");
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ResponseObj nft_contract_id filed!"));
			return;
		}
	}
	if (!URL_Redirect.IsEmpty())
	{
		fullURL += "&success_url=" + URL_Redirect;
	}
	UKismetSystemLibrary::LaunchURL(fullURL + "&public_key=" + FString(client->GetPublicKey()));
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(NearAuthTimer, this, &UClientNear::TimerAuth, 1.0f, true, 1.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Set timer World not exist!"));
}

void UClientNear::OnResponseReceived()
{
	BadKey = false;
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UClientNear::OnGetRequest);
	Request->SetURL(URLContract);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

void UClientNear::SetAccount(game::battlemon::auth::VerifyCodeResponse& _accountID)
{
	BadKey = false;
	this->accountID = CONV_CHAR_TO_FSTRING(_accountID.near_account_id().c_str());
	client->SetAccount(*(this->accountID));

}

void UClientNear::CVerifyCode(game::battlemon::auth::VerifyCodeRequest& Request, game::battlemon::auth::VerifyCodeResponse& VerifyCodeResponse, game::battlemon::auth::SendCodeResponse& CodeResponse)
{
	FString pubKey = client->GetPublicKey();
	Request.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
	Request.set_sign(client->CreateMessageNewSign(CodeResponse.code().c_str()));
	VerifyCodeResponse = grpcClient->CallRPCVerifyCode(&Request);
}

void UClientNear::CSignMessage(game::battlemon::auth::SendCodeResponse& CodeResponse)
{
	game::battlemon::auth::SendCodeRequest Request;
	FString pubKey = client->GetPublicKey();
	Request.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
	CodeResponse = grpcClient->CallRPCSendCode(&Request);
}

void UClientNear::BadKeyCreateNew()
{
	typeClient = TypeClient::NEW;
	freeClient();
	client = new Client(nullptr, nullptr, typeClient);
	OnResponseReceived();
}

void UClientNear::TimerAuth()
{
	if (!client->IsValidAccount())
	{
		if (AsyncAuthTask == nullptr)
		{
			grpcClient = new gRPC_ClientAuth(true, URL);
			AsyncAuthTask = new FAsyncTask<FMAsyncAuthTask>();
			AsyncAuthTask->GetTask().SetData(this, &structResultDelegate);
			AsyncAuthTask->StartBackgroundTask();
		}
		else if (AsyncAuthTask->IsDone())
		{
			AsyncAuthTask->StartBackgroundTask();
		}
	}
	else
	{
		if (AsyncAuthTask && !AsyncAuthTask->Cancel())
		{
			AsyncAuthTask->EnsureCompletion();
		}
		delete grpcClient;
		grpcClient = nullptr;
		delete AsyncAuthTask;
		AsyncAuthTask = nullptr;
		ClearTimer();
	}
}

void UClientNear::TryAuth()
{
	if (client->GetError() != nullptr && typeClient == TypeClient::OLD)
	{
		BadKeyCreateNew();
		return;
	}
	else
	{
		game::battlemon::auth::VerifyCodeRequest VerifyCodeRequest;
		game::battlemon::auth::SendCodeResponse CodeResponse;
		game::battlemon::auth::VerifyCodeResponse _accountID;
		const char* sign = client->GetSing();
		bool save = true;
		if (*sign != '\0')
		{
			//CSignMessage(CodeResponse);

			{
				game::battlemon::auth::SendCodeRequest Request;
				FString pubKey = client->GetPublicKey();
				Request.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
				CodeResponse = grpcClient->CallRPCSendCode(&Request);
			}


			save = false;
		}
		//CVerifyCode(VerifyCodeRequest, _accountID, CodeResponse);

		{
			FString pubKey = client->GetPublicKey();
			VerifyCodeRequest.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
			VerifyCodeRequest.set_sign(client->CreateMessageNewSign(CodeResponse.code().c_str()));
			_accountID = grpcClient->CallRPCVerifyCode(&VerifyCodeRequest);
		}

		if (_accountID.near_account_id() == "")
		{
			save = false;
			_accountID.Clear();
			VerifyCodeRequest.Clear();
			//CSignMessage(CodeResponse);
			{
				game::battlemon::auth::SendCodeRequest Request;
				FString pubKey = client->GetPublicKey();
				Request.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
				CodeResponse = grpcClient->CallRPCSendCode(&Request);
			}

			//CVerifyCode(VerifyCodeRequest, _accountID, CodeResponse);
			{
				FString pubKey = client->GetPublicKey();
				VerifyCodeRequest.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
				VerifyCodeRequest.set_sign(client->CreateMessageNewSign(CodeResponse.code().c_str()));
				_accountID = grpcClient->CallRPCVerifyCode(&VerifyCodeRequest);
			}


			if (_accountID.near_account_id() != "")
			{
				SetAccount(_accountID);
			}
		}
		else
		{
			SetAccount(_accountID);
		}
		if (ResultNearRegist_Delegate.IsBound() && client->IsValidAccount())
		{
			if (!save)
			{
				client->SaveSign(*FPaths::ProjectSavedDir(), client->GetSing());
				client->SaveKey(*FPaths::ProjectSavedDir());
				saveAccountId();
			}
			ResultNearRegist_Delegate.Broadcast(this->accountID);
		}
		else
		{
			if (BadKey)
			{
				BadKeyCreateNew();
			}

		}
	}
#if UE_BUILD_DEBUG
#endif
}

void UClientNear::ClearTimer()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Clear timer World not exist!"));
}