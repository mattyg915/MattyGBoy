# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/MattyG/Documents/Programming/MattyGBoy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MattyGBoy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MattyGBoy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MattyGBoy.dir/flags.make

CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.o: ../src/bit_rotate_shift_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/bit_rotate_shift_instructions.c

CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/bit_rotate_shift_instructions.c > CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.i

CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/bit_rotate_shift_instructions.c -o CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.s

CMakeFiles/MattyGBoy.dir/src/control_instructions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/control_instructions.c.o: ../src/control_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/MattyGBoy.dir/src/control_instructions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/control_instructions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/control_instructions.c

CMakeFiles/MattyGBoy.dir/src/control_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/control_instructions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/control_instructions.c > CMakeFiles/MattyGBoy.dir/src/control_instructions.c.i

CMakeFiles/MattyGBoy.dir/src/control_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/control_instructions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/control_instructions.c -o CMakeFiles/MattyGBoy.dir/src/control_instructions.c.s

CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.o: ../src/cpu_control_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/cpu_control_instructions.c

CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/cpu_control_instructions.c > CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.i

CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/cpu_control_instructions.c -o CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.s

CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.o: ../src/cpu_emulator.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/cpu_emulator.c

CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/cpu_emulator.c > CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.i

CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/cpu_emulator.c -o CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.s

CMakeFiles/MattyGBoy.dir/src/graphics.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/graphics.c.o: ../src/graphics.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/MattyGBoy.dir/src/graphics.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/graphics.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/graphics.c

CMakeFiles/MattyGBoy.dir/src/graphics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/graphics.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/graphics.c > CMakeFiles/MattyGBoy.dir/src/graphics.c.i

CMakeFiles/MattyGBoy.dir/src/graphics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/graphics.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/graphics.c -o CMakeFiles/MattyGBoy.dir/src/graphics.c.s

CMakeFiles/MattyGBoy.dir/src/helper_functions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/helper_functions.c.o: ../src/helper_functions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/MattyGBoy.dir/src/helper_functions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/helper_functions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/helper_functions.c

CMakeFiles/MattyGBoy.dir/src/helper_functions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/helper_functions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/helper_functions.c > CMakeFiles/MattyGBoy.dir/src/helper_functions.c.i

CMakeFiles/MattyGBoy.dir/src/helper_functions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/helper_functions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/helper_functions.c -o CMakeFiles/MattyGBoy.dir/src/helper_functions.c.s

CMakeFiles/MattyGBoy.dir/src/load_instructions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/load_instructions.c.o: ../src/load_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/MattyGBoy.dir/src/load_instructions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/load_instructions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/load_instructions.c

CMakeFiles/MattyGBoy.dir/src/load_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/load_instructions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/load_instructions.c > CMakeFiles/MattyGBoy.dir/src/load_instructions.c.i

CMakeFiles/MattyGBoy.dir/src/load_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/load_instructions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/load_instructions.c -o CMakeFiles/MattyGBoy.dir/src/load_instructions.c.s

CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.o: ../src/logical_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/logical_instructions.c

CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/logical_instructions.c > CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.i

CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/logical_instructions.c -o CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.s

CMakeFiles/MattyGBoy.dir/src/math_instructions.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/math_instructions.c.o: ../src/math_instructions.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/MattyGBoy.dir/src/math_instructions.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/math_instructions.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/math_instructions.c

CMakeFiles/MattyGBoy.dir/src/math_instructions.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/math_instructions.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/math_instructions.c > CMakeFiles/MattyGBoy.dir/src/math_instructions.c.i

CMakeFiles/MattyGBoy.dir/src/math_instructions.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/math_instructions.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/math_instructions.c -o CMakeFiles/MattyGBoy.dir/src/math_instructions.c.s

CMakeFiles/MattyGBoy.dir/src/mattygboy.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/mattygboy.c.o: ../src/mattygboy.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/MattyGBoy.dir/src/mattygboy.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/mattygboy.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/mattygboy.c

CMakeFiles/MattyGBoy.dir/src/mattygboy.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/mattygboy.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/mattygboy.c > CMakeFiles/MattyGBoy.dir/src/mattygboy.c.i

