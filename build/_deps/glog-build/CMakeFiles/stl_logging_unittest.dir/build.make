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
include _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/depend.make

# Include the progress variables for this target.
include _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/progress.make

# Include the compile flags for this target's objects.
include _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/flags.make

_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.o: _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/flags.make
_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.o: _deps/glog-src/src/stl_logging_unittest.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.o"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.o -c /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-src/src/stl_logging_unittest.cc

_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.i"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-src/src/stl_logging_unittest.cc > CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.i

_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.s"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-src/src/stl_logging_unittest.cc -o CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.s

# Object files for target stl_logging_unittest
stl_logging_unittest_OBJECTS = \
"CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.o"

# External object files for target stl_logging_unittest
stl_logging_unittest_EXTERNAL_OBJECTS =

_deps/glog-build/stl_logging_unittest: _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/src/stl_logging_unittest.cc.o
_deps/glog-build/stl_logging_unittest: _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/build.make
_deps/glog-build/stl_logging_unittest: _deps/glog-build/libglog.a
_deps/glog-build/stl_logging_unittest: /usr/lib/x86_64-linux-gnu/libgflags.so.2.2.2
_deps/glog-build/stl_logging_unittest: _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/haoliu/csci499/csci499_hao-liu-1117/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable stl_logging_unittest"
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stl_logging_unittest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/build: _deps/glog-build/stl_logging_unittest

.PHONY : _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/build

_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/clean:
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && $(CMAKE_COMMAND) -P CMakeFiles/stl_logging_unittest.dir/cmake_clean.cmake
.PHONY : _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/clean

_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/depend:
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/haoliu/csci499/csci499_hao-liu-1117 /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-src /home/haoliu/csci499/csci499_hao-liu-1117/build /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build/CMakeFiles/stl_logging_unittest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/glog-build/CMakeFiles/stl_logging_unittest.dir/depend

