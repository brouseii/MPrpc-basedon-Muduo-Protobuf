# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
CMAKE_COMMAND = /usr/bin/cmake3

# The command to remove a file.
RM = /usr/bin/cmake3 -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/learning_test_programm/MPRPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/learning_test_programm/MPRPC/build

# Include any dependencies generated for this target.
include example/callee/CMakeFiles/provider.dir/depend.make

# Include the progress variables for this target.
include example/callee/CMakeFiles/provider.dir/progress.make

# Include the compile flags for this target's objects.
include example/callee/CMakeFiles/provider.dir/flags.make

example/callee/CMakeFiles/provider.dir/FriendService.cpp.o: example/callee/CMakeFiles/provider.dir/flags.make
example/callee/CMakeFiles/provider.dir/FriendService.cpp.o: ../example/callee/FriendService.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/callee/CMakeFiles/provider.dir/FriendService.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/example/callee && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/provider.dir/FriendService.cpp.o -c /home/learning_test_programm/MPRPC/example/callee/FriendService.cpp

example/callee/CMakeFiles/provider.dir/FriendService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/provider.dir/FriendService.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/example/callee && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/example/callee/FriendService.cpp > CMakeFiles/provider.dir/FriendService.cpp.i

example/callee/CMakeFiles/provider.dir/FriendService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/provider.dir/FriendService.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/example/callee && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/example/callee/FriendService.cpp -o CMakeFiles/provider.dir/FriendService.cpp.s

# Object files for target provider
provider_OBJECTS = \
"CMakeFiles/provider.dir/FriendService.cpp.o"

# External object files for target provider
provider_EXTERNAL_OBJECTS =

../bin/provider: example/callee/CMakeFiles/provider.dir/FriendService.cpp.o
../bin/provider: example/callee/CMakeFiles/provider.dir/build.make
../bin/provider: ../lib/libmprpc.a
../bin/provider: example/callee/CMakeFiles/provider.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/provider"
	cd /home/learning_test_programm/MPRPC/build/example/callee && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/provider.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/callee/CMakeFiles/provider.dir/build: ../bin/provider

.PHONY : example/callee/CMakeFiles/provider.dir/build

example/callee/CMakeFiles/provider.dir/clean:
	cd /home/learning_test_programm/MPRPC/build/example/callee && $(CMAKE_COMMAND) -P CMakeFiles/provider.dir/cmake_clean.cmake
.PHONY : example/callee/CMakeFiles/provider.dir/clean

example/callee/CMakeFiles/provider.dir/depend:
	cd /home/learning_test_programm/MPRPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/learning_test_programm/MPRPC /home/learning_test_programm/MPRPC/example/callee /home/learning_test_programm/MPRPC/build /home/learning_test_programm/MPRPC/build/example/callee /home/learning_test_programm/MPRPC/build/example/callee/CMakeFiles/provider.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/callee/CMakeFiles/provider.dir/depend

