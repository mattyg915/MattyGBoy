/*
 * =====================================================================================
 *
 *       Filename:  cpu_control_instructions.h
 *
 *    Description:  Contains declarations for cpu control functions
 *
 *        Version:  1.0
 *        Created:  06/09/2018 20:43:09
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:  
 *
 * =====================================================================================
 */
#ifndef CPUCONTROLINSTRUCTIONS
#define CPUCONTROLINSTRUCTIONS
unsigned char halt();
unsigned char stop();
unsigned char push(unsigned char opcode);
unsigned char pop(unsigned char opcode);
unsigned char ei();
unsigned char di();
unsigned char ccf();
unsigned char scf();
#endif
