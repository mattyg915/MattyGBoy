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
#include "load_instructions.h"
#include "global_declarations.h"
#include "memory.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  basic_ld
 *  Description:  Handles basic LD instructions for loading data between registers
 *  		      or between registers and memory[HL]
 * =====================================================================================
 */
	void
basic_ld ()
{
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
				break;
			case 0x1:
				load_value = regs->C;
				break;
			case 0x2:
				load_value = regs->D;
				break;
			case 0x3:
				load_value = regs->E;
				break;
			case 0x4:
				load_value = regs->H;
				break;
			case 0x5:
				load_value = regs->L;
				break;
			case 0x6:
				load_value = read_memory(reg_hl);
				break;
			case 0x7:
				load_value = regs->A;
				break;
			default:
				printf("ERROR: Unable to determine value to load\n");
				load_value = 0;
				break;
		}

	switch (left_operand)
	{
		case 0x0:
			load_to = &regs->B;
			break;
		case 0x1:
			load_to = &regs->C;
			break;
		case 0x2:
			load_to = &regs->D;
			break;
		case 0x3:
			load_to = &regs->E;
			break;
		case 0x4:
			load_to = &regs->H;
			break;
		case 0x5:
			load_to = &regs->L;
			break;
		case 0x6:
			// Write to memory
			write_memory(reg_hl, load_value);
			return;
		case 0x7:
			load_to = &regs->A;
			break;
		default:
			load_to = 0;
			printf("ERROR: Unable to determine load location\n");
			break;
	}

	*load_to = load_value;
}		/* -----  end of function basic_ld  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_one_byte_imm
 *  Description:  Handles instructions to load 1-byte immediate value into reg/mem
 * =====================================================================================
 */
	void
load_one_byte_imm ()
{
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
			break;
		case 0x1:
			load_to = &regs->C;
			break;
		case 0x2:
			load_to = &regs->D;
			break;
		case 0x3:
			load_to = &regs->E;
			break;
		case 0x4:
			load_to = &regs->H;
			break;
		case 0x5:
			load_to = &regs->L;
			break;
		case 0x6:
			// Write to memory
			write_memory(reg_hl, imm);
			return;
		case 0x7:
			load_to = &regs->A;
			break;
		default:
			load_to = NULL;
			printf("ERROR: Unable to determine load location\n");
			break;
	}

	*load_to = imm;
}		/* -----  end of function load_one_byte_imm  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_from_to_mem
 *  Description:  Handles instructions to load value from memory at specified address
 *  		  into A and vice versa
 * =====================================================================================
 */
	void
load_from_to_mem ()
{

	unsigned char mem_lo = read_memory(ptrs->PC);
	unsigned char mem_hi = read_memory((unsigned short) (ptrs->PC + 1));
	unsigned short addr = combine_bytes(mem_lo, mem_hi);

	unsigned char val;

	switch (opcode)
	{
		case 0x0A:
			addr = combine_bytes(regs->B, regs->C);
			val = read_memory(addr);
			regs->A = val;
			return;
		case 0x1A:
			addr = combine_bytes(regs->D, regs->E);
			val = read_memory(addr);
			regs->A = val;
			return;
		case 0xFA:
			ptrs->PC += 2;
			val = read_memory(addr);
			regs->A = val;
			return;
		case 0x02:
			addr = combine_bytes(regs->B, regs->C);
			write_memory(addr, regs->A);
			return;
		case 0x12:
			addr = combine_bytes(regs->D, regs->E);
			write_memory(addr, regs->A);
			return;
		case 0xEA:
			ptrs->PC += 2;
			write_memory(addr, regs->A);
			return;
		default:
			break;
	}
}		/* -----  end of function load_from_to_mem  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_hl
 *  Description:  Handles loads between A and HL with inc/dec 
 * =====================================================================================
 */
	void
load_hl ()
{
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);

	switch (opcode)
	{
		case 0x22:
			write_memory(reg_hl, regs->A);
			reg_hl++;
			split_bytes(reg_hl, &regs->H, &regs->L);
			return;
		case 0x2A:
			regs->A = read_memory(reg_hl);
			reg_hl++;
            		split_bytes(reg_hl, &regs->H, &regs->L);
			return;
		case 0x32:
			write_memory(reg_hl, regs->A);
			reg_hl--;
            		split_bytes(reg_hl, &regs->H, &regs->L);
			return;
		case 0x3A:
            		regs->A = read_memory(reg_hl);
			reg_hl--;
            		split_bytes(reg_hl, &regs->H, &regs->L);
			return;
        	default:
            		break;
    }
}		/* -----  end of function load_hl  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ld_hl_sp
 *  Description:  Handles loads between HL and SP
 * =====================================================================================
 */
    void
ld_hl_sp ()
{
    unsigned char offset;

    switch (opcode)
    {
        case 0xF8:
            offset = read_memory(ptrs->PC);
            ptrs->PC++;
            split_bytes(ptrs->SP + offset, &regs->H, &regs->L);
            return;
        case 0xF9:
            ptrs->SP = combine_bytes(regs->H, regs->L);
            return;
        default:
            return;
    }
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  sixteen_bit_load
 *  Description:  Handles instructions to load 16-bit values
 * =====================================================================================
 */
	void
sixteen_bit_load ()
{
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
			break;
		case 0x08: // This one is obnoxious
			sp_lo = (unsigned char) ptrs->SP;
			sp_hi = (unsigned char ) (ptrs->SP >> 0x8u);
			write_memory(imm_hi, sp_hi);
			write_memory(imm_lo, sp_lo);
			break;
		case 0x11:
		    regs->D = imm_hi;
		    regs->E = imm_lo;
			break;
		case 0x21:
		    regs->H = imm_hi;
		    regs->L = imm_lo;
			break;
		case 0x31:
			ptrs->SP = combine_bytes(imm_hi, imm_lo);
			break;
        default:
            break;
    }
}		/* -----  end of function sixteen_bit_load  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_write_io
 *  Description:  Handles instructions to read/write to/from i/o ports
 * =====================================================================================
 */
	void
read_write_io ()
{

	unsigned char imm;
	unsigned short addr;

	switch (opcode)
	{
		case 0xF0:
			imm = read_memory(ptrs->PC);
			ptrs->PC++;
			imm += 0xFF00;
			regs->A = imm;
			return;
		case 0xE0:
			imm = read_memory(ptrs->PC);
			ptrs->PC++;
            		imm += 0xFF00;
			write_memory(imm, regs->A);
			return;
		case 0xF2:
			addr = (unsigned short) (regs->C + 0xFF00);
			imm = read_memory(addr);
			regs->A = imm;
			return;
		case 0xE2:
			addr = (unsigned short) (regs->C + 0xFF00);
			write_memory(addr, regs->A);
			return;
        default:
            break;
    }
}		/* -----  end of function read_write_io  ----- */
