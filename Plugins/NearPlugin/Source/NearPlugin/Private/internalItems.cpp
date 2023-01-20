#include"internalItems.h"
#include "AsyncTask.h"

RPC_InternalItemsService* UInternalItemsService::_RPC_InternalItemsService = nullptr;

RPC_InternalItemsService::RPC_InternalItemsService(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out) {}

RPC_InternalItemsService::~RPC_InternalItemsService() {}

game::battlemon::items::internal::InternalLemonsInfoResponse RPC_InternalItemsService::InternalGetLemonsInfo(grpc::ClientContext* context, const game::battlemon::items::internal::InternalLemonsInfoRequest* request)
{
	game::battlemon::items::internal::InternalLemonsInfoResponse read;
	CheckError(stub.get()->InternalGetLemonsInfo(context, *request, &read));

	if (static_cast<FInternalGetLemonsInfoDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUInternalLemonsInfoResponse*>(out) = read;
		static_cast<FInternalGetLemonsInfoDelegate*>(Delegate)->Broadcast(*static_cast<FUInternalLemonsInfoResponse*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_InternalItemsService::InternalInitUserItems(grpc::ClientContext* context, const game::battlemon::items::internal::InternalInitUserItemsRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->InternalInitUserItems(context, *request, &read));

	if (static_cast<FInternalInitUserItemsDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FInternalInitUserItemsDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

game::battlemon::common::Empty RPC_InternalItemsService::InternalRemoveUserItems(grpc::ClientContext* context, const game::battlemon::items::internal::InternalRemoveUserItemsRequest* request)
{
	game::battlemon::common::Empty read;
	CheckError(stub.get()->InternalRemoveUserItems(context, *request, &read));

	if (static_cast<FInternalRemoveUserItemsDelegate*>(Delegate)->IsBound())
	{
		*static_cast<FUEmpty*>(out) = read;
		static_cast<FInternalRemoveUserItemsDelegate*>(Delegate)->Broadcast(*static_cast<FUEmpty*>(out));
	}
	return read;
}

void UInternalItemsService::free_RPC_InternalItemsService()
{
	if (_RPC_InternalItemsService != nullptr)
	{
		if (_RPC_InternalItemsService->Task != nullptr)
		{
			switch (rpc)
			{
			case InternalItemsServiceRPC::InternalGetLemonsInfo:
				if (!CAST_ASINCTASK(FUInternalLemonsInfoResponse, RPC_InternalItemsService, game::battlemon::items::internal::InternalLemonsInfoRequest, game::battlemon::items::internal::InternalLemonsInfoResponse)(_RPC_InternalItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUInternalLemonsInfoResponse, RPC_InternalItemsService, game::battlemon::items::internal::InternalLemonsInfoRequest, game::battlemon::items::internal::InternalLemonsInfoResponse)(_RPC_InternalItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUInternalLemonsInfoResponse, RPC_InternalItemsService, game::battlemon::items::internal::InternalLemonsInfoRequest, game::battlemon::items::internal::InternalLemonsInfoResponse)(_RPC_InternalItemsService->Task);
				break;
			case InternalItemsServiceRPC::InternalInitUserItems:
				if (!CAST_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalInitUserItemsRequest, game::battlemon::common::Empty)(_RPC_InternalItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalInitUserItemsRequest, game::battlemon::common::Empty)(_RPC_InternalItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalInitUserItemsRequest, game::battlemon::common::Empty)(_RPC_InternalItemsService->Task);
				break;
			case InternalItemsServiceRPC::InternalRemoveUserItems:
				if (!CAST_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalRemoveUserItemsRequest, game::battlemon::common::Empty)(_RPC_InternalItemsService->Task)->Cancel())
				{
					CAST_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalRemoveUserItemsRequest, game::battlemon::common::Empty)(_RPC_InternalItemsService->Task)->EnsureCompletion();
				}
				delete CAST_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalRemoveUserItemsRequest, game::battlemon::common::Empty)(_RPC_InternalItemsService->Task);
				break;
			}
			_RPC_InternalItemsService->Task = nullptr;
		}
		delete _RPC_InternalItemsService;
	}
	_RPC_InternalItemsService = nullptr;
}

UInternalItemsService::UInternalItemsService() {}

UInternalItemsService::~UInternalItemsService() 
{
	free_RPC_InternalItemsService();
}

void UInternalItemsService::InternalGetLemonsInfo(TMap<FString, FString> context, FUInternalLemonsInfoRequest inp, FUInternalLemonsInfoResponse &out)
{
	free_RPC_InternalItemsService();
	rpc = InternalItemsServiceRPC::InternalGetLemonsInfo;
	game::battlemon::items::internal::InternalLemonsInfoRequest g_request;
	g_request << inp;
	_RPC_InternalItemsService = new RPC_InternalItemsService(ssl, URL, &InternalGetLemonsInfoDelegate, &out);
	CREATE_ASINCTASK(FUInternalLemonsInfoResponse, RPC_InternalItemsService, game::battlemon::items::internal::InternalLemonsInfoRequest, game::battlemon::items::internal::InternalLemonsInfoResponse);
	_RPC_InternalItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalItemsService, &out, &g_request, context, &RPC_InternalItemsService::InternalGetLemonsInfo);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalItemsService::InternalInitUserItems(TMap<FString, FString> context, FUInternalInitUserItemsRequest inp, FUEmpty &out)
{
	free_RPC_InternalItemsService();
	rpc = InternalItemsServiceRPC::InternalInitUserItems;
	game::battlemon::items::internal::InternalInitUserItemsRequest g_request;
	g_request << inp;
	_RPC_InternalItemsService = new RPC_InternalItemsService(ssl, URL, &InternalInitUserItemsDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalInitUserItemsRequest, game::battlemon::common::Empty);
	_RPC_InternalItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalItemsService, &out, &g_request, context, &RPC_InternalItemsService::InternalInitUserItems);
	GET_ASINCTASK->StartBackgroundTask();
}

void UInternalItemsService::InternalRemoveUserItems(TMap<FString, FString> context, FUInternalRemoveUserItemsRequest inp, FUEmpty &out)
{
	free_RPC_InternalItemsService();
	rpc = InternalItemsServiceRPC::InternalRemoveUserItems;
	game::battlemon::items::internal::InternalRemoveUserItemsRequest g_request;
	g_request << inp;
	_RPC_InternalItemsService = new RPC_InternalItemsService(ssl, URL, &InternalRemoveUserItemsDelegate, &out);
	CREATE_ASINCTASK(FUEmpty, RPC_InternalItemsService, game::battlemon::items::internal::InternalRemoveUserItemsRequest, game::battlemon::common::Empty);
	_RPC_InternalItemsService->Task = GET_ASINCTASK;
	GET_ASINCTASK->GetTask().SetData(_RPC_InternalItemsService, &out, &g_request, context, &RPC_InternalItemsService::InternalRemoveUserItems);
	GET_ASINCTASK->StartBackgroundTask();
}

FString UInternalItemsService::GetError()
{
	if (_RPC_InternalItemsService != nullptr)
		return _RPC_InternalItemsService->GetError();
	return FString();
}


FUInternalRemoveUserItemsRequest& FUInternalRemoveUserItemsRequest::operator=(const game::battlemon::items::internal::InternalRemoveUserItemsRequest& grpcInternalRemoveUserItemsRequest)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalRemoveUserItemsRequest.user_id().c_str());
	return *this;
}


