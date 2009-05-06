##### http://autoconf-archive.cryp.to/ax_cxx_rtti.html
#
# SYNOPSIS
#
#   AX_CXX_RTTI
#
# DESCRIPTION
#
#   If the compiler supports Run-Time Type Identification (typeinfo
#   header and typeid keyword), define HAVE_RTTI.
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

AC_DEFUN([AX_CXX_RTTI],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler supports Run-Time Type Identification],
    [ax_cv_cxx_rtti],[
    AC_LANG_PUSH([C++])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        #include <typeinfo>
        class Base {
          public:
            Base() {
            }
            virtual int f() {
              return 0;
            }
        };
        class Derived:
          public Base {
            public:
              Derived() {
              }
              virtual int f() {
                return 1;
              }
          };
      ]],[[
        Derived d;
        Base *ptr = &d;
        return typeid (*ptr) == typeid (Derived);
      ]])
    ],[
      ax_cv_cxx_rtti=yes
    ],[
      ax_cv_cxx_rtti=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_rtti" = x"yes"],[
    AC_DEFINE(HAVE_RTTI,,
              [define if the compiler supports Run-Time Type Identification])
  ])
])
