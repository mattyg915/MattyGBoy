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
	// F register is used for flags
	unsigned char A, B, C, D, E, F, H, L;
} Registers;

typedef struct Pointers 
{
	// Two 16-bit registers are used for stack pointer and program counter
	unsigned short SP, PC;
} Pointers;

typedef struct CPU_Flags 
{
	// Special flags used only by CPU
	// jumped set when an instruction sets the PC and cleared after each cyycle
	// IME is the Interrupt Master Enable flag
	unsigned char jumped, IME;
} CPU_Flags;

Registers* init_registers();
CPU_Flags* init_flags();
Pointers* init_pointers();

#endif
