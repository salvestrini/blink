#####
#
# SYNOPSIS
#
#   AX_GETOPT_LONG
#
# DESCRIPTION
#
#   Check for getopt_long support. Defines HAVE_GETOPT_LONG if found.
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

AC_DEFUN([AX_GETOPT_LONG],[dnl
  AC_CHECK_FUNCS([getopt_long],[
    # This macro automatically defines HAVE_GETOPT_LONG
	:
  ],[
	:
  ])
])