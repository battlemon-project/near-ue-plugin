#pragma once

class EdKeysInterfase
{

	char* StrPubKey58;

public:
	EdKeysInterfase();
	~EdKeysInterfase();
	void GeneratingKeys();
	void SaveKeys(const char* accountID, const char* network);
	void LoadKeys(const char* accountID, const char* network);
	char* GetStrPubKey()const;
};

