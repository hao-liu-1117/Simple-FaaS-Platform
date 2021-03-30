# csci499_hao-liu-1117

## 0. Requirements
* Ubuntu 20.04
* cmake version required: 3.15 or higher
* grpc installed globally

## 1. Build
```
git clone https://github.com/hao-liu-1117/csci499_hao-liu-1117.git
cd csci499_hao-liu-1117
mkdir build && cd build
cmake ..
make
```

## 2. Run Command Line Client
```
cd src

# start kvstore server and faz server

./kvstore_server

# open a new terminal

./faz_server

# open a new terminal and run go-client

cd ../../src/go-client

# registeruser

./client --registeruser <username>

# caw

./client --caw <caw_text> --user <username>
# or
./client --caw <caw_text> --user <username> --reply <Caw_ID>

# read

./client --read <Caw_ID>

# follow

./client --follow <to> --user <from>

# profile

./client --profile --user <username>
```

### Test KVStore
```
cd src

# test kvstore functionality

./kvstore_test
```
```
# test kvstore server

./kvstore_server

# open a new terminal
./kvstore_server_test
```
```
# test kvstore storage

./kvstore_server --store kvstore.dat

# open a new terminal
./kvstore_server_test

# shut down kvstore server by Ctrl+C
# restart kvstore server to load data from kvstore.dat

./kvstore_server --store kvstore.dat

# in a new terminal
./kvstore_server_load_test
```

### Test Caw Functionality
```
cd src

./kvstore_server

# open a new terminal
./caw_test
```