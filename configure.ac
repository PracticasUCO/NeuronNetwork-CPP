#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
m4_include([m4/m4-ax_cxx_compile_stdcxx_11.m4])

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AC_CONFIG_SRCDIR([test/test.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_LANG([C++])
CXXFLAGS='-Wall -std=c++14'

# Check compiler standard supports C++11
AX_CXX_COMPILE_STDCXX_11([], [mandatory])

# Checks for libraries.
AC_CHECK_LIB([gtest], [main])

# Checks for header files.
AC_CHECK_HEADER([gtest/gtest.h],
                [AC_DEFINE([HAVE_GTEST_H], 1)],
                [AC_MSG_ERROR([unable to find the google test framework (gtest)])])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([pow sqrt])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
