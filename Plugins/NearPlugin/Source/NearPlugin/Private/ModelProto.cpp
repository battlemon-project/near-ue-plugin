// Fill out your copyright notice in the Description page of Project Settings.


#include "ModelProto.h"

#if PLATFORM_WINDOWS
#define CONV_CHAR_TO_FSTRING(str) FString(ANSI_TO_TCHAR(str))
#endif // PLATFORM_WINDOWS

FUItemsResponse& FUItemsResponse::operator=(const game::battlemon::items::ItemsResponse& itemR)
{
	int size = itemR.items_size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			items[Idx] = itemR.items(Idx);
		});

	return *this;
}

FUItem& FUItem::operator=(const game::battlemon::items::Item& item)
{
	token_id = CONV_CHAR_TO_FSTRING(item.token_id().c_str());
	media = CONV_CHAR_TO_FSTRING(item.media().c_str());
	owner_id = CONV_CHAR_TO_FSTRING(item.owner_id().c_str());
	in_fight = item.in_fight();
	model << item.model_case();
	switch (model)
	{
	case FUModel::kLemon:
		lemon = item.lemon();
		break;
	case FUModel::kOutfit:
		outfit = item.outfit();
		break;
	case FUModel::MODEL_NOT_SET:
		break;
	default:
		break;
	}
	return *this;
}

FULemonModel& FULemonModel::operator=(const game::battlemon::items::LemonModel& lemonModel)
{
	cap = lemonModel.cap();
	cloth = lemonModel.cap();
	exo = CONV_CHAR_TO_FSTRING(lemonModel.exo().c_str());
	eyes = CONV_CHAR_TO_FSTRING(lemonModel.eyes().c_str());
	head = CONV_CHAR_TO_FSTRING(lemonModel.head().c_str());
	teeth = CONV_CHAR_TO_FSTRING(lemonModel.teeth().c_str());
	face = CONV_CHAR_TO_FSTRING(lemonModel.face().c_str());
	fire_arm = lemonModel.fire_arm();
	cold_arm = lemonModel.cold_arm();
	back = lemonModel.back();

	int size = lemonModel.attached_bundles_size();
	attached_bundles.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			attached_bundles[Idx] = lemonModel.attached_bundles(Idx);
		});

	return *this;
}

FUOutfitModel& FUOutfitModel::operator=(const game::battlemon::items::OutfitModel& outfitModel)
{
	flavour = CONV_CHAR_TO_FSTRING(outfitModel.flavour().c_str());
	token_id = CONV_CHAR_TO_FSTRING(outfitModel.token_id().c_str());
	kind << outfitModel.kind();

	return *this;
}


FUWeaponBundle& FUWeaponBundle::operator=(const game::battlemon::items::WeaponBundle& weaponBundle)
{
	bundle_num = weaponBundle.bundle_num();
	title = CONV_CHAR_TO_FSTRING(weaponBundle.title().c_str());
	level = weaponBundle.level();

	int size = weaponBundle.items_size();
	items.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			items[Idx] = weaponBundle.items(Idx);
		});

	return *this;
}

FUWeaponBundleItem& FUWeaponBundleItem::operator=(const game::battlemon::items::WeaponBundleItem& weaponBundleItem)
{
	item_type << weaponBundleItem.item_type();
	skin = CONV_CHAR_TO_FSTRING(weaponBundleItem.skin().c_str());
	slot_type << weaponBundleItem.slot_type();
	return *this;
}

FUGetBundlesResponse& FUGetBundlesResponse::operator=(const game::battlemon::items::GetBundlesResponse& weaponBundleResponse)
{
	int size = weaponBundleResponse.bundles_size();
	bundles.SetNum(size);

	ParallelFor(size, [&](int32 Idx)
		{
			bundles[Idx] = weaponBundleResponse.bundles(Idx);
		});

	return *this;
}

