##### http://autoconf-archive.cryp.to/ax_cxx_dynamic_cast.html
#
# SYNOPSIS
#
#   AX_CXX_DYNAMIC_CAST
#
# DESCRIPTION
#
#   If the compiler supports dynamic_cast<>, define HAVE_DYNAMIC_CAST.
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

AC_DEFUN([AX_CXX_DYNAMIC_CAST],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler supports dynamic_cast<>],
    [ax_cv_cxx_dynamic_cast],[
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
      ]],[[
        Derived d;
        Base&   b = d; 
        return dynamic_cast<Derived*>(&b) ? 0 : 1;
      ]])
    ],[
      ax_cv_cxx_dynamic_cast=yes
    ],[
      ax_cv_cxx_dynamic_cast=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test x"$ax_cv_cxx_dynamic_cast" = x"yes"],[
    AC_DEFINE(HAVE_DYNAMIC_CAST,,
      [define if the compiler supports dynamic_cast<>])
  ])
])
