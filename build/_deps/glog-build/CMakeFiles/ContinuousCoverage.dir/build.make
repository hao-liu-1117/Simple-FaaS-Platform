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

# Utility rule file for ContinuousCoverage.

# Include the progress variables for this target.
include _deps/glog-build/CMakeFiles/ContinuousCoverage.dir/progress.make

_deps/glog-build/CMakeFiles/ContinuousCoverage:
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && /usr/bin/ctest -D ContinuousCoverage

ContinuousCoverage: _deps/glog-build/CMakeFiles/ContinuousCoverage
ContinuousCoverage: _deps/glog-build/CMakeFiles/ContinuousCoverage.dir/build.make

.PHONY : ContinuousCoverage

# Rule to build all files generated by this target.
_deps/glog-build/CMakeFiles/ContinuousCoverage.dir/build: ContinuousCoverage

.PHONY : _deps/glog-build/CMakeFiles/ContinuousCoverage.dir/build

_deps/glog-build/CMakeFiles/ContinuousCoverage.dir/clean:
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousCoverage.dir/cmake_clean.cmake
.PHONY : _deps/glog-build/CMakeFiles/ContinuousCoverage.dir/clean

_deps/glog-build/CMakeFiles/ContinuousCoverage.dir/depend:
	cd /home/haoliu/csci499/csci499_hao-liu-1117/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/haoliu/csci499/csci499_hao-liu-1117 /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-src /home/haoliu/csci499/csci499_hao-liu-1117/build /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build /home/haoliu/csci499/csci499_hao-liu-1117/build/_deps/glog-build/CMakeFiles/ContinuousCoverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/glog-build/CMakeFiles/ContinuousCoverage.dir/depend

