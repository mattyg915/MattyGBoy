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
#include <stdio.h>
#include "math_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  eight_bit_add
 *  Description:  Handles opcodes translating to 8-bit ADD instructions
 * =====================================================================================
 */
	void
eight_bit_add ()
{
	// Clear the N flag
	flags->N = 0;

	// Hold the value to be added to A
	unsigned char value;

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0xC6:
			value = read_memory(ptrs->PC);
			ptrs->PC++;
            add_cycles(0x8);
			break;
		/* Oddball case. SP updated instead of A, so do all needed
		 * actions and return. Value is also signed, so check and set
		 * N flag if negative
		 */
		case 0xE8:
		    value = read_memory(ptrs->PC);
			flags->N = 0;
			// SP requires a 16-bit update
			sixteen_bit_update_flags(ptrs->SP, (char)value);
			flags->Z = 0;
			ptrs->SP += (char)value;
			ptrs->PC++;
            add_cycles(0x10);
			return;
		// 8-bit register cases
		case 0x80:
			value = regs->B;
			add_cycles(0x4);
			break;
		case 0x81:
			value = regs->C;
            add_cycles(0x4);
			break;
		case 0x82:
			value = regs->D;
            add_cycles(0x4);
			break;
		case 0x83:
			value = regs->E;
            add_cycles(0x4);
			break;
		case 0x84:
			value = regs->H;
            add_cycles(0x4);
			break;
		case 0x85:
			value = regs->L;
            add_cycles(0x4);
			break;
		case 0x87:
			value = regs->A;
            add_cycles(0x4);
			break;
		case 0x86:
			value = read_memory(reg_hl);
            add_cycles(0x8);
			break;
		default:
		    value = 0; // Error case
			break;
	}
	
	eight_bit_update_flags(regs->A, value);
	regs->A += value;
}		/* -----  end of function add  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_add
 *  Description:  Handles opcodes translating to 16-bit ADD instructions
 * =====================================================================================
 */
        void
