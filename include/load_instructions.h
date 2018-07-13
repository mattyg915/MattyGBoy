/*
 * =====================================================================================
 *
 *       Filename:  load_instructions.h
 *
 *    Description:  Header file containing declarations for load instructions
 *
 *        Version:  1.0
 *        Created:  06/09/2018 15:55:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef LOADINSTRUCTIONS
#define LOADINSTRUCTIONS
unsigned char basic_ld();
unsigned char load_from_to_mem();
unsigned char load_one_byte_imm();
unsigned char read_write_io();
unsigned char load_hl();
unsigned char sixteen_bit_load();
unsigned char ld_hl_sp();
#endif
