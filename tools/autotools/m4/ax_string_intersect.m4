##### http://autoconf-archive.cryp.to/ax_check_awk_int.html
#
# SYNOPSIS
#
#   AX_STRING_INTERSECT([VARIABLE],[STRING_A],[STRING_B])
#
# DESCRIPTION
#
#   Intersects values from STRING_A and STRING_B. Places result into VARIABLE
#
# NOTE:
#
#   This macro has a bug, do not place ';' inside STRING_A or STRING_B
#
# LAST MODIFICATION
#
#  2007-03-19
#
# COPYLEFT
#
#  Copyright (c) 2007 Francesco Salvestrini <salvestrini@users.sourceforge.net>
#                     Alessandro Massignan <ff0000.it@gmail.com>
#
#  Copying and distribution of this file, with or without
#  modification, are permitted in any medium without royalty provided
#  the copyright notice and this notice are preserved
#
##########################################################################
AC_DEFUN([AX_STRING_INTERSECT], [
  #AC_MSG_NOTICE([first  = $2])
  #AC_MSG_NOTICE([second = $3])
  $1=""
  AS_IF([test -n "$2"],[
    AS_IF([test -n "$3"],[
      for a in $2 ; do
        #AC_MSG_NOTICE([a = $a])
        for b in $3 ; do
          #AC_MSG_NOTICE([b = $b])
          AS_IF([test x"$a" = x"$b"],[
            v="$a"
            exists="false"
            for c in "$[]$1"; do
              AS_IF([test x"$c" = x"$v"],[
                exists="true"
              ])
            done
            AS_IF([test x"$exists" != x"true"],[
              $1="$[]$1 $v"
            ])
          ])
        done
      done
    ])
  ])
  #AC_MSG_NOTICE([result = $[]$1])
])
