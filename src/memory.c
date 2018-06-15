/*
 * =====================================================================================
 *
 *       Filename:  memory.c
 *
 *    Description:  Contains structs and functions used to emulate
 *                  the Gameboy's memory
 *
 *        Version:  1.0
 *        Created:  06/15/2018 09:53:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "global_declarations.h"
#include "helper_functions.h"
#include "memory.h"

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_memory
 *  Description:  Initializes the the virtual memory
 *       Return:  Pointer to the start of the virtual memory array
 * =====================================================================================
 */
	unsigned char*
init_memory(unsigned char *cartridge)
{
	Memory *memory = malloc(sizeof(*memory));
	memory->rom = malloc(0x4000);
	memory->rom_switchable = malloc(0x4000);
	memory->vram = malloc(0x2000);


	// Initialize hardware registers and IME flag
	
	return memory;
}		/* -----  end of function init_memory  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  load_cartridge
 *  Description:  Loads the game cartridge rom
 *   Parameters:  file is the name of the .gb rom file to load
 *       Return:  Pointer to the start of the virtual memory array containing the cart
 * =====================================================================================
 */
        unsigned char*
load_cartridge(char *file)
{

        return memory;
}               /* -----  end of function load_cartridge  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  get_IME
 *  Description:  Returns the value of the Interrupt Master Enable flag
 * =====================================================================================
 */
        unsigned char
get_IME()
{
        return memory[0xFFFF];
}               /* -----  end of function get_IME  ----- */
