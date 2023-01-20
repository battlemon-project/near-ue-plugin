#include"internalMm.h"
#include "AsyncTask.h"

RPC_InternalMMService* UInternalMMService::_RPC_InternalMMService = nullptr;

RPC_InternalMMService::RPC_InternalMMService(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out) {}

RPC_InternalMMService::~RPC_InternalMMService() {}

game::battlemon::common::Empty RPC_InternalMMService::UserLeftBattle(grpc::ClientContext* context, const game::battlemon::mm::internal::InternalUserLeftBattleRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->UserLeftBattle(context, *request, &read));

	if (static_cast<FUserLeftBattleDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FUserLeftBattleDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_InternalMMService::SaveBattleResult(grpc::ClientContext* context, const game::battlemon::mm::internal::SaveBattleResultRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->SaveBattleResult(context, *request, &read));

	if (static_cast<FSaveBattleResultDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FSaveBattleResultDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

game::battlemon::mm::internal::RoomInfoResponse RPC_InternalMMService::GetRoomInfo(grpc::ClientContext* context, const game::battlemon::mm::internal::RoomInfoRequest* request)
{
	game::battlemon::mm::internal::RoomInfoResponse read;
	CheckError(stub.get()->GetRoomInfo(context, *request, &read));

	if (static_cast<FGetRoomInfoDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FURoomInfoResponse*>(out) = read;
		static_cast<FGetRoomInfoDelegate*>(Delegate)->Broadcast(*static_cast<FURoomInfoResponse*>(out));
	}
	return read;
}

game::battlemon::mm::internal::RoomInfoResponse RPC_InternalMMService::CreateRoomWithPlayers(grpc::ClientContext* context, const game::battlemon::mm::internal::CreateRoomRequest* request)
{
	game::battlemon::mm::internal::RoomInfoResponse read;
	CheckError(stub.get()->CreateRoomWithPlayers(context, *request, &read));

	if (static_cast<FCreateRoomWithPlayersDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FURoomInfoResponse*>(out) = read;
		static_cast<FCreateRoomWithPlayersDelegate*>(Delegate)->Broadcast(*static_cast<FURoomInfoResponse*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_InternalMMService::DedicatedServerIsReady(grpc::ClientContext* context, const game::battlemon::mm::internal::DedicatedServerIsReadyRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->DedicatedServerIsReady(context, *request, &read));

	if (static_cast<FDedicatedServerIsReadyDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FDedicatedServerIsReadyDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

void UInternalMMService::free_RPC_InternalMMService()
{
	if (_RPC_InternalMMService != nullptr)
	{
		if (_RPC_InternalMMService->Task != nullptr)
		{
			switch (rpc)
			{
			case InternalMMServiceRPC::UserLeftBattle:
				if (!CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::InternalUserLeftBattleRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::InternalUserLeftBattleRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::InternalUserLeftBattleRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task);
				break;
			case InternalMMServiceRPC::SaveBattleResult:
				if (!CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::SaveBattleResultRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::SaveBattleResultRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::SaveBattleResultRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task);
				break;
			case InternalMMServiceRPC::GetRoomInfo:
				if (!CAST_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse)(_RPC_InternalMMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse)(_RPC_InternalMMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse)(_RPC_InternalMMService->Task);
				break;
			case InternalMMServiceRPC::CreateRoomWithPlayers:
				if (!CAST_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse)(_RPC_InternalMMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse)(_RPC_InternalMMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse)(_RPC_InternalMMService->Task);
				break;
			case InternalMMServiceRPC::DedicatedServerIsReady:
				if (!CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, game::battlemon::common::Empty)(_RPC_InternalMMService->Task);
				break;
			}
			_RPC_InternalMMService->Task = nullptr;
		}
		delete _RPC_InternalMMService;
	}
	_RPC_InternalMMService = nullptr;
}

UInternalMMService::UInternalMMService() {}

UInternalMMService::~UInternalMMService() 
{
	free_RPC_InternalMMService();
}

void UInternalMMService::UserLeftBattle(TMap<FString, FString> context, FUInternalUserLeftBattleRequest inp, FUEmpty &out)
{
	free_RPC_InternalMMService();
	rpc = InternalMMServiceRPC::UserLeftBattle;
	game::battlemon::mm::internal::InternalUserLeftBattleRequest g_request;
	g_request << inp;
	_RPC_InternalMMService = new RPC_InternalMMService(ssl, URL, &UserLeftBattleDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::InternalUserLeftBattleRequest, game::battlemon::common::Empty);
	_RPC_InternalMMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalMMService, &out, &g_request, context, &RPC_InternalMMService::UserLeftBattle);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalMMService::SaveBattleResult(TMap<FString, FString> context, FUSaveBattleResultRequest inp, FUEmpty &out)
{
	free_RPC_InternalMMService();
	rpc = InternalMMServiceRPC::SaveBattleResult;
	game::battlemon::mm::internal::SaveBattleResultRequest g_request;
	g_request << inp;
	_RPC_InternalMMService = new RPC_InternalMMService(ssl, URL, &SaveBattleResultDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::SaveBattleResultRequest, game::battlemon::common::Empty);
	_RPC_InternalMMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalMMService, &out, &g_request, context, &RPC_InternalMMService::SaveBattleResult);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalMMService::GetRoomInfo(TMap<FString, FString> context, FURoomInfoRequest inp, FURoomInfoResponse &out)
{
	free_RPC_InternalMMService();
	rpc = InternalMMServiceRPC::GetRoomInfo;
	game::battlemon::mm::internal::RoomInfoRequest g_request;
	g_request << inp;
	_RPC_InternalMMService = new RPC_InternalMMService(ssl, URL, &GetRoomInfoDelegate, &out);
	CREATE_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse);
	_RPC_InternalMMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalMMService, &out, &g_request, context, &RPC_InternalMMService::GetRoomInfo);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalMMService::CreateRoomWithPlayers(TMap<FString, FString> context, FUCreateRoomRequest inp, FURoomInfoResponse &out)
{
	free_RPC_InternalMMService();
	rpc = InternalMMServiceRPC::CreateRoomWithPlayers;
	game::battlemon::mm::internal::CreateRoomRequest g_request;
	g_request << inp;
	_RPC_InternalMMService = new RPC_InternalMMService(ssl, URL, &CreateRoomWithPlayersDelegate, &out);
	CREATE_ASINCTASK(FURoomInfoResponse, RPC_InternalMMService, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse);
	_RPC_InternalMMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalMMService, &out, &g_request, context, &RPC_InternalMMService::CreateRoomWithPlayers);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalMMService::DedicatedServerIsReady(TMap<FString, FString> context, FUDedicatedServerIsReadyRequest inp, FUEmpty &out)
{
	free_RPC_InternalMMService();
	rpc = InternalMMServiceRPC::DedicatedServerIsReady;
	game::battlemon::mm::internal::DedicatedServerIsReadyRequest g_request;
	g_request << inp;
	_RPC_InternalMMService = new RPC_InternalMMService(ssl, URL, &DedicatedServerIsReadyDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_InternalMMService, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, game::battlemon::common::Empty);
	_RPC_InternalMMService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalMMService, &out, &g_request, context, &RPC_InternalMMService::DedicatedServerIsReady);
	GET_ASINCTASK->StartBackgroundTask();
}

FString UInternalMMService::GetError()
{
	if (_RPC_InternalMMService != nullptr)
		return _RPC_InternalMMService->GetError();
	return FString();
}


FUDedicatedServerIsReadyRequest& FUDedicatedServerIsReadyRequest::operator=(const game::battlemon::mm::internal::DedicatedServerIsReadyRequest& grpcDedicatedServerIsReadyRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcDedicatedServerIsReadyRequest.room_id().c_str());
	ott = CONV_CHAR_TO_FSTRING(grpcDedicatedServerIsReadyRequest.ott().c_str());
	return *this;
}


FUCreateRoomRequest& FUCreateRoomRequest::operator=(const game::battlemon::mm::internal::CreateRoomRequest& grpcCreateRoomRequest)
{
	mode = grpcCreateRoomRequest.mode();
{
	int size = grpcCreateRoomRequest.user_ids().size();
	user_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		user_ids[Idx] = CONV_CHAR_TO_FSTRING(grpcCreateRoomRequest.user_ids(Idx).c_str());
		});

	}
	prev_room_id = CONV_CHAR_TO_FSTRING(grpcCreateRoomRequest.prev_room_id().c_str());
	ott = CONV_CHAR_TO_FSTRING(grpcCreateRoomRequest.ott().c_str());
	return *this;
}


FURoomPlayerInfo& FURoomPlayerInfo::operator=(const game::battlemon::mm::internal::RoomPlayerInfo& grpcRoomPlayerInfo)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcRoomPlayerInfo.user_id().c_str());
	lemon = grpcRoomPlayerInfo.lemon();
	return *this;
}