CMakeFiles/MattyGBoy.dir/src/mattygboy.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/mattygboy.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/mattygboy.c -o CMakeFiles/MattyGBoy.dir/src/mattygboy.c.s

CMakeFiles/MattyGBoy.dir/src/memory.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/memory.c.o: ../src/memory.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object CMakeFiles/MattyGBoy.dir/src/memory.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/memory.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/memory.c

CMakeFiles/MattyGBoy.dir/src/memory.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/memory.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/memory.c > CMakeFiles/MattyGBoy.dir/src/memory.c.i

CMakeFiles/MattyGBoy.dir/src/memory.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/memory.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/memory.c -o CMakeFiles/MattyGBoy.dir/src/memory.c.s

CMakeFiles/MattyGBoy.dir/src/register_structures.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/register_structures.c.o: ../src/register_structures.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object CMakeFiles/MattyGBoy.dir/src/register_structures.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/register_structures.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/register_structures.c

CMakeFiles/MattyGBoy.dir/src/register_structures.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/register_structures.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/register_structures.c > CMakeFiles/MattyGBoy.dir/src/register_structures.c.i

CMakeFiles/MattyGBoy.dir/src/register_structures.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/register_structures.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/register_structures.c -o CMakeFiles/MattyGBoy.dir/src/register_structures.c.s

CMakeFiles/MattyGBoy.dir/src/timers.c.o: CMakeFiles/MattyGBoy.dir/flags.make
CMakeFiles/MattyGBoy.dir/src/timers.c.o: ../src/timers.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object CMakeFiles/MattyGBoy.dir/src/timers.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MattyGBoy.dir/src/timers.c.o   -c /Users/MattyG/Documents/Programming/MattyGBoy/src/timers.c

CMakeFiles/MattyGBoy.dir/src/timers.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MattyGBoy.dir/src/timers.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/MattyG/Documents/Programming/MattyGBoy/src/timers.c > CMakeFiles/MattyGBoy.dir/src/timers.c.i

CMakeFiles/MattyGBoy.dir/src/timers.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MattyGBoy.dir/src/timers.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/MattyG/Documents/Programming/MattyGBoy/src/timers.c -o CMakeFiles/MattyGBoy.dir/src/timers.c.s

# Object files for target MattyGBoy
MattyGBoy_OBJECTS = \
"CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/control_instructions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.o" \
"CMakeFiles/MattyGBoy.dir/src/graphics.c.o" \
"CMakeFiles/MattyGBoy.dir/src/helper_functions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/load_instructions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/math_instructions.c.o" \
"CMakeFiles/MattyGBoy.dir/src/mattygboy.c.o" \
"CMakeFiles/MattyGBoy.dir/src/memory.c.o" \
"CMakeFiles/MattyGBoy.dir/src/register_structures.c.o" \
"CMakeFiles/MattyGBoy.dir/src/timers.c.o"

# External object files for target MattyGBoy
MattyGBoy_EXTERNAL_OBJECTS =

MattyGBoy: CMakeFiles/MattyGBoy.dir/src/bit_rotate_shift_instructions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/control_instructions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/cpu_control_instructions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/cpu_emulator.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/graphics.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/helper_functions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/load_instructions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/logical_instructions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/math_instructions.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/mattygboy.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/memory.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/register_structures.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/src/timers.c.o
MattyGBoy: CMakeFiles/MattyGBoy.dir/build.make
MattyGBoy: CMakeFiles/MattyGBoy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C executable MattyGBoy"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MattyGBoy.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MattyGBoy.dir/build: MattyGBoy

.PHONY : CMakeFiles/MattyGBoy.dir/build

CMakeFiles/MattyGBoy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MattyGBoy.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MattyGBoy.dir/clean

CMakeFiles/MattyGBoy.dir/depend:
	cd /Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/MattyG/Documents/Programming/MattyGBoy /Users/MattyG/Documents/Programming/MattyGBoy /Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug /Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug /Users/MattyG/Documents/Programming/MattyGBoy/cmake-build-debug/CMakeFiles/MattyGBoy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MattyGBoy.dir/depend