sixteen_bit_add ()
{
	// Clear N
	flags->N = 0;
	// Preserve Z
	unsigned char initial_z = flags->Z;
	// Left operand always HL
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	unsigned short value;

	switch (opcode)
	{
		case 0x09:
			value = combine_bytes(regs->B, regs->C);
			add_cycles(0x8);
			break;
		case 0x19:
			value = combine_bytes(regs->D, regs->E);
			add_cycles(0x8);
			break;
		case 0x29:
			value = reg_hl;
			add_cycles(0x8);
			break;
		case 0x39:
			value = ptrs->SP;
			add_cycles(0x8);
			break;
		default:
			value = 0;
			break;
	}

	sixteen_bit_update_flags(reg_hl, value);
	flags->Z = initial_z;
	split_bytes((reg_hl + value), &(regs->H), &(regs->L));
}		/* -----  end of function sixteen_bit_add  ----- */
	

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
    flags->N = 0;

	unsigned char sum = 0; // Total the operand and the carry flag
    sum += flags->C;

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	// All operations update A, so just need to get sum
        switch (opcode)
        {
		case 0xCE:
			sum += read_memory(ptrs->PC);
			ptrs->PC++;
			add_cycles(0x8);
			break;
		case 0x8E:
			sum += read_memory(reg_hl);
			add_cycles(0x8);
			break;
		case 0x8F:
			sum += regs->A;
			add_cycles(0x4);
			break;
		case 0x88:
			sum += regs->B;
			add_cycles(0x4);
			break;
		case 0x89:
			sum += regs->C;
			add_cycles(0x4);
			break;
		case 0x8A:
			sum += regs->D;
			add_cycles(0x4);
			break;
		case 0x8B:
			sum += regs->E;
			add_cycles(0x4);
			break;
		case 0x8C:
			sum += regs->H;
			add_cycles(0x4);
			break;
		case 0x8D:
			sum += regs->L;
			add_cycles(0x4);
			break;
		default:
			break;
		}

	// Update A and the flags
	eight_bit_update_flags(regs->A, sum);
	regs->A += sum;
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
	// Set the N flag
	flags->N = 1;

	// Minuend is always register A
	unsigned char subtrahend;
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0xD6:
			subtrahend = read_memory(ptrs->PC);
            ptrs->PC++;
            add_cycles(0x8);
			break;
		case 0x90:
			subtrahend = regs->B;
			add_cycles(0x4);
			break;
		case 0x91:
			subtrahend = regs->C;
			add_cycles(0x4);
			break;
		case 0x92:
			subtrahend = regs->D;
			add_cycles(0x4);
			break;
		case 0x93:
			subtrahend = regs->E;
			add_cycles(0x4);
			break;
		case 0x94:
			subtrahend = regs->H;
			add_cycles(0x4);
			break;
		case 0x95:
			subtrahend = regs->L;
			add_cycles(0x4);
			break;
		case 0x96:
			subtrahend = read_memory(reg_hl);
			add_cycles(0x8);
			break;
		case 0x97:
			subtrahend = regs->A;
			add_cycles(0x4);
			break;
		default:
			subtrahend = 0;
			break;
	}
	
	// Update A and the flags
	eight_bit_update_flags(regs->A, subtrahend);
	regs->A -= subtrahend;
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
    flags->N = 1;

    unsigned char subtrahend = 0; // Total the operand and the carry flag
    subtrahend += flags->C;
    unsigned short reg_hl = combine_bytes(regs->H, regs->L);

    // All operations update A, so just need to get sum
    switch (opcode)
    {
        case 0xDE:
            subtrahend += read_memory(ptrs->PC);
            ptrs->PC++;
            add_cycles(0x8);
            break;
        case 0x9E:
            subtrahend += read_memory(reg_hl);
			add_cycles(0x8);
            break;
        case 0x9F:
            subtrahend += regs->A;
			add_cycles(0x4);
            break;
        case 0x98:
            subtrahend += regs->B;
			add_cycles(0x4);
            break;
        case 0x99:
            subtrahend += regs->C;
			add_cycles(0x4);
            break;
        case 0x9A:
            subtrahend += regs->D;
			add_cycles(0x4);
            break;
        case 0x9B:
            subtrahend += regs->E;
			add_cycles(0x4);
            break;
        case 0x9C:
            subtrahend += regs->H;
			add_cycles(0x4);
            break;
        case 0x9D:
            subtrahend += regs->L;
			add_cycles(0x4);
            break;
        default:
            break;
    }

    // Update A and the flags
    eight_bit_update_flags(regs->A, subtrahend);
    regs->A -= subtrahend;
}		/* -----  end of function sbc  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  eight_bit_inc
 *  Description:  Handles opcodes translating to an 8-bit INC instruction
 * =====================================================================================
 */
	void
eight_bit_inc ()
{
	// Clear N flag
	flags->N = 0;

	// Capture state of C flag so it can be preserved
	unsigned char c_flag = flags->C;

	unsigned char initial_state; // Capture initial state for flag updates
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	switch (opcode)
	{
		case 0x34:
			initial_state = read_memory(reg_hl);
			write_memory(reg_hl, (unsigned char) (initial_state + 1));
			add_cycles(0xC);
			break;
		case 0x3C:
			initial_state = regs->A;
			add_cycles(0x4);
			regs->A++;
			break;
		case 0x04:
			initial_state = regs->B;
			add_cycles(0x4);
			regs->B++;
			break;
		case 0x0C:
			initial_state = regs->C;
			add_cycles(0x4);
			regs->C++;
			break;
		case 0x14:
			initial_state = regs->D;
			add_cycles(0x4);
			regs->D++;
			break;
		case 0x1C:
			initial_state = regs->E;
			add_cycles(0x4);
			regs->E++;
			break;
		case 0x24:
			initial_state = regs->H;
			add_cycles(0x4);
			regs->H++;
			break;
		case 0x2C:
			initial_state = regs->L;
			add_cycles(0x4);
			regs->L++;
			break;
		default:
			initial_state = 0;
			break;
	}

	eight_bit_update_flags(initial_state, 1);

	// Restore C flag, this instruction doesn't set or clear it
	flags->C = c_flag;
}		/* -----  end of function eight_bit_inc  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_inc
 *  Description:  Handles opcodes translating to 16-bit INC instructions
 *  		  This instruction does not affect flags
 * =====================================================================================
 */
	void
