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
			default:
				break;
		}
	}

	// Virtual registers are loaded
	regs = init_registers();
	ptrs = init_pointers();
	flags = init_flags();

	// TODO: for now just load rom via command line argument
	cartridge = load_cartridge(argv[optind]);
	memory = init_memory();


	// TODO:Main program loop, fetch/decode/execute
	// TODO just set up for testing for the moment
    int i = 0;
    //while(ptrs->PC != 0x100) // Boot
    while (memory[0xFF44] == 0)
    //while (memory[0xFF44] < 1)
    {
        cpu_execution();
        i++;
    }
    printf("i is %d\n\n", i);
    printf("opcode: %x\n",opcode);
    dump_registers();
    printf("mem ff44 is 0x%x\n", memory[0xFF44]);
    printf("divider is 0x%x and timer is 0x%x\n", memory[0xFF04], memory[0xFF05]);

    return 0;

    boot = 0x0; // Disable boot rom

	while (i < 16545)
	{
        //printf("mem ff44 is %x\n", memory[0xFF44]);
        //printf("divider is %x and timer is %x\n", memory[0xFF04], memory[0xFF05]);
        cpu_execution();
        printf("opcode: %x\n",opcode);
        dump_registers();
        i++;
	}
    printf("mem ff44 is %x\n", memory[0xFF44]);
    printf("divider is %x and timer is %x\n", memory[0xFF04], memory[0xFF05]);
    dump_registers();
	free(regs); free(ptrs); free(flags);
	return EXIT_SUCCESS;
}