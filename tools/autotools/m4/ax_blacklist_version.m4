#####
#
# SYNOPSIS
#
#   AX_BLACKLIST_VERSION(PROGRAM,VERSION,BLACKLIST,ACTION-IF-SUCCESSFUL,ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#   Check if VERSION is inside BLACKLIST. If successful execute 
#   ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL otherwise.
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

AC_DEFUN([AX_BLACKLIST_VERSION],[dnl
  AC_MSG_CHECKING([whether $1 version $2 is blacklisted ($3)])
  if test "`echo \"$3\" | grep \"$2\"`" = "$2" ; then
    AC_MSG_RESULT([yes])
    $4
  else
    AC_MSG_RESULT([no])
    $5
  fi
])
