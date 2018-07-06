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
static MBC_Registers *mbc = NULL;

// Track RAM banking
static unsigned char *ext_ram_bank = NULL; // Single array to virtualize all RAM banks

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
			banking_mode = 0x0; // ROM only
			break;
		case 0x1 ... 0x3: // MBC1
			banking_mode = 0x1;
			mbc = init_mbc();
			break;
		case 0x5 ... 0x6:
			banking_mode = 0x2;
			mbc = init_mbc();
			break;
		default: // Other banking not handled yet
			banking_mode = 0x0;
			break;
	}

	switch (new_cartridge[0x149])
	{
		case 0x0:
		    break;
		case 0x1:
			mbc->ram_bank_size = 0x800;
			ext_ram_bank = malloc(0x1000);
			break;
		case 0x2:
		    mbc->ram_bank_size = 0x800;
			ext_ram_bank = malloc(0x2000);
			break;
		case 0x3:
		    mbc->ram_bank_size = 0x2000;
			ext_ram_bank = malloc(0x8000);
			break;
	    case 0x4:
	        mbc->ram_bank_size = 0x2000;
	        ext_ram_bank = malloc(0x20000);
	        break;
	    case 0x5:
	        mbc->ram_bank_size = 0x2000;
	        ext_ram_bank = malloc(0x10000);
	        break;
		default:
			break;
	}

	return new_cartridge;
}               /* -----  end of function load_cartridge  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  load_test_cartridge
 *  Description:  Loads a testing file as the game cartridge
 * =====================================================================================
 */
	unsigned char*
load_test_cartridge()
{
	unsigned char *new_cartridge = malloc(0x200000);

	for (int i = 0x0; i < 0x100; i++)
    {
        new_cartridge[i] = 0x0;
    }
    new_cartridge[0x100] = 0x00;
	new_cartridge[0x101] = 0xC3;
	new_cartridge[0x102] = 0x50;
	new_cartridge[0x103] = 0x01;
	new_cartridge[0x150] = 0x00;
	new_cartridge[0x151] = 0x26;
	new_cartridge[0x152] = 0x70;
	new_cartridge[0x153] = 0x2E;
    new_cartridge[0x154] = 0x75;
    new_cartridge[0x155] = 0x7E;
    new_cartridge[0x156] = 0xCD;
    new_cartridge[0x157] = 0x50;
    new_cartridge[0x158] = 0x65;
    new_cartridge[0x6550] = 0xC9;
    new_cartridge[0x159] = 0x3E;
    new_cartridge[0x15A] = 0xF;
    new_cartridge[0x15B] = 0xC6;
    new_cartridge[0x15C] = 0x01;
    new_cartridge[0x15D] = 0xF5;
    new_cartridge[0x15E] = 0x79;
    new_cartridge[0x15F] = 0xD6;
    new_cartridge[0x160] = 0x13;
    new_cartridge[0x161] = 0xF1;
    new_cartridge[0x162] = 0x76;
	new_cartridge[0x7075] = 0x77;

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
}               /* -----  end of function load_test_cartridge  ----- */

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
		mbc_ptr->ram_bank_size = 0x0;
		mbc_ptr->ram_bank_number = 0x0;
		mbc_ptr->ram_rom_select = 0x0;
	}

	if (banking_mode == 2) // MBC2
	{
		mbc_ptr->ram_enable = 0x0;
		mbc_ptr->rom_bank_number = 0x1;
		mbc_ptr->ram_bank_size = 0x0;
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

	if (banking_mode == 1) // MBC1
	{
        if (addr < 0x4000)
        {
            data = cartridge[addr];
        }
        else if ((addr >= 0x4000) && (addr < 0x8000)) // Read from ROM banks
        {
        addr -= 0x4000;
        data = cartridge[addr + (mbc->rom_bank_number * 0x4000)];
        }
        else if ((addr >= 0xA000) && (addr < 0xC000))
        // Read from RAM banks
        {
            if (!mbc->ram_enable)
            {
                return error_value;
            }
            else
            {
                addr -= 0xA000;
                data = ext_ram_bank[addr + (mbc->ram_bank_number * mbc->ram_bank_size)];
            }
        }
        else
        {
            data = memory[addr];

            if (addr > 0xFF00)
            {
                //printf("writing data at %x to %x and i is %d\n", addr, data, i);
            }
        }
	}
	else if (banking_mode == 2) // MBC2
	    {
			if (addr < 0x4000)
            {
                data = cartridge[addr];
            }
			else if ((addr > 0x3FFF) && (addr < 0x8000)) // Read from ROM banks
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
        if (addr < 0x8000)
        {
            data = cartridge[addr];
        }
        else
        {
            data = memory[addr];
        }
	}

	return data;
}		/* -----  end of function read_memory  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  read_memory_ptr
 *  Description:  Returns a pointer to the specified memory address while taking
 *                into account rom and ram banks
 *   Parameters:  addr is a 16-bit memory address
 * =====================================================================================
 */
    unsigned char*
