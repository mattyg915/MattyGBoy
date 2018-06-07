/*
 * =====================================================================================
 *
 *       Filename:  mattygboy.c
 *
 *    Description:  Main source file for the application
 *
 *        Version:  1.0
 *        Created:  05/25/2018 10:45:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include "register_structures.h"
#include "global_declarations.h"
#include "cpu_emulator.h"

#define EXIT_SUCCESS 0 // Quit without error condition
#define MEMORY_SIZE 0xFFFF // Top end of address range

unsigned char *memory;
Registers *regs;
Pointers *ptrs;
CPU_Flags *flags;

int main(int argc, char *argv[]) 
{
	// Array containing initializing values for all registers (default to 0)
	int reg_init_values[8] = { 0 };
	// Virtual registers are loaded
	regs = init_registers(reg_init_values);
	ptrs = init_pointers();
	flags = init_flags();

	// TODO:Initialize virtual memory
	memory = malloc(MEMORY_SIZE);
	// TODO:Load cartridge data into virtual memory
	
	// TODO:Main program loop, fetch/decode/execute
	
	free(regs); free(ptrs); free(memory);
	return EXIT_SUCCESS;
}
