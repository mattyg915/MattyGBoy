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
 *   Parameters:  init_values a pointer to the beginning of an int array
 *   		  containing 7 values, which will be assigned as the 
 *   		  initializing value of each register in alphabetical order
 *       Return:  Pointer to the struct containing the virtual registers
 * =====================================================================================
 */
	Registers*
init_registers(int *init_values)
{
	Registers *reg_ptr = malloc(sizeof(*reg_ptr));
	if (reg_ptr == NULL) 
	{
		return NULL;
	}

	// Initialize with specified values
	reg_ptr->A = init_values[0];
	reg_ptr->B = init_values[1];
	reg_ptr->C = init_values[2];
	reg_ptr->D = init_values[3];
	reg_ptr->E = init_values[4];
	reg_ptr->H = init_values[5];
	reg_ptr->L = init_values[6];

	return reg_ptr;
}		/* -----  end of function init_registers  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_pointers
 *  Description:  Initializes the virtual stack pointer and program counter
 *       Return:  Pointer to the struct containing the virtual registers
 * =====================================================================================
 */
	Pointers*
init_pointers() 
{
	Pointers *ptrs_ptr = malloc(sizeof(*ptrs_ptr));
	if (ptrs_ptr == NULL) 
	{
		return NULL;
	}
	// Program counter starts at 0x100, stack at 0xFFFE
	ptrs_ptr->PC = 0x0100;
	ptrs_ptr->SP = 0xFFFE;

	return ptrs_ptr;
}		/* -----  end of function init_pointers  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_flags
 *  Description:  Initializes the flags used by CPU
 *       Return:  Pointer to the struct containing the flags
 * =====================================================================================
 */
	CPU_Flags*
init_flags ()
{
	CPU_Flags *flags_ptr = malloc(sizeof(*flags_ptr));
	if (flags_ptr == NULL)
	{
		return NULL;
	}

	flags->Z = 0;
	flags->N = 0;
	flags->H = 0;
	flags->C = 0;
	flags_ptr->jumped = 0;
	flags_ptr->IME = 0;

	return flags_ptr;
}		/* -----  end of function init_flags  ----- */
