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
