#####
#
# SYNOPSIS
#
#   AX_CHECK_SYMBOLIC_LINKS(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#   Checks if the build system supports symbolic links. If successfull execute
#   ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL otherwise 
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

AC_DEFUN([AX_CHECK_SYMBOLIC_LINKS], [
  AC_REQUIRE([AC_PROG_LN_S])
  AC_MSG_CHECKING([if build system supports symbolic links])
  if test "$LN_S" = "ln -s" ; then
    AC_MSG_RESULT([yes])
    $1
  else
    AC_MSG_RESULT([no])
    $2
  fi
])
