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
	unsigned char rom_bank_number;
	unsigned char ram_rom_bank_number; // Purpose of field depends on next field
	unsigned char ram_rom_select; // Sets if above field is ram bank or rom
} MBC_Registers;

MBC_Registers* init_mbc();
void free_all_memory();
unsigned char* init_memory(unsigned char *cartridge);
void write_memory(unsigned short addr, unsigned char data);
void* read_memory(unsigned short addr);
unsigned char* load_cartridge(char *file);

#endif
