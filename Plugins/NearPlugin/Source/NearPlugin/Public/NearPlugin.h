// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"


typedef void* v_dllHandle;
typedef size_t(*AuthorizedRust)(const char* pub_key_cpp, const char* account_id, const char* networkType);
DECLARE_LOG_CATEGORY_EXTERN(LogNear, Log, All);

class FNearPluginModule : public IModuleInterface
{
public:
	static FString path;
	v_dllHandle NearRust;
	static AuthorizedRust _AuthorizedRust;

protected:
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
