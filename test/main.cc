#include <gtest/gtest.h>
#include "gmock/gmock.h"

#include "keyvaluestoreclass.h"

TEST(FunctionTest, PutAndGetTest) {
  KeyValueStore store;
  std::vector<int> comp_arr;
  for (int i = 0; i < 10; i++) {
    store.put(0, i);
    comp_arr.push_back(i);
  }

  std::vector<int> store_arr = store.getWithOrder(0);
  ASSERT_TRUE(store_arr.size()==comp_arr.size()); // expected: 10==10
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(store_arr[i], comp_arr[i]); // expected: [0, 1, 2, ..., 9]
  }

  store_arr = store.getWithOrder(1);
  ASSERT_TRUE(0==store_arr.size()); // expected: 0==0
}

TEST(FunctionTest, RemoveTest) {
  KeyValueStore store;
  std::vector<int> comp_arr;
  for (int i = 0; i < 10; i++) {
    store.put(0, i);
    comp_arr.push_back(i);
  }
  std::vector<int> store_arr = store.getWithOrder(0); // expected: 10==10
  ASSERT_TRUE(store_arr.size()==comp_arr.size());
  for (int i = 0; i < 10; i++) {
    ASSERT_EQ(store_arr[i], comp_arr[i]); // expected: [0, 1, 2, ..., 9]
  }

  store.remove(0);
  store_arr = store.getWithOrder(0);
  ASSERT_TRUE(0==store_arr.size()); // expected: 0==0
};

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
