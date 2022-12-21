#include"mm.h"

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


FUSearchGameResponse& FUSearchGameResponse::operator=(const game::battlemon::mm::SearchGameResponse& grpcSearchGameResponse)
{
	status << grpcSearchGameResponse.status();
	return *this;
}


FUAcceptGameRequest& FUAcceptGameRequest::operator=(const game::battlemon::mm::AcceptGameRequest& grpcAcceptGameRequest)
{
	lemon_id = CONV_CHAR_TO_FSTRING(grpcAcceptGameRequest.lemon_id().c_str());
	return *this;
}


FUCancelSearchRequest& FUCancelSearchRequest::operator=(const game::battlemon::mm::CancelSearchRequest& grpcCancelSearchRequest)
{
	return *this;
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


game::battlemon::mm::SearchGameResponse &operator<<(game::battlemon::mm::SearchGameResponse &grpcSearchGameResponse, const FUSearchGameResponse &UE)
{
	{
		game::battlemon::mm::SearchGameResponseStatus go;
		go << UE.status;
		grpcSearchGameResponse.set_status(go);
	}
	return grpcSearchGameResponse;
}


game::battlemon::mm::AcceptGameRequest &operator<<(game::battlemon::mm::AcceptGameRequest &grpcAcceptGameRequest, const FUAcceptGameRequest &UE)
{
	{
		grpcAcceptGameRequest.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	return grpcAcceptGameRequest;
}


game::battlemon::mm::CancelSearchRequest &operator<<(game::battlemon::mm::CancelSearchRequest &grpcCancelSearchRequest, const FUCancelSearchRequest &UE)
{
	return grpcCancelSearchRequest;
}

