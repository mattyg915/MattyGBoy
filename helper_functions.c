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

#include "helper_functions.h"
#include "register_structures.h"
#include "global_declarations.h"

/*
 * ===  FUNCTION  ======================================================================
 *	   Name:  combine_registers
 *  Description:  Takes the 8-bit values from 2 registers and returns them as a 
 *                single 16-bit value
 *   Parameters:  reg1 is an unsigned char from the register that should occupy
 *                the 8 most significant bits of the new value
 *                reg2 is an unsigned char from the register that should occupy
 *                the lower-order 8 bits of the new value
 *       Return:  an unsigned short that is the concatenation of the passed values
 * =====================================================================================
 */
	unsigned short
combine_registers(unsigned char reg1, unsigned char reg2)
{
	unsigned short result = (unsigned short)reg1;
	// bit-shift reg1 8 to the left to get the 8 most significant bits
	result <<= 8;
	// Then just add reg2 to get the 8 least significant bits
	result += reg2;

	return result;
}		/* -----  end of function combine_registers  ----- */

/* ===  FUNCTION  ======================================================================
 *         Name:  split_between_registers
 *  Description:  Takes a 16-bit value and splits it between two 8-bit registers
 *   Parameters:  value is the 16-bit value to split
 *                reg1 is a pointer to the register where the higher-order bits should
 *                be placed
 *                reg2 is a pointer to the register where the lower-order bits should
 *                be placed
 * =====================================================================================
 */
	void
split_between_registers(unsigned short value, 
		unsigned char *reg1, unsigned char *reg2)
{
	// Cast as a char to just grab the lower-order bits
	*reg2 = (unsigned char)value;
	// Shift the higher bits into the lower position then cast
	value >>= 8;
	*reg1 = (unsigned char)value;
}	/* -----  end of function split_between_registers  ----- */
