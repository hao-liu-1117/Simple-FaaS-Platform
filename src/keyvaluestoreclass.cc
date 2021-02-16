#include "keyvaluestoreclass.h"

void KeyValueStore::Put(const std::string &key, const std::string &value) {
  const std::lock_guard<std::mutex> lock(map_mutex_);
  map_[key].insert(value);
}

std::unordered_set<std::string> KeyValueStore::Get(const std::string &key) const {
  const std::lock_guard<std::mutex> lock(map_mutex_);
  std::unordered_set<std::string> res_set;
  // Checking existence of key is needed becasue 
  // calling method .at(key) with an invalid key 
  // would cause a std::out_of_range() exception.
  if (!map_.count(key)) {
    return res_set;
  }

  for (const std::string &str : map_.at(key)) {
    res_set.insert(str);
  }
  return res_set;
}

void KeyValueStore::Remove(const std::string &key) {
  const std::lock_guard<std::mutex> lock(map_mutex_);
  map_.erase(key);
}