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
CMAKE_COMMAND = /opt/clion/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/sf_Dante/PROJEKT_GRA/serwer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/serwer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/serwer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/serwer.dir/flags.make

CMakeFiles/serwer.dir/main.c.o: CMakeFiles/serwer.dir/flags.make
CMakeFiles/serwer.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/serwer.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serwer.dir/main.c.o   -c /media/sf_Dante/PROJEKT_GRA/serwer/main.c

CMakeFiles/serwer.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serwer.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/sf_Dante/PROJEKT_GRA/serwer/main.c > CMakeFiles/serwer.dir/main.c.i

CMakeFiles/serwer.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serwer.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/sf_Dante/PROJEKT_GRA/serwer/main.c -o CMakeFiles/serwer.dir/main.c.s

CMakeFiles/serwer.dir/function.c.o: CMakeFiles/serwer.dir/flags.make
CMakeFiles/serwer.dir/function.c.o: function.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/serwer.dir/function.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/serwer.dir/function.c.o   -c /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/function.c

CMakeFiles/serwer.dir/function.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/serwer.dir/function.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/function.c > CMakeFiles/serwer.dir/function.c.i

CMakeFiles/serwer.dir/function.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/serwer.dir/function.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/function.c -o CMakeFiles/serwer.dir/function.c.s

# Object files for target serwer
serwer_OBJECTS = \
"CMakeFiles/serwer.dir/main.c.o" \
"CMakeFiles/serwer.dir/function.c.o"

# External object files for target serwer
serwer_EXTERNAL_OBJECTS =

serwer: CMakeFiles/serwer.dir/main.c.o
serwer: CMakeFiles/serwer.dir/function.c.o
serwer: CMakeFiles/serwer.dir/build.make
serwer: CMakeFiles/serwer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable serwer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/serwer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/serwer.dir/build: serwer

.PHONY : CMakeFiles/serwer.dir/build

CMakeFiles/serwer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/serwer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/serwer.dir/clean

CMakeFiles/serwer.dir/depend:
	cd /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/sf_Dante/PROJEKT_GRA/serwer /media/sf_Dante/PROJEKT_GRA/serwer /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug /media/sf_Dante/PROJEKT_GRA/serwer/cmake-build-debug/CMakeFiles/serwer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/serwer.dir/depend

