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
void halt();
void stop();
void push();
void pop();
void ei();
void di();
void ccf();
void scf();
#endif
