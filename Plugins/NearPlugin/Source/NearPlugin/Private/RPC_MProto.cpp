
#include "RPC_MProto.h"
#include "NearAuth.h"

#include "AsyncTask.h"

gRPC_SuiAuth* USuiAuth::_gRPC_SuiAuth = nullptr;
gRPC_ClientItems* UNearItems::gRPC_Item = nullptr;
gRPC_ClientMM* UNearMM::gRPC_MM = nullptr;
gRPC_ClientInternalMM* UNearInternalMM::gRPC_InternalMM = nullptr;


gRPC_SuiAuth::gRPC_SuiAuth(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out)
{
}

game::battlemon::auth::WalletAddressResponse gRPC_SuiAuth::CallRPCGetWalletAddress(game::battlemon::auth::WalletAddressRequest* request)
{
    UE_LOG_REQUEST("write client_id %s", request->client_id());
    game::battlemon::auth::WalletAddressResponse read;

    grpc::ClientContext context;
    CheckError(stub.get()->GetWalletAddress(&context, *request, &read));

    if (static_cast<FGetWalletAddressDelegate*>(Delegate)->IsBound())
    {
        *static_cast<FUWalletAddressResponse*>(out) = read;
        static_cast<FGetWalletAddressDelegate*>(Delegate)->Broadcast(*static_cast<FUWalletAddressResponse*>(out));
    }
    return read;
}

/// items.rpc
gRPC_ClientItems::gRPC_ClientItems(const bool& ssl, FString& url, void* _getItemsDelegate, void* _out) :gRPC_Stub(ssl, url), getItemsDelegate(_getItemsDelegate), out(_out)
{
}

game::battlemon::items::ItemsResponse gRPC_ClientItems::CallRPC_GetItems()
{
    game::battlemon::items::ItemsResponse read;
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::items::ItemsRequest write;

        std::string meta[2] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[2] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        CheckError(stub.get()->GetItems(&context, write, &read));
    }

    if (static_cast<FGetItemsDelegate*>(getItemsDelegate)->IsBound())
    {
        *static_cast<FUItemsResponse*>(out) = read;
        static_cast<FGetItemsDelegate*>(getItemsDelegate)->Broadcast(*static_cast<FUItemsResponse*>(out));
    }

    return read;
}


game::battlemon::items::GetBundlesResponse gRPC_ClientItems::CallRPC_GetBundles()
{
    game::battlemon::items::GetBundlesResponse read;
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::items::GetBundlesRequest write;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        CheckError(stub.get()->GetBundles(&context, write, &read));
    }

    if (static_cast<FGetBundlesDelegate*>(getItemsDelegate)->IsBound())
    {
        *static_cast<FUGetBundlesResponse*>(out) = read;
        static_cast<FGetBundlesDelegate*>(getItemsDelegate)->Broadcast(*static_cast<FUGetBundlesResponse*>(out));
    }
    return read;
}


game::battlemon::items::WeaponBundle gRPC_ClientItems::CallRPC_EditBundle(game::battlemon::items::EditBundleRequest* request)
{
    game::battlemon::items::WeaponBundle read;
    if (UNearAuth::client != nullptr)
    {

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        CheckError(stub.get()->EditBundle(&context, *request, &read));
    }
    if (static_cast<FEditBundleDelegate*>(getItemsDelegate)->IsBound())
    {
        *static_cast<FUWeaponBundle*>(out) = read;
        static_cast<FEditBundleDelegate*>(getItemsDelegate)->Broadcast(*static_cast<FUWeaponBundle*>(out));
    }
    return read;
}

bool gRPC_ClientItems::CallRPC_AttachBundle(game::battlemon::items::AttachBundleRequest* request)
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        if (static_cast<FBoolDelegate*>(getItemsDelegate)->IsBound())
        {
            *static_cast<bool*>(out) = true;
            static_cast<FBoolDelegate*>(getItemsDelegate)->Broadcast(*static_cast<bool*>(out));
        }
        return CheckError(stub.get()->AttachBundle(&context, *request, &read));
    }
    if (static_cast<FBoolDelegate*>(getItemsDelegate)->IsBound())
    {
        *static_cast<bool*>(out) = false;
        static_cast<FBoolDelegate*>(getItemsDelegate)->Broadcast(*static_cast<bool*>(out));
    }
    return false;
}

