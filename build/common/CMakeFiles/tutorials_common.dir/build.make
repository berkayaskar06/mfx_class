# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/cmake-3.23.0-rc3-linux-x86_64/bin/cmake

# The command to remove a file.
RM = /opt/cmake-3.23.0-rc3-linux-x86_64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/berkay/Desktop/main_msdk/mfx_decode_post_process

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build

# Include any dependencies generated for this target.
include common/CMakeFiles/tutorials_common.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include common/CMakeFiles/tutorials_common.dir/compiler_depend.make

# Include the progress variables for this target.
include common/CMakeFiles/tutorials_common.dir/progress.make

# Include the compile flags for this target's objects.
include common/CMakeFiles/tutorials_common.dir/flags.make

common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.o: common/CMakeFiles/tutorials_common.dir/flags.make
common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.o: ../common/cmd_options.cpp
common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.o: common/CMakeFiles/tutorials_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.o"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.o -MF CMakeFiles/tutorials_common.dir/cmd_options.cpp.o.d -o CMakeFiles/tutorials_common.dir/cmd_options.cpp.o -c /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/cmd_options.cpp

common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorials_common.dir/cmd_options.cpp.i"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/cmd_options.cpp > CMakeFiles/tutorials_common.dir/cmd_options.cpp.i

common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorials_common.dir/cmd_options.cpp.s"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/cmd_options.cpp -o CMakeFiles/tutorials_common.dir/cmd_options.cpp.s

common/CMakeFiles/tutorials_common.dir/common_utils.cpp.o: common/CMakeFiles/tutorials_common.dir/flags.make
common/CMakeFiles/tutorials_common.dir/common_utils.cpp.o: ../common/common_utils.cpp
common/CMakeFiles/tutorials_common.dir/common_utils.cpp.o: common/CMakeFiles/tutorials_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object common/CMakeFiles/tutorials_common.dir/common_utils.cpp.o"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/tutorials_common.dir/common_utils.cpp.o -MF CMakeFiles/tutorials_common.dir/common_utils.cpp.o.d -o CMakeFiles/tutorials_common.dir/common_utils.cpp.o -c /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_utils.cpp

common/CMakeFiles/tutorials_common.dir/common_utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorials_common.dir/common_utils.cpp.i"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_utils.cpp > CMakeFiles/tutorials_common.dir/common_utils.cpp.i

common/CMakeFiles/tutorials_common.dir/common_utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorials_common.dir/common_utils.cpp.s"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_utils.cpp -o CMakeFiles/tutorials_common.dir/common_utils.cpp.s

common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o: common/CMakeFiles/tutorials_common.dir/flags.make
common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o: ../common/common_utils_linux.cpp
common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o: common/CMakeFiles/tutorials_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o -MF CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o.d -o CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o -c /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_utils_linux.cpp

common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.i"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_utils_linux.cpp > CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.i

common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.s"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_utils_linux.cpp -o CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.s

common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o: common/CMakeFiles/tutorials_common.dir/flags.make
common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o: ../common/common_vaapi.cpp
common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o: common/CMakeFiles/tutorials_common.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o -MF CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o.d -o CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o -c /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_vaapi.cpp

common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tutorials_common.dir/common_vaapi.cpp.i"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_vaapi.cpp > CMakeFiles/tutorials_common.dir/common_vaapi.cpp.i

common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tutorials_common.dir/common_vaapi.cpp.s"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common/common_vaapi.cpp -o CMakeFiles/tutorials_common.dir/common_vaapi.cpp.s

# Object files for target tutorials_common
tutorials_common_OBJECTS = \
"CMakeFiles/tutorials_common.dir/cmd_options.cpp.o" \
"CMakeFiles/tutorials_common.dir/common_utils.cpp.o" \
"CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o" \
"CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o"

# External object files for target tutorials_common
tutorials_common_EXTERNAL_OBJECTS =

__lib/release/libtutorials_common.a: common/CMakeFiles/tutorials_common.dir/cmd_options.cpp.o
__lib/release/libtutorials_common.a: common/CMakeFiles/tutorials_common.dir/common_utils.cpp.o
__lib/release/libtutorials_common.a: common/CMakeFiles/tutorials_common.dir/common_utils_linux.cpp.o
__lib/release/libtutorials_common.a: common/CMakeFiles/tutorials_common.dir/common_vaapi.cpp.o
__lib/release/libtutorials_common.a: common/CMakeFiles/tutorials_common.dir/build.make
__lib/release/libtutorials_common.a: common/CMakeFiles/tutorials_common.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../__lib/release/libtutorials_common.a"
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && $(CMAKE_COMMAND) -P CMakeFiles/tutorials_common.dir/cmake_clean_target.cmake
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tutorials_common.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
common/CMakeFiles/tutorials_common.dir/build: __lib/release/libtutorials_common.a
.PHONY : common/CMakeFiles/tutorials_common.dir/build

common/CMakeFiles/tutorials_common.dir/clean:
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common && $(CMAKE_COMMAND) -P CMakeFiles/tutorials_common.dir/cmake_clean.cmake
.PHONY : common/CMakeFiles/tutorials_common.dir/clean

common/CMakeFiles/tutorials_common.dir/depend:
	cd /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/berkay/Desktop/main_msdk/mfx_decode_post_process /home/berkay/Desktop/main_msdk/mfx_decode_post_process/common /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common /home/berkay/Desktop/main_msdk/mfx_decode_post_process/build/common/CMakeFiles/tutorials_common.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : common/CMakeFiles/tutorials_common.dir/depend
