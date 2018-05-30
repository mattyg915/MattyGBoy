/*
 * =====================================================================================
 *
 * 	Filename:  helper_functions.c
 *
 *   Description:  Contains definitions of functions to assist in repeated misc. tasks
 *   		   used throughout the program
 *
 *       Version:  1.0
 *       Created:  05/29/2018 09:33:27
 *      Revision:  none
 *      Compiler:  gcc
 *
 *        Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "helper_functions.h"
#include "register_structures.h"
#include "global_declarations.h"
#include "cpu_emulato.h"

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


