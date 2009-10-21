# Process this file with autoconf to produce a configure script.

#
# configure.ac for BLink
#
# Copyright (C) 2008, 2009 Francesco Salvestrini
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

AC_INIT([BLink],
        m4_esyscmd([tools/maint/git-version-gen .tarball-version]),
        [salvestrini@gmail.com],
        [blink],
        [http://github.com/salvestrini/blink])

# Check for a recent version of autoconf
AC_PREREQ([2.64])

# Place/find all autotools related files in the following directories
AC_CONFIG_AUX_DIR([tools/autotools])
AC_CONFIG_MACRO_DIR([tools/autotools/m4])
AC_CONFIG_SRCDIR([src/core.c])

AC_CANONICAL_BUILD
AC_CANONICAL_HOST
AC_CANONICAL_TARGET

#
# For automake options (AM_INIT_AUTOMAKE options) see Makefile.am
# file, AUTOMAKE_OPTIONS variable
#
#AM_INIT_AUTOMAKE([1.10 foreign no-installman no-installinfo -Wall nostdinc])
AM_INIT_AUTOMAKE([1.10 foreign nostdinc std-options -Wall])

#
# Checks for needed programs
#
AC_PROG_GREP
AC_PROG_SED
AC_PROG_INSTALL
AC_PROG_MKDIR_P

AX_PATH_MISSING([BFD_SECTION_STAT], [bfd-section-stat])
AX_PATH_MISSING([PERL],             [perl])
AX_PATH_MISSING([WGET],             [wget])
AX_PATH_MISSING([DNT],              [dnt])


AX_SPLIT_VERSION($PACKAGE_VERSION, AX_MAJOR_VERSION, AX_MINOR_VERSION, AX_MICRO_VERSION, AX_EXTRA_VERSION)
AC_SUBST([PACKAGE_API],[${AX_MAJOR_VERSION}"."${AX_MINOR_VERSION}])

# Gather supported flags while checking programs and their features
AX_CONFIG_CPPFLAGS=""
AX_CONFIG_CFLAGS=""
AX_CONFIG_CXXCPPFLAGS=""
AX_CONFIG_CXXFLAGS=""
AX_CONFIG_LDFLAGS=""

# Assembler
AM_PROG_AS

# C Preprocessor
AC_PROG_CPP

# C Preprocessor flags
AX_CPP_CHECK_FLAG([-W],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -W"
])
AX_CPP_CHECK_FLAG([-Wall],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wall"
])
AX_CPP_CHECK_FLAG([-Werror],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Werror"
])
AX_CPP_CHECK_FLAG([-Wendif-labels],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wendif-labels"
])
AX_CPP_CHECK_FLAG([-Wcast-align],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wcast-align"
])
AX_CPP_CHECK_FLAG([-Wredundant-decls],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wredundant-decls"
])
AX_CPP_CHECK_FLAG([-Wswitch],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wswitch"
])
AX_CPP_CHECK_FLAG([-Wswitch-enum],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wswitch-enum"
])
AX_CPP_CHECK_FLAG([-Wparentheses],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wparentheses"
])
AX_CPP_CHECK_FLAG([-Wimplicit],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wimplicit"
])
AX_CPP_CHECK_FLAG([-Wunused],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wunused"
])
AX_CPP_CHECK_FLAG([-Wmissing-braces],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wmissing-braces"
])
AX_CPP_CHECK_FLAG([-Wreturn-type],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wreturn-type"
])
AX_CPP_CHECK_FLAG([-Wundef],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wundef"
])
AX_CPP_CHECK_FLAG([-Wswitch-default],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wswitch-default"
])
AX_CPP_CHECK_FLAG([-Wchar-subscripts],[],[],[
  TEMP_CPPFLAGS="$TEMP_CPPFLAGS -Wchar-subscripts"
])

# C compiler
AC_PROG_CC([gcc])
AS_IF([test x"$CC" = x"gcc"],[
  gcc_available=1
],[
  gcc_available=0
])
AC_DEFINE_UNQUOTED(HAVE_GCC,$gcc_available,[ Define to 1 if gcc is available ])

