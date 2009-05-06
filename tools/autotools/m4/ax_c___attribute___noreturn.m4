#####
#
# SYNOPSIS
#
#   AX_C___ATTRIBUTE___NORETURN
#
# DESCRIPTION
#
#   Provides a test for the compiler support of __attribute__((noreturn))
#   extensions.
#
#   defines HAVE___ATTRIBUTE___NORETURN if it is found.
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

AC_DEFUN([AX_C___ATTRIBUTE___NORETURN], [
  AC_MSG_CHECKING(if compiler supports __attribute__((noreturn)))
  AC_CACHE_VAL(ax_cv_c__attribute___noreturn, [
    AC_COMPILE_IFELSE(
      AC_LANG_SOURCE([[
static void foo(void) __attribute__ ((noreturn));
static void foo(void)
{
	int a;

	a = 1;
}

int
main(int argc, char **argv)
{
	foo();
}
      ]]),
      ax_cv_c__attribute___noreturn=yes,
      ax_cv_c__attribute___noreturn=no
    )])
  if test "x$ax_cv_c__attribute___noreturn" != "xno" ; then
    AC_DEFINE(HAVE___ATTRIBUTE___NORETURN,,[Define if your compiler allows __attribute__((noreturn))])
  fi
  AC_MSG_RESULT($ax_cv_c__attribute___noreturn)
])
