#include <iostream>
#include <string>

#include "cmd_client.h"

// Define cmd client flags
DEFINE_string(registeruser, "", "Registers the given username.");
DEFINE_string(user, "", "Logs in as the given username.");
DEFINE_string(caw, "", "Creates a new caw with the given text.");
DEFINE_string(reply, "", "Indicates that the new caw is a reply to the given id.");
DEFINE_string(follow, "", "Starts following the given username.");
DEFINE_string(read, "", "Reads the caw thread starting at the given id.");
DEFINE_bool(profile, false, "Gets the user’s profile of following and followers.");
DEFINE_int32(hook, -1, "Specify event type id that will be hooked with event function.");
DEFINE_int32(unhook, -1, "Specify event type id that will be unhooked.");
DEFINE_string(event_function, "", "Specify event function.");
DEFINE_string(subscribe, "", "Specify a hashtag user want to subscribe");

void RunCommand() {
  CMDClient client(grpc::CreateChannel("0.0.0.0:50000",
                   grpc::InsecureChannelCredentials()));
  int cmd_count = 0;
  // Each command should only execute one command.
  if (!FLAGS_registeruser.empty()) cmd_count++;
  if (!FLAGS_caw.empty()) cmd_count++;
  if (!FLAGS_follow.empty()) cmd_count++;
  if (!FLAGS_read.empty()) cmd_count++;
  if (!FLAGS_subscribe.empty()) cmd_count++;
  if (FLAGS_profile) cmd_count++;
  if (FLAGS_hook != -1) cmd_count++;
  if (FLAGS_unhook != -1) cmd_count++;
  
  if (cmd_count > 1) {
    std::cout << "Command should only execute one command." << std::endl;
    return;
  }
  if (cmd_count == 0) {
    std::cout << "No executable command found." << std::endl;
  }
  // Execute command.
  if (!FLAGS_registeruser.empty()) {
    // Check if function is registered.
    if (client.IsRegistered("registeruser") == -1) {
      std::cout << "registeruser function is not registered." << std::endl;
      return;
    }
    client.RegisterUser(FLAGS_registeruser);
  }
  else if (!FLAGS_caw.empty()) {
    // Check if function is registered.
    if (client.IsRegistered("caw") == -1) {
      std::cout << "caw function is not registered." << std::endl;
      return;
    }
    client.Caw(FLAGS_user, FLAGS_caw, FLAGS_reply);
  }
  else if (!FLAGS_follow.empty()) {
    // Check if function is registered.
    if (client.IsRegistered("follow") == -1) {
      std::cout << "follow function is not registered." << std::endl;
      return;
    }
    client.Follow(FLAGS_user, FLAGS_follow);
  }
  else if (!FLAGS_read.empty()) {
    // Check if function is registered.
    if (client.IsRegistered("read") == -1) {
      std::cout << "read function is not registered." << std::endl;
      return;
    }
    client.Read(FLAGS_read);
  }
  else if (!FLAGS_subscribe.empty()) {
    // Check if function is registered.
	if (client.IsRegistered("subscribe") == -1) {
       std::cout << "subscribe function is not registered" << std::endl;
	   return;
	}
	client.Subscribe(FLAGS_user, FLAGS_subscribe);
  }
  else if (FLAGS_profile) {
    // Check if function is registered.
    if (client.IsRegistered("profile") == -1) {
      std::cout << "profile function is not regitsered." << std::endl;
      return;
    }
    std::cout << client.IsRegistered("profile") << std::endl;
    client.Profile(FLAGS_user);
  }
  else if (FLAGS_hook != -1) {
    // Hook event type with function.
    client.Hook(FLAGS_hook, FLAGS_event_function);
  }
  else if (FLAGS_unhook != -1) {
    client.Unhook(FLAGS_unhook);
  }
}

int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  RunCommand();
  return 0;
}
