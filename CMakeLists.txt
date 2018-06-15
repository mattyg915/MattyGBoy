cmake_minimum_required(VERSION 3.9)
project(MattyGBoy)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(MattyGBoy
        include/bit_rotate_shift_instructions.h
        include/control_instructions.h
        include/cpu_control_instructions.h
        include/cpu_emulator.h
        include/global_declarations.h
        include/helper_functions.h
        include/load_instructions.h
        include/logical_instructions.h
        include/math_instructions.h
        include/register_structures.h
        src/bit_rotate_shift_instructions.c
        src/control_instructions.c
        src/cpu_control_instructions.c
        src/cpu_emulator.c
        src/helper_functions.c
        src/load_instructions.c
        src/logical_instructions.c
        src/math_instructions.c
        src/mattygboy.c
        src/register_structures.c)
