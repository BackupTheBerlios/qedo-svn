dnl autoconf macroses for detecting mico (http://www.ooc.com)
dnl (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
dnl $Id: RSSH_CHECK_MICO.m4,v 1.1 2002/10/07 07:17:02 tom Exp $
dnl
AC_DEFUN(RSSH_CHECK_MICO,[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl

AC_CHECKING(for MICO)

mico=no

AC_ARG_WITH(mico, [mico: prefix to MICO installation (default: /usr/local) ],\
            MICO_PREFIX=${with_mico} , MICO_PREFIX=/usr/local )

AC_CHECKING(for mico)

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

if test ! $MICO_PREFIX = no
then


svCPPFLAGS=$CPPFLAGS
svCXXFLAGS=$CXXFLAGS
svCXXCPPFLAGS=$CXXCPPFLAGS
svLIBS=$LIBS
svRSSH_ROLLBACK=$rssh_rollback
rssh_rollback=true

CXXCPPFLAGS="$CXXCPPFLAGS  -I$MICO_PREFIX/include"
CPPFLAGS="$CPPFLAGS  -I$MICO_PREFIX/include"

AC_CHECK_HEADER( CORBA-SMALL.h, mico=yes , mico=no )
else
 mico=no
fi

if test "x$mico" = "xyes"
then

MICO_VERSION=` sed -n '/MICO_VERSION/ { y/b/./; s#^[^"]*"\([^"]*\)".*#\1#p; }' "$MICO_PREFIX/include/mico/version.h" `

if test -z "$MICO_VERSION"
then
AC_MSG_WARN(no MICO version found in $MICO_PREFIX/include/mico/version.h)
fi
AC_SUBST(MICO_VERSION)
AC_CHECK_LIB(socket,socket, LIBS="-lsocket $LIBS",,)
AC_CHECK_LIB(nsl,gethostbyname, LIBS="-lnsl $LIBS",,)

LIBS="-L$MICO_PREFIX/lib -lmico$MICO_VERSION -lpthread -lposix4 -lssl -lcrypto -ldl -lelf -lsocket -lnsl $LIBS"
         
AC_SUBST(MICO_PREFIX)

ORB_PREFIX=$MICO_PREFIX
AC_SUBST(ORB_PREFIX)

ORB=MICO
AC_SUBST(ORB)


IDL="$MICO_PREFIX/bin/idl --c++-skel"
AC_SUBST(IDL,$IDL)
IDLCXX=$IDL
AC_SUBST(IDLCXX,$IDLCXX)

IDLFLAGS="$IDLFLAGS -I$MICO_PREFIX/include"
AC_SUBST(IDLFLAGS)

ORB_INCLUDE_PREFIX=mico
AC_SUBST(ORB_INCLUDE_PREFIX)


IDL_CLN_H=.h
IDL_CLN_H_SUFFIX=.h
IDL_CLN_H1_SUFFIX=no
AC_SUBST(IDL_CLN_H,$IDL_CLN_H)
AC_SUBST(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)
AC_SUBST(IDL_CLN_H1_SUFFIX,$IDL_CLN_H1_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_CLN_H,$IDL_CLN_H)
AC_DEFINE_UNQUOTED(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)

IDL_CLN_CPP=.cc
IDL_CLN_CPP_SUFFIX=.cc
AC_SUBST(IDL_CLN_CPP,$IDL_CLN_CPP)
AC_SUBST(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)
AC_DEFINE_UNQUOTED(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)

IDL_CLN_O=.o 
IDL_CLN_OBJ_SUFFIX=.o 
AC_SUBST(IDL_CLN_O,$IDL_CLN_O)
AC_SUBST(IDL_CLN_OBJ_SUFFIX,$IDL_CLN_OBJ_SUFFIX)

IDL_SRV_H=.h
IDL_SRV_H_SUFFIX=.h
IDL_SRV_H1_SUFFIX=no 
AC_SUBST(IDL_SRV_H,$IDL_SRV_H)
AC_SUBST(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)
AC_SUBST(IDL_SRV_H1_SUFFIX,$IDL_SRV_H1_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H)

IDL_SRV_CPP=_skel.cc
IDL_SRV_CPP_SUFFIX=_skel.cc
AC_SUBST(IDL_SRV_CPP,$IDL_SRV_CPP)
AC_SUBST(IDL_SRV_CPP_SUFFIX,$IDL_SRV_CPP)

IDL_SRV_O=_skel.o
IDL_SRV_OBJ_SUFFIX=_skel.o
AC_SUBST(IDL_SRV_O,$IDL_SRV_O)
AC_SUBST(IDL_SRV_OBJ_SUFFIX,$IDL_SRV_O)

IDL_TIE_H_SUFFIX=.h
IDL_TIE_H1_SUFFIX=no
IDL_TIE_CPP_SUFFIX=no
AC_SUBST(IDL_TIE_H_SUFFIX,$IDL_TIE_H_SUFFIX)
AC_SUBST(IDL_TIE_H1_SUFFIX,$IDL_TIE_H1_SUFFIX)
AC_SUBST(IDL_TIE_CPP_SUFFIX,$IDL_TIE_CPP_SUFFIX)


CORBA_H='CORBA.h'
AC_DEFINE_UNQUOTED(CORBA_H,<$CORBA_H>)

COSNAMING_H='CosNaming.h'
AC_DEFINE_UNQUOTED(COSNAMING_H,<$COSNAMING_H>)
ORB_COSNAMING_LIB="-lmicocoss"
AC_SUBST(ORB_COSNAMING_LIB)

dnl AC_CACHE_CHECK("if OB_INTEGER_VERSION defined",
dnl rssh_cv_have_ob_integer_version,
dnl AC_TRY_COMPILE(#include <$CORBA_H>
dnl ,
dnl [
dnl #ifndef OB_INTEGER_VERSION
dnl #error "OB_INTEGER_VERSION_NOT_DEFINED"
dnl ob integer version not defined and C++ compiler think, that errors are warning
dnl #else
dnl return 0;
dnl #endif
dnl ], rssh_cv_have_ob_integer_version=1, rssh_cv_have_ob_integer_version=0)
dnl )


dnl if test "x$rssh_cv_have_ob_integer_version" = "x1" 
dnl then
dnl AC_CACHE_CHECK("if this is 4.x branch ",
dnl rssh_cv_ob_4,
dnl AC_TRY_COMPILE(#include <$CORBA_H>
dnl ,
dnl [
dnl #if (OB_INTEGER_VERSION >= 3999951L )
dnl return 0;
dnl #else
dnl #error "qqq"
dnl ob integer version < ,,, but C++ compiler think, that errors are warning
dnl #endif
dnl ],rssh_cv_ob_4=yes,rssh_cv_ob_4=no)
dnl )
dnl fi


dnl if test "x$rssh_cv_ob_4" = "xyes" 
dnl then
AC_DEFINE(CORBA_MODULE_NAMESPACE_MAPPING)
AC_DEFINE(CORBA_HAVE_POA)
HAVE_ORB_IDL=1
AC_DEFINE(CORBA_SYSTEM_EXCEPTION_IS_STREAMBLE)
AC_DEFINE(CORBA_ORB_HAVE_DESTROY)
dnl else
dnl HAVE_ORB_IDL=0
dnl AC_DEFINE(CORBA_MODULE_C_MAPPING)
dnl CORBA_SKELETON_SUFFIX=_skel
dnl AC_DEFINE_UNQUOTED(CORBA_SKELETON_SUFFIX,$CORBA_SKELETON_SUFFIX)
dnl fi
AC_SUBST(HAVE_ORB_IDL)
  
AC_DEFINE(MICO,1,[Define if mico is present])

else

CPPFLAGS=$svCPPFLAGS
CXXCPPFLAGS=$svCXXCPPFLAGS
CXXFLAGS=$svCXXFLAGS
LIBS=$svLIBS
eval "$rssh_rollback"
rssh_rollback="$svRSSH_ROLLBACK"

fi

AC_LANG_RESTORE

AC_MSG_RESULT(mico check result: $mico)

])dnl
dnl
