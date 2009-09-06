##
## Input file for automake
##
## Copyright (C) 2008, 2009 Francesco Salvestrini
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License along
## with this program; if not, write to the Free Software Foundation, Inc.,
## 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
##

include $(top_srcdir)/Makefile.sub

AUTOMAKE_OPTIONS = subdir-objects

CLEANFILES =

bin_PROGRAMS = blink

blink_multiboot_x86_SRCS =			\
	multiboot/x86/crt0.S			\
	multiboot/x86/crt1.c

blink_multiboot_SRCS =				\
	$(blink_multiboot_x86_SRCS)		\
	multiboot/crt2.c			\
	multiboot/multiboot.h

blink_archs_x86_SRCS =				\
	archs/x86/vga.c				\
	archs/x86/vga.h				\
	archs/x86/stdio.c			\
	archs/x86/stdio.h			\
	archs/x86/power.c			\
	archs/x86/port.c			\
	archs/x86/port.h			\
	archs/x86/backtrace.c			\
	archs/x86/dl.c

blink_archs_SRCS =				\
	$(blink_archs_x86_SRCS)			\
	archs/arch.h				\
	archs/asm.h

blink_SOURCES =					\
	$(blink_multiboot_SRCS)			\
	$(blink_archs_SRCS)			\
	heap.c					\
	heap.h					\
	panic.c					\
	dl.c					\
	dl.h					\
	mem.c					\
	mem.h					\
	core.c					\
	core.h					\
	constants.h

LDSCRIPT = $(top_builddir)/src/multiboot/$(architecture)/linker.ld
$(top_builddir)/src/multiboot/$(architecture)/linker.ld: Makefile $(top_srcdir)/src/multiboot/$(architecture)/linker.ld.in
	( rm -f $@ $@.tmp && \
	  $(SED) -e 's,[@]CONFIG_LMA[@],'$(CONFIG_LMA)',g' \
		 -e 's,[@]CONFIG_VMA[@],'$(CONFIG_VMA)',g' \
	  < $(top_srcdir)/src/multiboot/$(architecture)/linker.ld.in > $@.tmp && \
	  chmod -x $@.tmp && \
	  chmod a-w $@.tmp && \
	  mv -f $@.tmp $@ ) || { \
	        rm -f $@ $@.tmp ; \
	        exit 1 ; \
	}
CLEANFILES += $(LDSCRIPT)

blink_DEPENDENCIES = $(LDSCRIPT)
blink_CCASFLAGS    =				\
	$(AX_CONFIG_CCASFLAGS)			\
	$(ELKLIB_CCASFLAGS)			\
	-I$(top_srcdir)/src			\
	-I$(top_builddir)/src
blink_CPPFLAGS     =				\
	$(AX_CONFIG_CPPFLAGS)			\
	$(ELKLIB_CPPFLAGS)			\
	-I$(top_srcdir)/src			\
	-I$(top_builddir)/src
blink_CFLAGS       =				\
	$(AX_CONFIG_CFLAGS)			\
	$(ELKLIB_CFLAGS)
blink_CXXFLAGS     =				\
	$(AX_CONFIG_CXXFLAGS)			\
	$(ELKLIB_CXXFLAGS)
blink_LDFLAGS      =				\
	$(AX_CONFIG_LDFLAGS)			\
	$(ELKLIB_LDFLAGS)			\
	-static					\
	-T $(LDSCRIPT)				\
        -nostartfiles                           \
        -nostdlib                               \
        -nodefaultlibs                          \
        --warn-common                           \
        --warn-section-align                    \
        --warn-constructors                     \
        --no-gc-sections                        \
        --fatal-warnings                        \
        -Wl,--as-needed	
blink_LDADD        =				\
	$(ELKLIB_LDADD)


##
## statistics related
##
stats:
	@$(BFD_SECTION_STAT) -- $(bin_PROGRAMS) || exit 1

##
## map related
##
MAPFILE = system.map
CLEANFILES += $(MAPFILE)
map: Makefile $(bin_PROGRAMS)
	$(NM) -a $(bin_PROGRAMS) > $(MAPFILE) || { \
		rm -f $(MAPFILE) ; \
		exit 1 ; \
	}


##
## Maintainer related targets
##
update-local: Makefile

maintainer-check-whitespaces: Makefile $(blink_SOURCES)
	$(WHITESPACE_DETECT) $(blink_SOURCES)

maintainer-check-local: Makefile maintainer-check-whitespaces
