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
#include "load_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  basic_ld
 *  Description:  Handles basic LD instructions for loading data between registers
 *  		  or between registers and memory[HL]
 * =====================================================================================
 */
	void
basic_ld ()
{
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	// Pointers to locations to which to load data and the value to load
	unsigned char load_value;
	unsigned char *load_to;

	unsigned char left_operand = (opcode - 0x40) / 8;
	unsigned char right_operand = (opcode - 0x40) % 8;

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
                        load_to = memory + reg_hl;
                        break;
		case 0x7:
                        load_to = &regs->A;
                        break;
	}

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
                        load_value = memory[reg_hl];
                        break;
                case 0x7:
                        load_value = regs->A;
                        break;
        }

	*load_to = load_value;

	return;
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
	unsigned char imm = memory[ptrs->PC + 1];
	unsigned char *load_to;
	unsigned short reg_hl = combine_bytes(regs->H, regs->L);
	unsigned char left_operand = opcode % 8;

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
                        load_to = memory + reg_hl;
                        break;
		case 0x7:
			load_to = &regs->A;
			break;
	}

	*load_to = imm;
	ptrs->PC++;

	return;
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
	unsigned short addr = 0;
	switch (opcode)
	{
		case 0x0A:
			addr = combine_bytes(regs->B, regs->C);
			regs->A = memory[addr];
			return;
		case 0x1A:
			addr = combine_bytes(regs->D, regs->E);
                        regs->A = memory[addr];
			return;
		case 0xFA:
			addr = combine_bytes(memory[ptrs->PC + 1], 
					memory[ptrs->PC + 2]);
			ptrs->PC += 2;
			regs->A = memory[addr];
			return;
		case 0x02:
			addr = combine_bytes(regs->B, regs->C);
			memory[addr] = regs->A;
			return;
		case 0x12:
			addr = combine_bytes(regs->D, regs->E);
			memory[addr] = regs->A;
			return;
		case 0xEA:
			addr = combine_bytes(memory[ptrs->PC + 1],
                                        memory[ptrs->PC + 2]);
                        ptrs->PC += 2;
			memory[addr] = regs->A;
			return;
	}

	return;
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
			memory[reg_hl] = regs->A;
			reg_hl++;
			split_between_registers(reg_hl, regs->H, regs->L);
			return;
		case 0x2A:
			regs->A = memory[reg_hl];
			reg_hl++;
                        split_between_registers(reg_hl, regs->H, regs->L);
			return;
		case 0x32:
			memory[reg_hl] = regs->A
			reg_hl--;
                        split_between_registers(reg_hl, regs->H, regs->L);
			return;
		case 0x3A:
			regs->A = memory[reg_hl];
			reg_hl--;
                        split_between_registers(reg_hl, regs->H, regs->L);
			return;
	}

	return;
}		/* -----  end of function load_hl  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_write_io
 *  Description:  Handles instructions to read/write to/from i/o ports
 * =====================================================================================
 */
	void
read_write_io ()
{
	return;
}		/* -----  end of function read_write_io  ----- */
