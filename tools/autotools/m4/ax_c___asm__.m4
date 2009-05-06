#####
#
# SYNOPSIS
#
#   AX_C___ASM__
#
# DESCRIPTION
#
#   This macro tests if the C compiler supports the __asm__ extension. Defines
#   HAVE_C__ASM__ if it is supported.
#
# LAST MODIFICATION
#
#  2007-02-18
#
# COPYLEFT
#
#  Copyright (c) 2007 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#  
#  Copying and distribution of this file, with or without
#  modification, are permitted in any medium without royalty provided
#  the copyright notice and this notice are preserved
#
##########################################################################

AC_DEFUN([AX_C___ASM__], [
  AC_PREREQ([2.61])
  AC_CACHE_CHECK([if C compiler supports __asm__],
    [ax_cv_c___asm__],[
      AC_LANG_PUSH(C)
      AC_COMPILE_IFELSE([
        AC_LANG_PROGRAM([
          ],[
            __asm__("");
        ])
      ],[
        ax_cv_c___asm__=yes
      ],[
        ax_cv_c___asm__=no
      ])
      AC_LANG_POP
  ])
  AS_IF([test "$ax_cv_c___asm__" = "yes"],[
    AC_DEFINE(HAVE_C__ASM__, 1, [Define if your C compiler allows __asm__])
  ])
])
