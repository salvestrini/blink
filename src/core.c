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
#include "core.h"

int load_elf_image(image_t * image)
{
        assert(image);
        assert(image->name);

        printf("Loading image `%s'\n", image->name);

#if 0
        assert(name);
        assert(entry);
        assert(buffer);

        if (!elf_check_buffer((struct Elf32_Header *) buffer)) {
                printf("Image '%s' is not a valid elf image\n", name);
                return 0;
        }

        ** entry = (unsigned long)
                elf_get_entry_point((struct Elf32_Header *) buffer);

        printf("Image '%s' entry point: 0x%lx\n", name, **entry);

        if (!elf_load_buffer(buffer, 1)) {
                return 0;
        }
#endif

        return 1;
}

void core(image_t * images)
{
        assert(images);

        printf("%s version %s running ...\n", PACKAGE_NAME, PACKAGE_VERSION);
        printf("(C) 2008, 2009 Francesco Salvestrini\n");
        printf("\n");
        printf("Please report bugs to <%s>\n", PACKAGE_BUGREPORT);
        printf("Visit %s for updates\n", PACKAGE_URL);
        printf("\n");

        /* Load kernel image */

        image_t * p;

        for (p = images; p != NULL; p = p->next) {
                load_elf_image(p);
        }

        /* Call kernel_preload() if available in kernel image */

        /* Perform linking using dl information */

        /* Jump to the entry point */

        /* Argh, we shouldn't have reached this point ... */
        panic("Cannot jump to the entry point");
}
