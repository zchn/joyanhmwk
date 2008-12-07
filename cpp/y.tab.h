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
     MAIN = 258,
     PRINTF = 259,
     INT = 260,
     VOID = 261,
     CHAR = 262,
     AUTO = 263,
     STATIC = 264,
     STRUCT = 265,
     RETURN = 266,
     NUM = 267,
     CHARACTER = 268,
     ID = 269,
     LOGOR = 270,
     LOGAND = 271,
     LOGNEQ = 272,
     LOGEQU = 273,
     LESSEQU = 274,
     MOREEQU = 275,
     LESSTHAN = 276,
     MORETHAN = 277
   };
#endif
/* Tokens.  */
#define MAIN 258
#define PRINTF 259
#define INT 260
#define VOID 261
#define CHAR 262
#define AUTO 263
#define STATIC 264
#define STRUCT 265
#define RETURN 266
#define NUM 267
#define CHARACTER 268
#define ID 269
#define LOGOR 270
#define LOGAND 271
#define LOGNEQ 272
#define LOGEQU 273
#define LESSEQU 274
#define MOREEQU 275
#define LESSTHAN 276
#define MORETHAN 277




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 30 "sc.y"
{
	char *id_val;
	int num_val;
	int attrib_val;
	struct {
		symtab_head_t *psymhead;
	} declst_type;
	struct {
		symtab_node_t *psymnode;
	} dec_type;
	symtab_node_t *exp_type;
	struct {
		symtab_node_t *offsetvar;/*若是array类型的var，此域记录其offset*/
		symtab_node_t *retvar;
	} exexp_type;
	int notype;
	int stat_type;
}
/* Line 1489 of yacc.c.  */
#line 112 "y.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

