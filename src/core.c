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
#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/assert.h"

int load_elf_image(const char *     name,
                   unsigned long ** entry,
                   void *           buffer)
{
        assert(name);
        assert(entry);
        assert(buffer);

#if 0
        if (!elf_check_file((struct Elf32_Header *) buffer)) {
                printf("Image '%s' is not a valid elf image\n", name);
                return 0;
        }

        ** entry = (unsigned long)
                elf_get_entry_point((struct Elf32_Header *) buffer);

        printf("Image '%s' entry point: 0x%lx\n", name, **entry);

        if (!elf_loadFile(buffer, 1)) {
                return 0;
        }
#endif

        return 1;
}

void core()
{
        printf("%s version %s running ...\n",
               PACKAGE_NAME, PACKAGE_VERSION);
        printf("(C) 2008, 2009 Francesco Salvestrini\n");
        printf("\n");
        printf("Please report bugs to <%s>\n",
               PACKAGE_BUGREPORT);
        printf("Visit %s for updates\n",
               PACKAGE_URL);
        printf("\n");

        /* Load kernel image */
#if 0
        if (!load_elf_image("kernel", ,)) {
                panic("Cannot load elf image");
        }
#endif
        /* Call kernel_preload() if available in kernel image */

        /* Perform linking using dl information */

        /* Jump to the entry point */

        /* Argh, we shouldn't have reached this point ... */
        panic("Cannot jump to the entry point");
}
