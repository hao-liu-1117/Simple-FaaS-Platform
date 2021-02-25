#include <glog/logging.h>

#include "kvstore_client.h"

bool KVStoreClient::Put (const std::string &key, const std::string &value) {
  grpc::ClientContext context;
  kvstore::PutRequest request;
  kvstore::PutReply reply;

  request.set_key(key);
  request.set_value(value);
  // Put function finished by server.
  grpc::Status status = stub_->Put(&context, request, &reply);

  if (!status.ok()) {
    LOG(INFO) << "status error: " << status.error_message();
    return false;
  }
  return true;
}

bool KVStoreClient::Get(const std::vector<std::string> &keyarr, 
                        std::vector<std::string> &valarr) {
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
    LOG(INFO) << "status error: " << status.error_message();
    return false;
  }
  return true;
}

bool KVStoreClient::Remove(const std::string &key){
  grpc::ClientContext context;
  kvstore::RemoveRequest request;
  kvstore::RemoveReply reply;

  request.set_key(key);
  grpc::Status status = stub_->Remove(&context, request, &reply);

  if (!status.ok()) {
    LOG(INFO) << "status error: " << status.error_message();
    return false;
  }
  return true;
}