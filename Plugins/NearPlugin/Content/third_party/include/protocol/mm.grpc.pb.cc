// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: mm.proto

#include "mm.pb.h"
#include "mm.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace game {
namespace battlemon {
namespace mm {

static const char* MMService_method_names[] = {
  "/game.battlemon.mm.MMService/SearchGame",
  "/game.battlemon.mm.MMService/AcceptGame",
  "/game.battlemon.mm.MMService/CancelSearch",
};

std::unique_ptr< MMService::Stub> MMService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MMService::Stub> stub(new MMService::Stub(channel, options));
  return stub;
}

MMService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_SearchGame_(MMService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_AcceptGame_(MMService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CancelSearch_(MMService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MMService::Stub::SearchGame(::grpc::ClientContext* context, const ::game::battlemon::mm::SearchGameRequest& request, ::game::battlemon::mm::SearchGameResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::game::battlemon::mm::SearchGameRequest, ::game::battlemon::mm::SearchGameResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_SearchGame_, context, request, response);
}

void MMService::Stub::async::SearchGame(::grpc::ClientContext* context, const ::game::battlemon::mm::SearchGameRequest* request, ::game::battlemon::mm::SearchGameResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::game::battlemon::mm::SearchGameRequest, ::game::battlemon::mm::SearchGameResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SearchGame_, context, request, response, std::move(f));
}

void MMService::Stub::async::SearchGame(::grpc::ClientContext* context, const ::game::battlemon::mm::SearchGameRequest* request, ::game::battlemon::mm::SearchGameResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_SearchGame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::game::battlemon::mm::SearchGameResponse>* MMService::Stub::PrepareAsyncSearchGameRaw(::grpc::ClientContext* context, const ::game::battlemon::mm::SearchGameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::game::battlemon::mm::SearchGameResponse, ::game::battlemon::mm::SearchGameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_SearchGame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::game::battlemon::mm::SearchGameResponse>* MMService::Stub::AsyncSearchGameRaw(::grpc::ClientContext* context, const ::game::battlemon::mm::SearchGameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncSearchGameRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MMService::Stub::AcceptGame(::grpc::ClientContext* context, const ::game::battlemon::mm::AcceptGameRequest& request, ::game::battlemon::common::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::game::battlemon::mm::AcceptGameRequest, ::game::battlemon::common::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_AcceptGame_, context, request, response);
}

void MMService::Stub::async::AcceptGame(::grpc::ClientContext* context, const ::game::battlemon::mm::AcceptGameRequest* request, ::game::battlemon::common::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::game::battlemon::mm::AcceptGameRequest, ::game::battlemon::common::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AcceptGame_, context, request, response, std::move(f));
}

void MMService::Stub::async::AcceptGame(::grpc::ClientContext* context, const ::game::battlemon::mm::AcceptGameRequest* request, ::game::battlemon::common::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_AcceptGame_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::game::battlemon::common::Empty>* MMService::Stub::PrepareAsyncAcceptGameRaw(::grpc::ClientContext* context, const ::game::battlemon::mm::AcceptGameRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::game::battlemon::common::Empty, ::game::battlemon::mm::AcceptGameRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_AcceptGame_, context, request);
}

::grpc::ClientAsyncResponseReader< ::game::battlemon::common::Empty>* MMService::Stub::AsyncAcceptGameRaw(::grpc::ClientContext* context, const ::game::battlemon::mm::AcceptGameRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncAcceptGameRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MMService::Stub::CancelSearch(::grpc::ClientContext* context, const ::game::battlemon::mm::CancelSearchRequest& request, ::game::battlemon::common::Empty* response) {
  return ::grpc::internal::BlockingUnaryCall< ::game::battlemon::mm::CancelSearchRequest, ::game::battlemon::common::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CancelSearch_, context, request, response);
}

void MMService::Stub::async::CancelSearch(::grpc::ClientContext* context, const ::game::battlemon::mm::CancelSearchRequest* request, ::game::battlemon::common::Empty* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::game::battlemon::mm::CancelSearchRequest, ::game::battlemon::common::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CancelSearch_, context, request, response, std::move(f));
}

void MMService::Stub::async::CancelSearch(::grpc::ClientContext* context, const ::game::battlemon::mm::CancelSearchRequest* request, ::game::battlemon::common::Empty* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CancelSearch_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::game::battlemon::common::Empty>* MMService::Stub::PrepareAsyncCancelSearchRaw(::grpc::ClientContext* context, const ::game::battlemon::mm::CancelSearchRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::game::battlemon::common::Empty, ::game::battlemon::mm::CancelSearchRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CancelSearch_, context, request);
}

::grpc::ClientAsyncResponseReader< ::game::battlemon::common::Empty>* MMService::Stub::AsyncCancelSearchRaw(::grpc::ClientContext* context, const ::game::battlemon::mm::CancelSearchRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCancelSearchRaw(context, request, cq);
  result->StartCall();
  return result;
}

MMService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MMService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MMService::Service, ::game::battlemon::mm::SearchGameRequest, ::game::battlemon::mm::SearchGameResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MMService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::game::battlemon::mm::SearchGameRequest* req,
             ::game::battlemon::mm::SearchGameResponse* resp) {
               return service->SearchGame(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MMService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MMService::Service, ::game::battlemon::mm::AcceptGameRequest, ::game::battlemon::common::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MMService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::game::battlemon::mm::AcceptGameRequest* req,
             ::game::battlemon::common::Empty* resp) {
               return service->AcceptGame(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MMService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MMService::Service, ::game::battlemon::mm::CancelSearchRequest, ::game::battlemon::common::Empty, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MMService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::game::battlemon::mm::CancelSearchRequest* req,
             ::game::battlemon::common::Empty* resp) {
               return service->CancelSearch(ctx, req, resp);
             }, this)));
}

MMService::Service::~Service() {
}

::grpc::Status MMService::Service::SearchGame(::grpc::ServerContext* context, const ::game::battlemon::mm::SearchGameRequest* request, ::game::battlemon::mm::SearchGameResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MMService::Service::AcceptGame(::grpc::ServerContext* context, const ::game::battlemon::mm::AcceptGameRequest* request, ::game::battlemon::common::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MMService::Service::CancelSearch(::grpc::ServerContext* context, const ::game::battlemon::mm::CancelSearchRequest* request, ::game::battlemon::common::Empty* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace game
}  // namespace battlemon
}  // namespace mm

