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

uint_t arch_backtrace_store(unsigned long * backtrace,
                            uint_t          max_len)
{
        uint_t * ebp;
        uint_t   i;

        __asm__ volatile ("movl %%ebp,%0" : "=r" (ebp));

        for (i = 0; i < max_len; i++) {
                backtrace[i] = ebp[1];
                ebp          = (uint_t *) ebp[0];
        }

        return i; /* Return the saved amount count */
}
