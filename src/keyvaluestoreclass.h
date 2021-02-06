#ifndef KEYVALUESTORECLASS_H_
#define KEYVALUESTORECLASS_H_

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Backend key-value store.
// TODO: cocurrent key-value store.
class KeyValueStore {
 public:
  explicit KeyValueStore() : map_() {}

  void Put(const std::string key, const std::string value);

  std::unordered_set<std::string> Get(const std::string key);

  void Remove(const std::string key);

 private:
  std::unordered_map<std::string, std::unordered_set<std::string>> map_;
};

#endif