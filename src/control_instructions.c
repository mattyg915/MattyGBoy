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
	eight_bit_update_flags(regs->A, operand);

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
	// Grab 16-bit immediate in case needed, only move PC if it's used
	unsigned short target = combine_bytes(memory[ptrs->PC + 1], 
			memory[ptrs->PC + 2]);
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0xC3:
			ptrs->PC = target;
			flags->jumped = 1;
			return;
		case 0xE9:
			ptrs->PC = memory[reg_hl];
			flags->jumped = 1;
			return;
		case 0xDA:
			if (flags->C)
                        {
                                ptrs->PC += target;
                                flags->jumped = 1;
                        }
                        else
                        {
                                ptrs->PC += 2;
                        }
			return;
		case 0xD2:
			if (!flags->C)
                        {
                                ptrs->PC += target;
                                flags->jumped = 1;
                        }
                        else
                        {
                                ptrs->PC += 2;
                        }
			return;
		case 0xC2:
			if (!flags->Z)
                        {
                                ptrs->PC += target;
                                flags->jumped = 1;
                        }
                        else
                        {
                                ptrs->PC += 2;
                        }
			return;
		case 0xCA:
			if (flags->Z)
                        {
                                ptrs->PC += target;
                                flags->jumped = 1;
                        }
                        else
                        {
                                ptrs->PC += 2;
                        }
			return;
	}

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
	// All ops use a 1-byte immediate
	unsigned char offset = memory[ptrs->PC + 1];

	switch (opcode)
	{
		case 0x18:
                        ptrs->PC += eight_bit_offset;
			flags->jumped = 1;
                        return;
                case 0x38:
			if (flags->C)
			{
				ptrs->PC += offset;
				flags->jumped = 1;
			}
			else
			{
				ptrs->PC++;
			}
                        return;
                case 0x30:
                        if (!flags->C)
                        {
                                ptrs->PC += offset;
                                flags->jumped = 1;
                        }
			else
			{
				ptrs->PC++;
			}
                        return;
                case 0x20:
                        if (!flags->Z)
                        {
                                ptrs->PC += offset;
                                flags->jumped = 1;
                        }
                        else
                        {
                                ptrs->PC++;
                        }

                        return;
                case 0x28:
                        if (flags->Z)
                        {
                                ptrs->PC += offset;
                                flags->jumped = 1;
                        }
                        else
                        {
                                ptrs->PC++;
                        }

                        return;
        }
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
	unsigned short target = memory[ptrs->PC + 1];
	ptrs->PC += 2; // two bytes after opcode are the target addres

	switch (opcode)
	{
		case 0xCD:
			memory[ptrs->SP - 1] = (unsigned char)(ptrs->PC >> 8);
			memory[ptrs->SP - 2] = ptrs->PC & 0xf;
 			ptrs->PC = target;
			ptrs->SP -= 2;
			flags->jumped = 1;
			return;
		case 0xDC:
			if (flags->C)
			{
				memory[ptrs->SP - 1] = (unsigned char)(ptrs->PC >> 8);
				memory[ptrs->SP - 2] = ptrs->PC & 0xf;
	 			ptrs->PC = target;
				ptrs->SP -= 2;
				flags->jumped = 1;
			}
			return;
		case 0xD4:
			if (!flags->C)
                        {
				memory[ptrs->SP - 1] = (unsigned char)(ptrs->PC >> 8);
				memory[ptrs->SP - 2] = ptrs->PC & 0xf;
	 			ptrs->PC = target;
				ptrs->SP -= 2;
				flags->jumped = 1;
                        }
			return;
		case 0xC4:
			if (!flags->Z)
                        {
				memory[ptrs->SP - 1] = (unsigned char)(ptrs->PC >> 8);
				memory[ptrs->SP - 2] = ptrs->PC & 0xf;
 				ptrs->PC = target;
				ptrs->SP -= 2;
				flags->jumped = 1;
                        }
			return;
		case 0xCC:
			if (flags->Z)
                        {
				memory[ptrs->SP - 1] = (unsigned char)(ptrs->PC >> 8);
				memory[ptrs->SP - 2] = ptrs->PC & 0xf;
 				ptrs->PC = target;
				ptrs->SP -= 2;
				flags->jumped = 1;
                        }
			return;
	}
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

	switch (opcode)
	{
		case 0xC9:
			ptrs->PC = memory[ptrs->SP] - 1;
			flags->jumped = 1;
 			ptrs->SP += 2;
			return;
		case 0xD8:
			if (flags->C)
			{
				ptrs->PC = memory[ptrs->SP] - 1;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		case 0xD0:
			if (!flags->C)
			{
				ptrs->PC = memory[ptrs->SP] - 1;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		case 0xC0:
			if (!flags->Z)
			{
				ptrs->PC = memory[ptrs->SP] - 1;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		case 0xC8:
			if (flags->Z)
			{
				ptrs->PC = memory[ptrs->SP] - 1;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
	}
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
	// Unconditional return
	ptrs->PC = memory[ptrs->SP] - 1;
 	ptrs->SP += 2;
	
	// Then enable interupts
	flags->IME = 1;

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
	unsigned char target = 0;

	switch (opcode)
	{
		case 0xC7:
			target = 0x00;
			return;
		case 0xCF:
			target = 0x08;
			return;
		case 0xD7:
			target = 0x10;
			return;
		case 0xDF:
			target = 0x18;
			return;
		case 0xE7:
			target = 0x20;
			return;
		case 0xEF:
			target = 0x28;
			return;
		case 0xF7:
			target = 0x30;
			return;
		case 0xFF:
			target = 0x38;
			return;
	}
	
	flags->jumped = 1;
	ptrs-PC = target;
        return;
}               /* -----  end of function rst  ----- */
