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
CMAKE_SOURCE_DIR = /home/martina9/senior-project/Senior-Project-Individual/first-game

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/martina9/senior-project/Senior-Project-Individual/first-game/build

# Include any dependencies generated for this target.
include CMakeFiles/template_cpp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/template_cpp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/template_cpp.dir/flags.make

CMakeFiles/template_cpp.dir/main.c.o: CMakeFiles/template_cpp.dir/flags.make
CMakeFiles/template_cpp.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/martina9/senior-project/Senior-Project-Individual/first-game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/template_cpp.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/template_cpp.dir/main.c.o   -c /home/martina9/senior-project/Senior-Project-Individual/first-game/main.c

CMakeFiles/template_cpp.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/template_cpp.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/martina9/senior-project/Senior-Project-Individual/first-game/main.c > CMakeFiles/template_cpp.dir/main.c.i

CMakeFiles/template_cpp.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/template_cpp.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/martina9/senior-project/Senior-Project-Individual/first-game/main.c -o CMakeFiles/template_cpp.dir/main.c.s

# Object files for target template_cpp
template_cpp_OBJECTS = \
"CMakeFiles/template_cpp.dir/main.c.o"

# External object files for target template_cpp
template_cpp_EXTERNAL_OBJECTS =

template_cpp: CMakeFiles/template_cpp.dir/main.c.o
template_cpp: CMakeFiles/template_cpp.dir/build.make
template_cpp: raylib/raylib/libraylib.a
template_cpp: /usr/lib/x86_64-linux-gnu/libOpenGL.so
template_cpp: /usr/lib/x86_64-linux-gnu/libGLX.so
template_cpp: /usr/lib/x86_64-linux-gnu/libGLU.so
template_cpp: /usr/lib/x86_64-linux-gnu/librt.so
template_cpp: /usr/lib/x86_64-linux-gnu/libm.so
template_cpp: CMakeFiles/template_cpp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/martina9/senior-project/Senior-Project-Individual/first-game/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable template_cpp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/template_cpp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/template_cpp.dir/build: template_cpp

.PHONY : CMakeFiles/template_cpp.dir/build

CMakeFiles/template_cpp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/template_cpp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/template_cpp.dir/clean

CMakeFiles/template_cpp.dir/depend:
	cd /home/martina9/senior-project/Senior-Project-Individual/first-game/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/martina9/senior-project/Senior-Project-Individual/first-game /home/martina9/senior-project/Senior-Project-Individual/first-game /home/martina9/senior-project/Senior-Project-Individual/first-game/build /home/martina9/senior-project/Senior-Project-Individual/first-game/build /home/martina9/senior-project/Senior-Project-Individual/first-game/build/CMakeFiles/template_cpp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/template_cpp.dir/depend

