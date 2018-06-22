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
	unsigned char ram_bank_number;
	unsigned char ram_rom_select; // Set to 1 if ROM mode, 0 for RAM
} MBC_Registers;

MBC_Registers* init_mbc();
unsigned char* init_memory();
void write_memory(unsigned short addr, unsigned char data);
void* read_memory(unsigned short addr);
unsigned char* load_cartridge(char *file);

#endif
