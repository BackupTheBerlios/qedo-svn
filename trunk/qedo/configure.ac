#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.53)
AC_INIT(Qedo, 0.9.0, qedo@qedo.berlios.de)
AC_CONFIG_SRCDIR([gendef/gendef.cc])
AC_CONFIG_HEADER([ComponentIDL/config.h])


AC_ARG_WITH(xerces,
 [  --with-xerces-c=xercesdir         use Xerces installed in xercesdir],
 XERCESDIR=$withval, XERCESDIR="")
AC_SUBST(XERCESDIR)

# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_LN_S
AC_PROG_INSTALL
AC_CHECK_PROG(HAVE_MICO_CONFIG,mico-config,yes,no)
AC_CHECK_PROG(HAVE_MKDIR_PROG,mkdir,yes,no)
AC_SUBST(HAVE_MICO_CONFIG)

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen])
AC_CHECK_LIB([z], [deflate])
AC_CHECK_LIB([uuid], [uuid_generate])

if test X"$HAVE_MKDIR_PROG" != Xyes; then
  AC_MSG_ERROR([cannot mkdir program])
fi

qedo_save_LIBS=$LIBS
qedo_save_CPPFLAGS=$CPPFLAGS
XERCESDIR=""
if test X"$with_xerces_c" != X ;then
	XERCESDIR="$with_xerces_c"
fi
AC_CACHE_CHECK([for Apache's Xerces-C XML library],
    [HAVE_XERCES],
    [AC_LANG_SAVE
     AC_LANG_CPLUSPLUS
if test X"$XERCESDIR" = X ;then
	XERCES_LIBS="-lxerces-c"
	LIBS="-lxerces-c $LIBS"
	XERCESDIR=""
else
	XERCES_LIBS="-L$XERCESDIR/lib -lxerces-c"
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


# Checks for header files.
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([fcntl.h stddef.h stdlib.h string.h unistd.h utime.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_MKTIME
AC_FUNC_STAT
AC_FUNC_UTIME_NULL
AC_CHECK_FUNCS([getcwd gethostname mkdir strchr strdup strerror strstr utime])

OS=`uname`
AC_SUBST(OS)

AC_CONFIG_FILES([Makefile
                 MakeVars
                 ComponentIDL/Makefile
                 ComponentContainer/Makefile
                 ComponentInstaller/Makefile
                 ComponentServer/Makefile
                 ComponentServerActivator/Makefile
                 AssemblyFactory/Makefile
                 HomeFinder/Makefile
                 DeploymentClient/Makefile
                 etc/Makefile
                 ])

AC_OUTPUT
