#include"items.h"
#include "AsyncTask.h"

RPC_ItemsService* UItemsService::_RPC_ItemsService = nullptr;

RPC_ItemsService::RPC_ItemsService(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out) {}

RPC_ItemsService::~RPC_ItemsService() {}

game::battlemon::items::ItemsResponse RPC_ItemsService::GetItems(grpc::ClientContext* context, const game::battlemon::items::ItemsRequest* request)
{
	game::battlemon::items::ItemsResponse read;
	CheckError(stub.get()->GetItems(context, *request, &read));

	if (static_cast<FGetItemsDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUItemsResponse*>(out) = read;
		static_cast<FGetItemsDelegate*>(Delegate)->Broadcast(*static_cast<FUItemsResponse*>(out));
	}
	return read;
}

game::battlemon::items::GetBundlesResponse RPC_ItemsService::GetBundles(grpc::ClientContext* context, const game::battlemon::items::GetBundlesRequest* request)
{
	game::battlemon::items::GetBundlesResponse read;
	CheckError(stub.get()->GetBundles(context, *request, &read));

	if (static_cast<FGetBundlesDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUGetBundlesResponse*>(out) = read;
		static_cast<FGetBundlesDelegate*>(Delegate)->Broadcast(*static_cast<FUGetBundlesResponse*>(out));
	}
	return read;
}

