/*
 * =====================================================================================
 *
 *       Filename:  register_structures.h
 *
 *    Description:  Header file with typedefs for the register structures
 *
 *        Version:  1.0
 *        Created:  05/25/2018 20:05:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef REGISTERSTRUCTURES
#define REGISTERSTRUCTURES

typedef struct Registers 
{
	unsigned char A, B, C, D, E, H, L;
} Registers;

typedef struct Pointers 
{
	// Two 16-bit registers are used for stack pointer and program counter
	unsigned short SP, PC;
} Pointers;

typedef struct CPU_Flags 
{
	// Z, N, H, and C are the zero, subtract, half-carry, carry flags respectively
	// IME is the interrupt master enable
	// jumped set when an instruction sets the PC and cleared after each cycle
	unsigned char Z, N, H, C, IME;
} CPU_Flags;

Registers* init_registers();
CPU_Flags* init_flags();
Pointers* init_pointers();

#endif
