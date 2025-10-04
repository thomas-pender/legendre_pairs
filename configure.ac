#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([legendre], [0.0], [tsp7@sfu.ca])

AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_SRCDIR([src/amicable.c++])
AC_CONFIG_HEADERS([src/config.h])

AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror])

AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_AR
AC_PROG_CXX

LT_PREREQ([2.4.6])
LT_INIT([static disable-shared])

#-------------------------------------------------
# doxygen
#-------------------------------------------------
DX_INIT_DOXYGEN([$PACKAGE_NAME],[Doxyfile],doc)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)

if test "x${DX_FLAG_doc}" = "x1"; then
_doxy=yes
fi

AM_CONDITIONAL([DOXY], [test "x${_doxy}" = xyes])
#-------------------------------------------------

#-------------------------------------------------
# C++20
#-------------------------------------------------
AX_CXX_COMPILE_STDCXX(20)
#-------------------------------------------------

#-------------------------------------------------
# check for math library -lm
#-------------------------------------------------
have_math=no
AC_SEARCH_LIBS([exp], [m], [have_math=yes])

if test "x${have_math}" = xyes; then
AC_CHECK_HEADERS([math.h], [], have_math=no)
fi

if test "x${have_math}" = xno; then
AC_MSG_ERROR([
--------------------------------------------
The math library m must be installed and in
the search path of the compiler. Check
'config.log' for more information.
--------------------------------------------])
fi
#-------------------------------------------------

#-------------------------------------------------
# check for fftw3 library -lfftw3
#-------------------------------------------------
have_fftw=no
AC_SEARCH_LIBS([fftw_malloc], [fftw3], [have_fftw=yes])

if test "x${have_fftw}" = xyes; then
AC_CHECK_HEADERS([fftw3.h], [], [have_fftw=no])
fi

if test "x${have_fftw}" = xno; then
AC_MSG_ERROR([
--------------------------------------------
The library fftw3 must be installed and in
the search path of the compiler. Check
'config.log' for more information.
--------------------------------------------])
fi
#-------------------------------------------------

#-------------------------------------------------
# check for combinat library
# only the headers need to be included
# and no linking is done
#-------------------------------------------------
AC_LANG_PUSH([C++])
have_strings=yes
AC_CHECK_HEADERS([combinat.h], [], [have_strings=no])

if test "x${have_strings}" = xno; then
AC_MSG_ERROR([
--------------------------------------------
The library combinat must be installed and in
the search path of the compiler. Check
'config.log' for more information.
--------------------------------------------])
fi
AC_LANG_POP([C++])
#-------------------------------------------------

AC_SUBST([LIBS])

AC_CONFIG_FILES([Makefile Doxyfile])
AC_OUTPUT

cat << EOF

============================================================

${PACKAGE_NAME} version ${PACKAGE_VERSION}

Prefix: ${prefix}
CXX compiler: '${CXX} ${CXXFLAGS} ${CPPFLAGS} ${LDFLAGS} ${LIBS}'
Compile with 'make'.

============================================================

EOF