FUInternalInitUserItemsRequest& FUInternalInitUserItemsRequest::operator=(const game::battlemon::items::internal::InternalInitUserItemsRequest& grpcInternalInitUserItemsRequest)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalInitUserItemsRequest.user_id().c_str());
	return *this;
}


FUInternalUserLemon& FUInternalUserLemon::operator=(const game::battlemon::items::internal::InternalUserLemon& grpcInternalUserLemon)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLemon.user_id().c_str());
	lemon = grpcInternalUserLemon.lemon();
	return *this;
}


FUInternalLemonsInfoResponse& FUInternalLemonsInfoResponse::operator=(const game::battlemon::items::internal::InternalLemonsInfoResponse& grpcInternalLemonsInfoResponse)
{
{
	int size = grpcInternalLemonsInfoResponse.user_lemons().size();
	user_lemons.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		user_lemons[Idx] = grpcInternalLemonsInfoResponse.user_lemons(Idx);
		});

	}
	return *this;
}


FUInternalUserLemonID& FUInternalUserLemonID::operator=(const game::battlemon::items::internal::InternalUserLemonID& grpcInternalUserLemonID)
{
	user_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLemonID.user_id().c_str());
	lemon_id = CONV_CHAR_TO_FSTRING(grpcInternalUserLemonID.lemon_id().c_str());
	return *this;
}


