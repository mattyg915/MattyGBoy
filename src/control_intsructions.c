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
	// Grab 16-bit immediate in case needed, only move PC if it's used
	// As PC is incremented in the CPU loop, 1 is subtracted from each target
	unsigned char sixteen_bit_target = combine_bytes(memory[ptrs->PC + 1], 
			memory[ptrs->PC + 2]) - 1;
	unsigned short reg_hl = combine_bytes(regs->H, regs->L) - 1;

	switch (opcode)
	{
		case 0xC3:
			ptrs->PC = sixteen_bit_target;
			return;
		case 0xE9:
			ptrs->PC = reg_hl;
			return;
		case 0xDA:
			ptrs->PC = get_carry_flag() ? sixteen_bit_target : ptrs->PC + 2;
			return;
		case 0xD2:
			ptrs->PC = !get_carry_flag() ? sixteen_bit_target : ptrs->PC + 2;
			return;
		case 0xC2:
			ptrs->PC = !get_zero_flag() ? sixteen_bit_target : ptrs->PC + 2;
			return;
		case 0xCA:
			ptrs->PC = get_zero_flag() ? sixteen_bit_target : ptrs->PC + 2;
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
	// Don't adjust for cpu() method incrementing PC as it's balanced by
	// jumping from the address of the immediate value, so 
	// the proper offset from the initial address would be offset + 1
	unsigned char eight_bit_offset = memory[ptrs->PC + 1];

	switch (opcode)
	{
		case 0x18:
                        ptrs->PC += eight_bit_target;
                        return;
                case 0x38:
                        ptrs->PC += get_carry_flag() ? eight_bit_target : 1;
                        return;
                case 0x30:
                        ptrs->PC += !get_carry_flag() ? eight_bit_target : 1;
                        return;
                case 0x20:
                        ptrs->PC += !get_zero_flag() ? eight_bit_target : 1;
                        return;
                case 0x28:
                        ptrs->PC += get_zero_flag() ? eight_bit_target : 1;
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
	// All ops take a 2-byte immediate operand
	// Subtract one from target because PC incremented by CPU function
	unsigned char target = combine_bytes(memory[ptrs->PC + 1], 
			memory[ptrs->PC + 2]) - 1;
	ptrs->PC += 2;

	switch (opcode)
	{
		case 0xCD:
			ptrs->SP -= 2;
			memory[ptrs->SP + 1] = (unsigned char)(ptrs->PC >> 8);
			memory[ptrs->SP] = ptrs->PC & 0xf;
			ptrs->PC = target;
			return;
		case 0xDC:
			if (get_carry_flag())
			{
				ptrs->SP -= 2;
                        	memory[ptrs->SP + 1] = (unsigned char)(ptrs->PC >> 8);
                        	memory[ptrs->SP] = (unsigned char)ptrs->PC;
                        	ptrs->PC = target;
			}
			return;
		case 0xD4:
			if (!get_carry_flag())
                        {       
                                ptrs->SP -= 2;
                                memory[ptrs->SP + 1] = (unsigned char)(ptrs->PC >> 8);
                                memory[ptrs->SP] = (unsigned char)ptrs->PC;
                                ptrs->PC = target;
                        }
			return;
		case 0xC4:
			if (!get_zero_flag())
                        {
                                ptrs->SP -= 2;
                                memory[ptrs->SP + 1] = (unsigned char)(ptrs->PC >> 8);
                                memory[ptrs->SP] = (unsigned char)ptrs->PC;
                                ptrs->PC = target;
                        }
			return;
		case 0xCC:
			if (get_zero_flag())
                        {
                                ptrs->SP -= 2;
                                memory[ptrs->SP + 1] = (unsigned char)(ptrs->PC >> 8);
                                memory[ptrs->SP] = (unsigned char)ptrs->PC;
                                ptrs->PC = target;
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
		// Decrement since PC will be incremented by cpu function
		unsigned short return_address = combine_bytes(memory[ptrs->SP + 1],
				memory[ptrs->SP]) - 1;
		case 0xC9:
			ptrs->SP += 2;
			ptrs->PC = return_address;
			return;
		case 0xD8:
			if (get_carry_flag())
			{
				ptrs->SP += 2;
                        	ptrs->PC = return_address;
			}
			return;
		case 0xD0:
			if (!get_carry_flag())
			{
				ptrs->SP += 2;
                        	ptrs->PC = return_address;
			}
			return;
		case 0xC0:
			if (!get_zero_flag())
			{
				ptrs->SP += 2;
                        	ptrs->PC = return_address;
			}
			return;
		case 0xC8:
			if (get_zero_flag())
			{
				ptrs->SP += 2;
                        	ptrs->PC = return_address;
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
	// Decrement since PC will be incremented by cpu function
        unsigned short return_address = combine_bytes(memory[ptrs->SP + 1], 
			memory[ptrs->SP]) - 1;
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
