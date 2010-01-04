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
#include "elklib.h"
#include "libc/stddef.h"
#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/assert.h"
#include "libc/string.h"
#include "archs/arch.h"

static int hanging_mode = 0;

void hang(const char * message)
{
        assert(message);

        printf(message);
        switch (hanging_mode) {
                case 0: arch_halt();      break;
                case 1: arch_power_off(); break;
                case 2: arch_reset();     break;
                default:                  break;
        }

        panic("We couldn't hang as supposed ...");
}
