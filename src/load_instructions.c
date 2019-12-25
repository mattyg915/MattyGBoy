/*
 * =====================================================================================
 *
 *       Filename:  load_instructions.c
 *
 *    Description:  Contains functions to emulate load instructions
 *
 *        Version:  1.0
 *        Created:  06/09/2018 15:56:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include "global_declarations.h"
#include "memory.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  basic_ld
 *  Description:  Handles basic LD instructions for loading data between registers
 *  		      or between registers and memory[HL]
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
basic_ld ()
{
	unsigned char cycles = 0;

	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	// Pointers to locations to which to load data and the value to load
	unsigned char load_value;
	unsigned char *load_to;

	unsigned char left_operand = (unsigned char) ((opcode - 0x40) / 8);
	unsigned char right_operand = (unsigned char) ((opcode - 0x40) % 8);

	switch (right_operand)
        {
			case 0x0:
				load_value = regs->B;
				cycles += 0x2;
				break;
			case 0x1:
				load_value = regs->C;
				cycles += 0x2;
				break;
			case 0x2:
				load_value = regs->D;
				cycles += 0x2;
				break;
			case 0x3:
				load_value = regs->E;
				cycles += 0x2;
				break;
			case 0x4:
				load_value = regs->H;
				cycles += 0x2;
				break;
			case 0x5:
				load_value = regs->L;
				cycles += 0x2;
				break;
			case 0x6:
				load_value = read_memory(reg_hl);
				cycles += 0x6;
				break;
			case 0x7:
				load_value = regs->A;
				cycles += 0x2;
				break;
			default:
				printf("ERROR: Unable to determine value to load\n");
				load_value = 0x0;
				cycles += 0x0;
				break;
		}

	switch (left_operand)
	{
		case 0x0:
			load_to = &regs->B;
			cycles += 0x2;
			break;
		case 0x1:
			load_to = &regs->C;
			cycles += 0x2;
			break;
		case 0x2:
			load_to = &regs->D;
			cycles += 0x2;
			break;
		case 0x3:
			load_to = &regs->E;
			cycles += 0x2;
			break;
		case 0x4:
			load_to = &regs->H;
			cycles += 0x2;
			break;
		case 0x5:
			load_to = &regs->L;
			cycles += 0x2;
			break;
		case 0x6:
			// Write to memory
			write_memory(reg_hl, load_value);
			cycles += 0x6;
			return cycles;
		case 0x7:
			load_to = &regs->A;
			cycles += 0x2;
			break;
		default:
			load_to = 0x0;
			printf("ERROR: Unable to determine load location\n");
			cycles += 0x0;
			break;
	}

	*load_to = load_value;
	return cycles;
}		/* -----  end of function basic_ld  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_one_byte_imm
 *  Description:  Handles instructions to load 1-byte immediate value into reg/mem
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
load_one_byte_imm ()
{
    unsigned char cycles;

	// Immediate to load and place to load it to
	unsigned char imm = read_memory(ptrs->PC);
	ptrs->PC++;
	unsigned char *load_to;
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	int left_operand = opcode / 8;

	switch (left_operand)
	{
		case 0x0:
			load_to = &regs->B;
			cycles = 0x8;
			break;
		case 0x1:
			load_to = &regs->C;
			cycles = 0x8;
			break;
		case 0x2:
			load_to = &regs->D;
			cycles = 0x8;
			break;
		case 0x3:
			load_to = &regs->E;
			cycles = 0x8;
			break;
		case 0x4:
			load_to = &regs->H;
			cycles = 0x8;
			break;
		case 0x5:
			load_to = &regs->L;
			cycles = 0x8;
			break;
		case 0x6:
			// Write to memory
			write_memory(reg_hl, imm);
			cycles = 0xC;
			return cycles;
		case 0x7:
			load_to = &regs->A;
			cycles = 0x8;
			break;
		default:
			load_to = NULL;
			printf("ERROR: Unable to determine load location\n");
			cycles = 0x0;
			break;
	}

	*load_to = imm;
	return cycles;
}		/* -----  end of function load_one_byte_imm  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_from_to_mem
 *  Description:  Handles instructions to load value from memory at specified address
 *  		  	  into A and vice versa
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
load_from_to_mem ()
{
    unsigned char cycles;

	unsigned char mem_lo = read_memory(ptrs->PC);
	unsigned char mem_hi = read_memory((unsigned short) (ptrs->PC + 1));
	unsigned short addr = combine_bytes(mem_hi, mem_lo);

	switch (opcode)
	{
		case 0x0A:
			addr = combine_bytes(regs->B, regs->C);
			regs->A = read_memory(addr);
			cycles = 0x8;
			return cycles;
		case 0x1A:
			addr = combine_bytes(regs->D, regs->E);
			regs->A = read_memory(addr);
			cycles = 0x8;
			return cycles;
		case 0xFA:
			ptrs->PC += 0x2;
			regs->A = read_memory(addr);
			cycles = 0x10;
			return cycles;
		case 0x02:
			addr = combine_bytes(regs->B, regs->C);
			write_memory(addr, regs->A);
			cycles = 0x8;
			return cycles;
		case 0x12:
			addr = combine_bytes(regs->D, regs->E);
			write_memory(addr, regs->A);
			cycles = 0x8;
			return cycles;
		case 0xEA:
			ptrs->PC += 0x2;
			write_memory(addr, regs->A);
			cycles = 0x10;
			return cycles;
		default:
		    return 0x0;
	}
}		/* -----  end of function load_from_to_mem  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_hl
 *  Description:  Handles loads between A and HL with inc/dec
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
load_hl ()
{
    unsigned char cycles;
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0x22:
			write_memory(reg_hl, regs->A);
			reg_hl++;
			split_bytes(reg_hl, &regs->H, &regs->L);
			cycles = 0x8;
			return cycles;
		case 0x2A:
			regs->A = read_memory(reg_hl);
			reg_hl++;
			split_bytes(reg_hl, &regs->H, &regs->L);
			cycles = 0x8;
			return cycles;
		case 0x32:
			write_memory(reg_hl, regs->A);
			reg_hl--;
			split_bytes(reg_hl, &regs->H, &regs->L);
			cycles = 0x8;
			return cycles;
		case 0x3A:
			regs->A = read_memory(reg_hl);
			reg_hl--;
			split_bytes(reg_hl, &regs->H, &regs->L);
			cycles = 0x8;
			return cycles;
        	default:
        	    return 0x0;
    }
}		/* -----  end of function load_hl  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ld_hl_sp
 *  Description:  Handles loads between HL and SP
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
    unsigned char
ld_hl_sp ()
{
    unsigned char cycles;
    char offset;

    switch (opcode)
    {
        case 0xF8:
            offset = read_memory(ptrs->PC);
            ptrs->PC++;
            split_bytes(ptrs->SP + offset, &regs->H, &regs->L);
            cycles = 0xC;
            return cycles;
        case 0xF9:
            ptrs->SP = combine_bytes(regs->H, regs->L);
            cycles = 0x8;
            return cycles;
        default:
            return 0x0;
    }
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_load
 *  Description:  Handles instructions to load 16-bit values
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
sixteen_bit_load ()
{
    unsigned char cycles;
	unsigned char imm_lo = read_memory(ptrs->PC);
	ptrs->PC++;
	unsigned char imm_hi = read_memory(ptrs->PC);
	ptrs->PC++;

	unsigned char sp_lo, sp_hi;

	switch (opcode)
	{
		case 0x01:
		    regs->B = imm_hi;
		    regs->C = imm_lo;
		    cycles = 0xC;
			return cycles;
		case 0x08: // This one is obnoxious
			sp_lo = (unsigned char) ptrs->SP;
			sp_hi = (unsigned char) (ptrs->SP >> 0x8u);
			unsigned short addr = combine_bytes(imm_hi, imm_lo);
			write_memory(addr, sp_lo);
			addr++;
			write_memory(addr, sp_hi);
			cycles = 0x14;
			return cycles;
		case 0x11:
		    regs->D = imm_hi;
		    regs->E = imm_lo;
		    cycles = 0xC;
			return cycles;
		case 0x21:
		    regs->H = imm_hi;
		    regs->L = imm_lo;
		    cycles = 0xC;
			return cycles;
		case 0x31:
			ptrs->SP = combine_bytes(imm_hi, imm_lo);
			cycles = 0xC;
			return cycles;
        default:
            return 0x0;
    }
}		/* -----  end of function sixteen_bit_load  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_write_io
 *  Description:  Handles instructions to read/write to/from i/o ports
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
read_write_io ()
{
    unsigned char cycles;
	unsigned char imm;
	unsigned short addr;

	switch (opcode)
	{
		case 0xF0:
			imm = read_memory(ptrs->PC);
			ptrs->PC++;
			addr = (unsigned short) (imm + 0xFF00);
			regs->A = read_memory(addr);
			cycles = 0xC;
			return cycles;
	    case 0xE0:
			imm = read_memory(ptrs->PC);
			ptrs->PC++;
            addr = (unsigned short) (imm + 0xFF00);
			write_memory(addr, regs->A);
			cycles = 0xC;
			return cycles;
		case 0xF2:
			addr = (unsigned short) (regs->C + 0xFF00);
			regs->A = read_memory(addr);
			cycles = 0x8;
			return cycles;
		case 0xE2:
			addr = (unsigned short) (regs->C + 0xFF00);
			write_memory(addr, regs->A);
			cycles = 0x8;
			return cycles;
        default:
            return 0x0;
    }
}		/* -----  end of function read_write_io  ----- */
