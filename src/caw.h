#ifndef CAW_H_
#define CAW_H_

#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>

#include "caw.pb.h"
#include "caw.grpc.pb.h"
#include "kvstore_client.h"

namespace cawfunc {

// Return true if register success, false if failed.
bool RegisterUser(const caw::RegisteruserRequest &request, KVStoreClient &client);

// Create a new caw and return caw_id.
caw::Caw Caw(const caw::CawRequest &request, KVStoreClient &client);

// Return true if follow success, false if failed.
bool Follow(const caw::FollowRequest &request, KVStoreClient &client);

// Return caw thread with the giving caw_id.
caw::ReadReply Read(const caw::ReadRequest &request, KVStoreClient &client);

// Return user's following and followers.
caw::ProfileReply Profile(const caw::ProfileRequest & request, KVStoreClient &client);

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

} // namespace cawfunc

#endif