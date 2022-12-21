#include"internalUpdates.h"

FUInternalUpdate& FUInternalUpdate::operator=(const game::battlemon::updates::InternalUpdate& grpcInternalUpdate)
{
	int size = grpcInternalUpdate.near_ids().size();
	near_ids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		near_ids[Idx] = CONV_CHAR_TO_FSTRING(grpcInternalUpdate.near_ids(Idx).c_str());
		});
	message = CONV_CHAR_TO_FSTRING(grpcInternalUpdate.message().c_str());
	remove_on_fail = grpcInternalUpdate.remove_on_fail();
	return *this;
}



game::battlemon::updates::InternalUpdate &operator<<(game::battlemon::updates::InternalUpdate &grpcInternalUpdate, const FUInternalUpdate &UE)
{
		int size = UE.near_ids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		std::string* ptr =grpcInternalUpdate.add_near_ids();
		*ptr =CONV_FSTRING_TO_CHAR(UE.near_ids[Idx]);
	}
	{
		grpcInternalUpdate.set_message(CONV_FSTRING_TO_CHAR(UE.message));
	}
	{
		grpcInternalUpdate.set_remove_on_fail(UE.remove_on_fail);
	}
	return grpcInternalUpdate;
}

