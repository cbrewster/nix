// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: rpc_pathinfo.proto

#include "rpc_pathinfo.pb.h"
#include "rpc_pathinfo.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
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
namespace tvix {
namespace store {
namespace v1 {

static const char* PathInfoService_method_names[] = {
  "/tvix.store.v1.PathInfoService/Get",
  "/tvix.store.v1.PathInfoService/Put",
  "/tvix.store.v1.PathInfoService/CalculateNAR",
  "/tvix.store.v1.PathInfoService/List",
};

std::unique_ptr< PathInfoService::Stub> PathInfoService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< PathInfoService::Stub> stub(new PathInfoService::Stub(channel, options));
  return stub;
}

PathInfoService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Get_(PathInfoService_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Put_(PathInfoService_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_CalculateNAR_(PathInfoService_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_List_(PathInfoService_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  {}

::grpc::Status PathInfoService::Stub::Get(::grpc::ClientContext* context, const ::tvix::store::v1::GetPathInfoRequest& request, ::tvix::store::v1::PathInfo* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tvix::store::v1::GetPathInfoRequest, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Get_, context, request, response);
}

void PathInfoService::Stub::async::Get(::grpc::ClientContext* context, const ::tvix::store::v1::GetPathInfoRequest* request, ::tvix::store::v1::PathInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tvix::store::v1::GetPathInfoRequest, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Get_, context, request, response, std::move(f));
}

void PathInfoService::Stub::async::Get(::grpc::ClientContext* context, const ::tvix::store::v1::GetPathInfoRequest* request, ::tvix::store::v1::PathInfo* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Get_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::PrepareAsyncGetRaw(::grpc::ClientContext* context, const ::tvix::store::v1::GetPathInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tvix::store::v1::PathInfo, ::tvix::store::v1::GetPathInfoRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Get_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::AsyncGetRaw(::grpc::ClientContext* context, const ::tvix::store::v1::GetPathInfoRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status PathInfoService::Stub::Put(::grpc::ClientContext* context, const ::tvix::store::v1::PathInfo& request, ::tvix::store::v1::PathInfo* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tvix::store::v1::PathInfo, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_Put_, context, request, response);
}

void PathInfoService::Stub::async::Put(::grpc::ClientContext* context, const ::tvix::store::v1::PathInfo* request, ::tvix::store::v1::PathInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tvix::store::v1::PathInfo, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Put_, context, request, response, std::move(f));
}

void PathInfoService::Stub::async::Put(::grpc::ClientContext* context, const ::tvix::store::v1::PathInfo* request, ::tvix::store::v1::PathInfo* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_Put_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::PrepareAsyncPutRaw(::grpc::ClientContext* context, const ::tvix::store::v1::PathInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tvix::store::v1::PathInfo, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_Put_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::AsyncPutRaw(::grpc::ClientContext* context, const ::tvix::store::v1::PathInfo& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncPutRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status PathInfoService::Stub::CalculateNAR(::grpc::ClientContext* context, const ::tvix::store::v1::Node& request, ::tvix::store::v1::CalculateNARResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::tvix::store::v1::Node, ::tvix::store::v1::CalculateNARResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_CalculateNAR_, context, request, response);
}

void PathInfoService::Stub::async::CalculateNAR(::grpc::ClientContext* context, const ::tvix::store::v1::Node* request, ::tvix::store::v1::CalculateNARResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::tvix::store::v1::Node, ::tvix::store::v1::CalculateNARResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CalculateNAR_, context, request, response, std::move(f));
}

void PathInfoService::Stub::async::CalculateNAR(::grpc::ClientContext* context, const ::tvix::store::v1::Node* request, ::tvix::store::v1::CalculateNARResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_CalculateNAR_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::tvix::store::v1::CalculateNARResponse>* PathInfoService::Stub::PrepareAsyncCalculateNARRaw(::grpc::ClientContext* context, const ::tvix::store::v1::Node& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::tvix::store::v1::CalculateNARResponse, ::tvix::store::v1::Node, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_CalculateNAR_, context, request);
}

::grpc::ClientAsyncResponseReader< ::tvix::store::v1::CalculateNARResponse>* PathInfoService::Stub::AsyncCalculateNARRaw(::grpc::ClientContext* context, const ::tvix::store::v1::Node& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncCalculateNARRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::ClientReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::ListRaw(::grpc::ClientContext* context, const ::tvix::store::v1::ListPathInfoRequest& request) {
  return ::grpc::internal::ClientReaderFactory< ::tvix::store::v1::PathInfo>::Create(channel_.get(), rpcmethod_List_, context, request);
}

void PathInfoService::Stub::async::List(::grpc::ClientContext* context, const ::tvix::store::v1::ListPathInfoRequest* request, ::grpc::ClientReadReactor< ::tvix::store::v1::PathInfo>* reactor) {
  ::grpc::internal::ClientCallbackReaderFactory< ::tvix::store::v1::PathInfo>::Create(stub_->channel_.get(), stub_->rpcmethod_List_, context, request, reactor);
}

::grpc::ClientAsyncReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::AsyncListRaw(::grpc::ClientContext* context, const ::tvix::store::v1::ListPathInfoRequest& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::tvix::store::v1::PathInfo>::Create(channel_.get(), cq, rpcmethod_List_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::tvix::store::v1::PathInfo>* PathInfoService::Stub::PrepareAsyncListRaw(::grpc::ClientContext* context, const ::tvix::store::v1::ListPathInfoRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::tvix::store::v1::PathInfo>::Create(channel_.get(), cq, rpcmethod_List_, context, request, false, nullptr);
}

PathInfoService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      PathInfoService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< PathInfoService::Service, ::tvix::store::v1::GetPathInfoRequest, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](PathInfoService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tvix::store::v1::GetPathInfoRequest* req,
             ::tvix::store::v1::PathInfo* resp) {
               return service->Get(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      PathInfoService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< PathInfoService::Service, ::tvix::store::v1::PathInfo, ::tvix::store::v1::PathInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](PathInfoService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tvix::store::v1::PathInfo* req,
             ::tvix::store::v1::PathInfo* resp) {
               return service->Put(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      PathInfoService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< PathInfoService::Service, ::tvix::store::v1::Node, ::tvix::store::v1::CalculateNARResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](PathInfoService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tvix::store::v1::Node* req,
             ::tvix::store::v1::CalculateNARResponse* resp) {
               return service->CalculateNAR(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      PathInfoService_method_names[3],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< PathInfoService::Service, ::tvix::store::v1::ListPathInfoRequest, ::tvix::store::v1::PathInfo>(
          [](PathInfoService::Service* service,
             ::grpc::ServerContext* ctx,
             const ::tvix::store::v1::ListPathInfoRequest* req,
             ::grpc::ServerWriter<::tvix::store::v1::PathInfo>* writer) {
               return service->List(ctx, req, writer);
             }, this)));
}

PathInfoService::Service::~Service() {
}

::grpc::Status PathInfoService::Service::Get(::grpc::ServerContext* context, const ::tvix::store::v1::GetPathInfoRequest* request, ::tvix::store::v1::PathInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status PathInfoService::Service::Put(::grpc::ServerContext* context, const ::tvix::store::v1::PathInfo* request, ::tvix::store::v1::PathInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status PathInfoService::Service::CalculateNAR(::grpc::ServerContext* context, const ::tvix::store::v1::Node* request, ::tvix::store::v1::CalculateNARResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status PathInfoService::Service::List(::grpc::ServerContext* context, const ::tvix::store::v1::ListPathInfoRequest* request, ::grpc::ServerWriter< ::tvix::store::v1::PathInfo>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace tvix
}  // namespace store
}  // namespace v1
