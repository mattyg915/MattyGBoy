/*
 * =====================================================================================
 *
 *       Filename:  memory.h
 *
 *    Description:  Contains declarations of structs and functions used to emulate
 *                  the Gameboy's memory
 *
 *        Version:  1.0
 *        Created:  06/15/2018 12:51:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */
#ifndef MEMORY
#define MEMORY

typedef struct MBC_Registers
{
	unsigned char ram_enable; // Must be !0 in order to read/write external RAM
	unsigned int ram_bank_size; // This may be necessary in the future for CGB
	unsigned char rom_bank_number;
	unsigned char ram_bank_number;
	unsigned char ram_rom_select; // Set to 1 if ROM mode, 0 for RAM
} MBC_Registers;

static unsigned char *memory;
static unsigned char *cartridge;
static unsigned char *boot_rom;
MBC_Registers* init_mbc();
void init_memory();
void write_memory(unsigned short addr, unsigned char data);
void increment_divider();
void increment_scanline();
unsigned char read_memory(unsigned short addr);
unsigned char* read_memory_ptr(unsigned short addr);
void load_cartridge(char *file);
#endif