FUEditBundleRequest& FUEditBundleRequest::operator=(const game::battlemon::items::EditBundleRequest& editBundleRequest)
{
	bundle_num = editBundleRequest.bundle_num();
	int size = editBundleRequest.items_size();
	items.SetNum(size);

	ParallelFor(size, [&](int32 Idx)
		{
			items[Idx] = editBundleRequest.items(Idx);
		});

	title = CONV_CHAR_TO_FSTRING(editBundleRequest.title().c_str());

	return *this;
}


FUAttachBundleRequest& FUAttachBundleRequest::operator=(const game::battlemon::items::AttachBundleRequest& attachBundleRequest)
{
	bundle_num = attachBundleRequest.bundle_num();
	lemon_id = CONV_CHAR_TO_FSTRING(attachBundleRequest.lemon_id().c_str());
	return *this;
}

FUDetachBundleRequest& FUDetachBundleRequest::operator=(const game::battlemon::items::DetachBundleRequest& detachBundleRequest)
{
	bundle_num = detachBundleRequest.bundle_num();
	lemon_id = CONV_CHAR_TO_FSTRING(detachBundleRequest.lemon_id().c_str());
	return *this;
}

//mm.massange

FUGameMode& FUGameMode::operator=(const game::battlemon::mm::GameMode& gameMode)
{
	match_type << gameMode.match_type();
	match_mode << gameMode.match_mode();

	return *this;
}

FUSearchGameRequest& FUSearchGameRequest::operator=(const game::battlemon::mm::SearchGameRequest& searchGameRequest)
{
	game_mode = searchGameRequest.game_mode();
	return *this;
}


FUSearchGameResponse& FUSearchGameResponse::operator=(const game::battlemon::mm::SearchGameResponse& searchGameResponse)
{
	status << searchGameResponse.status();
	return *this;
}

FUAcceptGameRequest& FUAcceptGameRequest::operator=(const game::battlemon::mm::AcceptGameRequest& acceptGameRequest)
{
	lemon_id = CONV_CHAR_TO_FSTRING(acceptGameRequest.lemon_id().c_str());
	return *this;
}

//mm.massange end

//InternalMM.massange


FUInternalUserLeftBattleRequest& FUInternalUserLeftBattleRequest::operator=(const game::battlemon::mm::internal::InternalUserLeftBattleRequest& internalUserLeftBattleRequest)
{
	near_id = CONV_CHAR_TO_FSTRING(internalUserLeftBattleRequest.near_id().c_str());
	room_id = CONV_CHAR_TO_FSTRING(internalUserLeftBattleRequest.room_id().c_str());

	return *this;
}

FUInternalPlayerResult& FUInternalPlayerResult::operator=(const game::battlemon::mm::internal::InternalPlayerResult& internalPlayerResult)
{
	near_id = CONV_CHAR_TO_FSTRING(internalPlayerResult.near_id().c_str());
	place = internalPlayerResult.place();

	return *this;
}

FUSaveBattleResultRequest& FUSaveBattleResultRequest::operator=(const game::battlemon::mm::internal::SaveBattleResultRequest& saveBattleResultRequest)
{
	
	room_id = CONV_CHAR_TO_FSTRING(saveBattleResultRequest.room_id().c_str());

	int size = saveBattleResultRequest.results_size();
	results.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			results[Idx] = saveBattleResultRequest.results(Idx);
		});

	return *this;
}


FURoomInfoRequest& FURoomInfoRequest::operator=(const game::battlemon::mm::internal::RoomInfoRequest& roomInfoRequest)
{
	room_id = CONV_CHAR_TO_FSTRING(roomInfoRequest.room_id().c_str());

	return *this;
}


FURoomPlayerInfo& FURoomPlayerInfo::operator=(const game::battlemon::mm::internal::RoomPlayerInfo& roomPlayerInfo)
{
	near_id = CONV_CHAR_TO_FSTRING(roomPlayerInfo.near_id().c_str());
	lemon = roomPlayerInfo.lemon();

	return *this;
}


