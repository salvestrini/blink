# ===========================================================================
# ===========================================================================
#
# SYNOPSIS
#
#   AX_PROG_GRUB1([PATH],[ACTION-IF-SUCCESS],[ACTION-IF-FAILURE])
#
# DESCRIPTION
#
#
#
# LAST MODIFICATION
#
#   2008-07-31
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   This program is free software; you can redistribute it and/or modify it
#   under the terms of the GNU General Public License as published by the
#   Free Software Foundation; either version 2 of the License, or (at your
#   option) any later version.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
#   Public License for more details.
#
#   You should have received a copy of the GNU General Public License along
#   with this program. If not, see <http://www.gnu.org/licenses/>.
#
#   As a special exception, the respective Autoconf Macro's copyright owner
#   gives unlimited permission to copy, distribute and modify the configure
#   scripts that are the output of Autoconf when processing the Macro. You
#   need not follow the terms of the GNU General Public License when using
#   or distributing such scripts, even though portions of the text of the
#   Macro appear in them. The GNU General Public License (GPL) does govern
#   all other use of the material that constitutes the Autoconf Macro.
#
#   This special exception to the GPL applies to versions of the Autoconf
#   Macro released by the Autoconf Macro Archive. When you make and
#   distribute a modified version of the Autoconf Macro, you may extend this
#   special exception to the GPL to apply to your modified version as well.

AC_DEFUN([AX_PROG_GRUB1], [
  AC_REQUIRE([AC_PROG_SED])
  AC_PATH_PROG([GRUB1_GRUB_INSTALL], [grub-install], [],[$1])

  AS_IF([test -z "$GRUB1_GRUB_INSTALL"],[
    :
    $3
  ],[
    GRUB_VERSION=`$GRUB1_GRUB_INSTALL -v | $SED -e 's,^.*([a-zA-Z ]*,,' -e 's,).*$,,'`

    AX_COMPARE_VERSION($GRUB_VERSION,ge,"0.0",[
      AX_COMPARE_VERSION($GRUB_VERSION,lt,"1.0",[

	# Usually in sbin
	AC_PATH_PROG([GRUB1_GRUB],             [grub],             [],[$1])
	AC_PATH_PROG([GRUB1_GRUB_MD5_CRYPT],   [grub-md5-crypt],   [],[$1])
	AC_PATH_PROG([GRUB1_GRUB_SET_DEFAULT], [grub-set-default], [],[$1])
	AC_PATH_PROG([GRUB1_GRUB_TERMINFO],    [grub-terminfo],    [],[$1])

	# Usually in bin
	AC_PATH_PROG([GRUB1_MBCHK],            [mbchk],            [],[$1])

	$2
      ],[
	:
      ])
    ],[
      :
    ])

  ])
])
