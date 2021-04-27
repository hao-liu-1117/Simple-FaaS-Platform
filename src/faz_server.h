#ifndef FAZ_SERVER_H_
#define FAZ_SERVER_H_

#include <functional>

#include <grpcpp/grpcpp.h>
#include <vector>

#include "caw.h"
#include "faz.grpc.pb.h"
#include "kvstore_client.h"
#include "util.cc"

// Faz Server hook/unhook functions and execute 
// functions through FazServer::Event().
class FazServer final : public faz::FazService::Service {
 public:
  // Initialize Faz server with kvstore client constructor.
  explicit FazServer(std::shared_ptr<grpc::Channel> channel);

  grpc::Status Hook(grpc::ServerContext* context, const faz::HookRequest* request,
                    faz::HookReply* response) override;
  
  grpc::Status Unhook(grpc::ServerContext* context, const faz::UnhookRequest* request,
                      faz::UnhookReply* response) override;

  grpc::Status Event(grpc::ServerContext* context, const faz::EventRequest* request,
                     faz::EventReply* response) override;

  grpc::Status Subscribe(grpc::ServerContext* context, const faz::EventRequest* request,
                         grpc::ServerWriter<faz::EventReply>* writer) override;

  grpc::Status IsRegistered(grpc::ServerContext* context, const faz::IsRegisteredRequest* request,
                            faz::IsRegisteredReply* response) override;
 private:
  // Broadcast new caw to all subscriber
  void streams_broadcast(const std::vector<std::string> &hashtags, const faz::EventReply* response);
  // register subscriber to hashtag
  void streams_register(const std::string &hashtag, grpc::ServerWriter<faz::EventReply>* writer);
  std::string GetFunctionStr(const int event_id);
  // Build a function map for FazServer::Event.
  // FazServer::Event can execute function based on which string::event_function passed in.
  std::unordered_map<std::string, std::function<faz::EventReply(
                                                const faz::EventRequest*,
                                                KVStoreClient&)>> funcmap_;
  // Build an event map for FazServer::Event.
  // FazServer::Event can reach out which function is going to execute by eventmap_.
  std::unordered_map<int, std::string> eventmap_;
  // Check if function is bind with specific event type.
  std::unordered_map<std::string, int> typemap_;
  // Map from hashtag to serverwriter of each stream
  std::unordered_map<std::string, std::vector<grpc::ServerWriter<faz::EventReply>*>> streammap_;
  // Lock for streammap_ to prevent race condition
  mutable std::mutex map_mutex_;
  KVStoreClient kvclient_;
};

#endif
