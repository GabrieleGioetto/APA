# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/gabriele/Downloads/clion-2018.2.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/gabriele/Downloads/clion-2018.2.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ES1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ES1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ES1.dir/flags.make

CMakeFiles/ES1.dir/main.c.o: CMakeFiles/ES1.dir/flags.make
CMakeFiles/ES1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ES1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ES1.dir/main.c.o   -c /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/main.c

CMakeFiles/ES1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ES1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/main.c > CMakeFiles/ES1.dir/main.c.i

CMakeFiles/ES1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ES1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/main.c -o CMakeFiles/ES1.dir/main.c.s

# Object files for target ES1
ES1_OBJECTS = \
"CMakeFiles/ES1.dir/main.c.o"

# External object files for target ES1
ES1_EXTERNAL_OBJECTS =

ES1: CMakeFiles/ES1.dir/main.c.o
ES1: CMakeFiles/ES1.dir/build.make
ES1: CMakeFiles/ES1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ES1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ES1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ES1.dir/build: ES1

.PHONY : CMakeFiles/ES1.dir/build

CMakeFiles/ES1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ES1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ES1.dir/clean

CMakeFiles/ES1.dir/depend:
	cd /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02 /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02 /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug /home/gabriele/Desktop/Algoritmi/Esercizi/L09/E02/cmake-build-debug/CMakeFiles/ES1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ES1.dir/depend

