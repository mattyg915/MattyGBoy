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
	unsigned short AF = regs->A << 0x8u;
	AF += (flags->Z << 0x7u); AF += (flags->N << 0x6u);
	AF += (flags->H << 0x5u); AF += (flags->C << 0x4u);
	unsigned short BC = combine_bytes(regs->B, regs->C);
	unsigned short DE = combine_bytes(regs->D, regs->E);
	unsigned short HL = combine_bytes(regs->H, regs->L);

	printf("Registers:\nAF: %x\nBC: %x\nDE: %x\nHL: %x\n", AF, BC, DE, HL);
	printf("Stack pointer: %x Program Counter: %x\n",
			ptrs->SP, ptrs->PC);
	printf("Flags: Z: %x N: %x H: %x C: %x\n\n",
			flags->Z, flags->N, flags->H, flags->C);
}		/* -----  end of function dump_registers  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  combine_bytes
 *  Description:  Takes two 8-bit values and returns them as a single 16-bit value
 *   Parameters:  byte1 is an unsigned char that should occupy the 8 most 
 *   		      significant bits of the new value
 *                byte2 is an unsigned char that should occupy the lower-order 8 
 *                bits of the new value
 *       Return:  an unsigned short that is the concatenation of the passed values
 * =====================================================================================
 */
        unsigned short
combine_bytes(unsigned char byte1, unsigned char byte2)
{       
    unsigned short result = 0;
    result += byte1;
    result <<= 8;
    result += byte2;

    return result;
}       /* -----  end of function combine_registers  ----- */

/* ===  FUNCTION  ======================================================================
 *         Name:  split_bytes
 *  Description:  Takes a 16-bit value and splits it between two 8-bit locations
 *  		  When using a location in virtual memory, addr1 should be the higher-
 *  		  numbered memory address, as GB is little-endian
 *   Parameters:  value is the 16-bit value to split
 *                addr1 is a pointer to the location where the higher-order bits should
 *                be placed
 *                addr2 is a pointer to the location where the lower-order bits should
 *                be placed
 * =====================================================================================
 */
        void
split_bytes(unsigned short value,
                unsigned char *addr1, unsigned char *addr2)
{
    // Cast as a char to just grab the lower-order bits
    *addr2 = (unsigned char)value;
    // Shift the higher bits into the lower position then cast
    value >>= 8;
    *addr1 = (unsigned char)value;
}       /* -----  end of function split_bytes  ----- */
