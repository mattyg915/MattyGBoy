/*
 * =====================================================================================
 *
 *       Filename:  math_tests.c
 *
 *    Description:  Unit tests for arithmetic instructions/functions
 *
 *        Version:  1.0
 *        Created:  05/29/2018 12:52:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */

#include "math_instructions.h"
#include "register_structures.h"
#include "global_declarations.h"
#include "helper_functions.h"
#include "cpu_emulator.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#define EXIT_SUCCESS 0
#define MEMORY_SIZE 0xFFFF

unsigned char *memory;
Registers *regs;
Pointers *ptrs;

int main (int argc, char *argv[])
{
	// Handle optional command line arguments
	int flag;
	// Array containing initializing values for all registers (default to 0)
	int reg_init_values[8] = { 0 };
	// Check variable for verbose flag
	int verbose = 0;
	while ((flag = getopt(argc, argv, "A:B:C:D:E:F:H:L:v")) != -1) 
	{
		switch (flag) 
		{
			case 'A':
				reg_init_values[0] = strtol(optarg, NULL, 16);
				break;
			case 'B':
				reg_init_values[1] = strtol(optarg, NULL, 16);
                		break;
			case 'C':
				reg_init_values[2] = strtol(optarg, NULL, 16);
                		break;
			case 'D':
				reg_init_values[3] = strtol(optarg, NULL, 16);
               			break;
			case 'E':
				reg_init_values[4] = strtol(optarg, NULL, 16);
                		break;
			case 'F':
				reg_init_values[5] = strtol(optarg, NULL, 16);
                		break;
			case 'H':
				reg_init_values[6] = strtol(optarg, NULL, 16);
                		break;
			case 'L':
				reg_init_values[7] = strtol(optarg, NULL, 16);
                		break;
			case 'v':
				verbose = 1;
                		break;
		}
	}
	if (optind == argc) { // Check for non-optional filename argument
		printf("USAGE: ./unit_tests [unit_test_file.txt]\n");
		exit(1);
	}
	
	regs = init_registers(reg_init_values);
	ptrs = init_pointers();
	memory = malloc(MEMORY_SIZE);

	// Read instructions into memory, track how many are read
	int inst_read = 0;
	FILE *unit_test_file = fopen(argv[optind], "rb"); // Open newly dumped file
	char inst_line[5];
	while (fgets(inst_line, 4, unit_test_file) != NULL) {
		// Convert to single-byte number and store in memory array
		memory[0x0100 + inst_read] = (unsigned char)strtol(inst_line, 
				NULL, 16);
		inst_read++;
	}
	memory[0x0100 + inst_read] = 0x00;

	fclose(unit_test_file);
	
	if (verbose)
	{
		for (int i = 0x0100; i < 0x0100 + inst_read; i++)
		{
			printf("Opcode at %x is %x\n\n", i, memory[i]);
		}
	}
	
	memory[0xAABB] = 0x77;
	
	do
	{
		if (verbose)
		{
			printf("Execute opcode %x\n",opcode);
		}
		cpu_execution();
	} while (opcode != 0x00);

	dump_registers();

	return EXIT_SUCCESS;
}
