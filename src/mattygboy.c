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
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"
#include "memory.h"

#define EXIT_SUCCESS 0 // Quit without error condition

unsigned char error_value = 0xFF;
unsigned char boot_up = 0x0;
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

	while (ptrs->PC != 0xcc41)
	{
		cpu_execution();
		i++;
	}
	//dump_registers();
	printf("\n");
	dump_registers();
	//    printf("ff05 is %x\n", read_memory(0xff05));
	//    printf("ff06 is %x\n", read_memory(0xff06));
	//    printf("ff07 is %x\n", read_memory(0xff07));
	//    printf("ff10 is %x\n", read_memory(0xff10));// wrong
	//    printf("ff11 is %x\n", read_memory(0xff11));// wrong
	//    printf("ff12 is %x\n", read_memory(0xff12));
	//    printf("ff14 is %x\n", read_memory(0xff14));// wrong
	//    printf("ff16 is %x\n", read_memory(0xff16));// wrong
	//    printf("ff17 is %x\n", read_memory(0xff17));
	//    printf("ff19 is %x\n", read_memory(0xff19));// wrong
	//    printf("ff1a is %x\n", read_memory(0xff1a));// wrong
	//    printf("ff1b is %x\n", read_memory(0xff1b));// wrong
	//    printf("ff1c is %x\n", read_memory(0xff1c));// wrong
	//    printf("ff1e is %x\n", read_memory(0xff1e));// wrong
	//    printf("ff20 is %x\n", read_memory(0xff20));// wrong
	//    printf("ff21 is %x\n", read_memory(0xff21));
	//    printf("ff22 is %x\n", read_memory(0xff22));
	//    printf("ff23 is %x\n", read_memory(0xff23));// wrong
	//    printf("ff24 is %x\n", read_memory(0xff24));
	//    printf("ff25 is %x\n", read_memory(0xff25));
	//    printf("ff26 is %x\n", read_memory(0xff26));// wrong
	//    printf("ff40 is %x\n", read_memory(0xff40));
	//    printf("ff42 is %x\n", read_memory(0xff42));
	//    printf("ff43 is %x\n", read_memory(0xff43));
	//    printf("ff45 is %x\n", read_memory(0xff45));
	//    printf("ff47 is %x\n", read_memory(0xff47));
	//    printf("ff48 is %x\n", read_memory(0xff48));// wrong
	//    printf("ff49 is %x\n", read_memory(0xff49));// wrong
	//    printf("ff4a is %x\n", read_memory(0xff4a));
	//    printf("ff4b is %x\n", read_memory(0xff4b));
	//    printf("ffff is %x\n", read_memory(0xffff));
	printf("i is %d\n", i);
	//dump_memory(0xC000, 0xCC70);

	free(regs);
	free(ptrs);
	free(flags);
	return EXIT_SUCCESS;
}