# C compiler version
CC_VERSION="unknown"

# Checks for gcc version, blacklist and supported flags
AS_IF([test x"$gcc_available" = x"1"],[
  AX_GCC_VERSION

  CC_VERSION=$GCC_VERSION

  AX_BLACKLIST_VERSION([gcc],$GCC_VERSION,[3.3.6],[
    AC_MSG_FAILURE([Sorry, your compiler is blacklisted.])
  ],[])

  AX_C_CHECK_FLAG([-fno-builtin],[],[],[
    AX_CONFIG_CFLAGS="$AX_CONFIG_CFLAGS -fno-builtin"
  ],[
  ])

  AX_C_CHECK_FLAG([-fmessage-length=0],[],[],[
    AX_CONFIG_CFLAGS="$AX_CONFIG_CFLAGS -fmessage-length=0"
  ],[
  ])

  AX_C_CHECK_FLAG([-fsigned-char],[],[],[
    AX_CONFIG_CFLAGS="$AX_CONFIG_CFLAGS -fsigned-char"
  ],[
  ])

  AX_C_CHECK_FLAG([-Wunreachable-code],[],[],[
    AX_REMOVE_FORBIDDEN(CC, [-Wunreachable-code])
  ],[
  ])

  AX_C_CHECK_FLAG([-Wsequence-point],[],[],[
    AX_REMOVE_FORBIDDEN(CC, [-Wsequence-point])
  ],[
  ])
])

AM_PROG_CC_C_O

# C++ Compiler
AC_PROG_CXX([g++])
AS_IF([test x"$CXX" = x"g++"],[
  gxx_available=1
],[
  gxx_available=0
])
AC_DEFINE_UNQUOTED(HAVE_GXX,$gxx_available,[ Define to 1 if g++ is available ])

# C compiler version
CXX_VERSION="unknown"

# Checks for g++ supported flags
AS_IF([test x"$gxx_available" = x"1"],[
  AX_GXX_VERSION

  CXX_VERSION=$GXX_VERSION

  AX_CXX_CHECK_FLAG([-fno-builtin],[],[],[
    AX_CONFIG_CXXFLAGS="$AX_CONFIG_CXXFLAGS -fno-builtin"
  ],[
  ])
  AX_CXX_CHECK_FLAG([-fno-rtti],[],[],[
    AX_CONFIG_CXXFLAGS="$AX_CONFIG_CXXFLAGS -fno-rtti"
  ],[
  ])
  AX_CXX_CHECK_FLAG([-fno-exceptions],[],[],[
    AX_CONFIG_CXXFLAGS="$AX_CONFIG_CXXFLAGS -fno-exceptions"
  ],[
  ])
  AX_CXX_CHECK_FLAG([-Woverloaded-virtual],[],[],[
    AX_CONFIG_CXXFLAGS="$AX_CONFIG_CXXFLAGS -Woverloaded-virtual"
  ],[
  ])
  AX_CXX_CHECK_FLAG([-fmessage-length=0],[],[],[
    AX_CONFIG_CXXFLAGS="$AX_CONFIG_CXXFLAGS -fmessage-length=0"
  ],[
  ])

  AX_REMOVE_FORBIDDEN(CXX, [-Wunreachable-code -Wsequence-point])
])

AC_PROG_CXX_C_O

# C++ Preprocessor
AC_PROG_CXXCPP