FURoomInfoResponse& FURoomInfoResponse::operator=(const game::battlemon::mm::internal::RoomInfoResponse& roomInfoResponse)
{
    room_id = CONV_CHAR_TO_FSTRING(roomInfoResponse.room_id().c_str());
	mode = roomInfoResponse.mode();

	int size = roomInfoResponse.players_size();
	players.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			players[Idx] = roomInfoResponse.players(Idx);
		});

	return *this;
}

FUCreateRoomRequest& FUCreateRoomRequest::operator=(const game::battlemon::mm::internal::CreateRoomRequest& createRoomRequest)
{
	mode = createRoomRequest.mode();

	int size = createRoomRequest.near_ids_size();
	near_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
			near_ids[Idx] = CONV_CHAR_TO_FSTRING(createRoomRequest.near_ids(Idx).c_str());
		});

    prev_room_id = CONV_CHAR_TO_FSTRING(createRoomRequest.prev_room_id().c_str());

	return *this;
}


FUWeaponBundleItemType& operator<<(FUWeaponBundleItemType& FU, const game::battlemon::items::WeaponBundleItemType& weaponBundleItemType)
{
    switch (weaponBundleItemType)
    {
    case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PRIMARY:
        FU = FUWeaponBundleItemType::BUNDLE_ITEM_PRIMARY;
        break;
    case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_SECONDARY:
        FU = FUWeaponBundleItemType::BUNDLE_ITEM_SECONDARY;
        break;
    case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MELEE:
        FU = FUWeaponBundleItemType::BUNDLE_ITEM_MELEE;
        break;
    case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_TACTICAL:
        FU = FUWeaponBundleItemType::BUNDLE_ITEM_TACTICAL;
        break;
    case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MILITARY:
        FU = FUWeaponBundleItemType::BUNDLE_ITEM_MILITARY;
        break;
    case game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PERK:
        FU = FUWeaponBundleItemType::BUNDLE_ITEM_PERK;
        break;
    default:
        FU = FUWeaponBundleItemType::Default;
        break;
    }
    return FU;
}

game::battlemon::items::WeaponBundleItemType& operator<<(game::battlemon::items::WeaponBundleItemType& weaponBundleItemType, const FUWeaponBundleItemType& FU)
{
    switch (FU)
    {
    case FUWeaponBundleItemType::BUNDLE_ITEM_PRIMARY:
        weaponBundleItemType = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PRIMARY;
        break;
    case FUWeaponBundleItemType::BUNDLE_ITEM_SECONDARY:
        weaponBundleItemType = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_SECONDARY;
        break;
    case FUWeaponBundleItemType::BUNDLE_ITEM_MELEE:
        weaponBundleItemType = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MELEE;
        break;
    case FUWeaponBundleItemType::BUNDLE_ITEM_TACTICAL:
        weaponBundleItemType = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_TACTICAL;
        break;
    case FUWeaponBundleItemType::BUNDLE_ITEM_MILITARY:
        weaponBundleItemType = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_MILITARY;
        break;
    case FUWeaponBundleItemType::BUNDLE_ITEM_PERK:
        weaponBundleItemType = game::battlemon::items::WeaponBundleItemType::BUNDLE_ITEM_PERK;
        break;
    default:
        break;
    }
    return weaponBundleItemType;
}

game::battlemon::items::WeaponBundleSlotType& operator<<(game::battlemon::items::WeaponBundleSlotType& weaponBundleSlotType, const FUWeaponBundleSlotType& FU)
{
    switch (FU)
    {
    case FUWeaponBundleSlotType::BUNDLE_SLOT_PRIMARY:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PRIMARY;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_SECONDARY:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_SECONDARY;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_MELEE:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MELEE;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE;
        break;
    case FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO:
        weaponBundleSlotType = game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO;
        break;
    default:
        break;
    }
    return weaponBundleSlotType;
}

