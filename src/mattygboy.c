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
	int verbose = 0;
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

	// Virtual registers are loaded
	regs = init_registers();
	ptrs = init_pointers();
	flags = init_flags();

	// TODO: for now just load rom via command line argument
	unsigned char *cartridge = load_cartridge(argv[optind]);
	memory = init_memory(cartridge);

	// TODO:Main program loop, fetch/decode/execute

	free(regs); free(ptrs); free(flags); free_all_memory();
	return EXIT_SUCCESS;
}
