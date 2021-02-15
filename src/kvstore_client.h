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
  explicit KVStoreClient (std::shared_ptr<grpc::Channel> channel)
                         : stub_(kvstore::KeyValueStore::NewStub(channel)) {}
  
  bool Put (const std::string &key, const std::string &value) {
    grpc::ClientContext context;
    kvstore::PutRequest request;
    kvstore::PutReply reply;

    request.set_key(key);
    request.set_value(value);
    // Put function finished by server.
    grpc::Status status = stub_->Put(&context, request, &reply);

    if (!status.ok()) {
      std::cout << "status error: " << status.error_message() << std::endl;
      return false;
    }
    return true;
  }

  bool Get (const std::vector<std::string> &keyarr, std::vector<std::string> &valarr) {
    grpc::ClientContext context;
    auto stream(stub_->Get(&context));

    // Create a thread to write stream of requests.
    std::thread writer([&stream, &keyarr]() {
      for (const std::string &key : keyarr) {
        kvstore::GetRequest request;
        request.set_key(key);
        stream->Write(request);
      }
      stream->WritesDone();
    });

    // Receive a stream of replies.
    kvstore::GetReply reply;
    while (stream->Read(&reply)) {
      valarr.push_back(reply.value());
    }
    // Waiting for writer thread.
    writer.join();
    grpc::Status status = stream->Finish();

    if (!status.ok()) {
      std::cout << "status error: " << status.error_message() << std::endl;
      return false;
    }
    return true;
  }

  bool Remove(const std::string &key) {
    grpc::ClientContext context;
    kvstore::RemoveRequest request;
    kvstore::RemoveReply reply;

    request.set_key(key);
    grpc::Status status = stub_->Remove(&context, request, &reply);

    if (!status.ok()) {
      std::cout << "status error: " << status.error_message() << std::endl;
      return false;
    }
    return true;
  }

 private:
  std::unique_ptr<kvstore::KeyValueStore::Stub> stub_;
};

#endif