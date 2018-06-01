/*
 * =====================================================================================
 *
 *       Filename:  math_instructions.c
 *
 *    Description:  Constains all of the functions needed for mathematical 
 *    		    instructions
 *
 *        Version:  1.0
 *        Created:  05/25/2018 20:05:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include "math_instructions.h"
#include "global_declarations.h"
#include "helper_functions.h"
#include "cpu_emulator.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  add
 *  Description:  Handles opcodes translating to ADD instructions
 * =====================================================================================
 */
	void
add ()
{
	// Clear the N flag
	regs->F &= 0xB0;

	/* Grab the next byte in case an immediate value is needed
	 * but don't increment PC unless it's actually used */
	unsigned char immediate_value = memory[ptrs->PC + 1];
	unsigned short value1 = 0, value2 = 0; // For operations using 16-bit values
	switch (opcode)
	{
		// Immediate value cases
		case 0xC6:
			eight_bit_update_flags(regs->A, immediate_value);
			regs->A += immediate_value;
			ptrs->PC++;
			break;
		case 0xE8:
			eight_bit_update_flags(regs->A, immediate_value);
			ptrs->SP += immediate_value;
			ptrs->PC++;
			break;
		// 8-bit register cases
		case 0x80:
			eight_bit_update_flags(regs->A, regs->B);
			regs->A += regs->B;
			break;
		case 0x81:
			eight_bit_update_flags(regs->A, regs->C);
			regs->A += regs->C;
			break;
		case 0x82:
			eight_bit_update_flags(regs->A, regs->D);
			regs->A += regs->D;
			break;
		case 0x83:
			eight_bit_update_flags(regs->A, regs->E);
			regs->A += regs->E;
			break;
		case 0x84:
			eight_bit_update_flags(regs->A, regs->H);
			regs->A += regs->H;
			break;
		case 0x85:
			eight_bit_update_flags(regs->A, regs->L);
			regs->A += regs->L;
			break;
		case 0x87:
			eight_bit_update_flags(regs->A, regs->A);
			regs->A += regs->A;
			break;
		case 0x86:
			// Use HL as address to get value from memory and add to A
			value1 = combine_registers(regs->H, regs->L);
			eight_bit_update_flags(regs->A, memory[value1]);
			regs->A += memory[value1];
			break;
		case 0x09:
			// HL + BC --> HL
			value1 = combine_registers(regs->H, regs->L);
			value2 = combine_registers(regs->B, regs->C);
			sixteen_bit_update_flags(value1, value2);
			split_between_registers((value1 + value2), &(regs->H), &(regs->L));
			break;
		case 0x19:
			// HL + DE --> HL
			value1 = combine_registers(regs->H, regs->L);
			value2 = combine_registers(regs->D, regs->E);
			sixteen_bit_update_flags(value1, value2);
			split_between_registers((value1 + value2), &(regs->H), &(regs->L));
			break;
		case 0x29:
			// HL + HL --> HL
			value1 = combine_registers(regs->H, regs->L);
			value2 = combine_registers(regs->H, regs->L);
			sixteen_bit_update_flags(value1, value2);
			split_between_registers((value1 + value2), &(regs->H), &(regs->L));
			break;
		case 0x39:
			// HL + SP --> HL
			value1 = combine_registers(regs->H, regs->L);
			value2 = ptrs->SP;
			sixteen_bit_update_flags(value1, value2);
			split_between_registers((value1 + value2), &(regs->H), &(regs->L));
			break;
	}
	return;
}		/* -----  end of function add  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  adc
 *  Description:  
 * =====================================================================================
 */
	void
adc ()
{
	return;
}		/* -----  end of function adc  ----- */



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  and
 *  Description:  
 * =====================================================================================
 */
	void
and ()
{
	return;
}		/* -----  end of function and  ----- */
