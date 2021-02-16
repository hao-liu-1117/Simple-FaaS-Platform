#ifndef KVSTORE_CLIENT_H_
#define KVSTORE_CLIENT_H_

#include <string>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpcpp/client_context.h>
#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>


#include "keyvaluestoreclass.h"
#include "keyvaluestore.grpc.pb.h"

// Key-value store client.
class KVStoreClient {
 public:
  explicit KVStoreClient(std::shared_ptr<grpc::Channel> channel)
                         : stub_(kvstore::KeyValueStore::NewStub(channel)) {}
  
  bool Put(const std::string &key, const std::string &value);

  bool Get(const std::vector<std::string> &keyarr, std::vector<std::string> &valarr);

  bool Remove(const std::string &key);

 private:
  // Client sends request usign stub and waits for response.
  std::unique_ptr<kvstore::KeyValueStore::Stub> stub_;
};

#endif