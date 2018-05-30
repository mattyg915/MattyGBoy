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

#ifndef GLOBALDECLARATIONS
#define GLOBALDECLARATIONS

extern unsigned char *memory; // Pointer to the beginning of the address space
extern Registers *regs; // Pointer to the general registers
extern Pointers *ptrs; // Pointer to stack pointer and program counter

#endif
