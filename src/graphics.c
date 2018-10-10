/*
 * =====================================================================================
 *
 *       Filename:  graphics.c
 *
 *    Description:  Contains functions that control access to memory for graphics
 *                  ports as well as for drawing the screen
 *
 *        Version:  1.0
 *        Created:  08/09/2018 21:18:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Matt Gercz (mg), matt.gercz@icloud.com
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdio.h>
#include "graphics.h"
#include "global_declarations.h"
#include "memory.h"
#include "cpu_emulator.h"

// Used to track, based on cpu cycles, when the scanline register should be incremented
static unsigned short scanline_counter =0x0;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  increment_scanline
 *  Description:  Increments the y coordinate register, mem address 0xFF44
 * =====================================================================================
 */
    void
increment_scanline()
{
    memory[0xFF44]++;

    if (memory[0xFF44] == 0x90) // V-Blank interrupt request
    {
        // TODO request an interrupt
    }
    if (memory[0xFF44] > 0x99) // Past last vertical line
    {
        memory[0xFF44] = 0x0;
    }
}		/* -----  end of function increment_scanline  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  update_graphics
 *  Description:  Handles updates to the graphics registers
 * =====================================================================================
 */
    void
    update_graphics(unsigned char cycles)
{
    unsigned char lcd_enable = (unsigned char) (memory[0xFF40] & 0x80u);
    if (lcd_enable != 0x80)
    {
        return;
    }

    for (int i = 0x0; i < cycles; i++)
    {
        scanline_counter++;
        if (scanline_counter == 0x1C8)
        {
            scanline_counter = 0x0;
            increment_scanline();
        }
    }
}        /* -----  end of function update_graphics  ----- */