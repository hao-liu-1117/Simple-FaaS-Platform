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

void CMDClient::Hook(const int event_type, const std::string &funcstr) {
  if (event_type == -1) {
    std::cout << "event tpye is not specified." << std::endl;
    return;
  }
  if (funcstr.empty()) {
    std::cout << "event function can not be empty." << std::endl;
    return;
  }
  bool suc = fazclient_.Hook(event_type, funcstr);
  if (suc) {
    std::cout << "Hook event type " << event_type
              << "with event function" << funcstr << " success.";
  }
  else {
    std::cout << "Hook event type " << event_type
              << "with event function" << funcstr << " falied."; 
  }
}

void CMDClient::Unhook(const int event_type) {
  if (event_type == -1) {
    std::cout << "event tpye is not specified." << std::endl;
    return;
  }
  bool suc = fazclient_.Unhook(event_type);
  if (suc) {
    std::cout << "Unhook event type " << event_type << " success.";
  }
  else {
    std::cout << "Unhook event type " << event_type << " falied."; 
  }
}

void CMDClient::RegisterUser(const std::string &username) {
  // Check if username is empty.
  if (username.empty()) {
    std::cout << "Username can not be empty when register user." << std::endl;
    return;
  }
  // Construct caw::RegisteruserRequest.
  caw::RegisteruserRequest req;
  req.set_username(username);
  // Pack to faz::EventRequest.
  faz::EventRequest event_req;
  int event_type = IsRegistered("registeruser");
  // std::cout << event_type << std::endl;
  event_req.set_event_type(event_type);
  (event_req.mutable_payload())->PackFrom(req);
  // Execute registeruser.
  faz::EventReply event_rep = fazclient_.Event(event_req);

  caw::RegisteruserReply rep;
  event_rep.payload().UnpackTo(&rep);
  if (rep.success()) {
    std::cout << "Register user " << username << " success." << std::endl;
  }
  else {
    std::cout << rep.success() << std::endl;
    std::cout << "Register user " << username << " failed." << std::endl;
  }
}

void CMDClient::Caw(const std::string &username, const std::string &text, std::string reply_id="") {
  // Check if username is empty.
  if (username.empty()) {
    std::cout << "Log in before sending a caw." << std::endl;
    return;
  }
  // Check if text is empty.
  if (text.empty()) {
    std::cout << "Text can not be empty." << std::endl;
    return;
  }
  // Construct caw::CawRequest
  caw::CawRequest req;
  req.set_username(username);
  req.set_text(text);
  req.set_parent_id(reply_id);
  // Consruct faz::EventRequest.
  faz::EventRequest event_req;
  int event_type = IsRegistered("caw");
  event_req.set_event_type(event_type);
  (event_req.mutable_payload())->PackFrom(req);
  // Execute registeruser.
  faz::EventReply event_rep = fazclient_.Event(event_req);
  caw::Caw rep;
  event_rep.payload().UnpackTo(&rep);

  if (rep.id() == "-1") {
    // Check if username is valid.
    std::cout << "User does not exist." << std::endl;
    return;
  }
  else if (rep.parent_id() == "-1") {
    // Check if parent caw id exists.
    std::cout << "Parent caw id does not exist." << std::endl;
    return;
  }
  else {
    // Already created and stored a valid caw in kvstore.
    // Print caw.
    std::cout << "Post a caw successfully." << std::endl;
    PrintCaw(rep);
  }
}

void CMDClient::Follow(const std::string &username, const std::string &to_follow) {
  // Check if username is empty.
  if (username.empty()) {
    std::cout << "Log in before following someone." << std::endl;
    return;
  }
  // Check if to_follow is empty.
  if (to_follow.empty()) {
    std::cout << "Can not follow an empty username." << std::endl;
    return;
  }
  // Construct caw::FollowRequest
  caw::FollowRequest req;
  req.set_username(username);
  req.set_to_follow(to_follow);
  // Pack to faz::EventRequest
  faz::EventRequest event_req;
  int event_type = IsRegistered("follow");
  event_req.set_event_type(event_type);
  (event_req.mutable_payload())->PackFrom(req);
  // Execute registeruser.
  faz::EventReply event_rep = fazclient_.Event(event_req);

  caw::FollowReply rep;
  event_rep.payload().UnpackTo(&rep);
  if (rep.success()) {
    std::cout << "Follow user " << to_follow << " success." << std::endl;
  }
  else {
    std::cout << "Follow user " << to_follow << " failed." << std::endl;
  }
}

void CMDClient::Read(const std::string &caw_id) {
  // Check if caw_id is empty.
  if (caw_id.empty()) {
    std::cout << "Caw Id can not be empty." << std::endl;
    return;
  }
  // Create caw::ReadRequest.
  caw::ReadRequest req;
  req.set_caw_id(caw_id);
  // Pack to faz::EventRequest.
  faz::EventRequest event_req;
  int event_type = IsRegistered("read");
  event_req.set_event_type(event_type);
  (event_req.mutable_payload())->PackFrom(req);
  // Execute registeruser.
  faz::EventReply event_rep = fazclient_.Event(event_req);
  caw::ReadReply rep;
  event_rep.payload().UnpackTo(&rep);
  if (rep.caws_size() == 0) {
    std::cout << "Caw Id " << caw_id << " does not exist." << std::endl;
    return;
  }
  std::cout << "Caw Thread " << caw_id << ": "<< std::endl;
  for (int i = 0; i < rep.caws_size(); i++) {
    PrintCaw(rep.caws(i));
  }
}

void CMDClient::Profile(const std::string &username) {
  // Check if username is empty.
  if (username.empty()) {
    std::cout << "Log in before viewing profile." << std::endl;
    return;
  }
  // Construct caw::ProfileRequest.
  caw::ProfileRequest req;
  req.set_username(username);
  // Pack to faz::EventRequest
  faz::EventRequest event_req;
  int event_type = IsRegistered("profile");
  event_req.set_event_type(event_type);
  (event_req.mutable_payload())->PackFrom(req);
  // Execute registeruser.
  faz::EventReply event_rep = fazclient_.Event(event_req);
  caw::ProfileReply rep;
  event_rep.payload().UnpackTo(&rep);
  PrintProfile(username, rep);
}

void PrintProfile(const std::string &username, const caw::ProfileReply &rep) {
  std::cout << username << "'s followers: ";
  for (int i = 0; i < rep.followers_size(); i++) {
    std::cout << rep.followers(i) << " ";
  }
  std::cout << std::endl;
  std::cout << username << "'s following: ";
  for (int i = 0; i < rep.following_size(); i++) {
    std::cout << rep.following(i) << " ";
  }
  std::cout << std::endl;
}

void PrintCaw(const caw::Caw &c) {
  std::cout << "Caw username: " << c.username() << std::endl;
  std::cout << "Text: " << c.text() << std::endl;
  std::cout << "Id: " << c.id() << std::endl;
  if (!c.parent_id().empty()) {
    std::cout << "Reply to caw id: " << c.parent_id() << std::endl;
  }
}

int CMDClient::IsRegistered(const std::string &funcstr) {
  return fazclient_.IsRegistered(funcstr);
}

void RunCommand() {
  CMDClient client(grpc::CreateChannel("0.0.0.0:50000",
                   grpc::InsecureChannelCredentials()));
  int cmd_count = 0;
  // Each command should only execute one command.
  if (!FLAGS_registeruser.empty()) cmd_count++;
  if (!FLAGS_caw.empty()) cmd_count++;
  if (!FLAGS_follow.empty()) cmd_count++;
  if (!FLAGS_read.empty()) cmd_count++;
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