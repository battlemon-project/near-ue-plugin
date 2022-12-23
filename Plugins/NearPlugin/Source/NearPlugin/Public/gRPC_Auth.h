// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "gRPC_Base.h"

#include "GrpcBegin.h"
#include <protocol/auth.grpc.pb.h>
#include "GrpcEnd.h"



class gRPC_ClientAuth : public gRPC_Stub<game::battlemon::auth::AuthService, game::battlemon::auth::AuthService::Stub>
{
public:
	gRPC_ClientAuth(const bool& ssl, FString& url);

	game::battlemon::auth::SendCodeResponse CallRPCSendCode(const game::battlemon::auth::SendCodeRequest& Request);
	game::battlemon::auth::VerifyCodeResponse CallRPCVerifyCode(const game::battlemon::auth::VerifyCodeRequest& Request);
};
