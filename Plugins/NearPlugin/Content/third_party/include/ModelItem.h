#pragma once

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

#if _WIN32
#define TYPE_CHAR char
#else
#define TYPE_CHAR char16_t
#endif

template <typename TargetClassList>
class ObjectList
{
	TargetClassList* list;
	int size;
	//static int owner;
public:

	ObjectList(int size) : size(size), list(nullptr)
	{
		//owner++;
		if (size > 0)
			this->list = new TargetClassList[size];
		else
			list = nullptr;
	};
	ObjectList(TargetClassList* list, int size) : list(list), size(size) {};
	ObjectList(const ObjectList& objectList) : size(objectList.size), list(nullptr)
	{
		//owner++;
		if (size != -1)
		{
			list = new TargetClassList[size];
			for (int i = 0; i < size; i++)
			{
				list[i] = objectList.list[i];
			}
		}
	}
	ObjectList() : list(nullptr), size(-1) {};
	~ObjectList()
	{
		//owner--;
		if (list != nullptr /*&& owner == 0*/)
			delete[]list;
		list = nullptr;
	}

	ObjectList& operator=(const ObjectList& copyObjectList)
	{
		size = copyObjectList.getSize();
		//owner++;
		if (size != -1)
		{
			list = new TargetClassList[size];
			for (int i = 0; i < size; i++)
			{
				list[i] = copyObjectList.list[i];
			}
		}
		return *this;
	};

	int getSize() const { return size; };
	TargetClassList* getObjectPtr() { return list; };
	TargetClassList& getObject(int id)
	{
		return list[id];
	};
	void setObject(TargetClassList TargetClass, int index)
	{
		if (index < size)
		{
			if (list != nullptr)
			{
				list[index] = TargetClass;
			}
			else
			{
				list = new TargetClassList[size];
				list[index] = TargetClass;
			}
		}
	}
};


namespace ModelMM
{

	enum class MatchType
	{
		DEATH_MATCH = 0,
		CATCH_THE_FLAG = 1,
		DEFAULT = 2
	};

	enum class MatchMode
	{
		NONE = 0,
		EQUIPMENT = 1,
		REALISM = 2,
		DEFAULT = 3
	};

	struct GameMode
	{
		MatchType match_type;
		MatchMode match_mode;
	};

	struct SearchGameRequest
	{
		GameMode game_mode;
	};

	enum class SearchGameResponseStatus
	{
		OK = 0,
		NFT_ERROR = 1,
		ALREADY_IN_QUEUE = 2,
		ALREADY_IN_BATTLE = 3,
		GAMEMODE_ERROR = 4,
		INVALID_REQUEST = 5,
		INTERNAL_ERROR = 6,
		DEFAULT = 7
	};

	struct SearchGameResponse
	{
		SearchGameResponseStatus status;
	};

	struct AcceptGameRequest
	{
		TYPE_CHAR* lemon_id;
	};

	class CancelSearchRequest
	{
	};
}

namespace ModelItems
{
	enum class OutfitKind
	{
		CAP = 0,
		CLOTH = 1,
		FIRE_ARM = 2,
		COLD_ARM = 3,
		BACK = 4,
		DEFAULT = 5
	};

	class OutfitModel
	{
		bool copy;

	public:
		TYPE_CHAR* flavour;
		TYPE_CHAR* token_id;
		OutfitKind kind;


		ModelItems::OutfitModel& operator=(const ModelItems::OutfitModel& from);

		OutfitModel(bool copy);
		OutfitModel(const OutfitModel& copy);
		~OutfitModel();
	};

	enum class WeaponBundleItemType
	{
		NONE,
		BUNDLE_ITEM_PRIMARY,
		BUNDLE_ITEM_SECONDARY,
		BUNDLE_ITEM_MELEE,
		BUNDLE_ITEM_TACTICAL,
		BUNDLE_ITEM_MILITARY,
		BUNDLE_ITEM_PERK
	};

