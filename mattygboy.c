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
#include "math_instructions.h"
#include "global_declarations.h"

#define MEMORY_SIZE 0xFFFF // Top end of address range

unsigned char *memory;
Registers *regs;
Pointers *ptrs;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  dump_registers
 *  Description:  Prints the contents of the registers to the console
 * =====================================================================================
 */
	void
dump_registers()
{
	printf("Registers: A: %x B: %x C: %x D: %x E: %x"
			" F: %x H: %x L: %x\n", regs->A, regs->B,
			regs->C, regs->D, regs->E, regs->F, 
			regs->H, regs->L);
	printf("Stack pointer: %x Program Counter: %x\n", 
			ptrs->SP, ptrs->PC);
	return;
}		/* -----  end of function dump_registers  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  decode
 *  Description:  Takes the current opcode pointed to by PC and determines 
 *  		  its generalized instruction (e.g. this is a 'load' instruction), 
 *  		  then calls the appropriate method to further decode and emulate it
 * =====================================================================================
 */
	void
initial_decode() {
	unsigned char opcode = memory[ptrs->PC];
	// TODO:pretty much this whole method
	switch (opcode) {
		case 0xC6:
		case 0x80 ... 0x87:
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
		case 0xE8:
			// Add instructions
			add();
			break;
	}
	return;
}		/* -----  end of function decode  ----- */

int main(int argc, char *argv[]) {
	// Virtual registers are loaded
	regs = init_registers();
	ptrs = init_pointers();

	// TODO:Initialize virtual memory
	memory = malloc(MEMORY_SIZE);
	// TODO:Load cartridge data into virtual memory
	
	// TODO:Main program loop, fetch/decode/execute
	
	free(regs); free(ptrs); free(memory);
	return 0;
}
