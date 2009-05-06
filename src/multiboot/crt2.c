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
#include "libc/ctype.h"
#include "libc/assert.h"
#include "libc/stdlib.h"
#include "libbfd/bfd.h"
#include "multiboot/multiboot.h"
#include "heap.h"
#include "dl.h"
#include "mem.h"
#include "core.h"
#include "constants.h"

#define CHECK_FLAG(FLAGS,BIT) ((FLAGS) & (1 << (BIT)))

static int scan_modules(multiboot_info_t * mbi,
                        uint_t *           base)
{
	assert(mbi);
        assert(base);

        printf("Checking multiboot modules ...\n");

	/* Are mods_* valid?  */
        if (CHECK_FLAG(mbi->flags, 3)) {
		module_t *   mod;
		unsigned int i;
		unsigned int j;

		printf("Handling modules (count = %d, addr = 0x%x)\n",
                       (int) mbi->mods_count, (int) mbi->mods_addr);

		/* NOTE: mods_count may be 0 */
		assert((int) mbi->mods_count >= 0);

		j   = 0;
		mod = (module_t *) mbi->mods_addr;
		for (i = 0; i < mbi->mods_count; i++) {
			assert(mod);
			assert(mod->string);

			printf("   0x%x: (0x%x-0x%x) '%s'\n",
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
                                printf("Heap base moved to 0x%x\n", *base);
                        }
		}
	} else {
		printf("No mod_* infos available in multiboot header\n");
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

        printf("Checking multiboot image ...\n");

	/* Bits 4 and 5 are mutually exclusive!  */
        if (CHECK_FLAG(mbi->flags, 4) && CHECK_FLAG(mbi->flags, 5)) {
                printf("Multiboot image format is both ELF and AOUT ?");
		return 0;
	}

	/* Is the section header table of ELF valid?  */
	if (CHECK_FLAG(mbi->flags, 5)) {
                elf_section_header_table_t * section;
                unsigned int                 num;
                unsigned int                 size;
                unsigned int                 addr;
                unsigned int                 shndx;


                printf("ELF section header table:\n");

                section = &(mbi->u.elf_sec);
                num     = (unsigned int) section->num;
                size    = (unsigned int) section->size;
                addr    = (unsigned int) section->addr;
                shndx   = (unsigned int) section->shndx;

                printf("  num = %u, size = 0x%x, addr = 0x%x, shndx = 0x%x\n",
                       num, size, addr, shndx);

                bfd_image_elf_add(img, (Elf32_Shdr *) addr, num, shndx);

                /*
                 * XXX FIXME:
                 *     We can't assume that modules are ordered in
                 *     memory ...
                 */
                if (*base <= (uint_t) (&(mbi->u.elf_sec) + size)) {
                        *base = (uint_t) (&(mbi->u.elf_sec) + size) + 1;
                        printf("Heap base moved to 0x%x\n", *base);
                }

        } else {
		printf("No ELF section header table available\n");
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
		printf("We have been booted by: '%s'\n",
                       (char *) mbi->boot_loader_name);
	}
#endif

	/* Print out the flags */
	printf("Multiboot flags = 0x%x\n", (unsigned int) mbi->flags);

        heap_base = 0;
        heap_size = 0;

	/* Is memory information available ? */
	if (CHECK_FLAG(mbi->flags, 0)) {
		printf("mem_lower = %d KB, mem_upper = %d KB\n",
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

        /* Look for heap size */
        if (heap_base < 1 * MB) {
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
	assert(heap_initialized());

	/* From this point on we are allowed to use malloc() and free() ... */

        /* Print heap infos */
        printf("Heap base = 0x%x, size = %d KB\n", heap_base, heap_size);

        dl_list_t dl;
        dl = (dl_list_t) xmalloc(sizeof(dl_list_t));

        /* Move interesting information inside dl data */

        /* Call main program */
        core(dl);
}
