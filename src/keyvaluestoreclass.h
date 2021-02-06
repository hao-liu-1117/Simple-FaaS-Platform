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

  void Put(int key, std::string value);

  std::unordered_set<std::string> Get(int key);

  void Remove(int key);

 private:
  std::unordered_map<int, std::unordered_set<std::string>> map_;
};

#endif