FURoomInfoResponse& FURoomInfoResponse::operator=(const game::battlemon::mm::internal::RoomInfoResponse& grpcRoomInfoResponse)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcRoomInfoResponse.room_id().c_str());
	mode = grpcRoomInfoResponse.mode();
{
	int size = grpcRoomInfoResponse.players().size();
	players.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		players[Idx] = grpcRoomInfoResponse.players(Idx);
		});

	}
	return *this;
}


FURoomInfoRequest& FURoomInfoRequest::operator=(const game::battlemon::mm::internal::RoomInfoRequest& grpcRoomInfoRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcRoomInfoRequest.room_id().c_str());
	ott = CONV_CHAR_TO_FSTRING(grpcRoomInfoRequest.ott().c_str());
	return *this;
}


FUInternalPlayerResult& FUInternalPlayerResult::operator=(const game::battlemon::mm::internal::InternalPlayerResult& grpcInternalPlayerResult)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalPlayerResult.user_id().c_str());
	place = grpcInternalPlayerResult.place();
	return *this;
}


FUSaveBattleResultRequest& FUSaveBattleResultRequest::operator=(const game::battlemon::mm::internal::SaveBattleResultRequest& grpcSaveBattleResultRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcSaveBattleResultRequest.room_id().c_str());
{
	int size = grpcSaveBattleResultRequest.results().size();
	results.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		results[Idx] = grpcSaveBattleResultRequest.results(Idx);
		});

	}
	ott = CONV_CHAR_TO_FSTRING(grpcSaveBattleResultRequest.ott().c_str());
	return *this;
}


