/*
 * =====================================================================================
 *
 *       Filename:  cpu_emulator.c
 *
 *    Description:  Contains functions used to emulate operations of the gameboy cpu
 *
 *        Version:  1.0
 *        Created:  05/29/2018 13:24:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "math_instructions.h"
#include "global_declarations.h"
#include "register_structures.h"
#include "cpu_emulator.h"
#include "logical_instructions.h"

unsigned char opcode;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  eight_bit_update_flags
 *  Description:  Handles updates to the Z, H, and C flags in the F register 
 *  		  after an eight-bit instruction executes. Assumes N flag has
 *  		  been set or cleared before this function is called
 *  		  
 *   Parameters:  value1 is the first operand of an arithmetic instruction
 *   		  value2 is the second operand in an arithmetic instruction
 * =====================================================================================
 */
	void
eight_bit_update_flags (int value1, int value2)
{
	int result;

	if ((regs->F & 0x40) == 0) // Checks that last op was addition
	{
		result = value1 + value2;
		/*
		 * Credit to StackOverflow user Tommy for the half-carry algorithm
		 * https://stackoverflow.com/questions/8868396/gbz80-what-constitutes
		 * -a-half-carry/
		 */
		if ((((value1 & 0xF) + (value2 & 0xF)) & 0x10) == 0x10)
		{
			regs->F |= 0x20;
		}
		else
		{
			regs->F &= 0xD0;
		}
		
		// Carry Flag - addition
		if (result > 0xFF)
		{
			regs->F |= 0x10;
		}
		else
		{
			regs->F &= 0xE0;
		}
	}
	// Otherwise it was a subtraction
	else
	{
		result = value1 - value2;

		// Half Carry Flag - subtraction
		if ((((value1 & 0xF) - (value2 & 0xF)) & 0x10) < 0)
		{
			regs->F |= 0x20;
		}
		else
		{
			regs->F &= 0xD0;
		}
		// Carry Flag - subtraction
		if (result < 0)
		{
			regs->F |= 0x10;
		}
		else
		{
			regs->F &= 0xE0;
		}
	}

	// Zero Flag
        if (!result)
        {
                regs->F |= 0x80;
        }
        else
        {
                regs->F &= 0x70; // Otherwise clear it
        }

	return;
}		/* -----  end of function eight_bit_update_flags  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_update_flags
 *  Description:  Handles updates to the Z, H, and C flags in the F register
 *                after a sixteen-bit instruction executes. Assumes N flag has
 *                been set or cleared before this function is called
 *
 *   Parameters:  value1 is the first operand of an arithmetic instruction
 *                value2 is the second operand in an arithmetic instruction
 * =====================================================================================
 */
        void
sixteen_bit_update_flags (int value1, int value2)
{
	int result;

        if ((regs->F & 0x40) == 0) // Checks that last op was addition
        {
                result = value1 + value2;

                // Half-Carry - addition
                if ((((value1 & 0x0FFF) + (value2 & 0x0FFF)) & 0x1000) == 0x1000)
                {
                        regs->F |= 0x20;
                }
                else
                {
                        regs->F &= 0xD0;
                }

                // Carry Flag - addition
                if (result > 0xFFFF)
                {
                        regs->F |= 0x10;
                }
                else
                {
                        regs->F &= 0xE0;
                }
        }
	// Otherwise it was a subtraction
        else
        {
                result = value1 - value2;

                // Half Carry Flag - subtraction
                if ((((value1 & 0x0FFF) - (value2 & 0x0FFF)) & 0x1000) < 0)
                {
                        regs->F |= 0x20;
                }
                else
                {
                        regs->F &= 0xD0;
                }
                // Carry Flag - subtraction
                if (result < 0)
                {
                        regs->F |= 0x10;
                }
                else
                {
                        regs->F &= 0xE0;
                }
        }

        // Zero Flag
        if (!result)
        {
                regs->F |= 0x80;
        }
        else
        {
                regs->F &= 0x70; // Otherwise clear it
        }

	return;
}		/* -----  end of function sixteen_bit_update_flags  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_carry_flag
 *  Description:  Returns 1 if the carry flag (bit 4 of the F register) is set,
 *  		  otherwise returns 0
 *      Returns:  1 or 0 based on whether the carry flag is set
 * =====================================================================================
 */
	unsigned char
get_carry_flag ()
{
	return regs->F & 0x10;
}		/* -----  end of function get_carry_flag  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_half_carry_flag
 *  Description:  Returns 1 if the half carry flag (bit 5 of the F register) is set,
 *                otherwise returns 0
 *      Returns:  1 or 0 based on whether the half carry flag is set
 * =====================================================================================
 */
	unsigned char
get_half_carry_flag ()
{
	return regs->F & 0x20;
}		/* -----  end of function get_half_carry_flag  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_subtract_flag
 *  Description:  Returns 1 if the subtract flag (bit 6 of the F register) is set,
 *                otherwise returns 0
 *      Returns:  1 or 0 based on whether the subtract flag is set
 * =====================================================================================
 */
	unsigned char
get_subtract_flag ()
{
	return regs->F & 0x40;
}		/* -----  end of function get_subtract_flag  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_zero_flag
 *  Description:  Returns 1 if the zero flag (bit 7 of the F register) is set,
 *                otherwise returns 0
 *      Returns:  1 or 0 based on whether the zero flag is set
 * =====================================================================================
 */
	unsigned char
get_zero_flag ()
{
	return regs->F & 0x80;
}		/* -----  end of function get_zero_flag  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  decode
 *  Description:  Takes the current opcode pointed to by PC and determines 
 *  		  its generalized instruction (e.g. this is a 'load' instruction), 
 *  		  then calls the appropriate method to further decode and emulate it
 * =====================================================================================
 */
	static void
decode ()
{
	// TODO: ALL the opcodes
	switch (opcode) {
		case 0x00: // NOP
			return;
		// Add instructions
			// 8-bit
		case 0xC6:
		case 0xE8:
		case 0x80 ... 0x87:
			eight_bit_add();
			break;
			// 16-bit
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
			sixteen_bit_add();
			break;
		// ADC instructions
		case 0xCE:
		case 0x88 ... 0x8D:
			adc();
			break;
		// AND instructions
		case 0xE6:
		case 0xA0 ... 0xA7:
			and();
			break;
		// SUB instructions
		case 0xD6:
		case 0x97:
		case 0x90 ... 0x95:
			sub();
			break;
		case 0xDE:
		case 0x98 ... 0x9F:
			sbc();
			break;
	}
	return;
}		/* -----  end of function decode  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fetch
 *  Description:  Sets the global variable opcode to the current instruction being
 *  		  executed by the CPU
 * =====================================================================================
 */
	static void
fetch ()
{
	opcode = memory[ptrs->PC];
	return;
}		/* -----  end of function fetch  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_execution
 *  Description:  Emulates the three primary functions of the CPU using associated 
 *  		  functions: fetch an opcode, decode it, execute it's instruction
 * =====================================================================================
 */
	void
cpu_execution ()
{
	fetch();
	decode();
	ptrs->PC++;
}		/* -----  end of function cpu_execution  ----- */

