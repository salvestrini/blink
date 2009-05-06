##### http://autoconf-archive.cryp.to/ax_cxx_typename.html
#
# SYNOPSIS
#
#   AX_CXX_TYPENAME
#
# DESCRIPTION
#
#   If the compiler recognizes the typename keyword, define
#   HAVE_TYPENAME.
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

AC_DEFUN([AX_CXX_TYPENAME],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler recognizes typename],
    [ax_cv_cxx_typename],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        template<typename T>class X {
          public:
            X(){
          }
        };
      ]],[[
        X<float> z;
        return 0;
      ]])
    ],[
      ax_cv_cxx_typename=yes
    ],[
      ax_cv_cxx_typename=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_typename" = x"yes"],[
    AC_DEFINE(HAVE_TYPENAME,,
      [define if the compiler recognizes typename])
  ])
])