game::battlemon::items::WeaponBundle RPC_ItemsService::EditBundle(grpc::ClientContext* context, const game::battlemon::items::EditBundleRequest* request)
{
	game::battlemon::items::WeaponBundle read;
	CheckError(stub.get()->EditBundle(context, *request, &read));

	if (static_cast<FEditBundleDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUWeaponBundle*>(out) = read;
		static_cast<FEditBundleDelegate*>(Delegate)->Broadcast(*static_cast<FUWeaponBundle*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_ItemsService::AttachBundle(grpc::ClientContext* context, const game::battlemon::items::AttachBundleRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->AttachBundle(context, *request, &read));

	if (static_cast<FAttachBundleDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FAttachBundleDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_ItemsService::DetachBundle(grpc::ClientContext* context, const game::battlemon::items::DetachBundleRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->DetachBundle(context, *request, &read));

	if (static_cast<FDetachBundleDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FDetachBundleDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

void UItemsService::free_RPC_ItemsService()
{
	if (_RPC_ItemsService != nullptr)
	{
		if (_RPC_ItemsService->Task != nullptr)
		{
			switch (rpc)
			{
			case ItemsServiceRPC::GetItems:
				if (!CAST_ASINCTASK(FUItemsResponse, RPC_ItemsService, game::battlemon::items::ItemsRequest, game::battlemon::items::ItemsResponse)(_RPC_ItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUItemsResponse, RPC_ItemsService, game::battlemon::items::ItemsRequest, game::battlemon::items::ItemsResponse)(_RPC_ItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUItemsResponse, RPC_ItemsService, game::battlemon::items::ItemsRequest, game::battlemon::items::ItemsResponse)(_RPC_ItemsService->Task);
				break;
			case ItemsServiceRPC::GetBundles:
				if (!CAST_ASINCTASK(FUGetBundlesResponse, RPC_ItemsService, game::battlemon::items::GetBundlesRequest, game::battlemon::items::GetBundlesResponse)(_RPC_ItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUGetBundlesResponse, RPC_ItemsService, game::battlemon::items::GetBundlesRequest, game::battlemon::items::GetBundlesResponse)(_RPC_ItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUGetBundlesResponse, RPC_ItemsService, game::battlemon::items::GetBundlesRequest, game::battlemon::items::GetBundlesResponse)(_RPC_ItemsService->Task);
				break;
			case ItemsServiceRPC::EditBundle:
				if (!CAST_ASINCTASK(FUWeaponBundle, RPC_ItemsService, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle)(_RPC_ItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUWeaponBundle, RPC_ItemsService, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle)(_RPC_ItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUWeaponBundle, RPC_ItemsService, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle)(_RPC_ItemsService->Task);
				break;
			case ItemsServiceRPC::AttachBundle:
				if (!CAST_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::AttachBundleRequest, game::battlemon::common::Empty)(_RPC_ItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::AttachBundleRequest, game::battlemon::common::Empty)(_RPC_ItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::AttachBundleRequest, game::battlemon::common::Empty)(_RPC_ItemsService->Task);
				break;
			case ItemsServiceRPC::DetachBundle:
				if (!CAST_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::DetachBundleRequest, game::battlemon::common::Empty)(_RPC_ItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::DetachBundleRequest, game::battlemon::common::Empty)(_RPC_ItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::DetachBundleRequest, game::battlemon::common::Empty)(_RPC_ItemsService->Task);
				break;
			}
			_RPC_ItemsService->Task = nullptr;
		}
		delete _RPC_ItemsService;
	}
	_RPC_ItemsService = nullptr;
}

UItemsService::UItemsService() {}

UItemsService::~UItemsService() 
{
	free_RPC_ItemsService();
}

void UItemsService::GetItems(TMap<FString, FString> context, FUItemsRequest inp, FUItemsResponse &out)
{
	free_RPC_ItemsService();
	rpc = ItemsServiceRPC::GetItems;
	game::battlemon::items::ItemsRequest g_request;
	g_request << inp;
	_RPC_ItemsService = new RPC_ItemsService(ssl, URL, &GetItemsDelegate, &out);
	CREATE_ASINCTASK(FUItemsResponse, RPC_ItemsService, game::battlemon::items::ItemsRequest, game::battlemon::items::ItemsResponse);
	_RPC_ItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_ItemsService, &out, &g_request, context, &RPC_ItemsService::GetItems);
	GET_ASINCTASK->StartBackgroundTask();
}

void UItemsService::GetBundles(TMap<FString, FString> context, FUGetBundlesRequest inp, FUGetBundlesResponse &out)
{
	free_RPC_ItemsService();
	rpc = ItemsServiceRPC::GetBundles;
	game::battlemon::items::GetBundlesRequest g_request;
	g_request << inp;
	_RPC_ItemsService = new RPC_ItemsService(ssl, URL, &GetBundlesDelegate, &out);
	CREATE_ASINCTASK(FUGetBundlesResponse, RPC_ItemsService, game::battlemon::items::GetBundlesRequest, game::battlemon::items::GetBundlesResponse);
	_RPC_ItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_ItemsService, &out, &g_request, context, &RPC_ItemsService::GetBundles);
	GET_ASINCTASK->StartBackgroundTask();
}

void UItemsService::EditBundle(TMap<FString, FString> context, FUEditBundleRequest inp, FUWeaponBundle &out)
{
	free_RPC_ItemsService();
	rpc = ItemsServiceRPC::EditBundle;
	game::battlemon::items::EditBundleRequest g_request;
	g_request << inp;
	_RPC_ItemsService = new RPC_ItemsService(ssl, URL, &EditBundleDelegate, &out);
	CREATE_ASINCTASK(FUWeaponBundle, RPC_ItemsService, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle);
	_RPC_ItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_ItemsService, &out, &g_request, context, &RPC_ItemsService::EditBundle);
	GET_ASINCTASK->StartBackgroundTask();
}

void UItemsService::AttachBundle(TMap<FString, FString> context, FUAttachBundleRequest inp, FUEmpty &out)
{
	free_RPC_ItemsService();
	rpc = ItemsServiceRPC::AttachBundle;
	game::battlemon::items::AttachBundleRequest g_request;
	g_request << inp;
	_RPC_ItemsService = new RPC_ItemsService(ssl, URL, &AttachBundleDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::AttachBundleRequest, game::battlemon::common::Empty);
	_RPC_ItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_ItemsService, &out, &g_request, context, &RPC_ItemsService::AttachBundle);
	GET_ASINCTASK->StartBackgroundTask();
}

void UItemsService::DetachBundle(TMap<FString, FString> context, FUDetachBundleRequest inp, FUEmpty &out)
{
	free_RPC_ItemsService();
	rpc = ItemsServiceRPC::DetachBundle;
	game::battlemon::items::DetachBundleRequest g_request;
	g_request << inp;
	_RPC_ItemsService = new RPC_ItemsService(ssl, URL, &DetachBundleDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_ItemsService, game::battlemon::items::DetachBundleRequest, game::battlemon::common::Empty);
	_RPC_ItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_ItemsService, &out, &g_request, context, &RPC_ItemsService::DetachBundle);
	GET_ASINCTASK->StartBackgroundTask();
}

FString UItemsService::GetError()
{
	if (_RPC_ItemsService != nullptr)
		return _RPC_ItemsService->GetError();
	return FString();
}



FUItemCase& operator<<(FUItemCase &UE, const game::battlemon::items::Item::ItemCase& grpc)
{
	UE = FUItemCase::Default;
	switch (grpc)
	{
	case game::battlemon::items::Item::ItemCase::kNft:
		UE = FUItemCase::kNft;
		break;
	case game::battlemon::items::Item::ItemCase::kNonNft:
		UE = FUItemCase::kNonNft;
		break;
	}
	return UE;
}


FUWeaponBundleItemType& operator<<(FUWeaponBundleItemType &UE, const game::battlemon::items::WeaponBundleItemType& grpc)
{
	UE = FUWeaponBundleItemType::Default;
	switch (grpc)
	{
	case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PRIMARY:
		UE = FUWeaponBundleItemType::BUNDLE_ITEM_PRIMARY;
		break;
	case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_SECONDARY:
		UE = FUWeaponBundleItemType::BUNDLE_ITEM_SECONDARY;
		break;
	case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MELEE:
		UE = FUWeaponBundleItemType::BUNDLE_ITEM_MELEE;
		break;
	case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_TACTICAL:
		UE = FUWeaponBundleItemType::BUNDLE_ITEM_TACTICAL;
		break;
	case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MILITARY:
		UE = FUWeaponBundleItemType::BUNDLE_ITEM_MILITARY;
		break;
	case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PERK:
		UE = FUWeaponBundleItemType::BUNDLE_ITEM_PERK;
		break;
	}
	return UE;
}


FUWeaponBundleSlotType& operator<<(FUWeaponBundleSlotType &UE, const game::battlemon::items::WeaponBundleSlotType& grpc)
{
	UE = FUWeaponBundleSlotType::Default;
	switch (grpc)
	{
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PRIMARY:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_PRIMARY;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_SECONDARY:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_SECONDARY;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MELEE:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_MELEE;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE;
		break;
	case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO:
		UE = FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO;
		break;
	}
	return UE;
}


game::battlemon::items::Item::ItemCase& operator<<(game::battlemon::items::Item::ItemCase & grpc, const FUItemCase &UE) 
{
	switch (UE)
	{
	case FUItemCase::kNft:
		grpc = game::battlemon::items::Item::ItemCase::kNft;
		break;
	case FUItemCase::kNonNft:
		grpc = game::battlemon::items::Item::ItemCase::kNonNft;
		break;
	}
	return grpc;
}


game::battlemon::items::WeaponBundleItemType& operator<<(game::battlemon::items::WeaponBundleItemType & grpc, const FUWeaponBundleItemType &UE) 
{
	switch (UE)
	{
	case FUWeaponBundleItemType::BUNDLE_ITEM_PRIMARY:
		grpc = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PRIMARY;
		break;
	case FUWeaponBundleItemType::BUNDLE_ITEM_SECONDARY:
		grpc = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_SECONDARY;
		break;
	case FUWeaponBundleItemType::BUNDLE_ITEM_MELEE:
		grpc = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MELEE;
		break;
	case FUWeaponBundleItemType::BUNDLE_ITEM_TACTICAL:
		grpc = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_TACTICAL;
		break;
	case FUWeaponBundleItemType::BUNDLE_ITEM_MILITARY:
		grpc = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MILITARY;
		break;
	case FUWeaponBundleItemType::BUNDLE_ITEM_PERK:
		grpc = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PERK;
		break;
	}
	return grpc;
}


game::battlemon::items::WeaponBundleSlotType& operator<<(game::battlemon::items::WeaponBundleSlotType & grpc, const FUWeaponBundleSlotType &UE) 
{
	switch (UE)
	{
	case FUWeaponBundleSlotType::BUNDLE_SLOT_PRIMARY:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PRIMARY;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_SECONDARY:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_SECONDARY;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_MELEE:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MELEE;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE;
		break;
	case FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO:
		grpc = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO;
		break;
	}
	return grpc;
}


FUDetachBundleRequest& FUDetachBundleRequest::operator=(const game::battlemon::items::DetachBundleRequest& grpcDetachBundleRequest)
{
	bundle_num = grpcDetachBundleRequest.bundle_num();
	lemon_id = CONV_CHAR_TO_FSTRING(grpcDetachBundleRequest.lemon_id().c_str());
	return *this;
}


FUAttachBundleRequest& FUAttachBundleRequest::operator=(const game::battlemon::items::AttachBundleRequest& grpcAttachBundleRequest)
{
	bundle_num = grpcAttachBundleRequest.bundle_num();
	lemon_id = CONV_CHAR_TO_FSTRING(grpcAttachBundleRequest.lemon_id().c_str());
	return *this;
}


FUWeaponBundleItem& FUWeaponBundleItem::operator=(const game::battlemon::items::WeaponBundleItem& grpcWeaponBundleItem)
{
	item_type << grpcWeaponBundleItem.item_type();
	skin = CONV_CHAR_TO_FSTRING(grpcWeaponBundleItem.skin().c_str());
	slot_type << grpcWeaponBundleItem.slot_type();
	return *this;
}


FUEditBundleRequest& FUEditBundleRequest::operator=(const game::battlemon::items::EditBundleRequest& grpcEditBundleRequest)
{
	bundle_num = grpcEditBundleRequest.bundle_num();
{
	int size = grpcEditBundleRequest.items().size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		items[Idx] = grpcEditBundleRequest.items(Idx);
		});

	}
	title = CONV_CHAR_TO_FSTRING(grpcEditBundleRequest.title().c_str());
	return *this;
}


FUWeaponBundle& FUWeaponBundle::operator=(const game::battlemon::items::WeaponBundle& grpcWeaponBundle)
{
	bundle_num = grpcWeaponBundle.bundle_num();
{
	int size = grpcWeaponBundle.items().size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		items[Idx] = grpcWeaponBundle.items(Idx);
		});

	}
	title = CONV_CHAR_TO_FSTRING(grpcWeaponBundle.title().c_str());
	level = grpcWeaponBundle.level();
	return *this;
}


