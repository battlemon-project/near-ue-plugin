#include"internalMm.h"

FUInternalUserLeftBattleRequest& FUInternalUserLeftBattleRequest::operator=(const game::battlemon::mm::internal::InternalUserLeftBattleRequest& grpcInternalUserLeftBattleRequest)
{
	near_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLeftBattleRequest.near_id().c_str());
	room_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLeftBattleRequest.room_id().c_str());
	is_accident = grpcInternalUserLeftBattleRequest.is_accident();
	return *this;
}


FUSaveBattleResultRequest& FUSaveBattleResultRequest::operator=(const game::battlemon::mm::internal::SaveBattleResultRequest& grpcSaveBattleResultRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcSaveBattleResultRequest.room_id().c_str());
	int size = grpcSaveBattleResultRequest.results().size();
	results.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		results[Idx] = grpcSaveBattleResultRequest.results(Idx);
		});
	ott = CONV_CHAR_TO_FSTRING(grpcSaveBattleResultRequest.ott().c_str());
	return *this;
}


FUInternalPlayerResult& FUInternalPlayerResult::operator=(const game::battlemon::mm::internal::InternalPlayerResult& grpcInternalPlayerResult)
{
	near_id = CONV_CHAR_TO_FSTRING(grpcInternalPlayerResult.near_id().c_str());
	place = grpcInternalPlayerResult.place();
	return *this;
}


FURoomInfoRequest& FURoomInfoRequest::operator=(const game::battlemon::mm::internal::RoomInfoRequest& grpcRoomInfoRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcRoomInfoRequest.room_id().c_str());
	ott = CONV_CHAR_TO_FSTRING(grpcRoomInfoRequest.ott().c_str());
	return *this;
}


FURoomInfoResponse& FURoomInfoResponse::operator=(const game::battlemon::mm::internal::RoomInfoResponse& grpcRoomInfoResponse)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcRoomInfoResponse.room_id().c_str());
	mode = grpcRoomInfoResponse.mode();
	int size = grpcRoomInfoResponse.players().size();
	players.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		players[Idx] = grpcRoomInfoResponse.players(Idx);
		});
	return *this;
}


FURoomPlayerInfo& FURoomPlayerInfo::operator=(const game::battlemon::mm::internal::RoomPlayerInfo& grpcRoomPlayerInfo)
{
	near_id = CONV_CHAR_TO_FSTRING(grpcRoomPlayerInfo.near_id().c_str());
	lemon = grpcRoomPlayerInfo.lemon();
	return *this;
}


FUCreateRoomRequest& FUCreateRoomRequest::operator=(const game::battlemon::mm::internal::CreateRoomRequest& grpcCreateRoomRequest)
{
	mode = grpcCreateRoomRequest.mode();
	int size = grpcCreateRoomRequest.near_ids().size();
	near_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		near_ids[Idx] = CONV_CHAR_TO_FSTRING(grpcCreateRoomRequest.near_ids(Idx).c_str());
		});
	prev_room_id = CONV_CHAR_TO_FSTRING(grpcCreateRoomRequest.prev_room_id().c_str());
	ott = CONV_CHAR_TO_FSTRING(grpcCreateRoomRequest.ott().c_str());
	return *this;
}


FUDedicatedServerIsReadyRequest& FUDedicatedServerIsReadyRequest::operator=(const game::battlemon::mm::internal::DedicatedServerIsReadyRequest& grpcDedicatedServerIsReadyRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcDedicatedServerIsReadyRequest.room_id().c_str());
	ott = CONV_CHAR_TO_FSTRING(grpcDedicatedServerIsReadyRequest.ott().c_str());
	return *this;
}



game::battlemon::mm::internal::InternalUserLeftBattleRequest &operator<<(game::battlemon::mm::internal::InternalUserLeftBattleRequest &grpcInternalUserLeftBattleRequest, const FUInternalUserLeftBattleRequest &UE)
{
	{
		grpcInternalUserLeftBattleRequest.set_near_id(CONV_FSTRING_TO_CHAR(UE.near_id));
	}
	{
		grpcInternalUserLeftBattleRequest.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		grpcInternalUserLeftBattleRequest.set_is_accident(UE.is_accident);
	}
	return grpcInternalUserLeftBattleRequest;
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


game::battlemon::mm::internal::InternalPlayerResult &operator<<(game::battlemon::mm::internal::InternalPlayerResult &grpcInternalPlayerResult, const FUInternalPlayerResult &UE)
{
	{
		grpcInternalPlayerResult.set_near_id(CONV_FSTRING_TO_CHAR(UE.near_id));
	}
	{
		grpcInternalPlayerResult.set_place(UE.place);
	}
	return grpcInternalPlayerResult;
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


game::battlemon::mm::internal::RoomPlayerInfo &operator<<(game::battlemon::mm::internal::RoomPlayerInfo &grpcRoomPlayerInfo, const FURoomPlayerInfo &UE)
{
	{
		grpcRoomPlayerInfo.set_near_id(CONV_FSTRING_TO_CHAR(UE.near_id));
	}
	{
		game::battlemon::items::Item* go = new game::battlemon::items::Item();
		*go << UE.lemon;
		grpcRoomPlayerInfo.set_allocated_lemon(go);
	}
	return grpcRoomPlayerInfo;
}


game::battlemon::mm::internal::CreateRoomRequest &operator<<(game::battlemon::mm::internal::CreateRoomRequest &grpcCreateRoomRequest, const FUCreateRoomRequest &UE)
{
	{
		game::battlemon::mm::GameMode* go = new game::battlemon::mm::GameMode();
		*go << UE.mode;
		grpcCreateRoomRequest.set_allocated_mode(go);
	}
		int size = UE.near_ids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		std::string* ptr =grpcCreateRoomRequest.add_near_ids();
		*ptr =CONV_FSTRING_TO_CHAR(UE.near_ids[Idx]);
	}
	{
		grpcCreateRoomRequest.set_prev_room_id(CONV_FSTRING_TO_CHAR(UE.prev_room_id));
	}
	{
		grpcCreateRoomRequest.set_ott(CONV_FSTRING_TO_CHAR(UE.ott));
	}
	return grpcCreateRoomRequest;
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

