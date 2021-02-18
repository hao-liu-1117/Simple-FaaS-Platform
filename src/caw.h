#ifndef CAW_H_
#define CAW_H_

#include <string>
#include <vector>
#include <grpcpp/grpcpp.h>

#include "caw.pb.h"
#include "keyvaluestoreclass.h"

namespace cawfunc {

// Return true if register success, false if failed.
bool RegisterUser(const caw::RegisteruserRequest &request);

// Create a new caw and return caw_id.
caw::Caw Caw(const caw::CawRequest &request);

// Return true if follow success, false if failed.
bool Follow(const caw::FollowRequest &request);

// Return caw thread with the giving caw_id.
caw::ReadReply Read(const caw::ReadRequest &request);

// Return user's following and followers.
caw::ProfileReply Profile(const caw::ProfileRequest & request);

bool UserExists(const std::string &username);

} // namespace cawfunc

#endif