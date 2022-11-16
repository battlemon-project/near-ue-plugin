#pragma once
#include "include/ModelItem.h"

class Client
{
	char* accountID;
	char* sign;
	void* keyPair;
	char* keyPub58;
	char* error;
	
public:

	Client(const TYPE_CHAR* dir, const TYPE_CHAR* inpText, Type_Call_gRPC::Type_gRPC_Auth type);

	~Client();
	Client() = delete;

	char* GetPublicKey() const { return keyPub58; };
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	char* GetAccount() const { return accountID; };
	char* GetError() const { return error; };
	const char* GetSing() const { return sign; };

	void saveKey(const TYPE_CHAR* dir);
	bool AuthServiceClient();
};