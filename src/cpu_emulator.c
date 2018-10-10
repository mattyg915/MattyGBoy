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
#include <stdio.h>
#include "math_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "logical_instructions.h"
#include "bit_rotate_shift_instructions.h"
#include "control_instructions.h"
#include "load_instructions.h"
#include "cpu_control_instructions.h"
#include "graphics.h"
#include "timers.h"

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
                flags->Z &= 0; // Otherwise clear it
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
sixteen_bit_update_flags (int value1, int value2)
{
	int carry_test;
	unsigned short zero_test;

        if (!flags->N) // If last op was addition
        {
            carry_test = value1 + value2;
            zero_test = (unsigned short) value1 + (unsigned short) value2;

            // Half-Carry - addition
            if ((((value1 & 0x00FF) + (value2 & 0x00FF)) & 0x1000) == 0x0100) //NOLINT
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
 *  Description:  Sets the global variable opcode to the current instruction being
 *                executed by the CPU
 * =====================================================================================
 */
	static void
fetch ()
{
    opcode = read_memory(ptrs->PC);
    //printf("opcode is %x\n", opcode);
    ptrs->PC++;
}               /* -----  end of function fetch  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  decode
 *  Description:  Takes the current opcode pointed to by PC and determines 
 *  		  its generalized instruction (e.g. this is a 'load' instruction), 
 *  		  then calls the appropriate method to further decode and emulate it
 *       Return:  The number of clock cycles used to execute the instruction
 * =====================================================================================
 */
	static unsigned char
decode ()
{
	unsigned char cycles;
	switch (opcode) {
		case 0x00: // NOP
            cycles = 0x4;
			return cycles;
			// Rotate A instructions
		case 0x0F:
			rrc(&regs->A);
			flags->Z = 0; // Z flag always cleared
			cycles = 0x4;
			return cycles;
		case 0x1F:
			rr(&regs->A);
			flags->Z = 0; // Z flag always cleared
			cycles = 0x4;
			return cycles;
		case 0x07:
			rlc(&regs->A);
			flags->Z = 0; // Z flag always cleared
			cycles = 0x4;
			return cycles;
		case 0x17:
			rl(&regs->A);
			flags->Z = 0; // Z flag always cleared
			cycles = 0x4;
			return cycles;
			// Bit test, rotate, and shift instructions
		case 0xCB:
			fetch();
			cycles = bit_rotate_shift();
			return cycles;
			// Add instructions
			// 8-bit
		case 0xC6:
		case 0xE8:
		case 0x80 ... 0x87:
			cycles = eight_bit_add();
			return cycles;
			// 16-bit
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
			cycles = sixteen_bit_add();
			return cycles;
			// ADC instructions
		case 0xCE:
		case 0x88 ... 0x8F:
			cycles = adc();
			return cycles;
			// AND instructions
		case 0xE6:
		case 0xA0 ... 0xA7:
			cycles = and();
			return cycles;
			// SUB instructions
		case 0xD6:
		case 0x90 ... 0x97:
			cycles = sub();
			return cycles;
			// SBC instructions
		case 0xDE:
		case 0x98 ... 0x9F:
			cycles = sbc();
			return cycles;
			// 8-bit INC instructions
		case 0x34:
		case 0x3C:
		case 0x04:
		case 0x0C:
		case 0x14:
		case 0x1C:
		case 0x24:
		case 0x2C:
			cycles = eight_bit_inc();
			return cycles;
			// 16-bit INC instructions
		case 0x03:
		case 0x13:
		case 0x23:
		case 0x33:
			cycles = sixteen_bit_inc();
			return cycles;
			// 8-bit DEC instructions
		case 0x35:
		case 0x3D:
		case 0x05:
		case 0x0D:
		case 0x15:
		case 0x1D:
		case 0x25:
		case 0x2D:
			cycles = eight_bit_dec();
			return cycles;
			// 16-bit DEC instructions
		case 0x0B:
		case 0x1B:
		case 0x2B:
		case 0x3B:
			cycles = sixteen_bit_dec();
			return cycles;
			// OR instructions
		case 0xF6:
		case 0xB0 ... 0xB7:
			cycles = or();
			return cycles;
			// XOR instructions
		case 0xEE:
		case 0xA8 ... 0xAF:
			cycles = xor();
			return cycles;
			// DAA
		case 0x27:
			cycles = daa();
			return cycles;
			// CPL
		case 0x2F:
			cycles = cpl();
			return cycles;
			// CP instructions
		case 0xFE:
		case 0xB9 ... 0xBF:
			cycles = cp();
			return cycles;
			// Jump instructions
		case 0xC3:
		case 0xE9:
		case 0xDA:
		case 0xD2:
		case 0xC2:
		case 0xCA:
			cycles = jp();
			return cycles;
		case 0x18:
		case 0x38:
		case 0x30:
		case 0x20:
		case 0x28:
			cycles = jr();
			return cycles;
			// Call and return instructions
		case 0xCD:
		case 0xDC:
		case 0xD4:
		case 0xC4:
		case 0xCC:
			cycles = call();
			return cycles;
	    case 0xC8:
		case 0xC9:
		case 0xD8:
		case 0xD0:
		case 0xC0:
			cycles = ret();
			return cycles;
		case 0xD9:
			cycles = reti();
			return cycles;
		case 0xC7:
		case 0xCF:
		case 0xD7:
		case 0xDF:
		case 0xE7:
		case 0xEF:
		case 0xF7:
		case 0xFF:
			cycles = rst();
			return cycles;
			// Load instructions
		case 0x40 ... 0x75:
		case 0x77 ... 0x7F:
			cycles = basic_ld();
			return cycles;
		case 0xF8:
		case 0xF9:
			cycles = ld_hl_sp();
			return cycles;
		case 0x22:
		case 0x2A:
		case 0x32:
		case 0x3A:
			cycles = load_hl();
			return cycles;
		case 0x06:
		case 0x0E:
		case 0x16:
		case 0x1E:
		case 0x26:
		case 0x2E:
		case 0x36:
		case 0x3E:
			cycles = load_one_byte_imm();
			return cycles;
		case 0x0A:
		case 0x1A:
		case 0xFA:
		case 0x02:
		case 0x12:
		case 0xEA:
			cycles = load_from_to_mem();
			return cycles;
		case 0x01:
		case 0x08:
		case 0x11:
		case 0x21:
		case 0x31:
			cycles = sixteen_bit_load();
			return cycles;
		case 0xF0:
		case 0xE0:
		case 0xF2:
		case 0xE2:
			cycles = read_write_io();
			return cycles;
		case 0x76:
			cycles = halt();
			return cycles;
		case 0xF3:
			cycles = di();
			return cycles;
		case 0xFB:
			cycles = ei();
			return cycles;
		case 0x10:
			cycles = stop();
			return cycles;
		case 0xF1:
		case 0xC1:
		case 0xD1:
		case 0xE1:
			cycles = pop();
			return cycles;
		case 0xC5:
		case 0xD5:
		case 0xE5:
		case 0xF5:
			cycles = push();
			return cycles;
		case 0x3F:
			cycles = ccf();
			return cycles;
		case 0x37:
			cycles = scf();
			return cycles;
		default:
			printf("ERROR: Invalid or unsupported opcode, %x, encountered\n", opcode);
			exit(1);
	}
}		/* -----  end of function decode  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_execution
 *  Description:  Emulates the three primary functions of the CPU using associated
 *                functions: fetch an opcode, decode it, execute it's instruction
 * =====================================================================================
 */
    void
cpu_execution ()
{
    unsigned char cycles;
    fetch();
    cycles = decode();

    // Pass reference to the counters since functions should change them
    update_timers(cycles);
    update_graphics(cycles);
    //dump_registers();
}		/* -----  end of function cpu_execution  ----- */
