#####
#
# SYNOPSIS
#
#   AX_C___ATTRIBUTE___UNUSED
#
# DESCRIPTION
#
#   Provides a test for the compiler support of __attribute__((unused))
#   extensions.
#
#   defines HAVE___ATTRIBUTE___UNUSED if it is found.
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

AC_DEFUN([AX_C___ATTRIBUTE___UNUSED], [
  AC_MSG_CHECKING(if compiler supports __attribute__((unused)))
  AC_CACHE_VAL(ax_cv_c__attribute___unused, [
    AC_COMPILE_IFELSE(
      AC_LANG_SOURCE([[
int
main(int argc, char **argv)
{
	int a  __attribute__ ((unused));

	return 0;
}
      ]]),
      ax_cv_c__attribute___unused=yes,
      ax_cv_c__attribute___unused=no
    )])
  if test "x$ax_cv_c__attribute___unused" != "xno" ; then
    AC_DEFINE(HAVE___ATTRIBUTE___UNUSED,,[Define if your compiler allows __attribute__((unused))])
  fi
  AC_MSG_RESULT($ax_cv_c__attribute___unused)
])
