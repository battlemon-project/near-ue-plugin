#pragma once
#include "include/ModelItem.h"
#include "include/Client.h"



template <typename Type_Call_gRPC>
class gRPC_Response
{
protected:

	const Client** client;
	void* gRPC_read;
	Type_Call_gRPC type_gRPC;
	char* error;

	virtual void free_gRPC() = 0;

public:
	bool IsValidResponse(Type_Call_gRPC& type_Call_gRPC) const
	{
		type_Call_gRPC = type_gRPC;
		return gRPC_read != nullptr;
	};

	Type_Call_gRPC GetCall_gRPC() const { return type_gRPC; };
	char* GetError() const { return error; };

	gRPC_Response(Client** client, Type_Call_gRPC type_gRPC) :client((const Client**)client), type_gRPC(type_gRPC), error(nullptr), gRPC_read(nullptr){};
	gRPC_Response() = delete;

	virtual ~gRPC_Response() {}
};


class gRPC_ResponseItem : public gRPC_Response<Type_Call_gRPC::Type_gRPCItem>
{
	void free_gRPC() override;

	//call server																													
	void CallRPC_GetItems();																										//return ItemsResponse
	void CallRPC_GetBundles();																										//return GetBundlesResponse
	void CallRPC_EditBundle(ModelItems::EditBundleRequest& request);		//return WeaponBundle
	void CallRPC_AttachBundle(ModelItems::AttachBundleRequest& request);												//return common.Empty
	void CallRPC_DetachBundle(ModelItems::DetachBundleRequest& request);												//return common.Empty

public:

	gRPC_ResponseItem(Client** client, void* inRequest, Type_Call_gRPC::Type_gRPCItem type_gRPC = Type_Call_gRPC::Type_gRPCItem::NONE);
	gRPC_ResponseItem() = delete;
	~gRPC_ResponseItem();

	ModelItems::WeaponBundle gRPC_EditBundle();
	bool gRPC_AttachBundle();
	bool gRPC_DetachBundle();

	ModelItems::Item gRPC_GetItem(int index);
	ObjectList<ModelItems::Item> gRPC_GetItemsArray();
	ObjectList<ModelItems::Item> gRPC_CopyDataItems();

	ModelItems::WeaponBundle gRPC_GetBundle(int index);
	ObjectList<ModelItems::WeaponBundle> gRPC_GetBundlesArray();
	ObjectList<ModelItems::WeaponBundle> gRPC_CopyDataBundles();

};

class gRPC_ResponseMM : public gRPC_Response<Type_Call_gRPC::Type_gRPC_MM>
{

	void free_gRPC() override;

	//call server			
	void CallRPC_SearchGame(ModelMM::SearchGameRequest& inRequest);	//SearchGameResponse
	void CallRPC_AcceptGame(ModelMM::AcceptGameRequest& inRequest);													//common.Empty
	void CallRPC_CancelSearch();																		//common.Empty

public:

	ModelMM::SearchGameResponse getResponse_SearchGame();
	bool getResponse_AcceptGame();
	bool getResponse_CancelSearch();

	gRPC_ResponseMM(Client** client, void* inRequest, Type_Call_gRPC::Type_gRPC_MM type_gRPC = Type_Call_gRPC::Type_gRPC_MM::NONE);
	gRPC_ResponseMM() = delete;
	~gRPC_ResponseMM();

};

class gRPC_ResponseInternalMM : public gRPC_Response<Type_Call_gRPC::Type_gRPC_InternalMM>
{

	void free_gRPC() override;

	//call server			
	void CallRPC_UserLeftBattle(ModelInternalMM::InternalUserLeftBattleRequest& inRequest);
	void CallRPC_SaveBattleResult(ModelInternalMM::SaveBattleResultRequest& inRequest);	
	void CallRPC_GetRoomInfo(ModelInternalMM::RoomInfoRequest& inRequest);
	void CallRPC_CreateRoomWithPlayers(ModelInternalMM::CreateRoomRequest& inRequest);
	void CallRPC_DedicatedServerIsReady(ModelInternalMM::DedicatedServerIsReadyRequest& inRequest);
public:

	bool getResponse_UserLeftBattle();
	bool getResponse_SaveBattleResult();
	ModelInternalMM::RoomInfoResponse getResponse_GetRoomInfo();
	ModelInternalMM::RoomInfoResponse getResponse_CreateRoomWithPlayers();
	bool getResponse_DedicatedServerIsReady();


	gRPC_ResponseInternalMM(Client** client, void* inRequest, Type_Call_gRPC::Type_gRPC_InternalMM type_gRPC = Type_Call_gRPC::Type_gRPC_InternalMM::NONE);
	gRPC_ResponseInternalMM() = delete;
	~gRPC_ResponseInternalMM();

};

class gRPC_ResponseUptate
{
	void* messageData;
public:
	gRPC_ResponseUptate();
	~gRPC_ResponseUptate();

	const ModelUpdates::MessageData& writeUpdate(const ModelUpdates::Update& Request);
	const ModelUpdates::MessageData& writeUpdateMessage(const ModelUpdates::UpdateMessage& Request);
	const ModelUpdates::MessageData& writeRoomNeedAccept(const ModelUpdates::RoomNeedAccept& Request);
	const ModelUpdates::MessageData& writeRoomInfo(const ModelUpdates::RoomInfo& Request);
	const ModelUpdates::MessageData& writeRoomPlayer(const ModelUpdates::RoomPlayer& Request);
};