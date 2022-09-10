#pragma once

namespace ModelItems
{
	enum OutfitKind
	{
		CAP = 0,
		CLOTH = 1,
		FIRE_ARM = 2,
		COLD_ARM = 3,
		BACK = 4,
		DEFAULT = 5
	};

	struct OutfitModel
	{
		char* flavour = nullptr;
		char* token_id = nullptr;
		OutfitKind kind;
		~OutfitModel();
	};

	struct LemonModel
	{
		OutfitModel cap;
		OutfitModel cloth;
		char* exo = nullptr;
		char* eyes = nullptr;
		char* head = nullptr;
		char* teeth = nullptr;
		char* face = nullptr;
		OutfitModel fire_arm;
		OutfitModel cold_arm;
		OutfitModel back;
		~LemonModel();
	};

	struct Item
	{
		char* token_id = nullptr;
		char* media = nullptr;
		char* owner_id = nullptr;
		LemonModel lemon;
		OutfitModel outfit;
		~Item();
	};
}