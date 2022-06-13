#pragma once
#include "EdKeys.h"

class Client
{
	char* accountID;
	const char* network;
	EdKeysInterfase keyPair;

	void RegistrKey();

public:
	Client(const char* accountID, const char* network);
	Client(const char* network);
	~Client();
	Client() = delete;
	char* GetPublicKey() const;
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys() { return keyPair.GetStrPubKey() != nullptr; };
	char* GetAccount() { return accountID; };
};

