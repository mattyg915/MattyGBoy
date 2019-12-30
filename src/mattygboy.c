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
#include "memory.h"

#define EXIT_SUCCESS 0 // Quit without error condition

unsigned char error_value = 0xFF;
unsigned char boot = 0x1;
Registers *regs;
Pointers *ptrs;
CPU_Flags *flags;

int main(int argc, char **argv) 
{
	// Virtual registers are loaded
	regs = init_registers();
	ptrs = init_pointers();
	flags = init_flags();

	// TODO: for now just load rom via command line argument
	load_cartridge(argv[optind]);
	init_memory();

	// TODO: Main program loop, fetch/decode/execute
	// TODO: just set up for testing for the moment
    int i = 0;
    unsigned char *mem = get_mem();


    //boot = 0x0; // Disable boot rom

	while (ptrs->PC != 0x100u)
	{
        cpu_execution(mem);
        i++;
	}
    //dump_registers();
    printf("\n");
    dump_memory();

	free(regs); free(ptrs); free(flags);
	return EXIT_SUCCESS;
}