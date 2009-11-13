/* -*- c -*- */

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
#include "archs/x86/port.h"

void arch_halt(void)
{
        __asm__ ("hlt" : : );
}

void arch_power_off(void)
{
        /* XXX FIXME: Add proper code here */
        arch_halt();
}

/*
 * There are three ways to reset the machine:
 *
 *   1) Make the corresponding BIOS call in real mode
 *   2) Program the keyboard controller to do the reset
 *   3) Triple fault the CPU by using an empty IDT
 *
 * Any of these can fail on odd hardware
 *
 */
void arch_reset(void)
{
        /* Reset via the keyboard */

        port_out8(0x70, 0x80);
        port_in8(0x71);

        while (port_in8(0x64) & 0x02) {
                /* Do nothing here ... */
        }

        port_out8(0x70, 0x8F);
        port_out8(0x71, 0x00);
        port_out8(0x64, 0xFE);
}
