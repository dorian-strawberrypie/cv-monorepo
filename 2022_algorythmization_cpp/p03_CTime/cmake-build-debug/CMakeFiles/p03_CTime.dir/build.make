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
CMAKE_SOURCE_DIR = /home/dorian_ubuntu/Documents/PA2/p03_CTime

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/p03_CTime.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/p03_CTime.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/p03_CTime.dir/flags.make

CMakeFiles/p03_CTime.dir/main.cpp.o: CMakeFiles/p03_CTime.dir/flags.make
CMakeFiles/p03_CTime.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/p03_CTime.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/p03_CTime.dir/main.cpp.o -c /home/dorian_ubuntu/Documents/PA2/p03_CTime/main.cpp

CMakeFiles/p03_CTime.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/p03_CTime.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dorian_ubuntu/Documents/PA2/p03_CTime/main.cpp > CMakeFiles/p03_CTime.dir/main.cpp.i

CMakeFiles/p03_CTime.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/p03_CTime.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dorian_ubuntu/Documents/PA2/p03_CTime/main.cpp -o CMakeFiles/p03_CTime.dir/main.cpp.s

# Object files for target p03_CTime
p03_CTime_OBJECTS = \
"CMakeFiles/p03_CTime.dir/main.cpp.o"

# External object files for target p03_CTime
p03_CTime_EXTERNAL_OBJECTS =

p03_CTime: CMakeFiles/p03_CTime.dir/main.cpp.o
p03_CTime: CMakeFiles/p03_CTime.dir/build.make
p03_CTime: CMakeFiles/p03_CTime.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable p03_CTime"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/p03_CTime.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/p03_CTime.dir/build: p03_CTime

.PHONY : CMakeFiles/p03_CTime.dir/build

CMakeFiles/p03_CTime.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/p03_CTime.dir/cmake_clean.cmake
.PHONY : CMakeFiles/p03_CTime.dir/clean

CMakeFiles/p03_CTime.dir/depend:
	cd /home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dorian_ubuntu/Documents/PA2/p03_CTime /home/dorian_ubuntu/Documents/PA2/p03_CTime /home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug /home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug /home/dorian_ubuntu/Documents/PA2/p03_CTime/cmake-build-debug/CMakeFiles/p03_CTime.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/p03_CTime.dir/depend

