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
include src/CMakeFiles/mprpc.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/mprpc.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/mprpc.dir/flags.make

src/CMakeFiles/mprpc.dir/Logger.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/Logger.cpp.o: ../src/Logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/mprpc.dir/Logger.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/Logger.cpp.o -c /home/learning_test_programm/MPRPC/src/Logger.cpp

src/CMakeFiles/mprpc.dir/Logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/Logger.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/Logger.cpp > CMakeFiles/mprpc.dir/Logger.cpp.i

src/CMakeFiles/mprpc.dir/Logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/Logger.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/Logger.cpp -o CMakeFiles/mprpc.dir/Logger.cpp.s

src/CMakeFiles/mprpc.dir/MPRpcProvider.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/MPRpcProvider.cpp.o: ../src/MPRpcProvider.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/mprpc.dir/MPRpcProvider.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/MPRpcProvider.cpp.o -c /home/learning_test_programm/MPRPC/src/MPRpcProvider.cpp

src/CMakeFiles/mprpc.dir/MPRpcProvider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/MPRpcProvider.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/MPRpcProvider.cpp > CMakeFiles/mprpc.dir/MPRpcProvider.cpp.i

src/CMakeFiles/mprpc.dir/MPRpcProvider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/MPRpcProvider.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/MPRpcProvider.cpp -o CMakeFiles/mprpc.dir/MPRpcProvider.cpp.s

src/CMakeFiles/mprpc.dir/MPrpcApplication.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/MPrpcApplication.cpp.o: ../src/MPrpcApplication.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/mprpc.dir/MPrpcApplication.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/MPrpcApplication.cpp.o -c /home/learning_test_programm/MPRPC/src/MPrpcApplication.cpp

src/CMakeFiles/mprpc.dir/MPrpcApplication.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/MPrpcApplication.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/MPrpcApplication.cpp > CMakeFiles/mprpc.dir/MPrpcApplication.cpp.i

src/CMakeFiles/mprpc.dir/MPrpcApplication.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/MPrpcApplication.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/MPrpcApplication.cpp -o CMakeFiles/mprpc.dir/MPrpcApplication.cpp.s

src/CMakeFiles/mprpc.dir/MPrpcChannel.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/MPrpcChannel.cpp.o: ../src/MPrpcChannel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/mprpc.dir/MPrpcChannel.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/MPrpcChannel.cpp.o -c /home/learning_test_programm/MPRPC/src/MPrpcChannel.cpp

src/CMakeFiles/mprpc.dir/MPrpcChannel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/MPrpcChannel.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/MPrpcChannel.cpp > CMakeFiles/mprpc.dir/MPrpcChannel.cpp.i

src/CMakeFiles/mprpc.dir/MPrpcChannel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/MPrpcChannel.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/MPrpcChannel.cpp -o CMakeFiles/mprpc.dir/MPrpcChannel.cpp.s

src/CMakeFiles/mprpc.dir/MPrpcConfig.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/MPrpcConfig.cpp.o: ../src/MPrpcConfig.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/mprpc.dir/MPrpcConfig.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/MPrpcConfig.cpp.o -c /home/learning_test_programm/MPRPC/src/MPrpcConfig.cpp

src/CMakeFiles/mprpc.dir/MPrpcConfig.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/MPrpcConfig.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/MPrpcConfig.cpp > CMakeFiles/mprpc.dir/MPrpcConfig.cpp.i

src/CMakeFiles/mprpc.dir/MPrpcConfig.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/MPrpcConfig.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/MPrpcConfig.cpp -o CMakeFiles/mprpc.dir/MPrpcConfig.cpp.s

src/CMakeFiles/mprpc.dir/MPrpcController.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/MPrpcController.cpp.o: ../src/MPrpcController.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/mprpc.dir/MPrpcController.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/MPrpcController.cpp.o -c /home/learning_test_programm/MPRPC/src/MPrpcController.cpp

src/CMakeFiles/mprpc.dir/MPrpcController.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/MPrpcController.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/MPrpcController.cpp > CMakeFiles/mprpc.dir/MPrpcController.cpp.i

