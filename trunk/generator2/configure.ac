#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.57)
AC_INIT(Qedo, 0.5.0, qedo@qedo.berlios.de)
AC_CONFIG_HEADER([CIDL_Frontend/CIDLFrontendLib/config.h])

AC_ARG_WITH(uuid,
 [  --with-uuid=uuiddir         use UUID library installed in uuiddir],
 UUIDDIR=$withval, UUIDDIR="")

AC_ARG_ENABLE(optimize,
 [  --disable-optimize      do not use -O2 to compile],
 use_opt=$enableval, use_opt=yes)

AC_ARG_ENABLE(debug,
 [  --enable-debug          use -g to compile],
 use_debug=$enableval, use_debug=no)


# Checks for programs.
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_INSTALL
AC_CHECK_PROG(HAVE_MICO_CONFIG,mico-config,yes,no)
AC_CHECK_PROG(HAVE_MKDIR_PROG,mkdir,yes,no)
AC_CHECK_PROG(HAVE_BISON,bison,yes,no)
AC_CHECK_PROG(HAVE_FLEX,flex,yes,no)
AC_CHECK_PROG(HAVE_PYTHON,python,yes,no)
AC_CHECK_PROG(HAVE_KC_PP,[kc++],yes,no)
AC_SUBST(HAVE_MICO_CONFIG)

if test X"$UUIDDIR" != X ; then
	LIBS="$LIBS -L$UUIDDIR"
fi

# Checks for libraries.

AC_CHECK_LIB([uuiid], [uuid_generate],,[uuid=no])

if test X"$uuid" == Xno; then
  AC_MSG_ERROR([cannot find library uuid])
fi

if test X"$HAVE_MKDIR_PROG" != Xyes; then
  AC_MSG_ERROR([cannot find mkdir program])
fi

if test X"$HAVE_BISON" != Xyes; then
  AC_MSG_ERROR([cannot find bison program])
fi
YACC=bison
AC_SUBST(YACC)

if test X"$HAVE_FLEX" != Xyes; then
  AC_MSG_ERROR([cannot find flex program])
fi
LEX=flex
AC_SUBST(LEX)

if test X"$HAVE_PYTHON" != Xyes; then
  AC_MSG_ERROR([cannot find python program])
fi
PYTHON=python
AC_SUBST(PYTHON)

if test X"$HAVE_KC_PP" != Xyes; then
  AC_MSG_ERROR([cannot find kc++ program])
fi
KC_PP="kc++"
AC_SUBST(KC_PP)

# do enable debug
CONF_OPT_FLAGS="-O2"
CONF_DEBUG_FLAGS="-g"

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
                 CIDL_Repository/IFRidl/Makefile
                 CIDL_Repository/ComponentRepositoryLib/Makefile
                 CIDL_Repository/CIDLRepositoryLib/Makefile
                 CIDL_Frontend/CIDLFrontendLib/Makefile
                 CIDL_Backend/CIDLGenerator/Makefile
                 ])

AC_OUTPUT
