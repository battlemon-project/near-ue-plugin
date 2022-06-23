#pragma once

typedef bool(*Rewrite)(const char* path);

class Client
{
	char* accountID;
	const char* network;
	void* keyPair;
	char* keyPub58;
	char* error;

	void RegistrKey(Rewrite _Rewrite);
	bool AuthServiceClient();
public:

	Client(const char* accountID, const char* network, Rewrite _Rewrite);
	Client(const char* network, Rewrite _Rewrite);
	~Client();
	Client() = delete;

	char* GetPublicKey() const { return keyPub58; };
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	char* GetAccount() { return accountID; };
	char* GetError() { return error; };
};