	enum class WeaponBundleSlotType
	{
		NONE,
		BUNDLE_SLOT_PRIMARY,
		BUNDLE_SLOT_SECONDARY,
		BUNDLE_SLOT_MELEE,
		BUNDLE_SLOT_TACTICAL_ONE,
		BUNDLE_SLOT_TACTICAL_TWO,
		BUNDLE_SLOT_MILITARY_ONE,
		BUNDLE_SLOT_MILITARY_TWO,
		BUNDLE_SLOT_PERK_ONE,
		BUNDLE_SLOT_PERK_TWO
	};

	struct WeaponBundleItem
	{
		WeaponBundleItemType item_type;
		TYPE_CHAR* skin;
		WeaponBundleSlotType slot_type;

		ModelItems::WeaponBundleItem& operator=(const ModelItems::WeaponBundleItem& from);

		WeaponBundleItem();
		WeaponBundleItem(WeaponBundleItemType item_type, WeaponBundleSlotType slot_type, TYPE_CHAR* skin);
		WeaponBundleItem(const WeaponBundleItem& copy);
		~WeaponBundleItem();
	};

	struct WeaponBundle
	{
		int bundle_num;
		ObjectList<WeaponBundleItem> WeaponList;

		TYPE_CHAR* title;
		int level;

		ModelItems::WeaponBundle& operator=(const ModelItems::WeaponBundle& from);

		WeaponBundle();
		WeaponBundle(int size_WeaponList);
		WeaponBundle(const WeaponBundle& copy);
		~WeaponBundle();

	};

	class LemonModel
	{
		bool copy;

	public:
		OutfitModel cap;
		OutfitModel cloth;
		TYPE_CHAR* exo;
		TYPE_CHAR* eyes;
		TYPE_CHAR* head;
		TYPE_CHAR* teeth;
		TYPE_CHAR* face;
		OutfitModel fire_arm;
		OutfitModel cold_arm;
		OutfitModel back;

		ObjectList<ModelItems::WeaponBundle> attached_bundles;

		ModelItems::LemonModel& operator=(const ModelItems::LemonModel& from);

		LemonModel(bool copy);
		LemonModel(int size_attached_bundles, int size_items[], bool copy);
		LemonModel(const LemonModel& copy);
		~LemonModel();
	};

	struct Item
	{
		TYPE_CHAR* token_id;
		TYPE_CHAR* media;
		TYPE_CHAR* owner_id;
		bool in_fight;
		LemonModel lemon;
		OutfitModel outfit;

		ModelItems::Item& operator=(const ModelItems::Item& from);

		Item();
		Item(void* item, int index, bool copy);
		Item(const Item& from);

		~Item();

		const bool copy;
	};

	class EditBundleRequest
	{
		const int bundle_num;
		ObjectList<ModelItems::WeaponBundleItem> items;
		const TYPE_CHAR* title;

	public:
		EditBundleRequest(int bundle_num, TYPE_CHAR* title, WeaponBundleItem* items, int size);

		const int& getBundle_num() const;
		ModelItems::WeaponBundleItem* getItems();
		const TYPE_CHAR* getTitle() const;
	};

	class AttachBundleRequest
	{
		const int bundle_num;
		const TYPE_CHAR* lemon_id;

	public:
		AttachBundleRequest(const int& bundle_num, const TYPE_CHAR*& lemon_id);
		const int& get_bundle_num() const;
		const TYPE_CHAR* get_lemon_id() const;
	};

	class DetachBundleRequest :public AttachBundleRequest
	{
	public:
		DetachBundleRequest(const int& bundle_num, const TYPE_CHAR*& lemon_id);
	};
}

namespace Type_Call_gRPC
{
	//items.proto
	enum class Type_gRPCItem
	{
		NONE,

		//items.proto
		GET_ITEMS,							//return ItemsResponse
		GET_BUNDLES,						//return GetBundlesResponse
		EDIT_BUNDLE,						//return WeaponBundle
		ATTACH_BUNDLE,						//return common.Empty
		DETACH_BUNDLE						//return common.Empty
	};

	enum class Type_gRPC_Auth
	{
		AUTHORIZATION,
		REGISTRATION
	};

	enum class Type_gRPC_MM
	{
		NONE,
		SEARCH_GAME,						//return SearchGameResponse
		ACCEPT_GAME,						//return common.Empty
		CANCEL_SEARCH						//return common.Empty
	};
}