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

	gRPC_Response(Client** client, Type_Call_gRPC type_gRPC) :client((const Client**)client), type_gRPC(type_gRPC), error(nullptr), gRPC_read(nullptr){};
	gRPC_Response() = delete;

	~gRPC_Response() {}
};


class gRPC_ResponseItem : public gRPC_Response<Type_Call_gRPC::Type_gRPCItem>
{
	void free_gRPC() override;

	//call server																													
	void CallRPC_GetItems();																										//return ItemsResponse
	void CallRPC_GetBundles();																										//return GetBundlesResponse
	void CallRPC_EditBundle(ModelItems::EditBundleRequest& request);		//return WeaponBundle
	bool CallRPC_AttachBundle(ModelItems::AttachBundleRequest& request);												//return common.Empty
	bool CallRPC_DetachBundle(ModelItems::DetachBundleRequest& request);												//return common.Empty

public:

	gRPC_ResponseItem(Client** client, void* inRequest, Type_Call_gRPC::Type_gRPCItem type_gRPC = Type_Call_gRPC::Type_gRPCItem::NONE);
	gRPC_ResponseItem() = delete;
	~gRPC_ResponseItem();

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
	bool CallRPC_AcceptGame(ModelMM::AcceptGameRequest& inRequest);													//common.Empty
	bool CallRPC_CancelSearch();																		//common.Empty

public:

	ModelMM::SearchGameResponse getResponse_SearchGame();
	bool getResponse_AcceptGame();
	bool getResponse_CancelSearch();

	gRPC_ResponseMM(Client** client, void* inRequest, Type_Call_gRPC::Type_gRPC_MM type_gRPC = Type_Call_gRPC::Type_gRPC_MM::NONE);
	gRPC_ResponseMM() = delete;
	~gRPC_ResponseMM();

};