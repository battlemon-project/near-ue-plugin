// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include <include/Client.h>

typedef void* v_dllHandle;
typedef size_t (*AuthorizedRust)(const char* pub_key_cpp, const char* account_id, const char* networkType);
/**
 * 
 */
class NEARPLUGIN_API UClient
{
	static Client* client;
	//static bool autoAuthorized;

	static void saveAccountId();
	static void loadAccountId(const char* networkType);

public:

	UClient();
	~UClient();

	static bool LoadDLL();
	static void FreeDLL();

	static bool RegistrationAccount(const char* networkType);
	static bool AuthorizedAccount(const char* AccountID, const char* networkType);
};
