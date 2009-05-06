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
#include "libc/stdlib.h"
#include "libc/stdio.h"
#include "libc/string.h"
#include "libc/assert.h"
#include "libbfd/elf-format.h"
#include "dl.h"
#include "archs/arch.h"

#if __WORDSIZE == 32

typedef Elf32_Word Elf_Word;
typedef Elf32_Addr Elf_Addr;
typedef Elf32_Ehdr Elf_Ehdr;
typedef Elf32_Shdr Elf_Shdr;
typedef Elf32_Sym  Elf_Sym;

# define ELF_ST_BIND(val) ELF32_ST_BIND(val)
# define ELF_ST_TYPE(val) ELF32_ST_TYPE(val)

#elif __WORDSIZE == 64

typedef Elf64_Word Elf_Word;
typedef Elf64_Addr Elf_Addr;
typedef Elf64_Ehdr Elf_Ehdr;
typedef Elf64_Shdr Elf_Shdr;
typedef Elf64_Sym  Elf_Sym;

# define ELF_ST_BIND(val) ELF64_ST_BIND(val)
# define ELF_ST_TYPE(val) ELF64_ST_TYPE(val)

#else

#error No __WORDSIZE defined

#endif

#if 0
static dl_list_t dl_head;

static dl_t dl_get(const char * name)
{
        dl_list_t l;

        assert(name);

        for (l = dl_head; l; l = l->next) {
                if (strcmp(name, l->mod->name) == 0) {
                        return l->mod;
                }
        }

        return 0;
}

static int dl_add(dl_t mod)
{
        dl_list_t l;

        if (dl_get(mod->name)) {
                printf("Module `%s' already loaded\n", mod->name);
                return 0;
        }

        l = (dl_list_t) malloc(sizeof(*l));
        if (!l) {
                printf("Cannot allocate %d bytes\n", sizeof(*l));
                return 0;
        }

        l->mod  = mod;
        l->next = dl_head;
        dl_head = l;

        return 1;
}

static void dl_remove(dl_t mod)
{
        dl_list_t * p, q;

        for (p = &dl_head, q = *p; q; p = &q->next, q = *p) {
                if (q->mod == mod) {
                        *p = q->next;
                        free(q);
                        return;
                }
        }
}
#endif

struct symbol {
        struct symbol * next;
        const char *    name;
        void *          addr;
        dl_t            mod;
};
typedef struct symbol * symbol_t;

#define SYMTAB_SIZE	509

static struct symbol * symtab[SYMTAB_SIZE];

static unsigned symbol_hash(const char *s)
{
        unsigned key = 0;

        while (*s) {
                key = key * 65599 + *s++;
        }

        return (key + (key >> 5)) % SYMTAB_SIZE;
}

static void * dl_resolve_symbol(const char * name)
{
        symbol_t sym;

        assert(name != 0);

        for (sym = symtab[symbol_hash(name)]; sym; sym = sym->next) {
                if (strcmp(sym->name, name) == 0) {
                        return sym->addr;
                }
        }

        return 0;
}

static int dl_register_symbol(const char * name,
                              void *       addr,
                              dl_t         mod)
{
        symbol_t sym;
        unsigned k;

        sym = (symbol_t) malloc(sizeof(*sym));
        if (!sym) {
                printf("Cannot allocate %d bytes\n", sizeof(*sym));
                return 0;
        }

        if (mod) {
                sym->name = strdup(name);
                if (!sym->name) {
                        printf("Cannot strdup `%s'\n", name);
                        free(sym);
                        return 0;
                }
        } else {
                sym->name = name;
        }

        sym->addr = addr;
        sym->mod  = mod;

        k         = symbol_hash(name);
        sym->next = symtab[k];
        symtab[k] = sym;

        return 1;
}

#if 0
static void dl_unregister_symbols(dl_t mod)
{
        unsigned i;

        assert(mod);

        for (i = 0; i < SYMTAB_SIZE; i++) {
                symbol_t sym, * p, q;

                for (p = &symtab[i], sym = *p; sym; sym = q) {
                        q = sym->next;
                        if (sym->mod == mod) {
                                *p = q;
                                free((void *) sym->name);
                                free(sym);
                        } else {
                                p = &sym->next;
                        }
                }
        }
}
#endif

static void * dl_get_section_addr(dl_t         mod,
                                  unsigned int n)
{
        dl_segment_t seg;

        for (seg = mod->segment; seg; seg = seg->next) {
                if (seg->section == n) {
                        return seg->addr;
                }
        }

        return 0;
}

