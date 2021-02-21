#ifndef FAZ_SERVER_H_
#define FAZ_SERVER_H_

#include <functional>

#include <grpcpp/grpcpp.h>

#include "caw.h"
#include "faz.grpc.pb.h"
#include "kvstore_client.h"

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

 private:
  std::string GetFunctionStr(const int event_id);
  // Build a function map for FazServer::Event.
  // FazServer::Event can execute function based on which string::event_function passed in.
  std::unordered_map<std::string, std::function<faz::EventReply*(
                                                const faz::EventRequest*,
                                                KVStoreClient&)>> funcmap_;
  KVStoreClient kvclient_;
};

#endif