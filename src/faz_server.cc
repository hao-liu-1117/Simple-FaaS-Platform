#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "faz_server.h"
#include "prefix.h"

FazServer::FazServer(std::shared_ptr<grpc::Channel> channel) : kvclient_(channel) {
  // Create function map.
  funcmap_["registeruser"] = cawfunc::RegisterUserHelper;
  funcmap_["caw"] = cawfunc::CawHelper;
  funcmap_["follow"] = cawfunc::FollowHelper;
  funcmap_["read"] = cawfunc::ReadHelper;
  funcmap_["profile"] = cawfunc::ProfileHelper;
}

grpc::Status FazServer::Hook(grpc::ServerContext* context, const faz::HookRequest* request,
                             faz::HookReply* response) {
  int event_type = request->event_type();
  std::string event_func = request->event_function();
  eventmap_[event_type] = event_func;
  return grpc::Status::OK;
}

grpc::Status FazServer::Unhook(grpc::ServerContext* context, const faz::UnhookRequest* request,
                               faz::UnhookReply* response) {
  int event_type = request->event_type();
  eventmap_.erase(event_type);
  return grpc::Status::OK;
}

grpc::Status FazServer::Event(grpc::ServerContext* context, const faz::EventRequest* request,
                              faz::EventReply* response) {
  int event_type = request->event_type();
  // match event_type to function
  std::string funcstr = GetFunctionStr(event_type);
  if (funcstr.empty()) {
    // no such event_type
    return grpc::Status::CANCELLED;
  }
  // execute event
  faz::EventReply event_rep = funcmap_[funcstr](request, kvclient_);
  response = new faz::EventReply(event_rep);
  return grpc::Status::OK;
}

std::string FazServer::GetFunctionStr(const int event_type) {
  std::string res = "";
  // Check if event_type hooked to a specific function.
  if (eventmap_.count(event_type)) {
    res = eventmap_[event_type];
  }
  return res;
}

void RunServer() {
  std::string server_address = "0.0.0.0:50000";
  FazServer fazserver(grpc::CreateChannel("0.0.0.0:50001",
                      grpc::InsecureChannelCredentials()));
  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&fazserver);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  server->Wait();
}

int main() {
  RunServer();
  return 0;
}