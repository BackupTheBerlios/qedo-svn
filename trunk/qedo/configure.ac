#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(Qedo, 0.6.0, www.qedo.org)
AC_CONFIG_SRCDIR([gendef/gendef.cc])
AC_CONFIG_HEADER([ComponentIDL/config.h])


AC_ARG_WITH(uuid,
 [  --with-uuid=dir         use UUID library installed in dir],
 UUIDDIR=$withval, UUIDDIR="")

AC_ARG_WITH(xerces,
 [  --with-xerces-c=dir     use Xerces installed in dir],
 XERCESDIR=$withval, XERCESDIR="")
AC_SUBST(XERCESDIR)

AC_ARG_WITH(mico,
 [  --with-mico=dir         use Mico installed in dir],
 MICODIR=$withval, MICODIR="")
AC_SUBST(MICODIR)

AC_ARG_WITH(orbacus,
 [  --with-orbacus=dir      use Orbacus installed in dir],
 ORBACUSDIR=$withval, ORBACUSDIR="")

AC_ARG_WITH(wxGTK,
 [  --with-wxGTK=dir        use wxGTK installed in dir],
 WXGTKDIR=$withval, WXGTKDIR="/usr")
AC_SUBST(WXGTKDIR)

AC_ARG_ENABLE(optimize,
 [  --disable-optimize      do not use -O2 to compile (default on)],
 use_opt=$enableval, use_opt=yes)

AC_ARG_ENABLE(debug,
 [  --enable-debug          use -g to compile (default off)],
 use_debug=$enableval, use_debug=no)

AC_ARG_ENABLE(streams,
 [  --enable-streams        compile stream support in container (default on)],
 use_streams=$enableval, use_streams=yes)

AC_ARG_ENABLE(qos,
 [  --disable-qos           compile QoS support in container (default off)],
 use_qos=$enableval, use_qos=no)

AC_ARG_ENABLE(db,
 [  --disable-db            compile Database support in container (default off)],
 use_db=$enableval, use_db=no)

# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LN_S
AC_PROG_INSTALL

if test X"$with_mico" != X -a X"$with_orbacus" != X; then
  AC_MSG_ERROR([you can use either Mico or Orbacus])
fi

QEDO_ORB=MICO_ORB

ORBACUSDIR=""
if test X"$with_orbacus" != X ;then
	ORBACUSDIR="$with_orbacus"
	HAVE_ORBACUS=yes
	QEDO_ORB=ORBACUS_ORB

	AC_MSG_NOTICE([please make sure, that $ORBACUSDIR/bin/idl will run])
else
	MICODIR=""
	if test X"$with_mico" != X ;then
		MICODIR="$with_mico"
		QEDO_ORB=MICO_ORB
		AC_CHECK_PROG(HAVE_MICO_CONFIG,mico-config,yes,no,[$MICODIR/bin])
		AC_MSG_NOTICE([please make sure, that $MICODIR/bin/idl will run])
	else
		AC_CHECK_PROG(HAVE_MICO_CONFIG,mico-config,yes,no)
	fi
	if test "$HAVE_MICO_CONFIG" != "yes"; then
 		AC_MSG_ERROR([found no mico-config])
	else
		QEDO_ORB=MICO_ORB
	fi
fi

AC_SUBST(HAVE_MICO_CONFIG)
AC_SUBST(HAVE_ORBACUS)
AC_SUBST(ORBACUSDIR)
AC_SUBST(QEDO_ORB)

AC_CHECK_PROG(HAVE_MKDIR_PROG,mkdir,yes,no)

if test X"$UUIDDIR" != X ; then
	LIBS="$LIBS -L$UUIDDIR"
fi

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen])
AC_CHECK_LIB([z], [deflate])
AC_CHECK_LIB([uuid], [uuid_generate],,[uuid=no])
AC_CHECK_LIB([pthread], [pthread_sigmask])

if test X"$uuid" == Xno; then
  AC_MSG_ERROR([you need a uuid library for Qedo])
fi

if test X"$HAVE_MKDIR_PROG" != Xyes; then
  AC_MSG_ERROR([cannot mkdir program])
fi

qedo_save_LIBS=$LIBS
qedo_save_CPPFLAGS=$CPPFLAGS
XERCESDIR=""
if test X"$with_xerces" != X ;then
	XERCESDIR="$with_xerces"
