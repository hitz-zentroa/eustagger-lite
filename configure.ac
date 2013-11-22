AC_INIT(eustagger_lite.cc)

dnl flag orokorrak zehaztu

AC_SUBST(CCFLAGS,["-g -fpic -Wall"])

dnl C/C++ konpiladoreak bilatu
AC_PROG_CC
AC_PROG_CXX
AC_LANG(C)
AC_LANG(C++)

AC_PROG_MAKE_SET

AC_HEADER_STDC

dnl BOOST goiburuak non daude?
AC_ARG_WITH(boost-include,
            [  --with-boost-include=DIR			Path of BOOST headers],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_INCLUDE_BOOST=$withval
            else
            AC_MSG_ERROR([Please specify a suitable BOOST include directory: --with-boost-include=DIR])
            fi ,
            CONF_INCLUDE_BOOST="")

dnl PCRE++ goiburuak non daude?
AC_ARG_WITH(pcreplusplus-include,
            [  --with-pcreplusplus-include=DIR		Path of PCRE++ headers],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_INCLUDE_PCREPLUSPLUS=$withval
            else
            AC_MSG_ERROR([Please specify a suitable PCRE++ include directory: --with-pcreplusplus-include=DIR"])
            fi ,
            CONF_INCLUDE_PCREPLUSPLUS="")

dnl PCRE++ liburutegia non dago?
AC_ARG_WITH(pcreplusplus-lib,
            [  --with-pcreplusplus-lib=DIR			Path of PCRE lib],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_LD_PCREPLUSPLUS=-L$withval;
	    [LDFLAGS="${LDFLAGS} -L${withval}"]
            else
            AC_MSG_ERROR([Please specify a suitable PCRE++ library directory: --with-pcreplusplus-lib=DIR])
            fi ,
            )

dnl FOMA goiburuak non daude?
AC_ARG_WITH(foma-include,
            [  --with-foma-include=DIR			Path of FOMA headers],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_INCLUDE_FOMA=$withval
            else
            AC_MSG_ERROR([Please specify a suitable FOMA include directory: --with-foma-include=DIR])
            fi ,
            CONF_INCLUDE_FOMA="")

dnl FOMA liburutegia non dago?
AC_ARG_WITH(foma-lib,
            [  --with-foma-lib=DIR				Path of FOMA lib],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_LD_FOMA=-L$withval;
	    [LDFLAGS="${LDFLAGS} -L${withval}"]
            else
            AC_MSG_ERROR([Please specify a suitable FOMA library directory: --with-foma-lib=DIR])
            fi ,
            )

dnl VISLCG3 goiburuak non daude?
AC_ARG_WITH(vislcg3-include,
            [  --with-vislcg3-include=DIR			Path of VISLCG3 headers],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_INCLUDE_VISLCG3=$withval
            else
            AC_MSG_ERROR([Please specify a suitable VISLCG3 include directory: --with-vislcg3-include=DIR])
            fi ,
            CONF_INCLUDE_VISLCG3="")


dnl VISLCG3 liburutegia non dago?
AC_ARG_WITH(vislcg3-lib,
            [  --with-vislcg3-lib=DIR			Path of VISLCG3 lib],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_LD_VISLCG3=-L$withval;
	    [LDFLAGS="${LDFLAGS} -L${withval}"]
            else
            AC_MSG_ERROR([Please specify a suitable VISLCG3 library directory: --with-vislcg3-lib=DIR])
            fi ,
            )


dnl SWIPL goiburuak non daude?
AC_ARG_WITH(swipl-include,
            [  --with-swipl-include=DIR			Path of SWIPL headers],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_INCLUDE_SWIPL=$withval
            else
            AC_MSG_ERROR([Please specify a suitable SWIPL include directory: --with-swipl-include=DIR])
            fi ,
            CONF_INCLUDE_SWIPL="")


dnl SWIPL liburutegia non dago?
AC_ARG_WITH(swipl-lib,
            [  --with-swipl-lib=DIR				Path of SWIPL lib],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_LD_SWIPL=-L$withval;
	    [LDFLAGS="${LDFLAGS} -L${withval}"]
            else
            AC_MSG_ERROR([Please specify a suitable SWIPL library directory: --with-swipl-lib=DIR])
            fi ,
            )


dnl swipl-ld eta swipl programak non daude?
AC_ARG_WITH(swipl-bin,
            [  --with-swipl-bin=DIR				Path of swipl & swipl-ld programs],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_SWIPLLD=$withval
   	    [PATH="${PATH}:${withval}"]
            else
            AC_MSG_ERROR([Please specify a correct PATH for swipl & swipl-ld programs: --with-swipl-bin=DIR])
            fi ,
            CONF_SWIPLLD="")

dnl bison programa non dago?
AC_ARG_WITH(bison,
            [  --with-bison=PROGRAM				Path of bison program],
            if test [ x$withval != x ] -a [ -f $withval ]; then
            CONF_BISON=$withval
            else
            AC_MSG_ERROR([Please specify a correct PATH for bison program: --with-bison=PROGRAMPATH])
            fi ,
            CONF_BISON="")


dnl flex programa non dago?
AC_ARG_WITH(flex,
            [  --with-flex=PROGRAN				Path of flex program],
            if test [ x$withval != x ] -a [ -f $withval ]; then
            CONF_FLEX=$withval
            else
	    AC_MSG_ERROR([Please specify a correct PATH for flex program: --with-flex=PROGRAMPATH])
            fi ,
            CONF_FLEX="")

dnl Freeling goiburuak non daude?
AC_ARG_WITH(freeling-include,
            [  --with-freeling-include=DIR			Path of Freeling 3.0 headers],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_INCLUDE_FREELING=$withval
            else
            AC_MSG_ERROR([Please specify a suitable Freeling 3.0 include directory: --with-freeling-include=DIR"])
            fi ,
            CONF_INCLUDE_FREELING="")

dnl Freeling liburutegia non dago?
AC_ARG_WITH(freeling-lib,
            [  --with-freeling-lib=DIR			Path of Freeling 3.0 lib],
            if test [ x$withval != x ] -a [ -d $withval ]; then
            CONF_LD_FREELING=-L$withval;
	    [LDFLAGS="${LDFLAGS} -L${withval}"]
            else
            AC_MSG_ERROR([Please specify a suitable Freeling 3.0 library directory: --with-freeling-lib=DIR])
            fi ,
            )

dnl boost bilatu, kasu hoentan config.hpp bilatuko dugu

if test "$CONF_INCLUDE_BOOST" = "" ; then
   AC_CHECK_HEADER(boost/config.hpp,, AC_MSG_ERROR([Please specify a suitable BOOST include directory: --with-boost-include=DIR]))
else
   AC_CHECK_FILE($CONF_INCLUDE_BOOST/boost/config.hpp,CONF_INCLUDE_BOOST=-I$CONF_INCLUDE_BOOST,AC_MSG_ERROR([Please specify a suitable BOOST include directory which contains general boost subdir: --with-boost-include=DIR]))
fi

AC_SUBST(CONF_INCLUDE_BOOST)

dnl pcre++.h bilatu

if test "$CONF_INCLUDE_PCREPLUSPLUS" = "" ; then
   AC_CHECK_HEADER(pcre++.h,, AC_MSG_ERROR([Please specify a suitable PCRE include directory: --with-pcreplusplus-include=DIR]))
else
   AC_CHECK_FILE($CONF_INCLUDE_PCREPLUSPLUS/pcre++.h,CONF_INCLUDE_PCREPLUSPLUS=-I$CONF_INCLUDE_PCREPLUSPLUS,AC_MSG_ERROR([Please specify a suitable PCRE include directory: --with-pcreplusplus-include=DIR]))
fi

AC_SUBST(CONF_INCLUDE_PCREPLUSPLUS)

dnl pcre++ liburutegia bilatu
AC_CHECK_LIB(pcre++,
	     main,
	     ,
	     AC_MSG_ERROR([libpcre++ not found. Please specify a suitable PCRE++ library directory: --with-pcreplusplus-lib=DIR]))

AC_SUBST(CONF_LD_PCREPLUSPLUS)

dnl fomalib.h bilatu

if test "$CONF_INCLUDE_FOMA" = "" ; then
   AC_CHECK_HEADER(fomalib.h,, AC_MSG_ERROR([Please specify a suitable FOMA include directory: --with-foma-include=DIR]),-)
else
  AC_CHECK_FILE($CONF_INCLUDE_FOMA/fomalib.h,CONF_INCLUDE_FOMA=-I$CONF_INCLUDE_FOMA,AC_MSG_ERROR([Please specify a suitable FOMA include directory: --with-foma-include=DIR]))
fi

AC_SUBST(CONF_INCLUDE_FOMA)


dnl foma liburutegia bilatu
AC_CHECK_LIB(foma,
	     main,
	     ,
	     AC_MSG_ERROR([libfoma not found. Please specify a suitable FOMA library directory: --with-foma-lib=DIR]))

AC_SUBST(CONF_LD_FOMA)

dnl cg3.h bilatu

if test "$CONF_INCLUDE_VISLCG3" = "" ; then
   AC_CHECK_HEADER(cg3.h,, AC_MSG_ERROR([Please specify a suitable VISLCG3 include directory: --with-vislcg3-include=DIR]))
else
   AC_CHECK_FILE($CONF_INCLUDE_VISLCG3/cg3.h,CONF_INCLUDE_VISLCG3=-I$CONF_INCLUDE_VISLCG3,AC_MSG_ERROR([Please specify a suitable VISLCG3 include directory: --with-vislcg3-include=DIR]))
fi

AC_SUBST(CONF_INCLUDE_VISLCG3)

dnl  libcg3.so liburutegia bilatu
AC_CHECK_LIB(cg3,
	     main,
	     ,
	     AC_MSG_ERROR([libcg3 not found. Please specify a suitable VISLCG3 library directory: --with-vislcg3-lib=DIR]))

AC_SUBST(CONF_LD_VISLCG3)

dnl SWI-Prolog.h bilatu

if test "$CONF_INCLUDE_SWIPL" = "" ; then
   AC_CHECK_HEADER(SWI-Prolog.h,, AC_MSG_ERROR([Please specify a suitable SWIPL include directory: --with-swipl-include=DIR]))
else
   AC_CHECK_FILE($CONF_INCLUDE_SWIPL/SWI-Prolog.h,CONF_INCLUDE_SWIPL=-I$CONF_INCLUDE_SWIPL,AC_MSG_ERROR([Please specify a suitable SWIPL include directory: --with-swipl-include=DIR]))
fi

AC_SUBST(CONF_INCLUDE_SWIPL)

dnl libswipl.a liburutegia bilatu
AC_CHECK_LIB(swipl,
	     main,
	     ,
	     AC_MSG_ERROR([libswipl not found. Please specify a suitable SWIPL library directory: --with-swipl-lib=DIR]))

AC_SUBST(CONF_LD_SWIPL)

dnl swipl-ld programa bilatu

if test "$CONF_SWIPLLD" = "" ; then
   AC_CHECK_PROG(CONF_SWIPLLD_HELP,swipl-ld,yes,no)
   if test "$CONF_SWIPLLD_HELP" = "no" ; then
      AC_MSG_ERROR([Program swipl-ld not found in PATH. Please specify a correct PATH for swipl & swipl-ld programs: --with-swipl-bin=DIR])
   fi
else
   AC_CHECK_FILE($CONF_SWIPLLD/swipl-ld,,AC_MSG_ERROR([Please specify a correct PATH for swipl & swipl-ld programs: --with-swipl-bin=DIR]))
fi

AC_SUBST(CONF_SWIPLLD)

dnl bison programa bilatu

if test "$CONF_BISON" = "" ; then
   AC_CHECK_PROG(CONF_BISON, bison, bison)
fi
if test "$CONF_BISON" = "" ; then
   AC_MSG_ERROR([Program bison not found in PATH. Please specify a suitable bison program path: --with-bison=PATH])
fi

AC_SUBST(CONF_BISON)

dnl flex programa bilatu

if test "$CONF_FLEX" = "" ; then
   AC_CHECK_PROG(CONF_FLEX, flex, flex)
fi
if test "$CONF_FLEX" = "" ; then
   AC_MSG_ERROR([Program flex not found in PATH. Please specify a suitable flex program path: --with-flex=PATH])
fi

AC_SUBST(CONF_FLEX)

dnl freeling goiburuak bilatu

if test "$CONF_INCLUDE_PCREPLUSPLUS" = "" ; then
   AC_CHECK_HEADER(freeling.h,, AC_MSG_ERROR([Please specify a suitable Freeling 3.0 include directory: --with-freeling-include=DIR]))
else
   AC_CHECK_FILE($CONF_INCLUDE_FREELING/freeling.h,CONF_INCLUDE_FREELING=-I$CONF_INCLUDE_FREELING,AC_MSG_ERROR([Please specify a suitable Freeling include directory: --with-freeling-include=DIR]))
fi

AC_SUBST(CONF_INCLUDE_FREELING)

dnl freeling liburutegia bilatu
AC_CHECK_LIB(freeling,
	     main,
	     ,
	     AC_MSG_ERROR([libfreeling not found. Please specify a suitable Freeling 3.0 library directory: --with-freeling-lib=DIR]))

AC_SUBST(CONF_LD_FREELING)




dnl Makefilean aldagaiak ordeztu


MAKEFILE_FILES="Makefile aurreprozesua_raw/Makefile morfologia/Makefile morfosintaxia_raw/Makefile habil/Makefile cg3manager/Makefile analisitresnak/Makefile"
SUBDIRS="aurreprozesua_raw morfologia morfosintaxia_raw habil cg3manager analisitresnak"

AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(SUBDIRS)
AC_SUBST(DBXMLSTR)
AC_SUBST(prefix)
AC_SUBST(CC)
AC_SUBST(CXX)

dnl Makefile idatzi
AC_OUTPUT($MAKEFILE_FILES)

