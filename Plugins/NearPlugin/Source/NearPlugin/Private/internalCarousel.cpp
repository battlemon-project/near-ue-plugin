#include"internalCarousel.h"
#include "AsyncTask.h"

FURequestCase& operator<<(FURequestCase &UE, const game::battlemon::carousel::internal::CarouselRequests::RequestCase& grpc)
{
	UE = FURequestCase::Default;
	switch (grpc)
	{
	case game::battlemon::carousel::internal::CarouselRequests::RequestCase::kNewPlayer:
		UE = FURequestCase::kNewPlayer;
		break;
	case game::battlemon::carousel::internal::CarouselRequests::RequestCase::kNewRoom:
		UE = FURequestCase::kNewRoom;
		break;
	case game::battlemon::carousel::internal::CarouselRequests::RequestCase::kRemovePlayer:
		UE = FURequestCase::kRemovePlayer;
		break;
	case game::battlemon::carousel::internal::CarouselRequests::RequestCase::kRoomFinished:
		UE = FURequestCase::kRoomFinished;
		break;
	case game::battlemon::carousel::internal::CarouselRequests::RequestCase::kAcceptGame:
		UE = FURequestCase::kAcceptGame;
		break;
	}
	return UE;
}


FUResponseCase& operator<<(FUResponseCase &UE, const game::battlemon::carousel::internal::CarouselResponses::ResponseCase& grpc)
{
	UE = FUResponseCase::Default;
	switch (grpc)
	{
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kRoomReady:
		UE = FUResponseCase::kRoomReady;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kNewRoomPlayer:
		UE = FUResponseCase::kNewRoomPlayer;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kNeedUsersAccept:
		UE = FUResponseCase::kNeedUsersAccept;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kRoomNotFound:
		UE = FUResponseCase::kRoomNotFound;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kAcceptingCanceled:
		UE = FUResponseCase::kAcceptingCanceled;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kPlayerInQueue:
		UE = FUResponseCase::kPlayerInQueue;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kPlayerInBattle:
		UE = FUResponseCase::kPlayerInBattle;
		break;
	case game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kPlayerOutOfLine:
		UE = FUResponseCase::kPlayerOutOfLine;
		break;
	}
	return UE;
}


game::battlemon::carousel::internal::CarouselRequests::RequestCase& operator<<(game::battlemon::carousel::internal::CarouselRequests::RequestCase & grpc, const FURequestCase &UE) 
{
	switch (UE)
	{
	case FURequestCase::kNewPlayer:
		grpc = game::battlemon::carousel::internal::CarouselRequests::RequestCase::kNewPlayer;
		break;
	case FURequestCase::kNewRoom:
		grpc = game::battlemon::carousel::internal::CarouselRequests::RequestCase::kNewRoom;
		break;
	case FURequestCase::kRemovePlayer:
		grpc = game::battlemon::carousel::internal::CarouselRequests::RequestCase::kRemovePlayer;
		break;
	case FURequestCase::kRoomFinished:
		grpc = game::battlemon::carousel::internal::CarouselRequests::RequestCase::kRoomFinished;
		break;
	case FURequestCase::kAcceptGame:
		grpc = game::battlemon::carousel::internal::CarouselRequests::RequestCase::kAcceptGame;
		break;
	}
	return grpc;
}


game::battlemon::carousel::internal::CarouselResponses::ResponseCase& operator<<(game::battlemon::carousel::internal::CarouselResponses::ResponseCase & grpc, const FUResponseCase &UE) 
{
	switch (UE)
	{
	case FUResponseCase::kRoomReady:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kRoomReady;
		break;
	case FUResponseCase::kNewRoomPlayer:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kNewRoomPlayer;
		break;
	case FUResponseCase::kNeedUsersAccept:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kNeedUsersAccept;
		break;
	case FUResponseCase::kRoomNotFound:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kRoomNotFound;
		break;
	case FUResponseCase::kAcceptingCanceled:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kAcceptingCanceled;
		break;
	case FUResponseCase::kPlayerInQueue:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kPlayerInQueue;
		break;
	case FUResponseCase::kPlayerInBattle:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kPlayerInBattle;
		break;
	case FUResponseCase::kPlayerOutOfLine:
		grpc = game::battlemon::carousel::internal::CarouselResponses::ResponseCase::kPlayerOutOfLine;
		break;
	}
	return grpc;
}


