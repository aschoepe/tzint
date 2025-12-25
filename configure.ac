#!/bin/bash -norc
dnl	This file is an input file used by the GNU "autoconf" program to
dnl	generate the file "configure", which is run during Tcl installation
dnl	to configure the system for the local environment.

#-----------------------------------------------------------------------
# Sample configure.in for Tcl Extensions.  The only places you should
# need to modify this file are marked by the string __CHANGE__
#-----------------------------------------------------------------------

#-----------------------------------------------------------------------
# __CHANGE__
# Set your package name and version numbers here.
#
# This initializes the environment with PACKAGE_NAME and PACKAGE_VERSION
# set as provided.  These will also be added as -D defs in your Makefile
# so you can encode the package version directly into the source files.
# This will also define a special symbol for Windows (BUILD_<PACKAGE_NAME>
# so that we create the export library with the dll.
#-----------------------------------------------------------------------

AC_INIT([tzint], [1.2])

#--------------------------------------------------------------------
# Call TEA_INIT as the first TEA_ macro to set up initial vars.
# This will define a ${TEA_PLATFORM} variable == "unix" or "windows"
# as well as PKG_LIB_FILE and PKG_STUB_LIB_FILE.
#--------------------------------------------------------------------

TEA_INIT()

AC_CONFIG_AUX_DIR(tclconfig)

#--------------------------------------------------------------------
# Load the tclConfig.sh file
#--------------------------------------------------------------------

TEA_PATH_TCLCONFIG
TEA_LOAD_TCLCONFIG

#--------------------------------------------------------------------
# Load the tkConfig.sh file if necessary (Tk extension)
#--------------------------------------------------------------------

#TEA_PATH_TKCONFIG
#TEA_LOAD_TKCONFIG

#-----------------------------------------------------------------------
# Handle the --prefix=... option by defaulting to what Tcl gave.
# Must be called after TEA_LOAD_TCLCONFIG and before TEA_SETUP_COMPILER.
#-----------------------------------------------------------------------

TEA_PREFIX

#-----------------------------------------------------------------------
# Standard compiler checks.
# This sets up CC by using the CC env var, or looks for gcc otherwise.
# This also calls AC_PROG_CC and a few others to create the basic setup
# necessary to compile executables.
#-----------------------------------------------------------------------

TEA_SETUP_COMPILER

#-----------------------------------------------------------------------
# __CHANGE__
# Specify the C source files to compile in TEA_ADD_SOURCES,
# public headers that need to be installed in TEA_ADD_HEADERS,
# stub library C source files to compile in TEA_ADD_STUB_SOURCES,
# and runtime Tcl library files in TEA_ADD_TCL_SOURCES.
# This defines PKG(_STUB)_SOURCES, PKG(_STUB)_OBJECTS, PKG_HEADERS
# and PKG_TCL_SOURCES.
#-----------------------------------------------------------------------

AC_ARG_ENABLE(filecmd, [  --enable-filecmd        with file command (png lib needed) (default: on)], [tcl_ok=$enableval], [tcl_ok=yes])

if test "$tcl_ok" = "no"; then

    AC_DEFINE(NO_CMD_FILE)

else

    AC_ARG_WITH(png-include, [  --with-png-include=DIR   PNG includes are in DIR], PNG_INC_DIR=$withval, PNG_INC_DIR="/usr/include")
    AC_ARG_WITH(png-lib, [  --with-png-lib=DIR	  PNG libraries are in DIR], PNG_LIB_DIR=$withval, PNG_LIB_DIR="/usr/lib")

    AC_ARG_ENABLE(pngstatic, [  --enable-pngstatic      link static with libpng.a (default: off)], [tcl_ok=$enableval], [tcl_ok=no])


    AC_MSG_CHECKING([for png header])
    if test ! -f ${PNG_INC_DIR}/png.h ; then
	AC_MSG_ERROR(Cannot find png.h in $PNG_INC_DIR use -with-png-include=?)
    fi
    AC_MSG_RESULT([yes])

    TEA_ADD_INCLUDES([-I"${PNG_INC_DIR}"])


    AC_MSG_CHECKING([for libpng lib])
    if test "$tcl_ok" = "yes"; then
	if test ! -f ${PNG_LIB_DIR}/libpng.a ; then
	    AC_MSG_ERROR(Cannot find libpng.a in $PNG_LIB_DIR use --with-png-lib=?)
	fi
    else 
	if test ! -f ${PNG_LIB_DIR}/libpng${TCL_SHLIB_SUFFIX} ; then
	    AC_MSG_ERROR(Cannot find libpng${TCL_SHLIB_SUFFIX} in $PNG_LIB_DIR use --with-png-lib=?)
	fi
    fi
    AC_MSG_RESULT([yes])

    if test "$tcl_ok" = "yes"; then
	TEA_ADD_LIBS([${PNG_LIB_DIR}/libpng.a])
    else
	TEA_ADD_LIBS([-L"${PNG_LIB_DIR}" -lpng])
    fi

