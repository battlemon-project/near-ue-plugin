#include"updates.h"
#include "AsyncTask.h"

FUUpdateCase& operator<<(FUUpdateCase &UE, const game::battlemon::updates::UpdateMessage::UpdateCase& grpc)
{
	UE = FUUpdateCase::Default;
	switch (grpc)
	{
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomNeedAccept:
		UE = FUUpdateCase::kRoomNeedAccept;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomAcceptingCanceled:
		UE = FUUpdateCase::kRoomAcceptingCanceled;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomFound:
		UE = FUUpdateCase::kRoomFound;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomTeammates:
		UE = FUUpdateCase::kRoomTeammates;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kRoomReady:
		UE = FUUpdateCase::kRoomReady;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kUserIsAlreadyInLine:
		UE = FUUpdateCase::kUserIsAlreadyInLine;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kUserIsAlreadyInBattle:
		UE = FUUpdateCase::kUserIsAlreadyInBattle;
		break;
	case game::battlemon::updates::UpdateMessage::UpdateCase::kUserOutOfLine:
		UE = FUUpdateCase::kUserOutOfLine;
		break;
	}
	return UE;
}


game::battlemon::updates::UpdateMessage::UpdateCase& operator<<(game::battlemon::updates::UpdateMessage::UpdateCase & grpc, const FUUpdateCase &UE) 
{
	switch (UE)
	{
	case FUUpdateCase::kRoomNeedAccept:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kRoomNeedAccept;
		break;
	case FUUpdateCase::kRoomAcceptingCanceled:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kRoomAcceptingCanceled;
		break;
	case FUUpdateCase::kRoomFound:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kRoomFound;
		break;
	case FUUpdateCase::kRoomTeammates:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kRoomTeammates;
		break;
	case FUUpdateCase::kRoomReady:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kRoomReady;
		break;
	case FUUpdateCase::kUserIsAlreadyInLine:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kUserIsAlreadyInLine;
		break;
	case FUUpdateCase::kUserIsAlreadyInBattle:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kUserIsAlreadyInBattle;
		break;
	case FUUpdateCase::kUserOutOfLine:
		grpc = game::battlemon::updates::UpdateMessage::UpdateCase::kUserOutOfLine;
		break;
	}
	return grpc;
}


FURoomPlayer& FURoomPlayer::operator=(const game::battlemon::updates::RoomPlayer& grpcRoomPlayer)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcRoomPlayer.user_id().c_str());
	lemon = grpcRoomPlayer.lemon();
	return *this;
}


FURoomInfo& FURoomInfo::operator=(const game::battlemon::updates::RoomInfo& grpcRoomInfo)
{
	room_id = CONV_CHAR_TO_FSTRING(grpcRoomInfo.room_id().c_str());
	server_ip = CONV_CHAR_TO_FSTRING(grpcRoomInfo.server_ip().c_str());
{
	int size = grpcRoomInfo.players().size();
	players.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		players[Idx] = grpcRoomInfo.players(Idx);
		});

	}
	return *this;
}


FURoomNeedAccept& FURoomNeedAccept::operator=(const game::battlemon::updates::RoomNeedAccept& grpcRoomNeedAccept)
{
	manual_accept = grpcRoomNeedAccept.manual_accept();
	time_to_accept = grpcRoomNeedAccept.time_to_accept();
	return *this;
}


FUUpdateMessage& FUUpdateMessage::operator=(const game::battlemon::updates::UpdateMessage& grpcUpdateMessage)
{
	return *this;
}


FUUpdate& FUUpdate::operator=(const game::battlemon::updates::Update& grpcUpdate)
{
	id = CONV_CHAR_TO_FSTRING(grpcUpdate.id().c_str());
	timestamp = grpcUpdate.timestamp();
	message = CONV_CHAR_TO_FSTRING(grpcUpdate.message().c_str());
	return *this;
}



game::battlemon::updates::RoomPlayer &operator<<(game::battlemon::updates::RoomPlayer &grpcRoomPlayer, const FURoomPlayer &UE)
{
	{
		grpcRoomPlayer.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		game::battlemon::items::Item* go = new game::battlemon::items::Item();
		*go << UE.lemon;
		grpcRoomPlayer.set_allocated_lemon(go);
	}
	return grpcRoomPlayer;
}


