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
unsigned char* init_memory(unsigned char *cartridge);
unsigned char write_memory(unsigned short addr, unsigned char data);
void* read_memory(unsigned short addr);
unsigned char* load_cartridge(char *file);
#endif
