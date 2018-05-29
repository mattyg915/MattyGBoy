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
#include "math_instructions.h"
#include "global_declarations.h"
#include "register_structures.h"
#include "cpu_emulator.h"

unsigned char opcode;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  decode
 *  Description:  Takes the current opcode pointed to by PC and determines 
 *  		  its generalized instruction (e.g. this is a 'load' instruction), 
 *  		  then calls the appropriate method to further decode and emulate it
 * =====================================================================================
 */
	static void
decode() 
{
	// TODO: ALL the opcodes
	switch (opcode) {
		case 0x00: // NOP
			return;
		// Add instructions
		case 0xC6:
		case 0x80 ... 0x87:
		case 0x09:
		case 0x19:
		case 0x29:
		case 0x39:
		case 0xE8:
			add();
			break;
	}
	return;
}		/* -----  end of function decode  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fetch
 *  Description:  Sets the global variable opcode to the current instruction being
 *  		  executed by the CPU
 * =====================================================================================
 */
	static void
fetch()
{
	opcode = memory[ptrs->PC];
	return;
}		/* -----  end of function fetch  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cpu_execution
 *  Description:  Emulates the three primary functions of the CPU using associated 
 *  		  functions: fetch an opcode, decode it, execute it's instruction
 * =====================================================================================
 */
	void
cpu_execution()
{
	fetch();
	decode();
	ptrs->PC++;
}		/* -----  end of function cpu_execution  ----- */