sixteen_bit_inc ()
{
	unsigned short value;
	switch (opcode)
	{
		case 0x03:
			value = combine_bytes(regs->B, regs->C);
			value++;
			split_bytes(value, &regs->B, &regs->C);
			add_cycles(0x8);
			break;
		case 0x13:
			value = combine_bytes(regs->D, regs->E);
			value++;
			split_bytes(value, &regs->D, &regs->E);
			add_cycles(0x8);
			break;
		case 0x23:
			value = combine_bytes(regs->L, regs->L);
			value++;
			split_bytes(value, &regs->H, &regs->L);
			add_cycles(0x8);
			break;
		case 0x33:
			ptrs->SP++;
			break;
		default:
			break;
	}
}		/* -----  end of function sixteen_bit_inc  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  eight_bit_dec
 *  Description:  Handles opcodes translating to 8-bit DEC instructions
 * =====================================================================================
 */
	void
eight_bit_dec ()
{
    // Set N flag
    flags->N = 1;

    // Capture state of C flag so it can be preserved
    unsigned char c_flag = flags->C;

    unsigned char initial_state; // Capture initial state for flag updates
    unsigned short reg_hl = combine_bytes(regs->H, regs->L);
    switch (opcode)
    {
        case 0x35:
            initial_state = read_memory(reg_hl);
            write_memory(reg_hl, (unsigned char) (initial_state - 1));
			add_cycles(0xC);
            break;
        case 0x3D:
            initial_state = regs->A;
            regs->A--;
			add_cycles(0x4);
            break;
        case 0x05:
            initial_state = regs->B;
            regs->B--;
			add_cycles(0x4);
            break;
        case 0x0D:
            initial_state = regs->C;
            regs->C--;
			add_cycles(0x4);
            break;
        case 0x15:
            initial_state = regs->D;
            regs->D--;
			add_cycles(0x4);
            break;
        case 0x1D:
            initial_state = regs->E;
            regs->E--;
			add_cycles(0x4);
            break;
        case 0x25:
            initial_state = regs->H;
            regs->H--;
			add_cycles(0x4);
            break;
        case 0x2D:
            initial_state = regs->L;
            regs->L--;
			add_cycles(0x4);
            break;
        default:
            initial_state = 0;
            break;
    }

    eight_bit_update_flags(initial_state, 1);

    // Restore C flag, this instruction doesn't set or clear it
    flags->C = c_flag;
}		/* -----  end of function eight_bit_dec  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_dec
 *  Description:  Handles opcodes translating to 16-bit DEC instructions
 *  		  This instruction does not affect flags
 * =====================================================================================
 */
	void
sixteen_bit_dec ()
{
	unsigned short value;
        switch (opcode)
        {
			case 0x0B:
				value = combine_bytes(regs->B, regs->C);
				value--;
				split_bytes(value, &regs->B, &regs->C);
				add_cycles(0x8);
				break;
			case 0x1B:
				value = combine_bytes(regs->D, regs->E);
				value--;
				split_bytes(value, &regs->D, &regs->E);
				add_cycles(0x8);
				break;
			case 0x2B:
				value = combine_bytes(regs->L, regs->L);
				value--;
				split_bytes(value, &regs->H, &regs->L);
				add_cycles(0x8);
				break;
			case 0x3B:
				ptrs->SP--;
				break;
			default:
				break;
		}
}		/* -----  end of function sixteen_bit_dec  ----- */
