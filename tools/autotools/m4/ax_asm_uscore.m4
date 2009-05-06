#####
#
# SYNOPSIS
#
#   AX_PROG_BISON(ACTION-IF-TRUE,ACTION-IF-FALSE)
#
# DESCRIPTION
#
#   Checks if C symbols get an undescoreafter compiling to assembler.
#   defines HAVE___ATTRIBUTE__ if it is found.
#   
#   Written by Pavel Roskin. Based on grub_ASM_EXT_C written by
#   Erich Boleyn and modified by OKUJI Yoshinori
#   Rearranged by <salvestrini@users.sourceforge.net>
#
# LAST MODIFICATION
#
#   2008-02-28
#
# COPYLEFT
#
#   Copyright (c) 2008 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#
#   This program is free software; you can redistribute it and/or
#   modify it under the terms of the GNU General Public License as
#   published by the Free Software Foundation; either version 2 of the
#   License, or (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful, but
#   WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
#   General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
#   02111-1307, USA.
#
#   As a special exception, the respective Autoconf Macro's copyright
#   owner gives unlimited permission to copy, distribute and modify the
#   configure scripts that are the output of Autoconf when processing
#   the Macro. You need not follow the terms of the GNU General Public
#   License when using or distributing such scripts, even though
#   portions of the text of the Macro appear in them. The GNU General
#   Public License (GPL) does govern all other use of the material that
#   constitutes the Autoconf Macro.
#
#   This special exception to the GPL applies to versions of the
#   Autoconf Macro released by the Autoconf Macro Archive. When you
#   make and distribute a modified version of the Autoconf Macro, you
#   may extend this special exception to the GPL to apply to your
#   modified version as well.

AC_DEFUN([AX_ASM_USCORE], [
  AC_REQUIRE([AC_PROG_CC])
  AC_MSG_CHECKING([if C symbols get an underscore after compilation])
  AC_CACHE_VAL(ax_cv_asm_uscore,[
cat > conftest.c <<\EOF
int
func (int *list)
{
  *list = 0;
  return *list;
}
EOF

if AC_TRY_COMMAND([${CC-cc} ${CFLAGS} -S conftest.c]) && test -s conftest.s; then
  true
else
  AC_MSG_ERROR([${CC-cc} failed to produce assembly code])
fi

if grep _func conftest.s >/dev/null 2>&1; then
  ax_cv_asm_uscore=yes
else
  ax_cv_asm_uscore=no
fi

rm -f conftest*
])

  if test "x$ax_cv_asm_uscore" = xyes; then
    AC_DEFINE_UNQUOTED([HAVE_ASM_USCORE],,[Define if C symbols get an underscore after compilation])
  fi

  AC_MSG_RESULT([$ax_cv_asm_uscore])
])