fi
AC_CACHE_CHECK([for Apache's Xerces-C XML library],
    [HAVE_XERCES],
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
if test X"$XERCESDIR" = X ;then
	XERCES_LIBS="-lxerces-c"
	XERCES_INCLUDES=""
	LIBS="-lxerces-c $LIBS"
	XERCESDIR=""
else
	XERCES_LIBS="-L$XERCESDIR/lib -lxerces-c"
	XERCES_INCLUDES="-I$XERCESDIR/include"
	LIBS="-L$XERCESDIR/lib -lxerces-c $LIBS"
	CPPFLAGS="-I$XERCESDIR/include $CPPFLAGS"
fi
     AC_TRY_LINK([
#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#ifndef XERCES_HAS_CPP_NAMESPACE
#define XERCES_CPP_NAMESPACE_QUALIFIER
#endif],
       [XERCES_CPP_NAMESPACE_QUALIFIER XMLPlatformUtils::Initialize();],
       [HAVE_XERCES=yes],
       [HAVE_XERCES=no])
       LIBS=$qedo_save_LIBS
	  CPPFLAGS=$qedo_save_CPPFLAGS
      AC_LANG_RESTORE
     ])

if test X"$HAVE_XERCES" = Xno; then
  AC_MSG_ERROR([cannot find libxerces-c])
fi
AC_SUBST(HAVE_XERCES)
AC_SUBST(XERCES_LIBS)
AC_SUBST(XERCES_INCLUDES)

HAVE_ODBCLIB=no
ODBCLIB=""

AC_CHECK_LIB([odbc],[SQLConnect],[HAVE_ODBCLIB=yes],[])

if test X"$HAVE_ODBCLIB" = Xyes ; then
	ODBCLIB="-lodbc"
else
	use_db=no
fi

AC_SUBST(ODBCLIB)

# do enable debug
CONF_OPT_FLAGS="-O2"
CONF_DEBUG_FLAGS="-g -D_DEBUG"
PICFLAGS="-fPIC"
AC_SUBST(PICFLAGS)

changequote(<<, >>)
CXXFLAGS=`echo " $CXXFLAGS " | sed -e 's/ -g / /g' -e 's/ -O[0-9]* / /g'`
CFLAGS=`echo " $CFLAGS " | sed -e 's/ -g / /g' -e 's/ -O[0-9]* / /g'`
changequote([, ])
if test X"$use_opt" != Xno; then
  CXXFLAGS="$CONF_OPT_FLAGS $CXXFLAGS"
  CFLAGS="$CONF_OPT_FLAGS $CFLAGS"
fi
if test X"$use_debug" != Xno; then
  CXXFLAGS="$CONF_DEBUG_FLAGS $CXXFLAGS"
  CFLAGS="$CONF_DEBUG_FLAGS $CFLAGS"
fi

QEDO_STREAMS=$use_streams
AC_SUBST(QEDO_STREAMS)
if test X"$use_streams" != Xyes; then
	AC_DEFINE(_QEDO_NO_STREAMS)
fi

QEDO_QOS=$use_qos
AC_SUBST(QEDO_QOS)
if test X"$use_qos" != Xyes; then
	AC_DEFINE(_QEDO_NO_QOS)
fi

QEDO_DB=$use_db
AC_SUBST(QEDO_DB)
if test X"$use_db" != Xyes; then
	AC_DEFINE(_QEDO_NO_DB)
fi

# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([fcntl.h stddef.h stdlib.h string.h unistd.h utime.h])
AC_LANG_SAVE
AC_LANG_CPLUSPLUS
AC_CHECK_HEADERS([cxxabi.h])
AC_CHECK_FUNCS([__cxa_demangle])
AC_LANG_RESTORE

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_STRUCT_TM
AC_TYPE_PID_T
AC_TYPE_SIGNAL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MKTIME
AC_FUNC_STAT
AC_FUNC_UTIME_NULL
AC_FUNC_MALLOC
AC_CHECK_FUNCS([getcwd gethostname mkdir strchr strdup strerror strstr utime])
AC_CHECK_FUNCS([sigaction strrchr waitpid sigwait])

OS=`uname`
AC_SUBST(OS)

AC_CONFIG_FILES([Makefile
                 MakeVars
                 ComponentIDL/Makefile
                 ComponentContainer/Makefile
                 qedoutil/Makefile
                 ComponentInstaller/Makefile
                 ComponentServer/Makefile
                 ComponentServer/qcs.sh
                 ComponentServerActivator/Makefile
                 AssemblyFactory/Makefile
                 HomeFinder/Makefile
                 DeploymentClient/Makefile
                 qcontroller/Makefile
		 explore_server/Makefile
                 etc/Makefile
                 etc/MakeComponentVars
                 ])

AC_OUTPUT
