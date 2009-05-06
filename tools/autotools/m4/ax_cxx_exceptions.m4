##### http://autoconf-archive.cryp.to/ax_cxx_exceptions.html
#
# SYNOPSIS
#
#   AX_CXX_EXCEPTIONS
#
# DESCRIPTION
#
#   If the C++ compiler supports exceptions handling (try, throw and
#   catch), define HAVE_EXCEPTIONS.
#
# LAST MODIFICATION
#
#   2006-02-28
#
# COPYLEFT
#
#  Copyright (c) 2004 Todd Veldhuizen
#  Copyright (c) 2004 Luc Maisonobe <luc@spaceroots.org>
#  Copyright (c) 2007 Alessandro Massignan <ff0000.it@gmail.com>
#  Copyright (c) 2007 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#  Copying and distribution of this file, with or without
#  modification, are permitted in any medium without royalty provided
#  the copyright notice and this notice are preserved.

AC_DEFUN([AX_CXX_EXCEPTIONS],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler supports exceptions],
    [ax_cv_cxx_exceptions],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([],[[
        try {
          throw 1;
        }
        catch(int i) {
          return i;
        }
      ]])
    ],[
      ax_cv_cxx_exceptions=yes
    ],[
      ax_cv_cxx_exceptions=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_exceptions" = x"yes"],[
    AC_DEFINE(HAVE_EXCEPTIONS,,
      [define if the compiler supports exceptions])
  ])
])
