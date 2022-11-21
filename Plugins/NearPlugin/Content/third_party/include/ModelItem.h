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
	bool owner;
public:

	ObjectList(int size) :list(nullptr), size(size), owner(true)
	{
		//owner++;
		if (size > 0)
			this->list = new TargetClassList[size];
		else
			list = nullptr;
	};
	ObjectList(TargetClassList* list, int size) : list(list), size(size), owner(true){};
	ObjectList(ObjectList& objectList) :list(nullptr), size(objectList.size), owner(true)
	{
		if (size > 0)
		{
			list = new TargetClassList[size];
			for (int i = 0; i < size; i++)
			{
				list[i] = objectList.list[i];
			}
		}
	}
	ObjectList() : list(nullptr), size(-1), owner(true) {};
	~ObjectList()
	{
		if (list != nullptr && owner)
			delete[]list;
		list = nullptr;
	}

	ObjectList& operator=(const ObjectList& copyObjectList)
	{
		size = copyObjectList.getSize();
		owner = true;
		if (size > 0)
		{
			list = new TargetClassList[size];
			for (int i = 0; i < size; i++)
			{
				list[i] = copyObjectList.list[i];
			}
		}
		return *this;
	};
	TargetClassList& operator[](const int& index)
	{
		return list[index];
	};
	const int& getSize() const { return size; };
	TargetClassList* getObjectPtr() const { return list; };
	TargetClassList& getObject(int id) const
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
		//else
		//{
		//	TargetClassList* buff = list;
		//	list = new TargetClassList[++index];
		//	for (size_t i = 0; i < size; i++)
		//	{
		//		list[i] = buff[i];
		//	}
		//	list[index] = buff[index];
		//	size = index;
		//}
	}
	bool setObjectList(TargetClassList* TargetClass, int size)
	{
		if (list == nullptr)
		{
			this->size = size;
			owner = true;
			list = TargetClass;
			return true;
		}
		return false;
	}
	TargetClassList* release() { owner = false; return list; };
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
		const GameMode* const game_mode;
		SearchGameRequest(const GameMode* game_mode);
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
		const TYPE_CHAR* const lemon_id;
		AcceptGameRequest(const TYPE_CHAR* lemon_id);
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

	enum class Model
	{
		LEMON,
		OUTFIT_MODEL,
		DEFAULT
	};

	class OutfitModel
	{

	public:
		bool copy;
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
		bool copy;
		WeaponBundleItemType item_type;
		TYPE_CHAR* skin;
		WeaponBundleSlotType slot_type;

		ModelItems::WeaponBundleItem& operator=(const ModelItems::WeaponBundleItem& from);

		WeaponBundleItem();
		WeaponBundleItem(bool copy);
		WeaponBundleItem(WeaponBundleItemType item_type, WeaponBundleSlotType slot_type, TYPE_CHAR* skin);
		WeaponBundleItem(const WeaponBundleItem& copy);
		~WeaponBundleItem();
	};

	struct WeaponBundle
	{
		bool copy;
		int bundle_num;
		ObjectList<WeaponBundleItem> WeaponList;

		TYPE_CHAR* title;
		int level;

		ModelItems::WeaponBundle& operator=(const ModelItems::WeaponBundle& from);

		WeaponBundle();
		WeaponBundle(int size_WeaponList, bool copy);
		WeaponBundle(WeaponBundleItem* WeaponList, int size_WeaponList, bool copy);
		WeaponBundle(const WeaponBundle& copy);
		~WeaponBundle();

	};

	class LemonModel
	{

	public:
		bool copy;
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
		Model model;
		TYPE_CHAR* token_id;
		TYPE_CHAR* media;
		TYPE_CHAR* owner_id;
		bool in_fight;
		LemonModel lemon;
		OutfitModel outfit;

		Item();
		Item(void* item, bool copy);
		Item(const ModelItems::Item& copyItem);
		ModelItems::Item& operator=(const ModelItems::Item& from);

		~Item();
	private:
		bool copy;
	};

	class EditBundleRequest
	{
	public:
		const int* const bundle_num;
		const ObjectList<ModelItems::WeaponBundleItem>* const items;
		const TYPE_CHAR* const title;

		EditBundleRequest(const int& bundle_num, const TYPE_CHAR* const title, ObjectList<ModelItems::WeaponBundleItem>* const items);
	};

	class AttachBundleRequest
	{
	public:
		const signed int* const bundle_num;
		const TYPE_CHAR* const lemon_id;

		AttachBundleRequest(const signed int& bundle_num, const TYPE_CHAR* lemon_id);
	};

	class DetachBundleRequest :public AttachBundleRequest
	{
	public:
		DetachBundleRequest(const signed int& bundle_num, const TYPE_CHAR* lemon_id);
	};
}

