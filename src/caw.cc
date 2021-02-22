#include <chrono>

#include "caw.h"

#include "prefix.h"

// KVStore instances for maintaining data.
KeyValueStore users;
KeyValueStore following, follower;
// Track reply of caw.
KeyValueStore be_replied;
// Store caws in a map. Key is caw_id and value is content of caw.
std::unordered_map<std::string, caw::Caw> cawmap;
namespace cawfunc {

bool RegisterUser(const caw::RegisteruserRequest &request,
                  KVStoreClient &client) {
  std::string username = request.username();
  // Check if user already exists.
  if (UserExists(username, client)) {
    return false;
  }
  // Use kvstore as a set.
  client.Put(prefix::kUser + username, username);
  return true;
}

caw::Caw Caw(const caw::CawRequest &request,
             KVStoreClient &client) {
  std::string username = request.username();
  std::string text = request.text();
  std::string parent_id = request.parent_id();
  // Assign caw_id as current count of caws.
  std::string id = GetNextCawId(client);

  std::chrono::seconds secs = std::chrono::duration_cast<std::chrono::seconds>(
    std::chrono::system_clock::now().time_since_epoch()
  );
  std::chrono::microseconds usecs = std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::system_clock::now().time_since_epoch()
  );

  // store reply caw_id for parent caw.
  client.Put(prefix::kCawSonId + parent_id, id);
  
  // Pack those info to Caw and return.
  caw::Caw result;
  result.set_username(username);
  result.set_text(text);
  result.set_id(id);
  result.set_parent_id(parent_id);
  result.mutable_timestamp()->set_seconds(secs.count());
  result.mutable_timestamp()->set_useconds(usecs.count());

  std::string result_str;
  // serialize caw to result_str and store in kvstore
  result.SerializeToString(&result_str);
  client.Put(prefix::kCawId + id, result_str);
  return result;
}

bool Follow(const caw::FollowRequest &request,
            KVStoreClient &client) {
  std::string username = request.username();
  std::string to_follow = request.to_follow();
  // check if username and to_follow exists.
  if (!UserExists(username, client) || !UserExists(to_follow, client)) {
    return false;
  }
  client.Put(prefix::kFollowing + username, to_follow);
  client.Put(prefix::kFollowers + to_follow, username);
  return true;
}

caw::ReadReply Read(const caw::ReadRequest &request,
                    KVStoreClient &client) {
  caw::ReadReply reply;
  ReadThread(request.caw_id(), reply, client);
  return reply;
}

caw::ProfileReply Profile(const caw::ProfileRequest & request,
                          KVStoreClient &client) {
  std::string username = request.username();
  // keyarr/valarr used by kvstore client to fetch data into valarr.
  std::vector<std::string> keyarr, valarr;
  caw::ProfileReply reply;
  // Get followers.
  keyarr.push_back(prefix::kFollowers + username);
  client.Get(keyarr, valarr);
  for (const auto &u_name : valarr) {
    reply.add_followers(u_name);
  }

  keyarr.clear();
  valarr.clear();
  // Get following.
  keyarr.push_back(prefix::kFollowing + username);
  client.Get(keyarr, valarr);
  for (const auto &u_name : valarr) {
    reply.add_following(u_name);
  }

  return reply;
}

bool UserExists(const std::string &username, KVStoreClient &client) {
  std::vector<std::string> keyarr, valarr;
  keyarr.push_back(prefix::kUser + username);
  client.Get(keyarr, valarr);
  if (valarr.empty()) {
    return false;
  }
  return true;
}

std::string GetNextCawId(KVStoreClient &client) {
  std::vector<std::string> keyarr, valarr;
  keyarr.push_back(prefix::kCawCount);
  client.Get(keyarr, valarr);
  // caw_id stored in valarr
  std::string caw_id = valarr[0];
  int caw_id_int = std::stoi(caw_id);
  caw_id_int++;
  client.Remove(prefix::kCawCount);
  client.Put(prefix::kCawCount, std::to_string(caw_id_int));
  return caw_id;
}

void ReadThread(const std::string &caw_id, caw::ReadReply &reply, 
                KVStoreClient &client) {
  // Put current caw into reply.
  caw::Caw cur_caw = GetCawWithCawId(caw_id, client);
  caw::Caw *put_caw = reply.add_caws();

  // Copy fields to reply
  put_caw->set_username(cur_caw.username());
  put_caw->set_text(cur_caw.text());
  put_caw->set_id(cur_caw.id());
  put_caw->set_parent_id(cur_caw.parent_id());
  put_caw->mutable_timestamp()->set_seconds(
    cur_caw.mutable_timestamp()->seconds()
  );
  put_caw->mutable_timestamp()->set_useconds(
    cur_caw.mutable_timestamp()->useconds()
  );
  
  // If other caws replied to this one, 
  // put them into caw::ReadReply recursively.
  std::vector<std::string> keyarr, valarr;
  keyarr.push_back(prefix::kCawSonId + caw_id);
  client.Get(keyarr, valarr);
  for (const auto &son_id : valarr) {
    ReadThread(son_id, reply, client);
  }
}

caw::Caw GetCawWithCawId(const std::string &caw_id, 
                         KVStoreClient &client) {
  caw::Caw cur_caw;
  // Get caw data from kvstore
  std::vector<std::string> keyarr, valarr;
  keyarr.push_back(prefix::kCawId + caw_id);
  client.Get(keyarr, valarr);
  if (!valarr.empty()) {
    // parse from serialized caw 
    cur_caw.ParseFromString(valarr[0]);
  }

  return cur_caw;
}

faz::EventReply RegisterUserHelper(const faz::EventRequest *event_req,
                                    KVStoreClient &client) {
  caw::RegisteruserRequest request;
  faz::EventReply event_rep;
  event_req->payload().UnpackTo(&request);
  RegisterUser(request, client);
  return event_rep;
}

faz::EventReply CawHelper(const faz::EventRequest *event_req, 
                           KVStoreClient &client) {
  caw::CawRequest request;
  faz::EventReply event_rep;
  event_req->payload().UnpackTo(&request);
  caw::Caw reply = Caw(request, client);
  (event_rep.mutable_payload())->PackFrom(reply);
  return event_rep;
}

faz::EventReply FollowHelper(const faz::EventRequest *event_req, 
                              KVStoreClient &client) {
  caw::FollowRequest request;
  faz::EventReply event_rep;
  (event_req->payload()).UnpackTo(&request);
  Follow(request, client);
  return event_rep;
}

faz::EventReply ReadHelper(const faz::EventRequest *event_req,
                            KVStoreClient &client) {
  caw::ReadRequest request;
  faz::EventReply event_rep;
  event_req->payload().UnpackTo(&request);
  caw::ReadReply reply = Read(request, client);
  (event_rep.mutable_payload())->PackFrom(reply);
  return event_rep;
}

faz::EventReply ProfileHelper(const faz::EventRequest *event_req,
                               KVStoreClient &client) {
  caw::ProfileRequest request;
  faz::EventReply event_rep;
  event_req->payload().UnpackTo(&request);
  caw::ProfileReply reply = Profile(request, client);
  (event_rep.mutable_payload())->PackFrom(reply);
  return event_rep;
}
} // namesapce cawfunc