FUGetBundlesResponse& FUGetBundlesResponse::operator=(const game::battlemon::items::GetBundlesResponse& grpcGetBundlesResponse)
{
{
	int size = grpcGetBundlesResponse.bundles().size();
	bundles.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		bundles[Idx] = grpcGetBundlesResponse.bundles(Idx);
		});

	}
	return *this;
}


FUGetBundlesRequest& FUGetBundlesRequest::operator=(const game::battlemon::items::GetBundlesRequest& grpcGetBundlesRequest)
{
	return *this;
}


FUNonNftItem& FUNonNftItem::operator=(const game::battlemon::items::NonNftItem& grpcNonNftItem)
{
	id = CONV_CHAR_TO_FSTRING(grpcNonNftItem.id().c_str());
	owner = CONV_CHAR_TO_FSTRING(grpcNonNftItem.owner().c_str());
	level = grpcNonNftItem.level();
{
	int size = grpcNonNftItem.attached_bundles().size();
	attached_bundles.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		attached_bundles[Idx] = grpcNonNftItem.attached_bundles(Idx);
		});

	}
	return *this;
}


FUItem& FUItem::operator=(const game::battlemon::items::Item& grpcItem)
{
	return *this;
}


FUTrait& FUTrait::operator=(const game::battlemon::items::Trait& grpcTrait)
{
	name = CONV_CHAR_TO_FSTRING(grpcTrait.name().c_str());
	flavour = CONV_CHAR_TO_FSTRING(grpcTrait.flavour().c_str());
	return *this;
}


