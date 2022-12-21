#include"items.h"

FUModelCase& operator<<(FUModelCase &UE, const game::battlemon::items::Item::ModelCase& grpc)
{
	UE = FUModelCase::Default;
	switch (grpc)
	{
	case game::battlemon::items::Item::ModelCase::kLemon:
		UE = FUModelCase::kLemon;
		break;
	case game::battlemon::items::Item::ModelCase::kOutfit:
		UE = FUModelCase::kOutfit;
		break;
	}
	return UE;
}


FUOutfitKind& operator<<(FUOutfitKind &UE, const game::battlemon::items::OutfitKind& grpc)
{
	UE = FUOutfitKind::Default;
	switch (grpc)
	{
	case game::battlemon::items::OutfitKind::CAP:
		UE = FUOutfitKind::CAP;
		break;
	case game::battlemon::items::OutfitKind::CLOTH:
		UE = FUOutfitKind::CLOTH;
		break;
	case game::battlemon::items::OutfitKind::FIRE_ARM:
		UE = FUOutfitKind::FIRE_ARM;
		break;
	case game::battlemon::items::OutfitKind::COLD_ARM:
		UE = FUOutfitKind::COLD_ARM;
		break;
	case game::battlemon::items::OutfitKind::BACK:
		UE = FUOutfitKind::BACK;
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


game::battlemon::items::Item::ModelCase& operator<<(game::battlemon::items::Item::ModelCase & grpc, const FUModelCase &UE) 
{
	switch (UE)
	{
	case FUModelCase::kLemon:
		grpc = game::battlemon::items::Item::ModelCase::kLemon;
		break;
	case FUModelCase::kOutfit:
		grpc = game::battlemon::items::Item::ModelCase::kOutfit;
		break;
	}
	return grpc;
}


game::battlemon::items::OutfitKind& operator<<(game::battlemon::items::OutfitKind & grpc, const FUOutfitKind &UE) 
{
	switch (UE)
	{
	case FUOutfitKind::CAP:
		grpc = game::battlemon::items::OutfitKind::CAP;
		break;
	case FUOutfitKind::CLOTH:
		grpc = game::battlemon::items::OutfitKind::CLOTH;
		break;
	case FUOutfitKind::FIRE_ARM:
		grpc = game::battlemon::items::OutfitKind::FIRE_ARM;
		break;
	case FUOutfitKind::COLD_ARM:
		grpc = game::battlemon::items::OutfitKind::COLD_ARM;
		break;
	case FUOutfitKind::BACK:
		grpc = game::battlemon::items::OutfitKind::BACK;
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


FUItemsRequest& FUItemsRequest::operator=(const game::battlemon::items::ItemsRequest& grpcItemsRequest)
{
	return *this;
}


FUItemsResponse& FUItemsResponse::operator=(const game::battlemon::items::ItemsResponse& grpcItemsResponse)
{
	int size = grpcItemsResponse.items().size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		items[Idx] = grpcItemsResponse.items(Idx);
		});
	return *this;
}


FUItem& FUItem::operator=(const game::battlemon::items::Item& grpcItem)
{
	token_id = CONV_CHAR_TO_FSTRING(grpcItem.token_id().c_str());
	media = CONV_CHAR_TO_FSTRING(grpcItem.media().c_str());
	owner_id = CONV_CHAR_TO_FSTRING(grpcItem.owner_id().c_str());
	in_fight = grpcItem.in_fight();
	return *this;
}


FULemonModel& FULemonModel::operator=(const game::battlemon::items::LemonModel& grpcLemonModel)
{
	cap = grpcLemonModel.cap();
	cloth = grpcLemonModel.cloth();
	exo = CONV_CHAR_TO_FSTRING(grpcLemonModel.exo().c_str());
	eyes = CONV_CHAR_TO_FSTRING(grpcLemonModel.eyes().c_str());
	head = CONV_CHAR_TO_FSTRING(grpcLemonModel.head().c_str());
	teeth = CONV_CHAR_TO_FSTRING(grpcLemonModel.teeth().c_str());
	face = CONV_CHAR_TO_FSTRING(grpcLemonModel.face().c_str());
	fire_arm = grpcLemonModel.fire_arm();
	cold_arm = grpcLemonModel.cold_arm();
	back = grpcLemonModel.back();
	int size = grpcLemonModel.attached_bundles().size();
	attached_bundles.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		attached_bundles[Idx] = grpcLemonModel.attached_bundles(Idx);
		});
	return *this;
}


FUOutfitModel& FUOutfitModel::operator=(const game::battlemon::items::OutfitModel& grpcOutfitModel)
{
	flavour = CONV_CHAR_TO_FSTRING(grpcOutfitModel.flavour().c_str());
	token_id = CONV_CHAR_TO_FSTRING(grpcOutfitModel.token_id().c_str());
	kind << grpcOutfitModel.kind();
	return *this;
}


FUWeaponBundle& FUWeaponBundle::operator=(const game::battlemon::items::WeaponBundle& grpcWeaponBundle)
{
	bundle_num = grpcWeaponBundle.bundle_num();
	int size = grpcWeaponBundle.items().size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		items[Idx] = grpcWeaponBundle.items(Idx);
		});
	title = CONV_CHAR_TO_FSTRING(grpcWeaponBundle.title().c_str());
	level = grpcWeaponBundle.level();
	return *this;
}


FUWeaponBundleItem& FUWeaponBundleItem::operator=(const game::battlemon::items::WeaponBundleItem& grpcWeaponBundleItem)
{
	item_type << grpcWeaponBundleItem.item_type();
	skin = CONV_CHAR_TO_FSTRING(grpcWeaponBundleItem.skin().c_str());
	slot_type << grpcWeaponBundleItem.slot_type();
	return *this;
}


