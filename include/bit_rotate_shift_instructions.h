/*
 * =====================================================================================
 *
 *       Filename:  bit_rotate_shift_instructions.h
 *
 *    Description:  Header file for bit/rotate/shift cpu intsructions source
 *
 *        Version:  1.0
 *        Created:  06/03/2018 17:03:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef BITROTATESHIFTINSTRUCTIONS
#define BITROTATESHIFTINSTRUCTIONS
void rr (unsigned char *reg);
void rrc (unsigned char *reg);
void rl (unsigned char *reg);
void rlc (unsigned char *reg);
void sla (unsigned char *reg);
void sra (unsigned char *reg);
void swap (unsigned char *reg);
void srl (unsigned char *reg);
void bit (unsigned char opcode, const unsigned char *reg);
void res (unsigned char opcode, unsigned char *reg);
void set (unsigned char opcode, unsigned char *reg);
unsigned char bit_rotate_shift (unsigned char opcode);
#endif
