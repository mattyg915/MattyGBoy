#include <stdlib.h>
#include <stdio.h>
#include "register_structures.h"

#define MEMORY 0xFFFF // Top end of address range

Registers *regs; // Pointer to registers
Pointers *ptrs; // Pointer to stack pointer and program counter
unsigned char *memory // Pointer to the beginning of the address space
/**
 * Prints the contents of the registers and pointers
 * to the console
 */
void dump_registers() {
	printf("Registers: A: %x B: %x C: %x D: %x E: %x"
			" F: %x H: %x L: %x\n", regs->A, regs->B,
			regs->C, regs->D, regs->E, regs->F, 
			regs->H, regs->L);
	printf("Stack pointer: %x Program Counter: %x\n", 
			ptrs->SP, ptrs->PC);
	return;
}

/**
 * Takes an opcode and determines its generalized instruction
 * (e.g. this is a 'load' instruction), then
 * calls the appropriate method to further decode and emulate it
 * @param opcode is the 1-byte opcode to decode
 */
void initial_decode(unsigned char opcode) {
	// TODO:this whole method
	switch (opcode) {
		
	}
}

int main(int argc, char *argv[]) {
	// Virtual registers are loaded
	regs = init_registers();
	ptrs = init_pointers();

	// TODO:Initialize virtual memory
	memory = malloc(MEMORY);
	// TODO:Load cartridge data into virtual memory
	
	// TODO:Main program loop, fetch/decode/execute
	
	free(regs); free(ptrs); free(memory);
	return 0;
}
