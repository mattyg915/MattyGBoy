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
#include "logical_instructions.h"
#include "bit_rotate_shift_instructions.h"
#include "control_instructions.h"
#include "load_instructions.h"
#include "cpu_control_instructions.h"
#include "graphics.h"
#include "timers.h"

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
eight_bit_update_flags (unsigned char value1, unsigned char value2)
{
	int carry_test; // An int is needed for the algorithm to check for carry
	unsigned char zero_test; // Need 1 byte data to check zero because of overflow

	if (!flags->N) // Checks that last op was addition
	{
		carry_test = value1 + value2;
		zero_test = (unsigned char) value1 + (unsigned char) value2;
		/*
		 * Credit to StackOverflow user Tommy for the half-carry algorithm
		 * https://stackoverflow.com/questions/8868396/gbz80-what-constitutes
		 * -a-half-carry/
		 */
		if ((((value1 & 0xF) + (value2 & 0xF)) & 0x10) == 0x10) //NOLINT
		{
			flags->H = 1;
		}
		else
		{
			flags->H = 0;
		}
		
		// Carry Flag - addition
		if (carry_test > 0xFF)
		{
			flags->C = 1;
		}
		else
		{
			flags->C = 0;
		}
	}
	// Otherwise it was a subtraction
	else
	{
		carry_test = value1 - value2;
        zero_test = (unsigned char) value1 - (unsigned char) value2;

		// Half Carry Flag - subtraction TODO something is still broken here
        if (((value1 & 0xF) - (value2 & 0xF)) < 0) //NOLINT
        {
            flags->H = 1;
        }
        else
		{
			flags->H = 0;
		}
		// Carry Flag - subtraction
		if (carry_test < 0)
		{
			flags->C = 1;
		}
		else
		{
			flags->C = 0;
		}
	}

	    // Zero Flag
        if (!zero_test)
        {
                flags->Z = 1;
        }
        else
        {
                flags->Z &= 0; // Otherwise clear it NOLINT
        }
}		/* -----  end of function eight_bit_update_flags  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_update_flags
 *  Description:  Handles updates to the Z, H, and C flags
 *                after a sixteen-bit instruction executes. Assumes N flag has
 *                been set or cleared before this function is called
 *
 *   Parameters:  value1 is the first operand of an arithmetic instruction
 *                value2 is the second operand in an arithmetic instruction
 * =====================================================================================
 */
    void
sixteen_bit_update_flags (unsigned short value1, unsigned short value2)
{
	int carry_test;
	unsigned short zero_test;

        if (!flags->N) // If last op was addition
        {
            carry_test = value1 + value2;
            zero_test = (unsigned short) value1 + (unsigned short) value2;

            // Half-Carry - addition
            if ((((value1 & 0xFF) + (value2 & 0xFF)) & 0x100) == 0x100) //NOLINT
            {
                    flags->H = 1;
            }
            else
            {
                    flags->H = 0;
            }

            // Carry Flag - addition
            if (carry_test > 0xFFFF)
            {
                    flags->C = 1;
            }
            else
            {
                    flags->C = 0;
            }
        }
	    // Otherwise subtraction
        else
        {
            carry_test = value1 - value2;
            zero_test = (unsigned short) value1 - (unsigned short) value2;

            // Half Carry Flag - subtraction
            if (((value1 & 0xFF) - (value2 & 0xFF)) < 0) // NOLINT
            {
                    flags->H = 1;
            }
            else
            {
                    flags->H = 0;
            }
            // Carry Flag - subtraction
            if (carry_test < 0)
            {
                    flags->C = 1;
            }
            else
            {
                    flags->C = 0;
            }
        }

        // Zero Flag
        if (!zero_test)
        {
                flags->Z = 1;
        }
        else
        {
                flags->Z = 0; // Otherwise clear it
        }
}		/* -----  end of function sixteen_bit_update_flags  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fetch
 *      Returns:  The current opcode to execute
 * =====================================================================================
 */
	static unsigned char
fetch ()
{
    unsigned char opcode = read_memory(ptrs->PC);
    ptrs->PC++;
    return opcode;
}               /* -----  end of function fetch  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  request_interrupt
 *  Description:  Requests a cpu interrupt by setting the appropriate bit in mem addr
 *                  0xFF0F
 *
 *  Parameters:   bitSetter is an unsigned char used to set the appropriate bit for
 *                  the interrupt being requested
 * =====================================================================================
 */
     void
request_interrupt (unsigned char bitSetter)
{
    unsigned char req_reg = read_memory(0xFF0F);
    req_reg |= bitSetter;
    write_memory(0xFF0F, req_reg);
}               /* -----  end of function request_interrupt  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  decode
 *  Description:  Takes the current opcode pointed to by PC and determines 
 *  		  its generalized instruction (e.g. this is a 'load' instruction), 
 *  		  then calls the appropriate method to further decode and emulate it
 *   Parameters:  opcode is the opcode as an unsigned char to decode and execute
 *       Return:  The number of clock cycles used to execute the instruction
 * =====================================================================================
 */
	static unsigned char
