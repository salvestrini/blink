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
#include "libc/stdint.h"
#include "libc/string.h"
#include "libc/ctype.h"
#include "libc/assert.h"
#include "libc/stdlib.h"
#include "libbfd/bfd.h"
#include "boot/multiboot.h"
#include "mem/heap.h"
#include "mem/mem.h"
#include "core.h"
#include "log.h"

#define CHECK_FLAG(FLAGS,BIT) ((FLAGS) & (1 << (BIT)))

#define MAX_IMAGES_COUNT 64

image_t images[MAX_IMAGES_COUNT];

#if 0
static void fill_dl(multiboot_info_t * mbi,
                    dl_list_t *        dl)
{
        assert(mbi);
        assert(dl);

        log("Building dl list ...");

        module_t *   mod;
        unsigned int i;
        unsigned int j;

        log("Handling modules (count = %d, addr = 0x%x)",
            (int) mbi->mods_count, (int) mbi->mods_addr);

        /* NOTE: mods_count may be 0 */
        assert((int) mbi->mods_count >= 0);

        j   = 0;
        mod = (module_t *) mbi->mods_addr;
        for (i = 0; i < mbi->mods_count; i++) {
                log("  dl-loading module `%s'", mod->string);
                dl_load((void *) mod->mod_start,
                        mod->mod_end - mod->mod_start + 1);
        }
}
#endif

static int scan_modules(multiboot_info_t * mbi,
                        uint_t *           base)
{
        assert(mbi);
        assert(base);

        log("Checking multiboot modules ...");

        /* Are mods_* valid?  */
        if (CHECK_FLAG(mbi->flags, 3)) {
                module_t *   mod;
                unsigned int i;
                unsigned int j;

                log("Handling modules (count = %d, addr = 0x%x)",
                    (int) mbi->mods_count, (int) mbi->mods_addr);

                /* NOTE: mods_count may be 0 */
                assert((int) mbi->mods_count >= 0);

                j   = 0;
                mod = (module_t *) mbi->mods_addr;
                for (i = 0; i < mbi->mods_count; i++) {
                        assert(mod);
                        assert(mod->string);

                        log("   0x%x: (0x%x-0x%x) '%s'",
                            mod,
                            (unsigned int) mod->mod_start,
                            (unsigned int) mod->mod_end,
                            (char *)       mod->string);

                        assert(mod->mod_start);
                        assert(mod->mod_end);
                        assert(mod->mod_start <= mod->mod_end);

                        /*
                         * XXX FIXME:
                         *     We can't assume that modules are ordered in
                         *     memory ...
                         */
                        if (*base <= mod->mod_end) {
                                *base = mod->mod_end + 1;
                                log("Heap base moved to 0x%x", *base);
                        }
                }
        } else {
                log("No mod_* infos available in multiboot header");
        }

        return 1;
}

static int scan_myself(multiboot_info_t * mbi,
                       bfd_image_t *      img,
                       uint_t *           base)
{
        assert(mbi);
        assert(img);
        assert(base);

        log("Checking multiboot image ...");

        /* Bits 4 and 5 are mutually exclusive!  */
        if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5)) {
                log("Multiboot image format is both ELF and AOUT ?");
                return 0;
        }

        /* Is the section header table of ELF valid?  */
        if (CHECK_FLAG(mbi->flags, 5)) {
                elf_section_header_table_t * section;
                unsigned int                 num;
                unsigned int                 size;
                unsigned int                 addr;
                unsigned int                 shndx;


                log("ELF section header table:");

                section = &(mbi->u.elf_sec);
                num     = (unsigned int) section->num;
                size    = (unsigned int) section->size;
                addr    = (unsigned int) section->addr;
                shndx   = (unsigned int) section->shndx;

                log("  num = %u, size = 0x%x, addr = 0x%x, shndx = 0x%x",
                    num, size, addr, shndx);

                bfd_image_elf_add(img, (Elf32_Shdr *) addr, num, shndx);

                /*
                 * XXX FIXME:
                 *     We can't assume that modules are ordered in
                 *     memory ...
                 */
                if (*base <= (uint_t) (&(mbi->u.elf_sec) + size)) {
                        *base = (uint_t) (&(mbi->u.elf_sec) + size) + 1;
                        log("Heap base moved to 0x%x", *base);
                }

        } else {
                log("No ELF section header table available");
                return 0;
        }

        return 1;
}

static bfd_image_t blink_image;

void crt2(multiboot_info_t * mbi)
{
        uint_t heap_base;
        uint_t heap_size;

        assert(mbi);

#if 0
        if (CHECK_FLAG(mbi->flags, 9)) {
                log("We have been booted by: '%s'",
                    (char *) mbi->boot_loader_name);
        }
#endif

        /* Print out the flags */
        log("Multiboot flags = 0x%x", (unsigned int) mbi->flags);

        heap_base = 0;
        heap_size = 0;

        /* Is memory information available ? */
        if (CHECK_FLAG(mbi->flags, 0)) {
                log("mem_lower = %d KB, mem_upper = %d KB",
                    (unsigned int) mbi->mem_lower,
                    (unsigned int) mbi->mem_upper);
        }

        if (!bfd_init()) {
                panic("Cannot initialize bfd subsystem");
        }

        /* Check multiboot infos while looking for our heap base */
        if (!scan_myself(mbi, &blink_image, &heap_base)) {
                panic("Cannot scan image info correctly");
        }
        if (!scan_modules(mbi, &heap_base)) {
                panic("Cannot scan modules infos correctly");
        }
        if (heap_base == 0) {
                panic("Cannot detect heap base");
        }

        /* XXX FIXME: Move the following code to an arch-dependant place */
        /* Look for heap size */
        if (heap_base < 1 * 1024 * 1024) {
                /* Consider lower memory */
        } else {
                /* Consider only upper memory */
                heap_size = (unsigned int) mbi->mem_upper;
        }
        if (heap_size == 0) {
                panic("Cannot detect heap size");
        }

        /* Initialize the heap now */
        if (!heap_init(heap_base, heap_size)) {
                panic("Cannot initialize heap");
        }
        log("Heap base = 0x%x, size = %d KB", heap_base, heap_size);
        assert(heap_initialized());

        /*
         * From this point on we are allowed to use malloc() and free() ...
         */

#if 0
        /* Move interesting information inside dl data */
        dl_list_t dl;
        dl = (dl_list_t) xmalloc(sizeof(dl_list_t));
        fill_dl(mbi, &dl);
#endif

        /* Call main program */
        core(images);
}
