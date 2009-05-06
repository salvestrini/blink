#####
#
# SYNOPSIS
#
#   AX_C___ATTRIBUTE___SECTION
#
# DESCRIPTION
#
#   Provides a test for the compiler support of __attribute__((section))
#   extensions.
#   
#   defines HAVE___ATTRIBUTE___SECTION if it is found.
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

AC_DEFUN([AX_C___ATTRIBUTE___SECTION], [
  AC_MSG_CHECKING(if compiler supports __attribute__((section)))
  AC_CACHE_VAL(ax_cv_c__attribute___section, [
    AC_COMPILE_IFELSE(
      AC_LANG_SOURCE([[
int x __attribute__ ((section ("MYSECTION"))) = 3;

int
main(int argc, char **argv)
{
	return 0;
}
      ]]),
      ax_cv_c__attribute___section=yes,
      ax_cv_c__attribute___section=no
    )])
  if test "x$ax_cv_c__attribute___section" != "xno" ; then
    AC_DEFINE(HAVE___ATTRIBUTE___SECTION,,[Define if your compiler allows __attribute__((section))])
  fi
  AC_MSG_RESULT($ax_cv_c__attribute___section)
])
