#include "keyvaluestoreclass.h"

void KeyValueStore::Put(const std::string key, const std::string value) {
  if (!map_.count(key)) {
    map_[key] = std::unordered_set<std::string>();
  }
  map_[key].insert(value);
}

std::unordered_set<std::string> KeyValueStore::Get(const std::string key) {
  if (!map_.count(key)) {
    return std::unordered_set<std::string>();
  }
  return map_[key];
}

void KeyValueStore::Remove(const std::string key) {
  if (map_.count(key)) {
    map_.erase(key);
  }
}