FUInternalUserLeftBattleRequest& FUInternalUserLeftBattleRequest::operator=(const game::battlemon::mm::internal::InternalUserLeftBattleRequest& grpcInternalUserLeftBattleRequest)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLeftBattleRequest.user_id().c_str());
	room_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLeftBattleRequest.room_id().c_str());
	is_accident = grpcInternalUserLeftBattleRequest.is_accident();
	return *this;
}



game::battlemon::mm::internal::DedicatedServerIsReadyRequest &operator<<(game::battlemon::mm::internal::DedicatedServerIsReadyRequest &grpcDedicatedServerIsReadyRequest, const FUDedicatedServerIsReadyRequest &UE)
{
	{
		grpcDedicatedServerIsReadyRequest.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		grpcDedicatedServerIsReadyRequest.set_ott(CONV_FSTRING_TO_CHAR(UE.ott));
	}
	return grpcDedicatedServerIsReadyRequest;
}


game::battlemon::mm::internal::CreateRoomRequest &operator<<(game::battlemon::mm::internal::CreateRoomRequest &grpcCreateRoomRequest, const FUCreateRoomRequest &UE)
{
	{
		game::battlemon::mm::GameMode* go = new game::battlemon::mm::GameMode();
		*go << UE.mode;
		grpcCreateRoomRequest.set_allocated_mode(go);
	}
		int size = UE.user_ids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		std::string* ptr =grpcCreateRoomRequest.add_user_ids();
		*ptr =CONV_FSTRING_TO_CHAR(UE.user_ids[Idx]);
	}
	{
		grpcCreateRoomRequest.set_prev_room_id(CONV_FSTRING_TO_CHAR(UE.prev_room_id));
	}
	{
		grpcCreateRoomRequest.set_ott(CONV_FSTRING_TO_CHAR(UE.ott));
	}
	return grpcCreateRoomRequest;
}


