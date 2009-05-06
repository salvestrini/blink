##### http://autoconf-archive.cryp.to/ax_check_awk_int.html
#
# SYNOPSIS
#
#   AX_STRING_CLEAN([VARIABLE])
#
# DESCRIPTION
#
#   Remove duplicated spaces from string.
#
# LAST MODIFICATION
#
#  2007-03-19
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
AC_DEFUN([AX_STRING_CLEAN], [
  AC_REQUIRE([AC_PROG_SED])
  #AC_MSG_NOTICE([**** Input  = $[]$1])
  AS_IF([test -n "$[]$1"],[
    $1=`echo $[]$1 | $SED -e 's, \+, ,g'`
  ])
  #AC_MSG_NOTICE([**** Output = $[]$1])
])
