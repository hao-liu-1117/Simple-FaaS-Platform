 #include <glog/logging.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "kvstore_client.h"

namespace {

// Test methods Put and Get in server works
TEST(KVStoreServerTest, PutAndGetTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));

  std::vector<std::string> keyarr, valarr;
  for (int i = 0; i < 10; i++) {
    keyarr.push_back("key"+std::to_string(i));
    valarr.push_back("value"+std::to_string(i));
    auto success = client.Put(keyarr[i], valarr[i]);
    if (!success) {
      LOG(INFO) << "KVStoreClient.Put falied";
      ASSERT_TRUE(success);
    }
  }
  std::vector<std::string> testvalarr;
  auto success = client.Get(keyarr, testvalarr);
  if (!success) {
    LOG(INFO) << "KVStoreClient.Get falied";
    ASSERT_TRUE(success);
  }
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(valarr[i], testvalarr[i]); // expected: ["value0", "value1", "value2", ...]
  }
}

// Test Remove method in server works.
TEST(KVStoreServerTest, RemoveTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  
  std::vector<std::string> keyarr, valarr;
  keyarr.push_back("key0");
  client.Put("key0", "value0");

  std::vector<std::string> testvalarr;
  client.Remove("key0");
  auto success = client.Get(keyarr, testvalarr);
  ASSERT_TRUE(testvalarr.empty());
}

} // namespace

int main (int argc, char** argv) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                         grpc::InsecureChannelCredentials()));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