game::battlemon::updates::RoomInfo &operator<<(game::battlemon::updates::RoomInfo &grpcRoomInfo, const FURoomInfo &UE)
{
	{
		grpcRoomInfo.set_room_id(CONV_FSTRING_TO_CHAR(UE.room_id));
	}
	{
		grpcRoomInfo.set_server_ip(CONV_FSTRING_TO_CHAR(UE.server_ip));
	}
		int size = UE.players.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::updates::RoomPlayer* ptr = grpcRoomInfo.add_players();
		*ptr <<UE.players[Idx];
	}
	return grpcRoomInfo;
}


game::battlemon::updates::RoomNeedAccept &operator<<(game::battlemon::updates::RoomNeedAccept &grpcRoomNeedAccept, const FURoomNeedAccept &UE)
{
	{
		grpcRoomNeedAccept.set_manual_accept(UE.manual_accept);
	}
	{
		grpcRoomNeedAccept.set_time_to_accept(UE.time_to_accept);
	}
	return grpcRoomNeedAccept;
}


game::battlemon::updates::UpdateMessage &operator<<(game::battlemon::updates::UpdateMessage &grpcUpdateMessage, const FUUpdateMessage &UE)
{
	switch (UE.update_case)
	{
	case FUUpdateCase::kRoomNeedAccept:
	{
		game::battlemon::updates::RoomNeedAccept* go = new game::battlemon::updates::RoomNeedAccept();
		*go << UE.room_need_accept;
		grpcUpdateMessage.set_allocated_room_need_accept(go);
	}
		break;
	case FUUpdateCase::kRoomAcceptingCanceled:
	{
		game::battlemon::common::Empty* go = new game::battlemon::common::Empty();
		*go << UE.room_accepting_canceled;
		grpcUpdateMessage.set_allocated_room_accepting_canceled(go);
	}
		break;
	case FUUpdateCase::kRoomFound:
	{
		game::battlemon::updates::RoomInfo* go = new game::battlemon::updates::RoomInfo();
		*go << UE.room_found;
		grpcUpdateMessage.set_allocated_room_found(go);
	}
		break;
	case FUUpdateCase::kRoomTeammates:
	{
		game::battlemon::updates::RoomInfo* go = new game::battlemon::updates::RoomInfo();
		*go << UE.room_teammates;
		grpcUpdateMessage.set_allocated_room_teammates(go);
	}
		break;
	case FUUpdateCase::kRoomReady:
	{
		game::battlemon::updates::RoomInfo* go = new game::battlemon::updates::RoomInfo();
		*go << UE.room_ready;
		grpcUpdateMessage.set_allocated_room_ready(go);
	}
		break;
	case FUUpdateCase::kUserIsAlreadyInLine:
	{
		game::battlemon::common::Empty* go = new game::battlemon::common::Empty();
		*go << UE.user_is_already_in_line;
		grpcUpdateMessage.set_allocated_user_is_already_in_line(go);
	}
		break;
	case FUUpdateCase::kUserIsAlreadyInBattle:
	{
		game::battlemon::updates::RoomInfo* go = new game::battlemon::updates::RoomInfo();
		*go << UE.user_is_already_in_battle;
		grpcUpdateMessage.set_allocated_user_is_already_in_battle(go);
	}
		break;
	case FUUpdateCase::kUserOutOfLine:
	{
		game::battlemon::common::Empty* go = new game::battlemon::common::Empty();
		*go << UE.user_out_of_line;
		grpcUpdateMessage.set_allocated_user_out_of_line(go);
	}
		break;
	}
	return grpcUpdateMessage;
}


game::battlemon::updates::Update &operator<<(game::battlemon::updates::Update &grpcUpdate, const FUUpdate &UE)
{
	{
		grpcUpdate.set_id(CONV_FSTRING_TO_CHAR(UE.id));
	}
	{
		grpcUpdate.set_timestamp(UE.timestamp);
	}
	{
		grpcUpdate.set_message(CONV_FSTRING_TO_CHAR(UE.message));
	}
	return grpcUpdate;
}

