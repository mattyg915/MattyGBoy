/*
 * =====================================================================================
 *
 *       Filename:  control_instructions.c
 *
 *    Description:  Constains functions needed for CPU instructions dealing with 
 *    		    program flow control, e.g. comparisons and jumps
 *
 *        Version:  1.0
 *        Created:  06/05/2018 09:45:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  cp
 *  Description:  Handles opcodes translating to CP instructions
 * =====================================================================================
 */
        void
cp ()
{
	regs->F |= 0x40; // CP sets the N flag

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	unsigned char operand;

	switch (opcode)
	{
		case 0xFE:
			ptrs->PC++;
			operand = memory[ptrs->PC];
			break;
		case 0xBE:
			operand = memory[reg_hl];
			break;
		case 0xBF:
			operand = regs->A;
			break;
		case 0xB8:
                        operand = regs->D;
                        break;
		case 0xB9:
                        operand = regs->C;
                        break;
		case 0xBA:
                        operand = regs->D;
                        break;
		case 0xBB:
                        operand = regs->E;
                        break;
		case 0xBC:
                        operand = regs->H;
                        break;
		case 0xBD:
                        operand = regs->L;
                        break;
	}

	// A's state is unchanged, only the flags are affected
	eight_bit_update_flags(regs-A, operand);

	return;
}		/* -----  end of function cp  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  jp
 *  Description:  Handles opcodes translating to JP instructions
 * =====================================================================================
 */
        void
jp ()
{
	return;
}		/* -----  end of function jp  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  jr
 *  Description:  Handles opcodes translating to JR instructions
 * =====================================================================================
 */
        void
jr ()
{
        return;
}               /* -----  end of function jr  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  call
 *  Description:  Handles opcodes translating to CALL instructions
 * =====================================================================================
 */
        void
call ()
{
        return;
}               /* -----  end of function call  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ret
 *  Description:  Handles opcodes translating to RET instructions
 * =====================================================================================
 */
        void
ret ()
{
        return;
}               /* -----  end of function ret  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  reti
 *  Description:  Handles opcodes translating to RETI instructions
 * =====================================================================================
 */
        void
reti ()
{
        return;
}               /* -----  end of function reti  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rst
 *  Description:  Handles opcodes translating to RST instructions
 * =====================================================================================
 */
        void
rst ()
{
        return;
}               /* -----  end of function rst  ----- */
