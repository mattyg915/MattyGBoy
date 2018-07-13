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
void boot();
void eight_bit_update_flags(int value1, int value2);
void sixteen_bit_update_flags(int value1, int value2);
void cpu_execution();
#endif
