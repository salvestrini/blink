##### http://autoconf-archive.cryp.to/ax_cxx_bool.html
#
# SYNOPSIS
#
#   AX_CXX_BOOL
#
# DESCRIPTION
#
#   If the compiler recognizes bool as a separate built-in type, define
#   HAVE_BOOL. Note that a typedef is not a separate type since you
#   cannot overload a function such that it accepts either the basic
#   type or the typedef.
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

AC_DEFUN([AX_CXX_BOOL],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler recognizes bool as a built-in type],
    [ax_cv_cxx_bool],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        int f(int  x) { return 1; }
        int f(char x) { return 1; }
        int f(bool x) { return 1; }
      ]],[[
        bool b = true;
        return f(b);
      ]])
    ],[
      ax_cv_cxx_bool=yes
    ],[
      ax_cv_cxx_bool=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_bool" = x"yes"],[
    AC_DEFINE(HAVE_BOOL,,[define if bool is a built-in type])
  ])
])
