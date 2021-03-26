#include <glog/logging.h>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "kvstore_client.h"

namespace {

// Test if KeyValueStore::Store/Load works.
// This test should run after kvstore_server_test.
// To run this test, open a kvstore server with flag --store.
// Then run kvstore_server_test and then kvstore_load_test.
TEST(KVStoreServerLoadTest, LoadTest) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  
  std::vector<std::string> keyarr, valarr;
  for (int i = 1; i < 10; i++) {
    keyarr.push_back("key"+std::to_string(i));
    valarr.push_back("value"+std::to_string(i));
  }
  std::vector<std::string> testvalarr;
  auto success = client.Get(keyarr, testvalarr);
  if (!success) {
    LOG(INFO) << "KVStoreClient.Get falied";
    ASSERT_TRUE(success);
  }

  for (int i = 0; i < 9; i++) {
    ASSERT_EQ(valarr[i], testvalarr[i]); // expected: ["value1", "value2", ...]
  }
}

} // namespace

int main (int argc, char** argv) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                       grpc::InsecureChannelCredentials()));
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
