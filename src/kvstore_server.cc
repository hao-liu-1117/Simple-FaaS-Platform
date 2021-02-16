#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

#include "kvstore_server.h"

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

void RunServer() {
  std::string server_address = "0.0.0.0:50001";
  KVStoreService service;
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();
  return 0;
}