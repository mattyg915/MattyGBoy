#include <stdlib.h>
#include "register_structures.h"

/**
 * Initializes the registers and returns a pointer to the
 * struct that contains them
 * @return a pointer to a Registers struct
 */
Registers* init_registers() {
	Registers *reg_ptr = malloc(sizeof(*reg_ptr));
	if (reg_ptr == NULL) {
		return NULL;
	}
	// All registers initialize to 0
	reg_ptr->A = 0;
	reg_ptr->B = 0;
	reg_ptr->C = 0;
	reg_ptr->D = 0;
	reg_ptr->E = 0;
	reg_ptr->F = 0;
	reg_ptr->H = 0;
	reg_ptr->L = 0;

	return reg_ptr;
}

/**
 * Initializes the stack pointer and program counter
 * and returns a pointer to the struct containing them
 * @return a pointer to a Pointers struct
 */
Pointers* init_pointers() {
	Pointers *ptrs_ptr = malloc(sizeof(*ptrs_ptr));
	if (ptrs_ptr == NULL) {
		return NULL;
	}
	// Program counter starts at 0x100, stack at 0xFFFE
	ptrs_ptr->PC = 0x0100;
	ptrs_ptr->SP = 0xFFFE;
}
