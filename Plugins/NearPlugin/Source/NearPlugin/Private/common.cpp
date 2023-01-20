#include"common.h"
#include "AsyncTask.h"

FUSortOrder& operator<<(FUSortOrder &UE, const game::battlemon::common::SortOrder& grpc)
{
	UE = FUSortOrder::Default;
	switch (grpc)
	{
	case game::battlemon::common::SortOrder::ASC:
		UE = FUSortOrder::ASC;
		break;
	case game::battlemon::common::SortOrder::DESC:
		UE = FUSortOrder::DESC;
		break;
	}
	return UE;
}


FUStatus& operator<<(FUStatus &UE, const game::battlemon::common::Status& grpc)
{
	UE = FUStatus::Default;
	switch (grpc)
	{
	case game::battlemon::common::Status::OK:
		UE = FUStatus::OK;
		break;
	case game::battlemon::common::Status::SYSTEM_ERROR:
		UE = FUStatus::SYSTEM_ERROR;
		break;
	}
	return UE;
}


FUServiceStatus& operator<<(FUServiceStatus &UE, const game::battlemon::common::ServiceStatus& grpc)
{
	UE = FUServiceStatus::Default;
	switch (grpc)
	{
	case game::battlemon::common::ServiceStatus::SUCCESS:
		UE = FUServiceStatus::SUCCESS;
		break;
	case game::battlemon::common::ServiceStatus::INTERNAL_ERROR:
		UE = FUServiceStatus::INTERNAL_ERROR;
		break;
	case game::battlemon::common::ServiceStatus::BAD_REQUEST:
		UE = FUServiceStatus::BAD_REQUEST;
		break;
	}
	return UE;
}


FURarity& operator<<(FURarity &UE, const game::battlemon::common::Rarity& grpc)
{
	UE = FURarity::Default;
	switch (grpc)
	{
	case game::battlemon::common::Rarity::COMMON:
		UE = FURarity::COMMON;
		break;
	case game::battlemon::common::Rarity::RARE:
		UE = FURarity::RARE;
		break;
	case game::battlemon::common::Rarity::EPIC:
		UE = FURarity::EPIC;
		break;
	case game::battlemon::common::Rarity::LEGENDARY:
		UE = FURarity::LEGENDARY;
		break;
	}
	return UE;
}


FUFaction& operator<<(FUFaction &UE, const game::battlemon::common::Faction& grpc)
{
	UE = FUFaction::Default;
	switch (grpc)
	{
	case game::battlemon::common::Faction::FIRST:
		UE = FUFaction::FIRST;
		break;
	}
	return UE;
}


game::battlemon::common::SortOrder& operator<<(game::battlemon::common::SortOrder & grpc, const FUSortOrder &UE) 
{
	switch (UE)
	{
	case FUSortOrder::ASC:
		grpc = game::battlemon::common::SortOrder::ASC;
		break;
	case FUSortOrder::DESC:
		grpc = game::battlemon::common::SortOrder::DESC;
		break;
	}
	return grpc;
}


game::battlemon::common::Status& operator<<(game::battlemon::common::Status & grpc, const FUStatus &UE) 
{
	switch (UE)
	{
	case FUStatus::OK:
		grpc = game::battlemon::common::Status::OK;
		break;
	case FUStatus::SYSTEM_ERROR:
		grpc = game::battlemon::common::Status::SYSTEM_ERROR;
		break;
	}
	return grpc;
}


game::battlemon::common::ServiceStatus& operator<<(game::battlemon::common::ServiceStatus & grpc, const FUServiceStatus &UE) 
{
	switch (UE)
	{
	case FUServiceStatus::SUCCESS:
		grpc = game::battlemon::common::ServiceStatus::SUCCESS;
		break;
	case FUServiceStatus::INTERNAL_ERROR:
		grpc = game::battlemon::common::ServiceStatus::INTERNAL_ERROR;
		break;
	case FUServiceStatus::BAD_REQUEST:
		grpc = game::battlemon::common::ServiceStatus::BAD_REQUEST;
		break;
	}
	return grpc;
}


game::battlemon::common::Rarity& operator<<(game::battlemon::common::Rarity & grpc, const FURarity &UE) 
{
	switch (UE)
	{
	case FURarity::COMMON:
		grpc = game::battlemon::common::Rarity::COMMON;
		break;
	case FURarity::RARE:
		grpc = game::battlemon::common::Rarity::RARE;
		break;
	case FURarity::EPIC:
		grpc = game::battlemon::common::Rarity::EPIC;
		break;
	case FURarity::LEGENDARY:
		grpc = game::battlemon::common::Rarity::LEGENDARY;
		break;
	}
	return grpc;
}


game::battlemon::common::Faction& operator<<(game::battlemon::common::Faction & grpc, const FUFaction &UE) 
{
	switch (UE)
	{
	case FUFaction::FIRST:
		grpc = game::battlemon::common::Faction::FIRST;
		break;
	}
	return grpc;
}


FUResultStatus& FUResultStatus::operator=(const game::battlemon::common::ResultStatus& grpcResultStatus)
{
	status << grpcResultStatus.status();
	return *this;
}


FUResponse& FUResponse::operator=(const game::battlemon::common::Response& grpcResponse)
{
	status << grpcResponse.status();
	return *this;
}


FUEmpty& FUEmpty::operator=(const game::battlemon::common::Empty& grpcEmpty)
{
	return *this;
}



game::battlemon::common::ResultStatus &operator<<(game::battlemon::common::ResultStatus &grpcResultStatus, const FUResultStatus &UE)
{
	{
		game::battlemon::common::Status go;
		go << UE.status;
		grpcResultStatus.set_status(go);
	}
	return grpcResultStatus;
}


game::battlemon::common::Response &operator<<(game::battlemon::common::Response &grpcResponse, const FUResponse &UE)
{
	{
		game::battlemon::common::ServiceStatus go;
		go << UE.status;
		grpcResponse.set_status(go);
	}
	return grpcResponse;
}


game::battlemon::common::Empty &operator<<(game::battlemon::common::Empty &grpcEmpty, const FUEmpty &UE)
{
	return grpcEmpty;
}

