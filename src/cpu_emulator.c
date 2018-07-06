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

unsigned char opcode;
unsigned int clock_cycles;
static unsigned short divider_counter = 0;

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

		// Half Carry Flag - subtraction
        if ((value1 & 0xF0u) == 0x0u) // NOLINT
        {
            flags->H = 0;
        }
		else if ((((value1 & 0xF0) - (value2 & 0xF)) & 0xF) > 0) //NOLINT
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
            if ((((value1 & 0x0FFF) + (value2 & 0x0FFF)) & 0x1000) == 0x1000) //NOLINT
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
            if ((value1 & 0xF000u) == 0x0u) // NOLINT
            {
                flags->H = 0;
            }
            if ((((value1 & 0xF000) - (value2 & 0x0FFF)) & 0xFFF) > 0) // NOLINT
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
    ptrs->PC++;
}               /* -----  end of function fetch  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  add_cycles
 *  Description:  Adds a specified amount of clock cycles to the counter
 *   Parameters:  cycles is the number of cycles to add
 * =====================================================================================
 */
    void
add_cycles (unsigned int cycles)
{
    clock_cycles += cycles;
}               /* -----  end of function fetch  ----- */

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
	unsigned short cycles;
	switch (opcode) {
		case 0x00: // NOP
            add_cycles(0x4);
			return;
			// Rotate A instructions
		case 0x0F:
			rrc(&regs->A);
			flags->Z = 0; // Z flag always cleared
			add_cycles(0x4);
			return;
		case 0x1F:
			rr(&regs->A);
			flags->Z = 0; // Z flag always cleared
			add_cycles(0x4);
			return;
		case 0x07:
			rlc(&regs->A);
			flags->Z = 0; // Z flag always cleared
			add_cycles(0x4);
			return;
		case 0x17:
			rl(&regs->A);
			flags->Z = 0; // Z flag always cleared
			add_cycles(0x4);
			return;
			// Bit test, rotate, and shift instructions
		case 0xCB:
			fetch();
			bit_rotate_shift();
			return;
			// Add instructions
			// 8-bit
		case 0xC6:
		case 0xE8:
		case 0x80 ... 0x87:
			eight_bit_add();
			return;
			// 16-bit
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
			sixteen_bit_add();
			return;
			// ADC instructions
		case 0xCE:
		case 0x88 ... 0x8F:
			adc();
			return;
			// AND instructions
		case 0xE6:
		case 0xA0 ... 0xA7:
			and();
			return;
			// SUB instructions
		case 0xD6:
		case 0x90 ... 0x97:
			sub();
			return;
			// SBC instructions
		case 0xDE:
		case 0x98 ... 0x9F:
			sbc();
			return;
			// 8-bit INC instructions
		case 0x34:
		case 0x3C:
		case 0x04:
		case 0x0C:
		case 0x14:
		case 0x1C:
		case 0x24:
		case 0x2C:
			eight_bit_inc();
			return;
			// 16-bit INC instructions
		case 0x03:
		case 0x13:
		case 0x23:
		case 0x33:
			sixteen_bit_inc();
			return;
			// 8-bit DEC instructions
		case 0x35:
		case 0x3D:
		case 0x05:
		case 0x0D:
		case 0x15:
		case 0x1D:
		case 0x25:
		case 0x2D:
			eight_bit_dec();
			return;
			// 16-bit DEC instructions
		case 0x0B:
		case 0x1B:
		case 0x2B:
		case 0x3B:
			sixteen_bit_dec();
			return;
			// OR instructions
		case 0xF6:
		case 0xB0 ... 0xB7:
			or();
			return;
			// XOR instructions
		case 0xEE:
		case 0xA8 ... 0xAF:
			xor();
			return;
			// DAA
		case 0x27:
			daa();
			return;
			// CPL
		case 0x2F:
			cpl();
			return;
			// CP instructions
		case 0xFE:
		case 0xB9 ... 0xBF:
			cp();
			return;
			// Jump instructions
		case 0xC3:
		case 0xE9:
		case 0xDA:
		case 0xD2:
		case 0xC2:
		case 0xCA:
			jp();
			return;
		case 0x18:
		case 0x38:
		case 0x30:
		case 0x20:
		case 0x28:
			jr();
			return;
			// Call and return instructions
		case 0xCD:
		case 0xDC:
		case 0xD4:
		case 0xC4:
		case 0xCC:
			call();
			return;
	    case 0xC8:
		case 0xC9:
		case 0xD8:
		case 0xD0:
		case 0xC0:
			ret();
			return;
		case 0xD9:
			reti();
			return;
		case 0xC7:
		case 0xCF:
		case 0xD7:
		case 0xDF:
		case 0xE7:
		case 0xEF:
		case 0xF7:
		case 0xFF:
			rst();
			return;
			// Load instructions
		case 0x40 ... 0x75:
		case 0x77 ... 0x7F:
			basic_ld();
			return;
		case 0xF8:
		case 0xF9:
			ld_hl_sp();
			return;
		case 0x22:
		case 0x2A:
		case 0x32:
		case 0x3A:
			load_hl();
			return;
		case 0x06:
		case 0x0E:
		case 0x16:
		case 0x1E:
		case 0x26:
		case 0x2E:
		case 0x36:
		case 0x3E:
			load_one_byte_imm();
			return;
		case 0x0A:
		case 0x1A:
		case 0xFA:
		case 0x02:
		case 0x12:
		case 0xEA:
			load_from_to_mem();
			return;
		case 0x01:
		case 0x08:
		case 0x11:
		case 0x21:
		case 0x31:
			sixteen_bit_load();
		case 0xF0:
		case 0xE0:
		case 0xF2:
		case 0xE2:
			read_write_io();
			return;
		case 0x76:
			halt();
			return;
		case 0xF3:
			di();
			return;
		case 0xFB:
			ei();
			return;
		case 0x10:
			stop();
			return;
		case 0xF1:
		case 0xC1:
		case 0xD1:
		case 0xE1:
			pop();
			return;
		case 0xC5:
		case 0xD5:
		case 0xE5:
		case 0xF5:
			push();
			return;
		case 0x3F:
			ccf();
			return;
		case 0x37:
			scf();
			return;
			// TODO: keep going!
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
    unsigned 
    fetch();
    decode();
}		/* -----  end of function cpu_execution  ----- */
