# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/haoliu/csci499/csci499_hao-liu-1117

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/haoliu/csci499/csci499_hao-liu-1117/build

# Include any dependencies generated for this target.
include src/CMakeFiles/kvstore_server.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/kvstore_server.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/kvstore_server.dir/flags.make

src/keyvaluestore.pb.cc: ../src/keyvaluestore.proto
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating keyvaluestore.pb.cc, keyvaluestore.pb.h, keyvaluestore.grpc.pb.cc, keyvaluestore.grpc.pb.h"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /home/haoliu/.local/bin/protoc-3.14.0.0 --grpc_out /home/haoliu/csci499/csci499_hao-liu-1117/build/src --cpp_out /home/haoliu/csci499/csci499_hao-liu-1117/build/src -I /home/haoliu/csci499/csci499_hao-liu-1117/src --plugin=protoc-gen-grpc="/home/haoliu/.local/bin/grpc_cpp_plugin" /home/haoliu/csci499/csci499_hao-liu-1117/src/keyvaluestore.proto

src/keyvaluestore.pb.h: src/keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/keyvaluestore.pb.h

src/keyvaluestore.grpc.pb.cc: src/keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/keyvaluestore.grpc.pb.cc

src/keyvaluestore.grpc.pb.h: src/keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E touch_nocreate src/keyvaluestore.grpc.pb.h

src/CMakeFiles/kvstore_server.dir/kvstore_server.cc.o: src/CMakeFiles/kvstore_server.dir/flags.make
src/CMakeFiles/kvstore_server.dir/kvstore_server.cc.o: ../src/kvstore_server.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/kvstore_server.dir/kvstore_server.cc.o"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kvstore_server.dir/kvstore_server.cc.o -c /home/haoliu/csci499/csci499_hao-liu-1117/src/kvstore_server.cc

src/CMakeFiles/kvstore_server.dir/kvstore_server.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kvstore_server.dir/kvstore_server.cc.i"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haoliu/csci499/csci499_hao-liu-1117/src/kvstore_server.cc > CMakeFiles/kvstore_server.dir/kvstore_server.cc.i

src/CMakeFiles/kvstore_server.dir/kvstore_server.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kvstore_server.dir/kvstore_server.cc.s"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haoliu/csci499/csci499_hao-liu-1117/src/kvstore_server.cc -o CMakeFiles/kvstore_server.dir/kvstore_server.cc.s

src/CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.o: src/CMakeFiles/kvstore_server.dir/flags.make
src/CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.o: src/keyvaluestore.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.o"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.o -c /home/haoliu/csci499/csci499_hao-liu-1117/build/src/keyvaluestore.pb.cc

src/CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.i"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haoliu/csci499/csci499_hao-liu-1117/build/src/keyvaluestore.pb.cc > CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.i

src/CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.s"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haoliu/csci499/csci499_hao-liu-1117/build/src/keyvaluestore.pb.cc -o CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.s

src/CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.o: src/CMakeFiles/kvstore_server.dir/flags.make
src/CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.o: src/keyvaluestore.grpc.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.o"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.o -c /home/haoliu/csci499/csci499_hao-liu-1117/build/src/keyvaluestore.grpc.pb.cc

src/CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.i"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haoliu/csci499/csci499_hao-liu-1117/build/src/keyvaluestore.grpc.pb.cc > CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.i

src/CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.s"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haoliu/csci499/csci499_hao-liu-1117/build/src/keyvaluestore.grpc.pb.cc -o CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.s

src/CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.o: src/CMakeFiles/kvstore_server.dir/flags.make
src/CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.o: ../src/keyvaluestoreclass.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.o"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.o -c /home/haoliu/csci499/csci499_hao-liu-1117/src/keyvaluestoreclass.cc

src/CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.i"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haoliu/csci499/csci499_hao-liu-1117/src/keyvaluestoreclass.cc > CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.i

src/CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.s"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haoliu/csci499/csci499_hao-liu-1117/src/keyvaluestoreclass.cc -o CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.s

# Object files for target kvstore_server
kvstore_server_OBJECTS = \
"CMakeFiles/kvstore_server.dir/kvstore_server.cc.o" \
"CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.o" \
"CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.o" \
"CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.o"

# External object files for target kvstore_server
kvstore_server_EXTERNAL_OBJECTS =

src/kvstore_server: src/CMakeFiles/kvstore_server.dir/kvstore_server.cc.o
src/kvstore_server: src/CMakeFiles/kvstore_server.dir/keyvaluestore.pb.cc.o
src/kvstore_server: src/CMakeFiles/kvstore_server.dir/keyvaluestore.grpc.pb.cc.o
src/kvstore_server: src/CMakeFiles/kvstore_server.dir/keyvaluestoreclass.cc.o
src/kvstore_server: src/CMakeFiles/kvstore_server.dir/build.make
src/kvstore_server: /home/haoliu/.local/lib/libgrpc++.a
src/kvstore_server: /home/haoliu/.local/lib/libprotobuf.a
src/kvstore_server: /home/haoliu/.local/lib/libgrpc.a
src/kvstore_server: /home/haoliu/.local/lib/libssl.a
src/kvstore_server: /home/haoliu/.local/lib/libcrypto.a
src/kvstore_server: /home/haoliu/.local/lib/libz.a
src/kvstore_server: /home/haoliu/.local/lib/libcares.a
src/kvstore_server: /home/haoliu/.local/lib/libre2.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_statusor.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_hash.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_bad_variant_access.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_city.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_raw_hash_set.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_hashtablez_sampler.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_exponential_biased.a
src/kvstore_server: /home/haoliu/.local/lib/libgpr.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_status.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_cord.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_bad_optional_access.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_synchronization.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_stacktrace.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_symbolize.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_debugging_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_demangle_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_graphcycles_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_time.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_civil_time.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_time_zone.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_malloc_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_str_format_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_strings.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_strings_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_int128.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_throw_delegate.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_base.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_raw_logging_internal.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_log_severity.a
src/kvstore_server: /home/haoliu/.local/lib/libabsl_spinlock_wait.a
src/kvstore_server: /home/haoliu/.local/lib/libaddress_sorting.a
src/kvstore_server: /home/haoliu/.local/lib/libupb.a
src/kvstore_server: src/CMakeFiles/kvstore_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable kvstore_server"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/kvstore_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/kvstore_server.dir/build: src/kvstore_server

.PHONY : src/CMakeFiles/kvstore_server.dir/build

src/CMakeFiles/kvstore_server.dir/clean:
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/src && $(CMAKE_COMMAND) -P CMakeFiles/kvstore_server.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/kvstore_server.dir/clean

src/CMakeFiles/kvstore_server.dir/depend: src/keyvaluestore.pb.cc
src/CMakeFiles/kvstore_server.dir/depend: src/keyvaluestore.pb.h
src/CMakeFiles/kvstore_server.dir/depend: src/keyvaluestore.grpc.pb.cc
src/CMakeFiles/kvstore_server.dir/depend: src/keyvaluestore.grpc.pb.h
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/haoliu/csci499/csci499_hao-liu-1117 /home/haoliu/csci499/csci499_hao-liu-1117/src /home/haoliu/csci499/csci499_hao-liu-1117/build /home/haoliu/csci499/csci499_hao-liu-1117/build/src /home/haoliu/csci499/csci499_hao-liu-1117/build/src/CMakeFiles/kvstore_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/kvstore_server.dir/depend

