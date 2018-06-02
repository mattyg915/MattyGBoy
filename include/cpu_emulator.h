/*
 * =====================================================================================
 *
 *       Filename:  cpu_emulator.h
 *
 *    Description:  Header containing declarations for the cpu emaulator functions
 *
 *        Version:  1.0
 *        Created:  05/25/2018 10:45:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *
 * =====================================================================================
 */

#ifndef CPUEMULATOR
#define CPUEMULATOR
extern unsigned char opcode;

unsigned short combine_registers(unsigned char reg1, unsigned char reg2);
void split_between_registers(unsigned short value, 
		unsigned char *reg1, unsigned char *reg2);
unsigned char get_zero_flag();
unsigned char get_subtract_flag();
unsigned char get_half_carry_flag();
unsigned char get_carry_flag();
void eight_bit_update_flags(int value1, int value2);
void sixteen_bit_update_flags(int value1, int value2);
void cpu_execution();
#endif
