dnl aclocal.m4 generated automatically by aclocal 1.4-p1

dnl Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl This program is distributed in the hope that it will be useful,
dnl but WITHOUT ANY WARRANTY, to the extent permitted by law; without
dnl even the implied warranty of MERCHANTABILITY or FITNESS FOR A
dnl PARTICULAR PURPOSE.

#@synonips RSSH_PROG_CXXAR
#
# check for program, which we use for creating static C++ libraries.
#   set it name to AR, flags to ARFLAGS
#
#@author   (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998, 2000
#@id $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
#
AC_DEFUN(RSSH_PROG_CXXAR,[
AC_REQUIRE([AC_PROG_CXX])
AC_REQUIRE([RSSH_CHECK_SUNPRO_CC])
if test x$rssh_cv_check_sunpro_cc = xyes
then
  AR=CC
  ARFLAGS="\$(CXXFLAGS) -xar -o"
else
  AR=ar
  ARFLAGS=cru
fi
AC_SUBST(AR,$AR)
AC_SUBST(ARFLAGS, $ARFLAGS)
])# RSSH_PROG_CXXAR

# RSSH_CHECK_SUNPROC_CC([ACTION-IF-YES], [ACTION-IF-NOT])
# ------------------------------------------------------
# check : are we using SUN workshop C++ compiler.
#  Corresponding cache value: rssh_cv_check_sunpro_cc is set to yes or no
#
#@author  Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998, 2000
#@version $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
#
#  RSSH_CHECK_SUNPRO_CC([ACTION-IF-YES],[ACTION-IF-NOT])
#
AC_DEFUN([RSSH_CHECK_SUNPRO_CC],
[AC_CACHE_CHECK([whether using Sun Worckshop C++ compiler],
                [rssh_cv_check_sunpro_cc],

[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([],
[#ifndef __SUNPRO_CC
# include "error: this is not Sun Workshop."
#endif
],
               rssh_cv_check_sunpro_cc=yes,
               rssh_cv_check_sunpro_cc=no)
AC_LANG_RESTORE])
if test ${rssh_cv_check_sunpro_cc} = yes
then
  $2
  :
else 
  $3
  :
fi
])# RSSH_CHECK_SUNPROC_CC

