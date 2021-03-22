#include <string>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "keyvaluestoreclass.h"

namespace {

// Test that put and get methods work.
TEST(FunctionTest, PutAndGetTest) {
  KeyValueStore store;
  std::vector<std::string> comp_arr;
  int arr_len = 10;
  for (int i = 0; i < arr_len; i++) {
    store.Put("key" + std::to_string(0), "value" + std::to_string(i));
    comp_arr.push_back("value" + std::to_string(i));
  }

  std::vector<std::string> store_arr;

  std::unordered_set<std::string> store_set = store.Get("key" + std::to_string(0));
  for (auto &str:store_set) {
    store_arr.push_back(str);
  }
  sort(store_arr.begin(), store_arr.end());

  ASSERT_EQ(store_arr.size(), comp_arr.size()); // expected: 10==10
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(store_arr[i], comp_arr[i]); // expected: ["value0", "value1", "value2", ...]
  }

  store_set = store.Get("key" + std::to_string(1));
  store_arr.clear();
  for (auto &str:store_set) {
    store_arr.push_back(str);
  }
  sort(store_arr.begin(), store_arr.end());

  ASSERT_EQ(0, store_arr.size()); // expected: 0==0
}

// Test that remove method works.
TEST(FunctionTest, RemoveTest) {
  KeyValueStore store;
  std::vector<std::string> comp_arr;
  int arr_len = 10;

  for (int i = 0; i < arr_len; i++) {
    store.Put("key" + std::to_string(0), "value" + std::to_string(i));
    comp_arr.push_back("value" + std::to_string(i));
  }

  std::vector<std::string> store_arr;

  std::unordered_set<std::string> store_set = store.Get("key" + std::to_string(0));
  for (auto &str:store_set) {
    store_arr.push_back(str);
  }
  sort(store_arr.begin(), store_arr.end());

  ASSERT_EQ(store_arr.size(), comp_arr.size()); // expected: 10==10
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(store_arr[i], comp_arr[i]); // expected: [0, 1, 2, ..., 9]
  }

  store.Remove("key" + std::to_string(0));
  store_set = store.Get("key" + std::to_string(0));
  store_arr.clear();
  for (auto &str:store_set) {
    store_arr.push_back(str);
  }
  sort(store_arr.begin(), store_arr.end());
  
  ASSERT_TRUE(store_arr.empty()); // expected: 0==0
};

TEST(FunctionTest, StoreLoadTest) {
  KeyValueStore store;
  std::vector<std::string> comp_arr;
  int arr_len = 10;
  for (int i = 0; i < arr_len; i++) {
    store.Put("key" + std::to_string(0), "value" + std::to_string(i));
    comp_arr.push_back("value" + std::to_string(i));
  }

  std::vector<std::string> store_arr;

  store.Store("teststore.txt");
  store.Remove("key" + std::to_string(0));
  std::unordered_set<std::string> store_set = store.Get("key" + std::to_string(0));
  ASSERT_TRUE(store_set.empty()); // expected: 0==0

  store.Load("teststore.txt");
  store_set = store.Get("key" + std::to_string(0));
  ASSERT_TRUE(store_set.size()==10); // expeceted: 10==10
}


} // namespace

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
