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
 *        Credits:  Lots of help from this blog: http://www.codeslinger.co.uk/pages/
 *        			projects/gameboy/memory.html
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "global_declarations.h"
#include "helper_functions.h"
#include "memory.h"

// Track ROM banking
char mbc1;
char mbc2;
char current_rom_bank;

// Track RAM banking
char num_banks;
char current_ram_bank;

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
	unsigned char *memory = malloc(0xFFFF);

	// Initialize hardware registers
	write_memory(0xFF10, 0x80);
	write_memory(0xFF11, 0xBF);
	write_memory(0xFF12, 0xF3);
	write_memory(0xFF14, 0xBF);
	write_memory(0xFF16, 0x3F);
	write_memory(0xFF19, 0xBF);
	write_memory(0xFF1A, 0xFF);
	write_memory(0xFF1B, 0x7F);
	write_memory(0xFF1C, 0x9F);
	write_memory(0xFF1E, 0xBF);
	write_memory(0xFF20, 0xFF);
	write_memory(0xFF23, 0xBF);
	write_memory(0xFF24, 0x77);
	write_memory(0xFF25, 0xF3);
	write_memory(0xFF26, 0xF1);
	write_memory(0xFF40, 0x91);
	write_memory(0xFF47, 0xFC);
	write_memory(0xFF48, 0xFF);
	write_memory(0xFF49, 0xFF);

	// TODO: read the cartridge into memory
	current_rom_bank = 1; // We start on bank 1
	current_ram_bank = 1;


	return memory;
}		/* -----  end of function init_memory  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  load_cartridge
 *  Description:  Loads the game cartridge rom
 * =====================================================================================
 */
	unsigned char*
load_cartridge(char *file)
{
	unsigned char *cartridge = malloc(0x200000);
	FILE *binary_file = fopen(file, "rb");
	fread(cartridge, 0x1, 0x200000, binary_file);
	fclose(binary_file);

	// Determine if/which banking used by this game
	switch (cartridge[0x147])
	{
		case 0x1 .. 0x3:
			mbc1 = 1;
			mbc2 = 0;
			break;
		case 0x4 ... 0x5:
			mbc1 = 0;
			mbc2 = 1;
			break;
	}

	return cartridge;
}               /* -----  end of function load_cartridge  ----- */


/*
 * ===  FUNCTION  ======================================================================
 *         Name:  read_memory
 *  Description:  Returns a void pointer to the start of the requested memory
 * =====================================================================================
 */
	void*
read_memory(unsigned short addr)
{
	void *mem;
}		/* -----  end of function read_memory  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  write_memory
 *  Description:  Writes data to the appropriate location in virtual memory
 *   Parameters:  addr is the memory address to write to
 *   			  data is the byte of data to write there
 *      Returns:  1 if write was successful, else 0
 * =====================================================================================
 */
	unsigned char
write_memory(unsigned short addr, unsigned char data)
{
	if (addr <= 0x7FFF) // ROM
	{
		printf("ERROR: Memory at address %x is read-only, unable to write %x\n",
			   addr, data);
		return 0;
	}
	else if ((addr >= 0xE000) && (addr <= 0xFDFF)) // ECHO
	{
		memory[addr] = data;
		memory[addr - 0x2000] = data;
		return 1;
	}
	else if ((addr >= 0xFEA0) && (addr <= 0xFEFF)) // Unusable because reasons
	{
		printf("ERROR: Cannot write %x to %x...Restricted memory\n", data, addr);
		return 0;
	}
	else // Unrestricted memory write access
	{
		memory[addr] = data;
	}
}               /* -----  end of function write_memory  ----- */
