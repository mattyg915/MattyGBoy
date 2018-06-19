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

extern unsigned char *memory;

// Track ROM banking
static unsigned char banking_mode;
static MBC_Registers *mbc;

// Track RAM banking
static unsigned char *ext_ram_bank; // Single array to virtualize all RAM banks

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
	
	// Read first 0x4000 bytes of cartridge into ROM
	for (int i = 0x0; i < 0x4000; i++)
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
			banking_mode = 0; // ROM only
			break;
		case 0x1 ... 0x3: // MBC1
			banking_mode = 1;
			mbc = init_mbc();
			break;
		case 0x5 ... 0x6:
			banking_mode = 2;
			mbc = init_mbc();
			break;
		default: // Other banking not handled yet
			banking_mode = 0;
			break;
	}

	switch (cartridge[0x149])
	{
		case 0x1:
			ext_ram_bank = malloc(0x800);
		case 0x2:
			ext_ram_bank = malloc(0x2000);
		case 0x3:
			ext_ram_bank = malloc(0x8000);
		default:
			break;
	}

	return cartridge;
}               /* -----  end of function load_cartridge  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  free_all_memory
 *  Description:  Frees all allocated memory for the various structures used in the 
 *  		      emulator's virtual memory
 * =====================================================================================
 */
        void
free_all_memory()
{
        
}               /* -----  end of function free_all_memory  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  init_mbc
 *  Description:  Initializes struct containing needed registers when using an MBC chip
 *      Returns:  Pointer to a struct containing registers for MBC chip
 * =====================================================================================
 */
	MBC_Registers*
init_mbc()
{
	MBC_Registers *mbc_ptr = malloc(sizeof(*mbc_ptr));
	if (banking_mode == 1) // MBC1
	{
		mbc_ptr->ram_enable = 0x0;
		mbc_ptr->rom_bank_number = 0x1;
		mbc_ptr->ram_rom_bank_number = 0x0;
		mbc_ptr->ram_rom_select = 0x0;
	}

	if (banking_mode == 2) // MBC2
	{
		mbc_ptr->ram_enable = 0x0;
		mbc_ptr->rom_bank_number = 0x1;
		mbc_ptr->ram_rom_bank_number = NULL;
		mbc_ptr->ram_rom_select = NULL;
	}

	return mbc_ptr;
}               /* -----  end of function init_mbc  ----- */

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
	return mem;
}		/* -----  end of function read_memory  ----- */
/*
 * ===  FUNCTION  ======================================================================
 *         Name:  write_memory
 *  Description:  Writes data to the appropriate location in virtual memory
 *   Parameters:  addr is the memory address to write to
 *   			  data is the byte of data to write there
 * =====================================================================================
 */
	void
write_memory(unsigned short addr, unsigned char data)
{
	if (addr <= 0x1FFF) // RAM enable
	{
		mbc->ram_enable = data;
		return;
	}
	else if ((addr >= 0x2000) && (addr <= 0x3FFF)) // Set low 5 bits of rom bank
	{
		mbc->rom_bank_number |= data;
		switch (mbc->rom_bank_number)
		{
			case 0x0: // Bank 0 is fixed
				mbc->rom_bank_number = 0x1;
				break;
			case 0x20: // Banks 20, 40, and 60 aren't used/don't exist
				mbc->rom_bank_number = 0x21;
				break;
			case 0x40:
				mbc->rom_bank_number = 0x41;
				break;
			case 0x61:
				mbc->rom_bank_number = 0x61;
				break;
			default:
				break;
		}
		return;
	}
	else if ((addr >= 0x4000) && (addr <= 0x5FFF)) // Set ram bank or upper 2 bits rom
	{
		if (mbc->ram_rom_select) // RAM mode
		{
			mbc->ram_rom_bank_number = data;
		}
		else // ROM mode
		{
			unsigned char mask = data << 0x5u;
			mbc->rom_bank_number |= mask;
			switch (mbc->rom_bank_number)
			{
				case 0x0:
					mbc->rom_bank_number = 0x1;
				break;
				case 0x20:
					mbc->rom_bank_number = 0x21;
				break;
				case 0x40:
					mbc->rom_bank_number = 0x41;
				break;
				case 0x61:
					mbc->rom_bank_number = 0x61;
				break;
				default:
					break;
			}
		}
	}
	else if ((addr >= 0xE000) && (addr <= 0xFDFF)) // ECHO
	{
		memory[addr] = data;
		memory[addr - 0x2000] = data;
	}
	else if ((addr >= 0xFEA0) && (addr <= 0xFEFF)) // Unusable because reasons
	{
		printf("ERROR: Cannot write %x to %x...Restricted memory\n", data, addr);
	}
	else // Unrestricted memory write access
	{
		memory[addr] = data;
	}
}               /* -----  end of function write_memory  ----- */
