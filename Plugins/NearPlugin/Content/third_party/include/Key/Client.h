#pragma once

#if defined(_WIN32)
#define TYPE_CHAR wchar_t
#else
#define TYPE_CHAR char16_t
#endif

enum class TypeClient
{
	NONE,
	NEW,
	OLD
};

class Client
{
	const TYPE_CHAR* accountID;
	void* keyPair;
	TYPE_CHAR* keyPub58;
	TYPE_CHAR* error;

public:

	Client(const TYPE_CHAR* dir, const TYPE_CHAR* inpText, TypeClient& type);

	~Client();
	Client() = delete;

	TYPE_CHAR* GetPublicKey() const { return keyPub58; };
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	const TYPE_CHAR* GetAccount() const { return accountID; };
	void SetAccount(const TYPE_CHAR* _accountID) { accountID = _accountID; };
	TYPE_CHAR* GetError() const { return error; };
	const char* GetSing() const;

	void SaveKey(const TYPE_CHAR* dir);

	void SaveSign(const TYPE_CHAR* dir, const TYPE_CHAR* sign);
	const char* CreateMessageNewSign(const char* Message);
};