FUWeaponBundleSlotType& operator<<(FUWeaponBundleSlotType& FU, const game::battlemon::items::WeaponBundleSlotType& weaponBundleSlotType)
{
    switch (weaponBundleSlotType)
    {
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PRIMARY:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_PRIMARY;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_SECONDARY:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_SECONDARY;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MELEE:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_MELEE;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_ONE;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_TACTICAL_TWO;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_ONE;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_MILITARY_TWO;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_ONE;
        break;
    case game::battlemon::items::WeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO:
        FU = FUWeaponBundleSlotType::BUNDLE_SLOT_PERK_TWO;
        break;
    default:
        break;
    }
    return FU;
}

FUOutfitKind& operator<<(FUOutfitKind& FU, const game::battlemon::items::OutfitKind& outfitKind)
{
    switch (outfitKind)
    {
    case game::battlemon::items::OutfitKind::CAP:
        FU = FUOutfitKind::CAP;
        break;
    case game::battlemon::items::OutfitKind::CLOTH:
        FU = FUOutfitKind::CLOTH;
        break;
    case game::battlemon::items::OutfitKind::FIRE_ARM:
        FU = FUOutfitKind::FIRE_ARM;
        break;
    case game::battlemon::items::OutfitKind::COLD_ARM:
        FU = FUOutfitKind::COLD_ARM;
        break;
    case game::battlemon::items::OutfitKind::BACK:
        FU = FUOutfitKind::BACK;
        break;
    default:
        FU = FUOutfitKind::Default;
        break;
    }

    return FU;
}

game::battlemon::items::OutfitKind& operator<<(game::battlemon::items::OutfitKind& outfitKind, const FUOutfitKind& FU)
{
    switch (FU)
    {
    case FUOutfitKind::CAP:
        outfitKind = game::battlemon::items::OutfitKind::CAP;
        break;
    case FUOutfitKind::CLOTH:
        outfitKind = game::battlemon::items::OutfitKind::CLOTH;
        break;
    case FUOutfitKind::FIRE_ARM:
        outfitKind = game::battlemon::items::OutfitKind::FIRE_ARM;
        break;
    case FUOutfitKind::COLD_ARM:
        outfitKind = game::battlemon::items::OutfitKind::COLD_ARM;
        break;
    case FUOutfitKind::BACK:
        outfitKind = game::battlemon::items::OutfitKind::BACK;
        break;
    default:
        break;
    }

    return outfitKind;
}

FUModel& operator<<(FUModel& FU, const game::battlemon::items::Item::ModelCase& modelCase)
{
    switch (modelCase)
    {
    case game::battlemon::items::Item::ModelCase::kLemon:
        FU = FUModel::kLemon;
        break;
    case game::battlemon::items::Item::ModelCase::kOutfit:
        FU = FUModel::kOutfit;
        break;
    case game::battlemon::items::Item::ModelCase::MODEL_NOT_SET:
    default:
        FU = FUModel::MODEL_NOT_SET;
        break;
    }
    return FU;
}

FUMatchType& operator<<(FUMatchType& FU, const game::battlemon::mm::MatchType& matchType)
{
    switch (matchType)
    {
    case game::battlemon::mm::MatchType::DEATH_MATCH:
        FU = FUMatchType::DEATH_MATCH;
        break;
    case game::battlemon::mm::MatchType::CATCH_THE_FLAG:
        FU = FUMatchType::CATCH_THE_FLAG;
        break;
    default:
        FU = FUMatchType::DEFAULT;
        break;
    }
    return FU;
}

game::battlemon::mm::MatchType& operator<<(game::battlemon::mm::MatchType& matchType, const FUMatchType& FU)
{
    switch (FU)
    {
    case FUMatchType::DEATH_MATCH:
        matchType = game::battlemon::mm::MatchType::DEATH_MATCH;
        break;
    case FUMatchType::CATCH_THE_FLAG:
        matchType = game::battlemon::mm::MatchType::CATCH_THE_FLAG;
        break;
    default:
        break;
    }
    return matchType;
}