bool gRPC_ClientItems::CallRPC_DetachBundle(game::battlemon::items::DetachBundleRequest* request)
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        if (static_cast<FBoolDelegate*>(getItemsDelegate)->IsBound())
        {
            *static_cast<bool*>(out) = true;
            static_cast<FBoolDelegate*>(getItemsDelegate)->Broadcast(*static_cast<bool*>(out));
        }
        return CheckError(stub.get()->DetachBundle(&context, *request, &read));
    }
    if (static_cast<FBoolDelegate*>(getItemsDelegate)->IsBound())
    {
        *static_cast<bool*>(out) = false;
        static_cast<FBoolDelegate*>(getItemsDelegate)->Broadcast(*static_cast<bool*>(out));
    }
    return false;
}

/// items.rpc end


/// mm.rpc
gRPC_ClientMM::gRPC_ClientMM(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out)
{
}

game::battlemon::mm::SearchGameResponse gRPC_ClientMM::CallRPC_SearchGame(game::battlemon::mm::SearchGameRequest* Request)
{
    game::battlemon::mm::SearchGameResponse read;
    if (UNearAuth::client != nullptr)
    {
        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        CheckError(stub.get()->SearchGame(&context, *Request, &read));
    }
    //FSearchGameDelegate
    if (static_cast<FSearchGameDelegate*>(Delegate)->IsBound())
    {
        *static_cast<FUSearchGameResponse*>(out) = read;
        static_cast<FSearchGameDelegate*>(Delegate)->Broadcast(*static_cast<FUSearchGameResponse*>(out));
    }
    return read;
}

bool gRPC_ClientMM::CallRPC_AcceptGame(game::battlemon::mm::AcceptGameRequest* Request)
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);
        *static_cast<bool*>(out) = true;

        if (static_cast<FBoolDelegate*>(Delegate)->IsBound())
        {
            static_cast<FBoolDelegate*>(Delegate)->Broadcast(*static_cast<bool*>(out));
        }
        return *static_cast<bool*>(out);

        
    }
    *static_cast<bool*>(out) = false;
    return false;
}

bool gRPC_ClientMM::CallRPC_CancelSearch()
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::mm::CancelSearchRequest write;
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        if (static_cast<FBoolDelegate*>(Delegate)->IsBound())
        {
            *static_cast<bool*>(out) = CheckError(stub.get()->CancelSearch(&context, write, &read));
            static_cast<FBoolDelegate*>(Delegate)->Broadcast(*static_cast<bool*>(out));
        }
        return  *static_cast<bool*>(out);
    }
    if (static_cast<FBoolDelegate*>(Delegate)->IsBound())
    {
        *static_cast<bool*>(out) = false;
        static_cast<FBoolDelegate*>(Delegate)->Broadcast(*static_cast<bool*>(out));
    }
    return false;
}


/// mm.rpc end

/// InternalMM.rpc
gRPC_ClientInternalMM::gRPC_ClientInternalMM(const bool& ssl, FString& url, void* _Delegate, void* _out) :gRPC_Stub(ssl, url), Delegate(_Delegate), out(_out)
{
}

bool gRPC_ClientInternalMM::CallRPC_UserLeftBattle(game::battlemon::mm::internal::InternalUserLeftBattleRequest* Request)
{
    game::battlemon::common::Empty read;
    grpc::ClientContext context;

    *static_cast<bool*>(out) = CheckError(stub.get()->UserLeftBattle(&context, *Request, &read));
    if (static_cast<FBoolDelegate*>(Delegate)->IsBound())
    {
        static_cast<FBoolDelegate*>(Delegate)->Broadcast(*static_cast<bool*>(out));
    }
    return  *static_cast<bool*>(out);
}

bool gRPC_ClientInternalMM::CallRPC_SaveBattleResult(game::battlemon::mm::internal::SaveBattleResultRequest* Request)
{
    game::battlemon::common::Empty read;
    grpc::ClientContext context;

    *static_cast<bool*>(out) = CheckError(stub.get()->SaveBattleResult(&context, *Request, &read));

    if (static_cast<FBoolDelegate*>(Delegate)->IsBound())
    {
        static_cast<FBoolDelegate*>(Delegate)->Broadcast(*static_cast<bool*>(out));
    }
    return  *static_cast<bool*>(out);
}