dnl autoconf macros: RSSH_PROG_CXXLD
dnl   (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
dnl   $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl --------------------------------------------------------------------
dnl RSSH_PROG_CXXLD
dnl check for program, which used for creating shared C++ libraries.
dnl set variables LD and LD_CREATE_FLAGS.
dnl
dnl
AC_DEFUN(RSSH_PROG_CXXLD,[
AC_REQUIRE([RSSH_CHECK_SUNPRO_CC])
if test x$rssh_cv_check_sunpro_cc = xyes
then 
  LD=CC
  LD_CREATE_FLAGS="\$(CXXFLAGS) -pta -G -o"
else
  if test x$GXX = xyes
  then
    LD=g++
    LD_CREATE_FLAGS="-shared -o"
  else
    LD=ld
    LD_CREATE_FLAGS="-G -o"
  fi
fi
AC_SUBST(LD,$LD)
AC_SUBST(LD_CREATE_FLAGS, $LD_CREATE_FLAGS)
])dnl
dnl

dnl   (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
dnl   $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl --------------------------------------------------------------------
dnl RSSH_PIC_FLAG()
dnl   set PIC_FLAG to compiler flag, for producing PIC files.
dnl siutable for building sharing libs.
dnl
AC_DEFUN(RSSH_PIC_FLAG,[
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([RSSH_CHECK_SUNPRO_CC])dnl
AC_MSG_CHECKING( "how we generate PIC code  " )


 if test "x$rssh_cv_check_sunpro_cc" = xyes
 then
   PIC_FLAG="-KPIC"
 else
   PIC_FLAG="-fpic"  #most compilers understood that.
 fi


AC_MSG_RESULT($PIC_FLAG)

AC_SUBST(PIC_FLAG)

])dnl
dnl
dnl

dnl RSSH_GCC_STDCPLUSPLUS 
dnl
dnl add -lstdc++ to libs, if we use g++
dnl
dnl Author: (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>,
dnl $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
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

dnl@synopsis RSSH_CHECK_ORB
dnl
dnl   check for CORBA ORB, set complilation flags 
dnl   and define appropriative variables and preprocessor symbols
dnl  (look at CORBA-autoconf.pdf for details)
dnl
dnl@author   (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
dnl@id   Id: RSSH_CHECK_ORB.m4,v 1.7 2000/08/03 18:34:37 rssh Exp $
dnl --------------------------------------------------------------------
AC_DEFUN([RSSH_CHECK_ORB],[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl

AC_ARG_WITH(orb, [orb: orb used (one of TAO  omniORB  ORBacus, VisiBroker)] ,\
            ORB=${with_orb} , ORB=unknown )

AC_CHECKING(ORB)

if test x$ORB = x
then
  ORB=unknown
fi

rssh_know_orb_name=no

if test  "$ORB" = "unknown"  -o  "$ORB" = "TAO" 
then
  RSSH_CHECK_TAO
  rssh_know_orb_name=yes
fi
if test  "$ORB" = "unknown"  -o  "$ORB" = "MICO" 
then
  RSSH_CHECK_MICO
  rssh_know_orb_name=yes
fi
if test  "$ORB" = "unknown"  -o  "$ORB" = "ORBacus" 
then
  RSSH_CHECK_ORBACUS
  rssh_know_orb_name=yes
fi
if test  "x$ORB" = "xunknown"  -o  "$ORB" = "omniORB"  -o "$ORB" = "omniBroker"
then
  RSSH_CHECK_OMNIORB
  rssh_know_orb_name=yes
fi
if test  "x$ORB" = "xunknown"  -o  "$ORB" = "VisiBroker"  
then
  RSSH_CHECK_VISIBROKER
  rssh_know_orb_name=yes
fi

if test "$rssh_know_orb_name" = "no"
then
  AC_MSG_ERROR(unknown ORB name)
fi
     

if test "$ORB" = "xunknown" ; then
  AC_MSG_ERROR(no orb found)
fi

IDL_DEPEND_ORB_FLAGS=""
svX=$X
X=""
X="$X --cln_h_suffix  $IDL_CLN_H_SUFFIX"
X="$X --cln_h1_suffix  $IDL_CLN_H1_SUFFIX"
X="$X --cln_cpp_suffix    $IDL_CLN_CPP_SUFFIX"
X="$X --cln_obj_suffix    $IDL_CLN_OBJ_SUFFIX"
X="$X --srv_h_suffix    $IDL_SRV_H_SUFFIX"
X="$X --srv_h1_suffix    $IDL_SRV_H1_SUFFIX"
X="$X --srv_cpp_suffix    $IDL_SRV_CPP_SUFFIX"
X="$X --srv_obj_suffix    $IDL_SRV_OBJ_SUFFIX"
X="$X --tie_h_suffix    $IDL_TIE_H_SUFFIX"
X="$X --tie_h1_suffix    $IDL_TIE_H1_SUFFIX"
X="$X --tie_cpp_suffix    $IDL_TIE_CPP_SUFFIX"

IDL_DEPEND_ORB_FLAGS="$X"
AC_SUBST(IDL_DEPEND_ORB_FLAGS)
X=$svX

AC_MSG_RESULT("Result for ORB: $ORB")

])dnl
dnl

#@synopsis RSSH_CHECK_TAO
#
# support macroses for TAO CORBA ORB
#        (see http://www.cs.wustl.edu/~schmidt/TAO.html)
#
#@author (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998, 2000
#
#@id Id: RSSH_CHECK_TAO.m4,v 1.10 2000/08/04 20:52:32 rssh Exp $
#
AC_DEFUN([RSSH_CHECK_TAO],[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl


AC_ARG_WITH(tao, [tao: prefix to TAO installation (default: \$TAO_ROOT)] ,\
            TAO_PREFIX=${with_tao} , TAO_PREFIX=/usr/local )

AC_CHECKING(for TAO)

if test "x$TAO_PREFIX" = "xno"
then
 tao=no
else

svCXXCPPFLAGS=$CXXCPPFLAGS
svCXXFLAGS=$CXXFLAGS
svCPPFLAGS=$CPPFLAGS
svLIBS=$LIBS
svLDFLAGS=$LDFLAGS
svRSSH_ROLLBACK=$rssh_rollback
rssh_rollback="true"

if  test "x$ACE_ROOT" = "x"
then
  AC_MSG_RESULT(ACE_ROOT not set)
  tao=no
else

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

ORB_INCLUDES="-I$ACE_ROOT -I$ACE_ROOT/TAO -I$ACE_ROOT/TAO/orbsvcs"
CXXCPPFLAGS="$CXXCPPFLAGS $ORB_INCLUDES"
CPPFLAGS="$CPPFLAGS $ORB_INCLUDES"

AC_CHECK_HEADER( tao/corba.h, tao=yes , tao=no, )

if test "x$tao" = "xyes" 
then
  LDFLAGS="$LDFLAGS -L$ACE_ROOT/ace"
#  AC_CHECK_LIB(ACE,main, LIBS="-lACE $LIBS",ace_lib=no,)
#  AC_HAVE_LIBRARY(ACE, LIBS="-lACE $LIBS",ace_lib=no,)
  YAD_CHECK_INCLUDE_LIB([#include <tao/corba.h>],TAO,CORBA::ORB_var orb, LIBS="-lTAO -lACE $LIBS",tao_libs=no,-lACE)
  AC_CHECK_LIB(socket,socket, LIBS="-lsocket $LIBS",,)
  AC_CHECK_LIB(nsl,gethostbyname, LIBS="-lnsl $LIBS",,)
  AC_CHECK_HEADER( tao/PortableServer/PortableServer.h, tao_poahead=yes, tao_poahead=no, )
  if test "x$tao_poahead" = "xyes"
  then
    AC_DEFINE(TAO_HAVE_PORTABLE_SERVER_H,1,[Defined if we have a PortableServer.h])
    YAD_CHECK_INCLUDE_LIB([#include <tao/corba.h>
#include <tao/PortableServer/PortableServer.h>],TAO_PortableServer,PortableServer::ObjectId_var oid = PortableServer::string_to_ObjectId("myObj"), LIBS="-lTAO_PortableServer $LIBS")
  fi
  YAD_CHECK_INCLUDE_LIB([#include <orbsvcs/Time_Utilities.h>],TAO_Svc_Utils,ORBSVCS_Time::zero(), LIBS="-lTAO_Svc_Utils $LIBS")
  AC_CHECK_HEADER( tao/IORTable/IORTable.h, tao_iortable=yes, tao_iortable=no, )
  if test "x$tao_iortable" = "xyes"
  then
    AC_DEFINE(TAO_HAVE_IORTABLE_ADAPTER,1,[Defined ...])
    YAD_CHECK_INCLUDE_LIB([#include <tao/IORTable/IORTable.h>],TAO_IORTable,TAO_IORTable_Initializer::init(), LIBS="-lTAO_IORTable $LIBS")
  fi
  LIBS="$LDFLAGS $LIBS"
fi

#if test "x$ace_lib" = "xno"
#then
# tao=no
#fi

if test "x$tao_libs" = "xno"
then
 tao=no
fi

fi

if test "x$tao" = "xno"
then
  CXXCPPFLAGS=$svCXXCPPFLAGS
  CPPFLAGS=$svCPPFLAGS
  LIBS=$svLIBS
  LDFLAGS=$svLDFLAGS
  eval "$rssh_rollback"
  rssh_rollback=$svRSSH_ROLLBACK
else
  ORB_PREFIX=$ACE_ROOT
  AC_SUBST(ORB_PREFIX)

  ORB=TAO
  AC_SUBST(ORB)

  IDL=$ACE_ROOT/TAO/TAO_IDL/tao_idl
  AC_SUBST(IDL)

  IDLFLAGS="$IDLFLAGS -I$ACE_ROOT/TAO/orbsvcs/orbsvcs"
  AC_SUBST(IDLFLAGS)

  ORB_INCLUDE_PREFIX=tao
  AC_SUBST(ORB_INCLUDE_PREFIX)


  IDL_CLN_H=C.h
  IDL_CLN_H_SUFFIX=C.h
  IDL_CLN_H1_SUFFIX=C.i
  AC_SUBST(IDL_CLN_H,$IDL_CLN_H)
  AC_SUBST(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)
  AC_SUBST(IDL_CLN_H1_SUFFIX,$IDL_CLN_H1_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)

  IDL_CLN_CPP=C.cpp
  IDL_CLN_CPP_SUFFIX=C.cpp
  AC_SUBST(IDL_CLN_CPP,$IDL_CLN_CPP)
  AC_SUBST(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP_SUFFIX)

  IDL_CLN_O=C.o 
  IDL_CLN_OBJ_SUFFIX=C.o 
  AC_SUBST(IDL_CLN_O,$IDL_CLN_O)
  AC_SUBST(IDL_CLN_OBJ_SUFFIX,$IDL_CLN_OBJ_SUFFIX)

  IDL_SRV_H=S.h 
  IDL_SRV_H_SUFFIX=S.h 
  IDL_SRV_H1_SUFFIX=S.i 
  AC_SUBST(IDL_SRV_H,$IDL_SRV_H)
  AC_SUBST(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)
  AC_SUBST(IDL_SRV_H1_SUFFIX,$IDL_SRV_H1_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)

  IDL_SRV_CPP=S.cpp
  IDL_SRV_CPP_SUFFIX=S.cpp
  AC_SUBST(IDL_SRV_CPP)
  AC_SUBST(IDL_SRV_CPP_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_SRV_CPP_SUFFIX,$IDL_SRV_CPP_SUFFIX,[Define the suffix for c++ server implementation files])

  IDL_SRV_O=S.o
  IDL_SRV_OBJ_SUFFIX=S.o
  AC_SUBST(IDL_SRV_O,$IDL_SRV_O)
  AC_SUBST(IDL_SRV_OBJ_SUFFIX,$IDL_SRV_OBJ_SUFFIX)

  IDL_TIE_H_SUFFIX=S_T.h
  IDL_TIE_H1_SUFFIX=S_T.i
  IDL_TIE_CPP_SUFFIX=S_T.cpp
  AC_SUBST(IDL_TIE_H_SUFFIX,$IDL_TIE_H_SUFFIX)
  AC_SUBST(IDL_TIE_H1_SUFFIX,$IDL_TIE_H1_SUFFIX)
  AC_SUBST(IDL_TIE_CPP_SUFFIX,$IDL_TIE_CPP_SUFFIX)

  CORBA_H='tao/corba.h'
  AC_DEFINE_UNQUOTED(CORBA_H,<$CORBA_H>)

  COSNAMING_H='orbsvcs/CosNamingC.h'
  AC_DEFINE_UNQUOTED(COSNAMING_H,<$COSNAMING_H>)

  YAD_CHECK_INCLUDE_LIB([#include <$CORBA_H>
#include <$COSNAMING_H>],orbsvcs,CORBA::Object_var obj; CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(obj),have_orbsvcs=yes,have_orbsvcs=no)
  YAD_CHECK_INCLUDE_LIB([#include <$CORBA_H>
#include <$COSNAMING_H>],TAO_CosNaming,CORBA::Object_var obj; CosNaming::NamingContext_ptr nc = CosNaming::NamingContext::_narrow(obj),have_taoCosNaming=yes,have_taoCosNaming=no)
  if test "$have_orbsvcs" = yes 
  then
    ORB_COSNAMING_LIB="-lorbsvcs"
    TAO_VERSION=11
  else
   if test "$have_taoCosNaming" = yes 
   then
    ORB_COSNAMING_LIB="-lTAO_CosNaming"
    TAO_VERSION=12
   else
    AC_MSG_ERROR("found TAO but can not find TAO CosNaming libraries")
   fi
  fi
   
  AC_SUBST(ORB_COSNAMING_LIB)

  HAVE_ORB_IDL=1
  AC_SUBST(HAVE_ORB_IDL)

  CORBA_HAVE_POA=1
  AC_DEFINE_UNQUOTED(CORBA_HAVE_POA,$CORBA_HAVE_POA)

  AC_CACHE_CHECK("whether TAO support namespaces",
  rssh_cv_tao_corba_namespaces,
  AC_TRY_COMPILE(#include <$CORBA_H>
,
[
#ifndef ACE_HAS_USING_KEYWORD
#error "we have no namespaces"
we have no namespaces -- $$$$
#else
return 0;
#endif
], rssh_cv_tao_corba_namespaces=yes, rssh_cv_tao_corba_namespaces=0)
  )

  if test "$rssh_cv_tao_corba_namespaces" = "yes" 
  then
    AC_DEFINE(CORBA_MODULE_NAMESPACE_MAPPING)
  else
    AC_DEFINE(CORBA_MODULE_CLASS_MAPPING)
  fi
  
  AC_DEFINE(RSSH_TAO,1,[Defined if TAO is present])
  AC_DEFINE(CORBA_SYSTEM_EXCEPTION_IS_STREAMBLE)
  AC_DEFINE(CORBA_ORB_HAVE_DESTROY)

fi
fi

AC_LANG_RESTORE

AC_MSG_RESULT(for TAO: $tao)

])dnl
dnl

dnl@synopsys YAD_CHECK_INCLUDE_LIB(INCLUDE, LIBRARY, CODE
dnl              [, ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND
dnl              [, OTHER-LIBRARIES]]])
dnl 
dnl same as the AC_CHECK_LIB except of the following:
dnl      - You sholud specify include part of test.
dnl      - You can test any code for linking, not just function calls.
dnl
dnl@author Alexandr Yanovets <yad@gradsoft.kiev.ua>
dnl@id $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl
AC_DEFUN(YAD_CHECK_INCLUDE_LIB,
[AC_MSG_CHECKING([for $3 in -l$2])
dnl Use a cache variable name containing both the library and function name,
dnl because the test really is for library $2 defining function $3, not
dnl just for library $2.  Separate tests with the same $2 and different $3s
dnl may have different results.
ac_lib_var=`echo $2['_']include | sed 'y%./+-%__p_%'`
AC_CACHE_VAL(ac_cv_lib_$ac_lib_var,
[yad_check_lib_save_LIBS="$LIBS"
LIBS="-l$2 $6 $LIBS"
AC_TRY_LINK(dnl
            [$1],
	    [$3],
	    eval "ac_cv_lib_$ac_lib_var=yes",
	    eval "ac_cv_lib_$ac_lib_var=no")
LIBS="$yad_check_lib_save_LIBS"
])dnl
if eval "test \"`echo '$ac_cv_lib_'$ac_lib_var`\" = yes"; then
  AC_MSG_RESULT(yes)
  ifelse([$4], ,
[changequote(, )dnl
  ac_tr_lib=HAVE_LIB`echo $2 | sed -e 's/[^a-zA-Z0-9_]/_/g' \
    -e 'y/abcdefghijklmnopqrstuvwxyz/ABCDEFGHIJKLMNOPQRSTUVWXYZ/'`
changequote([, ])dnl
  AC_DEFINE_UNQUOTED($ac_tr_lib)
  LIBS="-l$2 $LIBS"
], [$4])
else
  AC_MSG_RESULT(no)
ifelse([$5], , , [$5
])dnl
fi
])


dnl autoconf macroses for detecting mico (http://www.ooc.com)
dnl (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
dnl $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
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

dnl autoconf macroses for detecting ORBacus (http://www.ooc.com)
dnl (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
dnl $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl
AC_DEFUN(RSSH_CHECK_ORBACUS,[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl

AC_CHECKING(for ORBACUS)

orbacus=no

AC_ARG_WITH(ob, [ob: prefix to OB installation (default: /usr/local) ],\
            OB_PREFIX=${with_ob} , OB_PREFIX=/usr/local )

AC_CHECKING(for ORBacus)

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

if test ! $OB_PREFIX = no
then


svCPPFLAGS=$CPPFLAGS
svCXXFLAGS=$CXXFLAGS
svCXXCPPFLAGS=$CXXCPPFLAGS
svLIBS=$LIBS
svRSSH_ROLLBACK=$rssh_rollback
rssh_rollback=true

RSSH_CHECK_JTC

CXXCPPFLAGS="$CXXCPPFLAGS  -I$OB_PREFIX/include"
CPPFLAGS="$CPPFLAGS  -I$OB_PREFIX/include"

AC_CHECK_HEADER( OB/CORBA.h, orbacus=yes , orbacus=no )
else
 orbacus=no
fi

if test "x$orbacus" = xyes
then

AC_CHECK_LIB(socket,socket, LIBS="-lsocket $LIBS",,)
AC_CHECK_LIB(nsl,gethostbyname, LIBS="-lnsl $LIBS",,)

LIBS="-L$OB_PREFIX/lib -lOB $LIBS"
         
AC_SUBST(OB_PREFIX)

ORB_PREFIX=$OB_PREFIX
AC_SUBST(ORB_PREFIX)

ORB=ORBacus
AC_SUBST(ORB)


IDL=$OB_PREFIX/bin/idl
AC_SUBST(IDL,$IDL)
IDLCXX=$OB_PREFIX/bin/idl
AC_SUBST(IDLCXX,$IDLCXX)

IDLFLAGS="$IDLFLAGS -I$OB_PREFIX/idl -I$OB_PREFIX/idl/OB"
AC_SUBST(IDLFLAGS)

ORB_INCLUDE_PREFIX=OB
AC_SUBST(ORB_INCLUDE_PREFIX)


IDL_CLN_H=.h
IDL_CLN_H_SUFFIX=.h
IDL_CLN_H1_SUFFIX=no
AC_SUBST(IDL_CLN_H,$IDL_CLN_H)
AC_SUBST(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)
AC_SUBST(IDL_CLN_H1_SUFFIX,$IDL_CLN_H1_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_CLN_H,$IDL_CLN_H)
AC_DEFINE_UNQUOTED(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)

IDL_CLN_CPP=.cpp
IDL_CLN_CPP_SUFFIX=.cpp
AC_SUBST(IDL_CLN_CPP,$IDL_CLN_CPP)
AC_SUBST(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)
AC_DEFINE_UNQUOTED(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)

IDL_CLN_O=.o 
IDL_CLN_OBJ_SUFFIX=.o 
AC_SUBST(IDL_CLN_O,$IDL_CLN_O)
AC_SUBST(IDL_CLN_OBJ_SUFFIX,$IDL_CLN_OBJ_SUFFIX)

IDL_SRV_H=_skel.h 
IDL_SRV_H_SUFFIX=_skel.h 
IDL_SRV_H1_SUFFIX=no 
AC_SUBST(IDL_SRV_H,$IDL_SRV_H)
AC_SUBST(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)
AC_SUBST(IDL_SRV_H1_SUFFIX,$IDL_SRV_H1_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H)

IDL_SRV_CPP=_skel.cpp
IDL_SRV_CPP_SUFFIX=_skel.cpp
AC_SUBST(IDL_SRV_CPP,$IDL_SRV_CPP)
AC_SUBST(IDL_SRV_CPP_SUFFIX,$IDL_SRV_CPP)

IDL_SRV_O=_skel.o
IDL_SRV_OBJ_SUFFIX=_skel.o
AC_SUBST(IDL_SRV_O,$IDL_SRV_O)
AC_SUBST(IDL_SRV_OBJ_SUFFIX,$IDL_SRV_O)

IDL_TIE_H_SUFFIX=_tie_skel.h
IDL_TIE_H1_SUFFIX=no
IDL_TIE_CPP_SUFFIX=no
AC_SUBST(IDL_TIE_H_SUFFIX,$IDL_TIE_H_SUFFIX)
AC_SUBST(IDL_TIE_H1_SUFFIX,$IDL_TIE_H1_SUFFIX)
AC_SUBST(IDL_TIE_CPP_SUFFIX,$IDL_TIE_CPP_SUFFIX)


CORBA_H='OB/CORBA.h'
AC_DEFINE_UNQUOTED(CORBA_H,<$CORBA_H>)

COSNAMING_H='OB/CosNaming.h'
AC_DEFINE_UNQUOTED(COSNAMING_H,<$COSNAMING_H>)
ORB_COSNAMING_LIB="-lCosNaming"
AC_SUBST(ORB_COSNAMING_LIB)

AC_CACHE_CHECK("if OB_INTEGER_VERSION defined",
rssh_cv_have_ob_integer_version,
AC_TRY_COMPILE(#include <$CORBA_H>
,
[
#ifndef OB_INTEGER_VERSION
#error "OB_INTEGER_VERSION_NOT_DEFINED"
ob integer version not defined and C++ compiler think, that errors are warning
#else
return 0;
#endif
], rssh_cv_have_ob_integer_version=1, rssh_cv_have_ob_integer_version=0)
)


if test "x$rssh_cv_have_ob_integer_version" = "x1" 
then
AC_CACHE_CHECK("if this is 4.x branch ",
rssh_cv_ob_4,
AC_TRY_COMPILE(#include <$CORBA_H>
,
[
#if (OB_INTEGER_VERSION >= 3999951L )
return 0;
#else
#error "qqq"
ob integer version < ,,, but C++ compiler think, that errors are warning
#endif
],rssh_cv_ob_4=yes,rssh_cv_ob_4=no)
)
fi


if test "x$rssh_cv_ob_4" = "xyes" 
then
AC_DEFINE(CORBA_MODULE_NAMESPACE_MAPPING)
AC_DEFINE(CORBA_HAVE_POA)
HAVE_ORB_IDL=1
AC_DEFINE(CORBA_SYSTEM_EXCEPTION_IS_STREAMBLE)
AC_DEFINE(CORBA_ORB_HAVE_DESTROY,1,[Defined if the ORB has a destroy operation])
else
HAVE_ORB_IDL=0
AC_DEFINE(CORBA_MODULE_C_MAPPING,1,[Defined if the ORB use C-style mapping])
CORBA_SKELETON_SUFFIX=_skel
AC_DEFINE_UNQUOTED(CORBA_SKELETON_SUFFIX,$CORBA_SKELETON_SUFFIX,[Define the suffix part for skeleton files generated by the idl compiler])
fi
AC_SUBST(HAVE_ORB_IDL)
  
AC_DEFINE(ORBACUS,1,[Defined if ORBacus is present])

else

CPPFLAGS=$svCPPFLAGS
CXXCPPFLAGS=$svCXXCPPFLAGS
CXXFLAGS=$svCXXFLAGS
LIBS=$svLIBS
eval "$rssh_rollback"
rssh_rollback="$svRSSH_ROLLBACK"

fi

AC_LANG_RESTORE

AC_MSG_RESULT(ORBacus check result: $orbacus)

])dnl
dnl

dnl  set of additional configure scripts.
dnl   (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998, 2000
dnl   $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl --------------------------------------------------------------------
dnl
dnl
AC_DEFUN(RSSH_CHECK_JTC,[

AC_ARG_WITH(jtc, [jtc: prefix to JTC installation (default: /usr/local)] ,
            JTC_PREFIX=${with_jtc} , JTC_PREFIX=/usr/local )

AC_CHECKING("for JTC")

  svLIBS=$LIBS
  svCXXFLAGS="$CXXFLAGS"
  svCPPFLAGS="$CPPFLAGS"
  svCXXCPPFLAGS="$CXXCPPFLAGS"
  svRSSH_ROLLBACK="$rssh_rollback"
  rssh_rollback="true"

  RSSH_ENABLE_PTHREADS

  AC_LANG_SAVE
  AC_LANG_CPLUSPLUS

  CXXCPPFLAGS="$CXXCPPFLAGS  -I$JTC_PREFIX/include"
  CPPFLAGS="$CPPFLAGS  -I$JTC_PREFIX/include"
  CXXFLAGS="$CXXFLAGS $CXXFLAGS_THREADS"

  AC_CHECK_HEADER(JTC/JTC.h,have_jtc_header=yes,have_jtc_header=no)

  if test $have_jtc_header = yes
  then
    LIBS="-L${JTC_PREFIX}/lib -lJTC $LIBS" 
    
    AC_CACHE_CHECK("whether we can link with JTC",
                 [rssh_cv_check_jtc],
[
      AC_LANG_SAVE
      AC_LANG_CPLUSPLUS
      AC_TRY_LINK(
#include <JTC/JTC.h>
,
int x=0;
JTCInitialize bootJTC(x,NULL),
                 [rssh_cv_check_jtc=yes],
                 [rssh_cv_check_jtc=no]
     )
     AC_LANG_RESTORE
])
  else
    rssh_cv_check_jtc=no
  fi

  AC_LANG_RESTORE

AC_MSG_RESULT("Result for JTC: $rssh_cv_check_jtc")

if test $rssh_cv_check_jtc = yes
then
  AC_DEFINE(HAVE_JTC,1,[Define if JTC is present.])
else
  LIBS=$svLIBS
  CXXFLAGS="$svCXXFLAGS"
  CXXCPPFLAGS="$svCXXCPPFLAGS"
  CPPFLAGS="$svCPPFLAGS"
  eval "$rssh_rollback" 
  rssh_rollback="$svRSSH_ROLLBACK"
fi

])dnl
dnl

dnl@synopsis RSSH_ENABLE_PTHREADS
dnl
dnl modify CFLAGS, CXXFLAGS and LIBS for compiling pthread-based programs.
dnl
dnl@author  (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998, 2000
dnl@id  $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl
dnl
AC_DEFUN([RSSH_ENABLE_PTHREADS],[
AC_REQUIRE([RSSH_CHECK_PTHREADS])

if test -z "$rssh_enable_pthreads_done"
then
 CFLAGS="$CFLAGS $CFLAGS_PTHREADS"
 CXXFLAGS="$CXXFLAGS $CXXFLAGS_PTHREADS"
 LIBS="$LIBS $LIBS_PTHREADS"
fi
rssh_enable_pthreads_done=yes

rssh_rollback="$rssh_rollback; rssh_enable_pthreads_done=" 
])dnl
dnl

#@synonpsis RSSH_CHECK_PTHREADS
#  check for pthreads system interfaces.
#  set CFLAGS_PTHREADS,  CXXFLAGS_PTHREADS and LIBS_PTHREADS to
#  flags to compiler option, which denote multithread program compilation 
# (if one exists),
#  and multithread library, if one required.
#
#@author   (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998
#@id $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
#
AC_DEFUN(RSSH_CHECK_PTHREADS,[
AC_REQUIRE([AC_CANONICAL_SYSTEM])dnl
AC_REQUIRE([RSSH_CHECK_SUNPRO_C])dnl
AC_REQUIRE([RSSH_CHECK_SUNPRO_CC])dnl
AC_CHECK_HEADER(pthread.h)
AC_MSG_CHECKING(parameters for using pthreads: )
if test x$rssh_cv_check_sunpro_c = xyes
then
  CFLAGS_PTHREADS="-mt"
fi
if test x$rssh_cv_check_sunpro_cc = xyes
then
  CXXFLAGS_PTHREADS="-mt"
fi
case $build_os in
  freebsd*)
    CFLAGS_PTHREADS="-pthread"
    CXXFLAGS_PTHREADS="-pthread"
    freebsd_pthreads=yes
    ;;
  *)
    freebsd_pthreads=no
    ;;
esac
if test x$freebsd_pthreads = xno
then
  AC_CHECK_LIB(pthread,pthread_create, LIBS_PTHREADS="-lpthread")
fi
_libs=$LIBS
LIBS="$LIBS -lposix4"
AC_MSG_CHECKING([for nanosleep in -lposix4])
AC_TRY_LINK([#include <time.h>],[nanosleep(0,0);],[
LIBS_PTHREADS="$LIBS_PTHREADS -lposix4"
result=yes], result=no)
AC_MSG_RESULT($result)
LIBS=$_libs

dnl AC_CHECK_LIB(posix4,nanosleep, LIBS_PTHREADS="$LIBS_PTHREADS -lposix4")
AC_MSG_RESULT(["flags $CFLAGS_PTHREADS\;libs: $LIBS_PTHREADS"])
])dnl

# RSSH_CHECK_SUNPROC_C([ACTION-IF-YES], [ACTION-IF-NOT])
# ------------------------------------------------------
# check : are we using SUN workshop C compiler.
#  Corresponding cache value: rssh_cv_check_sunpro_c is set to yes or no
#
#@author  Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1998, 2000
#@version $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
#
#  RSSH_CHECK_SUNPRO_C([ACTION-IF-YES],[ACTION-IF-NOT])
#
AC_DEFUN([RSSH_CHECK_SUNPRO_C],
[AC_CACHE_CHECK([whether using Sun Worckshop C compiler],
                [rssh_cv_check_sunpro_c],

[AC_LANG_SAVE
 AC_LANG_C
 AC_TRY_COMPILE([],
[#ifndef __SUNPRO_C
# include "error: this is not Sun Workshop."
#endif
],
               rssh_cv_check_sunpro_c=yes,
                rssh_cv_check_sunpro_c=no)
AC_LANG_RESTORE])
if test ${rssh_cv_check_sunpro_c} = yes
then
  $2
  :
else 
  $3
  :
fi
])# RSSH_CHECK_SUNPROC_C

dnl@synposis RSSH_CHECK_CORBA_ORB 
dnl
dnl set CORBA support for omniORB v3-pr2 or highter
dnl    ( http://www.uk.research.att.com/omniORB/omniORB.html)
dnl
dnl@author (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 1999, 2000
dnl@id $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl
AC_DEFUN([RSSH_CHECK_OMNIORB],[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl


AC_ARG_WITH(omni, [omni: prefix to omniORB installation (default: \$OMNI_ROOT)] ,\
            OMNI_PREFIX=${with_omni} , OMNI_PREFIX=/usr/local )

AC_CHECKING(for omniORB)

if test "x$OMNI_ROOT" = "x"
then
 if test "x$OMNI_PREFIX" = "x"
 then
   OMNI_ROOT="/usr/local"
 else
   OMNI_ROOT="$OMNI_PREFIX"
 fi
fi

if  test "x$OMNI_PREFIX" = "xno"
then
dnl OMNI NOT SET 
  AC_MSG_RESULT(omniORB is disabled)
  omni=no
else

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

svCXXCPPFLAGS=$CXXCPPFLAGS
svCXXFLAGS=$CXXFLAGS
svCPPFLAGS=$CPPFLAGS
svLIBS=$LIBS
svLDFLAGS=$LDFLAGS
svRSSH_ROLLBACK=$rssh_rollback
rssh_rollback="true"

ORB_INCLUDES="-I$OMNI_ROOT/include"
CXXCPPFLAGS="$CXXCPPFLAGS -I$OMNI_ROOT/include "
CPPFLAGS="$CPPFLAGS -I$OMNI_ROOT/include "

RSSH_ENABLE_PTHREADS

CXXCPPFLAGS="$CXXCPPFLAGS"

case $build_cpu in
 sparc*)
    IDLCXXFLAGS="$IDLCXXFLAGS -D__sparc__"
    ;;
 "i686"|"i586"|"i486"|"i386")
    IDLCXXFLAGS="$IDLCXXFLAGS -D__x86__"
    ;;
esac
case $build_os in
 solaris*)
    IDLCXXFLAGS="$IDLCXXFLAGS -D__sunos__"
    __OSVERSION__=5
    IDLCXXFLAGS="$IDLCXXFLAGS -D__OSVERSION__=5"
    ;;
 freebsd*)
    IDLCXXFLAGS="$IDLCXXFLAGS -D__freebsd__"
    ;;
esac

AC_SUBST(IDLCXXFLAGS)

CXXCPPFLAGS="$CXXCPPFLAGS $IDLCXXFLAGS"

AC_CHECK_HEADER( omniORB3/CORBA.h, omni=yes , omni=no, )

if test "x$omni" = "xyes" 
then
  ORB_LIBDIR="$OMNI_ROOT/lib"
  if test ! -r "$ORB_LIBDIR/libomniORB3.so"
  then
    for i in $OMNI_ROOT/lib/*/lib*.so
    do
      ORB_LIBDIR=`dirname $i` 
      break;
    done
  fi

  LIBS="$LIBS -lomnithread"
  svLIBS=$LIBS
  LIBS="-L$ORB_LIBDIR $LIBS"

  AC_CACHE_CHECK("are we have omnithreads",
    rssh_cv_check_omnithreads,
    rssh_enable_pthreads_done=""
    RSSH_ENABLE_PTHREADS
    AC_LANG_SAVE
    AC_LANG_CPLUSPLUS
    AC_TRY_LINK(
#include <omnithread.h>
,omni_mutex my_mutex,
                 rssh_cv_check_omnithreads=yes,rssh_cv_check_omnithreads=no)
    AC_LANG_RESTORE
  )
  if  test ! $rssh_cv_check_omnithreads = yes
  then
    AC_MSG_RESULT("omnithreads not found")
    omni_lib=no
  fi
  AC_CHECK_LIB(socket,socket, LIBS="-lsocket $LIBS",,)
  AC_CHECK_LIB(nsl,gethostbyname, LIBS="-lnsl $LIBS",,)

  ORB_LDFLAGS="-L$ORB_LIBDIR"
  LIBS="$ORB_LDFLAGS -lomniORB3 -ltcpwrapGK -lomniDynamic3 $svLIBS"
  AC_CACHE_CHECK("whether we can link with omniORB3",
    rssh_cv_check_omniORBlib,
    AC_TRY_LINK(
#include <omniORB3/CORBA.h>
,CORBA::ORB_var orb,
    rssh_cv_check_omniORBlib=yes,rssh_cv_check_omniORBlib=no
    )
  )

  if  test ! $rssh_cv_check_omniORBlib = yes
  then
    AC_MSG_RESULT("omniORB libs not found")
    omni_lib=no
  fi


  ORB_LIBS="$ORB_LDFLAGS -lomniORB3 -lomnithread"
fi

if test "x$omni_lib" = "xno"
then
 AC_MSG_RESULT(omniORB library linking failed)
 omni="no"
fi

fi

if test "x$omni" = "x" -o "x$omni" = "xno"
then
  CXXCPPFLAGS=$svCXXCPPFLAGS
  CPPFLAGS=$svCPPFLAGS
  LIBS=$svLIBS
  LDFLAGS=$svLDFLAGS
  ORB=unknown
  omni=no
  eval "$rssh_rollback"
  rssh_rollback=$svRSSH_ROLLBACK 
else
  AC_SUBST(CORBA_INCLUDES)

  ORB_PREFIX=$OMNI_ROOT
  AC_SUBST(ORB_PREFIX)

  ORB=omniORB
  AC_SUBST(ORB)

  IDL=omniidl
  if test -x $OMNI_ROOT/bin/omniidl
  then
    IDL=$OMNI_ROOT/bin/omniidl
  else
    for i in $OMNI_ROOT/bin/*/omniidl
    do
      if test "$i" != $OMNI_ROOT'/bin/*/omniidl'
      then
        IDL=$i
        break
      fi
    done 
  fi
  AC_SUBST(IDL)
  IDLCXX=$IDL
  AC_SUBST(IDLCXX)

  IDLFLAGS="$IDLFLAGS -bcxx -I$OMNI_ROOT/idl"
  AC_SUBST(IDLFLAGS)

  ORB_INCLUDE_PREFIX=
  AC_SUBST(ORB_INCLUDE_PREFIX)

  IDL_H_SUFFIX=.hh
  AC_SUBST(IDL_H_SUFFIX)
  IDL_H1_SUFFIX=no
  AC_SUBST(IDL_H1_SUFFIX)

  IDL_CLN_H=.hh
  IDL_CLN_H_SUFFIX=.hh
  IDL_CLN_H1_SUFFIX=no

  AC_SUBST(IDL_CLN_H,$IDL_CLN_H)
  AC_SUBST(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)
  AC_SUBST(IDL_CLN_H1_SUFFIX,$IDL_CLN_H1_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)

  IDL_CLN_CPP=SK.cc
  IDL_CLN_CPP_SUFFIX=SK.cc
  AC_SUBST(IDL_CLN_CPP,$IDL_CLN_CPP)
  AC_SUBST(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)

  IDL_CLN_O=SK.o 
  IDL_CLN_OBJ_SUFFIX=SK.o 
  AC_SUBST(IDL_CLN_O,$IDL_CLN_O)
  AC_SUBST(IDL_CLN_OBJ_SUFFIX,$IDL_CLN_OBJ_SUFFIX)

  IDL_SRV_H=.hh
  IDL_SRV_H_SUFFIX=.hh
  IDL_SRV_H1_SUFFIX=no
  AC_SUBST(IDL_SRV_H,$IDL_SRV_H)
  AC_SUBST(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)
  AC_SUBST(IDL_SRV_H1_SUFFIX,$IDL_SRV_H1_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)

  IDL_SRV_CPP=SK.cc
  IDL_SRV_CPP_SUFFIX=SK.cc
  AC_SUBST(IDL_SRV_CPP,$IDL_SRV_CPP)
  AC_SUBST(IDL_SRV_CPP_SUFFIX,$IDL_SRV_CPP_SUFFIX)
  AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)

  IDL_SRV_O=SK.o
  IDL_SRV_OBJ_SUFFIX=SK.o
  AC_SUBST(IDL_SRV_O,$IDL_SRV_O)
  AC_SUBST(IDL_SRV_OBJ_SUFFIX,$IDL_SRV_OBJ_SUFFIX)

  IDL_TIE_H_SUFFIX=no
  IDL_TIE_H1_SUFFIX=no
  IDL_TIE_CPP_SUFFIX=no
  AC_SUBST(IDL_TIE_H_SUFFIX,$IDL_TIE_H_SUFFIX)
  AC_SUBST(IDL_TIE_H1_SUFFIX,$IDL_TIE_H1_SUFFIX)
  AC_SUBST(IDL_TIE_CPP_SUFFIX,$IDL_TIE_CPP_SUFFIX)

  CORBA_H='omniORB3/CORBA.h'
  AC_DEFINE_UNQUOTED(CORBA_H,<$CORBA_H>)

  COSNAMING_H='omniORB3/Naming.hh'
  AC_DEFINE_UNQUOTED(COSNAMING_H,<$COSNAMING_H>)

  ORB_COSNAMING_LIB= 
  AC_SUBST(ORB_COSNAMING_LIB)

dnl i. e. it's build into ORB lib

  HAVE_ORB_IDL=1
  AC_SUBST(HAVE_ORB_IDL)

  AC_CACHE_CHECK("whether CORBA modules mapped to namespaces",
    rssh_cv_corba_namespaces,
  AC_TRY_COMPILE(#include <$CORBA_H>
,
[
#ifndef HAS_Cplusplus_Namespace
#error "we have no namespaces"
we have no namespaces -- $$$$
#else
return 0;
#endif
], rssh_cv_corba_namespaces=yes, rssh_cv_corba_namespaces=no)
  )

  if test "$rssh_cv_corba_namespaces" = "yes" 
  then
    AC_DEFINE(CORBA_MODULE_NAMESPACE_MAPPING)
  else
    AC_DEFINE(CORBA_MODULE_CLASS_MAPPING)
  fi
  
  AC_DEFINE(OMNIORB,1,[Defined if omniORB is present])

  CORBA_HAVE_POA=1
  AC_DEFINE(CORBA_HAVE_POA)

  CORBA_ORB_INIT_HAVE_3_ARGS=1
  AC_DEFINE(CORBA_ORB_INIT_HAVE_3_ARGS,1,[Defined if the init operation for the ORB have 3 arguments])
  CORBA_ORB_INIT_THIRD_ARG='"omniORB3"'
  AC_DEFINE(CORBA_ORB_INIT_THIRD_ARG, "omniORB3",[Define the third argument to ORB_init()])
  AC_DEFINE(CORBA_ORB_HAVE_DESTROY)


fi

AC_LANG_RESTORE

AC_MSG_RESULT(for omniORB: $omni)

])dnl
dnl

dnl autoconf macroses for detecting Visibroker (http://www.borland.com)
dnl (C) Ruslan Shevchenko <Ruslan@Shevchenko.Kiev.UA>, 2000
dnl $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl
AC_DEFUN(RSSH_CHECK_VISIBROKER,[
AC_REQUIRE([AC_PROG_CC])dnl
AC_REQUIRE([AC_PROG_CXX])dnl
AC_REQUIRE([AC_PROG_CPP])dnl
AC_REQUIRE([AC_PROG_CXXCPP])dnl
AC_REQUIRE([AC_CXX_NAMESPACES])dnl

AC_CHECKING(for VISIBROKER)

visibroker=no

AC_ARG_WITH(visi, [visi: prefix to Visibroker installation (default: /usr/inprise/vbroker) ],\
            VISI_PREFIX=${with_visi} , VISI_PREFIX=/usr/inprise/vbroker )

AC_LANG_SAVE
AC_LANG_CPLUSPLUS

if test ! $VISI_PREFIX = no
then

svCPPFLAGS=$CPPFLAGS
svCXXFLAGS=$CXXFLAGS
svCXXCPPFLAGS=$CXXCPPFLAGS
svLIBS=$LIBS
svRSSH_ROLLBACK=$rssh_rollback
rssh_rollback=true

CXXCPPFLAGS="$CXXCPPFLAGS  -I$VISI_PREFIX/include"
CPPFLAGS="$CPPFLAGS  -I$VISI_PREFIX/include"

AC_CHECK_HEADER( corba.h, visibroker=yes , visibroker=no )
else
 visibroker=no
fi

AC_CHECK_PROG(have_vbj, vbj, yes, no)


if test "x$visibroker" = xyes -a  "x$have_vbj" = "xyes"
then

RSSH_ENABLE_PTHREADS

AC_CHECK_LIB(socket,socket, LIBS="-lsocket $LIBS",,)
AC_CHECK_LIB(nsl,gethostbyname, LIBS="-lnsl $LIBS",,)

ORB_LIBS="-lorb_r -lvport_r"
ORB_LIBDIR="-L$VISI_PREFIX/lib"
LIBS="$ORB_LIBDIR $ORB_LIBS $LIBS"
         
AC_SUBST(VISI_PREFIX)

ORB_PREFIX=$VISI_PREFIX
AC_SUBST(VISI_PREFIX)

ORB=VisiBroker
AC_SUBST(ORB)


IDL=$VISI_PREFIX/bin/idl2cpp
AC_SUBST(IDL,$IDL)
IDLCXX=$VISI_PREFIX/bin/idl2cpp
AC_SUBST(IDLCXX,$IDLCXX)

IDLFLAGS="$IDLFLAGS -I$VISI_PREFIX/idl "
if test "$ac_cv_cxx_namespaces" = yes
then
  IDLFLAGS="$IDLFLAGS -namespace"
  AC_DEFINE(CORBA_MODULE_NAMESPACE_MAPPING,1,[Define if we use namespaces with visibroker])
  AC_DEFINE(CORBA_IS_CLASS,1,[Define if we use classes for CORBA under visibroker])
else
  AC_DEFINE(CORBA_MODULE_CLASS_MAPPING,1,[Define if we use classes for namespaces under visibroker])
fi

AC_SUBST(IDLFLAGS)

ORB_INCLUDE_PREFIX=$OB_PREFIX/include
AC_SUBST(ORB_INCLUDE_PREFIX)


IDL_CLN_H=_c.hh
IDL_CLN_H_SUFFIX=_c.hh
IDL_CLN_H1_SUFFIX=no
AC_SUBST(IDL_CLN_H,$IDL_CLN_H)
AC_SUBST(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX)
AC_SUBST(IDL_CLN_H1_SUFFIX,$IDL_CLN_H1_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_CLN_H,$IDL_CLN_H,[Define the suffix for c++ client include files])
AC_DEFINE_UNQUOTED(IDL_CLN_H_SUFFIX,$IDL_CLN_H_SUFFIX,[Define the suffix for c++ client include files])

IDL_CLN_CPP=_c.cc
IDL_CLN_CPP_SUFFIX=_c.cc
AC_SUBST(IDL_CLN_CPP,$IDL_CLN_CPP)
AC_SUBST(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP)
AC_DEFINE_UNQUOTED(IDL_CLN_CPP_SUFFIX,$IDL_CLN_CPP,[Define the suffix for c++ client implementation  files])

IDL_CLN_O=_c.o 
IDL_CLN_OBJ_SUFFIX=_c.o 
AC_SUBST(IDL_CLN_O,$IDL_CLN_O)
AC_SUBST(IDL_CLN_OBJ_SUFFIX,$IDL_CLN_OBJ_SUFFIX)

IDL_SRV_H=_s.hh 
IDL_SRV_H_SUFFIX=_s.hh 
IDL_SRV_H1_SUFFIX=no 
AC_SUBST(IDL_SRV_H,$IDL_SRV_H)
AC_SUBST(IDL_SRV_H_SUFFIX,$IDL_SRV_H_SUFFIX)
AC_SUBST(IDL_SRV_H1_SUFFIX,$IDL_SRV_H_SUFFIX)
AC_DEFINE_UNQUOTED(IDL_SRV_H_SUFFIX,$IDL_SRV_H,[Define the suffix for c++ server include files])

IDL_SRV_CPP=_s.cc
IDL_SRV_CPP_SUFFIX=_s.cc
AC_SUBST(IDL_SRV_CPP,$IDL_SRV_CPP)
AC_SUBST(IDL_SRV_CPP_SUFFIX,$IDL_SRV_CPP)

IDL_SRV_O=_s.o
IDL_SRV_OBJ_SUFFIX=_s.o
AC_SUBST(IDL_SRV_O,$IDL_SRV_O)
AC_SUBST(IDL_SRV_OBJ_SUFFIX,$IDL_SRV_O)

IDL_TIE_H_SUFFIX=no
IDL_TIE_H1_SUFFIX=no
IDL_TIE_CPP_SUFFIX=no
AC_SUBST(IDL_TIE_H_SUFFIX,$IDL_TIE_H_SUFFIX)
AC_SUBST(IDL_TIE_H1_SUFFIX,$IDL_TIE_H1_SUFFIX)
AC_SUBST(IDL_TIE_CPP_SUFFIX,$IDL_TIE_CPP_SUFFIX)


CORBA_H='corba.h'
AC_DEFINE_UNQUOTED(CORBA_H,<$CORBA_H>,[Define the name of the CORBA include file])

COSNAMING_H='CosNaming_c.h'
AC_DEFINE_UNQUOTED(COSNAMING_H,<$COSNAMING_H>,[Define the name of the COSNaming include file])
ORB_COSNAMING_LIB="-lcosnm_r"
AC_SUBST(ORB_COSNAMING_LIB)

AC_DEFINE(CORBA_HAVE_POA,1,[Defined if the ORB implements POA])
AC_DEFINE(CORBA_SYSTEM_EXCEPTION_IS_STREAMBLE,1,[Defined if exeception could be pass to cout])
AC_DEFINE(CORBA_ORB_HAVE_NO_DESTROY,1,[Defined if the ORB has no destroy operation])
HAVE_ORB_IDL=1
AC_SUBST(HAVE_ORB_IDL)
  
AC_DEFINE(VISIBROKER,1,[Defined if visibroker is present])

else

visibroker=no
CPPFLAGS=$svCPPFLAGS
CXXCPPFLAGS=$svCXXCPPFLAGS
CXXFLAGS=$svCXXFLAGS
LIBS=$svLIBS
eval $rssh_rollback
rssh_rollback=$svRSSH_ROLLBACK

fi

AC_LANG_RESTORE

AC_MSG_RESULT(Visibroker check result: $visibroker)

])dnl
dnl

dnl @synopsis AC_CXX_NAMESPACES
dnl
dnl If the compiler can prevent names clashes using namespaces, define
dnl HAVE_NAMESPACES.
dnl
dnl @version $Id: aclocal.m4,v 1.1 2002/10/07 07:01:10 tom Exp $
dnl @author Luc Maisonobe
dnl
AC_DEFUN(AC_CXX_NAMESPACES,
[AC_CACHE_CHECK(whether the compiler implements namespaces,
ac_cv_cxx_namespaces,
[AC_LANG_SAVE
 AC_LANG_CPLUSPLUS
 AC_TRY_COMPILE([namespace Outer { namespace Inner { int i = 0; }}],
                [using namespace Outer::Inner; return i;],
 ac_cv_cxx_namespaces=yes, ac_cv_cxx_namespaces=no)
 AC_LANG_RESTORE
])
if test "$ac_cv_cxx_namespaces" = yes; then
  AC_DEFINE(HAVE_NAMESPACES,,[define if the compiler implements namespaces])
fi
])