FUInternalLemonsInfoRequest& FUInternalLemonsInfoRequest::operator=(const game::battlemon::items::internal::InternalLemonsInfoRequest& grpcInternalLemonsInfoRequest)
{
{
	int size = grpcInternalLemonsInfoRequest.user_lemonids().size();
	user_lemonids.SetNum(size);
	ParallelFor(size, [&](int32 Idx)
		{
		user_lemonids[Idx] = grpcInternalLemonsInfoRequest.user_lemonids(Idx);
		});

	}
	return *this;
}



game::battlemon::items::internal::InternalRemoveUserItemsRequest &operator<<(game::battlemon::items::internal::InternalRemoveUserItemsRequest &grpcInternalRemoveUserItemsRequest, const FUInternalRemoveUserItemsRequest &UE)
{
	{
		grpcInternalRemoveUserItemsRequest.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	return grpcInternalRemoveUserItemsRequest;
}


game::battlemon::items::internal::InternalInitUserItemsRequest &operator<<(game::battlemon::items::internal::InternalInitUserItemsRequest &grpcInternalInitUserItemsRequest, const FUInternalInitUserItemsRequest &UE)
{
	{
		grpcInternalInitUserItemsRequest.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	return grpcInternalInitUserItemsRequest;
}


game::battlemon::items::internal::InternalUserLemon &operator<<(game::battlemon::items::internal::InternalUserLemon &grpcInternalUserLemon, const FUInternalUserLemon &UE)
{
	{
		grpcInternalUserLemon.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		game::battlemon::items::Item* go = new game::battlemon::items::Item();
		*go << UE.lemon;
		grpcInternalUserLemon.set_allocated_lemon(go);
	}
	return grpcInternalUserLemon;
}


game::battlemon::items::internal::InternalLemonsInfoResponse &operator<<(game::battlemon::items::internal::InternalLemonsInfoResponse &grpcInternalLemonsInfoResponse, const FUInternalLemonsInfoResponse &UE)
{
		int size = UE.user_lemons.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::internal::InternalUserLemon* ptr =grpcInternalLemonsInfoResponse.add_user_lemons();
		(*ptr) << UE.user_lemons[Idx];
	}
	return grpcInternalLemonsInfoResponse;
}


game::battlemon::items::internal::InternalUserLemonID &operator<<(game::battlemon::items::internal::InternalUserLemonID &grpcInternalUserLemonID, const FUInternalUserLemonID &UE)
{
	{
		grpcInternalUserLemonID.set_user_id(CONV_FSTRING_TO_CHAR(UE.user_id));
	}
	{
		grpcInternalUserLemonID.set_lemon_id(CONV_FSTRING_TO_CHAR(UE.lemon_id));
	}
	return grpcInternalUserLemonID;
}


game::battlemon::items::internal::InternalLemonsInfoRequest &operator<<(game::battlemon::items::internal::InternalLemonsInfoRequest &grpcInternalLemonsInfoRequest, const FUInternalLemonsInfoRequest &UE)
{
		int size = UE.user_lemonids.Num(); 
	for(size_t Idx = 0; Idx < size; Idx++)
	{
		game::battlemon::items::internal::InternalUserLemonID* ptr =grpcInternalLemonsInfoRequest.add_user_lemonids();
		(*ptr) << UE.user_lemonids[Idx];
	}
	return grpcInternalLemonsInfoRequest;
}

