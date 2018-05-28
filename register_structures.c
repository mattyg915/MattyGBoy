/*
 * =====================================================================================
 *
 *       Filename:  register_structures.c
 *
 *    Description:  Constains definitions of functions used to initialize the
 *    		    structures that contain the registers
 *
 *        Version:  1.0
 *        Created:  05/25/2018 20:05:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "register_structures.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_registers
 *  Description:  Initializes the virtual registers
 *  Return:	  Pointer to the struct containing the virtual registers
 * =====================================================================================
 */
	Registers*
init_registers() {
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
}		/* -----  end of function init_registers  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_pointers
 *  Description:  Initializes the virtual stack pointer and program counter
 *  Return:       Pointer to the struct containing the virtual registers
 * =====================================================================================
 */
	Pointers*
init_pointers() {
	Pointers *ptrs_ptr = malloc(sizeof(*ptrs_ptr));
	if (ptrs_ptr == NULL) {
		return NULL;
	}
	// Program counter starts at 0x100, stack at 0xFFFE
	ptrs_ptr->PC = 0x0100;
	ptrs_ptr->SP = 0xFFFE;

	return ptrs_ptr;
}		/* -----  end of function init_pointers  ----- */
