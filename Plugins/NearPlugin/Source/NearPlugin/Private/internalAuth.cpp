#include"internalAuth.h"
#include "AsyncTask.h"

RPC_InternalAuthService* UInternalAuthService::_RPC_InternalAuthService = nullptr;

RPC_InternalAuthService::RPC_InternalAuthService(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out) {}

RPC_InternalAuthService::~RPC_InternalAuthService() {}

game::battlemon::auth::internal::InternalVerifyJwtResponse RPC_InternalAuthService::InternalVerifyJwt(grpc::ClientContext* context, const game::battlemon::auth::internal::InternalVerifyJwtRequest* request)
{
	game::battlemon::auth::internal::InternalVerifyJwtResponse read;
	CheckError(stub.get()->InternalVerifyJwt(context, *request, &read));

	if (static_cast<FInternalVerifyJwtDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUInternalVerifyJwtResponse*>(out) = read;
		static_cast<FInternalVerifyJwtDelegate*>(Delegate)->Broadcast(*static_cast<FUInternalVerifyJwtResponse*>(out));
	}
	return read;
}

game::battlemon::auth::internal::InternalAccountsInfoResponse RPC_InternalAuthService::InternalGetAccountsInfo(grpc::ClientContext* context, const game::battlemon::auth::internal::InternalAccountsInfoRequest* request)
{
	game::battlemon::auth::internal::InternalAccountsInfoResponse read;
	CheckError(stub.get()->InternalGetAccountsInfo(context, *request, &read));

	if (static_cast<FInternalGetAccountsInfoDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUInternalAccountsInfoResponse*>(out) = read;
		static_cast<FInternalGetAccountsInfoDelegate*>(Delegate)->Broadcast(*static_cast<FUInternalAccountsInfoResponse*>(out));
	}
	return read;
}

