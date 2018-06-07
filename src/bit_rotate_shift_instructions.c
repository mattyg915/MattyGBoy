/*
 * =====================================================================================
 *
 *       Filename:  bit_rotate_shift_instructions.c
 *
 *    Description:  Contains functions needed for bit test, rotate, and shift cpu
 *    		    instructions
 *
 *        Version:  1.0
 *        Created:  06/03/2018 17:14:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "bit_rotate_shift_instructions.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rotate_a
 *  Description:  Handles opcodes that translate to rotate instructions for 
 *  		  the A register
 * =====================================================================================
 */
	void
rotate_a ()
{
	// Clear N, H, and Z flags
	flags->Z = 0; flags->N = 0; flags->H = 0;
	switch (opcode)
	{
		case 0x07: // RLCA
			// Each bit of A shifts left one with bit 7 shifting 
			// into C AND bit 0
			flags->C = (regs->A & 0x80);
			regs->A <<= 1;
			regs->A |= flags->C;
			return;
		case 0x17: // RLA
			// A bit shifts 1 to the left, but 7 goes int C, 
			// C goes into bit 0
			unsigned char initial_c = flags->C;
			flags->C = (regs->A & 0x80);
			regs->A <<= 1;
			regs->A |= initial_c;
			return;
		case 0x0F: // RRCA
			// Each bit of A shifts right one with bit 0 shifting
                        // into C AND bit 7
                        flags->C = (regs->A & 0x1);
                        regs->A >>= 1;
                        regs->A |= (flags->C << 7);
			return;
		case 0x1F: // RRA
			// A bit shifts 1 to the right, bit 0 goes int C,
                        // C goes into bit 7
                        unsigned char initial_c = flags->C;
                        flags->C = (regs->A & 0x1);
                        regs->A >>= 1;
                        regs->A |= (initial_c << 7);
			return;
	}

	return;
}		/* -----  end of function rotate_a  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bit_rotate_shift
 *  Description:  Translates the much-abused CB opcode into its appropriate intsruction
 *  		  and calls executing function
 * =====================================================================================
 */
	void
bit_rotate_shift ()
{
	return;
}		/* -----  end of function bit_rotate_shift  ----- */
