#include "gtest/gtest.h"

#include "util.cc"

namespace {

// Test for resolve hashtags
TEST(FazServerTest, ResolveHashtagsTest) {
  std::string text = "#test1#test2 for #test.";
  std::vector<std::string> expected_hashtags {"test1", "test2", "test"};
  std::vector<std::string> actual_hashtags = util::ResolveHashtags(text);
  ASSERT_EQ(expected_hashtags[0], actual_hashtags[0]);
  ASSERT_EQ(expected_hashtags[1], actual_hashtags[1]);
  ASSERT_EQ(expected_hashtags[2], actual_hashtags[2]);
}
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
