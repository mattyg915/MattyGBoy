/*
 * =====================================================================================
 *
 *       Filename:  unit_tests.c
 *
 *    Description:  Unit tests for cpu instructions
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
#include "register_structures.h"
#include "global_declarations.h"
#include "helper_functions.h"
#include "cpu_emulator.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#define EXIT_SUCCESS 0
#define MEMORY_SIZE 0xFFFF

unsigned char *memory;
Registers *regs;
Pointers *ptrs;
// Check variable for verbose flag
static int verbose;
// Array containing initializing values for all registers (default to 0)
static int reg_init_values[8] = { 0 };

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  add_tests
 *  Description:  Unit tests for the add() function
 * =====================================================================================
 */
	void
add_tests ()
{
	printf("Executing unit tests for add()\n");
	reg_init_values[2] = 0x5;
	reg_init_values[3] = 0xFF;
	reg_init_values[6] = 0xAA;
	reg_init_values[7] = 0xBB;

	regs = init_registers(reg_init_values);
	ptrs = init_pointers();
	memory = malloc(MEMORY_SIZE);
	
	// Read instructions for this test into memory, track how many are read
        int inst_read = 0;
	char *add_tests_file = "/Users/MattyG/Documents/Programming/MattyGBoy/tests/add_tests.txt";
        FILE *unit_test_file = fopen(add_tests_file, "r"); // Stream from test file
	assert(unit_test_file != NULL);
        char inst_line[5];
        while (fgets(inst_line, 4, unit_test_file) != NULL) 
	{
                // Store newly read instruction in virtual memory
                memory[0x0100 + inst_read] = (unsigned char)strtol(inst_line,
                                NULL, 16);
                inst_read++;
        }
	// Append 'NOP' so we have a hook to break the execution loop
        memory[0x0100 + inst_read] = 0x00;
	
	memory[0xAABB] = 0x4E;

        fclose(unit_test_file);
	
	/* In verbose mode, print out instructions loaded into memory
	 * to the console
	 */
	if (verbose)
        {
                for (int i = 0x0100; i < 0x0100 + inst_read; i++)
                {
                        printf("Opcode at %x is %x\n\n", i, memory[i]);
                }
        }
			/* First run tests basic 8 bit instructions and half-carry */
        do
        {
        	cpu_execution(); // Emulate instructions until NOP reached
		if (verbose && (opcode != 0x00)) // Dump registers after each instruction
		{
			dump_registers();
		}
        } while (opcode != 0x00);

	// Check state of registers
	assert(regs->A == 0x5A);
	assert(regs->B == 0x0);
	assert(regs->C == 0x5);
	assert(regs->D == 0xFF);
	assert(regs->E == 0x0);
	assert(regs->F == 0x20);
	assert(regs->H == 0xAA);
	assert(regs->L == 0xBB);

	// Check state of pointers
	assert(ptrs->SP == 0xFFFE);
	assert(ptrs->PC == 0x0106);

		/* Second run tests 16-bit instructions and carry */

	do
        {
                cpu_execution(); // Emulate instructions until NOP reached
                if (verbose && (opcode != 0x00)) // Dump registers after each instruction
                {
                        dump_registers();
                }
        } while (opcode != 0x00);

        // Check state of registers
        assert(regs->A == 0x04);
        assert(regs->F == 0x30);
        assert(regs->L == 0xC0);

        // Check state of pointers
        assert(ptrs->PC == 0x0109);

	/*  Third run tests SP ops */

	do
        {
                cpu_execution(); // Emulate instructions until NOP reached
                if (verbose && (opcode != 0x00)) // Dump registers after each instruction
                {
                        dump_registers();
                }
        } while (opcode != 0x00);

	assert(ptrs->SP == 0xFFFD);
	assert(regs->F == 0x40);

	printf("All add() tests passed successfully\n");
	return;
}	/* -----  end of function add_tests  ----- */

int main (int argc, char *argv[])
{
	// Handle optional command line arguments
	int flag;
	while ((flag = getopt(argc, argv, "A:B:C:D:E:F:H:L:v")) != -1) 
	{
		switch (flag) 
		{
			case 'v':
				verbose = 1;
                		break;
		}
	}
	
	// Run unit tests for add()
	add_tests();
	
	return EXIT_SUCCESS;
}
