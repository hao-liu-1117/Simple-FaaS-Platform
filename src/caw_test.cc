#include <glog/logging.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "caw.h"
#include "kvstore_client.h"
#include "prefix.h"

namespace {

// Test cawfunc::RegisterUser works.
TEST(CawfuncTest, RegisterUserTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  caw::RegisteruserRequest request;
  request.set_username("user1");
  bool rep = cawfunc::RegisterUser(request, client);
  ASSERT_TRUE(rep);
  // register same username should return false.
  rep = cawfunc::RegisterUser(request, client);
  ASSERT_FALSE(rep);
  request.set_username("user2");
  rep = cawfunc::RegisterUser(request, client);
  ASSERT_TRUE(rep);
  request.set_username("user3");
  rep = cawfunc::RegisterUser(request, client);
  ASSERT_TRUE(rep);
}

// Test cawfunc::Caw works.
TEST(CawfuncTest, CawTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  caw::CawRequest request;
  request.set_username("user1");
  request.set_text("A test caw message.");
  // not a reply to other caw.
  request.set_parent_id("");
  caw::Caw result = cawfunc::Caw(request, client);
  // first caw should be assigned id=0.
  ASSERT_EQ("0", result.id());
  request.set_username("user2");
  request.set_text("A reply to caw_id=0.");
  // a reply to caw_id = 0;
  request.set_parent_id("0");
  result = cawfunc::Caw(request, client);
  ASSERT_EQ("1", result.id());
  ASSERT_EQ("0", result.parent_id());
}

// Test Caw with hastags text
TEST(CawfuncTest, CawAndSubscribeWithHashtagTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  caw::CawRequest caw_request;
  caw_request.set_username("user1");
  caw_request.set_text("Test caw with #hashtag1 and #hashtag2");
  // not a reply to other caw.
  caw_request.set_parent_id("");
  caw::Caw result = cawfunc::Caw(caw_request, client);
  // Check DB stream_tag2caw_hashtag1
  std::vector<std::string> keyarr, valarr;
  keyarr.push_back(prefix::kStream_tag2caws + "hashtag1");
  keyarr.push_back(prefix::kStream_tag2caws + "hashtag2");
  client.Get(keyarr, valarr);
  ASSERT_EQ(2, valarr.size());
}

// Test cawfunc::Follow and caw::Profile works.
TEST(CawfuncTest, FollowProfileTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  caw::FollowRequest request;
  // user1 follow user2 should be success.
  request.set_username("user1");
  request.set_to_follow("user2");
  bool rep = cawfunc::Follow(request, client);
  ASSERT_TRUE(rep);
  // user2 follow user3 should be success.
  request.set_username("user2");
  request.set_to_follow("user3");
  rep = cawfunc::Follow(request, client);
  ASSERT_TRUE(rep);
  // user2 follow user4 should be failed because user4 does not exist.
  request.set_to_follow("user4");
  rep = cawfunc::Follow(request, client);
  ASSERT_FALSE(rep);

  // Test caw::Profile
  caw::ProfileRequest prequest;
  prequest.set_username("user1");
  caw::ProfileReply reply = cawfunc::Profile(prequest, client);
  // user1's followers: [] ; user1's following: [user2]
  ASSERT_EQ(0, reply.followers_size());
  ASSERT_EQ(1, reply.following_size());
  ASSERT_EQ("user2", reply.following(0));

  prequest.set_username("user2");
  reply = cawfunc::Profile(prequest, client);
  // user2's followers: [user1] ; user2's following: [user3]
  ASSERT_EQ(1, reply.followers_size());
  ASSERT_EQ("user1", reply.followers(0));
  ASSERT_EQ(1, reply.following_size());
  ASSERT_EQ("user3", reply.following(0));
}

TEST(CawfuncTest, ReadTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  caw::ReadRequest request;
  request.set_caw_id(std::string("0"));
  caw::ReadReply reply = cawfunc::Read(request, client); // reply caw_id: [0, 1]
  ASSERT_EQ(2, reply.caws_size());
  for (int i = 0; i < reply.caws_size(); i++) {
    caw::Caw cur_caw = reply.caws(i);
    ASSERT_EQ(std::to_string(i), cur_caw.id());
  }
}

// Test function that resolve hashtags from caw text
TEST(CawfuncTest, ResolveHashtagsTest) {
  std::string caw_text = "This is a #test #msg";
  std::vector<std::string> hashtags = cawfunc::ResolveHashtags(caw_text);
  ASSERT_EQ(2, hashtags.size());
  ASSERT_EQ("test", hashtags[0]);
  ASSERT_EQ("msg", hashtags[1]);
}

} // namespace

int main (int argc, char** argv) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
