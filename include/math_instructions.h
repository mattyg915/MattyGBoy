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
unsigned char eight_bit_add();
unsigned char sixteen_bit_add();
unsigned char adc();
unsigned char sub();
unsigned char sbc();
unsigned char eight_bit_inc();
unsigned char sixteen_bit_inc();
unsigned char eight_bit_dec();
unsigned char sixteen_bit_dec();
#endif
