##### http://autoconf-archive.cryp.to/ac_cxx_dtor_after_atexit.html
#
# SYNOPSIS
#
#   AC_CXX_DTOR_AFTER_ATEXIT
#
# DESCRIPTION
#
#   If the C++ compiler calls global destructors after atexit
#   functions, define HAVE_DTOR_AFTER_ATEXIT. WARNING: If
#   cross-compiling, the test cannot be performed, the default action
#   is to define HAVE_DTOR_AFTER_ATEXIT.
#
# LAST MODIFICATION
#
#   2007-02-28
#
# COPYLEFT
#
#  Copyright (c) 2004 Todd Veldhuizen
#  Copyright (c) 2004 Luc Maisonobe <luc@spaceroots.org>
#  Copyright (c) 2007 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#                     Alessandro Massignan <ff0000.it@gmail.com>
#
#  Copying and distribution of this file, with or without
#  modification, are permitted in any medium without royalty provided
#  the copyright notice and this notice are preserved.

AC_DEFUN([AX_CXX_DTOR_AFTER_ATEXIT],[
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([whether the C++ compiler calls global destructors after functions registered through atexit],[ax_cv_cxx_dtor_after_atexit],[
    AC_LANG_PUSH([C++])
    AC_RUN_IFELSE([
      AC_LANG_PROGRAM([[
#include <unistd.h>
#include <stdlib.h>

static int dtor_called = 0;

class A {
public:
	~A () {
		dtor_called = 1;
	}
};

static A a;

static void f(void)
{
	_exit(dtor_called);
}
      ]],[[
	atexit(f);
	return 0;
      ]])
    ],[
      ax_cv_cxx_dtor_after_atexit=yes
    ],[
      ax_cv_cxx_dtor_after_atexit=no
    ],[
      ax_cv_cxx_dtor_after_atexit=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test "$ax_cv_cxx_dtor_after_atexit" = yes],[
    AC_DEFINE(HAVE_DTOR_AFTER_ATEXIT,,
              [define if the compiler calls global destructors after functions registered through atexit])
  ])
])
