##### http://autoconf-archive.cryp.to/ax_cxx_namespaces.html
#
# SYNOPSIS
#
#   AX_CXX_NAMESPACES
#
# DESCRIPTION
#
#   If the compiler can prevent names clashes using namespaces, define
#   HAVE_NAMESPACES.
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

AC_DEFUN([AX_CXX_NAMESPACES],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler implements namespaces],
    [ax_cv_cxx_namespaces],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        namespace Outer {
          namespace Inner {
            int i = 0;
           }
        }
      ]],[[
        using namespace Outer::Inner;
        return i;
      ]])
    ],[
      ax_cv_cxx_namespaces=yes
    ],[
      ax_cv_cxx_namespaces=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_namespaces" = x"yes"],[
    AC_DEFINE(HAVE_NAMESPACES,,
      [define if the compiler implements namespaces])
  ])
])
