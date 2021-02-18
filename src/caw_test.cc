#include <glog/logging.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "caw.h"

namespace {

// Test cawfunc::RegisterUser works.
TEST(CawfuncTest, RegisterUserTest) {
  caw::RegisteruserRequest request;
  request.set_username("user1");
  bool suc = cawfunc::RegisterUser(request);
  ASSERT_TRUE(suc);
  // register same username should return false.
  suc = cawfunc::RegisterUser(request);
  ASSERT_FALSE(suc);
  request.set_username("user2");
  suc = cawfunc::RegisterUser(request);
  ASSERT_TRUE(suc);
  request.set_username("user3");
  suc = cawfunc::RegisterUser(request);
  ASSERT_TRUE(suc);
}

// Test cawfunc::Caw works.
TEST(CawfuncTest, CawTest) {
  caw::CawRequest request;
  request.set_username("user1");
  request.set_text("A test caw message.");
  // not a reply to other caw.
  request.set_parent_id("");
  caw::Caw result = cawfunc::Caw(request);
  // first caw should be assigned id=0.
  ASSERT_EQ("0", result.id());
  request.set_username("user2");
  request.set_text("A reply to caw_id=0.");
  // a reply to caw_id = 0;
  request.set_parent_id("0");
  result = cawfunc::Caw(request);
  ASSERT_EQ("1", result.id());
  ASSERT_EQ("0", result.parent_id());
}

// Test cawfunc::Follow and caw::Profile works.
TEST(CawfuncTest, FollowProfileTest) {
  caw::FollowRequest request;
  // user1 follow user2 should be success.
  request.set_username("user1");
  request.set_to_follow("user2");
  bool suc = cawfunc::Follow(request);
  ASSERT_TRUE(suc);
  // user2 follow user3 should be success.
  request.set_username("user2");
  request.set_to_follow("user3");
  suc = cawfunc::Follow(request);
  ASSERT_TRUE(suc);
  // user2 follow user4 should be failed because user4 does not exist.
  request.set_to_follow("user4");
  suc = cawfunc::Follow(request);
  ASSERT_FALSE(suc);

  // Test caw::Profile
  caw::ProfileRequest prequest;
  prequest.set_username("user1");
  caw::ProfileReply reply = cawfunc::Profile(prequest);
  // user1's followers: [] ; user1's following: [user2]
  ASSERT_EQ(0, reply.followers_size());
  ASSERT_EQ(1, reply.following_size());
  ASSERT_EQ("user2", reply.following(0));

  prequest.set_username("user2");
  reply = cawfunc::Profile(prequest);
  // user2's followers: [user1] ; user2's following: [user3]
  ASSERT_EQ(1, reply.followers_size());
  ASSERT_EQ("user1", reply.followers(0));
  ASSERT_EQ(1, reply.following_size());
  ASSERT_EQ("user3", reply.following(0));
}

TEST(CawfuncTest, ReadTest) {
  // TODO.
  // I'm a bit confused with Read implementation. Details are in caw.cc
}

} // namespace

int main (int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}