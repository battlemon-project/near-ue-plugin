#pragma once

/*enum TypeInp
{
	AUTHORIZATION,
	REGISTRATION,
};
*/

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

	Client(const char* inpText, bool type);
	~Client();
	Client() = delete;

	char* GetPublicKey() const { return keyPub58; };
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	char* GetAccount() { return accountID; };
	char* GetError() { return error; };
	bool VerifySing();
};