FUNftItem& FUNftItem::operator=(const game::battlemon::items::NftItem& grpcNftItem)
{
	id = CONV_CHAR_TO_FSTRING(grpcNftItem.id().c_str());
	type = CONV_CHAR_TO_FSTRING(grpcNftItem.type().c_str());
	owner = CONV_CHAR_TO_FSTRING(grpcNftItem.owner().c_str());
	url = CONV_CHAR_TO_FSTRING(grpcNftItem.url().c_str());
{
	int size = grpcNftItem.traits().size();
	traits.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		traits[Idx] = grpcNftItem.traits(Idx);
		});

	}
	created_at = grpcNftItem.created_at();
{
	int size = grpcNftItem.attached_bundles().size();
	attached_bundles.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		attached_bundles[Idx] = grpcNftItem.attached_bundles(Idx);
		});

	}
	return *this;
}


FUItemsResponse& FUItemsResponse::operator=(const game::battlemon::items::ItemsResponse& grpcItemsResponse)
{
{
	int size = grpcItemsResponse.items().size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		items[Idx] = grpcItemsResponse.items(Idx);
		});

	}
	return *this;
}


FUItemsRequest& FUItemsRequest::operator=(const game::battlemon::items::ItemsRequest& grpcItemsRequest)
{
	return *this;
}



