cmake_minimum_required(VERSION 3.14)
project(MattyGBoy)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(MattyGBoy
        include/bit_rotate_shift_instructions.h
        include/control_instructions.h
        include/cpu_control_instructions.h
        include/cpu_emulator.h
        include/global_declarations.h
        include/graphics.h
        include/helper_functions.h
        include/load_instructions.h
        include/logical_instructions.h
        include/math_instructions.h
        include/memory.h
        include/register_structures.h
        include/timers.h
        src/bit_rotate_shift_instructions.c
        src/control_instructions.c
        src/cpu_control_instructions.c
        src/cpu_emulator.c
        src/graphics.c
        src/helper_functions.c
        src/load_instructions.c
        src/logical_instructions.c
        src/math_instructions.c
        src/mattygboy.c
        src/memory.c
        src/register_structures.c
        src/timers.c
        testFiles/add_tests.txt
        testFiles/control_tests.txt
        testFiles/sub_tests.txt
        mattyGboy.gitignore
        README.md)
