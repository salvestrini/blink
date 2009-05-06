#####
#
# SYNOPSIS
#
#   AX_TEST_S(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#   Checks if 'test' supports the 'test -s' check. AC_SUBST TEST_S variable to
#   the correct value or 'false' if the specific test is not supported.
#   If successfull execute ACTION-IF-SUCCESSFUL otherwise
#   ACTION-IF-NOT-SUCCESSFUL
#
# LAST MODIFICATION
#
#   2009-01-11
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_TEST_S], [
  AC_CACHE_CHECK([if test supports -s option],[ax_cv_test_s],[
    AS_IF([test -s / >/dev/null 2>&1],[
      test_s='test -s'
      ax_cv_test_s=yes
    ],[
      test_s='false'
      ax_cv_test_s=no
    ])
  ])

  AC_SUBST([TEST_S],[$test_s])

  AS_IF([test "$ax_cv_test_s" = yes],[
    :
    $1
  ],[
    :
    $2
  ])
])

#####
#
# SYNOPSIS
#
#   AX_TEST_E(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#   Checks if 'test' supports the 'test -e' check. AC_SUBST TEST_E variable to
#   the correct value or 'false' if the specific test is not supported
#   If successfull execute ACTION-IF-SUCCESSFUL otherwise
#   ACTION-IF-NOT-SUCCESSFUL
#
# LAST MODIFICATION
#
#   2009-01-11
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_TEST_E], [
  AC_CACHE_CHECK([if test supports -e option],[ax_cv_test_e],[
    AS_IF([test -e / >/dev/null 2>&1],[
      test_e='test -e'
      ax_cv_test_e=yes
    ],[
      test_e='false'
      ax_cv_test_e=no
    ])
  ])

  AC_SUBST([TEST_E],[$test_e])

  AS_IF([test "$ax_cv_test_e" = yes],[
    :
    $1
  ],[
    :
    $2
  ])
])

#####
#
# SYNOPSIS
#
#   AX_TEST_X(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#   Checks if 'test' supports the 'test -x' check. AC_SUBST TEST_X variable to
#   the correct value or 'false' if the specific test is not supported
#   If successfull execute ACTION-IF-SUCCESSFUL otherwise
#   ACTION-IF-NOT-SUCCESSFUL
#
# LAST MODIFICATION
#
#   2009-01-11
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_TEST_X], [
  AC_CACHE_CHECK([if test supports -x option],[ax_cv_test_x],[
    AS_IF([test -x / >/dev/null 2>&1],[
      test_x='test -x'
      ax_cv_test_x=yes
    ],[
      AS_IF([ls -dL / >/dev/null 2>&1],[
        as_ls_L_option=L
      ],[
        as_ls_L_option=
      ])
      as_test_x='
        eval sh -c '\''
        if test -d "$1"; then
          test -d "$1/.";
        else
          case $1 in
          -*)set "./$1";;
          esac;
          case `ls -ld'$as_ls_L_option' "$1" 2>/dev/null` in
          ???[sx]*):;;*)false;;esac;fi
        '\'' sh
      '
      ax_cv_test_x=no
    ])
  ])

  AC_SUBST([TEST_X],[$test_x])

  AS_IF([test "$ax_cv_test_x" = yes],[
    :
    $1
  ],[
    :
    $2
  ])
])

#####
#
# SYNOPSIS
#
#   AX_TEST_R(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#   Checks if 'test' supports the 'test -r' check. AC_SUBST TEST_R variable to
#   the correct value or 'false' if the specific test is not supported
#   If successfull execute ACTION-IF-SUCCESSFUL otherwise
#   ACTION-IF-NOT-SUCCESSFUL
#
# LAST MODIFICATION
#
#   2009-01-11
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_TEST_R], [
  AC_CACHE_CHECK([if test supports -r option],[ax_cv_test_r],[
    touch ./ax_test_file.tmp
    AS_IF([test -r ./ax_test_file.tmp >/dev/null 2>&1],[
      test_r='test -r'
      ax_cv_test_r=yes
    ],[
      test_r='false'
      ax_cv_test_r=no
    ])
    rm -f ./ax_test_file.tmp
  ])

  AC_SUBST([TEST_R],[$test_r])

  AS_IF([test "$ax_cv_test_r" = yes],[
    :
    $1
  ],[
    :
    $2
  ])
])

#####
#
# SYNOPSIS
#
#   AX_TEST_W(ACTION-IF-SUCCESSFUL, ACTION-IF-NOT-SUCCESSFUL)
#
# DESCRIPTION
#
#  Checks if 'test' supports the 'test -w' check. AC_SUBST TEST_W variable to
#  the correct value or 'false' if the specific test is not supported
#  If successfull execute ACTION-IF-SUCCESSFUL otherwise
#  ACTION-IF-NOT-SUCCESSFUL
#
# LAST MODIFICATION
#
#   2009-01-11
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   Copying and distribution of this file, with or without
#   modification, are permitted in any medium without royalty provided
#   the copyright notice and this notice are preserved.

AC_DEFUN([AX_TEST_W], [
  AC_CACHE_CHECK([if test supports -w option],[ax_cv_test_w],[
    touch ./ax_test_file.tmp
    AS_IF([test -w ./ax_test_file.tmp >/dev/null 2>&1],[
      test_w='test -w'
      ax_cv_test_w=yes
    ],[
      test_w='false'
      ax_cv_test_w=no
    ])
    rm -f ./ax_test_file.tmp
  ])

  AC_SUBST([TEST_W],[$test_w])

  AS_IF([test "$ax_cv_test_w" = yes],[
    :
    $1
  ],[
    :
    $2
  ])
])
