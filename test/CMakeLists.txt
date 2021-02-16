include_directories("${PROJECT_SOURCE_DIR}/src")

include(FetchContent)

find_package(GTest REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# Import glog
FetchContent_Declare(
  glog
  GIT_REPOSITORY https://github.com/google/glog.git
  GIT_TAG v0.4.0
)
FetchContent_MakeAvailable(glog)

message(STATUS "${PROJECT_SOURCE_DIR}/src")

add_executable(kvstore_test "kvstore_test.cc")

target_link_libraries(kvstore_test kvstore_lib GTest::GTest GTest::Main glog)

set(kvstore_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/../src/keyvaluestore.pb.cc")
set(kvstore_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../src/keyvaluestore.pb.h")
set(kvstore_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/../src/keyvaluestore.grpc.pb.cc")
set(kvstore_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/../src/keyvaluestore.grpc.pb.h")

add_executable(kvstore_server_test "kvstore_server_test.cc" "${PROJECT_SOURCE_DIR}/src/kvstore_server.cc" ${kvstore_proto_srcs} ${kvstore_grpc_srcs})

target_link_libraries(kvstore_test kvstore_lib GTest::GTest GTest::Main glog ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})



