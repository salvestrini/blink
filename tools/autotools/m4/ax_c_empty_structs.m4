#####
#
# SYNOPSIS
#
#   AX_C_EMPTY_STRUCTS
#
# DESCRIPTION
#
#   AX_C_EMPTY_STRUCTS checks if the compiler allows empty structs.
#   Defines HAVE_EMPTY_STRUCTS if it is allowed.
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

AC_DEFUN([AX_C_EMPTY_STRUCTS], [
  AC_MSG_CHECKING(if compiler allows empty structs)

  AC_CACHE_VAL(ax_cv_c_empty_structs,[
    AC_LANG_PUSH([C])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([
      ],[
        typedef struct { } junk;
      ])
    ],[
      ax_cv_c_empty_structs=yes
    ],[
      ax_cv_c_empty_structs=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test "x$ax_cv_c_empty_structs" != "xno"],[
    AC_DEFINE(HAVE_EMPTY_STRUCTS,,[Define if your compile allows empty structs])
  ])

  AC_MSG_RESULT($ax_cv_c_empty_structs)
])

