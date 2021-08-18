# Simple FaaS Platform

In this project, we build a simple FaaS (Function as a Service) platform called *Faz*. On top of *Faz* build the infrastructure for a social network platform we’ll call *Caw*.

There are three keycomponents:
* ***Faz***: Responsible for function registration and management. An execution layer is needed in *Faz* to receive requests and execute them simultaneously. A key-value store abstraction that can enable storage and retrieval of data of functions that are being executed.
* ***Key Value Store***: A key-value store service that exposes put/get/remove functionality for use by Faz.
* ***Caw***: Handler functions for Caw requests (that live inside/run inside of Faz) that each make appropriate requests to the key-value store to put or get data and return the appropriate information to users. A C++ Caw frontend tool that enables a user to register, post new/reply to caws, follow other users, and read caw threads.

## 0. Requirements
* Ubuntu 20.04
* cmake version required: 3.15 or higher
```
# install cmake

sudo apt install -y cmake
```
* grpc installed globally
```
# grpc setup

export MY_INSTALL_DIR=$HOME/.local
mkdir -p $MY_INSTALL_DIR
export PATH="$PATH:$MY_INSTALL_DIR/bin"

# install other required tools

sudo apt install -y build-essential autoconf libtool pkg-config

#  install grpc

git clone --recurse-submodules -b v1.35.0 https://github.com/grpc/grpc
cd grpc
mkdir -p cmake/build
pushd cmake/build
cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
      ../..
make
make install
popd

# install protobuf

cd grpc/third_party/protobuf/cmake
cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR .
make
sudo apt install libprotobuf-dev
```
* Go installed globally

```
# install Go

rm -rf /usr/local/go && tar -C /usr/local -xzf go1.16.2.linux-amd64.tar.gz
export PATH=$PATH:/usr/local/go/bin
source ~/.profile

# install Go plugins for protobuf compiler

export GO111MODULE=on  # Enable module mode
go get google.golang.org/protobuf/cmd/protoc-gen-go \
       google.golang.org/grpc/cmd/protoc-gen-go-grpc

export PATH="$PATH:$(go env GOPATH)/bin"

```

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

# open a new terminal to build and run go-client

cd ../../src/go-client
go build client.go

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

# subscribe
./client --subscribe <hashtag>
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

### Test Utils
```
cd src

./util_test
```
