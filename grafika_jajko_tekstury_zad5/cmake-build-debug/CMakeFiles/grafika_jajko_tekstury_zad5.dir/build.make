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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/grafika_jajko_tekstury_zad5.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/grafika_jajko_tekstury_zad5.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/grafika_jajko_tekstury_zad5.dir/flags.make

CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.o: CMakeFiles/grafika_jajko_tekstury_zad5.dir/flags.make
CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.o -c /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/main.cpp

CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/main.cpp > CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.i

CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/main.cpp -o CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.s

# Object files for target grafika_jajko_tekstury_zad5
grafika_jajko_tekstury_zad5_OBJECTS = \
"CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.o"

# External object files for target grafika_jajko_tekstury_zad5
grafika_jajko_tekstury_zad5_EXTERNAL_OBJECTS =

grafika_jajko_tekstury_zad5: CMakeFiles/grafika_jajko_tekstury_zad5.dir/main.cpp.o
grafika_jajko_tekstury_zad5: CMakeFiles/grafika_jajko_tekstury_zad5.dir/build.make
grafika_jajko_tekstury_zad5: CMakeFiles/grafika_jajko_tekstury_zad5.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable grafika_jajko_tekstury_zad5"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/grafika_jajko_tekstury_zad5.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/grafika_jajko_tekstury_zad5.dir/build: grafika_jajko_tekstury_zad5

.PHONY : CMakeFiles/grafika_jajko_tekstury_zad5.dir/build

CMakeFiles/grafika_jajko_tekstury_zad5.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/grafika_jajko_tekstury_zad5.dir/cmake_clean.cmake
.PHONY : CMakeFiles/grafika_jajko_tekstury_zad5.dir/clean

CMakeFiles/grafika_jajko_tekstury_zad5.dir/depend:
	cd /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5 /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5 /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug /home/kamil/CLionProjects/grafika_jajko_tekstury_zad5/cmake-build-debug/CMakeFiles/grafika_jajko_tekstury_zad5.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/grafika_jajko_tekstury_zad5.dir/depend