game::battlemon::items::DetachBundleRequest &operator<<(game::battlemon::items::DetachBundleRequest &grpcDetachBundleRequest, const FUDetachBundleRequest &UE)
{
	{
		grpcDetachBundleRequest.set_bundle_num(UE.bundle_num);
	}
	{
		grpcDetachBundleRequest.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	return grpcDetachBundleRequest;
}


game::battlemon::items::AttachBundleRequest &operator<<(game::battlemon::items::AttachBundleRequest &grpcAttachBundleRequest, const FUAttachBundleRequest &UE)
{
	{
		grpcAttachBundleRequest.set_bundle_num(UE.bundle_num);
	}
	{
		grpcAttachBundleRequest.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	return grpcAttachBundleRequest;
}


game::battlemon::items::WeaponBundleItem &operator<<(game::battlemon::items::WeaponBundleItem &grpcWeaponBundleItem, const FUWeaponBundleItem &UE)
{
	{
		game::battlemon::items::WeaponBundleItemType go;
		go << UE.item_type;
		grpcWeaponBundleItem.set_item_type(go);
	}
	{
		grpcWeaponBundleItem.set_skin(CONV_FSTRING_TO_CHAR(UE.skin));
	}
	{
		game::battlemon::items::WeaponBundleSlotType go;
		go << UE.slot_type;
		grpcWeaponBundleItem.set_slot_type(go);
	}
	return grpcWeaponBundleItem;
}


game::battlemon::items::EditBundleRequest &operator<<(game::battlemon::items::EditBundleRequest &grpcEditBundleRequest, const FUEditBundleRequest &UE)
{
	{
		grpcEditBundleRequest.set_bundle_num(UE.bundle_num);
	}
		int size = UE.items.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::WeaponBundleItem* ptr =grpcEditBundleRequest.add_items();
		(*ptr) << UE.items[Idx];
	}
	{
		grpcEditBundleRequest.set_title(CONV_FSTRING_TO_CHAR(UE.title));
	}
	return grpcEditBundleRequest;
}


game::battlemon::items::WeaponBundle &operator<<(game::battlemon::items::WeaponBundle &grpcWeaponBundle, const FUWeaponBundle &UE)
{
	{
		grpcWeaponBundle.set_bundle_num(UE.bundle_num);
	}
		int size = UE.items.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::WeaponBundleItem* ptr =grpcWeaponBundle.add_items();
		(*ptr) << UE.items[Idx];
	}
	{
		grpcWeaponBundle.set_title(CONV_FSTRING_TO_CHAR(UE.title));
	}
	{
		grpcWeaponBundle.set_level(UE.level);
	}
	return grpcWeaponBundle;
}


