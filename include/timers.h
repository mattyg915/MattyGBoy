/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  Header file for timer control functions
 *
 *        Version:  1.0
 *        Created:  08/29/2018 08:50:24
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:
 *
 * =====================================================================================
 */

#ifndef MATTYGBOY_TIMERS_H
#define MATTYGBOY_TIMERS_H
void update_timers(unsigned char cycles);
void increment_timer();
void increment_divider();
#endif
