#include <glog/logging.h>

#include "faz_client.h"
#include "caw.h"

bool FazClient::Hook(const int event_type, const std::string &funcstr) {
  grpc::ClientContext context;
  faz::HookRequest request;
  faz::HookReply reply;
  request.set_event_type(event_type);
  request.set_event_function(funcstr);
  grpc::Status status = stub_->Hook(&context, request, &reply);
  if (!status.ok()) {
    LOG(INFO) << "status error: " << status.error_message();
    return false;
  }
  return true;
}

bool FazClient::Unhook(const int event_type) {
  grpc::ClientContext context;
  faz::UnhookRequest request;
  faz::UnhookReply reply;
  request.set_event_type(event_type);
  grpc::Status status = stub_->Unhook(&context, request, &reply);
  if (!status.ok()) {
    LOG(INFO) << "status error: " << status.error_message();
    return false;
  }
  return true;
}

faz::EventReply FazClient::Event(const faz::EventRequest &request) {
  grpc::ClientContext context;
  faz::EventReply reply;
  grpc::Status status = stub_->Event(&context, request, &reply);
  return reply;
}

grpc::Status FazClient::Subscribe(const faz::EventRequest &request) {
  grpc::ClientContext context;
  faz::EventReply reply;
  std::unique_ptr<grpc::ClientReader<faz::EventReply>> reader(
                  stub_->Subscribe(&context, request));
  // Keep reading reply for up-to-date caw
  while (reader->Read(&reply)) {
    caw::Caw cur_caw;
    reply.payload().UnpackTo(&cur_caw);
    std::cout << "[" << cur_caw.id() << "] " << 
          cur_caw.username() << " : " << 
          cur_caw.text() <<
          std::endl;
  }
  return reader->Finish();
}

int FazClient::IsRegistered(const std::string &funcstr) {
  grpc::ClientContext context;
  faz::IsRegisteredRequest request;
  request.set_event_function(funcstr);
  faz::IsRegisteredReply reply;
  grpc::Status status = stub_->IsRegistered(&context, request, &reply);
  return reply.event_type();
}
