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
void bit_rotate_shift ();
#endif