read_memory_ptr(unsigned short addr)
{
    unsigned char *mem;

    if (banking_mode == 1) // MBC1
    {
        if ((addr > 0x3FFF) && (addr < 0x8000)) // Read from ROM banks
        {
            addr -= 0x4000;
            mem = &cartridge[addr + (mbc->rom_bank_number * 0x4000)];
        }
        else if ((addr > 0x9FFF) && (addr < 0xC000))
        // Read from RAM banks
        {
            {
                if (!mbc->ram_enable)
                {
                    return &error_value;
                }
                else
                {
                    addr -= 0xA000;
                    mem = &ext_ram_bank[addr + (mbc->ram_bank_number * mbc->ram_bank_size)];
                }
            }
        }
        else
        {
            mem = &memory[addr];
        }
    }
    else if (banking_mode == 2) // MBC2
    {
        if ((addr > 0x3FFF) && (addr < 0x8000)) // Read from ROM banks
        {
            mem = &cartridge[addr + (mbc->rom_bank_number * 0x4000)];
        }
        else
        {
            mem = &memory[addr];
        }
    }
    else // No memory banking
    {
        if (addr < 0x8000)
        {
            mem = &cartridge[addr];
        }
        else
        {
            mem = &memory[addr];
        }
    }

    return mem;
}		/* -----  end of function read_memory_ptr  ----- */

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
		mbc->ram_enable = (unsigned char) ((data & 0xFu) == 0xA ? 1 : 0);
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
		else // ROM mode, set bits 5 and 6 of rom bank
		{
			mbc->rom_bank_number &= 0x6E0u;
			data &= 0x1F;
			mbc->rom_bank_number |= data;
			if (mbc->rom_bank_number == 0)
            {
                mbc->rom_bank_number = 1;
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
	else if ((addr > 0x9FFF) && (addr < 0xC000))
    {
        if (mbc->ram_enable)
        {
            addr -= 0xA000;
            ext_ram_bank[addr + (mbc->ram_bank_number * 0x2000)] = data;
        }
    }
	else if ((addr > 0xDFFF) && (addr < 0xFE00)) // ECHO
	{
		memory[addr] = data;
		memory[addr - 0x2000] = data;
	}
	else if ((addr >= 0xFEA0) && (addr < 0xFF00)) // Unusable because reasons
	{
		return;
	}
	// TODO this is here for testing
	else if ((addr >= 0xFF00) && (addr < 0xFF80))
	{
		if ((addr == 0xFF02) && (data == 0x81))
		{
			printf("%c", memory[0xFF01]);
			fflush(stdout);
		}
        memory[addr] = data;
	}
	else // Unrestricted memory write access
	{
		memory[addr] = data;
	}
}               /* -----  end of function write_memory  ----- */