void UInternalAuthService::free_RPC_InternalAuthService()
{
	if (_RPC_InternalAuthService != nullptr)
	{
		if (_RPC_InternalAuthService->Task != nullptr)
		{
			switch (rpc)
			{
			case InternalAuthServiceRPC::InternalVerifyJwt:
				if (!CAST_ASINCTASK(FUInternalVerifyJwtResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalVerifyJwtRequest, game::battlemon::auth::internal::InternalVerifyJwtResponse)(_RPC_InternalAuthService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUInternalVerifyJwtResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalVerifyJwtRequest, game::battlemon::auth::internal::InternalVerifyJwtResponse)(_RPC_InternalAuthService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUInternalVerifyJwtResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalVerifyJwtRequest, game::battlemon::auth::internal::InternalVerifyJwtResponse)(_RPC_InternalAuthService->Task);
				break;
			case InternalAuthServiceRPC::InternalGetAccountsInfo:
				if (!CAST_ASINCTASK(FUInternalAccountsInfoResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalAccountsInfoRequest, game::battlemon::auth::internal::InternalAccountsInfoResponse)(_RPC_InternalAuthService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUInternalAccountsInfoResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalAccountsInfoRequest, game::battlemon::auth::internal::InternalAccountsInfoResponse)(_RPC_InternalAuthService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUInternalAccountsInfoResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalAccountsInfoRequest, game::battlemon::auth::internal::InternalAccountsInfoResponse)(_RPC_InternalAuthService->Task);
				break;
			}
			_RPC_InternalAuthService->Task = nullptr;
		}
		delete _RPC_InternalAuthService;
	}
	_RPC_InternalAuthService = nullptr;
}

UInternalAuthService::UInternalAuthService() {}

UInternalAuthService::~UInternalAuthService() 
{
	free_RPC_InternalAuthService();
}

void UInternalAuthService::InternalVerifyJwt(TMap<FString, FString> context, FUInternalVerifyJwtRequest inp, FUInternalVerifyJwtResponse &out)
{
	free_RPC_InternalAuthService();
	rpc = InternalAuthServiceRPC::InternalVerifyJwt;
	game::battlemon::auth::internal::InternalVerifyJwtRequest g_request;
	g_request << inp;
	_RPC_InternalAuthService = new RPC_InternalAuthService(ssl, URL, &InternalVerifyJwtDelegate, &out);
	CREATE_ASINCTASK(FUInternalVerifyJwtResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalVerifyJwtRequest, game::battlemon::auth::internal::InternalVerifyJwtResponse);
	_RPC_InternalAuthService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalAuthService, &out, &g_request, context, &RPC_InternalAuthService::InternalVerifyJwt);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalAuthService::InternalGetAccountsInfo(TMap<FString, FString> context, FUInternalAccountsInfoRequest inp, FUInternalAccountsInfoResponse &out)
{
	free_RPC_InternalAuthService();
	rpc = InternalAuthServiceRPC::InternalGetAccountsInfo;
	game::battlemon::auth::internal::InternalAccountsInfoRequest g_request;
	g_request << inp;
	_RPC_InternalAuthService = new RPC_InternalAuthService(ssl, URL, &InternalGetAccountsInfoDelegate, &out);
	CREATE_ASINCTASK(FUInternalAccountsInfoResponse, RPC_InternalAuthService, game::battlemon::auth::internal::InternalAccountsInfoRequest, game::battlemon::auth::internal::InternalAccountsInfoResponse);
	_RPC_InternalAuthService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalAuthService, &out, &g_request, context, &RPC_InternalAuthService::InternalGetAccountsInfo);
	GET_ASINCTASK->StartBackgroundTask();
}

FString UInternalAuthService::GetError()
{
	if (_RPC_InternalAuthService != nullptr)
		return _RPC_InternalAuthService->GetError();
	return FString();
}


FUInternalVerifyJwtStatus& operator<<(FUInternalVerifyJwtStatus &UE, const game::battlemon::auth::internal::InternalVerifyJwtStatus& grpc)
{
	UE = FUInternalVerifyJwtStatus::Default;
	switch (grpc)
	{
	case game::battlemon::auth::internal::InternalVerifyJwtStatus::OK:
		UE = FUInternalVerifyJwtStatus::OK;
		break;
	case game::battlemon::auth::internal::InternalVerifyJwtStatus::EXPIRED:
		UE = FUInternalVerifyJwtStatus::EXPIRED;
		break;
	case game::battlemon::auth::internal::InternalVerifyJwtStatus::INVALID:
		UE = FUInternalVerifyJwtStatus::INVALID;
		break;
	}
	return UE;
}


FUInteranalAccountType& operator<<(FUInteranalAccountType &UE, const game::battlemon::auth::internal::InteranalAccountType& grpc)
{
	UE = FUInteranalAccountType::Default;
	switch (grpc)
	{
	case game::battlemon::auth::internal::InteranalAccountType::GUEST:
		UE = FUInteranalAccountType::GUEST;
		break;
	case game::battlemon::auth::internal::InteranalAccountType::SUI:
		UE = FUInteranalAccountType::SUI;
		break;
	}
	return UE;
}


game::battlemon::auth::internal::InternalVerifyJwtStatus& operator<<(game::battlemon::auth::internal::InternalVerifyJwtStatus & grpc, const FUInternalVerifyJwtStatus &UE) 
{
	switch (UE)
	{
	case FUInternalVerifyJwtStatus::OK:
		grpc = game::battlemon::auth::internal::InternalVerifyJwtStatus::OK;
		break;
	case FUInternalVerifyJwtStatus::EXPIRED:
		grpc = game::battlemon::auth::internal::InternalVerifyJwtStatus::EXPIRED;
		break;
	case FUInternalVerifyJwtStatus::INVALID:
		grpc = game::battlemon::auth::internal::InternalVerifyJwtStatus::INVALID;
		break;
	}
	return grpc;
}


game::battlemon::auth::internal::InteranalAccountType& operator<<(game::battlemon::auth::internal::InteranalAccountType & grpc, const FUInteranalAccountType &UE) 
{
	switch (UE)
	{
	case FUInteranalAccountType::GUEST:
		grpc = game::battlemon::auth::internal::InteranalAccountType::GUEST;
		break;
	case FUInteranalAccountType::SUI:
		grpc = game::battlemon::auth::internal::InteranalAccountType::SUI;
		break;
	}
	return grpc;
}


FUInternalAccountInfo& FUInternalAccountInfo::operator=(const game::battlemon::auth::internal::InternalAccountInfo& grpcInternalAccountInfo)
{
	id = CONV_CHAR_TO_FSTRING(grpcInternalAccountInfo.id().c_str());
	type << grpcInternalAccountInfo.type();
	return *this;
}


FUInternalAccountsInfoResponse& FUInternalAccountsInfoResponse::operator=(const game::battlemon::auth::internal::InternalAccountsInfoResponse& grpcInternalAccountsInfoResponse)
{
{
	int size = grpcInternalAccountsInfoResponse.accounts().size();
	accounts.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		accounts[Idx] = grpcInternalAccountsInfoResponse.accounts(Idx);
		});

	}
	return *this;
}


