#ifndef CMD_CLIENT_H_
#define CMD_CLIENT_H_

#include <string>
#include <unordered_map>
#include <unistd.h>
#include <chrono>

#include <gflags/gflags.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

#include "caw.grpc.pb.h"
#include "faz.grpc.pb.h"
#include "faz_client.h"

class CMDClient {
 public:
  // explicit CMDClient(std::shared_ptr<grpc::Channel> channel) 
  //                       : fazclient_(channel) {}
  explicit CMDClient(std::shared_ptr<grpc::Channel> channel) 
                        : fazclient_(channel){}

  void Hook(const int event_type, const std::string &funcstr);

  void Unhook(const int event_type);

  void RegisterUser(const std::string &username);

  void Caw(const std::string &username, const std::string &text, std::string reply_id);

  void Follow(const std::string &username, const std::string &to_follow);

  void Read(const std::string &caw_id);

  void Profile(const std::string &username);

  void Subscribe(const std::string &username, const std::string &hastag);

  int IsRegistered(const std::string &funcstr);

 private:
  FazClient fazclient_;
};

void PrintCaw(const caw::Caw &c);

void PrintProfile(const std::string &username, const caw::ProfileReply &rep);

#endif
