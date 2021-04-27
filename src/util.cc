#include <string>
#include <regex>
#include <vector>

// some useful util
namespace util {
// Resolve hashtag "#hashtag" from string text
std::vector<std::string> ResolveHashtags(const std::string &text) {
  std::vector<std::string> hashtags;
  std::string text_to_resolve = text;
  std::smatch match;
  std::regex expr("#[A-Za-z0-9]+");
  while (std::regex_search(text_to_resolve, match, expr)) {
    for (auto m : match) {
      hashtags.push_back(m.str().substr(1));
    }
    text_to_resolve = match.suffix().str();
  }
  return hashtags;
}
}
