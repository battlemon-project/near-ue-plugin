#pragma once

enum class TypeInp
{
	AUTHORIZATION,
	REGISTRATION,
};


class Client
{
	char* accountID;
	char* network;
	char* sing;
	void* keyPair;
	char* keyPub58;
	char* error;

	void RegistrKey();
	bool AuthServiceClient();
public:

	Client(const char* dir, const char* inpText, TypeInp type);
	~Client();
	Client() = delete;

	char* GetPublicKey() const { return keyPub58; };
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	char* GetAccount() { return accountID; };
	char* GetError() { return error; };
	const char* GetSing(){ return sing; };
};

