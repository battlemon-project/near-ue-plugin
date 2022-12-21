#include"internalAuth.h"

FUInternalVerifySignStatus& operator<<(FUInternalVerifySignStatus &UE, const game::battlemon::auth::internal::InternalVerifySignStatus& grpc)
{
	UE = FUInternalVerifySignStatus::Default;
	switch (grpc)
	{
	case game::battlemon::auth::internal::InternalVerifySignStatus::OK:
		UE = FUInternalVerifySignStatus::OK;
		break;
	case game::battlemon::auth::internal::InternalVerifySignStatus::EXPIRED:
		UE = FUInternalVerifySignStatus::EXPIRED;
		break;
	case game::battlemon::auth::internal::InternalVerifySignStatus::INVALID_SIGN:
		UE = FUInternalVerifySignStatus::INVALID_SIGN;
		break;
	case game::battlemon::auth::internal::InternalVerifySignStatus::PK_NOT_FOUND:
		UE = FUInternalVerifySignStatus::PK_NOT_FOUND;
		break;
	case game::battlemon::auth::internal::InternalVerifySignStatus::PK_NOT_VERIFIED:
		UE = FUInternalVerifySignStatus::PK_NOT_VERIFIED;
		break;
	}
	return UE;
}


game::battlemon::auth::internal::InternalVerifySignStatus& operator<<(game::battlemon::auth::internal::InternalVerifySignStatus & grpc, const FUInternalVerifySignStatus &UE) 
{
	switch (UE)
	{
	case FUInternalVerifySignStatus::OK:
		grpc = game::battlemon::auth::internal::InternalVerifySignStatus::OK;
		break;
	case FUInternalVerifySignStatus::EXPIRED:
		grpc = game::battlemon::auth::internal::InternalVerifySignStatus::EXPIRED;
		break;
	case FUInternalVerifySignStatus::INVALID_SIGN:
		grpc = game::battlemon::auth::internal::InternalVerifySignStatus::INVALID_SIGN;
		break;
	case FUInternalVerifySignStatus::PK_NOT_FOUND:
		grpc = game::battlemon::auth::internal::InternalVerifySignStatus::PK_NOT_FOUND;
		break;
	case FUInternalVerifySignStatus::PK_NOT_VERIFIED:
		grpc = game::battlemon::auth::internal::InternalVerifySignStatus::PK_NOT_VERIFIED;
		break;
	}
	return grpc;
}


FUInternalVerifySignRequest& FUInternalVerifySignRequest::operator=(const game::battlemon::auth::internal::InternalVerifySignRequest& grpcInternalVerifySignRequest)
{
	near_account_id = CONV_CHAR_TO_FSTRING(grpcInternalVerifySignRequest.near_account_id().c_str());
	sign = CONV_CHAR_TO_FSTRING(grpcInternalVerifySignRequest.sign().c_str());
	return *this;
}


FUInternalVerifySignResponse& FUInternalVerifySignResponse::operator=(const game::battlemon::auth::internal::InternalVerifySignResponse& grpcInternalVerifySignResponse)
{
	status << grpcInternalVerifySignResponse.status();
	return *this;
}



game::battlemon::auth::internal::InternalVerifySignRequest &operator<<(game::battlemon::auth::internal::InternalVerifySignRequest &grpcInternalVerifySignRequest, const FUInternalVerifySignRequest &UE)
{
	{
		grpcInternalVerifySignRequest.set_near_account_id(CONV_FSTRING_TO_CHAR(UE.near_account_id));
	}
	{
		grpcInternalVerifySignRequest.set_sign(CONV_FSTRING_TO_CHAR(UE.sign));
	}
	return grpcInternalVerifySignRequest;
}


game::battlemon::auth::internal::InternalVerifySignResponse &operator<<(game::battlemon::auth::internal::InternalVerifySignResponse &grpcInternalVerifySignResponse, const FUInternalVerifySignResponse &UE)
{
	{
		game::battlemon::auth::internal::InternalVerifySignStatus go;
		go << UE.status;
		grpcInternalVerifySignResponse.set_status(go);
	}
	return grpcInternalVerifySignResponse;
}

