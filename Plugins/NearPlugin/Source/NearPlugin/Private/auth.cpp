#include"auth.h"
#include "AsyncTask.h"

RPC_AuthService* UAuthService::_RPC_AuthService = nullptr;

RPC_AuthService::RPC_AuthService(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out) {}

RPC_AuthService::~RPC_AuthService() {}

game::battlemon::auth::SuiSession RPC_AuthService::SuiAuth(grpc::ClientContext* context, const game::battlemon::auth::SuiAuthRequest* request)
{
	game::battlemon::auth::SuiSession read;
	CheckError(stub.get()->SuiAuth(context, *request, &read));

	if (static_cast<FSuiAuthDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUSuiSession*>(out) = read;
		static_cast<FSuiAuthDelegate*>(Delegate)->Broadcast(*static_cast<FUSuiSession*>(out));
	}
	return read;
}

game::battlemon::auth::Session RPC_AuthService::GuestAuth(grpc::ClientContext* context, const game::battlemon::auth::GuestAuthRequest* request)
{
	game::battlemon::auth::Session read;
	CheckError(stub.get()->GuestAuth(context, *request, &read));

	if (static_cast<FGuestAuthDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUSession*>(out) = read;
		static_cast<FGuestAuthDelegate*>(Delegate)->Broadcast(*static_cast<FUSession*>(out));
	}
	return read;
}

game::battlemon::auth::WalletAddressResponse RPC_AuthService::GetWalletAddress(grpc::ClientContext* context, const game::battlemon::auth::WalletAddressRequest* request)
{
	game::battlemon::auth::WalletAddressResponse read;
	CheckError(stub.get()->GetWalletAddress(context, *request, &read));

	if (static_cast<FGetWalletAddressDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUWalletAddressResponse*>(out) = read;
		static_cast<FGetWalletAddressDelegate*>(Delegate)->Broadcast(*static_cast<FUWalletAddressResponse*>(out));
	}
	return read;
}

void UAuthService::free_RPC_AuthService()
{
	if (_RPC_AuthService != nullptr)
	{
		if (_RPC_AuthService->Task != nullptr)
		{
			switch (rpc)
			{
			case AuthServiceRPC::SuiAuth:
				if (!CAST_ASINCTASK(FUSuiSession, RPC_AuthService, game::battlemon::auth::SuiAuthRequest, game::battlemon::auth::SuiSession)(_RPC_AuthService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUSuiSession, RPC_AuthService, game::battlemon::auth::SuiAuthRequest, game::battlemon::auth::SuiSession)(_RPC_AuthService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUSuiSession, RPC_AuthService, game::battlemon::auth::SuiAuthRequest, game::battlemon::auth::SuiSession)(_RPC_AuthService->Task);
				break;
			case AuthServiceRPC::GuestAuth:
				if (!CAST_ASINCTASK(FUSession, RPC_AuthService, game::battlemon::auth::GuestAuthRequest, game::battlemon::auth::Session)(_RPC_AuthService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUSession, RPC_AuthService, game::battlemon::auth::GuestAuthRequest, game::battlemon::auth::Session)(_RPC_AuthService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUSession, RPC_AuthService, game::battlemon::auth::GuestAuthRequest, game::battlemon::auth::Session)(_RPC_AuthService->Task);
				break;
			case AuthServiceRPC::GetWalletAddress:
				if (!CAST_ASINCTASK(FUWalletAddressResponse, RPC_AuthService, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse)(_RPC_AuthService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUWalletAddressResponse, RPC_AuthService, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse)(_RPC_AuthService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUWalletAddressResponse, RPC_AuthService, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse)(_RPC_AuthService->Task);
				break;
			}
			_RPC_AuthService->Task = nullptr;
		}
		delete _RPC_AuthService;
	}
	_RPC_AuthService = nullptr;
}

UAuthService::UAuthService() {}

UAuthService::~UAuthService() 
{
	free_RPC_AuthService();
}

void UAuthService::SuiAuth(TMap<FString, FString> context, FUSuiAuthRequest inp, FUSuiSession &out)
{
	free_RPC_AuthService();
	rpc = AuthServiceRPC::SuiAuth;
	game::battlemon::auth::SuiAuthRequest g_request;
	g_request << inp;
	_RPC_AuthService = new RPC_AuthService(ssl, URL, &SuiAuthDelegate, &out);
	CREATE_ASINCTASK(FUSuiSession, RPC_AuthService, game::battlemon::auth::SuiAuthRequest, game::battlemon::auth::SuiSession);
	_RPC_AuthService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_AuthService, &out, &g_request, context, &RPC_AuthService::SuiAuth);
	GET_ASINCTASK->StartBackgroundTask();
}

void UAuthService::GuestAuth(TMap<FString, FString> context, FUGuestAuthRequest inp, FUSession &out)
{
	free_RPC_AuthService();
	rpc = AuthServiceRPC::GuestAuth;
	game::battlemon::auth::GuestAuthRequest g_request;
	g_request << inp;
	_RPC_AuthService = new RPC_AuthService(ssl, URL, &GuestAuthDelegate, &out);
	CREATE_ASINCTASK(FUSession, RPC_AuthService, game::battlemon::auth::GuestAuthRequest, game::battlemon::auth::Session);
	_RPC_AuthService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_AuthService, &out, &g_request, context, &RPC_AuthService::GuestAuth);
	GET_ASINCTASK->StartBackgroundTask();
}

void UAuthService::GetWalletAddress(TMap<FString, FString> context, FUWalletAddressRequest inp, FUWalletAddressResponse &out)
{
	free_RPC_AuthService();
	rpc = AuthServiceRPC::GetWalletAddress;
	game::battlemon::auth::WalletAddressRequest g_request;
	g_request << inp;
	_RPC_AuthService = new RPC_AuthService(ssl, URL, &GetWalletAddressDelegate, &out);
	CREATE_ASINCTASK(FUWalletAddressResponse, RPC_AuthService, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse);
	_RPC_AuthService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_AuthService, &out, &g_request, context, &RPC_AuthService::GetWalletAddress);
	GET_ASINCTASK->StartBackgroundTask();
}

