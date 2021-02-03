#ifndef KEYVALUESTORECLASS_H_
#define KEYVALUESTORECLASS_H_

#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

class KeyValueStore {
public:

  explicit KeyValueStore();

  void put(int key, int value);

  std::unordered_set<int> get(int key);

  void remove(int key);

  // code for better testing
  std::vector<int> getWithOrder(int key);

private:
  std::unordered_map<int, std::unordered_set<int>> map_;
};

#endif