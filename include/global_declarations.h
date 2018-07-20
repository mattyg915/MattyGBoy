/*
 * =====================================================================================
 *
 *       Filename:  global_declarations.h
 *
 *    Description:  Header file to hold all declarations of global variables
 *
 *        Version:  1.0
 *        Created:  05/28/2018 11:18:18
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *
 * =====================================================================================
 */

#include "register_structures.h"
#include "helper_functions.h"
#include "memory.h"

#ifndef GLOBALDECLARATIONS
#define GLOBALDECLARATIONS

extern unsigned char error_value;
extern unsigned char opcode;
extern unsigned char boot;
extern Registers *regs; // Pointer to the general registers
extern Pointers *ptrs; // Pointer to stack pointer and program counter
extern CPU_Flags *flags; // Pointer to the cpu flags

#endif