# C++ Preprocessor flags
AX_CXXCPP_CHECK_FLAG([-W],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -W"
])
AX_CXXCPP_CHECK_FLAG([-Wall],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wall"
])
AX_CXXCPP_CHECK_FLAG([-Werror],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Werror"
])
AX_CXXCPP_CHECK_FLAG([-Wendif-labels],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wendif-labels"
])
AX_CXXCPP_CHECK_FLAG([-Wcast-align],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wcast-align"
])
AX_CXXCPP_CHECK_FLAG([-Wredundant-decls],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wredundant-decls"
])
AX_CXXCPP_CHECK_FLAG([-Wswitch],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wswitch"
])
AX_CXXCPP_CHECK_FLAG([-Wswitch-enum],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wswitch-enum"
])
AX_CXXCPP_CHECK_FLAG([-Wparentheses],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wparentheses"
])
AX_CXXCPP_CHECK_FLAG([-Wimplicit],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wimplicit"
])
AX_CXXCPP_CHECK_FLAG([-Wunused],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wunused"
])
AX_CXXCPP_CHECK_FLAG([-Wmissing-braces],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wmissing-braces"
])
AX_CXXCPP_CHECK_FLAG([-Wreturn-type],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wreturn-type"
])
AX_CXXCPP_CHECK_FLAG([-Wundef],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wundef"
])
AX_CXXCPP_CHECK_FLAG([-Wswitch-default],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wswitch-default"
])
AX_CXXCPP_CHECK_FLAG([-Wchar-subscripts],[],[],[
  TEMP_CXXCPPFLAGS="$TEMP_CXXCPPFLAGS -Wchar-subscripts"
])

# Build AX_CONFIG_CPPFLAGS as intersection of TEMP_CPPFLAGS and
# TEMP_CPPCXXFLAGS variable values
AX_STRING_INTERSECT(AX_CONFIG_CPPFLAGS,$TEMP_CPPFLAGS,$TEMP_CXXCPPFLAGS)

# Substitute gathered flags (clean them first)
AX_STRING_CLEAN(AX_CONFIG_CPPFLAGS)
AC_SUBST(AX_CONFIG_CPPFLAGS)
AX_STRING_CLEAN(AX_CONFIG_CFLAGS)
AC_SUBST(AX_CONFIG_CFLAGS)
AX_STRING_CLEAN(AX_CONFIG_CXXFLAGS)
AC_SUBST(AX_CONFIG_CXXFLAGS)

AC_PROG_RANLIB
#AC_PROG_LIBTOOL

#AC_PROG_LN_S
#AX_CHECK_VPATH_BUILD([
#  AX_CHECK_SYMBOLIC_LINKS([],[
#    AC_MSG_ERROR([you are building in a separate directory than the source directory but your system does not support symbolic links ...])
#  ])
#],[
#])

#
# Libraries
#

AC_PATH_PROG(ELKLIB_CONFIG,elklib-config)
AS_IF([test "$ELKLIB_CONFIG" = ""],[
  AC_MSG_ERROR([Could not find elklib-config program])
])
AS_IF([test `$ELKLIB_CONFIG --target-cpus | grep -v $target_cpu` ],[
  AC_MSG_ERROR([Current elklib installation does not support $target_cpu target])
])
AC_PATH_PROG(ELKLIB_CONFIG_TARGET,elklib-config-$target_cpu)
AS_IF([test "$ELKLIB_CONFIG_TARGET" = ""],[
  AC_MSG_ERROR([Could not find elklib-config-$target_cpu program])
])

AC_MSG_CHECKING([elklib --cppflags option])
ELKLIB_CPPFLAGS=`$ELKLIB_CONFIG_TARGET --cppflags`
AS_IF([test "$ELKLIB_CPPFLAGS" == ""],[
  AC_MSG_RESULT([empty])
], [
  AC_MSG_RESULT([$ELKLIB_CPPFLAGS])
])
AC_SUBST([ELKLIB_CPPFLAGS])

AC_MSG_CHECKING([elklib --cflags option])
ELKLIB_CFLAGS=`$ELKLIB_CONFIG_TARGET --cflags`
AS_IF([test "$ELKLIB_CFLAGS" == ""],[
  AC_MSG_RESULT([empty])
], [
  AC_MSG_RESULT([$ELKLIB_CFLAGS])
])
AC_SUBST([ELKLIB_CFLAGS])

AC_MSG_CHECKING([elklib --cxxflags option])
ELKLIB_CXXFLAGS=`$ELKLIB_CONFIG_TARGET --cxxflags`
AS_IF([test "$ELKLIB_CXXFLAGS" == ""],[
  AC_MSG_RESULT([empty])
], [
  AC_MSG_RESULT([$ELKLIB_CXXFLAGS])
])
AC_SUBST([ELKLIB_CXXFLAGS])

