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
CMAKE_SOURCE_DIR = /home/kadyrov_suleyman/tp-cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kadyrov_suleyman/tp-cpp/CMakeBuilding

# Include any dependencies generated for this target.
include project/test/CMakeFiles/mytest.dir/depend.make

# Include the progress variables for this target.
include project/test/CMakeFiles/mytest.dir/progress.make

# Include the compile flags for this target's objects.
include project/test/CMakeFiles/mytest.dir/flags.make

project/test/CMakeFiles/mytest.dir/src/test.cpp.o: project/test/CMakeFiles/mytest.dir/flags.make
project/test/CMakeFiles/mytest.dir/src/test.cpp.o: ../project/test/src/test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kadyrov_suleyman/tp-cpp/CMakeBuilding/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object project/test/CMakeFiles/mytest.dir/src/test.cpp.o"
	cd /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mytest.dir/src/test.cpp.o -c /home/kadyrov_suleyman/tp-cpp/project/test/src/test.cpp

project/test/CMakeFiles/mytest.dir/src/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mytest.dir/src/test.cpp.i"
	cd /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kadyrov_suleyman/tp-cpp/project/test/src/test.cpp > CMakeFiles/mytest.dir/src/test.cpp.i

project/test/CMakeFiles/mytest.dir/src/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mytest.dir/src/test.cpp.s"
	cd /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kadyrov_suleyman/tp-cpp/project/test/src/test.cpp -o CMakeFiles/mytest.dir/src/test.cpp.s

# Object files for target mytest
mytest_OBJECTS = \
"CMakeFiles/mytest.dir/src/test.cpp.o"

# External object files for target mytest
mytest_EXTERNAL_OBJECTS =

project/test/mytest: project/test/CMakeFiles/mytest.dir/src/test.cpp.o
project/test/mytest: project/test/CMakeFiles/mytest.dir/build.make
project/test/mytest: project/libparcer_in_series.a
project/test/mytest: project/libparcer_in_parallel.so
project/test/mytest: lib/libgtest.a
project/test/mytest: project/test/CMakeFiles/mytest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kadyrov_suleyman/tp-cpp/CMakeBuilding/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mytest"
	cd /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mytest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
project/test/CMakeFiles/mytest.dir/build: project/test/mytest

.PHONY : project/test/CMakeFiles/mytest.dir/build

project/test/CMakeFiles/mytest.dir/clean:
	cd /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test && $(CMAKE_COMMAND) -P CMakeFiles/mytest.dir/cmake_clean.cmake
.PHONY : project/test/CMakeFiles/mytest.dir/clean

project/test/CMakeFiles/mytest.dir/depend:
	cd /home/kadyrov_suleyman/tp-cpp/CMakeBuilding && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kadyrov_suleyman/tp-cpp /home/kadyrov_suleyman/tp-cpp/project/test /home/kadyrov_suleyman/tp-cpp/CMakeBuilding /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test /home/kadyrov_suleyman/tp-cpp/CMakeBuilding/project/test/CMakeFiles/mytest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : project/test/CMakeFiles/mytest.dir/depend