game::battlemon::mm::internal::RoomInfoResponse gRPC_ClientInternalMM::CallRPC_GetRoomInfo(game::battlemon::mm::internal::RoomInfoRequest* Request)
{
    game::battlemon::mm::internal::RoomInfoResponse read;

    grpc::ClientContext context;
    CheckError(stub.get()->GetRoomInfo(&context, *Request, &read));
    if (static_cast<FGetRoomInfoDelegate*>(Delegate)->IsBound())
    {
        *static_cast<FURoomInfoResponse*>(out) = read;
        static_cast<FGetRoomInfoDelegate*>(Delegate)->Broadcast(*static_cast<FURoomInfoResponse*>(out));
    }
    return read;
}

game::battlemon::mm::internal::RoomInfoResponse gRPC_ClientInternalMM::CallRPC_CreateRoomWithPlayers(game::battlemon::mm::internal::CreateRoomRequest* Request)
{
    game::battlemon::mm::internal::RoomInfoResponse read;
    grpc::ClientContext context;

    CheckError(stub.get()->CreateRoomWithPlayers(&context, *Request, &read));
    return read;
}

bool gRPC_ClientInternalMM::CallRPC_DedicatedServerIsReady(game::battlemon::mm::internal::DedicatedServerIsReadyRequest* Request)
{
    game::battlemon::common::Empty read;
    grpc::ClientContext context;

    *static_cast<bool*>(out) = CheckError(stub.get()->DedicatedServerIsReady(&context, *Request, &read));
    if (static_cast<FBoolDelegate*>(Delegate)->IsBound())
    {
        static_cast<FBoolDelegate*>(Delegate)->Broadcast(*static_cast<bool*>(out));
    }
    return  *static_cast<bool*>(out);
}


/// InternalMM.rpc end

void USuiAuth::free_gRPC_SuiAuth()
{
    if (_gRPC_SuiAuth != nullptr)
    {
        if (_gRPC_SuiAuth->Task != nullptr)
        {
            if (!CAST_ASINCTASK(FUWalletAddressResponse, gRPC_SuiAuth, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse)(_gRPC_SuiAuth->Task)->Cancel())
            {
                CAST_ASINCTASK(FUWalletAddressResponse, gRPC_SuiAuth, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse)(_gRPC_SuiAuth->Task)->EnsureCompletion();
            }
            delete CAST_ASINCTASK(FUWalletAddressResponse, gRPC_SuiAuth, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse)(_gRPC_SuiAuth->Task);
            _gRPC_SuiAuth->Task = nullptr;
        }
        delete _gRPC_SuiAuth;
    }
    _gRPC_SuiAuth = nullptr;
}

USuiAuth::USuiAuth()
{
}

USuiAuth::~USuiAuth()
{
    free_gRPC_SuiAuth();
}


void USuiAuth::GetWalletAddress(FUWalletAddressRequest Request, FUWalletAddressResponse& out)
{
    free_gRPC_SuiAuth();

    _gRPC_SuiAuth = new gRPC_SuiAuth(ssl, URL, &GetWalletAddressDelegate, &out);

    game::battlemon::auth::WalletAddressRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(FUWalletAddressResponse, gRPC_SuiAuth, game::battlemon::auth::WalletAddressRequest, game::battlemon::auth::WalletAddressResponse);
    _gRPC_SuiAuth->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(_gRPC_SuiAuth, &structResultDelegate, &out, &g_request, &gRPC_SuiAuth::CallRPCGetWalletAddress);
    GET_ASINCTASK->StartBackgroundTask();
}

FString USuiAuth::GetError()
{
    if (_gRPC_SuiAuth != nullptr)
        return _gRPC_SuiAuth->GetError();
    return FString();
}

