/*
 * =====================================================================================
 *
 *       Filename:  graphics.c
 *
 *    Description:  Contains functions that control access to memory for timers
 *
 *        Version:  1.0
 *        Created:  08/29/2018 08:55:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:
 *
 * =====================================================================================
 */

#include "timers.h"
#include "memory.h"
#include "global_declarations.h"
#include "cpu_emulator.h"

// Used to track when the actual timer and divider registers should be incremented
static unsigned char divider_counter = 0x0;
static unsigned int timer_counter = 0x0;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  update_timers
 *  Description:  Handles updates to the timer registers
 * =====================================================================================
 */
void
update_timers(unsigned char cycles)
{
    // Only increment timer register if bit 3 of TAC set
    unsigned char tac_reg = read_memory(0xFF07);
    unsigned char timer_frequency = (unsigned char) (tac_reg & 0x3u);
    unsigned char tima_enable = (unsigned char) (tac_reg & 0x4u);

    for (int i = 0x0; i < cycles; i++)
    {
        // Update the divider register
        divider_counter++;
        if (divider_counter == 0x0) {
            increment_divider();
        }

        // Update the timer register
        timer_counter++;

        // TIMA update frequency specified by 2 LSB in TAC
        switch (timer_frequency)
        {
            case 0x00:
                if (timer_counter == 0x400) // 4096 Hz / 1024 clocks
                {
                    if (tima_enable)
                    {
                        increment_timer();
                    }
                    timer_counter = 0x0;
                }
                break;
            case 0x01:
                if (timer_counter == 0x10) // 262144 Hz / 16 clocks
                {
                    if (tima_enable)
                    {
                        increment_timer();
                    }
                    timer_counter = 0x0;
                }
                break;
            case 0x02:
                if (timer_counter == 0x40) // 65536 Hz / 64 clocks
                {
                    if (tima_enable)
                    {
                        increment_timer();
                    }
                    timer_counter = 0x0;
                }
                break;
            case 0x3:
                if (timer_counter == 0x100) // 16384 Hz / 256 clocks
                {
                    if (tima_enable)
                    {
                        increment_timer();
                    }
                    timer_counter = 0x0;
                }
                break;
            default:
                break;
        }
    }
}        /* -----  end of function update timers  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  increment_timer
 *  Description:  Increments the divider register, mem address 0xFF04
 * =====================================================================================
 */
void
increment_timer()
{
    memory[0xFF05]++;

    if (memory[0xFF05] == 0x0)
    {
        memory[0xFF05] = memory[0xFF06]; // Value resets to value in TMA reg at overflow
        memory[0xFF0F] |= 0x4u; // Request timer interrupt
    }
}		/* -----  end of function increment_timer  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  increment_divider
 *  Description:  Increments the divider register, mem address 0xFF04
 * =====================================================================================
 */
void
increment_divider()
{
    memory[0xFF04]++;
}		/* -----  end of function increment_divider  ----- */