/* A Bison parser, made by GNU Bison 2.6.1.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef HAT_KARGA_HAT_KARGA_TAB_HH
# define HAT_KARGA_HAT_KARGA_TAB_HH
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int hat_kargadebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INFORMAZIOA = 258,
     LEMAA = 259,
     HAT_INFO = 260,
     HITZA = 261,
     OHARRA = 262,
     HAT_LEMA = 263,
     HITZ_FORMA = 264,
     ETIK = 265,
     ETIK_PUNT = 266,
     ALDAERA = 267,
     ETIK_HAUL = 268,
     ZIFRA = 269,
     PAR_IREKI = 270,
     PAR_ITXI = 271,
     ERROA = 272,
     ETENA = 273,
     EZORD = 274,
     BUK_MARKA = 275,
     BAI = 276,
     EZ = 277,
     PIPE = 278,
     OSAGAI_KOP = 279,
     FORMA_DA = 280,
     LEMA_DA = 281,
     CORRECT = 282,
     AMAITU = 283
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 37 "hat_karga.y"

        char str[500];
        char kar;
        int zif;
       

/* Line 2049 of yacc.c  */
#line 92 "hat_karga.tab.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE hat_kargalval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int hat_kargaparse (void *YYPARSE_PARAM);
#else
int hat_kargaparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int hat_kargaparse (void);
#else
int hat_kargaparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !HAT_KARGA_HAT_KARGA_TAB_HH  */
