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

unsigned char error_value = 0xFF;
unsigned char boot = 0x1;
unsigned char *memory;
unsigned char *cartridge;
Registers *regs;
Pointers *ptrs;
CPU_Flags *flags;

int main(int argc, char **argv) 
{
	// Virtual registers are loaded
	regs = init_registers();
	ptrs = init_pointers();
	flags = init_flags();

	printf(argv[optind]);

	// TODO: for now just load rom via command line argument
	cartridge = load_cartridge(argv[optind]);
	memory = init_memory();

	// TODO: Main program loop, fetch/decode/execute
	// TODO: just set up for testing for the moment
    int i = 0;


    //boot = 0x0; // Disable boot rom

	while (1)
	{
        cpu_execution();
        i++;
	}

	free(regs); free(ptrs); free(flags); free(cartridge);
	return EXIT_SUCCESS;
}