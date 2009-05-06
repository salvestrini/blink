#####
#
# SYNOPSIS
#
#   AX_C___ATTRIBUTE___DEPRECATED
#
# DESCRIPTION
#
#  Provides a test for the compiler support of __attribute__((deprecated))
#  extensions.
# 
#   Work loosely based on ac_c_var_func macro by Christopher Currie.
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

AC_DEFUN([AX_C___ATTRIBUTE___DEPRECATED], [
  AC_MSG_CHECKING(if compiler supports __attribute__((deprecated)))
  AC_CACHE_VAL(ax_cv_c__attribute___deprecated, [
    AC_COMPILE_IFELSE(
      AC_LANG_SOURCE([[
int foo(void) __attribute__ ((deprecated));
int foo(void)
{
	return 1;
}

int bar(void);
int bar(void)
{
	return 2;
}

int
main(int argc, char **argv)
{
	foo();

	return 0;
}
      ]]),
      ax_cv_c__attribute___deprecated=yes,
      ax_cv_c__attribute___deprecated=no
    )])
  if test "x$ax_cv_c__attribute___deprecated" != "xno" ; then
  AC_DEFINE(HAVE___ATTRIBUTE___DEPRECATED,,[Define if your compiler allows __attribute__((deprecated))])
  fi
  AC_MSG_RESULT($ax_cv_c__attribute___deprecated)
])
