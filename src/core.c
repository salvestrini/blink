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
#include "libc/stddef.h"
#include "libc/stdlib.h"
#include "libc/assert.h"
#include "libc/string.h"
#include "archs/arch.h"
#include "misc.h"
#include "core.h"
#include "log.h"

void * elf_image_symbol_lookup(image_t *    image,
                               const char * symbol)
{
        assert(image);
        assert(symbol);

        return NULL;
}

int elf_images_link(image_t * images)
{
        assert(images);

        /* XXX FIXME: This procedure is a shame, please use a better one ! */

        image_t * p;
        for (p = images; p != NULL; p = p->next) {
                image_t * q;

                for (q = images; q != NULL; q = q->next) {
                }
        }

        return 1;
}

void core(image_t * images)
{
        log("%s version %s running ...\n", PACKAGE_NAME, PACKAGE_VERSION);
        log("(C) 2008, 2009 Francesco Salvestrini\n");
        log("\n");
        log("Please report bugs to <%s>\n", PACKAGE_BUGREPORT);
        log("Visit %s for updates\n", PACKAGE_URL);
        log("\n");

        /* Load kernel image */
        image_t * kernel;
        image_t * p;

        kernel = NULL;
        for (p = images; p != NULL; p = p->next) {
                if (!strcmp(p->name, "kernel")) {
                        /* We got the kernel image */
                        kernel = p;

                        /* Does the image provide a kernel_preload() symbol? */
                        int (* kernel_preload)(void);
                        kernel_preload =
                                elf_image_symbol_lookup(kernel,
                                                        "kernel_preload");

                        /* Call kernel_preload() if available */
                        if (kernel_preload) {
                                if (!kernel_preload()) {
                                        hang("Cannot preload kernel image");
                                }
                        }
                }
        }

        if (!kernel) {
                hang("Cannot find a valid kernel image");
        }

        /* Perform linking over all available images */
        if (!elf_images_link(images)) {
                hang("Cannot perform linking");
        }

        /* Jump to the entry point */
        int (* kernel_start)(void);
        kernel_start = elf_image_symbol_lookup(kernel, "kernel_start");
        if (!kernel_start) {
                hang("Cannot find kernel entry point");
        }
        kernel_start();

        /* Argh, we shouldn't have reached this point ... */
        hang("???");
}
