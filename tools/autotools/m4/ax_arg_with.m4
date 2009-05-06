#####
#
# SYNOPSIS
#
#   AX_ARG_WITH
#
# DESCRIPTION
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

AC_DEFUN([AX_ARG_WITH],[
	AC_MSG_CHECKING([if $1 is requested])

	AC_ARG_WITH([$1],
		    AS_HELP_STRING([--with-$1],[use $1 (default is $2)]),[
			ax_arg_with_$1=$withval
		    ],[
			ax_arg_with_$1=$2
	])

	AC_MSG_RESULT($ax_arg_with_$1)
])
