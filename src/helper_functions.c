/*
 * =====================================================================================
 *
 * 	Filename:  helper_functions.c
 *
 *   Description:  Contains definitions of functions to assist in repeated misc. tasks
 *   		   used throughout the program
 *
 *       Version:  1.0
 *       Created:  05/29/2018 09:33:27
 *      Revision:  none
 *      Compiler:  gcc
 *
 *        Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */
#include <time.h>
#include <stdio.h>
#include "helper_functions.h"
#include "register_structures.h"
#include "global_declarations.h"
#include "cpu_emulator.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  delay
 *  Description:  Handle timing of a much slower CPU by delaying execution on the 
 *  		  emulating system's CPU
 *  		  Credit: https://stackoverflow.com/questions/27447195/how-to-use-
 *  		  delay-function-in-c-using-codeblocks-13-12mingw
 *   Parameters:  mseconds is the number of milliseconds to delay
 * =====================================================================================
 */
	void
delay (unsigned int mseconds)
{
	clock_t goal = mseconds + clock();
    	while (goal > clock());

	return;
}		/* -----  end of function delay  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  dump_registers
 *  Description:  Prints the contents of the registers to the console
 * =====================================================================================
 */
	void
dump_registers()
{
	printf("Registers: A: %x B: %x C: %x D: %x E: %x"
			" H: %x L: %x\n", regs->A, regs->B,
			regs->C, regs->D, regs->E, regs->H, 
			regs->L);
	printf("Stack pointer: %x Program Counter: %x\n",
			ptrs->SP, ptrs->PC);
	printf("Flags: Z: %x N: %x H: %x C: %x Jumped: %x IME: %x\n\n",
			flags->Z, flags->N, flags->H, flags->C,
			flags->jumped, flags->IME);
	return;
}		/* -----  end of function dump_registers  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  combine_bytes
 *  Description:  Takes two 8-bit values and returns them as a single 16-bit value
 *   Parameters:  byte1 is an unsigned char that should occupy the 8 most 
 *   		  significant bits of the new value
 *                byte2 is an unsigned char that should occupy the lower-order 8 
 *                bits of the new value
 *       Return:  an unsigned short that is the concatenation of the passed values
 * =====================================================================================
 */
        unsigned short
combine_bytes(unsigned char byte1, unsigned char byte2)
{       
        unsigned short result = (unsigned short)byte1;
        result <<= 8;
        result += byte2;
        
        return result;
}       /* -----  end of function combine_registers  ----- */

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
