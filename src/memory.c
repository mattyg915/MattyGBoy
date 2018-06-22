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
#include "memory.h"
#include "global_declarations.h"

extern unsigned char *memory;
extern unsigned char *cartridge;

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
init_memory()
{
	unsigned char *new_memory = malloc(0xFFFF);

	// Initialize hardware registers
	new_memory[0xFF10] = 0x80;
	new_memory[0xFF11] = 0xBF;
	new_memory[0xFF12] = 0xF3;
	new_memory[0xFF14] = 0xBF;
	new_memory[0xFF16] = 0x3F;
	new_memory[0xFF19] = 0xBF;
	new_memory[0xFF1A] = 0xFF;
	new_memory[0xFF1B] = 0x7F;
	new_memory[0xFF1C] = 0x9F;
	new_memory[0xFF1E] = 0xBF;
	new_memory[0xFF20] = 0xFF;
	new_memory[0xFF23] = 0xBF;
	new_memory[0xFF24] = 0x77;
	new_memory[0xFF25] = 0xF3;
	new_memory[0xFF26] = 0xF1;
	new_memory[0xFF40] = 0x91;
	new_memory[0xFF47] = 0xFC;
	new_memory[0xFF48] = 0xFF;
	new_memory[0xFF49] = 0xFF;
	
	// Read first 0x4000 bytes of cartridge into ROM
	for (int i = 0x0; i < 0x4000; i++)
	{
		new_memory[i] = cartridge[i];
	}

	return new_memory;
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
	unsigned char *new_cartridge = malloc(0x200000);
	FILE *binary_file = fopen(file, "rb");
	fread(new_cartridge, 0x1, 0x200000, binary_file);
	fclose(binary_file);

	// Parse fields of the header to determine rom/ram banking used
	switch (new_cartridge[0x147]) // Which mbc should be used
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

	switch (new_cartridge[0x149])
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

	return new_cartridge;
}               /* -----  end of function load_cartridge  ----- */

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
		mbc_ptr->ram_bank_number = 0x0;
		mbc_ptr->ram_rom_select = 0x0;
	}

	if (banking_mode == 2) // MBC2
	{
		mbc_ptr->ram_enable = 0x0;
		mbc_ptr->rom_bank_number = 0x1;
		mbc_ptr->ram_bank_number = 0xFF;
		mbc_ptr->ram_rom_select = 0xFF;
	}

	return mbc_ptr;
}               /* -----  end of function init_mbc  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  read_memory
 *  Description:  Returns a 1-byte value located at the specified memory address
 *  		  while taking into account rom and ram banks
 *   Parameters:  addr is a 16-bit memory address
 * =====================================================================================
 */
	unsigned char
read_memory(unsigned short addr)
{
	unsigned char data;

	if (addr < 0x4000) // Read from onboard ROM
	{
		data = memory[addr];
	}
	else if (banking_mode == 1) // MBC1
	{
		if ((addr > 0x3FFF) && (addr < 0x8000)) // Read from ROM banks
		{
			data = cartridge[addr + (mbc->rom_bank_number * 0x4000)];
		}
		else if ((addr > 0x9FFF) && (addr < 0xC000) && mbc->ram_enable)
		// Read from RAM banks
		{
			data = ext_ram_bank[addr + (mbc->ram_bank_number * 0x2000)];
		}
		else
		{
			data = memory[addr];
		}
	}
	else if (banking_mode == 2) // MBC2
	{
		if ((addr > 0x3FFF) && (addr < 0x8000)) // Read from ROM banks
		{
			data = cartridge[addr + (mbc->rom_bank_number * 0x4000)];
		}
		else
		{
			data = memory[addr];
		}
	}
	else // No memory banking
	{
		data = memory[addr];
	}

	return data;
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
		// Enable RAM if lower nibble of data == 0xA
		mbc->ram_enable = (unsigned char) ((data & 0x0Fu) == 0xA ? 1 : 0);
		return;
	}
	else if ((addr >= 0x2000) && (addr <= 0x3FFF)) // Set low 5 bits of rom bank
	{
		mbc->rom_bank_number += (unsigned char) (data & 0x1Fu);

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
	else if ((addr > 0x3FFF) && (addr < 0x6000)) // Set ram bank or upper 2 bits rom
	{
		if (mbc->ram_rom_select) // RAM mode
		{
			mbc->ram_bank_number = (unsigned char) (data & 0x3u);
		}
		else // ROM mode
		{
			mbc->rom_bank_number += (unsigned char)(data & 0x60u);

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
	else if ((addr > 0x5FFF) && (addr < 0x8000)) // Select RAM/ROM mode
	{
		mbc->ram_rom_select = (unsigned char) (data & 0x1u);

		if (mbc->ram_rom_select)
		{
			mbc->ram_bank_number = 0;
		}
	}
	else if ((addr > 0xDFFF) && (addr < 0xFE00)) // ECHO
	{
		memory[addr] = data;
		memory[addr - 0x2000] = data;
	}
	else if ((addr >= 0xFEA0) && (addr <= 0xFEFF)) // Unusable because reasons
	{
		printf("ERROR: Cannot write %x to %x...Restricted memory\n", data, addr);
	}
	// TODO this is here for testing
	else if ((addr >= 0xFF00) && (addr <= 0xFF7F))
	{
	    printf("io access %x: %x\n",addr, data);
		if ((addr == 0xFF02) && (data == 0x81))
		{
			printf("%c", (char)memory[0xFF01]);
			fflush(stdout);
		}
		else
		{
			memory[addr] = data;
		}
	}
	else // Unrestricted memory write access
	{
		memory[addr] = data;
	}
}               /* -----  end of function write_memory  ----- */