FUNeedUsersAccept& FUNeedUsersAccept::operator=(const game::battlemon::carousel::internal::NeedUsersAccept& grpcNeedUsersAccept)
{
{
	int size = grpcNeedUsersAccept.user_ids().size();
	user_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		user_ids[Idx] = CONV_CHAR_TO_FSTRING(grpcNeedUsersAccept.user_ids(Idx).c_str());
		});

	}
	manual_accept = grpcNeedUsersAccept.manual_accept();
	time_to_accept = grpcNeedUsersAccept.time_to_accept();
	return *this;
}


FUInternalPlayer& FUInternalPlayer::operator=(const game::battlemon::carousel::internal::InternalPlayer& grpcInternalPlayer)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalPlayer.user_id().c_str());
	lemon_id = CONV_CHAR_TO_FSTRING(grpcInternalPlayer.lemon_id().c_str());
	room_id = CONV_CHAR_TO_FSTRING(grpcInternalPlayer.room_id().c_str());
	mode = grpcInternalPlayer.mode();
	return *this;
}


FUInternalRoomInfo& FUInternalRoomInfo::operator=(const game::battlemon::carousel::internal::InternalRoomInfo& grpcInternalRoomInfo)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcInternalRoomInfo.room_id().c_str());
	mode = grpcInternalRoomInfo.mode();
{
	int size = grpcInternalRoomInfo.players().size();
	players.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		players[Idx] = grpcInternalRoomInfo.players(Idx);
		});

	}
	region << grpcInternalRoomInfo.region();
	return *this;
}


FUCarouselResponses& FUCarouselResponses::operator=(const game::battlemon::carousel::internal::CarouselResponses& grpcCarouselResponses)
{
	return *this;
}


FUCarouselRequests& FUCarouselRequests::operator=(const game::battlemon::carousel::internal::CarouselRequests& grpcCarouselRequests)
{
	return *this;
}



game::battlemon::carousel::internal::NeedUsersAccept &operator<<(game::battlemon::carousel::internal::NeedUsersAccept &grpcNeedUsersAccept, const FUNeedUsersAccept &UE)
{
		int size = UE.user_ids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		std::string* ptr =grpcNeedUsersAccept.add_user_ids();
		*ptr =CONV_FSTRING_TO_CHAR(UE.user_ids[Idx]);
	}
	{
		grpcNeedUsersAccept.set_manual_accept(UE.manual_accept);
	}
	{
		grpcNeedUsersAccept.set_time_to_accept(UE.time_to_accept);
	}
	return grpcNeedUsersAccept;
}


game::battlemon::carousel::internal::InternalPlayer &operator<<(game::battlemon::carousel::internal::InternalPlayer &grpcInternalPlayer, const FUInternalPlayer &UE)
{
	{
		grpcInternalPlayer.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		grpcInternalPlayer.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	{
		grpcInternalPlayer.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		game::battlemon::mm::GameMode* go = new game::battlemon::mm::GameMode();
		*go << UE.mode;
		grpcInternalPlayer.set_allocated_mode(go);
	}
	return grpcInternalPlayer;
}


game::battlemon::carousel::internal::InternalRoomInfo &operator<<(game::battlemon::carousel::internal::InternalRoomInfo &grpcInternalRoomInfo, const FUInternalRoomInfo &UE)
{
	{
		grpcInternalRoomInfo.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		game::battlemon::mm::GameMode* go = new game::battlemon::mm::GameMode();
		*go << UE.mode;
		grpcInternalRoomInfo.set_allocated_mode(go);
	}
		int size = UE.players.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::carousel::internal::InternalPlayer* ptr =grpcInternalRoomInfo.add_players();
		(*ptr) << UE.players[Idx];
	}
	{
		game::battlemon::mm::Region go;
		go << UE.region;
		grpcInternalRoomInfo.set_region(go);
	}
	return grpcInternalRoomInfo;
}


