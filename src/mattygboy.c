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
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "register_structures.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

#define EXIT_SUCCESS 0 // Quit without error condition
#define MEMORY_SIZE 0xFFFF // Top end of address range

unsigned char *memory;
Registers *regs;
Pointers *ptrs;
CPU_Flags *flags;

int main(int argc, char **argv) 
{
	int verbose = 1;
	// Handle optional command line arguments
	int flag;
	while ((flag = getopt(argc, argv, "v")) != -1)
	{
		switch (flag)
		{
			case 'v':
				verbose = 1;
                		break;
		}
	}

	// Array containing initializing values for all registers (default to 0)
	int reg_init_values[7] = { 0 };
	// Virtual registers are loaded
	regs = init_registers(reg_init_values);
	ptrs = init_pointers();
	flags = init_flags();

	// TODO:Initialize virtual memory
	memory = malloc(MEMORY_SIZE);
	// TODO:Load cartridge data into virtual memory
	load_rom(argv[optind]); // TODO this is just set this way for testing for now
	// TODO:Main program loop, fetch/decode/execute
	// TODO just set up for testing for the moment
	while (opcode != 0x76)
	{
		cpu_execution();
		printf("opcode: %x\n", opcode);
		if (verbose)
		{
			dump_registers();
		}
	}
	dump_registers();

	free(regs); free(ptrs); free(memory);
	return EXIT_SUCCESS;
}
