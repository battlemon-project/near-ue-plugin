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
		TYPE_CHAR* flavour = nullptr;
		TYPE_CHAR* token_id = nullptr;
		OutfitKind kind;


		ModelItems::OutfitModel& operator=(const ModelItems::OutfitModel& from);

		OutfitModel(bool copy) :copy(copy) {};
		OutfitModel(const OutfitModel& copy)
		{
			flavour = copy.flavour;
			token_id = copy.token_id;
			kind = copy.kind;
		}
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

		WeaponBundleItem() :item_type(WeaponBundleItemType::NONE), skin(nullptr), slot_type(WeaponBundleSlotType::NONE) {};
		WeaponBundleItem(WeaponBundleItemType item_type, WeaponBundleSlotType slot_type, TYPE_CHAR* skin) : item_type(item_type), slot_type(slot_type), skin(skin){};
		WeaponBundleItem(const WeaponBundleItem& copy);
		~WeaponBundleItem() {};
	};

	struct WeaponBundle
	{
		int bundle_num;
		ObjectList<WeaponBundleItem> WeaponList;

		TYPE_CHAR* title;
		int level;

		ModelItems::WeaponBundle& operator=(const ModelItems::WeaponBundle& from);

		WeaponBundle() :bundle_num(-1), title(nullptr), level(-1), WeaponList(ObjectList<WeaponBundleItem>(-1)){};
		WeaponBundle(int size_WeaponList) : bundle_num(-1), title(nullptr), level(-1), WeaponList(size_WeaponList) {};
		WeaponBundle(const WeaponBundle& copy);
		~WeaponBundle()
		{
			WeaponList.~ObjectList();
		};

	};

	class LemonModel
	{
		bool copy;

	public:
		OutfitModel cap;
		OutfitModel cloth;
		TYPE_CHAR* exo = nullptr;
		TYPE_CHAR* eyes = nullptr;
		TYPE_CHAR* head = nullptr;
		TYPE_CHAR* teeth = nullptr;
		TYPE_CHAR* face = nullptr;
		OutfitModel fire_arm;
		OutfitModel cold_arm;
		OutfitModel back;

		ObjectList<ModelItems::WeaponBundle> attached_bundles;

		ModelItems::LemonModel& operator=(const ModelItems::LemonModel& from);

		LemonModel(bool copy) :copy(copy), cap(copy), cloth(copy), fire_arm(copy), cold_arm(copy), back(copy) {};
		LemonModel(int size_attached_bundles, int size_items[], bool copy) :attached_bundles(size_attached_bundles), copy(copy), cap(copy), cloth(copy), fire_arm(copy), cold_arm(copy), back(copy)
		{
			if (size_attached_bundles != -1)
			{
				for (int i = 0; i < size_attached_bundles; i++)
				{
					attached_bundles.setObject(WeaponBundle(size_items[i]), i);
				}
			}
		};
		LemonModel(const LemonModel& from);
		~LemonModel();
	};

	struct Item
	{
		TYPE_CHAR* token_id = nullptr;
		TYPE_CHAR* media = nullptr;
		TYPE_CHAR* owner_id = nullptr;
		bool in_fight;
		LemonModel lemon;
		OutfitModel outfit;

		ModelItems::Item& operator=(const ModelItems::Item& from);

		Item() :copy(true), lemon(true), outfit(true) {};
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
		EditBundleRequest(int bundle_num, TYPE_CHAR* title, WeaponBundleItem* items, int size) :bundle_num(bundle_num), items(items, size), title(title) {};

		const int& getBundle_num() const { return bundle_num; };
		ModelItems::WeaponBundleItem* getItems() { return items.getObjectPtr(); };
		const TYPE_CHAR* getTitle() const { return title; };
	};

	class AttachBundleRequest
	{
		const int bundle_num;
		const TYPE_CHAR* lemon_id;

	public:
		AttachBundleRequest(const int& bundle_num, const TYPE_CHAR*& lemon_id) :bundle_num(bundle_num), lemon_id(lemon_id) {};
		const int& get_bundle_num() const { return bundle_num; };
		const TYPE_CHAR* get_lemon_id() const { return lemon_id; };
	};

	class DetachBundleRequest :public AttachBundleRequest
	{
	public:
		DetachBundleRequest(const int& bundle_num, const TYPE_CHAR*& lemon_id) : AttachBundleRequest(bundle_num, lemon_id) {};
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