#include <iostream>
#include <string>
#include <vector>

#include "kvstore_client.h"

bool TestPrintPairs (const std::vector<std::string> &keyarr, 
                     const std::vector<std::string> &valarr, 
                     const std::vector<std::string> &testarr) {
  int len = keyarr.size();
  if (testarr.size()!=len) {
    std::cout << "length of key array != length of return value array!" << std::endl;
    return false;
  }

  for (int i = 0; i < len; i++) {
    if (valarr[i]!=testarr[i]) {
      std::cout << "get wrong value using " << keyarr[i] 
                << std::endl;
      return false;
    }
    std::cout << keyarr[i] << "---" << testarr[i] << std::endl;
  }
  return true;
}

int main (int argc, char** argv) {
  KVStoreClient client(grpc::CreateChannel("0.0.0.0:50001",
                grpc::InsecureChannelCredentials()));
  std::vector<std::string> keyarr, valarr;
  for (int i = 0; i < 10; i++) {
    keyarr.push_back("key"+std::to_string(i));
    valarr.push_back("value"+std::to_string(i));
    client.Put(keyarr[i], valarr[i]);
  }
  std::vector<std::string> testvalarr;
  auto success = client.Get(keyarr, testvalarr);
  if (!success) {
    std::cout << "KVStoreClient.Get falied" << std::endl;
    return 1;
  }
  TestPrintPairs(keyarr, valarr, testvalarr);
  
  return 0;
}