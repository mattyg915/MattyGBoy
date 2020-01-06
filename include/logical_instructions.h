/*
 * =====================================================================================
 *
 *       Filename:  logical_instructions.h
 *
 *    Description:  Header file for logical instruction functions
 *
 *        Version:  1.0
 *        Created:  06/01/2018 21:09:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef LOGICALINSTRUCTIONS
#define LOGICALINSTRUCTIONS
unsigned char and(unsigned char opcode);
unsigned char or(unsigned char opcode);
unsigned char xor(unsigned char opcode);
unsigned char daa();
unsigned char cpl();
#endif
