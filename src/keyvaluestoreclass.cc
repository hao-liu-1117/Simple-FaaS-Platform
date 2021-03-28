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

void KeyValueStore::Store(KeyValueStore &instance, const std::string &filename) {

  std::fstream output(filename, std::ios::out | std::ios::trunc | std::ios::binary);

  storage::Memory mem;
  for (const auto& [key, valset] : instance.map_) {
    for (const auto& val : valset) {
      storage::Memory::KVPair *pair_to_add = mem.add_kv_pairs();
      pair_to_add->set_key(key);
      pair_to_add->set_value(val);
    }
  }

  mem.SerializeToOstream(&output);
}

void KeyValueStore::Load(KeyValueStore &instance, const std::string &filename) {
  std::fstream input(filename, std::ios::in | std::ios::binary);
  if (!input) {
    // Can not find file to load.
    return;
  }
  storage::Memory mem;
  mem.ParseFromIstream(&input);
  int len = mem.kv_pairs_size();
  for (int i = 0; i < len; i++) {
    instance.Put(mem.kv_pairs(i).key(), mem.kv_pairs(i).value());
  }
}