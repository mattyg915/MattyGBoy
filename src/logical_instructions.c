/*
 * =====================================================================================
 *
 *       Filename:  logical_instructions.c
 *
 *    Description:  Contains functions needed to emulate logical CPU instructions
 *
 *        Version:  1.0
 *        Created:  06/01/2018 21:02:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include "logical_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  and
 *  Description:  Handles opcodes translating to AND instructions
 * =====================================================================================
 */
        void
and ()
{
        // Right operand is dependant on opcode, left is always register A
        unsigned char operand = 0;
        unsigned reg_hl = combine_bytes(regs->H, regs->L);

        switch (opcode)
        {
                case 0xE6:
                        ptrs->PC++;
                        operand = memory[ptrs->PC];
                        break;
                case 0xA0:
                        operand = regs->B;
                        break;
                case 0xA1:
                        operand = regs->C;
                        break;
                case 0xA2:
                        operand = regs->D;
                        break;
                case 0xA3:
                        operand = regs->E;
                        break;
                case 0xA4:
                        operand = regs->H;
                        break;
                case 0xA5:
                        operand = regs->L;
                        break;
                case 0xA6:
                        operand = memory[reg_hl];
                        break;
                case 0xA7:
                        operand = regs->A;
                        break;
        }

        // AND instruction clears subtract and carry, but sets half-carry flags
        regs->F = 0x20;

        // Register A & with operand, if yields 0 set zero flag
        regs->A &= operand;
        if (!regs->A)
        {
                regs->F |= 0x80;
        }

        return;
}               /* -----  end of function and  ----- */