static int dl_check_header(void * ehdr,
                           size_t size)
{
        Elf_Ehdr * e;

        e = ehdr;
        assert(e);

        if (size < sizeof(Elf_Ehdr)) {
                printf("ELF header smaller than expected\n");
                return 0;
        }

        /* Check the magic numbers.  */
        if (arch_dl_check_header(ehdr)             ||
            (e->e_ident[EI_MAG0]    != ELFMAG0)    ||
            (e->e_ident[EI_MAG1]    != ELFMAG1)    ||
            (e->e_ident[EI_MAG2]    != ELFMAG2)    ||
            (e->e_ident[EI_MAG3]    != ELFMAG3)    ||
            (e->e_ident[EI_VERSION] != EV_CURRENT) ||
            (e->e_version           != EV_CURRENT)) {
                printf("Invalid architecture independent ELF magic\n");
                return 0;
        }

        return 1;
}

static int dl_resolve_symbols(dl_t       mod,
                              Elf_Ehdr * e)
{
        unsigned     i;
        Elf_Shdr *   s;
        Elf_Sym *    sym;
        const char * str;
        Elf_Word     size, entsize;

        for (i = 0, s = (Elf_Shdr *) ((char *) e + e->e_shoff);
             i < e->e_shnum;
             i++, s = (Elf_Shdr *) ((char *) s + e->e_shentsize)) {
                if (s->sh_type == SHT_SYMTAB) {
                        break;
                }
        }

        if (i == e->e_shnum) {
                printf("No symbols table found\n");
                return 0;
        }

        sym     = (Elf_Sym *) ((char *) e + s->sh_offset);
        size    = s->sh_size;
        entsize = s->sh_entsize;

        s   = (Elf_Shdr *) ((char *) e +
                            e->e_shoff +
                            e->e_shentsize * s->sh_link);
        str = (char *) e + s->sh_offset;

        for (i = 0;
             i < size / entsize;
             i++, sym = (Elf_Sym *) ((char *) sym + entsize)) {
                unsigned char type = ELF_ST_TYPE (sym->st_info);
                unsigned char bind = ELF_ST_BIND (sym->st_info);
                const char *  name = str + sym->st_name;

                switch (type) {
                        case STT_NOTYPE:
                                /* Resolve a global symbol.  */
                                if (sym->st_name != 0 && sym->st_shndx == 0) {
                                        sym->st_value = (Elf_Addr) dl_resolve_symbol(name);
                                        if (!sym->st_value)
                                                printf("Cannot find symbol "
                                                       "`%s'\n", name);
                                                return 0;
                                } else {
                                        sym->st_value = 0;
                                }
                                break;

                        case STT_OBJECT:
                                sym->st_value += (Elf_Addr) dl_get_section_addr(mod,
                                                                                sym->st_shndx);
                                if (bind != STB_LOCAL) {
                                        if (dl_register_symbol(name,
                                                               (void *) sym->st_value,
                                                               mod)) {
                                                return 0;
                                        }
                                }
                                break;

                        case STT_FUNC:
                                sym->st_value += (Elf_Addr) dl_get_section_addr(mod,
                                                                                sym->st_shndx);
                                if (bind != STB_LOCAL) {
                                        if (dl_register_symbol(name,
                                                               (void *) sym->st_value,
                                                               mod)) {
                                                return 0;
                                        }
                                }
                                break;

                        case STT_SECTION:
                                sym->st_value = (Elf_Addr) dl_get_section_addr(mod,
                                                                               sym->st_shndx);
                                break;

                        case STT_FILE:
                                sym->st_value = 0;
                                break;

                        default:
                                printf("Unknown symbol type `%d'\n",
                                       (int) type);
                                break;
                }
        }

        return 1;
}

int dl_load(void * addr,
            size_t size)
{
        Elf_Ehdr * e;
        dl_t       mod;

        printf("module at %p, size 0x%lx\n", addr, (unsigned long) size);
        e = addr;
        if (dl_check_header(e, size)) {
                return 0;
        }

        if (e->e_type != ET_REL) {
                printf("Invalid ELF file type\n");
                return 0;
        }

        if (size < e->e_shoff + e->e_shentsize * e->e_shnum) {
                printf("ELF sections outside core\n");
                return 0;
        }

        mod = (dl_t) malloc(sizeof(*mod));
        if (!mod) {
                printf("Cannot allocate %d bytes\n", sizeof(*mod));
                return 0;
        }

        mod->name      = 0;
        mod->segment   = 0;

        if (dl_resolve_symbols(mod, e)) {
                printf("Cannot resolve symbols for module `%s'\n",
                       mod->name);
                return 0;
        }
        if (arch_dl_relocate_symbols(mod, e)) {
                printf("Cannot relocate symbols for module `%s'\n",
                       mod->name);
                return 0;
        }

        return 1;
}
