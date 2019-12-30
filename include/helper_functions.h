/*
 * =====================================================================================
 *
 *       Filename:  helper_functions.h
 *
 *    Description:  Header containing declarations for helper functions
 *
 *        Version:  1.0
 *        Created:  05/29/2018 09:33:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */

#ifndef HELPERFUNCTIONS
#define HELPERFUNCTIONS
unsigned short combine_bytes(unsigned char byte1, unsigned char byte2);
void split_bytes(unsigned short value, unsigned char *addr1, unsigned char *addr2);
void dump_registers();
void dump_memory();
#endif
