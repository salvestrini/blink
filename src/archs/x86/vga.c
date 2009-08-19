/*
 * Copyright (C) 2008, 2009 Francesco Salvestrini
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "config.h"
#include "libc/stdint.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/stddef.h"
#include "libc/ctype.h"
#include "libc/assert.h"
#include "archs/x86/port.h"

#define VGA_SET_CURSOR_START 0xA
#define VGA_SET_CURSOR_END   0xB
#define VGA_SET_ADDRESS_HIGH 0xC
#define VGA_SET_ADDRESS_LOW  0xD
#define VGA_SET_CURSOR_HIGH  0xE
#define VGA_SET_CURSOR_LOW   0xF

#define VGA_COLOR_BACKGROUND 4
#define VGA_COLOR_FOREGROUND 0

#define VGA_COLOR_BLACK      0
#define VGA_COLOR_BLUE       1
#define VGA_COLOR_GREEN      2
#define VGA_COLOR_CYAN       3
#define VGA_COLOR_RED        4
#define VGA_COLOR_MAGENTA    5
#define VGA_COLOR_YELLOW     6
#define VGA_COLOR_WHITE      7

#define VGA_REG_START_CUR    0xA
#define VGA_REG_END_CUR      0xB

#define VGA_COMMAND_PORT     0x3D4
#define VGA_DATA_PORT        0x3D5

#define VGA_BASE             0xB8000
#define VGA_COLUMNS          80
#define VGA_ROWS             25

static struct {
        uint8_t * base;
        uint_t    row;
        uint_t    column;
} vga;

static void vga_move_cursor(uint_t row,
                            uint_t column)
{
        uint_t position;

        /* assert(row >= 0); */
        assert(row < VGA_ROWS);
        /* assert(column >= 0); */
        assert(column < VGA_COLUMNS);

        position = (row * VGA_COLUMNS + column);

        port_out8(VGA_COMMAND_PORT, VGA_SET_CURSOR_HIGH);
        port_out8(VGA_DATA_PORT,    (position >> 8));
        port_out8(VGA_COMMAND_PORT, VGA_SET_CURSOR_LOW);
        port_out8(VGA_DATA_PORT,    (position & 0xFF));
}

static void vga_clear(void)
{
        memset(vga.base, 0, VGA_ROWS * VGA_COLUMNS * 2);
        vga_move_cursor(0, 0);
}

static void vga_scroll_up(void)
{
        uint_t i, delta;

        delta = 1;
#if 0
        if (delta == 0) {
                return;
        }
#endif
        for (i = 0 ; i < VGA_ROWS - delta ; i++) {
                memcpy((void *)(vga.base + i * VGA_COLUMNS * 2),
                       (void *)(vga.base + (i + delta) * VGA_COLUMNS * 2),
                       VGA_COLUMNS * 2);
        }

        for (; i < VGA_ROWS ; i++) {
                memset((void *)(vga.base + i * VGA_COLUMNS * 2), 0x0,
                       VGA_COLUMNS * 2);
        }
}

static void vga_putc(int    c,
                     uint_t row,
                     uint_t column)
{
        uint_t offset;

        /* assert(row >= 0); */
        assert(row < VGA_ROWS);
        /* assert(column >= 0); */
        assert(column < VGA_COLUMNS);

        offset = (row * VGA_COLUMNS + column) * 2;

        /* Character */
        *(vga.base + offset    ) = c & 0xFF;
        /* Attribute */
        *(vga.base + offset + 1) =
                VGA_COLOR_WHITE << VGA_COLOR_FOREGROUND |
                VGA_COLOR_BLACK << VGA_COLOR_BACKGROUND;
}

static int initialized = 0;

static void check_bounds(uint_t* column, uint_t* row)
{
        uint_t r;
        uint_t c;

        r = *row;
        c = *column;

        if (c >= VGA_COLUMNS) {
                /* We reached the right margin ... */
                c = 0;
                r = r + 1;
        }
#if 0
        /* Huh ... c is an unit_t */
        else if (c < 0) {
                c = VGA_COLUMNS - 1;
                r = r - 1;
        }
#endif
        if (r >= VGA_ROWS) {
                /* We reached the bottom margin */
                r = VGA_ROWS - 1;

                /* And we need to scroll up the screen */
                vga_scroll_up();
        }
#if 0
        /* Huh ... r is an unit_t */
        else if (r < 0) {
                r = 0;
        }
#endif

        *column = c;
        *row    = r;
}

int vga_putchar(int c)
{
        uint_t row;
        uint_t column;

        int    print_action;
        int    post_action;
        int    move_action;

        if (!initialized) {
                return EOF;
        }

        /* Retrieve the old cursor position */
        row    = vga.row;
        column = vga.column;

        print_action = 1;
        move_action  = 1;
        post_action  = 1;

        /* Pre-print action */
        switch (c) {
                case '\a': /* Bell */
                        /* Missing */
                        break;

                case '\b': /* Back Space */
                        column       = column - 1;
                        c            = ' ';
                        print_action = 1;
                        post_action  = 0;
                        break;

                case '\t': /* Tab */
                        column       = column + 8;
                        print_action = 0;
                        post_action  = 0;
                        break;

                case '\v': /* Vertical Tab ? */
                        /* missing */
                        break;

                case '\n': /* New Line */
                        row          = row    + 1;
                        column       = 0;
                        print_action = 0;
                        post_action  = 0;
                        break;

                case '\f': /* Form Feed */
                        row          = row    + 1;
                        print_action = 0;
                        post_action  = 0;
                        break;

                case '\r': /* Line Feed */
                        column       = 0;
                        print_action = 0;
                        post_action  = 0;
                        break;

                default:
                        print_action = isprint(c);
                        post_action  = print_action;
                        break;
        }

        check_bounds(&column, &row);

        /* Print */
        if (print_action) {
                vga_putc(c, row, column);
        }

        /* Post-print action */
        if (post_action) {
                switch (c) {
                        default:
                                column = column + 1;
                                break;
                }
        }

        check_bounds(&column, &row);

        /* Move */
        if (move_action) {
                vga_move_cursor(row, column);
        }

        /* Save the final cursor position */
        vga.row    = row;
        vga.column = column;

        return (unsigned char) c;
}

int vga_init(void)
{
        assert(!initialized);

        vga.base   = (uint8_t *) VGA_BASE;
        vga.row    = 0;
        vga.column = 0;

        /*
         * NOTE:
         *     Set the first scan line for the cursor, and the blinking
         *     mode. First scan line is 11, so that we have a visible
         *     cursor.
         */
        port_out8(VGA_COMMAND_PORT, VGA_SET_CURSOR_START);
        port_out8(VGA_DATA_PORT,    ((0x2 << 5) | 11));

        vga_clear();

        initialized = 1;

        return 1;
}

void vga_fini(void)
{
        if (initialized) {
                initialized = 0;
        }
}
