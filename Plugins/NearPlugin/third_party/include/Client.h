#pragma once

class Client
{
	char* accountID;
	const char* network;
	void* keyPair;

	void RegistrKey();
	bool AuthServiceClient();
public:
	Client(const char* accountID, const char* network);
	Client(const char* network);
	~Client();
	Client() = delete;
	//char* GetPublicKey() const;
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	char* GetAccount() { return accountID; };
};

