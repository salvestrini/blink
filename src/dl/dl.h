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

#ifndef DL_H
#define DL_H

struct dl_segment {
        struct dl_segment * next;
        void *              addr;
        size_t              size;
        unsigned int        section;
};
typedef struct dl_segment * dl_segment_t;

struct dl;

struct dl {
        char *       name;
        dl_segment_t segment;
};
typedef struct dl * dl_t;

struct dl_list
{
        struct dl_list * next;
        dl_t             mod;
};
typedef struct dl_list * dl_list_t;

int  dl_load(void * addr,
             size_t size);

#endif /* DL_H */