FUMatchMode& operator<<(FUMatchMode& FU, const game::battlemon::mm::MatchMode& matchMode)
{
    switch (matchMode)
    {
    case game::battlemon::mm::MatchMode::EQUIPMENT:
        FU = FUMatchMode::EQUIPMENT;
        break;
    case game::battlemon::mm::MatchMode::REALISM:
        FU = FUMatchMode::REALISM;
        break;
    case game::battlemon::mm::MatchMode::NONE:
    default:
        FU = FUMatchMode::NONE;
        break;
    }
    return FU;
}

game::battlemon::mm::MatchMode& operator<<(game::battlemon::mm::MatchMode& matchMode, const FUMatchMode& FU)
{
    switch (FU)
    {
    case FUMatchMode::EQUIPMENT:
        matchMode = game::battlemon::mm::MatchMode::EQUIPMENT;
        break;
    case FUMatchMode::REALISM:
        matchMode = game::battlemon::mm::MatchMode::REALISM;
        break;
    case FUMatchMode::NONE:
    default:
        matchMode = game::battlemon::mm::MatchMode::NONE;
        break;
    }
    return matchMode;
}

game::battlemon::mm::SearchGameResponseStatus& operator<<(game::battlemon::mm::SearchGameResponseStatus& searchGameResponseStatus, const FUSearchGameResponseStatus& FU)
{
    switch (FU)
    {
    case FUSearchGameResponseStatus::OK:
        searchGameResponseStatus = game::battlemon::mm::SearchGameResponseStatus::OK;
        break;
    case FUSearchGameResponseStatus::NFT_ERROR:
        searchGameResponseStatus = game::battlemon::mm::SearchGameResponseStatus::NFT_ERROR;
        break;
    case FUSearchGameResponseStatus::ALREADY_IN_QUEUE:
        searchGameResponseStatus = game::battlemon::mm::SearchGameResponseStatus::ALREADY_IN_QUEUE;
        break;
    case FUSearchGameResponseStatus::GAMEMODE_ERROR:
        searchGameResponseStatus = game::battlemon::mm::SearchGameResponseStatus::GAMEMODE_ERROR;
        break;
    case FUSearchGameResponseStatus::INVALID_REQUEST:
        searchGameResponseStatus = game::battlemon::mm::SearchGameResponseStatus::INVALID_REQUEST;
        break;
    case FUSearchGameResponseStatus::INTERNAL_ERROR:
        searchGameResponseStatus = game::battlemon::mm::SearchGameResponseStatus::INTERNAL_ERROR;
        break;
    }
    return searchGameResponseStatus;
}

FUSearchGameResponseStatus& operator<<(FUSearchGameResponseStatus& FU, const game::battlemon::mm::SearchGameResponseStatus& searchGameResponseStatus)
{
    switch (searchGameResponseStatus)
    {
    case game::battlemon::mm::SearchGameResponseStatus::OK:
        FU = FUSearchGameResponseStatus::OK;
        break;
    case game::battlemon::mm::SearchGameResponseStatus::NFT_ERROR:
        FU = FUSearchGameResponseStatus::NFT_ERROR;
        break;
    case game::battlemon::mm::SearchGameResponseStatus::ALREADY_IN_QUEUE:
        FU = FUSearchGameResponseStatus::ALREADY_IN_QUEUE;
        break;
    case game::battlemon::mm::SearchGameResponseStatus::GAMEMODE_ERROR:
        FU = FUSearchGameResponseStatus::GAMEMODE_ERROR;
        break;
    case game::battlemon::mm::SearchGameResponseStatus::INVALID_REQUEST:
        FU = FUSearchGameResponseStatus::INVALID_REQUEST;
        break;
    case game::battlemon::mm::SearchGameResponseStatus::INTERNAL_ERROR:
        FU = FUSearchGameResponseStatus::INTERNAL_ERROR;
        break;
    }
    return FU;
}