game::battlemon::carousel::internal::CarouselResponses &operator<<(game::battlemon::carousel::internal::CarouselResponses &grpcCarouselResponses, const FUCarouselResponses &UE)
{
	switch (UE.response_case)
	{
	case FUResponseCase::kRoomReady:
	{
		game::battlemon::carousel::internal::InternalRoomInfo* go = new game::battlemon::carousel::internal::InternalRoomInfo();
		*go << UE.room_ready;
		grpcCarouselResponses.set_allocated_room_ready(go);
	}
		break;
	case FUResponseCase::kNewRoomPlayer:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.new_room_player;
		grpcCarouselResponses.set_allocated_new_room_player(go);
	}
		break;
	case FUResponseCase::kNeedUsersAccept:
	{
		game::battlemon::carousel::internal::NeedUsersAccept* needUsersAccept = new game::battlemon::carousel::internal::NeedUsersAccept();

		*needUsersAccept << UE.need_users_accept;
		grpcCarouselResponses.set_allocated_need_users_accept(needUsersAccept);
	}
		break;
	case FUResponseCase::kRoomNotFound:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.room_not_found;
		grpcCarouselResponses.set_allocated_room_not_found(go);
	}
		break;
	case FUResponseCase::kAcceptingCanceled:
	{
		game::battlemon::carousel::internal::InternalRoomInfo* go = new game::battlemon::carousel::internal::InternalRoomInfo();
		*go << UE.accepting_canceled;
		grpcCarouselResponses.set_allocated_accepting_canceled(go);
	}
		break;
	case FUResponseCase::kPlayerInQueue:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.player_in_queue;
		grpcCarouselResponses.set_allocated_player_in_queue(go);
	}
		break;
	case FUResponseCase::kPlayerInBattle:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.player_in_battle;
		grpcCarouselResponses.set_allocated_player_in_battle(go);
	}
		break;
	case FUResponseCase::kPlayerOutOfLine:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.player_out_of_line;
		grpcCarouselResponses.set_allocated_player_out_of_line(go);
	}
		break;
	}
	return grpcCarouselResponses;
}


game::battlemon::carousel::internal::CarouselRequests &operator<<(game::battlemon::carousel::internal::CarouselRequests &grpcCarouselRequests, const FUCarouselRequests &UE)
{
	switch (UE.request_case)
	{
	case FURequestCase::kNewPlayer:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.new_player;
		grpcCarouselRequests.set_allocated_new_player(go);
	}
		break;
	case FURequestCase::kNewRoom:
	{
		game::battlemon::carousel::internal::InternalRoomInfo* go = new game::battlemon::carousel::internal::InternalRoomInfo();
		*go << UE.new_room;
		grpcCarouselRequests.set_allocated_new_room(go);
	}
		break;
	case FURequestCase::kRemovePlayer:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.remove_player;
		grpcCarouselRequests.set_allocated_remove_player(go);
	}
		break;
	case FURequestCase::kRoomFinished:
	{
		game::battlemon::carousel::internal::InternalRoomInfo* go = new game::battlemon::carousel::internal::InternalRoomInfo();
		*go << UE.room_finished;
		grpcCarouselRequests.set_allocated_room_finished(go);
	}
		break;
	case FURequestCase::kAcceptGame:
	{
		game::battlemon::carousel::internal::InternalPlayer* go = new game::battlemon::carousel::internal::InternalPlayer();
		*go << UE.accept_game;
		grpcCarouselRequests.set_allocated_accept_game(go);
	}
		break;
	}
	return grpcCarouselRequests;
}

