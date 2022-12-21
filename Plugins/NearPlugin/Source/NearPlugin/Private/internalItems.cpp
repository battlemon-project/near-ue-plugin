#include"internalItems.h"

FUIsOwnerRequest& FUIsOwnerRequest::operator=(const game::battlemon::items::internal::IsOwnerRequest& grpcIsOwnerRequest)
{
	int size = grpcIsOwnerRequest.nft_ids().size();
	nft_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		nft_ids[Idx] = CONV_CHAR_TO_FSTRING(grpcIsOwnerRequest.nft_ids(Idx).c_str());
		});
	near_id = CONV_CHAR_TO_FSTRING(grpcIsOwnerRequest.near_id().c_str());
	return *this;
}


FUIsOwnerResponse& FUIsOwnerResponse::operator=(const game::battlemon::items::internal::IsOwnerResponse& grpcIsOwnerResponse)
{
	result = grpcIsOwnerResponse.result();
	return *this;
}


FUInternalLemonsInfoRequest& FUInternalLemonsInfoRequest::operator=(const game::battlemon::items::internal::InternalLemonsInfoRequest& grpcInternalLemonsInfoRequest)
{
	int size = grpcInternalLemonsInfoRequest.users_lemonids().size();
	users_lemonids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		users_lemonids[Idx] = grpcInternalLemonsInfoRequest.users_lemonids(Idx);
		});
	return *this;
}


FUInternalUserLemonID& FUInternalUserLemonID::operator=(const game::battlemon::items::internal::InternalUserLemonID& grpcInternalUserLemonID)
{
	near_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLemonID.near_id().c_str());
	lemon_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLemonID.lemon_id().c_str());
	return *this;
}


FUInternalLemonsInfoResponse& FUInternalLemonsInfoResponse::operator=(const game::battlemon::items::internal::InternalLemonsInfoResponse& grpcInternalLemonsInfoResponse)
{
	int size = grpcInternalLemonsInfoResponse.users_lemons().size();
	users_lemons.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		users_lemons[Idx] = grpcInternalLemonsInfoResponse.users_lemons(Idx);
		});
	return *this;
}


FUInternalUserLemon& FUInternalUserLemon::operator=(const game::battlemon::items::internal::InternalUserLemon& grpcInternalUserLemon)
{
	near_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLemon.near_id().c_str());
	lemon = grpcInternalUserLemon.lemon();
	return *this;
}



game::battlemon::items::internal::IsOwnerRequest &operator<<(game::battlemon::items::internal::IsOwnerRequest &grpcIsOwnerRequest, const FUIsOwnerRequest &UE)
{
		int size = UE.nft_ids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		std::string* ptr =grpcIsOwnerRequest.add_nft_ids();
		*ptr =CONV_FSTRING_TO_CHAR(UE.nft_ids[Idx]);
	}
	{
		grpcIsOwnerRequest.set_near_id(CONV_FSTRING_TO_CHAR(UE.near_id));
	}
	return grpcIsOwnerRequest;
}


game::battlemon::items::internal::IsOwnerResponse &operator<<(game::battlemon::items::internal::IsOwnerResponse &grpcIsOwnerResponse, const FUIsOwnerResponse &UE)
{
	{
		grpcIsOwnerResponse.set_result(UE.result);
	}
	return grpcIsOwnerResponse;
}


game::battlemon::items::internal::InternalLemonsInfoRequest &operator<<(game::battlemon::items::internal::InternalLemonsInfoRequest &grpcInternalLemonsInfoRequest, const FUInternalLemonsInfoRequest &UE)
{
		int size = UE.users_lemonids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::internal::InternalUserLemonID* ptr =grpcInternalLemonsInfoRequest.add_users_lemonids();
		(*ptr) << UE.users_lemonids[Idx];
	}
	return grpcInternalLemonsInfoRequest;
}


game::battlemon::items::internal::InternalUserLemonID &operator<<(game::battlemon::items::internal::InternalUserLemonID &grpcInternalUserLemonID, const FUInternalUserLemonID &UE)
{
	{
		grpcInternalUserLemonID.set_near_id(CONV_FSTRING_TO_CHAR(UE.near_id));
	}
	{
		grpcInternalUserLemonID.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	return grpcInternalUserLemonID;
}


game::battlemon::items::internal::InternalLemonsInfoResponse &operator<<(game::battlemon::items::internal::InternalLemonsInfoResponse &grpcInternalLemonsInfoResponse, const FUInternalLemonsInfoResponse &UE)
{
		int size = UE.users_lemons.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::internal::InternalUserLemon* ptr =grpcInternalLemonsInfoResponse.add_users_lemons();
		(*ptr) << UE.users_lemons[Idx];
	}
	return grpcInternalLemonsInfoResponse;
}


game::battlemon::items::internal::InternalUserLemon &operator<<(game::battlemon::items::internal::InternalUserLemon &grpcInternalUserLemon, const FUInternalUserLemon &UE)
{
	{
		grpcInternalUserLemon.set_near_id(CONV_FSTRING_TO_CHAR(UE.near_id));
	}
	{
		game::battlemon::items::Item* go = new game::battlemon::items::Item();
		*go << UE.lemon;
		grpcInternalUserLemon.set_allocated_lemon(go);
	}
	return grpcInternalUserLemon;
}

