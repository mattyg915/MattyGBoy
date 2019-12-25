/*
 * =====================================================================================
 *
 *       Filename:  bit_rotate_shift_instructions.c
 *
 *    Description:  Contains functions needed for bit test, rotate, and shift cpu
 *    		    instructions
 *
 *        Version:  1.0
 *        Created:  06/03/2018 17:14:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *
 * =====================================================================================
 */
#include <math.h>
#include "global_declarations.h"
#include "helper_functions.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rlc
 *  Description:  Handles all RLC instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
        void
rlc (unsigned char *reg)
{
	// Clears N and H flags
	flags->N = 0x0; flags->H = 0x0;

	// Each bit of A shifts left one with bit 7 shifting
	// into C AND bit 0
	flags->C = *reg >> 0x7u;
	*reg <<= 0x1u;
	*reg |= flags->C; // Bit 0 is 0, since it's been filled in for the shift
	flags->Z = (unsigned char) (*reg == 0x0 ? 0x1 : 0x0);
}               /* -----  end of function rlc  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rl
 *  Description:  Handles all RL instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
        void
rl (unsigned char *reg)
{
	// Clears N and H flags
	flags->N = 0; flags->H = 0;
	// Each bit of register shifts left one with bit 0 shifting
	// into C and C going into bit 7
	unsigned char initial_c = flags->C;
	flags->C = *reg >> 0x7u;
	*reg <<= 0x1u;
	*reg |= initial_c;
	flags->Z = (unsigned char) ((*reg == 0) ? 1 : 0);
}               /* -----  end of function rl  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  rr
 *  Description:  Handles all RR instructions
 *   Parameters:  reg is a pointer to the register to be rotated
 * =====================================================================================
 */
        void
rr (unsigned char *reg)
{
	// Clears N and H flags
	flags->N = 0; flags->H = 0;

	// Each bit of register shifts right one with bit 0 shifting
	// into C and C goes into bit 7
	unsigned char initial_c = flags->C;
	flags->C = (unsigned char) (*reg & 0x1u);
	*reg >>= 0x1u;
	*reg |= (unsigned char)(initial_c << 0x7u);
	flags->Z = (unsigned char) ((*reg == 0) ? 1 : 0);
}               /* -----  end of function rr  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  rrc
 *  Description:  Handles all RRC instructions
 *   Parameters:  reg is a pointer to the register or memory location to be rotated
 * =====================================================================================
 */
	void
rrc (unsigned char *reg)
{
	// Clears N and H flags
	flags->N = 0; flags->H = 0;

	// Each bit of register shifts right one with bit 0 shifting
	// into C AND bit 7
	flags->C = (unsigned char) (*reg & 0x1u);
	*reg >>= 0x1u;
	*reg |= (unsigned char)(flags->C << 0x7u);
	flags->Z = (unsigned char) ((*reg == 0) ? 1 : 0);
}		/* -----  end of function rrc  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sla
 *  Description:  Handles SLA instructions
 *   Parameters:  reg is a pointer to the register/memory location to be shifted
 * =====================================================================================
 */
	void
sla (unsigned char *reg)
{
	// N and H are cleared, C and Z set by result
	flags->N = 0; flags->H = 0;
	flags->C = (unsigned char) ((unsigned short) *reg << 0x1u > 0xFF ? 0x1 : 0x0);

	*reg <<= 0x1u;

	flags->Z = (unsigned char) ((*reg) ? 0 : 1);
}		/* -----  end of function sla  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  sra
 *  Description:  Handles SRA instructions
 *   Parameters:  reg is a pointer to the register/memory location to be shifted
 * =====================================================================================
 */
        void
sra (unsigned char *reg)
{
	// N and H are cleared, C and Z set by result
    flags->N = 0; flags->H = 0;
    flags->C = (unsigned char) ((unsigned short) *reg >> 0x1u > 0xFF ? 0x1 : 0x0);

	// Need to convert the register to signed value so it will shift arithmetically
	char reg_value = (char)(*reg);
	reg_value >>= 1; // NOLINT
	*reg = (unsigned char) reg_value;

	flags->Z = (unsigned char) ((*reg) ? 0 : 1);
}               /* -----  end of function sra  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  swap
 *  Description:  Handles SWAP instructions
 *   Parameters:  reg is a pointer to the register/memory location to be swapped
 * =====================================================================================
 */
        void
