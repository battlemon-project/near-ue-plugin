#include"mm.h"
#include "AsyncTask.h"

RPC_MMService* UMMService::_RPC_MMService = nullptr;

RPC_MMService::RPC_MMService(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out) {}

RPC_MMService::~RPC_MMService() {}

game::battlemon::mm::SearchGameResponse RPC_MMService::SearchGame(grpc::ClientContext* context, const game::battlemon::mm::SearchGameRequest* request)
{
	game::battlemon::mm::SearchGameResponse read;
	CheckError(stub.get()->SearchGame(context, *request, &read));

	if (static_cast<FSearchGameDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUSearchGameResponse*>(out) = read;
		static_cast<FSearchGameDelegate*>(Delegate)->Broadcast(*static_cast<FUSearchGameResponse*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_MMService::AcceptGame(grpc::ClientContext* context, const game::battlemon::mm::AcceptGameRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->AcceptGame(context, *request, &read));

	if (static_cast<FAcceptGameDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FAcceptGameDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_MMService::CancelSearch(grpc::ClientContext* context, const game::battlemon::mm::CancelSearchRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->CancelSearch(context, *request, &read));

	if (static_cast<FCancelSearchDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FCancelSearchDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

void UMMService::free_RPC_MMService()
{
	if (_RPC_MMService != nullptr)
	{
		if (_RPC_MMService->Task != nullptr)
		{
			switch (rpc)
			{
			case MMServiceRPC::SearchGame:
				if (!CAST_ASINCTASK(FUSearchGameResponse, RPC_MMService, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse)(_RPC_MMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUSearchGameResponse, RPC_MMService, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse)(_RPC_MMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUSearchGameResponse, RPC_MMService, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse)(_RPC_MMService->Task);
				break;
			case MMServiceRPC::AcceptGame:
				if (!CAST_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::AcceptGameRequest, game::battlemon::common::Empty)(_RPC_MMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::AcceptGameRequest, game::battlemon::common::Empty)(_RPC_MMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::AcceptGameRequest, game::battlemon::common::Empty)(_RPC_MMService->Task);
				break;
			case MMServiceRPC::CancelSearch:
				if (!CAST_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::CancelSearchRequest, game::battlemon::common::Empty)(_RPC_MMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::CancelSearchRequest, game::battlemon::common::Empty)(_RPC_MMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::CancelSearchRequest, game::battlemon::common::Empty)(_RPC_MMService->Task);
				break;
			}
			_RPC_MMService->Task = nullptr;
		}
		delete _RPC_MMService;
	}
	_RPC_MMService = nullptr;
}

UMMService::UMMService() {}

UMMService::~UMMService() 
{
	free_RPC_MMService();
}

void UMMService::SearchGame(TMap<FString, FString> context, FUSearchGameRequest inp, FUSearchGameResponse &out)
{
	free_RPC_MMService();
	rpc = MMServiceRPC::SearchGame;
	game::battlemon::mm::SearchGameRequest g_request;
	g_request << inp;
	_RPC_MMService = new RPC_MMService(ssl, URL, &SearchGameDelegate, &out);
	CREATE_ASINCTASK(FUSearchGameResponse, RPC_MMService, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse);
	_RPC_MMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_MMService, &out, &g_request, context, &RPC_MMService::SearchGame);
	GET_ASINCTASK->StartBackgroundTask();
}

void UMMService::AcceptGame(TMap<FString, FString> context, FUAcceptGameRequest inp, FUEmpty &out)
{
	free_RPC_MMService();
	rpc = MMServiceRPC::AcceptGame;
	game::battlemon::mm::AcceptGameRequest g_request;
	g_request << inp;
	_RPC_MMService = new RPC_MMService(ssl, URL, &AcceptGameDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::AcceptGameRequest, game::battlemon::common::Empty);
	_RPC_MMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_MMService, &out, &g_request, context, &RPC_MMService::AcceptGame);
	GET_ASINCTASK->StartBackgroundTask();
}

void UMMService::CancelSearch(TMap<FString, FString> context, FUCancelSearchRequest inp, FUEmpty &out)
{
	free_RPC_MMService();
	rpc = MMServiceRPC::CancelSearch;
	game::battlemon::mm::CancelSearchRequest g_request;
	g_request << inp;
	_RPC_MMService = new RPC_MMService(ssl, URL, &CancelSearchDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_MMService, game::battlemon::mm::CancelSearchRequest, game::battlemon::common::Empty);
	_RPC_MMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_MMService, &out, &g_request, context, &RPC_MMService::CancelSearch);
	GET_ASINCTASK->StartBackgroundTask();
}

FString UMMService::GetError()
{
	if (_RPC_MMService != nullptr)
		return _RPC_MMService->GetError();
	return FString();
}


FUMatchType& operator<<(FUMatchType &UE, const game::battlemon::mm::MatchType& grpc)
{
	UE = FUMatchType::Default;
	switch (grpc)
	{
	case game::battlemon::mm::MatchType::DEATH_MATCH:
		UE = FUMatchType::DEATH_MATCH;
		break;
	case game::battlemon::mm::MatchType::CATCH_THE_FLAG:
		UE = FUMatchType::CATCH_THE_FLAG;
		break;
	}
	return UE;
}


FUMatchMode& operator<<(FUMatchMode &UE, const game::battlemon::mm::MatchMode& grpc)
{
	UE = FUMatchMode::Default;
	switch (grpc)
	{
	case game::battlemon::mm::MatchMode::NONE:
		UE = FUMatchMode::NONE;
		break;
	case game::battlemon::mm::MatchMode::EQUIPMENT:
		UE = FUMatchMode::EQUIPMENT;
		break;
	case game::battlemon::mm::MatchMode::REALISM:
		UE = FUMatchMode::REALISM;
		break;
	}
	return UE;
}


FURegion& operator<<(FURegion &UE, const game::battlemon::mm::Region& grpc)
{
	UE = FURegion::Default;
	switch (grpc)
	{
	case game::battlemon::mm::Region::US:
		UE = FURegion::US;
		break;
	case game::battlemon::mm::Region::EU:
		UE = FURegion::EU;
		break;
	}
	return UE;
}


FUSearchGameResponseStatus& operator<<(FUSearchGameResponseStatus &UE, const game::battlemon::mm::SearchGameResponseStatus& grpc)
{
	UE = FUSearchGameResponseStatus::Default;
	switch (grpc)
	{
	case game::battlemon::mm::SearchGameResponseStatus::OK:
		UE = FUSearchGameResponseStatus::OK;
		break;
	case game::battlemon::mm::SearchGameResponseStatus::NFT_ERROR:
		UE = FUSearchGameResponseStatus::NFT_ERROR;
		break;
	case game::battlemon::mm::SearchGameResponseStatus::ALREADY_IN_QUEUE:
		UE = FUSearchGameResponseStatus::ALREADY_IN_QUEUE;
		break;
	case game::battlemon::mm::SearchGameResponseStatus::ALREADY_IN_BATTLE:
		UE = FUSearchGameResponseStatus::ALREADY_IN_BATTLE;
		break;
	case game::battlemon::mm::SearchGameResponseStatus::GAMEMODE_ERROR:
		UE = FUSearchGameResponseStatus::GAMEMODE_ERROR;
		break;
	case game::battlemon::mm::SearchGameResponseStatus::INVALID_REQUEST:
		UE = FUSearchGameResponseStatus::INVALID_REQUEST;
		break;
	case game::battlemon::mm::SearchGameResponseStatus::INTERNAL_ERROR:
		UE = FUSearchGameResponseStatus::INTERNAL_ERROR;
		break;
	}
	return UE;
}


game::battlemon::mm::MatchType& operator<<(game::battlemon::mm::MatchType & grpc, const FUMatchType &UE) 
{
	switch (UE)
	{
	case FUMatchType::DEATH_MATCH:
		grpc = game::battlemon::mm::MatchType::DEATH_MATCH;
		break;
	case FUMatchType::CATCH_THE_FLAG:
		grpc = game::battlemon::mm::MatchType::CATCH_THE_FLAG;
		break;
	}
	return grpc;
}


game::battlemon::mm::MatchMode& operator<<(game::battlemon::mm::MatchMode & grpc, const FUMatchMode &UE) 
{
	switch (UE)
	{
	case FUMatchMode::NONE:
		grpc = game::battlemon::mm::MatchMode::NONE;
		break;
	case FUMatchMode::EQUIPMENT:
		grpc = game::battlemon::mm::MatchMode::EQUIPMENT;
		break;
	case FUMatchMode::REALISM:
		grpc = game::battlemon::mm::MatchMode::REALISM;
		break;
	}
	return grpc;
}


game::battlemon::mm::Region& operator<<(game::battlemon::mm::Region & grpc, const FURegion &UE) 
{
	switch (UE)
	{
	case FURegion::US:
		grpc = game::battlemon::mm::Region::US;
		break;
	case FURegion::EU:
		grpc = game::battlemon::mm::Region::EU;
		break;
	}
	return grpc;
}


game::battlemon::mm::SearchGameResponseStatus& operator<<(game::battlemon::mm::SearchGameResponseStatus & grpc, const FUSearchGameResponseStatus &UE) 
{
	switch (UE)
	{
	case FUSearchGameResponseStatus::OK:
		grpc = game::battlemon::mm::SearchGameResponseStatus::OK;
		break;
	case FUSearchGameResponseStatus::NFT_ERROR:
		grpc = game::battlemon::mm::SearchGameResponseStatus::NFT_ERROR;
		break;
	case FUSearchGameResponseStatus::ALREADY_IN_QUEUE:
		grpc = game::battlemon::mm::SearchGameResponseStatus::ALREADY_IN_QUEUE;
		break;
	case FUSearchGameResponseStatus::ALREADY_IN_BATTLE:
		grpc = game::battlemon::mm::SearchGameResponseStatus::ALREADY_IN_BATTLE;
		break;
	case FUSearchGameResponseStatus::GAMEMODE_ERROR:
		grpc = game::battlemon::mm::SearchGameResponseStatus::GAMEMODE_ERROR;
		break;
	case FUSearchGameResponseStatus::INVALID_REQUEST:
		grpc = game::battlemon::mm::SearchGameResponseStatus::INVALID_REQUEST;
		break;
	case FUSearchGameResponseStatus::INTERNAL_ERROR:
		grpc = game::battlemon::mm::SearchGameResponseStatus::INTERNAL_ERROR;
		break;
	}
	return grpc;
}


FUCancelSearchRequest& FUCancelSearchRequest::operator=(const game::battlemon::mm::CancelSearchRequest& grpcCancelSearchRequest)
{
	return *this;
}


FUAcceptGameRequest& FUAcceptGameRequest::operator=(const game::battlemon::mm::AcceptGameRequest& grpcAcceptGameRequest)
{
	lemon_id = CONV_CHAR_TO_FSTRING(grpcAcceptGameRequest.lemon_id().c_str());
	return *this;
}


FUSearchGameResponse& FUSearchGameResponse::operator=(const game::battlemon::mm::SearchGameResponse& grpcSearchGameResponse)
{
	status << grpcSearchGameResponse.status();
	return *this;
}


FUGameMode& FUGameMode::operator=(const game::battlemon::mm::GameMode& grpcGameMode)
{
	match_type << grpcGameMode.match_type();
	match_mode << grpcGameMode.match_mode();
	return *this;
}


FUSearchGameRequest& FUSearchGameRequest::operator=(const game::battlemon::mm::SearchGameRequest& grpcSearchGameRequest)
{
	game_mode = grpcSearchGameRequest.game_mode();
	region << grpcSearchGameRequest.region();
	return *this;
}



game::battlemon::mm::CancelSearchRequest &operator<<(game::battlemon::mm::CancelSearchRequest &grpcCancelSearchRequest, const FUCancelSearchRequest &UE)
{
	return grpcCancelSearchRequest;
}


game::battlemon::mm::AcceptGameRequest &operator<<(game::battlemon::mm::AcceptGameRequest &grpcAcceptGameRequest, const FUAcceptGameRequest &UE)
{
	{
		grpcAcceptGameRequest.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	return grpcAcceptGameRequest;
}


game::battlemon::mm::SearchGameResponse &operator<<(game::battlemon::mm::SearchGameResponse &grpcSearchGameResponse, const FUSearchGameResponse &UE)
{
	{
		game::battlemon::mm::SearchGameResponseStatus go;
		go << UE.status;
		grpcSearchGameResponse.set_status(go);
	}
	return grpcSearchGameResponse;
}


game::battlemon::mm::GameMode &operator<<(game::battlemon::mm::GameMode &grpcGameMode, const FUGameMode &UE)
{
	{
		game::battlemon::mm::MatchType go;
		go << UE.match_type;
		grpcGameMode.set_match_type(go);
	}
	{
		game::battlemon::mm::MatchMode go;
		go << UE.match_mode;
		grpcGameMode.set_match_mode(go);
	}
	return grpcGameMode;
}


game::battlemon::mm::SearchGameRequest &operator<<(game::battlemon::mm::SearchGameRequest &grpcSearchGameRequest, const FUSearchGameRequest &UE)
{
	{
		game::battlemon::mm::GameMode* go = new game::battlemon::mm::GameMode();
		*go << UE.game_mode;
		grpcSearchGameRequest.set_allocated_game_mode(go);
	}
	{
		game::battlemon::mm::Region go;
		go << UE.region;
		grpcSearchGameRequest.set_region(go);
	}
	return grpcSearchGameRequest;
}

