#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "kvstore_server.h"

DEFINE_string(store, "", "filename to store data.");

KVStoreService::KVStoreService() {
  // Init caw count in kvstore backend
  storeinstance_.Put(prefix::kCawCount, prefix::kCawInitId);
}

grpc::Status KVStoreService::Put(grpc::ServerContext* context, 
                                 const kvstore::PutRequest* request, 
                                 kvstore::PutReply* response) {
  storeinstance_.Put(request->key(), request->value());
  return grpc::Status::OK;
}

grpc::Status KVStoreService::Get(grpc::ServerContext* context, 
                                 grpc::ServerReaderWriter< kvstore::GetReply, 
                                 kvstore::GetRequest>* stream) {
  kvstore::GetRequest request;

  while (stream->Read(&request)) {
    // For each request with a key, it may return different number of values.
    std::unordered_set<std::string> res_set = storeinstance_.Get(request.key());
    for (auto &str : res_set) {
      kvstore::GetReply reply;
      reply.set_value(str);
      stream->Write(reply);
    }
  }
  return grpc::Status::OK;
}

grpc::Status KVStoreService::Remove(grpc::ServerContext* context, 
                                    const kvstore::RemoveRequest* request, 
                                    kvstore::RemoveReply* response) {
  storeinstance_.Remove(request->key());
  return grpc::Status::OK;
}

static KVStoreService service;

void storeHandler(int signum) {
  KeyValueStore::Store(service.storeinstance_, FLAGS_store);
  exit(0);
}

void RunServer() {
  std::string server_address = "0.0.0.0:50001";
  grpc::ServerBuilder builder;
  if (!FLAGS_store.empty()) {
    // Register store handler. If SIGINT received, store data.
    signal(SIGINT, storeHandler);
    KeyValueStore::Load(service.storeinstance_, FLAGS_store);
  }
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  RunServer();
  return 0;
}