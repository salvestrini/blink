#####
#
# SYNOPSIS
#
#   AX_C_VAR_FUNCTION
#
# DESCRIPTION
#
#   This macro tests if the C compiler supports the C9X standard
#   __FUNCTION__ indentifier.
# 
#   Work loosely based on ac_c_var_func macro by Christopher Currie.
#
# LAST MODIFICATION
#
#   2008-02-29
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_C_VAR___FUNCTION__],[
  AC_REQUIRE([AC_PROG_CC])
  AC_CACHE_CHECK([whether $CC recognizes __FUNCTION__],[ax_cv_c_var_function],[
    AC_LANG_PUSH([C])

    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([],[ int main() { char *s = __FUNCTION__; } ])
    ],[
      ax_cv_c_var_function=yes
    ],[
      ax_cv_c_var_function=no
    ])

    AC_LANG_POP
  ])

  AS_IF([test "x$ax_cv_c_var_function" != "xno"],[
    AC_DEFINE(HAVE___FUNCTION__,,[Define to 1 if the C complier supports __FUNCTION__])
  ])
])