game::battlemon::items::GetBundlesResponse &operator<<(game::battlemon::items::GetBundlesResponse &grpcGetBundlesResponse, const FUGetBundlesResponse &UE)
{
		int size = UE.bundles.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::WeaponBundle* ptr =grpcGetBundlesResponse.add_bundles();
		(*ptr) << UE.bundles[Idx];
	}
	return grpcGetBundlesResponse;
}


game::battlemon::items::GetBundlesRequest &operator<<(game::battlemon::items::GetBundlesRequest &grpcGetBundlesRequest, const FUGetBundlesRequest &UE)
{
	return grpcGetBundlesRequest;
}


game::battlemon::items::NonNftItem &operator<<(game::battlemon::items::NonNftItem &grpcNonNftItem, const FUNonNftItem &UE)
{
	{
		grpcNonNftItem.set_id(CONV_FSTRING_TO_CHAR(UE.id));
	}
	{
		grpcNonNftItem.set_owner(CONV_FSTRING_TO_CHAR(UE.owner));
	}
	{
		grpcNonNftItem.set_level(UE.level);
	}
		int size = UE.attached_bundles.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::WeaponBundle* ptr =grpcNonNftItem.add_attached_bundles();
		(*ptr) << UE.attached_bundles[Idx];
	}
	return grpcNonNftItem;
}


game::battlemon::items::Item &operator<<(game::battlemon::items::Item &grpcItem, const FUItem &UE)
{
	switch (UE.item_case)
	{
	case FUItemCase::kNft:
	{
		game::battlemon::items::NftItem* go = new game::battlemon::items::NftItem();
		*go << UE.nft;
		grpcItem.set_allocated_nft(go);
	}
		break;
	case FUItemCase::kNonNft:
	{
		game::battlemon::items::NonNftItem* go = new game::battlemon::items::NonNftItem();
		*go << UE.non_nft;
		grpcItem.set_allocated_non_nft(go);
	}
		break;
	}
	return grpcItem;
}


game::battlemon::items::Trait &operator<<(game::battlemon::items::Trait &grpcTrait, const FUTrait &UE)
{
	{
		grpcTrait.set_name(CONV_FSTRING_TO_CHAR(UE.name));
	}
	{
		grpcTrait.set_flavour(CONV_FSTRING_TO_CHAR(UE.flavour));
	}
	return grpcTrait;
}


game::battlemon::items::NftItem& operator<<(game::battlemon::items::NftItem& grpcNftItem, const FUNftItem& UE)
{
	{
		grpcNftItem.set_id(CONV_FSTRING_TO_CHAR(UE.id));
	}
	{
		grpcNftItem.set_type(CONV_FSTRING_TO_CHAR(UE.type));
	}
	{
		grpcNftItem.set_owner(CONV_FSTRING_TO_CHAR(UE.owner));
	}
	{
		grpcNftItem.set_url(CONV_FSTRING_TO_CHAR(UE.url));
	}
	{
	int size = UE.traits.Num();
	for (size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::Trait* ptr = grpcNftItem.add_traits();
		(*ptr) << UE.traits[Idx];
	}
	}
	{
		grpcNftItem.set_created_at(UE.created_at);
	}
	{
		int size = UE.attached_bundles.Num();
		for (size_t Idx = 0; Idx < size; Idx++)
		{
			game::battlemon::items::WeaponBundle* ptr = grpcNftItem.add_attached_bundles();
			(*ptr) << UE.attached_bundles[Idx];
		}
	}
	return grpcNftItem;
}


game::battlemon::items::ItemsResponse &operator<<(game::battlemon::items::ItemsResponse &grpcItemsResponse, const FUItemsResponse &UE)
{
	int size = UE.items.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::Item* ptr =grpcItemsResponse.add_items();
		(*ptr) << UE.items[Idx];
	}
	return grpcItemsResponse;
}


game::battlemon::items::ItemsRequest &operator<<(game::battlemon::items::ItemsRequest &grpcItemsRequest, const FUItemsRequest &UE)
{
	return grpcItemsRequest;
}

