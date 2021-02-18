include(FetchContent)

# Import glog
FetchContent_Declare(
  glog
  GIT_REPOSITORY https://github.com/google/glog.git
  GIT_TAG v0.4.0
)
FetchContent_MakeAvailable(glog)

# Protobuf
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${protobuf_VERSION}")

# Protobuf-compiler
set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# gRPC
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")
set(_GRPC_GRPCPP gRPC::grpc++)
set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)

# KVStore Proto file
get_filename_component(kvstore_proto "keyvaluestore.proto" ABSOLUTE)
get_filename_component(kvstore_proto_path "${kvstore_proto}" PATH)

# Generated sources
set(kvstore_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/keyvaluestore.pb.cc")
set(kvstore_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/keyvaluestore.pb.h")
set(kvstore_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/keyvaluestore.grpc.pb.cc")
set(kvstore_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/keyvaluestore.grpc.pb.h")

message(STATUS "current cmake dir = ${CMAKE_CURRENT_BINARY_DIR}")

message(STATUS "kvstore path = ${kvstore_proto_path}")

# aux_source_directory(. DIR_LIB_SRCS)

# add_library(kvstore_lib STATIC "keyvaluestoreclass.cc")

add_custom_command(
      OUTPUT "${kvstore_proto_srcs}" "${kvstore_proto_hdrs}" "${kvstore_grpc_srcs}" "${kvstore_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${kvstore_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${kvstore_proto}"
      DEPENDS "${kvstore_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# Targets (client|server)
foreach(_target
   kvstore_server)
  add_executable(${_target} "${_target}.cc"
    ${kvstore_proto_srcs}
    ${kvstore_grpc_srcs}
    "keyvaluestoreclass.cc"
    )
  target_link_libraries(${_target}
    ${_REFLECTION}
    ${_GRPC_GRPCPP}
    ${_PROTOBUF_LIBPROTOBUF})
endforeach()

# test kvstore server
find_package(GTest REQUIRED)

add_executable(kvstore_server_test "kvstore_server_test.cc" ${kvstore_proto_srcs} ${kvstore_grpc_srcs} "kvstore_client.cc")
target_link_libraries(kvstore_server_test GTest::GTest GTest::Main glog
${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})

# Caw Proto file
get_filename_component(caw_proto "caw.proto" ABSOLUTE)
get_filename_component(caw_proto_path "${caw_proto}" PATH)

# Generated sources
set(caw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/caw.pb.cc")
set(caw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/caw.pb.h")
set(caw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/caw.grpc.pb.cc")
set(caw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/caw.grpc.pb.h")

add_custom_command(
      OUTPUT "${caw_proto_srcs}" "${caw_proto_hdrs}" "${caw_grpc_srcs}" "${caw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${caw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${caw_proto}"
      DEPENDS "${caw_proto}")

# test caw functionality

add_executable(caw_test "caw_test.cc" ${caw_proto_srcs} ${caw_grpc_srcs} "caw.cc" "keyvaluestoreclass.cc")
target_link_libraries(caw_test GTest::GTest GTest::Main glog
${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF})
