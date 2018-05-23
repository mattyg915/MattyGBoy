#include "register_structures.h"

#define MEMORY 0xFFFF // Top end of address range

Registers *regs; // Global pointer to registers
Pointers *ptrs; // Global pointer to stack pointer and program counter

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

int main(int argc, char *argv[]) {
	
	return 0;
}
