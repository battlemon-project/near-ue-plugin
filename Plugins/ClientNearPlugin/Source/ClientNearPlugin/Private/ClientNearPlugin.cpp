// Copyright Epic Games, Inc. All Rights Reserved.

#include "ClientNearPlugin.h"

#define LOCTEXT_NAMESPACE "FClientNearPluginModule"
#include "Misc/Paths.h"



void FClientNearPluginModule::StartupModule()
{
}

void FClientNearPluginModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FClientNearPluginModule, NearPlugin)