#ifndef KVSTORE_SERVER_H_
#define KVSTORE_SERVER_H_

#include <string>

#include <grpcpp/grpcpp.h>

#include "keyvaluestoreclass.h"
#include "keyvaluestore.grpc.pb.h"

class KVStoreService final : public kvstore::KeyValueStore::Service {
 public:
  explicit KVStoreService () {}
  grpc::Status Put(grpc::ServerContext* context, const kvstore::PutRequest* request,
                   kvstore::PutReply* response) override {
    storeinstance_.Put(request->key(), request->value());
    return grpc::Status::OK;
  }

  grpc::Status Get(grpc::ServerContext* context, grpc::ServerReaderWriter< kvstore::GetReply, 
                   kvstore::GetRequest>* stream) override {
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

  grpc::Status Remove(grpc::ServerContext* context, const kvstore::RemoveRequest* request, 
                      kvstore::RemoveReply* response) override {
    storeinstance_.Remove(request->key());
    return grpc::Status::OK;
  }
 private:
  KeyValueStore storeinstance_;
};

#endif