game::battlemon::mm::internal::RoomPlayerInfo &operator<<(game::battlemon::mm::internal::RoomPlayerInfo &grpcRoomPlayerInfo, const FURoomPlayerInfo &UE)
{
	{
		grpcRoomPlayerInfo.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		game::battlemon::items::Item* go = new game::battlemon::items::Item();
		*go << UE.lemon;
		grpcRoomPlayerInfo.set_allocated_lemon(go);
	}
	return grpcRoomPlayerInfo;
}


game::battlemon::mm::internal::RoomInfoResponse &operator<<(game::battlemon::mm::internal::RoomInfoResponse &grpcRoomInfoResponse, const FURoomInfoResponse &UE)
{
	{
		grpcRoomInfoResponse.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		game::battlemon::mm::GameMode* go = new game::battlemon::mm::GameMode();
		*go << UE.mode;
		grpcRoomInfoResponse.set_allocated_mode(go);
	}
		int size = UE.players.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::mm::internal::RoomPlayerInfo* ptr =grpcRoomInfoResponse.add_players();
		(*ptr) << UE.players[Idx];
	}
	return grpcRoomInfoResponse;
}


game::battlemon::mm::internal::RoomInfoRequest &operator<<(game::battlemon::mm::internal::RoomInfoRequest &grpcRoomInfoRequest, const FURoomInfoRequest &UE)
{
	{
		grpcRoomInfoRequest.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		grpcRoomInfoRequest.set_ott(CONV_FSTRING_TO_CHAR(UE.ott));
	}
	return grpcRoomInfoRequest;
}


game::battlemon::mm::internal::InternalPlayerResult &operator<<(game::battlemon::mm::internal::InternalPlayerResult &grpcInternalPlayerResult, const FUInternalPlayerResult &UE)
{
	{
		grpcInternalPlayerResult.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		grpcInternalPlayerResult.set_place(UE.place);
	}
	return grpcInternalPlayerResult;
}


game::battlemon::mm::internal::SaveBattleResultRequest &operator<<(game::battlemon::mm::internal::SaveBattleResultRequest &grpcSaveBattleResultRequest, const FUSaveBattleResultRequest &UE)
{
	{
		grpcSaveBattleResultRequest.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
		int size = UE.results.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::mm::internal::InternalPlayerResult* ptr =grpcSaveBattleResultRequest.add_results();
		(*ptr) << UE.results[Idx];
	}
	{
		grpcSaveBattleResultRequest.set_ott(CONV_FSTRING_TO_CHAR(UE.ott));
	}
	return grpcSaveBattleResultRequest;
}


game::battlemon::mm::internal::InternalUserLeftBattleRequest &operator<<(game::battlemon::mm::internal::InternalUserLeftBattleRequest &grpcInternalUserLeftBattleRequest, const FUInternalUserLeftBattleRequest &UE)
{
	{
		grpcInternalUserLeftBattleRequest.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		grpcInternalUserLeftBattleRequest.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		grpcInternalUserLeftBattleRequest.set_is_accident(UE.is_accident);
	}
	return grpcInternalUserLeftBattleRequest;
}