swap (unsigned char *reg)
{
	unsigned char low_nibble = (unsigned char) (*reg & 0xFu);
	
	// Shift upper nibble to lower position
	*reg >>= 0x4u;
	// And add back left-shifted lower nibble
	*reg += (low_nibble << 0x4u);
}               /* -----  end of function swap  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  srl
 *  Description:  Handles SRL instructions
 *   Parameters:  reg is a pointer to the register/memory location to be shifted
 * =====================================================================================
 */
        void
srl (unsigned char *reg)
{
	// N and H are cleared, C and Z set by result
    flags->N = 0x0u; flags->H = 0x0u;
    flags->C = (unsigned char) ((unsigned short) (*reg) << 0x1u > 0xFF ? 0x1u : 0x0u);

	*reg >>= 0x1u;
        
	flags->Z = (unsigned char) ((*reg) ? 0x0 : 0x1);
}               /* -----  end of function srl  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bit
 *  Description:  Handles BIT instructions
 *   Parameters:  reg is a pointer to the register/memory location to be bit tested
 * =====================================================================================
 */
        void
bit (const unsigned char *reg)
{
	// Bit to test is a function of the opcode
	unsigned char bitmask = (unsigned char) ((opcode - 0x40) / 0x8);
	bitmask = (unsigned char)pow(2, bitmask);

	// BIT sets N to 0, H to 1
	flags->N = 0x0; flags->H = 0x1;

	// Z is 0 if bit is not 0, else 1
	flags->Z = (unsigned char) ((*reg & bitmask) ? 0x0 : 0x1);
}               /* -----  end of function bit  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  res
 *  Description:  Handles RES instructions; No flags are affected
 *   Parameters:  reg is a pointer to the register/memory location to be bit reset
 * =====================================================================================
 */
        void
res (unsigned char *reg)
{
	unsigned char bitmask = (unsigned char) ((opcode - 0x40) / 0x8);
	bitmask ^= 0xFFu;

	// Set bit to 0
	*reg &= bitmask;
}               /* -----  end of function res  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  set
 *  Description:  Handles SET instructions; No flags are affected
 *   Parameters:  reg is a pointer to the register/memory location to be bit set
 * =====================================================================================
 */
        void
set (unsigned char *reg)
{
	unsigned char bit = (unsigned char) ((opcode - 0x40) / 0x8);
	
	// Set bit to 1
	*reg |= (unsigned char)pow(2, bit);
}               /* -----  end of function set  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  bit_rotate_shift
 *  Description:  Translates the much-abused CB opcode into its appropriate intsruction
 *  		      and calls executing function
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
bit_rotate_shift ()
{
	unsigned char cycles;
	// For ones where memory[HL] is needed
    unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	
	// The affected registers/memory depend on the 4 lsb of the opcode
	unsigned char *argument;
	unsigned char arg_nibble = (unsigned char) (opcode & 0xFu);

	switch (arg_nibble)
	{
		case 0x00:
		case 0x08:
			argument = &regs->B;
            cycles = 0x8;
			break;
		case 0x01:
		case 0x09:
			argument = &regs->C;
            cycles = 0x8;
			break;
		case 0x02:
		case 0x0A:
			argument = &regs->D;
            cycles = 0x8;
			break;
		case 0x03:
		case 0x0B:
			argument = &regs->E;
            cycles = 0x8;
			break;
		case 0x04:
		case 0x0C:
			argument = &regs->H;
            cycles = 0x8;
			break;
		case 0x05:
		case 0x0D:
			argument = &regs->L;
            cycles = 0x8;
			break;
		case 0x06:
		case 0x0E:
			argument = read_memory_ptr(reg_hl);
            cycles = 0x10;
			break;
		case 0x07:
		case 0x0F:
			argument = &regs->A;
            cycles = 0x8;
			break;
        default:
            return 0x0;
	}

	switch (opcode)
	{
		case 0x00 ... 0x07:
			rlc(argument);
			return cycles;
		case 0x08 ... 0x0F:
			rrc(argument);
			return cycles;
		case 0x10 ... 0x17:
			rl(argument);
			return cycles;
		case 0x18 ... 0x1F:
			rr(argument);
			return cycles;
		case 0x20 ... 0x27:
			sla(argument);
			return cycles;
		case 0x28 ... 0x2F:
			sra(argument);
			return cycles;
		case 0x30 ... 0x37:
			swap(argument);
			return cycles;
		case 0x38 ... 0x3F:
			srl(argument);
			return cycles;
		case 0x40 ... 0x7F:
			bit(argument);
			return cycles;
		case 0x80 ... 0xBF:
			res(argument);
			return cycles;
		case 0xC0 ... 0xFF:
			set(argument);
			return cycles;
		default:
			return 0x0 ;
	}
}		/* -----  end of function bit_rotate_shift  ----- */