AC_MSG_CHECKING([elklib --static-libs option])
ELKLIB_LDADD=`$ELKLIB_CONFIG_TARGET --static-libs`
AS_IF([test "$ELKLIB_LDADD" == ""],[
  AC_MSG_RESULT([empty])
], [
  AC_MSG_RESULT([$ELKLIB_LDADD])
])
AC_SUBST([ELKLIB_LDADD])

#
# Build tools debug option
#
AC_ARG_ENABLE([bt_debug],
  AS_HELP_STRING([--enable-bt-debug],
		 [enable build tools debugging messages]),[
  AC_MSG_NOTICE([build tools debug traces enabled])
  enable_build_tools_debug=yes
],[
  AC_MSG_NOTICE([build tools debug traces disabled])
  enable_build_tools_debug=no
])

#
# Build tools verbose option
#
AC_ARG_ENABLE([bt_verbose],
  AS_HELP_STRING([--enable-bt-verbose],
		 [enable build tools verbose messages]),[
  AC_MSG_NOTICE([build tools verbose tracing enabled])
  enable_build_tools_verbose=yes
],[
  AC_MSG_NOTICE([build tools verbose tracing disabled])
  enable_build_tools_verbose=no
])

#
# Script flags
#
AX_TOOL_FLAGS=""
AS_IF([test "x$enable_build_tools_verbose" = "xyes"],[
  AX_TOOL_FLAGS="$AX_TOOL_FLAGS -v"
#
#   AC_MSG_NOTICE([silencing libtool])
#   LIBTOOLFLAGS="$LIBTOOLFLAGS --silent"
#
])
AS_IF([test "x$enable_build_tools_debug" = "xyes"],[
  AX_TOOL_FLAGS="$AX_TOOL_FLAGS -d"
])
AC_SUBST(AX_TOOL_FLAGS)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_C_CONST
AC_C_VOLATILE
AC_C_STRINGIZE
AC_C_BIGENDIAN([
  AC_DEFINE(WORDS_BIGENDIAN,,[Define if your target machine is big-endian])
  target_endianess="big-endian"
],[
  AC_DEFINE(WORDS_LITTLEENDIAN,,[Define if your target machine is little-endian])
  target_endianess="little-endian"
],[
  AC_MSG_ERROR([target machine endianess cannot be detected ...])
])
AX_C_CONCATENATION
AX_C___ATTRIBUTE__
AX_C___ATTRIBUTE___NORETURN
AX_C___ATTRIBUTE___UNUSED
AX_C___ATTRIBUTE___DEPRECATED
AX_C___ATTRIBUTE___SECTION
AX_C___ASM__
AX_C___BUILTIN_EXPECT
AX_C_EMPTY_STRUCTS
AX_C_VAR___TIME__
AX_C_VAR___DATE__
AX_C_VAR___LINE__
AX_C_VAR___FILE__
AX_C_VAR___FUNCTION__
AX_C_VAR___PRETTY_FUNCTION__
AX_CXX_BOOL
AX_CXX_TEMPLATES
AX_CXX_EXCEPTIONS
AX_CXX_NAMESPACES
AX_CXX_RTTI
AX_CXX_DTOR_AFTER_ATEXIT
AX_CXX_STATIC_CAST
AX_CXX_DYNAMIC_CAST
AX_CXX_TYPENAME
AX_ASM_USCORE

# Make an alias of the current target cpu (it will be useful later)
AS_CASE([$target],
  [ i?86-*-* ],[ architecture="x86"  ],
  [ ppc*     ],[ architecture="ppc32" ],
  [ AC_MSG_ERROR([unknown target $target]) ]
)

# Use the alias defined before in order to define the architecture
AS_CASE([$architecture],
  [ x86   ],[ AC_DEFINE(ARCH_X86,   1, [ 32 bit Intel architecture ]) ],
  [ ppc32 ],[ AC_DEFINE(ARCH_PPC32, 1, [ 32 bit PPC architecture   ]) ],
  [ AC_MSG_ERROR([unknown architecture $architecture]) ]
)

