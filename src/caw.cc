#include <chrono>

#include "caw.h"

using namespace std::chrono;

namespace cawfunc {

// KVStore instances for maintaining data.
KeyValueStore users;
KeyValueStore following, follower;
// Track reply of caw.
KeyValueStore be_replied;
// Store caws in a map. Key is caw_id and value is content of caw.
std::unordered_map<std::string, caw::Caw> cawmap;

bool RegisterUser(const caw::RegisteruserRequest &request) {
  std::string username = request.username();
  // check if user already exists.
  if (UserExists(username)) {
    return false;
  }
  // use kvstore as a set.
  users.Put(username, username);
  return true;
}

caw::Caw Caw(const caw::CawRequest &request) {
  std::string username = request.username();
  std::string text = request.text();
  std::string parent_id = request.parent_id();
  // Assign caw_id as current count of caws.
  std::string id = std::to_string(cawmap.size());

  seconds secs = duration_cast<seconds>(
    system_clock::now().time_since_epoch()
  );
  microseconds usecs = duration_cast<microseconds>(
    system_clock::now().time_since_epoch()
  );
  
  // Notify which caw get a reply.
  if (!parent_id.empty()) {
    be_replied.Put(parent_id, id);
  }
  
  // Pack those info to Caw and return.
  caw::Caw result;
  result.set_username(username);
  result.set_text(text);
  result.set_id(id);
  result.set_parent_id(parent_id);
  result.mutable_timestamp()->set_seconds(secs.count());
  result.mutable_timestamp()->set_useconds(usecs.count());
  
  cawmap[id] = result;
  return result;
}

bool Follow(const caw::FollowRequest &request) {
  std::string username = request.username();
  std::string to_follow = request.to_follow();
  // check if username and to_follow exists.
  if (!UserExists(username) || !UserExists(to_follow)) {
    return false;
  }
  following.Put(username, to_follow);
  follower.Put(to_follow, username);
  return true;
}

caw::ReadReply Read(const caw::ReadRequest &request) {
  // TODO.
  /*
    I'm not sure what to return with the given caw_id.
    Should I return caw itself and all the reply of this caw?
  */
 caw::ReadReply reply;
 return reply;
}

caw::ProfileReply Profile(const caw::ProfileRequest & request) {
  std::string username = request.username();

  caw::ProfileReply reply;
  auto follower_set = follower.Get(username);
  for (auto u_name : follower_set) {
    reply.add_followers(u_name);
  }

  auto following_set = following.Get(username);
  for (auto u_name : following_set) {
    reply.add_following(u_name);
  }

  return reply;
}

bool UserExists(const std::string &username) {
  if (users.Get(username).empty()) {
    return false;
  }
  return true;
}

} // namespace cawfunc