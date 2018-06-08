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
#include "bit_rotate_shift_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rlc
 *  Description:  Handles all RLC instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
        void
rlc (unsigned char *reg)
{
        // Clears N and H flags
        flags->N = 0; flags->H = 0;
        // Each bit of A shifts left one with bit 7 shifting 
        // into C AND bit 0
        flags->C = (regs->A & 0x80);
        regs->A <<= 1;
        regs->A |= flags->C;
	return;
}               /* -----  end of function rlc  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rl
 *  Description:  Handles all RL instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
        void
rl (unsigned char *reg)
{
        // Clears N and H flags
        flags->N = 0; flags->H = 0;
        // Each bit of register shifts left one with bit 0 shifting
        // into C and c going into bit 7
        unsigned char initial_c = flags->C;
        flags->C = (*reg & 0x80);
        *reg <<= 1;
        *reg |= initial_c;
        return;
}               /* -----  end of function rl  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rr
 *  Description:  Handles all RR instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
        void
rr (unsigned char *reg)
{
        // Clears N and H flags
        flags->N = 0; flags->H = 0;
        // Each bit of register shifts right one with bit 0 shifting
        // into C and C goes into bit 7
	unsigned char initial_c = flags->C;
        flags->C = (*reg & 0x1);
        *reg >>= 1;
        *reg |= (initial_c << 7);
        return;
}               /* -----  end of function rr  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rrc
 *  Description:  Handles all RRC instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
	void
rrc (unsigned char *reg)
{
	// Clears N and H flags
        flags->N = 0; flags->H = 0;
	// Each bit of register shifts right one with bit 0 shifting
        // into C AND bit 7
        flags->C = (*reg & 0x1);
        *reg >>= 1;
        *reg |= (flags->C << 7);
	return;
}		/* -----  end of function rrc  ----- */

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
	switch (opcode)
	{
		case 0x00:
			return;
	}
	return;
}		/* -----  end of function bit_rotate_shift  ----- */
