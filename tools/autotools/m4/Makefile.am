##
## Input file for automake
##
## Copyright (C) 2007, 2008 Francesco Salvestrini
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

##
## Maintainer related targets
##
HOST = "http://git.savannah.gnu.org/cgit/autoconf-archive.git/plain"

DOWNLOAD =						\
	ax_split_version.m4				\
	ax_with_prog.m4					\
	ax_compare_version.m4				\
	ax_cflags_gcc_option.m4				\
	ax_missing_prog.m4				\
	ax_path_missing.m4				\
	ax_gcc_version.m4				\
	ax_gxx_version.m4				\
	ax_gcc_option.m4

MACROS =					\
	$(DOWNLOAD)				\
	ax_arg_with.m4				\
	ax_asm_uscore.m4			\
	ax_blacklist_version.m4			\
	ax_c___asm__.m4				\
	ax_c___attribute__.m4			\
	ax_c___attribute___deprecated.m4	\
	ax_c___attribute___noreturn.m4		\
	ax_c___attribute___section.m4		\
	ax_c___attribute___unused.m4		\
	ax_c___builtin_expect.m4		\
	ax_c_check_flag.m4			\
	ax_c_concatenation.m4			\
	ax_c_empty_structs.m4			\
	ax_c_var___date__.m4			\
	ax_c_var___file__.m4			\
	ax_c_var___function__.m4		\
	ax_c_var___line__.m4			\
	ax_c_var___pretty_func__.m4		\
	ax_c_var___time__.m4			\
	ax_check_symbolic_links.m4		\
	ax_check_vpath_build.m4			\
	ax_cpp_check_flag.m4			\
	ax_cxx_bool.m4				\
	ax_cxx_check_flag.m4			\
	ax_cxx_dtor_after_atexit.m4		\
	ax_cxx_dynamic_cast.m4			\
	ax_cxx_exceptions.m4			\
	ax_cxx_namespaces.m4			\
	ax_cxx_rtti.m4				\
	ax_cxx_static_cast.m4			\
	ax_cxx_templates.m4			\
	ax_cxx_typename.m4			\
	ax_cxxcpp_check_flag.m4			\
	ax_getopt_long.m4			\
	ax_ld_check_flag.m4			\
	ax_remove_forbidden.m4			\
	ax_string_clean.m4			\
	ax_string_intersect.m4

update-local: Makefile
	rm -r -f fetch-dir && \
	mkdir fetch-dir && \
	for i in $(DOWNLOAD) ; do \
		$(FETCH) $(HOST)/$$i fetch-dir/$$i || { \
			rm -f fetch-dir/$$i ; \
			exit 1 ; \
		} \
	done && \
	for i in $(DOWNLOAD) ; do \
		mv fetch-dir/$$i $$i && \
		touch $$i || { \
			exit 1 ; \
		} \
	done && \
	rm -r -f fetch-dir

maintainer-check-local: Makefile
