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
	/* Grab the next byte in case an immediate value is needed
	 * but don't increment PC unless it's actually used */
	char immediate_value = memory[ptrs->PC + 1];
	unsigned short value1 = 0; // For operations using 16-bit values
	switch (opcode)
	{
		// Immediate value cases
		case 0xC6:
			regs->A += immediate_value;
			ptrs->PC++;
			break;
		case 0xE8:
			ptrs->SP += immediate value;
			ptrs->PC++;
			break;
		// 8-bit register cases
		case 0x80
			regs->A += regs->B;
			break;
		case 0x81:
			regs->A += regs->C;
			break;
		case 0x82:
			regs->A += regs->D;
			break;
		case 0x83:
			regs->A += regs->E;
			break;
		case 0x84:
			regs->A += regs->H;
			break;
		case 0x85:
			regs->A += regs->L;
			break;
		case 0x87:
			regs->A += regs->A;
			break;
		// Cases involving 16-bit registers
		case 0x86:
			// Use HL as address to get value from memory and add to A
			value = combine_registers(regs->H, regs->L);
			regs->A += memory[value];
			break;
		case 0x09:
			// HL + BC --> HL
			value = combine_registers(regs->H, regs->L);
			value += combine_registers(regs->B, regs->C)
			split_between_registers(value, &(regs->H), &(regs->L))
			break;
		case 0x19:
			// HL + DE --> HL
			value = combine_registers(regs->H, regs->L);
			value += combine_registers(regs->D, regs->E);
			split_between_registers(value, &(regs->H), &(regs->L));
			break;
		case 0x29:
			// HL + HL --> HL
			value = combine_registers(regs->H, regs->L);
			value += combine_registers(regs->H, regs->L);
			split_between_registers(value, &(regs->H), &(regs->L));
			break;
		case 0x39:
			// HL + SP --> HL
			value = combine_registers(regs->H, regs->L);
			value += ptrs->SP;
			split_between_registers(value, &(regs->H), &(regs->L));
			break;
	}
	return;
}		/* -----  end of function add  ----- */
