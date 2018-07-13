/*
 * =====================================================================================
 *
 *       Filename:  control_instructions.h
 *
 *    Description:  Constains declarations needed for CPU instructions dealing with
 *                  program flow control, e.g. comparisons and jumps
 *
 *        Version:  1.0
 *        Created:  06/5/2018 10:05:04
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (matt.gercz@icloud.com)
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef CONTROLINSTRUCTIONS
#define CONTROLINSTRUCTIONS
unsigned char cp();
unsigned char jp();
unsigned char jr();
unsigned char call();
unsigned char ret();
unsigned char reti();
unsigned char rst();
#endif
