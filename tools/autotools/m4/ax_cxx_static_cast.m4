##### http://autoconf-archive.cryp.to/ax_cxx_static_cast.html
#
# SYNOPSIS
#
#   AX_CXX_STATIC_CAST
#
# DESCRIPTION
#
#   If the compiler supports static_cast<>, define HAVE_STATIC_CAST.
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

AC_DEFUN([AX_CXX_STATIC_CAST],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler supports static_cast<>],
    [ax_cv_cxx_static_cast],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        #include <typeinfo>
        class Base {
          public:
            Base() {
            }
            virtual void f() = 0;
        };
        class Derived:
          public Base { 
            public:
              Derived() {
              }
              virtual void f() {
              }
        };
        int g (Derived&) {
          return 0;
        }
      ]],[[
        Derived d;
        Base&    b = d;
        Derived& s = static_cast<Derived&> (b);
        return g(s);
      ]])
    ],[
      ax_cv_cxx_static_cast=yes
    ],[
      ax_cv_cxx_static_cast=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_static_cast" = x"yes"],[
    AC_DEFINE(HAVE_STATIC_CAST,,
      [define if the compiler supports static_cast<>])
  ])
])
