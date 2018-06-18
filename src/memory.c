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

extern unsigned char *memory;

// Track ROM banking
static unsigned char banking_mode;
static MBC1_Registers mbc1;
static MBC2_Registers mbc2;
static unsigned char rom_bank_number; // bank 0 is gameboy internal rom

// Track RAM banking
static unsigned char ext_ram_bank; // Single array to virtualize all RAM banks
static unsigned char num_ram_banks;
static unsigned char ram_bank_number;

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

	// TODO: finish handling reading cartridge into ROM
	
	// Read first 0x8000 bytes of cartridge into ROM
	for (int i = 0x0; i < 0x8000; i++)
	{
		memory[i] = cartridge[i];
	}

	return memory;
}		/* -----  end of function init_memory  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  load_cartridge
 *  Description:  Loads the game cartridge rom and parses the cartridge header
 * =====================================================================================
 */
	unsigned char*
load_cartridge(char *file)
{
	unsigned char *cartridge = malloc(0x200000);
	FILE *binary_file = fopen(file, "rb");
	fread(cartridge, 0x1, 0x200000, binary_file);
	fclose(binary_file);

	// Parse fields of the header to determine rom/ram banking used
	switch (cartridge[0x147]) // Which mbc should be used
	{
		case 0x0:
			mbc1 = 0;
			mbc2 = 0;
			break;
		case 0x1 ... 0x3:
			mbc1 = 1;
			mbc2 = 0;
			break;
		case 0x5 ... 0x6:
			mbc1 = 0;
			mbc2 = 1;
			break;
		default: // Other banking not handled yet
			mbc1 = 0;
			mbc2 = 0;
			break;
	}
	current_rom_bank = 1;

	switch (cartridge[0x149])
	{
		case 0x0:
			num_ram_banks = 0;
			break;
		case 0x1:
			num_ram_banks = 1;
			ext_ram_bank = malloc(0x800);
		case 0x2:
			num_ram_banks = 1;
			ext_ram_bank = malloc(0x2000);
		case 0x3:
			num_ram_banks = 4;
			ext_ram_bank = malloc(0x8000);
		default:
			break;
	}
	current_ram_bank = 0;

	return cartridge;
}               /* -----  end of function load_cartridge  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  free_all_memory
 *  Description:  Frees all allocated memory for the various structures used in the 
 *  		  emulator's virtual memory
 * =====================================================================================
 */
        void*
free_all_memory()
{
        
}               /* -----  end of function free_all_memory  ----- */

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
	if (addr <= 0x) // ROM
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
