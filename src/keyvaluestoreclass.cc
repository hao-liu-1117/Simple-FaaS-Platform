#include "keyvaluestoreclass.h"

KeyValueStore::KeyValueStore() {
    ;
}

void KeyValueStore::put(int key, int value) {
  if (!map_.count(key)) {
    map_[key] = std::unordered_set<int>();
  }
  map_[key].insert(value);
}

std::unordered_set<int> KeyValueStore::get(int key) {
  if (!map_.count(key)) {
    return std::unordered_set<int>();
  }
  return map_[key];
}

void KeyValueStore::remove(int key) {
  if (map_.count(key)) {
    map_.erase(key);
  }
}

// code for better testing
std::vector<int> KeyValueStore::getWithOrder(int key) {
  auto result_set = get(key);
  std::vector<int> sorted_values;
  for (auto num:result_set) {
    sorted_values.push_back(num);
  }
  std::sort(sorted_values.begin(), sorted_values.end());
  return sorted_values;
}