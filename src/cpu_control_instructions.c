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
#include "cpu_control_instructions.h"
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "helper_functions.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  pop
 *  Description:  Handles instructions to pop data off of the stack
 * =====================================================================================
 */
	void
pop ()
{
	return;
}		/* -----  end of function pop  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  push
 *  Description:  Handles instructions to push data onto the stack
 * =====================================================================================
 */
	void
push ()
{
	return;
}		/* -----  end of function push  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  halt
 *  Description:  Handles opcodes that direct the CPU to halt
 * =====================================================================================
 */
	void
halt ()
{
	
	return;
}		/* -----  end of function halt  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ei
 *  Description:  Handles instructions to enable interrupts
 * =====================================================================================
 */
	void
ei ()
{
	flags->IME = 1;
	return;
}		/* -----  end of function ei  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  di
 *  Description:  Handles instructions to disable interrupts
 * =====================================================================================
 */
	void
di ()
{
	flags->IME = 0;
	return;
}		/* -----  end of function di  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  stop
 *  Description:  Handles instructions to stop the CPU's execution
 * =====================================================================================
 */
	void

stop ()
{
	return;
}		/* -----  end of function stop  ----- */