void UNearItems::freegRPC_Item()
{
    if (gRPC_Item != nullptr)
    {
        if (gRPC_Item->Task != nullptr)
        {
            switch (rpc)
            {
            case ItemsRPC::GetItems:
                if (!CAST_ASINCTASK(FUItemsResponse, gRPC_ClientItems, void*, game::battlemon::items::ItemsResponse)(gRPC_Item->Task)->Cancel())
                {
                    CAST_ASINCTASK(FUItemsResponse, gRPC_ClientItems, void*, game::battlemon::items::ItemsResponse)(gRPC_Item->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(FUItemsResponse, gRPC_ClientItems, void*, game::battlemon::items::ItemsResponse)(gRPC_Item->Task);
                break;
            case ItemsRPC::GetBundles:
                if (!CAST_ASINCTASK(FUGetBundlesResponse, gRPC_ClientItems, void*, game::battlemon::items::GetBundlesResponse)(gRPC_Item->Task)->Cancel())
                {
                    CAST_ASINCTASK(FUGetBundlesResponse, gRPC_ClientItems, void*, game::battlemon::items::GetBundlesResponse)(gRPC_Item->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(FUGetBundlesResponse, gRPC_ClientItems, void*, game::battlemon::items::GetBundlesResponse)(gRPC_Item->Task);
                break;
            case ItemsRPC::EditBundle:
                if (!CAST_ASINCTASK(FUWeaponBundle, gRPC_ClientItems, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle)(gRPC_Item->Task)->Cancel())
                {
                    CAST_ASINCTASK(FUWeaponBundle, gRPC_ClientItems, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle)(gRPC_Item->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(FUWeaponBundle, gRPC_ClientItems, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle)(gRPC_Item->Task);
                break;
            case ItemsRPC::AttachBundle:
                if (!CAST_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::AttachBundleRequest, bool)(gRPC_Item->Task)->Cancel())
                {
                    CAST_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::AttachBundleRequest, bool)(gRPC_Item->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::AttachBundleRequest, bool)(gRPC_Item->Task);
                break;
            case ItemsRPC::DetachBundle:
                if (!CAST_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::DetachBundleRequest, bool)(gRPC_Item->Task))
                {
                    CAST_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::DetachBundleRequest, bool)(gRPC_Item->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::DetachBundleRequest, bool)(gRPC_Item->Task);
                break;
            default:
                break;
            }
            gRPC_Item->Task = nullptr;
        }
        delete gRPC_Item;
    }
    gRPC_Item = nullptr;
}

UNearItems::UNearItems()
{
}

UNearItems::~UNearItems()
{
    freegRPC_Item();
}


void UNearItems::GetItems(FUItemsResponse& out)
{
    freegRPC_Item();
    rpc = ItemsRPC::GetItems;
    gRPC_Item = new gRPC_ClientItems(ssl, URL, &getItemsDelegate, &out);
    CREATE_ASINCTASK(FUItemsResponse, gRPC_ClientItems, void*, game::battlemon::items::ItemsResponse);
    gRPC_Item->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_Item, &structResultDelegate, &out, &gRPC_ClientItems::CallRPC_GetItems);
    GET_ASINCTASK->StartBackgroundTask();
    //out = gRPC_Item->CallRPC_GetItems();

}

void UNearItems::GetBundles(FUGetBundlesResponse& out)
{
    freegRPC_Item();
    rpc = ItemsRPC::GetBundles;
    gRPC_Item = new gRPC_ClientItems(ssl, URL, &getBundlesDelegate, &out);

    CREATE_ASINCTASK(FUGetBundlesResponse, gRPC_ClientItems, void*, game::battlemon::items::GetBundlesResponse);
    gRPC_Item->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_Item, &structResultDelegate, &out, &gRPC_ClientItems::CallRPC_GetBundles);
    GET_ASINCTASK->StartBackgroundTask();

    //out = gRPC_Item->CallRPC_GetBundles();
}

void UNearItems::EditBundle(FUEditBundleRequest Request, FUWeaponBundle& out)
{
    freegRPC_Item();
    rpc = ItemsRPC::EditBundle;
    gRPC_Item = new gRPC_ClientItems(ssl, URL, &editBundleDelegate, &out);

    game::battlemon::items::EditBundleRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(FUWeaponBundle, gRPC_ClientItems, game::battlemon::items::EditBundleRequest, game::battlemon::items::WeaponBundle);
    gRPC_Item->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_Item, &structResultDelegate, &out, &g_request, &gRPC_ClientItems::CallRPC_EditBundle);
    GET_ASINCTASK->StartBackgroundTask();
    //out = gRPC_Item->CallRPC_EditBundle(g_request);
}

bool UNearItems::AttachBundle(FUAttachBundleRequest Request, bool& out)
{
    freegRPC_Item();
    rpc = ItemsRPC::AttachBundle;
    gRPC_Item = new gRPC_ClientItems(ssl, URL, &AttachBundleDelegate, &out);

    game::battlemon::items::AttachBundleRequest g_request;

    g_request << Request;


    CREATE_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::AttachBundleRequest, bool);
    gRPC_Item->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_Item, &structResultDelegate, &out, &g_request, &gRPC_ClientItems::CallRPC_AttachBundle);
    GET_ASINCTASK->StartBackgroundTask();

    return out;
    //return gRPC_Item->CallRPC_AttachBundle(g_request);
}

