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
/* Tokens.  */
#define INFORMAZIOA 258
#define LEMAA 259
#define HAT_INFO 260
#define HITZA 261
#define OHARRA 262
#define HAT_LEMA 263
#define HITZ_FORMA 264
#define ETIK 265
#define ETIK_PUNT 266
#define ALDAERA 267
#define ETIK_HAUL 268
#define ZIFRA 269
#define PAR_IREKI 270
#define PAR_ITXI 271
#define ERROA 272
#define ETENA 273
#define EZORD 274
#define BUK_MARKA 275
#define BAI 276
#define EZ 277
#define PIPE 278
#define OSAGAI_KOP 279
#define FORMA_DA 280
#define LEMA_DA 281
#define CORRECT 282
#define AMAITU 283




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 36 "hat_karga.y"
{
        char str[500];
        char kar;
        int zif;
       }
/* Line 1529 of yacc.c.  */
#line 111 "hat_karga.tab.hh"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE hat_kargalval;

