#####
#
# SYNOPSIS
#
#   AX_C___ATTRIBUTE__
#
# DESCRIPTION
#
#   Provides a test for the compiler support of __attribute__ extensions.
#   defines HAVE___ATTRIBUTE__ if it is found.
#
#   Originating from the 'pork' package by Ryan McCabe <ryan@numb.org>
#   Changed by Christian Haggstrom <chm@c00.info>
#   Changed again by Francesco Salvestrini <salvestrini@users.sourceforge.net>
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

AC_DEFUN([AX_C___ATTRIBUTE__], [
  AC_MSG_CHECKING(if compiler supports __attribute__)
  AC_CACHE_VAL(ax_cv_c__attribute__, [
    AC_COMPILE_IFELSE(
      AC_LANG_SOURCE([[
static void foo(void) __attribute__ ((unused));
static void foo(void)
{
	int a;

	a = 1;
}

int main(int argc, char **argv) {
	return 0;
}
      ]]),
      ax_cv_c__attribute__=yes,
      ax_cv_c__attribute__=no
    )])
  if test "x$ax_cv_c__attribute__" != "xno" ; then
    AC_DEFINE(HAVE___ATTRIBUTE__,,[Define if your compiler allows __attribute__(())])
  fi
  AC_MSG_RESULT($ax_cv_c__attribute__)
])
