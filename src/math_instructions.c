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
	regs->F &= 0xB0;

	/* Grab the next byte in case an immediate value is needed
	 * but don't increment PC unless it's actually used */
	unsigned char value = memory[ptrs->PC + 1];

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		// Immediate value cases
		case 0xC6:
			ptrs->PC++;
			break;
		/* Oddball case. SP updated instead of A, so do all needed
		 * actions and return. Value is also signed, so check and set
		 * N flag if negative
		 */
		case 0xE8:
			if ((char)value < 0)
			{
				regs->F |= 0x40;
			}
			sixteen_bit_update_flags(ptrs->SP, (char)value);
			ptrs->SP += (char)value;
			ptrs->PC++;
			return;
		// 8-bit register cases
		case 0x80:
			value = regs->B;
			break;
		case 0x81:
			value = regs->C;
			break;
		case 0x82:
			value = regs->D;
			break;
		case 0x83:
			value = regs->E;
			break;
		case 0x84:
			value = regs->H;
			break;
		case 0x85:
			value = regs->L;
			break;
		case 0x87:
			value = regs->A;
			break;
		case 0x86:
			value = memory[reg_hl];
			break;
	}
	
	eight_bit_update_flags(regs->A, value);
	regs->A += value;

	return;
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
	// Left operand always HL
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	unsigned short value;

	switch (opcode)
	{
		case 0x09:
                        value = combine_bytes(regs->B, regs->C);
                        break;
                case 0x19:
                        value = combine_bytes(regs->D, regs->E);
                        break;
                case 0x29:
			value = reg_hl;
                        break;
                case 0x39:
                        value = ptrs->SP;
                        break;
        }

	sixteen_bit_update_flags(reg_hl, value);
	split_between_registers((reg_hl + value), &(regs->H), &(regs->L));

        return;
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
        regs->F &= 0xB0;

	unsigned char sum = 0; // Total the operand and the carry flag
        sum += get_carry_flag();
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

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
	// Set the N flag
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
		case 0x96:
			unsigned short addr = combine_registers(regs->H, regs->L);
			subtrahend = memory[addr];
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
        unsigned char reg_hl = combine_bytes(regs->H, regs->L);

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
	regs->F &= 0xB0;
	// Capture state of C flag so it can be preserved
	unsigned char c_flag = get_carry_flag();

	unsigned char initial_state; // Capture initial state for flag updates
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	switch (opcode)
	{
		case 0x34:
			initial_state = memory[reg_hl];
			memory[reg_hl]++;
			break;
		case 0x3C:
			initial_state = regs->A;
			regs->A++;
		        break;
		case 0x04:
			initial_state = regs->B;
			regs->B++;
		        break;
		case 0x0C:
			initial_state = regs->C;
			regs->C++;
		        break;
		case 0x14:
			initial_state = regs->D;
			regs->D++;
		        break;
		case 0x1C:
			initial_state = regs->E;
			regs->E++;
		        break;
		case 0x24:
			initial_state = regs->H;
			regs->H++;
		        break;
		case 0x2C:
			initial_state = regs->L;
			regs->L++;
		        break;
	}

	eight_bit_update_flags(initial_state, 1);

	// Restore C flag, this instruction doesn't set or clear it
	if (c_flag)
	{
		regs->F |= 0x10;
	}
	else
	{
		regs->F &= 0xE0;
	}

	return;
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
			split_between_registers(value, &regs->B, &regs->C);
			break;
		case 0x13:
			value = combine_bytes(regs->D, regs->E);
			value++;
			split_between_registers(value, &regs->D, &regs->E);
			break;
		case 0x23:
			value = combine_bytes(regs->L, regs->L);
			value++;
			split_between_registers(value, &regs->H, &regs->L);
			break;
		case 0x33:
			ptrs->SP++;
			break;
	}

	return;
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
        regs->F |= 0x40;

        // Capture state of C flag so it can be preserved
        unsigned char c_flag = get_carry_flag();

        unsigned char initial_state; // Capture initial state for flag updates
        unsigned short reg_hl = combine_bytes(regs->H, regs->L);
        switch (opcode)
        {
                case 0x35:
                        initial_state = memory[reg_hl];
                        memory[reg_hl]--;
                        break;
                case 0x3D:
                        initial_state = regs->A;
                        regs->A--;
                        break;
                case 0x05:
                        initial_state = regs->B;
                        regs->B--;
                        break;
                case 0x0D:
                        initial_state = regs->C;
                        regs->C--;
                        break;
                case 0x15:
                        initial_state = regs->D;
                        regs->D--;
                        break;
                case 0x1D:
                        initial_state = regs->E;
                        regs->E--;
                        break;
                case 0x25:
                        initial_state = regs->H;
                        regs->H--;
                        break;
                case 0x2D:
                        initial_state = regs->L;
                        regs->L--;
                        break;
        }
	
	// Restore C flag, this instruction doesn't set or clear it
        if (c_flag)
        {
                regs->F |= 0x10;
        }
        else
        {
                regs->F &= 0xE0;
        }


        eight_bit_update_flags(initial_state, 1);

	return;
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
                        split_between_registers(value, &regs->B, &regs->C);
                        break;
                case 0x1B:
                        value = combine_bytes(regs->D, regs->E);
                        value--;
                        split_between_registers(value, &regs->D, &regs->E);
                        break;
                case 0x2B:
                        value = combine_bytes(regs->L, regs->L);
                        value--;
                        split_between_registers(value, &regs->H, &regs->L);
                        break;
                case 0x3B:
                        ptrs->SP--;
                        break;
        }

	return;
}		/* -----  end of function sixteen_bit_dec  ----- */
