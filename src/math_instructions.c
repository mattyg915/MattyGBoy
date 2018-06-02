/*
 * =====================================================================================
 *
 *       Filename:  math_instructions.c
 *
 *    Description:  Constains functions needed for mathematical CPU instructions
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
	// For operations using 16-bit values
	unsigned short reg_hl = combine_registers(regs->H, regs->L);
	unsigned short value = 0;

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
			eight_bit_update_flags(regs->A, memory[reg_hl]);
			regs->A += memory[reg_hl];
			break;
		// 16-bit register cases
		case 0x09:
			value = combine_registers(regs->B, regs->C);
			sixteen_bit_update_flags(reg_hl, value);
			split_between_registers((reg_hl + value), &(regs->H), &(regs->L));
			break;
		case 0x19:
			value = combine_registers(regs->D, regs->E);
			sixteen_bit_update_flags(reg_hl, value);
			split_between_registers((reg_hl + value), &(regs->H), &(regs->L));
			break;
		case 0x29:
			sixteen_bit_update_flags(reg_hl, reg_hl);
			split_between_registers((reg_hl + reg_hl), &(regs->H), &(regs->L));
			break;
		case 0x39:
			value = ptrs->SP;
			sixteen_bit_update_flags(reg_hl, value);
			split_between_registers((reg_hl + value), &(regs->H), &(regs->L));
			break;
	}

	return;
}		/* -----  end of function add  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  adc
 *  Description:  Handles opcodes translating to ADC instructions
 * =====================================================================================
 */
        void
adc ()
{
        // Clear the N flag
        regs->F &= 0xB0;

	unsigned char sum = 0; // Total the operand and the carry flag
        sum += get_carry_flag();
	unsigned char reg_hl = combine_registers(regs->H, regs->L);

	// All operations update A, so just need to get sum
        switch (opcode)
        {
                case 0xCE:
                        ptrs->PC++;
                        sum += memory[ptrs->PC];
                        break;
		case 0x8E:
			sum += memory[reg_hl];
			break;
		case 0x8F:
			sum += regs->A;
			break;
		case 0x88:
			sum += regs->B;
			break;
		case 0x89:
			sum += regs->C;
			break;
		case 0x8A:
			sum += regs->D;
			break;
		case 0x8B:
			sum += regs->E;
			break;
		case 0x8C:
			sum += regs->H;
			break;
		case 0x8D:
			sum += regs->L;
			break;
	}

	// Update A and the flags
	eight_bit_update_flags(regs->A, sum);
	regs->A += sum;
			
        return;
}               /* -----  end of function adc  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sub
 *  Description:  Handles opcodes translating to SUB instructions
 * =====================================================================================
 */
	void
sub ()
{
	// Set the subtract flag
	regs->F |= 0x40;

	// Minuend is always register A
	unsigned char subtrahend;
	
	switch (opcode)
	{
		case 0xD6:
			ptrs->PC++;
			subtrahend = memory[ptrs->PC];
			break;
		case 0x90:
			subtrahend = regs->B;
			break;
		case 0x91:
			subtrahend = regs->C;
			break;
		case 0x92:
			subtrahend = regs->D;
			break;
		case 0x93:
			subtrahend = regs->E;
			break;
		case 0x94:
			subtrahend = regs->H;
			break;
		case 0x95:
			subtrahend = regs->L;
			break;
		case 0x97:
			subtrahend = regs->A;
			break;
	}
	
	// Update A and the flags
	eight_bit_update_flags(regs->A, subtrahend);
	regs->A -= subtrahend;

	return;
}		/* -----  end of function sub  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sbc
 *  Description:  Handles opcodes translating to SBC instructions
 * =====================================================================================
 */
	void
sbc ()
{
	// Set the N flag
        regs->F |= 0x40;

        unsigned char subtrahend = 0; // Total the operand and the carry flag
        subtrahend += get_carry_flag();
        unsigned char reg_hl = combine_registers(regs->H, regs->L);

        // All operations update A, so just need to get sum
        switch (opcode)
        {
                case 0xDE:
                        ptrs->PC++;
                        subtrahend += memory[ptrs->PC];
                        break;
                case 0x9E:
                        subtrahend += memory[reg_hl];
                        break;
                case 0x9F:
                        subtrahend += regs->A;
                        break;
                case 0x98:
                        subtrahend += regs->B;
                        break;
                case 0x99:
                        subtrahend += regs->C;
                        break;
                case 0x9A:
                        subtrahend += regs->D;
                        break;
                case 0x9B:
                        subtrahend += regs->E;
                        break;
                case 0x9C:
                        subtrahend += regs->H;
                        break;
                case 0x9D:
                        subtrahend += regs->L;
                        break;
        }

        // Update A and the flags
        eight_bit_update_flags(regs->A, subtrahend);
        regs->A -= subtrahend;

	return;
}		/* -----  end of function sbc  ----- */