# Architecture variable is needed in some Makefile.am
AC_SUBST(architecture)

# automake conditionals...
AM_CONDITIONAL([SUPPORT_ARCH_X86],   [ test x"$architecture" = x"x86"  ])
AM_CONDITIONAL([SUPPORT_ARCH_PPC32], [ test x"$architecture" = x"ppc32" ])

#
# Autoheader support
#
AC_CONFIG_HEADERS([src/config.h])

## Place header guard (C style)
#AH_TOP([
##ifndef CONFIG_AUTOCONFIG_H
##define CONFIG_AUTOCONFIG_H
#])
#AH_BOTTOM([
##endif /* CONFIG_AUTOCONFIG_H */
#])

# XXX FIXME: Awful, please change it ASAP
AC_SUBST(CONFIG_LMA, 0x00100000)
AC_SUBST(CONFIG_VMA, 0x00100000)

#
# Finally output the configuration
#
AC_CONFIG_FILES([
	Makefile

	docs/Makefile
        docs/info/Makefile

	src/Makefile

	tools/Makefile
	tools/maint/Makefile
	tools/autotools/Makefile
	tools/autotools/m4/Makefile
])

AC_CONFIG_FILES([tools/maint/fetch],               [chmod +x tools/maint/fetch])
AC_CONFIG_FILES([tools/maint/whitespace-detect],   [chmod +x tools/maint/whitespace-detect])
AC_CONFIG_FILES([tools/maint/gitlog-to-committers],[chmod +x tools/maint/gitlog-to-committers])
AC_CONFIG_FILES([tools/maint/gittag-to-date],      [chmod +x tools/maint/gittag-to-date])
AC_CONFIG_FILES([tools/maint/guards-check],        [chmod +x tools/maint/guards-check])

#
# XXX FIXME:
#     Build the correct link to the choosen target architecture. This solution
#     is not portable so it should be removed ASAP !
#AC_CONFIG_LINKS(src/arch:src/archs/$architecture)

AC_OUTPUT

# Header
cat <<EOF

  ${PACKAGE_NAME} ${PACKAGE_API} (${PACKAGE_VERSION}) configuration summary

EOF

# Body
cat <<EOF

   ${PACKAGE_NAME} configuration summary

     Software version : ${PACKAGE_VERSION}

     Host CPU         : ${host_cpu} ($host)
     Build CPU        : ${build_cpu} ($build)
     Target CPU       : ${target_cpu} ($target)

     Architecture     : ${architecture}
     Target endianess : ${target_endianess}

     C preprocessor   : ${CPP}
     C compiler       : ${CC} (version ${CC_VERSION})
     C++ preprocessor : ${CXXCPP}
     C++ compiler     : ${CXX} (version ${CXX_VERSION})
     Assembler        : ${CCAS}
     Archive handler  : ${RANLIB}

     Int. tools flags : ${AX_TOOL_FLAGS}

     C pp flags       : ${AX_CONFIG_CPPFLAGS}
     C flags          : ${AX_CONFIG_CFLAGS}
     C++ pp flags     : ${AX_CONFIG_CXXCPPFLAGS}
     C++ flags        : ${AX_CONFIG_CXXFLAGS}
     Linker flags     : ${AX_CONFIG_LDFLAGS}

   ELKLib configuration summary

     Preprocessor flags : ${ELKLIB_CPPFLAGS}
     C compiler flags   : ${ELKLIB_CFLAGS}
     C++ compiler flags : ${ELKLIB_CXXFLAGS}
     LDADD              : ${ELKLIB_LDADD}

EOF

# Footer
cat <<EOF

   Copyright (C) 2008, 2009 Francesco Salvestrini
   All Rights Reserved.

   The ${PACKAGE_NAME}; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.

   The ${PACKAGE_NAME} is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   Francesco Salvestrini <salvestrini@gmail.com>

EOF
