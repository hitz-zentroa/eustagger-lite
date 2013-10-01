/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
/* Tokens.  */
#define t_forma_lerro 258
#define t_anal 259
#define t_forma 260
#define t_ald 261
#define t_aldaera 262
#define t_lema 263
#define t_morfema 264
#define t_sarrera 265
#define t_funtzioak 266
#define t_sinbolo 267
#define t_sinbolo_list 268
#define t_sinbolo_list_sym 269
#define t_sinbolo_set 270
#define t_literal 271
#define t_dolar 272
#define t_erregela 273
#define t_erroa 274
#define t_paren_ireki 275
#define t_paren_itxi 276
#define t_koma 277
#define t_stwol 278
#define t_atwol 279
#define t_lhb 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 42 "ana2morfsar.y"
{
  string *str;
  char  kar;
}
/* Line 1529 of yacc.c.  */
#line 104 "ana2morfsar.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE ana2morfsarlval;

