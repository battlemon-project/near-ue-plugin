
#include "RPC_MProto.h"
#include "NearAuth.h"


gRPC_ClientItems* UNearItems::gRPC_Item = nullptr;
gRPC_ClientMM* UNearMM::gRPC_MM = nullptr;

/// items.rpc
gRPC_ClientItems::gRPC_ClientItems(const bool& ssl, FString& url) :gRPC_Stub(ssl, url)
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

        CallRPC(stub.get()->GetItems(&context, write, &read));
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

        CallRPC(stub.get()->GetBundles(&context, write, &read));
    }
    return read;
}


game::battlemon::items::WeaponBundle gRPC_ClientItems::CallRPC_EditBundle(game::battlemon::items::EditBundleRequest& request)
{
    game::battlemon::items::WeaponBundle read;
    if (UNearAuth::client != nullptr)
    {

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        CallRPC(stub.get()->EditBundle(&context, request, &read));
    }
    return read;
}

bool gRPC_ClientItems::CallRPC_AttachBundle(game::battlemon::items::AttachBundleRequest& request)
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        return CallRPC(stub.get()->AttachBundle(&context, request, &read));

    }
    return false;
}

bool gRPC_ClientItems::CallRPC_DetachBundle(game::battlemon::items::DetachBundleRequest& request)
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        return CallRPC(stub.get()->DetachBundle(&context, request, &read));
    }
    return false;
}

/// items.rpc end

/// mm.rpc
gRPC_ClientMM::gRPC_ClientMM(const bool& ssl, FString& url) :gRPC_Stub(ssl, url)
{
}

game::battlemon::mm::SearchGameResponse gRPC_ClientMM::CallRPC_SearchGame(game::battlemon::mm::SearchGameRequest& Request)
{
    game::battlemon::mm::SearchGameResponse read;
    if (UNearAuth::client != nullptr)
    {
        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        CallRPC(stub.get()->SearchGame(&context, Request, &read));
    }
    return read;
}

bool gRPC_ClientMM::CallRPC_AcceptGame(game::battlemon::mm::AcceptGameRequest& Request)
{
    if (UNearAuth::client != nullptr)
    {
        game::battlemon::common::Empty read;

        std::string meta[] = { "nearid" , "sign" };
        FString nearid = UNearAuth::client->GetAccount();
        std::string value[] = { CONV_FSTRING_TO_CHAR(nearid) , UNearAuth::client->GetSing() };
        grpc::ClientContext context;
        CreateContext(context, meta, value, 2);

        return CallRPC(stub.get()->AcceptGame(&context, Request, &read));
    }
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

        return CallRPC(stub.get()->CancelSearch(&context, write, &read));
    }
    return false;
}

/// mm.rpc end

/// InternalMM.rpc
gRPC_ClientInternalMM::gRPC_ClientInternalMM(const bool& ssl, FString& url) :gRPC_Stub(ssl, url)
{
}

bool gRPC_ClientInternalMM::CallRPC_UserLeftBattle(game::battlemon::mm::internal::InternalUserLeftBattleRequest& Request)
{
    game::battlemon::common::Empty read;
    grpc::ClientContext context;

    return CallRPC(stub.get()->UserLeftBattle(&context, Request, &read));
}

bool gRPC_ClientInternalMM::CallRPC_SaveBattleResult(game::battlemon::mm::internal::SaveBattleResultRequest& Request)
{
    game::battlemon::common::Empty read;
    grpc::ClientContext context;

    return CallRPC(stub.get()->SaveBattleResult(&context, Request, &read));
}

game::battlemon::mm::internal::RoomInfoResponse gRPC_ClientInternalMM::CallRPC_GetRoomInfo(game::battlemon::mm::internal::RoomInfoRequest& Request)
{
    game::battlemon::mm::internal::RoomInfoResponse read;

    grpc::ClientContext context;

    CallRPC(stub.get()->GetRoomInfo(&context, Request, &read));
    return read;
}

game::battlemon::mm::internal::RoomInfoResponse gRPC_ClientInternalMM::CallRPC_CreateRoomWithPlayers(game::battlemon::mm::internal::CreateRoomRequest& Request)
{
    game::battlemon::mm::internal::RoomInfoResponse read;
    grpc::ClientContext context;

    CallRPC(stub.get()->CreateRoomWithPlayers(&context, Request, &read));
    return read;
}

bool gRPC_ClientInternalMM::CallRPC_DedicatedServerIsReady(game::battlemon::mm::internal::DedicatedServerIsReadyRequest& Request)
{
    game::battlemon::common::Empty read;
    grpc::ClientContext context;

    return CallRPC(stub.get()->DedicatedServerIsReady(&context, Request, &read));
}