namespace ModelInternalMM
{
	struct InternalUserLeftBattleRequest
	{
		const TYPE_CHAR* const near_id;
		const TYPE_CHAR* const room_id;
		InternalUserLeftBattleRequest(const TYPE_CHAR* const near_id, const TYPE_CHAR* const room_id);
	};

	struct InternalPlayerResult
	{
		const TYPE_CHAR* near_id;
		const int* place;
	};

	struct SaveBattleResultRequest
	{
		const TYPE_CHAR* const room_id;
		const ObjectList<ModelInternalMM::InternalPlayerResult>* const results;
		SaveBattleResultRequest(const TYPE_CHAR* const room_id, const ObjectList<ModelInternalMM::InternalPlayerResult>* const results);
	};

	struct RoomInfoRequest
	{
		const TYPE_CHAR* const room_id;
		RoomInfoRequest(const TYPE_CHAR* const room_id);
	};

	struct RoomPlayerInfo
	{
		bool copy;
		TYPE_CHAR* near_id;
		ModelItems::Item lemon;
		RoomPlayerInfo();
		RoomPlayerInfo(const ModelInternalMM::RoomPlayerInfo& copy);
		~RoomPlayerInfo();
	};

	struct RoomInfoResponse
	{
		bool copy;
		TYPE_CHAR* room_id;
		ModelMM::GameMode mode;
		ObjectList<ModelInternalMM::RoomPlayerInfo> players;

		RoomInfoResponse(void* readRoomInfoResponsePtr, bool copy);
		RoomInfoResponse(const ModelInternalMM::RoomInfoResponse& copy);
		RoomInfoResponse();
		~RoomInfoResponse();
	};

	struct CreateRoomRequest
	{
		const ModelMM::GameMode *const mode;
		const ObjectList<const TYPE_CHAR*>* const near_ids;
		CreateRoomRequest(const ModelMM::GameMode* mode, const ObjectList<const TYPE_CHAR*>* const near_ids);
	};

	struct DedicatedServerIsReadyRequest
	{
		const TYPE_CHAR* const room_id;
		DedicatedServerIsReadyRequest(const TYPE_CHAR* const room_id);
	};
}

namespace ModelUpdates
{
	struct MessageData
	{
		void* Data;
		unsigned long ByteSize;
	};

	struct Update
	{
		TYPE_CHAR* id; // update id
		long long timestamp; // millisec
		TYPE_CHAR* message; //UpdateMessage's bytes in base64
	};

	struct RoomPlayer
	{
		TYPE_CHAR* near_id;
		ModelItems::Item lemon;
	};

	struct RoomNeedAccept
	{
		bool manual_accept;
		int time_to_accept;
	};

	struct RoomInfo
	{
		TYPE_CHAR* room_id;
		TYPE_CHAR* server_ip;
		ObjectList<ModelUpdates::RoomPlayer>* players;
	};

	enum class UpdateCase
	{
		ROOM_NEED_ACCEPT,
		ROOM_ACCEPTING_CANCELED,
		ROOM_FOUND,
		ROOM_TEAMMATES,
		ROOM_READY,
		DEFAULT
	};

	struct UpdateMessage
	{
		UpdateCase update;
		RoomNeedAccept room_need_accept;
		bool room_accepting_canceled;
		RoomInfo room_found;
		RoomInfo room_teammates;
		RoomInfo room_ready;
	};
}



namespace Type_Call_gRPC
{
	//items.proto
	enum class Type_gRPCItem : char
	{
		NONE,

		//items.proto
		GET_ITEMS,							//return ItemsResponse
		GET_BUNDLES,						//return GetBundlesResponse
		EDIT_BUNDLE,						//return WeaponBundle
		ATTACH_BUNDLE,						//return common.Empty
		DETACH_BUNDLE						//return common.Empty
	};

	enum class Type_gRPC_Auth : char
	{
		AUTHORIZATION,
		REGISTRATION
	};

	enum class Type_gRPC_MM : char
	{
		NONE,
		SEARCH_GAME,						//return SearchGameResponse
		ACCEPT_GAME,						//return common.Empty
		CANCEL_SEARCH,						//return common.Empty

	};

	enum class Type_gRPC_InternalMM : char
	{
		NONE,
		USER_LEFT_BATTLE,					//returns(common.Empty);
		SAVE_BATTLE_RESULT,					//returns(common.Empty);
		GET_ROOM_INFO,						//returns(RoomInfoResponse);
		CREATE_ROOM_WITH_PLAYERS,			//returns(RoomInfoResponse);
		DEDICATED_SERVER_IS_READY			//common.Empty
	};
	
}