# csci499_hao-liu-1117

### Build and Test KVStore
```
mkdir build
cd build
cmake ..
make

cd src

./kvstore_server

# in a new terminal
./kvstore_server_test
```
### Test Caw Functionality
```
./kvstore_server

# in a new terminal
./caw_test
```

### cmd client setup
```
./cmd_client --hook 1 --event_function registeruser
./cmd_client --hook 2 --event_function caw
./cmd_client --hook 3 --event_function follow
./cmd_client --hook 4 --event_function read
./cmd_client --hook 5 --event_function profile
```

### Quick test cmd client
```
./kvstore_server

# in a new terminal
./faz_server

# in a new terminal
./client --registeruser Hao_Liu
./client --caw thisismyfirstcaw --user Hao_Liu
./client --caw thisismyreply --user Hao_Liu --reply 0
./client --caw this is my reply --user Hao_Liu --reply 1
./client --read 0
./client --registeruser Barath
./client --follow Barath --user Hao_Liu
./client --profile --user Hao_Liu
./client --profile --user Barath
#
```