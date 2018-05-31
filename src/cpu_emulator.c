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

unsigned char opcode;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  combine_registers
 *  Description:  Takes the 8-bit values from 2 registers and returns them as a
 *                single 16-bit value
 *   Parameters:  reg1 is an unsigned char from the register that should occupy
 *                the 8 most significant bits of the new value
 *                reg2 is an unsigned char from the register that should occupy
 *                the lower-order 8 bits of the new value
 *       Return:  an unsigned short that is the concatenation of the passed values
 * =====================================================================================
 */
        unsigned short
combine_registers(unsigned char reg1, unsigned char reg2)
{
        unsigned short result = (unsigned short)reg1;
        // bit-shift reg1 8 to the left to get the 8 most significant bits
        result <<= 8;
        // Then just add reg2 to get the 8 least significant bits
        result += reg2;

        return result;
}	/* -----  end of function combine_registers  ----- */

/* ===  FUNCTION  ======================================================================
 *         Name:  split_between_registers
 *  Description:  Takes a 16-bit value and splits it between two 8-bit registers
 *   Parameters:  value is the 16-bit value to split
 *                reg1 is a pointer to the register where the higher-order bits should
 *                be placed
 *                reg2 is a pointer to the register where the lower-order bits should
 *                be placed
 * =====================================================================================
 */
        void
split_between_registers(unsigned short value,
                unsigned char *reg1, unsigned char *reg2)
{
        // Cast as a char to just grab the lower-order bits
        *reg2 = (unsigned char)value;
        // Shift the higher bits into the lower position then cast
        value >>= 8;
        *reg1 = (unsigned char)value;
}       /* -----  end of function split_between_registers  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  update_flags
 *  Description:  Handles updates to the F register after an instruction executes
 *  		  with flag implications
 *   Parameters:  value1 is the first operand of an arithmetic instruction
 *   		  value2 is the second operand in an arithmetic instruction
 *   		  and is **added** to value1 to get a check value
 *   		  z should be set to 1 to evaluate for z flag, else 0
 *   		  n should be set to 1 to evaluate for s flag, else 0
 *   		  h should be set to 1 to evaluate for h flag, else 0
 *   		  c should be set to 1 to evaluate for c flag, else 0
 * =====================================================================================
 */
	void
update_flags (int value1, int value2, int z, int n, int h, int c)
{
	// Set the z flag if last op yielded a 0
	if (z) 
	{
		if ((value1 + value2) == 0) 
		{
			regs->F //TODO;
		}
		else
		{
			regs->F //TODO;
		}
	}
	return;
}		/* -----  end of function update_flags  ----- */

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
		case 0xC6:
		case 0x80 ... 0x87:
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
		case 0xE8:
			add();
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

