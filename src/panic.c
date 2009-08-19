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
#include "libc/assert.h"
#include "libc/stdint.h"
#include "libc/stdio.h"
#include "libc/stdarg.h"
#include "libc/unistd.h"
#include "libbfd/bfd.h"
#include "libcompiler/compiler.h"
#include "libcompiler/demangle.h"
#include "libbfd/elf-format.h"
#include "archs/arch.h"

#define DEMANGLE          0
#define MAX_STACK_LEVELS  32
#define MAX_SYMBOL_LENGTH 512

#if DEMANGLE
static unsigned long backtrace[MAX_STACK_LEVELS];
static char          mangled_symbol[MAX_SYMBOL_LENGTH];
extern unsigned long _start;
extern unsigned long _end;
#endif

void arch_panic(const char * message)
{
        static int panic_in_progress = 0;
#if DEMANGLE
        uint_t     frames;
        uint_t     i;
#endif

        panic_in_progress++;
        if (panic_in_progress > 1) {
                printf("Panic in progress ...\n");
                return;
        }

        /* Print the message (if any) */
        if (!message) {
                message = "EMPTY ???";
        }
        printf("Kernel panic: %s\n", message);

#if DEMANGLE
        frames = arch_backtrace_store(backtrace, MAX_STACK_LEVELS);
        assert(frames <= MAX_STACK_LEVELS);

        for (i = 0; i < frames; i++) {
                void * base;
                char * symbol;

#if 0
                assert(backtrace[i] >= &_start);
                assert(backtrace[i] <= &_end);
#endif

                /* Resolve the symbol base */
                if (bfd_symbol_reverse_lookup((void *) backtrace[i],
                                              mangled_symbol,
                                              MAX_SYMBOL_LENGTH,
                                              &base)) {
                        unsigned int delta;

                        symbol  = demangle(mangled_symbol);
                        if (!symbol) {
                                /* No luck this time */
                                symbol  = mangled_symbol;
                        }

                        /*
                         * NOTE:
                         *     Compute the difference between backtrace
                         *     and base ...
                         */
                        delta = backtrace[i] - (unsigned int) base;
                        if (delta) {
                                /* Delta is precious ... */
                                printf("  %p <%s+0x%x>\n",
                                        base, symbol, delta);
                        } else {
                                /* Huh ... hang in function call ? */
                                printf("  %p <%s>\n",
                                       base, symbol);
                        }
                } else {
                        /* Hmm ... No symbol found ??? */
                        printf("  %p <?>\n", backtrace[i]);
                }
        }
#endif

        panic_in_progress--;

        arch_halt();
        arch_reset();

        printf("Cannot halt or reset the hardware ...\n");
        for (;;) { /* hmmmm .... */ }
}
