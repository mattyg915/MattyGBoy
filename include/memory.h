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
typedef struct Memory 
{
	unsigned char *rom;
	unsigned char *rom_switchable;
	unsigned char *vram;
	unsigned char *wram;
	unsigned char *echo;
	unsigned char *oam;
	unsigned char *i_o_ports;
	unsigned char *hram;
} Memory;

Memory* init_memory(unsigned char *rom);
void write_memory(unsigned short addr, unsigned char data);
unsigned char read_memory(unsigned short addr);
unsigned char* load_cartridge(char *file);
unsigned char get_IME();
#endif