/// InternalMM.rpc end

void UNearItems::freegRPC_Item()
{
    if (gRPC_Item != nullptr)
        delete gRPC_Item;
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
    gRPC_Item = new gRPC_ClientItems(ssl, URL);
    out = gRPC_Item->CallRPC_GetItems();

}

void UNearItems::GetBundles(FUGetBundlesResponse& out)
{
    freegRPC_Item();
    gRPC_Item = new gRPC_ClientItems(ssl, URL);
    out = gRPC_Item->CallRPC_GetBundles();
}

void UNearItems::EditBundle(FUEditBundleRequest Request, FUWeaponBundle& out)
{
    freegRPC_Item();
    gRPC_Item = new gRPC_ClientItems(ssl, URL);

    game::battlemon::items::EditBundleRequest g_request;
    g_request << Request;
    out = gRPC_Item->CallRPC_EditBundle(g_request);
}

bool UNearItems::AttachBundle(FUAttachBundleRequest Request)
{
    freegRPC_Item();
    gRPC_Item = new gRPC_ClientItems(ssl, URL);

    game::battlemon::items::AttachBundleRequest g_request;

    g_request << Request;

    return gRPC_Item->CallRPC_AttachBundle(g_request);
}

bool UNearItems::DetachBundle(FUDetachBundleRequest Request)
{
    freegRPC_Item();
    gRPC_Item = new gRPC_ClientItems(ssl, URL);

    game::battlemon::items::DetachBundleRequest g_request;

    g_request << Request;

    return gRPC_Item->CallRPC_DetachBundle(g_request);
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
        delete gRPC_MM;
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
    gRPC_MM = new gRPC_ClientMM(ssl, URL);
    game::battlemon::mm::SearchGameRequest g_request;
    g_request << Request;
    out = gRPC_MM->CallRPC_SearchGame(g_request);
}

bool UNearMM::AcceptGame(FUAcceptGameRequest Request)
{
    freegRPC_MM();
    gRPC_MM = new gRPC_ClientMM(ssl, URL);
    game::battlemon::mm::AcceptGameRequest g_request;
    g_request << Request;

    return gRPC_MM->CallRPC_AcceptGame(g_request);
}

bool UNearMM::CancelSearch()
{
    freegRPC_MM();
    gRPC_MM = new gRPC_ClientMM(ssl, URL);

    return gRPC_MM->CallRPC_CancelSearch();
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
        delete gRPC_InternalMM;
    gRPC_InternalMM = nullptr;
}

UNearInternalMM::UNearInternalMM()
{
}

UNearInternalMM::~UNearInternalMM()
{
    freegRPC_InternalMM();
}

bool UNearInternalMM::UserLeftBattle(FUInternalUserLeftBattleRequest Request)
{
    freegRPC_InternalMM();
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL);
    game::battlemon::mm::internal::InternalUserLeftBattleRequest g_request;
    g_request << Request;

    return gRPC_InternalMM->CallRPC_UserLeftBattle(g_request);
}

bool UNearInternalMM::SaveBattleResult(FUSaveBattleResultRequest Request)
{
    freegRPC_InternalMM();
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL);

    game::battlemon::mm::internal::SaveBattleResultRequest g_request;

    g_request << Request;

    return gRPC_InternalMM->CallRPC_SaveBattleResult(g_request);
}

void UNearInternalMM::GetRoomInfo(FURoomInfoRequest Request, FURoomInfoResponse& out)
{
        freegRPC_InternalMM();
        gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL);

        game::battlemon::mm::internal::RoomInfoRequest g_request;
        g_request << Request;
        out = gRPC_InternalMM->CallRPC_GetRoomInfo(g_request);
}

void UNearInternalMM::CreateRoomWithPlayers(FUCreateRoomRequest Request, FURoomInfoResponse& out)
{
    freegRPC_InternalMM();
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL);

    game::battlemon::mm::internal::CreateRoomRequest g_request;
    g_request << Request;
    
    out = gRPC_InternalMM->CallRPC_CreateRoomWithPlayers(g_request);
}

bool UNearInternalMM::DedicatedServerIsReady(FUDedicatedServerIsReadyRequest Request)
{
    freegRPC_InternalMM();
    gRPC_InternalMM = new gRPC_ClientInternalMM(ssl, URL);
    game::battlemon::mm::internal::DedicatedServerIsReadyRequest g_request;
    g_request << Request;
    return gRPC_InternalMM->CallRPC_DedicatedServerIsReady(g_request);
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