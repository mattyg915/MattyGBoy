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
        flags->C = (*reg & 0x80);
        *reg <<= 1;
        *reg |= flags->C;
	flags->Z = ? (*reg == 0) 1 : 0;
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
	flags->Z = ? (*reg == 0) 1 : 0;
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
	flags->Z = ? (*reg == 0) 1 : 0;
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
	flags->Z = ? (*reg == 0) 1 : 0;
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
	// For ones where HL is needed
        unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		// RLC instructions
		case 0x00:
			rlc(&regs->B);
			return;
		case 0x01:
			rlc(&regs->C);
			return;
		case 0x02:
                        rlc(&regs->D);
                        return;
		case 0x03:
                        rlc(&regs->E);
                        return;
		case 0x04:
                        rlc(&regs->H);
                        return;
		case 0x05:
                        rlc(&regs->L);
                        return;
		case 0x06:
                        rlc(&(memory[reg_hl]));
                        return;
		case 0x07:
                        rlc(&regs->A);
                        return;
		// RRC instructions
		case 0x08:
			rrc(&regs->B);
			return;
		case 0x09:
                        rrc(&regs->C);
                        return;
		case 0x0A:
                        rrc(&regs->D);
                        return;
		case 0x0B:
                        rrc(&regs->E);
                        return;
		case 0x0C:
                        rrc(&regs->H);
                        return;
		case 0x0D:
                        rrc(&regs->L);
                        return;
		case 0x0E:
                        rrc(&(memory[reg_hl]));
                        return;
		case 0x0F:
                        rrc(&regs->A);
                        return;
		// 

	}
	return;
}		/* -----  end of function bit_rotate_shift  ----- */