FString UAuthService::GetError()
{
	if (_RPC_AuthService != nullptr)
		return _RPC_AuthService->GetError();
	return FString();
}



FUWalletAddressResponse& FUWalletAddressResponse::operator=(const game::battlemon::auth::WalletAddressResponse& grpcWalletAddressResponse)
{
	wallet_address = CONV_CHAR_TO_FSTRING(grpcWalletAddressResponse.wallet_address().c_str());
	return *this;
}


FUWalletAddressRequest& FUWalletAddressRequest::operator=(const game::battlemon::auth::WalletAddressRequest& grpcWalletAddressRequest)
{
	client_id = CONV_CHAR_TO_FSTRING(grpcWalletAddressRequest.client_id().c_str());
	return *this;
}


FUSession& FUSession::operator=(const game::battlemon::auth::Session& grpcSession)
{
	jwt = CONV_CHAR_TO_FSTRING(grpcSession.jwt().c_str());
	return *this;
}


FUSuiSession& FUSuiSession::operator=(const game::battlemon::auth::SuiSession& grpcSuiSession)
{
	session = grpcSuiSession.session();
	wallet_address = CONV_CHAR_TO_FSTRING(grpcSuiSession.wallet_address().c_str());
	return *this;
}


FUGuestAuthRequest& FUGuestAuthRequest::operator=(const game::battlemon::auth::GuestAuthRequest& grpcGuestAuthRequest)
{
	return *this;
}


FUSuiAuthRequest& FUSuiAuthRequest::operator=(const game::battlemon::auth::SuiAuthRequest& grpcSuiAuthRequest)
{
	client_id = CONV_CHAR_TO_FSTRING(grpcSuiAuthRequest.client_id().c_str());
	return *this;
}



game::battlemon::auth::WalletAddressResponse &operator<<(game::battlemon::auth::WalletAddressResponse &grpcWalletAddressResponse, const FUWalletAddressResponse &UE)
{
	{
		grpcWalletAddressResponse.set_wallet_address(CONV_FSTRING_TO_CHAR(UE.wallet_address));
	}
	return grpcWalletAddressResponse;
}


game::battlemon::auth::WalletAddressRequest &operator<<(game::battlemon::auth::WalletAddressRequest &grpcWalletAddressRequest, const FUWalletAddressRequest &UE)
{
	{
		grpcWalletAddressRequest.set_client_id(CONV_FSTRING_TO_CHAR(UE.client_id));
	}
	return grpcWalletAddressRequest;
}


game::battlemon::auth::Session &operator<<(game::battlemon::auth::Session &grpcSession, const FUSession &UE)
{
	{
		grpcSession.set_jwt(CONV_FSTRING_TO_CHAR(UE.jwt));
	}
	return grpcSession;
}


game::battlemon::auth::SuiSession &operator<<(game::battlemon::auth::SuiSession &grpcSuiSession, const FUSuiSession &UE)
{
	{
		game::battlemon::auth::Session* go = new game::battlemon::auth::Session();
		*go << UE.session;
		grpcSuiSession.set_allocated_session(go);
	}
	{
		grpcSuiSession.set_wallet_address(CONV_FSTRING_TO_CHAR(UE.wallet_address));
	}
	return grpcSuiSession;
}


game::battlemon::auth::GuestAuthRequest &operator<<(game::battlemon::auth::GuestAuthRequest &grpcGuestAuthRequest, const FUGuestAuthRequest &UE)
{
	return grpcGuestAuthRequest;
}


game::battlemon::auth::SuiAuthRequest &operator<<(game::battlemon::auth::SuiAuthRequest &grpcSuiAuthRequest, const FUSuiAuthRequest &UE)
{
	{
		grpcSuiAuthRequest.set_client_id(CONV_FSTRING_TO_CHAR(UE.client_id));
	}
	return grpcSuiAuthRequest;
}

