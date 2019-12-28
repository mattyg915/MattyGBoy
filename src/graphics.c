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
#include "global_declarations.h"
#include "cpu_emulator.h"
#include "memory.h"

// Used to track, based on cpu cycles, when the scanline register should be incremented
static unsigned short scanline_counter = 0x0;

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  increment_scanline
 *  Description:  Increments the y coordinate register, mem address 0xFF44
 * =====================================================================================
 */
    void
increment_scanline()
{
    unsigned char cur_line = read_memory(0xFF44);

    if (cur_line == 0x90u) // V-Blank interrupt request
    {
        request_interrupt(0x1u);
    }
    else if (cur_line > 0x99u) // Past last vertical line
    {
        cur_line = 0x0u;
    }
    else if (cur_line < 0x90u)
    {
        // TODO: Draw a line
    }

    cur_line++;
    memory[0xFF44] = cur_line;
}		/* -----  end of function increment_scanline  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  is_lcd_enabled
 *  Description:  Returns true if the lcd is enabled by reading lcd control register
 *                  at mem addr 0xFF40
 * =====================================================================================
 */
int
is_lcd_enabled()
{
    unsigned char lcd_enable = read_memory(0xFF40);

    return (lcd_enable & 0x80u) == 0x80u;
}        /* -----  end of function is_lcd_enabled  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  set_lcd_status
 *  Description:  Handles updates to the lcd status register at mem addr 0xFF41
 * =====================================================================================
 */
    void
set_lcd_status()
{
    unsigned char status = memory[0xFF41];

    if (!is_lcd_enabled()) {
        // If lcd disabled reset scanline and counter, set mode 1 (VBlank)
        scanline_counter = 0x0;
        memory[0xFF44] = 0x0;
        status |= 0x1u;
        write_memory(0xFF41, status);
        return;
    }

    unsigned char cur_line = read_memory(0xFF44);
    unsigned char cur_mode = status & 0x3u;
    unsigned char mode;
    unsigned int req_int = 0x0; // interrupt request, default false

    if (cur_line >= 0x90u)
    {
        // V-Blank, mode 1
        status &= 0xFDu;
        status |= 0x1u;
        mode = 0x1u;
        req_int = status & 0x10u;
    }
    else
    {
        // Set bounds to compare scanline counter against
        int mode_two_bound = 0x50;
        int mode_three_bound = mode_two_bound + 0xAC;

        if (scanline_counter <= mode_two_bound)
        {
            status &= 0xFEu;
            status |= 0x2u;
            mode = 0x2u;
            req_int = status & 0x20u;
        }
        else if (scanline_counter <= mode_three_bound)
        {
            status |= 0x3u;
            mode = 0x3;
        }
        else
        {
            status &= 0xFCu;
            mode = 0x0u;
            req_int = status & 0x4u;
        }
    }

    // Check if we should trigger lcd interrupt
    if (req_int && (mode != cur_mode))
    {
        request_interrupt(0x2u);
    }

    // ...and the coincidence flag
    if (read_memory(0xFF44) == read_memory(0xFF45))
    {
        status |= 0x4u;
        if (status & 0x40u)
        {
            request_interrupt(0x2u);
        }
    }
    else
    {
        status &= 0xFBu;
    }

    // write status back to status register
    write_memory(0xFF41, status);
}        /* -----  end of function set_lcd_status  ----- */

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  update_graphics
 *  Description:  Handles updates to the graphics registers
 * =====================================================================================
 */
    void
update_graphics(unsigned char cycles)
{
    set_lcd_status();

    if (is_lcd_enabled())
    {
        for (int i = 0x0; i < cycles; i++)
        {
            scanline_counter++;
            if (scanline_counter == 0x1C8)
            {
                scanline_counter = 0x0;
                increment_scanline();
            } else {
                increment_scanline();
            }
        }
    }
    else
    {
        return;
    }

}        /* -----  end of function update_graphics  ----- */