FUGetBundlesRequest& FUGetBundlesRequest::operator=(const game::battlemon::items::GetBundlesRequest& grpcGetBundlesRequest)
{
	return *this;
}


FUGetBundlesResponse& FUGetBundlesResponse::operator=(const game::battlemon::items::GetBundlesResponse& grpcGetBundlesResponse)
{
	int size = grpcGetBundlesResponse.bundles().size();
	bundles.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		bundles[Idx] = grpcGetBundlesResponse.bundles(Idx);
		});
	return *this;
}


FUEditBundleRequest& FUEditBundleRequest::operator=(const game::battlemon::items::EditBundleRequest& grpcEditBundleRequest)
{
	bundle_num = grpcEditBundleRequest.bundle_num();
	int size = grpcEditBundleRequest.items().size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		items[Idx] = grpcEditBundleRequest.items(Idx);
		});
	title = CONV_CHAR_TO_FSTRING(grpcEditBundleRequest.title().c_str());
	return *this;
}


FUAttachBundleRequest& FUAttachBundleRequest::operator=(const game::battlemon::items::AttachBundleRequest& grpcAttachBundleRequest)
{
	bundle_num = grpcAttachBundleRequest.bundle_num();
	lemon_id = CONV_CHAR_TO_FSTRING(grpcAttachBundleRequest.lemon_id().c_str());
	return *this;
}


FUDetachBundleRequest& FUDetachBundleRequest::operator=(const game::battlemon::items::DetachBundleRequest& grpcDetachBundleRequest)
{
	bundle_num = grpcDetachBundleRequest.bundle_num();
	lemon_id = CONV_CHAR_TO_FSTRING(grpcDetachBundleRequest.lemon_id().c_str());
	return *this;
}



game::battlemon::items::ItemsRequest &operator<<(game::battlemon::items::ItemsRequest &grpcItemsRequest, const FUItemsRequest &UE)
{
	return grpcItemsRequest;
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


game::battlemon::items::Item &operator<<(game::battlemon::items::Item &grpcItem, const FUItem &UE)
{
	{
		grpcItem.set_token_id(CONV_FSTRING_TO_CHAR(UE.token_id));
	}
	{
		grpcItem.set_media(CONV_FSTRING_TO_CHAR(UE.media));
	}
	{
		grpcItem.set_owner_id(CONV_FSTRING_TO_CHAR(UE.owner_id));
	}
	{
		grpcItem.set_in_fight(UE.in_fight);
	}
	switch (UE.model_case)
	{
	case FUModelCase::kLemon:
	{
		game::battlemon::items::LemonModel* go = new game::battlemon::items::LemonModel();
		*go << UE.lemon;
		grpcItem.set_allocated_lemon(go);
	}
		break;
	case FUModelCase::kOutfit:
	{
		game::battlemon::items::OutfitModel* go = new game::battlemon::items::OutfitModel();
		*go << UE.outfit;
		grpcItem.set_allocated_outfit(go);
	}
		break;
	}
	return grpcItem;
}


game::battlemon::items::LemonModel &operator<<(game::battlemon::items::LemonModel &grpcLemonModel, const FULemonModel &UE)
{
	{
		game::battlemon::items::OutfitModel* go = new game::battlemon::items::OutfitModel();
		*go << UE.cap;
		grpcLemonModel.set_allocated_cap(go);
	}
	{
		game::battlemon::items::OutfitModel* go = new game::battlemon::items::OutfitModel();
		*go << UE.cloth;
		grpcLemonModel.set_allocated_cloth(go);
	}
	{
		grpcLemonModel.set_exo(CONV_FSTRING_TO_CHAR(UE.exo));
	}
	{
		grpcLemonModel.set_eyes(CONV_FSTRING_TO_CHAR(UE.eyes));
	}
	{
		grpcLemonModel.set_head(CONV_FSTRING_TO_CHAR(UE.head));
	}
	{
		grpcLemonModel.set_teeth(CONV_FSTRING_TO_CHAR(UE.teeth));
	}
	{
		grpcLemonModel.set_face(CONV_FSTRING_TO_CHAR(UE.face));
	}
	{
		game::battlemon::items::OutfitModel* go = new game::battlemon::items::OutfitModel();
		*go << UE.fire_arm;
		grpcLemonModel.set_allocated_fire_arm(go);
	}
	{
		game::battlemon::items::OutfitModel* go = new game::battlemon::items::OutfitModel();
		*go << UE.cold_arm;
		grpcLemonModel.set_allocated_cold_arm(go);
	}
	{
		game::battlemon::items::OutfitModel* go = new game::battlemon::items::OutfitModel();
		*go << UE.back;
		grpcLemonModel.set_allocated_back(go);
	}
		int size = UE.attached_bundles.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::WeaponBundle* ptr =grpcLemonModel.add_attached_bundles();
		(*ptr) << UE.attached_bundles[Idx];
	}
	return grpcLemonModel;
}


game::battlemon::items::OutfitModel &operator<<(game::battlemon::items::OutfitModel &grpcOutfitModel, const FUOutfitModel &UE)
{
	{
		grpcOutfitModel.set_flavour(CONV_FSTRING_TO_CHAR(UE.flavour));
	}
	{
		grpcOutfitModel.set_token_id(CONV_FSTRING_TO_CHAR(UE.token_id));
	}
	{
		game::battlemon::items::OutfitKind go;
		go << UE.kind;
		grpcOutfitModel.set_kind(go);
	}
	return grpcOutfitModel;
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


game::battlemon::items::GetBundlesRequest &operator<<(game::battlemon::items::GetBundlesRequest &grpcGetBundlesRequest, const FUGetBundlesRequest &UE)
{
	return grpcGetBundlesRequest;
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

