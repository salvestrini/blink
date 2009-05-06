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
#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/assert.h"
#include "dl.h"

void core(dl_list_t dl)
{
        assert(dl);

        printf("%s version %s running ...\n",
               PACKAGE_NAME, PACKAGE_VERSION);
        printf("(C) 2008, 2009 "
               "Francesco Salvestrini <salvestrini@gmail.com>\n");
        printf("Please report bugs to <%s>\n",
               PACKAGE_BUGREPORT);

        /* Perform linking using dl information */

        /* Jump to the entry point */

        /* Argh ... */
        panic("Cannot jump to the entry point");
}
