#include <iostream>
#include <string>

#include "cmd_client.h"

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

  caw::RegisteruserRequest rep;
  event_rep.payload().UnpackTo(&rep);
  if (!rep.username().empty()) {
    std::cout << "Register user " << username << " success." << std::endl;
  }
  else {
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

  caw::RegisteruserRequest rep;
  event_rep.payload().UnpackTo(&rep);
  if (!rep.username().empty()) {
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

void CMDClient::Subscribe(const std::string &username, const std::string &hashtag) {
  // check is username is empty .
  if (username.empty()) {
	  std::cout << "Log in before subscribe" << std::endl;
	  return;
  }
  std::cout << username << " is subscribing " << hashtag << std::endl;
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
  std::cout << std::endl;
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
