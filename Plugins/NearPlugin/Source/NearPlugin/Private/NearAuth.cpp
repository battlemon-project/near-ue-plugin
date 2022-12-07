// Fill out your copyright notice in the Description page of Project Settings.


#include "NearAuth.h"
#include <Kismet/GameplayStatics.h>
#include "NearPlugin.h"
#include "TimerManager.h"
#include "Misc/Paths.h"
#include "NearAuthSaveGame.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

#if PLATFORM_UNIX
#include "Unix/UnixPlatformMisc.h"
#endif

Client* UNearAuth::client = nullptr;
FString UNearAuth::accountID = "";

UNearAuth::UNearAuth()
{
}

UNearAuth::~UNearAuth()
{
}

FString UNearAuth::getAccountID()
{
	return FString(client->GetAccount());
}

void UNearAuth::RegistrationAccount(FString URL_Success, FString URL_Contract, bool MainNet)
{
	URLContract = URL_Contract;
	URL_Redirect = URL_Success;
	freeClient();
	typeClient = TypeClient::NEW;
	client = new Client(nullptr, nullptr, typeClient);

	OnResponseReceived();
}

void UNearAuth::AuthorizedAccount(FString AccountID)
{
	freeClient();
	FString Paths = FPaths::ProjectSavedDir();
	typeClient = TypeClient::OLD;
	client = new Client(*Paths, *AccountID, typeClient);
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(NearAuthTimer, this, &UNearAuth::TimerAuth, 1.0f, true, 1.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Set timer World not exist!"));
}

void UNearAuth::loadAccountId(TArray<FString>& AccountsIds, bool& bIsValid)
{
	bIsValid = false;
	if (!UGameplayStatics::DoesSaveGameExist("UNearAuth", 0))
		return;

	const UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::LoadGameFromSlot("UNearAuth", 0));
	AccountsIds = SaveGameInstance->AccountsIds;

	if (AccountsIds.Num() < 0)
		return;

	bIsValid = true;
}

bool UNearAuth::ClientIsValid()
{
	return client->IsValidAccount();
}

UWorld* UNearAuth::GetWorld() const
{
	if (GetOuter()) return GetOuter()->GetWorld();
	else return nullptr;
}

void UNearAuth::freeClient()
{
	if (client != nullptr)
		delete client;
	client = nullptr;
}

void UNearAuth::saveAccountId()
{
	UNearAuthSaveGame* SaveGameInstance = Cast<UNearAuthSaveGame>(UGameplayStatics::CreateSaveGameObject(UNearAuthSaveGame::StaticClass()));
	SaveGameInstance->AccountsIds.Insert(FString(client->GetAccount()), 0);
	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "UNearAuth", 0);
}

void UNearAuth::OnGetRequest(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	FString fullURL = FString("https://wallet.") + FString(WEBTYPE_T) + ".near.org/login?title=rndname";
	if (!URLContract.IsEmpty())
	{
		TSharedPtr<FJsonObject> ResponseObj;
		TSharedRef<TJsonReader<TCHAR>> Reader = TJsonReaderFactory<TCHAR>::Create(Response->GetContentAsString());
		FJsonSerializer::Deserialize(Reader, ResponseObj);
		fullURL += "&contract_id=" + ResponseObj->GetStringField("nft_contract_id");
	}
	if (!URL_Redirect.IsEmpty())
	{
		fullURL += "&success_url=" + URL_Redirect;
	}
	UKismetSystemLibrary::LaunchURL(fullURL + "&public_key=" + FString(client->GetPublicKey()));

	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().SetTimer(NearAuthTimer, this, &UNearAuth::TimerAuth, 1.0f, true, 1.0f);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Set timer World not exist!"));
}

void UNearAuth::OnResponseReceived()
{
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UNearAuth::OnGetRequest);
	Request->SetURL(URLContract);
	Request->SetVerb("GET");
	Request->ProcessRequest();
}

bool UNearAuth::CheckAccountKey(FString AccountName)
{
	size_t res = 0;

	//res = FNearPluginModule::_AuthorizedRust(client->GetPublicKey(), client->GetAccount(), RPC_RUST);
	return false; //res == 10;
}
void UNearAuth::SetAccount(game::battlemon::auth::VerifyCodeResponse& _accountID)
{
	this->accountID = CONV_CHAR_TO_FSTRING(_accountID.near_account_id().c_str());
	client->SetAccount(*(this->accountID));
	
}

game::battlemon::auth::VerifyCodeResponse UNearAuth::CVerifyCode(gRPC_ClientAuth& grpcClient, const char* sign)
{
	game::battlemon::auth::VerifyCodeRequest VerifyCodeRequest;
	FString pubKey = client->GetPublicKey();
	VerifyCodeRequest.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
	VerifyCodeRequest.set_sign(sign);
	return grpcClient.CallRPCVerifyCode(VerifyCodeRequest);
}

const char* UNearAuth::CSignMessage(gRPC_ClientAuth& grpcClient)
{
	game::battlemon::auth::SendCodeResponse CodeResponse;
	game::battlemon::auth::SendCodeRequest Request;
	FString pubKey = client->GetPublicKey();
	Request.set_public_key(CONV_FSTRING_TO_CHAR(pubKey));
	CodeResponse = grpcClient.CallRPCSendCode(Request);
	return client->CreateMessageNewSign(CodeResponse.code().c_str());
}

void UNearAuth::TimerAuth()
{

	if (FString(client->GetError()) == FString("public key not found") && typeClient == TypeClient::OLD)
	{
		ClearTimer();
		typeClient = TypeClient::NEW;
		freeClient();
		FString Paths = FPaths::ProjectSavedDir();
		client = new Client(nullptr, nullptr, typeClient);
		OnResponseReceived();
		return;
	}
	else
	{
		gRPC_ClientAuth grpcClient(true, URL);
		game::battlemon::auth::VerifyCodeRequest VerifyCodeRequest;
		game::battlemon::auth::VerifyCodeResponse _accountID;

		const char* sign = client->GetSing();
		bool save = true;
		if (*sign != '\0')
		{
			sign = CSignMessage(grpcClient);
			save = false;
		}

		_accountID = CVerifyCode(grpcClient, sign);

		if (_accountID.near_account_id() == "")
		{
			save = false;
			_accountID.Clear();
			VerifyCodeRequest.Clear();

			sign = CSignMessage(grpcClient);
			_accountID = CVerifyCode(grpcClient, sign);

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
			if (!save && !accountID.IsEmpty())
			{
				client->SaveSign(*FPaths::ProjectSavedDir(), sign);
				client->SaveKey(*FPaths::ProjectSavedDir());
				ClearTimer();

				saveAccountId();
			}

			ResultNearRegist_Delegate.Broadcast(this->accountID);
		}
	}
}

void UNearAuth::ClearTimer()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearAllTimersForObject(this);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Clear timer World not exist!"));
}
