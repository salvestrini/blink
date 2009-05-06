dnl @synopsis AX_CHECK_VPATH_BUILD(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
dnl
dnl Checks if the build is a VPATH build. If successfull execute
dnl ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL otherwise 
dnl
dnl Written by Francesco Salvestrini
dnl
dnl @version $Id$
dnl @author Francesco Salvestrini <salvestrini@users.sourceforge.net>
AC_DEFUN([AX_CHECK_VPATH_BUILD], [
  AC_MSG_CHECKING([if build is a VPATH build])
  if test "`cd $srcdir; /bin/pwd`" = "`/bin/pwd`"; then
    AC_MSG_RESULT([no])
    $2
  else
    AC_MSG_RESULT([yes])
    $1
  fi
])