src/CMakeFiles/mprpc.dir/MPrpcController.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/MPrpcController.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/MPrpcController.cpp -o CMakeFiles/mprpc.dir/MPrpcController.cpp.s

src/CMakeFiles/mprpc.dir/RpcHeader.pb.cc.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/RpcHeader.pb.cc.o: ../src/RpcHeader.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/mprpc.dir/RpcHeader.pb.cc.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/RpcHeader.pb.cc.o -c /home/learning_test_programm/MPRPC/src/RpcHeader.pb.cc

src/CMakeFiles/mprpc.dir/RpcHeader.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/RpcHeader.pb.cc.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/RpcHeader.pb.cc > CMakeFiles/mprpc.dir/RpcHeader.pb.cc.i

src/CMakeFiles/mprpc.dir/RpcHeader.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/RpcHeader.pb.cc.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/RpcHeader.pb.cc -o CMakeFiles/mprpc.dir/RpcHeader.pb.cc.s

src/CMakeFiles/mprpc.dir/ZookeeperClient.cpp.o: src/CMakeFiles/mprpc.dir/flags.make
src/CMakeFiles/mprpc.dir/ZookeeperClient.cpp.o: ../src/ZookeeperClient.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/mprpc.dir/ZookeeperClient.cpp.o"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mprpc.dir/ZookeeperClient.cpp.o -c /home/learning_test_programm/MPRPC/src/ZookeeperClient.cpp

src/CMakeFiles/mprpc.dir/ZookeeperClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mprpc.dir/ZookeeperClient.cpp.i"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/learning_test_programm/MPRPC/src/ZookeeperClient.cpp > CMakeFiles/mprpc.dir/ZookeeperClient.cpp.i

src/CMakeFiles/mprpc.dir/ZookeeperClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mprpc.dir/ZookeeperClient.cpp.s"
	cd /home/learning_test_programm/MPRPC/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/learning_test_programm/MPRPC/src/ZookeeperClient.cpp -o CMakeFiles/mprpc.dir/ZookeeperClient.cpp.s

# Object files for target mprpc
mprpc_OBJECTS = \
"CMakeFiles/mprpc.dir/Logger.cpp.o" \
"CMakeFiles/mprpc.dir/MPRpcProvider.cpp.o" \
"CMakeFiles/mprpc.dir/MPrpcApplication.cpp.o" \
"CMakeFiles/mprpc.dir/MPrpcChannel.cpp.o" \
"CMakeFiles/mprpc.dir/MPrpcConfig.cpp.o" \
"CMakeFiles/mprpc.dir/MPrpcController.cpp.o" \
"CMakeFiles/mprpc.dir/RpcHeader.pb.cc.o" \
"CMakeFiles/mprpc.dir/ZookeeperClient.cpp.o"

# External object files for target mprpc
mprpc_EXTERNAL_OBJECTS =

../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/Logger.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/MPRpcProvider.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/MPrpcApplication.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/MPrpcChannel.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/MPrpcConfig.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/MPrpcController.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/RpcHeader.pb.cc.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/ZookeeperClient.cpp.o
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/build.make
../lib/libmprpc.a: src/CMakeFiles/mprpc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/learning_test_programm/MPRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX static library ../../lib/libmprpc.a"
	cd /home/learning_test_programm/MPRPC/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mprpc.dir/cmake_clean_target.cmake
	cd /home/learning_test_programm/MPRPC/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mprpc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/mprpc.dir/build: ../lib/libmprpc.a

.PHONY : src/CMakeFiles/mprpc.dir/build

src/CMakeFiles/mprpc.dir/clean:
	cd /home/learning_test_programm/MPRPC/build/src && $(CMAKE_COMMAND) -P CMakeFiles/mprpc.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/mprpc.dir/clean

src/CMakeFiles/mprpc.dir/depend:
	cd /home/learning_test_programm/MPRPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/learning_test_programm/MPRPC /home/learning_test_programm/MPRPC/src /home/learning_test_programm/MPRPC/build /home/learning_test_programm/MPRPC/build/src /home/learning_test_programm/MPRPC/build/src/CMakeFiles/mprpc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/mprpc.dir/depend