decode (unsigned char opcode)
{
	switch (opcode) {
		case 0x00: // NOP
            return 0x4;
			// Rotate A instructions
		case 0x0F:
			rrc(&regs->A);
			flags->Z = 0; // Z flag always cleared
			return 0x4;
		case 0x1F:
			rr(&regs->A);
			flags->Z = 0; // Z flag always cleared
			return 0x4;
		case 0x07:
			rlc(&regs->A);
			flags->Z = 0; // Z flag always cleared
			return 0x4;
		case 0x17:
			rl(&regs->A);
			flags->Z = 0; // Z flag always cleared
			return 0x4;
			// Bit test, rotate, and shift instructions
		case 0xCB:
			opcode = fetch();
			return bit_rotate_shift(opcode);
			// Add instructions
			// 8-bit
		case 0xC6:
		case 0xE8:
		case 0x80 ... 0x87:
			return eight_bit_add(opcode);
			// 16-bit
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
			return sixteen_bit_add(opcode);
			// ADC instructions
		case 0xCE:
		case 0x88 ... 0x8F:
			return adc(opcode);
			// AND instructions
		case 0xE6:
		case 0xA0 ... 0xA7:
			return and(opcode);
			// SUB instructions
		case 0xD6:
		case 0x90 ... 0x97:
			return sub(opcode);
			// SBC instructions
		case 0xDE:
		case 0x98 ... 0x9F:
			return sbc(opcode);
			// 8-bit INC instructions
		case 0x34:
		case 0x3C:
		case 0x04:
		case 0x0C:
		case 0x14:
		case 0x1C:
		case 0x24:
		case 0x2C:
			return eight_bit_inc(opcode);
			// 16-bit INC instructions
		case 0x03:
		case 0x13:
		case 0x23:
		case 0x33:
			return sixteen_bit_inc(opcode);
			// 8-bit DEC instructions
		case 0x35:
		case 0x3D:
		case 0x05:
		case 0x0D:
		case 0x15:
		case 0x1D:
		case 0x25:
		case 0x2D:
			return eight_bit_dec(opcode);
			// 16-bit DEC instructions
		case 0x0B:
		case 0x1B:
		case 0x2B:
		case 0x3B:
			return sixteen_bit_dec(opcode);
			// OR instructions
		case 0xF6:
		case 0xB0 ... 0xB7:
			return or(opcode);
			// XOR instructions
		case 0xEE:
		case 0xA8 ... 0xAF:
			return xor(opcode);
			// DAA
		case 0x27:
			return daa();
			// CPL
		case 0x2F:
			return cpl();
			// CP instructions
		case 0xFE:
		case 0xB9 ... 0xBF:
			return cp(opcode);
			// Jump instructions
		case 0xC3:
		case 0xE9:
		case 0xDA:
		case 0xD2:
		case 0xC2:
		case 0xCA:
			return jp(opcode);
		case 0x18:
		case 0x38:
		case 0x30:
		case 0x20:
		case 0x28:
			return jr(opcode);
			// Call and return instructions
		case 0xCD:
		case 0xDC:
		case 0xD4:
		case 0xC4:
		case 0xCC:
			return call(opcode);
	    case 0xC8:
		case 0xC9:
		case 0xD8:
		case 0xD0:
		case 0xC0:
			return ret(opcode);
		case 0xD9:
			return reti();
		case 0xC7:
		case 0xCF:
		case 0xD7:
		case 0xDF:
		case 0xE7:
		case 0xEF:
		case 0xF7:
		case 0xFF:
			return rst(opcode);
			// Load instructions
		case 0x40 ... 0x75:
		case 0x77 ... 0x7F:
			return basic_ld(opcode);
		case 0xF8:
		case 0xF9:
			return ld_hl_sp(opcode);
		case 0x22:
		case 0x2A:
		case 0x32:
		case 0x3A:
			return load_hl(opcode);
		case 0x06:
		case 0x0E:
		case 0x16:
		case 0x1E:
		case 0x26:
		case 0x2E:
		case 0x36:
		case 0x3E:
			return load_one_byte_imm(opcode);
		case 0x0A:
		case 0x1A:
		case 0xFA:
		case 0x02:
		case 0x12:
		case 0xEA:
			return load_from_to_mem(opcode);
		case 0x01:
		case 0x08:
		case 0x11:
		case 0x21:
		case 0x31:
			return sixteen_bit_load(opcode);
		case 0xF0:
		case 0xE0:
		case 0xF2:
		case 0xE2:
			return read_write_io(opcode);
		case 0x76:
			return halt();
		case 0xF3:
			return di();
		case 0xFB:
			return ei();
		case 0x10:
			return stop();
		case 0xF1:
		case 0xC1:
		case 0xD1:
		case 0xE1:
			return pop(opcode);
		case 0xC5:
		case 0xD5:
		case 0xE5:
		case 0xF5:
			return push(opcode);
		case 0x3F:
			return ccf();
		case 0x37:
			return scf();
		default:
			exit(1);
	}
}		/* -----  end of function decode  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_execution
 *  Description:  Emulates the three primary functions of the CPU using associated
 *                functions: fetch an opcode, decode it, execute it's instruction
 *   Parameters:  mem is a pointer to the virtual memory
 * =====================================================================================
 */
    void
cpu_execution ()
{
    unsigned char cycles;

    unsigned char opcode = fetch();

    cycles = decode(opcode);

    update_timers(cycles);
    update_graphics(cycles);
}		/* -----  end of function cpu_execution  ----- */