bool UNearItems::DetachBundle(FUDetachBundleRequest Request, bool& out)
{
    freegRPC_Item();
    rpc = ItemsRPC::DetachBundle;
    gRPC_Item = new gRPC_ClientItems(ssl, URL, &DetachBundleDelegate, &out);

    game::battlemon::items::DetachBundleRequest g_request;

    g_request << Request;

    CREATE_ASINCTASK(bool, gRPC_ClientItems, game::battlemon::items::DetachBundleRequest, bool);
    gRPC_Item->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_Item, &structResultDelegate, &out, &g_request, &gRPC_ClientItems::CallRPC_DetachBundle);
    GET_ASINCTASK->StartBackgroundTask();

    return out;
    //return gRPC_Item->CallRPC_DetachBundle(g_request);
}

FString UNearItems::GetError()
{
    if (gRPC_Item != nullptr)
        return gRPC_Item->GetError();
    return FString();
}

void UNearMM::freegRPC_MM()
{
    if (gRPC_MM != nullptr)
    {
        if (gRPC_MM->Task != nullptr)
        {
            switch (rpc)
            {
            case MMRPC::SearchGame:
                if (!CAST_ASINCTASK(FUSearchGameResponse, gRPC_ClientMM, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse)(gRPC_MM->Task)->Cancel())
                {
                    CAST_ASINCTASK(FUSearchGameResponse, gRPC_ClientMM, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse)(gRPC_MM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(FUSearchGameResponse, gRPC_ClientMM, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse)(gRPC_MM->Task);
                break;
            case MMRPC::AcceptGame:
                if (!CAST_ASINCTASK(bool, gRPC_ClientMM, game::battlemon::mm::AcceptGameRequest, bool)(gRPC_MM->Task)->Cancel())
                {
                    CAST_ASINCTASK(bool, gRPC_ClientMM, game::battlemon::mm::AcceptGameRequest, bool)(gRPC_MM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientMM, game::battlemon::mm::AcceptGameRequest, bool)(gRPC_MM->Task);
                break;
            case MMRPC::CancelSearch:
                if (!CAST_ASINCTASK(bool, gRPC_ClientMM, void*, bool)(gRPC_MM->Task)->Cancel())
                {
                    CAST_ASINCTASK(bool, gRPC_ClientMM, void*, bool)(gRPC_MM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientMM, void*, bool)(gRPC_MM->Task);
                break;
            default:
                break;
            }
            gRPC_MM->Task = nullptr;
        }
        delete gRPC_MM;
    }
    gRPC_MM = nullptr;
}

UNearMM::UNearMM()
{

}

UNearMM::~UNearMM()
{
    freegRPC_MM();
}


void UNearMM::SearchGame(FUSearchGameRequest Request, FUSearchGameResponse& out)
{
    freegRPC_MM();
    rpc = MMRPC::SearchGame;
    gRPC_MM = new gRPC_ClientMM(ssl, URL, &SearchGameDelegate, &out);
    game::battlemon::mm::SearchGameRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(FUSearchGameResponse, gRPC_ClientMM, game::battlemon::mm::SearchGameRequest, game::battlemon::mm::SearchGameResponse);
    gRPC_MM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_MM, &structResultDelegate, &out, &g_request, &gRPC_ClientMM::CallRPC_SearchGame);
    GET_ASINCTASK->StartBackgroundTask();

    //out = gRPC_MM->CallRPC_SearchGame(g_request);
}

bool UNearMM::AcceptGame(FUAcceptGameRequest Request, bool& out)
{
    freegRPC_MM();
    rpc = MMRPC::AcceptGame;
    gRPC_MM = new gRPC_ClientMM(ssl, URL, &AcceptGameDelegate, &out);
    game::battlemon::mm::AcceptGameRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(bool, gRPC_ClientMM, game::battlemon::mm::AcceptGameRequest, bool);
    gRPC_MM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_MM, &structResultDelegate, &out, &g_request, &gRPC_ClientMM::CallRPC_AcceptGame);
    GET_ASINCTASK->StartBackgroundTask();

    return out;//gRPC_MM->CallRPC_AcceptGame(g_request);
}

bool UNearMM::CancelSearch(bool& out)
{
    freegRPC_MM();
    rpc = MMRPC::CancelSearch;
    gRPC_MM = new gRPC_ClientMM(ssl, URL, &CancelSearchDelegate, &out);

    CREATE_ASINCTASK(bool, gRPC_ClientMM, void*, bool);
    gRPC_MM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_MM, &structResultDelegate, &out, &gRPC_ClientMM::CallRPC_CancelSearch);
    GET_ASINCTASK->StartBackgroundTask();

    return out;// gRPC_MM->CallRPC_CancelSearch();
}

FString UNearMM::GetError()
{
    if (gRPC_MM != nullptr)
        return gRPC_MM->GetError();
    return FString();
}

void UNearInternalMM::freegRPC_InternalMM()
{
    if (gRPC_InternalMM != nullptr)
    {
        if (gRPC_InternalMM->Task != nullptr)
        {
            switch (rpc)
            {
            case InternalMMRPC::UserLeftBattle:
                if (!CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::InternalUserLeftBattleRequest, bool)(gRPC_InternalMM->Task)->Cancel())
                {
                    CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::InternalUserLeftBattleRequest, bool)(gRPC_InternalMM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::InternalUserLeftBattleRequest, bool)(gRPC_InternalMM->Task);
                break;
            case InternalMMRPC::SaveBattleResult:
                if (!CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::SaveBattleResultRequest, bool)(gRPC_InternalMM->Task)->Cancel())
                {
                    CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::SaveBattleResultRequest, bool)(gRPC_InternalMM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::SaveBattleResultRequest, bool)(gRPC_InternalMM->Task);
                break;
            case InternalMMRPC::GetRoomInfo:
                if (!CAST_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse)(gRPC_InternalMM->Task)->Cancel())
                {
                    CAST_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse)(gRPC_InternalMM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse)(gRPC_InternalMM->Task);
                break;
            case InternalMMRPC::CreateRoomWithPlayers:
                if (!CAST_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse)(gRPC_InternalMM->Task)->Cancel())
                {
                    CAST_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse)(gRPC_InternalMM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse)(gRPC_InternalMM->Task);
                break;
            case InternalMMRPC::DedicatedServerIsReady:
                if (!CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, bool)(gRPC_InternalMM->Task)->Cancel())
                {
                    CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, bool)(gRPC_InternalMM->Task)->EnsureCompletion();
                }
                delete CAST_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, bool)(gRPC_InternalMM->Task);
                break;
            default:
                break;
            }
            gRPC_InternalMM->Task = nullptr;
        }
        delete gRPC_InternalMM;
    }
    gRPC_InternalMM = nullptr;

}

