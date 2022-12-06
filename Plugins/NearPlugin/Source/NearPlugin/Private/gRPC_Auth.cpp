// Fill out your copyright notice in the Description page of Project Settings.

#include"gRPC_Auth.h"
#include "NearAuth.h"
#include "gRPC_Base.h"

/// auth.rpc
gRPC_ClientAuth::gRPC_ClientAuth(const bool& ssl, FString& url):gRPC_Stub(ssl, url)
{
}


game::battlemon::auth::SendCodeResponse gRPC_ClientAuth::CallRPCSendCode(const game::battlemon::auth::SendCodeRequest& Request)
{
    game::battlemon::auth::SendCodeResponse read;

    grpc::ClientContext context;
    CallRPC<game::battlemon::auth::AuthService::Stub, game::battlemon::auth::SendCodeRequest, game::battlemon::auth::SendCodeResponse>(stub.get(), context, Request, &read, this->error, &game::battlemon::auth::AuthService::Stub::SendCode);
    return read;
}

game::battlemon::auth::VerifyCodeResponse gRPC_ClientAuth::CallRPCVerifyCode(const game::battlemon::auth::VerifyCodeRequest& Request)
{
    game::battlemon::auth::VerifyCodeResponse read;
    grpc::ClientContext context;
    CallRPC<game::battlemon::auth::AuthService::Stub, game::battlemon::auth::VerifyCodeRequest, game::battlemon::auth::VerifyCodeResponse>(stub.get(), context, Request, &read, this->error, &game::battlemon::auth::AuthService::Stub::VerifyCode);
    return read;
}

/// auth.rpc end
