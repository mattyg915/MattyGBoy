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
#include <stdio.h>
#include <stdlib.h>
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

// TODO: optimize the conditional jumps so that we only have the PC moving on one line
// TODO: fix call and possibly others because you need the 'else' part that just moves PC

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  cp
 *  Description:  Handles opcodes translating to CP instructions
 * =====================================================================================
 */
        void
cp ()
{
	flags->N = 1; // CP sets the N flag

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	unsigned char *operand;

	switch (opcode) {
		case 0xFE:
			ptrs->PC++;
			operand = read_memory(ptrs->PC);
			break;
		case 0xBE:
			operand = read_memory(reg_hl);
			break;
		case 0xBF:
			operand = &regs->A;
			break;
		case 0xB8:
			operand = &regs->B;
			break;
		case 0xB9:
			operand = &regs->C;
			break;
		case 0xBA:
			operand = &regs->D;
			break;
		case 0xBB:
			operand = &regs->E;
			break;
		case 0xBC:
			operand = &regs->H;
			break;
		case 0xBD:
			operand = &regs->L;
			break;
		default:
			return;
	}
	// A's state is unchanged, only the flags are affected
	eight_bit_update_flags(regs->A, *operand);
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
	// Grab 16-bit immediate for the target
	unsigned short *target = read_memory((unsigned short) (ptrs->PC + 0x1));

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0xC3:
			ptrs->PC = *target;
			flags->jumped = 1;
			return;
		case 0xE9:
			target = read_memory(reg_hl);
			ptrs->PC = *target;
			flags->jumped = 1;
			return;
		case 0xDA:
			if (flags->C)
			{
				ptrs->PC += *target;
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
				ptrs->PC += *target;
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
				ptrs->PC += *target;
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
				ptrs->PC += *target;
				flags->jumped = 1;
			}
			else
			{
				ptrs->PC += 2;
			}
			return;
		default:
			return;
	}
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
	unsigned char *offset = read_memory((unsigned short) (ptrs->PC + 1));

	switch (opcode)
	{
		case 0x18:
			ptrs->PC += *offset;
			flags->jumped = 1;
			return;
		case 0x38:
			if (flags->C)
			{
				ptrs->PC += *offset;
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
				ptrs->PC += *offset;
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
				ptrs->PC += *offset;
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
				ptrs->PC += *offset;
				flags->jumped = 1;
			}
			else
			{
				ptrs->PC++;
			}
			return;
		default:
			break;
	}
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
	unsigned short *target = read_memory((unsigned short) (ptrs->PC + 0x1));

	// Grab both nibbles of PC to store on the stack
	unsigned char pc_high = (unsigned char)(ptrs->PC >> 0x8u);
	unsigned char pc_low = (unsigned char) (ptrs->PC & 0xFu);

	switch (opcode)
	{
		case 0xCD:
			// Allocate space on stack and store PC there
			ptrs->SP--;
			write_memory(ptrs->SP, pc_high);
			ptrs->SP--;
			write_memory(ptrs->SP, pc_low);

 			ptrs->PC = *target;
			flags->jumped = 1;
			return;
		case 0xDC:
			if (flags->C)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

	 			ptrs->PC = *target;
				ptrs->SP -= 2;
				flags->jumped = 1;
			}
			return;
		case 0xD4:
			if (!flags->C)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

	 			ptrs->PC = *target;
				ptrs->SP -= 2;
				flags->jumped = 1;
			}
			return;
		case 0xC4:
			if (!flags->Z)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

 				ptrs->PC = *target;
				ptrs->SP -= 2;
				flags->jumped = 1;
			}
			return;
		case 0xCC:
			if (flags->Z)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

 				ptrs->PC = *target;
				ptrs->SP -= 2;
				flags->jumped = 1;
			}
			return;
		default:
			return;
	}
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
	unsigned short *return_address = read_memory((unsigned short) (ptrs->SP - 0x1));
	switch (opcode)
	{
		case 0xC9:
			ptrs->PC = *return_address;
			flags->jumped = 1;
 			ptrs->SP += 2;
			return;
		case 0xD8:
			if (flags->C)
			{
				ptrs->PC = *return_address;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		case 0xD0:
			if (!flags->C)
			{
				ptrs->PC = *return_address;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		case 0xC0:
			if (!flags->Z)
			{
				ptrs->PC = *return_address;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		case 0xC8:
			if (flags->Z)
			{
				ptrs->PC = *return_address;
				flags->jumped = 1;
 				ptrs->SP += 2;
			}
			return;
		default:
			return;
	}
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
	unsigned short *return_address = read_memory((unsigned short) (ptrs->SP - 0x1));
	// Unconditional return
	ptrs->PC = *return_address;
 	ptrs->SP += 2;
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
			break;
		case 0xCF:
			target = 0x08;
			break;
		case 0xD7:
			target = 0x10;
			break;
		case 0xDF:
			target = 0x18;
			break;
		case 0xE7:
			target = 0x20;
			break;
		case 0xEF:
			target = 0x28;
			break;
		case 0xF7:
			target = 0x30;
			break;
		case 0xFF:
			target = 0x38;
			break;
		default:
			return;
	}
	
	flags->jumped = 1;
	ptrs->PC = target;
}               /* -----  end of function rst  ----- */
