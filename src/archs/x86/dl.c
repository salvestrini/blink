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
#include "libc/stdio.h"
#include "libc/stddef.h"
#include "libc/assert.h"
#include "libbfd/elf-format.h"
#include "dl.h"

int arch_dl_check_header(void * ehdr)
{
        Elf32_Ehdr * e;

        assert(ehdr != NULL);

        e = ehdr;

        if ((e->e_ident[EI_CLASS] != ELFCLASS32) ||
            (e->e_ident[EI_DATA]  != ELFDATA2LSB) ||
            (e->e_machine         != EM_386)) {
                return 0;
        }

        return 1;
}

int arch_dl_relocate_symbols(dl_t   mod,
                             void * ehdr)
{
        Elf32_Ehdr * e;
        Elf32_Shdr * s;
        Elf32_Sym *  symtab;
        Elf32_Word   entsize;
        unsigned int i;

        e = ehdr;

        for (i = 0, s = (Elf32_Shdr *) ((char *) e + e->e_shoff);
             i < e->e_shnum;
             i++, s = (Elf32_Shdr *) ((char *) s + e->e_shentsize)) {
                if (s->sh_type == SHT_SYMTAB)
                        break;
        }

        if (i == e->e_shnum) {
                printf("No symbol table found\n");
                return 0;
        }

        symtab  = (Elf32_Sym *) ((char *) e + s->sh_offset);
        entsize = s->sh_entsize;

        for (i = 0, s = (Elf32_Shdr *) ((char *) e + e->e_shoff);
             i < e->e_shnum;
             i++, s = (Elf32_Shdr *) ((char *) s + e->e_shentsize)) {
                dl_segment_t seg;

                if (s->sh_type != SHT_REL) {
                        continue;
                }

                for (seg = mod->segment; seg; seg = seg->next) {
                        if (seg->section == s->sh_info) {
                                break;
                        }
                }

                if (seg) {
                        Elf32_Rel * rel, * max;

                        for (rel = (Elf32_Rel *) ((char *) e + s->sh_offset),
                                     max = rel + s->sh_size / s->sh_entsize;
                             rel < max;
                             rel++) {
                                Elf32_Word * addr;
                                Elf32_Sym *  sym;

                                if (seg->size < rel->r_offset) {
                                        printf("Relocation offset "
                                               "out of segment\n");
                                        return 0;
                                }

                                addr = (Elf32_Word *) ((char *) seg->addr +
                                                       rel->r_offset);
                                sym  = (Elf32_Sym *)
                                        ((char *) symtab +
                                         entsize * ELF32_R_SYM(rel->r_info));

                                switch (ELF32_R_TYPE(rel->r_info)) {
                                        case R_386_32:
                                                *addr += sym->st_value;
                                                break;

                                        case R_386_PC32:
                                                *addr +=(sym->st_value -
                                                         (Elf32_Word)
                                                         seg->addr -
                                                         rel->r_offset);
                                                break;
                                        default:
                                                assert(0);
                                                break;
                                }
                        }
                }
        }

        return 1;
}