UNearInternalMM::UNearInternalMM()
{
}

UNearInternalMM::~UNearInternalMM()
{
    freegRPC_InternalMM();
}

bool UNearInternalMM::UserLeftBattle(FUInternalUserLeftBattleRequest Request, bool& out)
{
    freegRPC_InternalMM();
    rpc = InternalMMRPC::UserLeftBattle;
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL, &userLeftBattleDelegate, &out);
    game::battlemon::mm::internal::InternalUserLeftBattleRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::InternalUserLeftBattleRequest, bool);
    gRPC_InternalMM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_InternalMM, &structResultDelegate, &out, &g_request, &gRPC_ClientInternalMM::CallRPC_UserLeftBattle);
    GET_ASINCTASK->StartBackgroundTask();

    return out;//  gRPC_InternalMM->CallRPC_UserLeftBattle(g_request);
}

bool UNearInternalMM::SaveBattleResult(FUSaveBattleResultRequest Request, bool& out)
{
    freegRPC_InternalMM();
    rpc = InternalMMRPC::SaveBattleResult;
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL, &saveBattleResultDelegate, &out);

    game::battlemon::mm::internal::SaveBattleResultRequest g_request;

    g_request << Request;

    CREATE_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::SaveBattleResultRequest, bool);
    gRPC_InternalMM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_InternalMM, &structResultDelegate, &out, &g_request, &gRPC_ClientInternalMM::CallRPC_SaveBattleResult);
    GET_ASINCTASK->StartBackgroundTask();

    return out;// gRPC_InternalMM->CallRPC_SaveBattleResult(g_request);
}

