##### http://autoconf-archive.cryp.to/ax_cxx_exceptions.html
#
# SYNOPSIS
#
#   AX_CXX_TEMPLATES
#
# DESCRIPTION
#
#   If the compiler supports basic templates, define HAVE_TEMPLATES.
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

AC_DEFUN([AX_CXX_TEMPLATES],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler supports basic templates],
    [ax_cv_cxx_templates],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        template<class T> class A {
          public:
            A() {
            }
        };
        template<class T> void f(const A<T>& ){
        }
      ]],[[
        A<double> d;
        A<int> i;
        f(d);
        f(i);
        return 0;
      ]])
    ],[
      ax_cv_cxx_templates=yes
    ],[
      ax_cv_cxx_templates=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_templates" = x"yes"],[
    AC_DEFINE(HAVE_TEMPLATES,,
      [define if the compiler supports basic templates])
  ])
])
