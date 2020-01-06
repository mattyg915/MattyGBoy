/*
 * =====================================================================================
 *
 *       Filename:  math_instructions.h
 *
 *    Description:  Header file for the arithmetic cpu instructions source
 *
 *        Version:  1.0
 *        Created:  05/28/2018 10:55:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *
 * =====================================================================================
 */

#ifndef MATHINSTRUCTIONS
#define MATHINSTRUCTIONS
unsigned char eight_bit_add(unsigned char opcode);
unsigned char sixteen_bit_add(unsigned char opcode);
unsigned char adc(unsigned char opcode);
unsigned char sub(unsigned char opcode);
unsigned char sbc(unsigned char opcode);
unsigned char eight_bit_inc(unsigned char opcode);
unsigned char sixteen_bit_inc(unsigned char opcode);
unsigned char eight_bit_dec(unsigned char opcode);
unsigned char sixteen_bit_dec(unsigned char opcode);
#endif
