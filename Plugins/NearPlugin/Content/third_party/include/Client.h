#pragma once
#include "include/ModelItem.h"
#if PLATFORM_WINDOWS
#define __APPLE__ 0
#define _WIN32 1
#define __linux__ 0
#elif PLATFORM_MAC
#define __APPLE__ 1
#define _WIN32 0
#define __linux__ 0
#elif PLATFORM_LINUX
#define __APPLE__ 0
#define _WIN32 0
#define __linux__ 1
#endif

#if __linux__
#define _GLIBCXX_USE_CXX11_ABI 0
#endif

#if _WIN32
#define TYPE_CHAR char
#else
#define TYPE_CHAR char16_t
#endif



class ItemsList
{
	ModelItems::Item* items;
public:

	const int size;
	ItemsList(ModelItems::Item* &items, int size);
	ItemsList(const ItemsList& itemsList);
	ItemsList() = delete;
	~ItemsList();

	ModelItems::Item& getItem(int id);
};

// повторяет структуру message PlayerItems
struct PlayerItemsClient
{
	char** near_id = nullptr;
	char*** items = nullptr;
	int players_items_size;
	int nft_ids_size;
	~PlayerItemsClient();
};

enum class TypeInp
{
	AUTHORIZATION,
	REGISTRATION,
};


class Client
{
	char* accountID;
	char* network;
	char* sign;
	void* keyPair;
	char* keyPub58;
	char* error;

public:

	Client(const TYPE_CHAR* dir, const TYPE_CHAR* inpText, TypeInp type);

	~Client();
	Client() = delete;

	char* GetPublicKey() const { return keyPub58; };
	bool IsValidAccount() { return accountID != nullptr; };
	bool IsValidKeys();
	char* GetAccount() { return accountID; };
	char* GetError() { return error; };
	const char* GetSing(){ return sign; };

	void gRPC_getPlayerItems(const TYPE_CHAR* room_id, int number_of_near_ids, const TYPE_CHAR** near_ids, PlayerItemsClient& playerItemsClient);
	void gRPC_SetMyItems(const TYPE_CHAR* room_id, int number_of_nft_ids, const TYPE_CHAR** nft_ids);
	ItemsList gRPC_GetItems();

	bool AuthServiceClient();
	void saveKey(const TYPE_CHAR* dir);
};

