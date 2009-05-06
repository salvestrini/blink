#####
#
# SYNOPSIS
#
#   AX_C_CONCATENATION
#
# DESCRIPTION
#
#   Provides a test for the compiler support of concatenation.
#   defines HAVE_CONCATENATION if it is found.
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

AC_DEFUN([AX_C_CONCATENATION], [
  AC_MSG_CHECKING(if compiler supports concatenation)

  AC_CACHE_VAL(ax_cv_concatenation,[
    AC_LANG_PUSH([C])
    AC_COMPILE_IFELSE([
      AC_LANG_PROGRAM([[
        #define MACRO(PARM1,PARM2,PARM3) char* PARM1##PARM2##PARM3;
      ]],
      [
        MACRO(This,Is,AString);
      ])
    ],[
        ax_cv_concatenation=yes
    ],[
        ax_cv_concatenation=no
    ])
    AC_LANG_POP
  ])

  AS_IF([test "x$ax_cv_concatenation" != "xno"],[
    AC_DEFINE(HAVE_CONCATENATION,,[Define if your compiler support concatenation])
  ])

  AC_MSG_RESULT($ax_cv_concatenation)
])
