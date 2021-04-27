#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "caw.h"
#include "faz_server.h"
#include "prefix.h"

FazServer::FazServer(std::shared_ptr<grpc::Channel> channel) : kvclient_(channel), map_mutex_() {
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
  if (eventmap_.count(event_type) || typemap_.count(event_func)) {
    // Event already exists.
    return grpc::Status::CANCELLED;
  }
  eventmap_[event_type] = event_func;
  typemap_[event_func] = event_type;

  return grpc::Status::OK;
}

grpc::Status FazServer::Unhook(grpc::ServerContext* context, const faz::UnhookRequest* request,
                               faz::UnhookReply* response) {
  int event_type = request->event_type();
  std::string event_func = eventmap_[event_type];
  if (!eventmap_.count(event_type) || !typemap_.count(event_func)) {
    // event_type does not exist.
    return grpc::Status::CANCELLED;
  }
  eventmap_.erase(event_type);
  typemap_.erase(event_func);
  
  return grpc::Status::OK;
}

// TODO: Add test
std::vector<std::string> FazServer::ResolveHashtags(const std::string &text) {
  std::vector<std::string> hashtags;
  std::string hashtag = "";
  bool is_hashtag = false;
  for (auto const ch : text) {
    if (ch == ' ') {
      if (hashtag.length() != 0) {
        hashtags.push_back(hashtag);
        hashtag = "";
        is_hashtag = false;
      }
    } else if (ch == '#') {
      is_hashtag = true;
    } else if (is_hashtag) {
      hashtag += ch;
    }
  }

  if (hashtag.length() != 0) {
    hashtags.push_back(hashtag);
  }

  return hashtags;
}

void FazServer::streams_broadcast(const std::vector<std::string> &hashtags,
                                        const faz::EventReply* response) {
    const std::lock_guard<std::mutex> lock(map_mutex_);
    for (auto const hashtag : hashtags) {
      if (streammap_.find(hashtag) != streammap_.end()) {
        auto streams = streammap_[hashtag];
        for (auto stream = streams.begin(); stream != streams.end(); stream++) {
          (*stream)->Write(*(response));
        }
      }
    }
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
  
  google::protobuf::Any *any = new google::protobuf::Any(event_rep.payload());
  response->set_allocated_payload(any);

  // Check whether New caw contain any hashtag
  // If does, write to all corresponding serverwriter
  if ( funcstr == "caw" ) {
    caw::Caw cur_caw; 
    response->payload().UnpackTo(&cur_caw);
    std::string caw_text = cur_caw.text();
    std::vector<std::string> hashtags = FazServer::ResolveHashtags(caw_text);
    FazServer::streams_broadcast(hashtags, response);
  }
  return grpc::Status::OK;
}

void FazServer::streams_register(const std::string &hashtag, grpc::ServerWriter<faz::EventReply>* writer) {
  const std::lock_guard<std::mutex> lock(map_mutex_);
  if (streammap_.find(hashtag) == streammap_.end()) {
    streammap_[hashtag] = {writer};
  } else {
    streammap_[hashtag].push_back(writer);
  }
}

grpc::Status FazServer::Subscribe(grpc::ServerContext* context, const faz::EventRequest* request,
                                  grpc::ServerWriter<faz::EventReply>* writer){
  
  int event_type = request->event_type();
  // match event_type to function
  std::string funcstr = GetFunctionStr(event_type);
  if (funcstr.empty()) {
    // no such event_type
    return grpc::Status::CANCELLED;
  }
  
  // expose hashtag from SubscribeRequest
  caw::SubscribeRequest subscribe_req;
  request->payload().UnpackTo(&subscribe_req);
  std::string hashtag = subscribe_req.hashtag();
  FazServer::streams_register(hashtag, writer);
  while(true) {} // keep streaming 
  return grpc::Status::OK;
}

grpc::Status FazServer::IsRegistered(grpc::ServerContext* context, const faz::IsRegisteredRequest* request,
                                     faz::IsRegisteredReply* response) {
  std::string funcstr = request->event_function();
  response->set_event_type(-1); // event_type == -1 indicates event does not exist.
  if (typemap_.count(funcstr)) {
    response->set_event_type(typemap_[funcstr]);
  }
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