fi


AC_DEFINE(ZINT_VERSION, "2.4.4")
AC_DEFINE(MY_TCL_INITSTUBS, "8.6-10")

TEA_ADD_SOURCES([common.c render.c png.c library.c ps.c large.c reedsol.c gs1.c svg.c])
TEA_ADD_SOURCES([code.c code128.c 2of5.c upcean.c telepen.c medical.c plessey.c rss.c])
TEA_ADD_SOURCES([postal.c auspost.c imail.c])
TEA_ADD_SOURCES([code16k.c dmatrix.c pdf417.c qr.c maxicode.c composite.c aztec.c code49.c code1.c gridmtx.c])
TEA_ADD_SOURCES([tps.c tsvg.c tzint.c])
TEA_ADD_HEADERS([])
TEA_ADD_INCLUDES([])
TEA_ADD_LIBS([-lz -lm])
TEA_ADD_CFLAGS([])
TEA_ADD_STUB_SOURCES([])
TEA_ADD_TCL_SOURCES([])

#--------------------------------------------------------------------
# __CHANGE__
#
# You can add more files to clean if your extension creates any extra
# files by extending CLEANFILES.
# Add pkgIndex.tcl if it is generated in the Makefile instead of ./configure
# and change Makefile.in to move it from CONFIG_CLEAN_FILES to BINARIES var.
#
# A few miscellaneous platform-specific items:
# TEA_ADD_* any platform specific compiler/build info here.
#--------------------------------------------------------------------

#CLEANFILES="$CLEANFILES pkgIndex.tcl"
if test "${TEA_PLATFORM}" = "windows" ; then
    # Ensure no empty if clauses
    :
    #TEA_ADD_SOURCES([win/winFile.c])
    #TEA_ADD_INCLUDES([-I\"$(${CYGPATH} ${srcdir}/win)\"])
else
    # Ensure no empty else clauses
    :
    #TEA_ADD_SOURCES([unix/unixFile.c])
    #TEA_ADD_LIBS([-lsuperfly])
fi

#--------------------------------------------------------------------
# __CHANGE__
# Choose which headers you need.  Extension authors should try very
# hard to only rely on the Tcl public header files.  Internal headers
# contain private data structures and are subject to change without
# notice.
# This MUST be called after TEA_LOAD_TCLCONFIG / TEA_LOAD_TKCONFIG
#--------------------------------------------------------------------

TEA_PUBLIC_TCL_HEADERS
#TEA_PRIVATE_TCL_HEADERS

#TEA_PUBLIC_TK_HEADERS
#TEA_PRIVATE_TK_HEADERS
#TEA_PATH_X

#--------------------------------------------------------------------
# Check whether --enable-threads or --disable-threads was given.
# This auto-enables if Tcl was compiled threaded.
#--------------------------------------------------------------------

TEA_ENABLE_THREADS

#--------------------------------------------------------------------
# The statement below defines a collection of symbols related to
# building as a shared library instead of a static library.
#--------------------------------------------------------------------

TEA_ENABLE_SHARED

#--------------------------------------------------------------------
# This macro figures out what flags to use with the compiler/linker
# when building shared/static debug/optimized objects.  This information
# can be taken from the tclConfig.sh file, but this figures it all out.
#--------------------------------------------------------------------

TEA_CONFIG_CFLAGS

#--------------------------------------------------------------------
# Set the default compiler switches based on the --enable-symbols option.
#--------------------------------------------------------------------

TEA_ENABLE_SYMBOLS

#--------------------------------------------------------------------
# Everyone should be linking against the Tcl stub library.  If you
# can't for some reason, remove this definition.  If you aren't using
# stubs, you also need to modify the SHLIB_LD_LIBS setting below to
# link against the non-stubbed Tcl library.  Add Tk too if necessary.
#--------------------------------------------------------------------

AC_DEFINE(USE_TCL_STUBS, 1, [Use Tcl stubs])
#AC_DEFINE(USE_TK_STUBS, 1, [Use Tk stubs])

#--------------------------------------------------------------------
# This macro generates a line to use when building a library.  It
# depends on values set by the TEA_ENABLE_SHARED, TEA_ENABLE_SYMBOLS,
# and TEA_LOAD_TCLCONFIG macros above.
#--------------------------------------------------------------------

TEA_MAKE_LIB

#--------------------------------------------------------------------
# Determine the name of the tclsh and/or wish executables in the
# Tcl and Tk build directories or the location they were installed
# into. These paths are used to support running test cases only,
# the Makefile should not be making use of these paths to generate
# a pkgIndex.tcl file or anything else at extension build time.
#--------------------------------------------------------------------

TEA_PROG_TCLSH
#TEA_PROG_WISH

#--------------------------------------------------------------------
# Finally, substitute all of the various values into the Makefile.
# You may alternatively have a special pkgIndex.tcl.in or other files
# which require substituting th AC variables in.  Include these here.
#--------------------------------------------------------------------

AC_OUTPUT([Makefile pkgIndex.tcl])
