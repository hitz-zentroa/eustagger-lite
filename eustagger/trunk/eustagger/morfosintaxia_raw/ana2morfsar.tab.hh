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

#ifndef ANA2MORFSAR_ANA2MORFSAR_TAB_HH
# define ANA2MORFSAR_ANA2MORFSAR_TAB_HH
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int ana2morfsardebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     t_forma_lerro = 258,
     t_anal = 259,
     t_forma = 260,
     t_ald = 261,
     t_aldaera = 262,
     t_lema = 263,
     t_morfema = 264,
     t_sarrera = 265,
     t_funtzioak = 266,
     t_sinbolo = 267,
     t_sinbolo_list = 268,
     t_sinbolo_list_sym = 269,
     t_sinbolo_set = 270,
     t_literal = 271,
     t_dolar = 272,
     t_erregela = 273,
     t_erroa = 274,
     t_paren_ireki = 275,
     t_paren_itxi = 276,
     t_koma = 277,
     t_stwol = 278,
     t_atwol = 279,
     t_lhb = 280
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{
/* Line 2049 of yacc.c  */
#line 43 "ana2morfsar.y"

  string *str;
  char  kar;


/* Line 2049 of yacc.c  */
#line 88 "ana2morfsar.tab.hh"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE ana2morfsarlval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int ana2morfsarparse (void *YYPARSE_PARAM);
#else
int ana2morfsarparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int ana2morfsarparse (void);
#else
int ana2morfsarparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !ANA2MORFSAR_ANA2MORFSAR_TAB_HH  */
