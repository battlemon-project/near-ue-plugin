#include"auth.h"

FUSendCodeRequest& FUSendCodeRequest::operator=(const game::battlemon::auth::SendCodeRequest& grpcSendCodeRequest)
{
	public_key = CONV_CHAR_TO_FSTRING(grpcSendCodeRequest.public_key().c_str());
	return *this;
}


FUSendCodeResponse& FUSendCodeResponse::operator=(const game::battlemon::auth::SendCodeResponse& grpcSendCodeResponse)
{
	code = CONV_CHAR_TO_FSTRING(grpcSendCodeResponse.code().c_str());
	return *this;
}


FUVerifyCodeRequest& FUVerifyCodeRequest::operator=(const game::battlemon::auth::VerifyCodeRequest& grpcVerifyCodeRequest)
{
	public_key = CONV_CHAR_TO_FSTRING(grpcVerifyCodeRequest.public_key().c_str());
	sign = CONV_CHAR_TO_FSTRING(grpcVerifyCodeRequest.sign().c_str());
	return *this;
}


FUVerifyCodeResponse& FUVerifyCodeResponse::operator=(const game::battlemon::auth::VerifyCodeResponse& grpcVerifyCodeResponse)
{
	near_account_id = CONV_CHAR_TO_FSTRING(grpcVerifyCodeResponse.near_account_id().c_str());
	return *this;
}



game::battlemon::auth::SendCodeRequest &operator<<(game::battlemon::auth::SendCodeRequest &grpcSendCodeRequest, const FUSendCodeRequest &UE)
{
	{
		grpcSendCodeRequest.set_public_key(CONV_FSTRING_TO_CHAR(UE.public_key));
	}
	return grpcSendCodeRequest;
}


game::battlemon::auth::SendCodeResponse &operator<<(game::battlemon::auth::SendCodeResponse &grpcSendCodeResponse, const FUSendCodeResponse &UE)
{
	{
		grpcSendCodeResponse.set_code(CONV_FSTRING_TO_CHAR(UE.code));
	}
	return grpcSendCodeResponse;
}


game::battlemon::auth::VerifyCodeRequest &operator<<(game::battlemon::auth::VerifyCodeRequest &grpcVerifyCodeRequest, const FUVerifyCodeRequest &UE)
{
	{
		grpcVerifyCodeRequest.set_public_key(CONV_FSTRING_TO_CHAR(UE.public_key));
	}
	{
		grpcVerifyCodeRequest.set_sign(CONV_FSTRING_TO_CHAR(UE.sign));
	}
	return grpcVerifyCodeRequest;
}


game::battlemon::auth::VerifyCodeResponse &operator<<(game::battlemon::auth::VerifyCodeResponse &grpcVerifyCodeResponse, const FUVerifyCodeResponse &UE)
{
	{
		grpcVerifyCodeResponse.set_near_account_id(CONV_FSTRING_TO_CHAR(UE.near_account_id));
	}
	return grpcVerifyCodeResponse;
}

