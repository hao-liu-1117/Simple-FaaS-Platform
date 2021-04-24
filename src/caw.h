#ifndef CAW_H_
#define CAW_H_

#include <string>
#include <vector>

#include <google/protobuf/any.pb.h>
#include <grpcpp/grpcpp.h>

#include "caw.pb.h"
#include "caw.grpc.pb.h"
#include "faz.grpc.pb.h"
#include "kvstore_client.h"

namespace cawfunc {

// Return true if register success, false if failed.
bool RegisterUser(const caw::RegisteruserRequest &request, KVStoreClient &client);

// Resolve hashtags from caw text
std::vector<std::string> ResolveHashtags(const std::string &text);

// Create a new caw and return caw_id.
caw::Caw Caw(const caw::CawRequest &request, KVStoreClient &client);

// Return true if follow success, false if failed.
bool Follow(const caw::FollowRequest &request, KVStoreClient &client);

// Return caw thread with the giving caw_id.
caw::ReadReply Read(const caw::ReadRequest &request, KVStoreClient &client);

// Return user's following and followers.
caw::ProfileReply Profile(const caw::ProfileRequest & request, KVStoreClient &client);

// Return caws that have hashtag
caw::SubscribeReply Subscribe(const caw::SubscribeRequest &request,
                                            KVStoreClient &client);

bool UserExists(const std::string &username, KVStoreClient &client);

// Assign caw_id as current count of caws.
// Current count of caws add by one.
// Store current caw_id into kvstore.
std::string GetNextCawId(KVStoreClient &client);

// Read caw thread by DFS and store caws into caw::ReadReply.
// A helper method of cawfunc::Read()
void ReadThread(const std::string &caw_id, caw::ReadReply &reply, 
                KVStoreClient &client);

caw::Caw GetCawWithCawId(const std::string &caw_id, KVStoreClient &client);

/*
  Helper functions for RegisterUser, Caw, Follow, Read and Profile.
  Input parameters are faz::EventRequest* and kvstore client 
  return is faz::EventReply*
*/
faz::EventReply RegisterUserHelper(const faz::EventRequest *event_req, KVStoreClient &client);
faz::EventReply CawHelper(const faz::EventRequest *event_req, KVStoreClient &client);
faz::EventReply FollowHelper(const faz::EventRequest *event_req, KVStoreClient &client);
faz::EventReply ReadHelper(const faz::EventRequest *event_req, KVStoreClient &client);
faz::EventReply ProfileHelper(const faz::EventRequest *event_req, KVStoreClient &client);

} // namespace cawfunc

#endif
