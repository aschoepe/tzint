#
# Include the TEA standard macro set
#

builtin(include,tclconfig/tcl.m4)

#
# Add here whatever m4 macros you want to define for your package
#

#------------------------------------------------------------------------
# TZINT_PATH_PNG --
#
#	Locate the PNG library and header files
#
# Arguments:
#	none
#
# Results:
#
#	Adds the following arguments to configure:
#		--enable-filecmd
#		--with-png-include=...
#		--with-png-lib=...
#		--enable-pngstatic
#
#	Defines the following vars:
#		PNG_INC_DIR	Full path to the directory containing png.h
#		PNG_LIB_DIR	Full path to the directory containing libpng
#
#	Sets up TEA_ADD_INCLUDES and TEA_ADD_LIBS accordingly
#	Defines NO_CMD_FILE if filecmd is disabled
#------------------------------------------------------------------------

AC_DEFUN([TZINT_PATH_PNG], [
    AC_ARG_ENABLE(filecmd,
	[  --enable-filecmd         with file command (png lib needed) (default: on)],
	[enable_filecmd=$enableval],
	[enable_filecmd=yes])

    if test "$enable_filecmd" = "no"; then
	AC_DEFINE(NO_CMD_FILE)
    else
	AC_ARG_WITH(png-include,
	    [  --with-png-include=DIR   PNG includes are in DIR],
	    [PNG_INC_DIR=$withval],
	    [PNG_INC_DIR=""])

	AC_ARG_WITH(png-lib,
	    [  --with-png-lib=DIR       PNG libraries are in DIR],
	    [PNG_LIB_DIR=$withval],
	    [PNG_LIB_DIR=""])

	AC_ARG_ENABLE(pngstatic,
	    [  --enable-pngstatic       link static with libpng.a (default: off)],
	    [png_static=$enableval],
	    [png_static=no])

    #--------------------------------------------------------------------
    # Search for png.h in common locations
    #--------------------------------------------------------------------
    AC_MSG_CHECKING([for png header])

    if test "x${PNG_INC_DIR}" = "x" ; then
	# Search in common locations
	png_inc_search="/usr/include /usr/local/include /opt/local/include /opt/homebrew/include /usr/include/libpng16 /usr/local/include/libpng16"

	for dir in $png_inc_search ; do
	    if test -f "$dir/png.h" ; then
		PNG_INC_DIR="$dir"
		break
	    fi
	done
    fi

    if test "x${PNG_INC_DIR}" = "x" || test ! -f "${PNG_INC_DIR}/png.h" ; then
	AC_MSG_ERROR([Cannot find png.h. Use --with-png-include=DIR to specify location])
    fi

    AC_MSG_RESULT([${PNG_INC_DIR}])
    TEA_ADD_INCLUDES([-I"${PNG_INC_DIR}"])

    #--------------------------------------------------------------------
    # Search for libpng in common locations
    #--------------------------------------------------------------------
    AC_MSG_CHECKING([for libpng library])

    if test "x${PNG_LIB_DIR}" = "x" ; then
	# Search in common locations
	png_lib_search="/usr/lib /usr/local/lib /opt/local/lib /opt/homebrew/lib /usr/lib/x86_64-linux-gnu"

	if test "$png_static" = "yes"; then
	    png_lib_name="libpng.a"
	else
	    png_lib_name="libpng${TCL_SHLIB_SUFFIX}"
	fi

	for dir in $png_lib_search ; do
	    if test -f "$dir/$png_lib_name" ; then
		PNG_LIB_DIR="$dir"
		break
	    fi
	    # Also try with version suffix
	    if test -f "$dir/libpng16${TCL_SHLIB_SUFFIX}" ; then
		PNG_LIB_DIR="$dir"
		break
	    fi
	done
    fi

    if test "x${PNG_LIB_DIR}" = "x" ; then
	AC_MSG_ERROR([Cannot find libpng. Use --with-png-lib=DIR to specify location])
    fi

    # Verify the library exists
    if test "$png_static" = "yes"; then
	if test ! -f "${PNG_LIB_DIR}/libpng.a" ; then
	    AC_MSG_ERROR([Cannot find libpng.a in ${PNG_LIB_DIR}])
	fi
	AC_MSG_RESULT([${PNG_LIB_DIR}/libpng.a (static)])
	TEA_ADD_LIBS([${PNG_LIB_DIR}/libpng.a])
    else
	if test ! -f "${PNG_LIB_DIR}/libpng${TCL_SHLIB_SUFFIX}" && test ! -f "${PNG_LIB_DIR}/libpng16${TCL_SHLIB_SUFFIX}" ; then
	    AC_MSG_ERROR([Cannot find libpng${TCL_SHLIB_SUFFIX} in ${PNG_LIB_DIR}])
	fi
	AC_MSG_RESULT([${PNG_LIB_DIR}])
	TEA_ADD_LIBS([-L"${PNG_LIB_DIR}" -lpng])
    fi
    fi
])
