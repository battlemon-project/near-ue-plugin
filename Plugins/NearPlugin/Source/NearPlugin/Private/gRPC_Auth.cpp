// Fill out your copyright notice in the Description page of Project Settings.

#include"gRPC_Auth.h"
#include "NearAuth.h"
#include "gRPC_Base.h"

/// auth.rpc
gRPC_ClientAuth::gRPC_ClientAuth(const bool& ssl, FString& url):gRPC_Stub(ssl, url)
{
}


game::battlemon::auth::SendCodeResponse gRPC_ClientAuth::AsyncCallRPCSendCode(const game::battlemon::auth::SendCodeRequest& Request)
{
    game::battlemon::auth::SendCodeResponse read;

    grpc::ClientContext context;
    grpc::CompletionQueue cq;
    AsyncCallRPC<game::battlemon::auth::SendCodeResponse>(cq, &read, stub.get()->AsyncSendCode(&context, Request, &cq));
    return read;
}

game::battlemon::auth::VerifyCodeResponse gRPC_ClientAuth::AsyncCallRPCVerifyCode(const game::battlemon::auth::VerifyCodeRequest& Request)
{
    game::battlemon::auth::VerifyCodeResponse read;
    grpc::ClientContext context;
    grpc::CompletionQueue cq;

    AsyncCallRPC<game::battlemon::auth::VerifyCodeResponse>(cq, &read, stub.get()->AsyncVerifyCode(&context, Request, &cq));
    return read;
}

game::battlemon::auth::SendCodeResponse gRPC_ClientAuth::CallRPCSendCode(const game::battlemon::auth::SendCodeRequest& Request)
{
    game::battlemon::auth::SendCodeResponse read;
    grpc::ClientContext context;

    CallRPC(stub.get()->SendCode(&context, Request, &read));
    return read;
}

game::battlemon::auth::VerifyCodeResponse gRPC_ClientAuth::CallRPCVerifyCode(const game::battlemon::auth::VerifyCodeRequest& Request)
{
    game::battlemon::auth::VerifyCodeResponse read;
    grpc::ClientContext context;

    CallRPC(stub.get()->VerifyCode(&context, Request, &read));
    return read;
}

/// auth.rpc end
