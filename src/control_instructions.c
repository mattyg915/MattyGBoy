/*
 * =====================================================================================
 *
 *       Filename:  control_instructions.c
 *
 *    Description:  Contains functions needed for CPU instructions dealing with
 *    		        program flow control, e.g. comparisons and jumps
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
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  cp
 *  Description:  Handles opcodes translating to CP instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
    unsigned char
cp ()
{
    unsigned char cycles;
	flags->N = 1; // CP sets the N flag

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	unsigned char operand;

	switch (opcode) {
		case 0xFE:
		    operand = read_memory(ptrs->PC);
			ptrs->PC++;
			cycles = 0x8;
			break;
		case 0xBE:
			operand = read_memory(reg_hl);
            cycles = 0x8;
			break;
		case 0xBF:
			operand = regs->A;
            cycles = 0x4;
			break;
		case 0xB8:
			operand = regs->B;
            cycles = 0x4;
			break;
		case 0xB9:
			operand = regs->C;
            cycles = 0x4;
			break;
		case 0xBA:
			operand = regs->D;
            cycles = 0x4;
			break;
		case 0xBB:
			operand = regs->E;
            cycles = 0x4;
			break;
		case 0xBC:
			operand = regs->H;
            cycles = 0x4;
			break;
		case 0xBD:
			operand = regs->L;
            cycles = 0x4;
			break;
		default:
		    operand = 0x0;
		    cycles = 0x0;
			break;
	}

	// A's state is unchanged, only the flags are affected
	eight_bit_update_flags(regs->A, operand);
	return cycles;
}		/* -----  end of function cp  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  jp
 *  Description:  Handles opcodes translating to JP instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
    unsigned char
jp ()
{
    unsigned char cycles;

	// Grab 16-bit immediate for the target
	unsigned char target_lo = read_memory(ptrs->PC);
	ptrs->PC++;
	unsigned char target_hi = read_memory(ptrs->PC);
	ptrs->PC++;
	unsigned short target = combine_bytes(target_hi, target_lo);

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0xC3:
			ptrs->PC = target;
            cycles = 0x10;
			return cycles;
		case 0xE9:
			target = reg_hl;
			ptrs->PC = target;
            cycles = 0x4;
			return cycles;
		case 0xDA:
			if (flags->C)
			{
				ptrs->PC = target;
				cycles = 0x10;
			}
			else
            {
                cycles = 0xC;
            }
			return cycles;
		case 0xD2:
            if (!flags->C)
			{
				ptrs->PC = target;
				cycles = 0x10;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		case 0xC2:
            if (!flags->Z)
			{
				ptrs->PC = target;
				cycles = 0x10;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		case 0xCA:
            if (flags->Z)
			{
				ptrs->PC = target;
				cycles = 0x10;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		default:
			return 0x0;
	}
}		/* -----  end of function jp  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  jr
 *  Description:  Handles opcodes translating to JR instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
jr ()
{
    unsigned char cycles;
	// All ops use a 1-byte immediate
	char offset = read_memory(ptrs->PC); // NOLINT
	ptrs->PC++;

	switch (opcode)
	{
		case 0x18:
			ptrs->PC += offset;
			cycles = 0xC;
			return cycles;
		case 0x38:
            if (flags->C)
			{
				ptrs->PC += offset;
				cycles = 0xC;
			}
            else
            {
                cycles = 0x8;
            }
			return cycles;
		case 0x30:
            if (!flags->C)
			{
				ptrs->PC += offset;
				cycles = 0xC;
			}
            else
            {
                cycles = 0x8;
            }
			return cycles;
		case 0x20:
            if (!flags->Z)
			{
				ptrs->PC += offset;
				cycles = 0xC;
			}
            else
            {
                cycles = 0x8;
            }
			return cycles;
		case 0x28:
            if (flags->Z)
			{
				ptrs->PC += offset;
				cycles = 0xC;
			}
            else
            {
                cycles = 0x8;
            }
			return cycles;
		default:
			return 0x0;
	}
}               /* -----  end of function jr  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  call
 *  Description:  Handles opcodes translating to CALL instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
call ()
{
    unsigned char cycles;

    // Grab 16-bit immediate for the target
    unsigned char target_lo = read_memory(ptrs->PC);
    ptrs->PC++;
    unsigned char target_hi = read_memory(ptrs->PC);
    ptrs->PC++;
    unsigned short target = combine_bytes(target_hi, target_lo);

	// Grab both bytes of PC to store on the stack
	unsigned char pc_high = (unsigned char)(ptrs->PC >> 0x08u);
	unsigned char pc_low = (unsigned char) (ptrs->PC & 0xFFu);

	switch (opcode)
	{
		case 0xCD:
			// Allocate space on stack and store PC there
			ptrs->SP--;
			write_memory(ptrs->SP, pc_high);
			ptrs->SP--;
			write_memory(ptrs->SP, pc_low);

 			ptrs->PC = target;
 			cycles = 0x18;
			return cycles;
		case 0xDC:
            if (flags->C)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

	 			ptrs->PC = target;
	 			cycles = 0x18;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		case 0xD4:
            if (!flags->C)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

	 			ptrs->PC = target;
	 			cycles = 0x18;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		case 0xC4:
            if (!flags->Z)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

 				ptrs->PC = target;
 				cycles = 0x18;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		case 0xCC:
            if (flags->Z)
			{
				ptrs->SP--;
				write_memory(ptrs->SP, pc_high);
				ptrs->SP--;
				write_memory(ptrs->SP, pc_low);

 				ptrs->PC = target;
 				cycles = 0x18;
			}
            else
            {
                cycles = 0xC;
            }
			return cycles;
		default:
			return 0x0;
	}
}               /* -----  end of function call  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ret
 *  Description:  Handles opcodes translating to RET instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
ret ()
{
    // Grab return address off the stack
    unsigned char return_lo = read_memory(ptrs->SP);
    ptrs->SP++;
    unsigned char return_hi = read_memory(ptrs->SP);
    ptrs->SP++;
    unsigned short return_address = combine_bytes(return_hi, return_lo);
	switch (opcode)
	{
		case 0xC9:
			ptrs->PC = return_address;
			return 0x10;
		case 0xD8:
            if (flags->C)
			{
				ptrs->PC = return_address;
				return 0x14;
			}
            else
            {
				return 0x8;
            }
		case 0xD0:
            if (!flags->C)
			{
				ptrs->PC = return_address;
				return 0x14;
			}
            else
            {
                return 0x8;
            }
		case 0xC0:
            if (!flags->Z)
			{
				ptrs->PC = return_address;
				return 0x14;
			}
            else
            {
				return 0x8;
            }
		case 0xC8:
            if (flags->Z)
			{
				ptrs->PC = return_address;
				return 0x14;
			}
            else
            {
				return 0x8;
            }
		default:
			return 0x0;
	}
}               /* -----  end of function ret  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  reti
 *  Description:  Handles opcodes translating to RETI instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
reti ()
{
    // Get return address off the stack
    unsigned char return_lo = read_memory(ptrs->SP);
    ptrs->SP++;
    unsigned char return_hi = read_memory(ptrs->SP);
    ptrs->SP++;
    unsigned short return_address = combine_bytes(return_hi, return_lo);

    // Unconditional return
	ptrs->PC = return_address;
	flags->IME = 0x1; // Enable interrupts

    return 0x10;
}               /* -----  end of function reti  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rst
 *  Description:  Handles opcodes translating to RST instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
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
			return 0x0;
	}

    // Grab both bytes of PC to store on the stack
    unsigned char pc_high = (unsigned char)(ptrs->PC >> 0x08u);
    unsigned char pc_low = (unsigned char) (ptrs->PC & 0xFFu);

    ptrs->SP--;
    write_memory(ptrs->SP, pc_high);
    ptrs->SP--;
    write_memory(ptrs->SP, pc_low);

	ptrs->PC = target;
	return 0x10;
}               /* -----  end of function rst  ----- */
