/*
 * =====================================================================================
 *
 *       Filename:  cpu_control_instructions.c
 *
 *    Description:  Contains functions to emulate cpu control instructions
 *
 *        Version:  1.0
 *        Created:  06/09/2018 20:42:47
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include "global_declarations.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pop
 *  Description:  Handles instructions to pop data off of the stack
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
pop (unsigned char opcode)
{
    unsigned char reg_f;
    switch (opcode)
    {
        case 0xC1:
            regs->C = read_memory(ptrs->SP);
            ptrs->SP++;
            regs->B = read_memory(ptrs->SP);
            ptrs->SP++;
            return 0xC;
        case 0xD1:
            regs->E = read_memory(ptrs->SP);
            ptrs->SP++;
            regs->D = read_memory(ptrs->SP);
            ptrs->SP++;
            return 0xC;
        case 0xE1:
            regs->L = read_memory(ptrs->SP);
            ptrs->SP++;
            regs->H = read_memory(ptrs->SP);
            ptrs->SP++;
            return 0xC;
        case 0xF1:
            reg_f = read_memory(ptrs->SP);
            // Need to reassemble since storing F flags discretely
            flags->Z = reg_f >> 0x7u;
            flags->N = reg_f >> 0x6u;
            flags->N &= 0x1u;
            flags->H = reg_f >> 0x5u;
            flags->H &= 0x1u;
            flags->C = reg_f >> 0x4u;
            flags->C &= 0x1u;
            ptrs->SP++;
            regs->A = read_memory(ptrs->SP);
            ptrs->SP++;
            return 0xC;
        default:
            return 0x0;
    }
}		/* -----  end of function pop  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  ccf
 *  Description:  Handles instructions to complement the carry flag
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
ccf ()
{
    flags->H = 0x0;
    flags->N = 0x0;
    flags->C ^= 0x1u;
    return 0x4;
}		/* -----  end of function ccf  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  scf
 *  Description:  Handles instructions to set the carry flag
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
scf ()
{
    flags->C = 0x1;
    flags->N = 0x0;
    flags->H = 0x0;
    return 0x4;
}		/* -----  end of function scf  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  push
 *  Description:  Handles instructions to push data onto the stack
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
push (unsigned char opcode)
{
	unsigned char f_reg = 0;
	switch (opcode)
	{
		case 0xF5:
			ptrs->SP--;
			write_memory(ptrs->SP, regs->A);
			ptrs->SP--;
			// F flags are stored discretely so need to get them and assemble
			f_reg += (flags->Z << 0x7u);
			f_reg += (flags->N << 0x6u);
			f_reg += (flags->H << 0x5u);
			f_reg += (flags->C << 0x4u);
			write_memory(ptrs->SP, f_reg);
			return 0x10;
	    case 0xC5:
	        ptrs->SP--;
	        write_memory(ptrs->SP, regs->B);
	        ptrs->SP--;
	        write_memory(ptrs->SP, regs->C);
	        return 0x10;
	    case 0xD5:
            ptrs->SP--;
            write_memory(ptrs->SP, regs->D);
            ptrs->SP--;
            write_memory(ptrs->SP, regs->E);
	        return 0x10;
	    case 0xE5:
            ptrs->SP--;
            write_memory(ptrs->SP, regs->H);
            ptrs->SP--;
            write_memory(ptrs->SP, regs->L);
	        return 0x10;
        default:
            return 0x10;
    }
}		/* -----  end of function push  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  halt
 *  Description:  Handles opcodes that direct the CPU to halt
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
halt ()
{
    return 0x4;
}		/* -----  end of function halt  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ei
 *  Description:  Handles instructions to enable interrupts
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
ei ()
{
	flags->IME = 0x1;
    return 0x4;
}		/* -----  end of function ei  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  di
 *  Description:  Handles instructions to disable interrupts
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
di ()
{
	flags->IME = 0x0;
	return 0x4;
}		/* -----  end of function di  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  stop
 *  Description:  Handles instructions to stop the CPU's execution
 *       Return:  The number of clock cycles to execute this instruction
 * =====================================================================================
 */
	unsigned char
stop ()
{
	return 0x4;
}		/* -----  end of function stop  ----- */
