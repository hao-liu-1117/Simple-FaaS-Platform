#ifndef KEYVALUESTORECLASS_H_
#define KEYVALUESTORECLASS_H_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "storage.pb.h"

// Backend key-value store which supports cocurrent access.
// To support multithread, a mutex required 
// in each method (except constructor) and released when finished.
class KeyValueStore {
 public:
  explicit KeyValueStore() : map_(), map_mutex_() {}

  virtual ~KeyValueStore() {}

  // Puts value to corresponding key.
  void Put(const std::string &key, const std::string &value);

  // Returns a set of values of the key.
  std::unordered_set<std::string> Get(const std::string &key) const;

  // Removes key-value pair.
  void Remove(const std::string &key);

  // Store key-value pairs to file.
  static void Store(KeyValueStore &instance, const std::string &filename);

  // Load key-value pairs from file.
  static void Load(KeyValueStore &instance, const std::string &filename);

 private:
  // Data structure for key-value storage.
  // Each key is a string.
  // Value could be a set of strings.
  std::unordered_map<std::string, std::unordered_set<std::string>> map_;

  // To support cocurrent access for key-value store, 
  // mutex is needed.
  mutable std::mutex map_mutex_;
};

#endif