dnl RSSH_GCC_STDCPLUSPLUS 
dnl
dnl add -lstdc++ to libs, if we use g++
dnl
dnl Author: (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>,
dnl $Id: RSSH_GCC_STDCPLUSPLUS.m4,v 1.1 2002/10/07 07:17:02 tom Exp $
dnl 
dnl RSSH_GCC_STDCPLUSPLUS
dnl
AC_DEFUN(RSSH_GCC_STDCPLUSPLUS,[
AC_REQUIRE([AC_PROG_CXX])
if test "x$rssh_gcc_stdcplusplus_done" != xyes
then
 AC_MSG_CHECKING( add -lstdc++ if this is gcc )
 if test x$GCC = xyes 
 then
  LIBS="$LIBS -lstdc++"
 fi
 rssh_gcc_stdcplusplus_done=yes
fi
AC_MSG_RESULT("$GCC")
])dnl
dnl