FUInternalAccountsInfoRequest& FUInternalAccountsInfoRequest::operator=(const game::battlemon::auth::internal::InternalAccountsInfoRequest& grpcInternalAccountsInfoRequest)
{
{
	int size = grpcInternalAccountsInfoRequest.user_ids().size();
	user_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		user_ids[Idx] = CONV_CHAR_TO_FSTRING(grpcInternalAccountsInfoRequest.user_ids(Idx).c_str());
		});

	}
	return *this;
}


FUInternalVerifyJwtResponse& FUInternalVerifyJwtResponse::operator=(const game::battlemon::auth::internal::InternalVerifyJwtResponse& grpcInternalVerifyJwtResponse)
{
	status << grpcInternalVerifyJwtResponse.status();
	account = grpcInternalVerifyJwtResponse.account();
	return *this;
}


FUInternalVerifyJwtRequest& FUInternalVerifyJwtRequest::operator=(const game::battlemon::auth::internal::InternalVerifyJwtRequest& grpcInternalVerifyJwtRequest)
{
	jwt = CONV_CHAR_TO_FSTRING(grpcInternalVerifyJwtRequest.jwt().c_str());
	return *this;
}



game::battlemon::auth::internal::InternalAccountInfo &operator<<(game::battlemon::auth::internal::InternalAccountInfo &grpcInternalAccountInfo, const FUInternalAccountInfo &UE)
{
	{
		grpcInternalAccountInfo.set_id(CONV_FSTRING_TO_CHAR(UE.id));
	}
	{
		game::battlemon::auth::internal::InteranalAccountType go;
		go << UE.type;
		grpcInternalAccountInfo.set_type(go);
	}
	return grpcInternalAccountInfo;
}


game::battlemon::auth::internal::InternalAccountsInfoResponse &operator<<(game::battlemon::auth::internal::InternalAccountsInfoResponse &grpcInternalAccountsInfoResponse, const FUInternalAccountsInfoResponse &UE)
{
		int size = UE.accounts.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::auth::internal::InternalAccountInfo* ptr = grpcInternalAccountsInfoResponse.add_accounts();
		*ptr <<UE.accounts[Idx];
	}
	return grpcInternalAccountsInfoResponse;
}


game::battlemon::auth::internal::InternalAccountsInfoRequest &operator<<(game::battlemon::auth::internal::InternalAccountsInfoRequest &grpcInternalAccountsInfoRequest, const FUInternalAccountsInfoRequest &UE)
{
		int size = UE.user_ids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		std::string* ptr =grpcInternalAccountsInfoRequest.add_user_ids();
		*ptr =CONV_FSTRING_TO_CHAR(UE.user_ids[Idx]);
	}
	return grpcInternalAccountsInfoRequest;
}


game::battlemon::auth::internal::InternalVerifyJwtResponse &operator<<(game::battlemon::auth::internal::InternalVerifyJwtResponse &grpcInternalVerifyJwtResponse, const FUInternalVerifyJwtResponse &UE)
{
	{
		game::battlemon::auth::internal::InternalVerifyJwtStatus go;
		go << UE.status;
		grpcInternalVerifyJwtResponse.set_status(go);
	}
	{
		game::battlemon::auth::internal::InternalAccountInfo* account = new game::battlemon::auth::internal::InternalAccountInfo();
		*account << UE.account;
		grpcInternalVerifyJwtResponse.set_allocated_account(account);
	}
	return grpcInternalVerifyJwtResponse;
}


game::battlemon::auth::internal::InternalVerifyJwtRequest &operator<<(game::battlemon::auth::internal::InternalVerifyJwtRequest &grpcInternalVerifyJwtRequest, const FUInternalVerifyJwtRequest &UE)
{
	{
		grpcInternalVerifyJwtRequest.set_jwt(CONV_FSTRING_TO_CHAR(UE.jwt));
	}
	return grpcInternalVerifyJwtRequest;
}

