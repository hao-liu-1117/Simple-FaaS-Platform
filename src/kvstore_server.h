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
                   kvstore::PutReply* response) override;

  grpc::Status Get(grpc::ServerContext* context, grpc::ServerReaderWriter< kvstore::GetReply, 
                   kvstore::GetRequest>* stream) override;

  grpc::Status Remove(grpc::ServerContext* context, const kvstore::RemoveRequest* request, 
                      kvstore::RemoveReply* response) override;
 private:
  KeyValueStore storeinstance_;
};

#endif