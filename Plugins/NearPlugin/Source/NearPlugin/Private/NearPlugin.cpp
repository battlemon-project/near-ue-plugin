// Copyright Epic Games, Inc. All Rights Reserved.

#include "NearPlugin.h"

#define LOCTEXT_NAMESPACE "FNearPluginModule"
#include "Misc/Paths.h"

DEFINE_LOG_CATEGORY(LogNear);
#define HANDLE_WINDOWS "near_lib.dll"
#define HANDLE_MAC "near_lib.dylib"
#define HANDLE_LINUX "near_lib.so"

#ifdef PLATFORM_WINDOWS
#define HANDLE_PATH "/Content/third_party/bin/" HANDLE_WINDOWS
#elif PLATFORM_MAC
#define HANDLE_PATH "/Content/third_party/bin/" HANDLE_MAC
#elif PLATFORM_LINUX
#define HANDLE_PATH "/Content/third_party/bin/" HANDLE_LINUX
#else
#error "Unknown platform"
#endif


AuthorizedRust FNearPluginModule::_AuthorizedRust = nullptr;
FString FNearPluginModule::path = "";

void FNearPluginModule::StartupModule()
{
	FString NearAuthPath = FPaths::ConvertRelativePathToFull(FPaths::ProjectPluginsDir()) + "NearPlugin" + TEXT(HANDLE_PATH);
	path = NearAuthPath;
	if (FPaths::FileExists(NearAuthPath))
	{
		NearRust = FPlatformProcess::GetDllHandle(*NearAuthPath);
		if (NearRust != nullptr)
		{
			UE_LOG(LogNear, Display, TEXT("%s: Library Rust loaded successfuly!"), ANSI_TO_TCHAR(__FUNCTION__));

			FString procName = "authorized";
			_AuthorizedRust = (AuthorizedRust)FPlatformProcess::GetDllExport(NearRust, *procName);
			if (_AuthorizedRust != nullptr)
			{
				UE_LOG(LogNear, Display, TEXT("%s: FAuthorized loaded successfuly!"), ANSI_TO_TCHAR(__FUNCTION__));
			}
			else
			{
				UE_LOG(LogNear, Error, TEXT("%s: Unable to locate handle_set_error_writer entry point!"), ANSI_TO_TCHAR(__FUNCTION__));
				return;
			}
		}
	}
	else
	{
		UE_LOG(LogNear, Error, TEXT("%s: Unable to locate handle_set_error_writer entry point!"), ANSI_TO_TCHAR(__FUNCTION__));
		return;
	}
}

void FNearPluginModule::ShutdownModule()
{
	if (NearRust != nullptr)
	{
		if (_AuthorizedRust != nullptr)
		{
			_AuthorizedRust = nullptr;
		}
		FPlatformProcess::FreeDllHandle(NearRust);
		NearRust = nullptr;
	}
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FNearPluginModule, NearPlugin)