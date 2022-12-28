// Fill out your copyright notice in the Description page of Project Settings.

#include"gRPC_Auth.h"
#include "NearAuth.h"
#include "gRPC_Base.h"


/// auth.rpc
gRPC_ClientAuth::gRPC_ClientAuth(const bool& ssl, FString& url):gRPC_Stub(ssl, url)
{
}


game::battlemon::auth::SendCodeResponse gRPC_ClientAuth::CallRPCSendCode(game::battlemon::auth::SendCodeRequest* Request)
{
    game::battlemon::auth::SendCodeResponse read;
    grpc::ClientContext context;

    UE_LOG_REQUEST("%c", static_cast<const char*>(Request->public_key().c_str()));

    CheckError(stub.get()->SendCode(&context, *Request, &read));
    return read;
}

game::battlemon::auth::VerifyCodeResponse gRPC_ClientAuth::CallRPCVerifyCode(game::battlemon::auth::VerifyCodeRequest* Request)
{
    game::battlemon::auth::VerifyCodeResponse read;
    grpc::ClientContext context;

    UE_LOG_REQUEST("%c%c", static_cast<const char*>(Request->public_key().c_str()), static_cast<const char*>(Request->sign().c_str()));

    CheckError(stub.get()->VerifyCode(&context, *Request, &read));
    return read;
}

/// auth.rpc end