void UNearInternalMM::GetRoomInfo(FURoomInfoRequest Request, FURoomInfoResponse& out)
{
    freegRPC_InternalMM();
    rpc = InternalMMRPC::GetRoomInfo;
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL, &getRoomInfoDelegate, &out);
    
    game::battlemon::mm::internal::RoomInfoRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::RoomInfoRequest, game::battlemon::mm::internal::RoomInfoResponse);
    gRPC_InternalMM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_InternalMM, &structResultDelegate, &out, &g_request, &gRPC_ClientInternalMM::CallRPC_GetRoomInfo);
    GET_ASINCTASK->StartBackgroundTask();

    //out = gRPC_InternalMM->CallRPC_GetRoomInfo(g_request);
}

void UNearInternalMM::CreateRoomWithPlayers(FUCreateRoomRequest Request, FURoomInfoResponse& out)
{
    freegRPC_InternalMM();
    rpc = InternalMMRPC::CreateRoomWithPlayers;
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL, &createRoomWithPlayersDelegate, &out);

    game::battlemon::mm::internal::CreateRoomRequest g_request;
    g_request << Request;


    CREATE_ASINCTASK(FURoomInfoResponse, gRPC_ClientInternalMM, game::battlemon::mm::internal::CreateRoomRequest, game::battlemon::mm::internal::RoomInfoResponse);
    gRPC_InternalMM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_InternalMM, &structResultDelegate, &out, &g_request, &gRPC_ClientInternalMM::CallRPC_CreateRoomWithPlayers);
    GET_ASINCTASK->StartBackgroundTask();

    //out = gRPC_InternalMM->CallRPC_CreateRoomWithPlayers(g_request);
}

bool UNearInternalMM::DedicatedServerIsReady(FUDedicatedServerIsReadyRequest Request, bool& out)
{
    freegRPC_InternalMM();
    rpc = InternalMMRPC::DedicatedServerIsReady;
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL, &dedicatedServerIsReadyDelegate, &out);
    game::battlemon::mm::internal::DedicatedServerIsReadyRequest g_request;
    g_request << Request;

    CREATE_ASINCTASK(bool, gRPC_ClientInternalMM, game::battlemon::mm::internal::DedicatedServerIsReadyRequest, bool);
    gRPC_InternalMM->Task = GET_ASINCTASK;
    GET_ASINCTASK->GetTask().SetData(gRPC_InternalMM, &structResultDelegate, &out, &g_request, &gRPC_ClientInternalMM::CallRPC_DedicatedServerIsReady);
    GET_ASINCTASK->StartBackgroundTask();

    return out;//  gRPC_InternalMM->CallRPC_DedicatedServerIsReady(g_request);
}

FString UNearInternalMM::GetError()
{
    if (gRPC_InternalMM != nullptr)
        return gRPC_InternalMM->GetError();
    return FString();
}

FString UNearInternalMM::GetEnvironmentVariable(FString VarName)
{
#if PLATFORM_UNIX
    return FUnixPlatformMisc::GetEnvironmentVariable(*VarName);
#elif PLATFORM_WINDOWS
    return FWindowsPlatformMisc::GetEnvironmentVariable(*VarName);
#endif
    return FGenericPlatformMisc::GetEnvironmentVariable(*VarName);
}