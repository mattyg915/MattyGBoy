/*
 * =====================================================================================
 *
 *       Filename:  logical_instructions.c
 *
 *    Description:  Contains functions needed to emulate logical CPU instructions
 *
 *        Version:  1.0
 *        Created:  06/01/2018 21:02:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "logical_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  and
 *  Description:  Handles opcodes translating to AND instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
and (unsigned char opcode)
{
    unsigned char cycles;

    // Right operand is dependant on opcode, left is always register A
    unsigned char operand = 0;
    unsigned short reg_hl = combine_bytes(regs->H, regs->L);

    switch (opcode)
    {
        case 0xE6:
            operand = read_memory(ptrs->PC);
            ptrs->PC++;
            cycles = 0x8;
            break;
        case 0xA0:
            operand = regs->B;
            cycles = 0x4;
            break;
        case 0xA1:
            operand = regs->C;
            cycles = 0x4;
            break;
        case 0xA2:
            operand = regs->D;
            cycles = 0x4;
            break;
        case 0xA3:
            operand = regs->E;
            cycles = 0x4;
            break;
        case 0xA4:
            operand = regs->H;
            cycles = 0x4;
            break;
        case 0xA5:
            operand = regs->L;
            cycles = 0x4;
            break;
        case 0xA6:
            operand = read_memory(reg_hl);
            cycles = 0x8;
            break;
        case 0xA7:
            operand = regs->A;
            cycles = 0x4;
            break;
        default:
            return 0x0;
    }

    // AND instruction clears subtract and carry, but sets half-carry flags
    flags->H = 0x1; flags->C = 0x0; flags->N = 0x0;

    // Register A & with operand, if yields 0 set zero flag
    regs->A &= operand;
    if (!regs->A)
    {
        flags->Z = 1;
    }
    else
    {
        flags->Z = 0;
    }

    return cycles;
}               /* -----  end of function and  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  or
 *  Description:  Handles opcodes translating to OR instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
or (unsigned char opcode)
{
    unsigned char cycles;
    // Right operand is dependant on opcode, left is always register A
    unsigned char operand = 0;
    unsigned short reg_hl = combine_bytes(regs->H, regs->L);

    switch (opcode)
    {
        case 0xF6:
            operand = read_memory(ptrs->PC);
            ptrs->PC++;
            cycles = 0x8;
            break;
        case 0xB0:
            operand = regs->B;
            cycles = 0x4;
            break;
        case 0xB1:
            operand = regs->C;
            cycles = 0x4;
            break;
        case 0xB2:
            operand = regs->D;
            cycles = 0x4;
            break;
        case 0xB3:
            operand = regs->E;
            cycles = 0x4;
            break;
        case 0xB4:
            operand = regs->H;
            cycles = 0x4;
            break;
        case 0xB5:
            operand = regs->L;
            cycles = 0x4;
            break;
        case 0xB6:
            operand = read_memory(reg_hl);
            cycles = 0x8;
            break;
        case 0xB7:
            operand = regs->A;
            cycles = 0x4;
            break;
        default:
            return 0x0;
    }

    // OR instruction clears half-carry, carry, and subtract flags
    flags->H = 0; flags->C = 0; flags->N = 0;

    // Register A | with operand, if yields 0 set zero flag
    regs->A |= operand;
    if (!regs->A)
    {
        flags->Z = 1;
    }
    else
    {
        flags->Z = 0;
    }

    return cycles;
}               /* -----  end of function or  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  xor
 *  Description:  Handles opcodes translating to XOR instructions
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
xor (unsigned char opcode)
{
    unsigned char cycles;
    // Right operand is dependant on opcode, left is always register A
    unsigned char operand = 0;
    unsigned short reg_hl = combine_bytes(regs->H, regs->L);

    switch (opcode)
    {
        case 0xEE:
            operand = read_memory(ptrs->PC);
            ptrs->PC++;
            cycles = 0x8;
            break;
        case 0xA8:
            operand = regs->B;
            cycles = 0x4;
            break;
        case 0xA9:
            operand = regs->C;
            cycles = 0x4;
            break;
        case 0xAA:
            operand = regs->D;
            cycles = 0x4;
            break;
        case 0xAB:
            operand = regs->E;
            cycles = 0x4;
            break;
        case 0xAC:
            operand = regs->H;
            cycles = 0x4;
            break;
        case 0xAD:
            operand = regs->L;
            cycles = 0x4;
            break;
        case 0xAE:
            operand = read_memory(reg_hl);
            cycles = 0x8;
            break;
        case 0xAF:
            operand = regs->A;
            cycles = 0x4;
            break;
        default:
            return 0x0;
    }

    // XOR instruction clears half-carry, carry, and subtract flags
    flags->H = 0; flags->C = 0; flags->N = 0;

    // Register A ^ with operand, if yields 0 set zero flag
    regs->A ^= operand;
    if (!regs->A)
    {
        flags->Z = 1;
    }
    else
    {
        flags->Z = 0;
    }

    return cycles;
}               /* -----  end of function xor  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cpl
 *  Description:  Handles opcodes translating to a CPL instruction
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
cpl ()
{
	regs->A ^= 0xFFu; // Just invert the bits to get 1's complement
	flags->N = 1; flags->H = 1;
    return 0x4;
}		/* -----  end of function cpl  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  daa
 *  Description:  Handles opcodes translating to DAA instructions
 *  		      Credit for inspiration for this function's algorithm to Eric Haskins
 *                https://ehaskins.com/2018-01-30%20Z80%20DAA/
 *		          and /u/mudanhonnyaku on reddit:
 *		          https://www.reddit.com/r/EmuDev/comments/4ycoix/a_guide_to_
 *		          the_gameboys_halfcarry_flag/d6p3rtl
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
        unsigned char
daa ()
{
	/* Lots of inspiration for this function's code taken from Eric Haskins at
	 * https://ehaskins.com/2018-01-30%20Z80%20DAA/ */

	unsigned char correction = 0;

	// If half carry set OR if least significant nibble of A > 9
	if (flags->H || (!flags->N && (regs->A & 0xFu) > 0x9u))
	{
		correction += 0x6;
	}

	// If carry set OR most significant nibble of A >9
	if(flags->C || (!flags->N && (regs->A & 0xF0u) > 0x9u))
	{
		correction += 0x60;
		flags->C = 1; // Carry flag gets set if correct upper nibble
	}

	flags->H = 0; // Half-carry flag gets cleared by this op

	// Correction added/subtracted to/from A based on previous op
	if (flags->N)
	{
		regs->A -= correction;
	}
	else
	{
		regs->A += correction;
	}

	return 0x4;
}		/* -----  end of function daa  ----- */
