/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



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




/* Copy the first part of user declarations.  */
#line 15 "sc.y"


#include <stdio.h>

#include "symtab.h"
#include "allocvar.h"
#include "allocfunc.h"
#include "op.h"
#include "initall.h"

void yyerror(const char *);
extern int lineno;
char *errtext_ptr;


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

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
/* Line 187 of yacc.c.  */
#line 174 "y.tab.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 187 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  39
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  50
/* YYNRULES -- Number of rules.  */
#define YYNRULES  98
/* YYNRULES -- Number of states.  */
#define YYNSTATES  152

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   277

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    37,     2,     2,     2,    36,     2,     2,
      34,    35,    26,    24,    29,    25,    38,    27,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    28,
       2,    15,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    30,     2,    31,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    32,     2,    33,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      16,    17,    18,    19,    20,    21,    22,    23
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     6,     7,     9,    12,    14,    16,    20,
      22,    26,    28,    30,    32,    35,    39,    44,    46,    49,
      50,    52,    54,    56,    58,    60,    63,    69,    74,    76,
      79,    83,    85,    88,    94,    96,    98,    99,   101,   105,
     108,   112,   115,   117,   120,   122,   124,   127,   130,   132,
     135,   137,   139,   141,   145,   148,   150,   156,   158,   162,
     164,   168,   170,   172,   176,   180,   184,   188,   190,   192,
     196,   200,   204,   208,   210,   212,   216,   220,   224,   228,
     232,   234,   236,   239,   242,   244,   246,   248,   253,   257,
     262,   264,   266,   268,   272,   273,   275,   279,   281
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      40,     0,    -1,    41,    42,    -1,    -1,    43,    -1,    42,
      43,    -1,    59,    -1,    44,    -1,    50,    45,    28,    -1,
      46,    -1,    45,    29,    46,    -1,    47,    -1,    14,    -1,
      48,    -1,    14,    49,    -1,    30,    88,    31,    -1,    30,
      88,    31,    49,    -1,    51,    -1,    52,    53,    -1,    -1,
       8,    -1,     9,    -1,     5,    -1,    54,    -1,    55,    -1,
      10,    14,    -1,    10,    14,    32,    56,    33,    -1,    10,
      32,    56,    33,    -1,    57,    -1,    56,    57,    -1,    58,
      45,    28,    -1,    53,    -1,    60,    64,    -1,    61,    14,
      34,    62,    35,    -1,     5,    -1,     7,    -1,    -1,    63,
      -1,    62,    29,    63,    -1,    50,    46,    -1,    32,    66,
      33,    -1,    32,    33,    -1,    44,    -1,    65,    44,    -1,
      65,    -1,    67,    -1,    66,    65,    -1,    66,    67,    -1,
      68,    -1,    67,    68,    -1,    71,    -1,    70,    -1,    69,
      -1,    11,    72,    28,    -1,    72,    28,    -1,    28,    -1,
       4,    34,    72,    35,    28,    -1,    73,    -1,    72,    29,
      73,    -1,    74,    -1,    83,    15,    73,    -1,    75,    -1,
      76,    -1,    75,    16,    75,    -1,    75,    17,    75,    -1,
      75,    19,    75,    -1,    75,    18,    75,    -1,    77,    -1,
      78,    -1,    77,    23,    77,    -1,    77,    22,    77,    -1,
      77,    21,    77,    -1,    77,    20,    77,    -1,    79,    -1,
      80,    -1,    79,    24,    79,    -1,    79,    25,    79,    -1,
      79,    26,    79,    -1,    79,    27,    79,    -1,    79,    36,
      79,    -1,    81,    -1,    82,    -1,    25,    81,    -1,    37,
      81,    -1,    83,    -1,    84,    -1,    86,    -1,    84,    30,
      72,    31,    -1,    84,    38,    14,    -1,    85,    34,    87,
      35,    -1,    14,    -1,    14,    -1,    88,    -1,    34,    72,
      35,    -1,    -1,    73,    -1,    87,    29,    73,    -1,    12,
      -1,    13,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    92,    92,   102,   114,   115,   118,   119,   123,   130,
     141,   154,   159,   168,   173,   184,   194,   206,   212,   217,
     218,   219,   222,   225,   230,   233,   249,   259,   272,   275,
     281,   286,   292,   302,   326,   327,   328,   331,   336,   342,
     348,   349,   352,   353,   356,   357,   358,   359,   362,   363,
     366,   367,   368,   371,   378,   379,   382,   389,   392,   397,
     400,   416,   421,   424,   433,   442,   451,   463,   468,   471,
     480,   489,   498,   509,   514,   517,   526,   536,   545,   554,
     565,   570,   573,   581,   591,   611,   616,   619,   639,   665,
     675,   690,   715,   726,   732,   733,   736,   741,   744
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MAIN", "PRINTF", "INT", "VOID", "CHAR",
  "AUTO", "STATIC", "STRUCT", "RETURN", "NUM", "CHARACTER", "ID", "'='",
  "LOGOR", "LOGAND", "LOGNEQ", "LOGEQU", "LESSEQU", "MOREEQU", "LESSTHAN",
  "MORETHAN", "'+'", "'-'", "'*'", "'/'", "';'", "','", "'['", "']'",
  "'{'", "'}'", "'('", "')'", "'%'", "'!'", "'.'", "$accept", "cpp_prog",
  "start_part", "translation_unit", "external_declare", "declaration",
  "declarator_list", "declarator", "direct_declarator", "array_declarator",
  "array_dimdec_list", "declaration_specifiers_sup",
  "declaration_specifiers", "storage_class_specifier", "type_specifier",
  "struct_specifier", "struct_defination", "struct_declaration_list",
  "struct_declaration", "type_specifier_sup", "function_defination",
  "function_defination_head", "rettype_specifier", "parameter_list",
  "parameter_declaration", "compound_statement", "declaration_list",
  "block_item_list", "statement_list", "statement", "return_statement",
  "expression_statement", "printf_statement", "expression",
  "assignment_expression", "conditional_expression", "logical_expression",
  "binary_expression", "relational_expression", "shift_expression",
  "arithmetic_exp", "cast_expression", "unary_sup_expression",
  "noarray_expression", "unary_expression", "postfix_expression",
  "funccall_head", "primary_expression", "argument_expression_list",
  "constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,    61,   270,   271,   272,   273,
     274,   275,   276,   277,    43,    45,    42,    47,    59,    44,
      91,    93,   123,   125,    40,    41,    37,    33,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    39,    40,    41,    42,    42,    43,    43,    44,    45,
      45,    46,    47,    47,    48,    49,    49,    50,    51,    52,
      52,    52,    53,    53,    54,    54,    55,    55,    56,    56,
      57,    58,    59,    60,    61,    61,    61,    62,    62,    63,
      64,    64,    65,    65,    66,    66,    66,    66,    67,    67,
      68,    68,    68,    69,    70,    70,    71,    72,    72,    73,
      73,    74,    75,    75,    75,    75,    75,    76,    77,    77,
      77,    77,    77,    78,    79,    79,    79,    79,    79,    79,
      80,    81,    81,    81,    82,    83,    84,    84,    84,    84,
      85,    86,    86,    86,    87,    87,    87,    88,    88
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     0,     1,     2,     1,     1,     3,     1,
       3,     1,     1,     1,     2,     3,     4,     1,     2,     0,
       1,     1,     1,     1,     1,     2,     5,     4,     1,     2,
       3,     1,     2,     5,     1,     1,     0,     1,     3,     2,
       3,     2,     1,     2,     1,     1,     2,     2,     1,     2,
       1,     1,     1,     3,     2,     1,     5,     1,     3,     1,
       3,     1,     1,     3,     3,     3,     3,     1,     1,     3,
       3,     3,     3,     1,     1,     3,     3,     3,     3,     3,
       1,     1,     2,     2,     1,     1,     1,     4,     3,     4,
       1,     1,     1,     3,     0,     1,     3,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,    19,     1,    34,    35,    20,    21,     2,     4,
       7,     0,    17,     0,     6,     0,     0,     5,    12,     0,
       9,    11,    13,    22,     0,    18,    23,    24,    19,    32,
       0,     0,    14,     8,     0,    25,     0,     0,     0,    97,
      98,    91,     0,    55,    41,     0,     0,    42,    44,    19,
      45,    48,    52,    51,    50,     0,    57,    59,    61,    62,
      67,    68,    73,    74,    80,    81,    84,    85,     0,    86,
      92,    19,     0,    10,     0,    31,     0,    28,     0,     0,
       0,    82,    84,     0,    83,    43,    40,    46,    47,    49,
      54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    94,     0,
       0,    37,    15,     0,    27,    29,     0,     0,    53,    93,
      58,    63,    64,    66,    65,    72,    71,    70,    69,    75,
      76,    77,    78,    79,    60,     0,    88,    95,     0,    39,
      19,    33,    16,    26,    30,     0,    87,     0,    89,    38,
      56,    96
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     8,     9,    10,    19,    20,    21,    22,
      32,    11,    12,    13,    75,    26,    27,    76,    77,    78,
      14,    15,    16,   110,   111,    29,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    82,    67,    68,    69,   138,    70
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -80
static const yytype_int16 yypact[] =
{
     -80,     6,   115,   -80,   -80,   -80,   -80,   -80,    85,   -80,
     -80,    13,   -80,    10,   -80,     2,    25,   -80,    36,    19,
     -80,   -80,   -80,   -80,    -7,   -80,   -80,   -80,    24,   -80,
      51,    69,   -80,   -80,    13,    27,    10,    57,   101,   -80,
     -80,    67,   101,   -80,   -80,   101,   101,   -80,   123,    75,
      93,   -80,   -80,   -80,   -80,    82,   -80,   -80,   128,   -80,
     129,   -80,    29,   -80,   -80,   -80,    59,   -22,    91,   -80,
     -80,   108,    65,   -80,    10,   -80,     8,   -80,    13,   101,
     137,   -80,   -80,    15,   -80,   -80,   -80,   123,    93,   -80,
     -80,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   134,   101,    13,
      35,   -80,    36,     9,   -80,   -80,   139,    38,   -80,   -80,
     -80,   145,   151,   -80,   -80,   -80,   -80,   -80,   -80,     4,
       4,   121,   121,    29,   -80,   105,   -80,   -80,    40,   -80,
     108,   -80,   -80,   -80,   -80,   109,   -80,   101,   -80,   -80,
     -80,   -80
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -80,   -80,   -80,   -80,   163,   -25,    94,   -33,   -80,   -80,
      63,   -69,   -80,   -80,   160,   -80,   -80,   100,   -67,   -80,
     -80,   -80,   -80,   -80,    37,   -80,   127,   -80,   130,   -45,
     -80,   -80,   -80,   -34,   -79,   -80,    61,   -80,    62,   -80,
      39,   -80,    56,   -80,   -28,   -80,   -80,   -80,   -80,   147
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -91
static const yytype_int16 yytable[] =
{
      66,    73,   109,    47,    80,    89,     3,    35,   106,   115,
      66,    83,   120,    23,    23,    23,   107,    66,    24,    24,
      24,    66,    66,    85,    47,    36,   134,    18,    37,   137,
     102,   103,     6,     7,    28,    38,    39,    40,    41,    30,
     104,   114,   143,    89,    91,   117,   115,    33,    34,    42,
     119,    66,    43,   100,   101,   102,   103,    44,    45,    74,
      66,    46,    85,    66,   140,   104,    31,    91,   151,   147,
     141,   109,   135,   145,   105,   148,   139,    66,    66,    37,
      66,    39,    40,     6,     7,    71,    38,    39,    40,    41,
       4,    79,     5,     6,     7,   -19,   112,    37,    81,   -36,
      42,   -90,    84,    43,    38,    39,    40,    41,    86,    45,
      90,    91,    46,    39,    40,    41,     6,     7,    42,    66,
       4,    43,     5,     6,     7,   108,    42,    45,   -19,   -36,
      46,     6,     7,   -19,    91,    45,   146,   150,    46,   129,
     130,   131,   132,   133,    92,    93,    94,    95,   136,    96,
      97,    98,    99,   121,   122,   123,   124,   104,   125,   126,
     127,   128,    93,    94,    95,   118,    91,   144,    34,    94,
      95,    17,   116,    25,   113,   142,    87,   149,    72,    88
};

static const yytype_uint8 yycheck[] =
{
      28,    34,    71,    28,    38,    50,     0,    14,    30,    76,
      38,    45,    91,     5,     5,     5,    38,    45,    10,    10,
      10,    49,    50,    48,    49,    32,   105,    14,     4,   108,
      26,    27,     8,     9,    32,    11,    12,    13,    14,    14,
      36,    33,    33,    88,    29,    79,   113,    28,    29,    25,
      35,    79,    28,    24,    25,    26,    27,    33,    34,    32,
      88,    37,    87,    91,    29,    36,    30,    29,   147,    29,
      35,   140,   106,    35,    15,    35,   109,   105,   106,     4,
     108,    12,    13,     8,     9,    34,    11,    12,    13,    14,
       5,    34,     7,     8,     9,    10,    31,     4,    42,    14,
      25,    34,    46,    28,    11,    12,    13,    14,    33,    34,
      28,    29,    37,    12,    13,    14,     8,     9,    25,   147,
       5,    28,     7,     8,     9,    34,    25,    34,     5,    14,
      37,     8,     9,    10,    29,    34,    31,    28,    37,   100,
     101,   102,   103,   104,    16,    17,    18,    19,    14,    20,
      21,    22,    23,    92,    93,    94,    95,    36,    96,    97,
      98,    99,    17,    18,    19,    28,    29,    28,    29,    18,
      19,     8,    78,    13,    74,   112,    49,   140,    31,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    40,    41,     0,     5,     7,     8,     9,    42,    43,
      44,    50,    51,    52,    59,    60,    61,    43,    14,    45,
      46,    47,    48,     5,    10,    53,    54,    55,    32,    64,
      14,    30,    49,    28,    29,    14,    32,     4,    11,    12,
      13,    14,    25,    28,    33,    34,    37,    44,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
      88,    34,    88,    46,    32,    53,    56,    57,    58,    34,
      72,    81,    83,    72,    81,    44,    33,    65,    67,    68,
      28,    29,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    36,    15,    30,    38,    34,    50,
      62,    63,    31,    56,    33,    57,    45,    72,    28,    35,
      73,    75,    75,    75,    75,    77,    77,    77,    77,    79,
      79,    79,    79,    79,    73,    72,    14,    73,    87,    46,
      29,    35,    49,    33,    28,    35,    31,    29,    35,    63,
      28,    73
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 92 "sc.y"
    {
		symtab_node_t *tmp = find_symnode_by_name("main",main_symtab);
		if(tmp == NULL){
			yyerror("Cannot find main func");
		}else{
			codeblock[1] = get_esvar_cnt();
			codeblock[12] = tmp->extra.func.offset - 11;
		}
	}
    break;

  case 3:
#line 102 "sc.y"
    {
		OUT_MAINBEGIN(0,0,0,0);
		OUT_FCALLBEGIN(INT_SIZE);
		OUT_CONSTANT(0);
		OUT_CONSTANT(0);
		OUT_FCALL(0);
		OUT_POPS;
		OUT_MAINEND;
	}
    break;

  case 4:
#line 114 "sc.y"
    {}
    break;

  case 5:
#line 115 "sc.y"
    {}
    break;

  case 6:
#line 118 "sc.y"
    {}
    break;

  case 7:
#line 119 "sc.y"
    {}
    break;

  case 8:
#line 123 "sc.y"
    {
		(yyval.declst_type) = (yyvsp[(2) - (3)].declst_type);
		allocmemory((yyvsp[(2) - (3)].declst_type).psymhead);
		splice_symtab((yyvsp[(2) - (3)].declst_type).psymhead,main_symtab);
	}
    break;

  case 9:
#line 130 "sc.y"
    {
		symtab_head_t *tmpsymhead = init_symtab();
		symtab_node_t *ret;
		if((ret = find_symnode_by_name((yyvsp[(1) - (1)].dec_type).psymnode->name,main_symtab))
			&& ret->scope == current_scope){
			errtext_ptr = (yyvsp[(1) - (1)].dec_type).psymnode->name;
			yyerror("Variable Redefination:");
		}
		insert_symnode((yyvsp[(1) - (1)].dec_type).psymnode,tmpsymhead);
		(yyval.declst_type).psymhead = tmpsymhead;
	}
    break;

  case 10:
#line 141 "sc.y"
    {
		symtab_node_t *ret;
		if((ret = find_symnode_by_name((yyvsp[(3) - (3)].dec_type).psymnode->name,main_symtab))
			&& ret->scope == current_scope
			|| find_symnode_by_name((yyvsp[(3) - (3)].dec_type).psymnode->name,(yyvsp[(1) - (3)].declst_type).psymhead)){
			errtext_ptr = (yyvsp[(3) - (3)].dec_type).psymnode->name;
			yyerror("Variable Redefination:");
		}
		insert_symnode((yyvsp[(3) - (3)].dec_type).psymnode,(yyvsp[(1) - (3)].declst_type).psymhead);
		(yyval.declst_type) = (yyvsp[(1) - (3)].declst_type);
	}
    break;

  case 11:
#line 154 "sc.y"
    {
		(yyval.dec_type) = (yyvsp[(1) - (1)].dec_type);
	}
    break;

  case 12:
#line 159 "sc.y"
    {
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = (yyvsp[(1) - (1)].id_val);
		tmp->scope = current_scope;
		tmp->type = TYPE_VAR;
		tmp->extra.var.vartype = current_type;
		fprintf(stderr,"[DEBUG] set ID %s type to:%x\n",(yyvsp[(1) - (1)].id_val),current_type);
		(yyval.dec_type).psymnode = tmp;
	}
    break;

  case 13:
#line 168 "sc.y"
    {
		(yyval.dec_type) = (yyvsp[(1) - (1)].dec_type);
	}
    break;

  case 14:
#line 173 "sc.y"
    {
		symtab_node_t *tmp = get_new_symnode();
                tmp->name = (yyvsp[(1) - (2)].id_val);
                tmp->scope = current_scope;
                tmp->type = TYPE_VAR;
                tmp->extra.var.vartype = (yyvsp[(2) - (2)].dec_type).psymnode;
		fprintf(stderr,"[DEBUG] set ID %s type to:%x\n",(yyvsp[(1) - (2)].id_val),(yyvsp[(2) - (2)].dec_type).psymnode);
                (yyval.dec_type).psymnode = tmp;
        }
    break;

  case 15:
#line 184 "sc.y"
    {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->scope = current_scope;
                tmp->type = TYPE_ARRAY;
		tmp->width = (yyvsp[(2) - (3)].num_val) * current_type->width;
                tmp->extra.array.elemtype = current_type;
		tmp->extra.array.count = (yyvsp[(2) - (3)].num_val);
                (yyval.dec_type).psymnode = tmp;
	}
    break;

  case 16:
#line 194 "sc.y"
    {
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->scope = current_scope;
                tmp->type = TYPE_ARRAY;
		tmp->width = (yyvsp[(2) - (4)].num_val) * (yyvsp[(4) - (4)].dec_type).psymnode->width;
                tmp->extra.array.elemtype = (yyvsp[(4) - (4)].dec_type).psymnode;
		tmp->extra.array.count = (yyvsp[(2) - (4)].num_val);
                (yyval.dec_type).psymnode = tmp;
	}
    break;

  case 17:
#line 206 "sc.y"
    {
		current_type = (yyvsp[(1) - (1)].dec_type).psymnode;
		fprintf(stderr,"[DEBUG] set current_type to:%x\n",(yyvsp[(1) - (1)].dec_type).psymnode);
	}
    break;

  case 18:
#line 212 "sc.y"
    {
		(yyval.dec_type) = (yyvsp[(2) - (2)].dec_type);
	}
    break;

  case 19:
#line 217 "sc.y"
    {(yyval.notype)=current_scope;}
    break;

  case 20:
#line 218 "sc.y"
    {(yyval.notype)=current_scope;}
    break;

  case 21:
#line 219 "sc.y"
    {(yyval.notype)=0;}
    break;

  case 22:
#line 222 "sc.y"
    {
		(yyval.dec_type).psymnode = INT_TYPE_POINTER;
	}
    break;

  case 23:
#line 225 "sc.y"
    {
		(yyval.dec_type) = (yyvsp[(1) - (1)].dec_type);
	}
    break;

  case 24:
#line 230 "sc.y"
    {
		(yyval.dec_type) = (yyvsp[(1) - (1)].dec_type);
	}
    break;

  case 25:
#line 233 "sc.y"
    {
		symtab_node_t *tmp = find_symnode_by_name((yyvsp[(2) - (2)].id_val),main_symtab);
		if(tmp == NULL){
			errtext_ptr = (yyvsp[(2) - (2)].id_val);
                        yyerror("Cannot find struct named ");
			(yyval.dec_type).psymnode = INT_TYPE_POINTER;
		}else if(tmp->type != TYPE_STRUCT){
			errtext_ptr = (yyvsp[(2) - (2)].id_val);
			yyerror("The ID is not a struct: ");
			(yyval.dec_type).psymnode = INT_TYPE_POINTER;
		}else{
			(yyval.dec_type).psymnode = tmp;
		}
	}
    break;

  case 26:
#line 249 "sc.y"
    {
		allocmemberoffset((yyvsp[(4) - (5)].declst_type).psymhead);
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = (yyvsp[(2) - (5)].id_val);
		tmp->type = TYPE_STRUCT;
		tmp->scope = current_scope;
		tmp->extra.struc.elemlist = (yyvsp[(4) - (5)].declst_type).psymhead;
		tmp->width = sum_all_width(tmp->extra.struc.elemlist);
		(yyval.dec_type).psymnode = tmp;
	}
    break;

  case 27:
#line 259 "sc.y"
    {
		allocmemberoffset((yyvsp[(3) - (4)].declst_type).psymhead);
                symtab_node_t *tmp = get_new_symnode();
                tmp->name = "czj";
                tmp->type = TYPE_STRUCT;
                tmp->scope = current_scope;
                tmp->extra.struc.elemlist = (yyvsp[(3) - (4)].declst_type).psymhead;
		fprintf(stderr,"[DEBUG]Struct NULL get elemlist:%x\n",(yyvsp[(3) - (4)].declst_type).psymhead);
		tmp->width = sum_all_width(tmp->extra.struc.elemlist);
                (yyval.dec_type).psymnode = tmp;
        }
    break;

  case 28:
#line 272 "sc.y"
    {
		(yyval.declst_type) = (yyvsp[(1) - (1)].declst_type);
	}
    break;

  case 29:
#line 275 "sc.y"
    {
		splice_symtab((yyvsp[(2) - (2)].declst_type).psymhead,(yyvsp[(1) - (2)].declst_type).psymhead);
		(yyval.declst_type) = (yyvsp[(1) - (2)].declst_type);
	}
    break;

  case 30:
#line 281 "sc.y"
    {
		(yyval.declst_type) = (yyvsp[(2) - (3)].declst_type);
	}
    break;

  case 31:
#line 286 "sc.y"
    {
		current_type = (yyvsp[(1) - (1)].dec_type).psymnode;
	}
    break;

  case 32:
#line 292 "sc.y"
    {
	        deleted_symtab = main_symtab->next;
		split_symtab(pop_symstack(main_symstack),deleted_symtab);
		OUT_CONSTANT(0);
		OUT_RETURNF(current_func->extra.func.paramlength,
                                current_func->extra.func.rettype->width);
		codeblock[current_func->extra.func.offset+1] = get_locvar_cnt();
	}
    break;

  case 33:
#line 302 "sc.y"
    {
		init_locpool();
		symtab_node_t *tmp = get_new_symnode();
		tmp->name = (yyvsp[(2) - (5)].id_val);
		fprintf(stderr,"[DEBUG] Got func :%s\n",(yyvsp[(2) - (5)].id_val));
		tmp->type = TYPE_FUNC;
		tmp->scope = SCOPE_GLOBAL;
		tmp->width = 0;
		tmp->extra.func.rettype = (yyvsp[(1) - (5)].dec_type).psymnode;
		tmp->extra.func.paramlength = sum_all_width((yyvsp[(4) - (5)].declst_type).psymhead);
		insert_symnode(tmp,main_symtab);
		allocfuncparam((yyvsp[(4) - (5)].declst_type).psymhead);
		push_symstack(main_symstack, main_symtab->next);
		splice_symtab((yyvsp[(4) - (5)].declst_type).psymhead,main_symtab);
		free((yyvsp[(4) - (5)].declst_type).psymhead);
		tmp->extra.func.offset = current_pc;

		OUT_FBEGIN(0,0,lineno);

		current_func=tmp;
		(yyval.dec_type).psymnode = tmp;
	}
    break;

  case 34:
#line 326 "sc.y"
    {(yyval.dec_type).psymnode=INT_TYPE_POINTER;}
    break;

  case 35:
#line 327 "sc.y"
    {(yyval.dec_type).psymnode=CHAR_TYPE_POINTER;}
    break;

  case 36:
#line 328 "sc.y"
    {(yyval.dec_type).psymnode=INT_TYPE_POINTER;}
    break;

  case 37:
#line 331 "sc.y"
    {
		symtab_head_t *tmpsymhead = init_symtab();
		insert_symnode((yyvsp[(1) - (1)].dec_type).psymnode,tmpsymhead);
		(yyval.declst_type).psymhead = tmpsymhead;
	}
    break;

  case 38:
#line 336 "sc.y"
    {
		insert_symnode((yyvsp[(3) - (3)].dec_type).psymnode,(yyvsp[(1) - (3)].declst_type).psymhead);
                (yyval.declst_type) = (yyvsp[(1) - (3)].declst_type);
        }
    break;

  case 39:
#line 342 "sc.y"
    {
		(yyval.dec_type) = (yyvsp[(2) - (2)].dec_type);
	}
    break;

  case 40:
#line 348 "sc.y"
    {(yyval.stat_type)=(yyvsp[(2) - (3)].stat_type);}
    break;

  case 41:
#line 349 "sc.y"
    {(yyval.stat_type)=0;}
    break;

  case 42:
#line 352 "sc.y"
    {}
    break;

  case 43:
#line 353 "sc.y"
    {}
    break;

  case 44:
#line 356 "sc.y"
    {(yyval.stat_type)=0;}
    break;

  case 45:
#line 357 "sc.y"
    {(yyval.stat_type)=(yyvsp[(1) - (1)].stat_type);}
    break;

  case 46:
#line 358 "sc.y"
    {(yyval.stat_type)+=(yyvsp[(1) - (2)].stat_type);}
    break;

  case 47:
#line 359 "sc.y"
    {(yyval.stat_type)+=(yyvsp[(1) - (2)].stat_type);}
    break;

  case 53:
#line 371 "sc.y"
    {
		OUT_LOCVAR_VALUE((yyvsp[(2) - (3)].exp_type)->extra.var.offset);
		OUT_RETURNF(current_func->extra.func.paramlength,
				current_func->extra.func.rettype->width);
	}
    break;

  case 54:
#line 378 "sc.y"
    {(yyval.stat_type)=0;}
    break;

  case 55:
#line 379 "sc.y"
    {(yyval.stat_type)=0;}
    break;

  case 56:
#line 382 "sc.y"
    {
		OUT_LOCVAR_VALUE((yyvsp[(3) - (5)].exp_type)->extra.var.offset);
		fprintf(stderr,"[DEBUG] print offset:%d\n",(yyvsp[(3) - (5)].exp_type)->extra.var.offset);
		OUT_WRITEINTX;
	}
    break;

  case 57:
#line 389 "sc.y"
    {
		(yyval.exp_type)=(yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 58:
#line 392 "sc.y"
    {
		(yyval.exp_type)=(yyvsp[(3) - (3)].exp_type);
	}
    break;

  case 59:
#line 397 "sc.y"
    {
		(yyval.exp_type)=(yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 60:
#line 400 "sc.y"
    {
		if((yyvsp[(1) - (3)].exexp_type).offsetvar != NULL){
			fprintf(stderr,"[DEBUG] Assign from %d to pointer %d width %d\n",
					(yyvsp[(3) - (3)].exp_type)->extra.var.offset,(yyvsp[(1) - (3)].exexp_type).offsetvar->extra.var.offset,(yyvsp[(1) - (3)].exexp_type).retvar->extra.var.vartype->width);
			OUT_LOCVAR((yyvsp[(1) - (3)].exexp_type).offsetvar->extra.var.offset);
			OUT_VALUE;
		}else{
			OUT_LOCVAR((yyvsp[(1) - (3)].exexp_type).retvar->extra.var.offset);
			fprintf(stderr,"[DEBUG] Assign from %d to %d width %d\n",(yyvsp[(3) - (3)].exp_type)->extra.var.offset,(yyvsp[(1) - (3)].exexp_type).retvar->extra.var.offset,(yyvsp[(1) - (3)].exexp_type).retvar->extra.var.vartype->width);
		}
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_ASSIGNL((yyvsp[(1) - (3)].exexp_type).retvar->extra.var.vartype->width);
		(yyval.exp_type)=(yyvsp[(3) - (3)].exp_type);
	}
    break;

  case 61:
#line 416 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 62:
#line 421 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 63:
#line 424 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_ORX;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 64:
#line 433 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_ANDX;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 65:
#line 442 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_EQUAL;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 66:
#line 451 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_EQUAL;
		OUT_NOTX;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 67:
#line 463 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 68:
#line 468 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 69:
#line 471 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_GREATER;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 70:
#line 480 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_LESS;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 71:
#line 489 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_GREATEREQUAL;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 72:
#line 498 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_LESSEQUAL;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 73:
#line 509 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 74:
#line 514 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 75:
#line 517 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_ADD;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 76:
#line 526 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_MINUS;
		OUT_ADD;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 77:
#line 536 "sc.y"
    {		
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_MULTIPLY;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 78:
#line 545 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_DIVIDE;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 79:
#line 554 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exp_type)->extra.var.offset);
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
		OUT_MODULO;
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 80:
#line 565 "sc.y"
    {
		(yyval.exp_type) = (yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 81:
#line 570 "sc.y"
    {
		(yyval.exp_type)=(yyvsp[(1) - (1)].exp_type);
	}
    break;

  case 82:
#line 573 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
                OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
                OUT_LOCVAR_VALUE((yyvsp[(2) - (2)].exp_type)->extra.var.offset);
                OUT_MINUS;
                OUT_ASSIGN;
		OUT_POPS;
        }
    break;

  case 83:
#line 581 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
                OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
                OUT_LOCVAR_VALUE((yyvsp[(2) - (2)].exp_type)->extra.var.offset);
                OUT_NOTX;
                OUT_ASSIGN;
                OUT_POPS;
	}
    break;

  case 84:
#line 591 "sc.y"
    {
		(yyval.exp_type) = alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exp_type)->extra.var.offset);
		if((yyvsp[(1) - (1)].exexp_type).offsetvar != NULL){
			fprintf(stderr,"[DEBUG] unarray offset:%d\n",(yyvsp[(1) - (1)].exexp_type).offsetvar->extra.var.offset);
			OUT_LOCVAR_VALUE((yyvsp[(1) - (1)].exexp_type).offsetvar->extra.var.offset);
			OUT_VALUE;
		}else{
			fprintf(stderr,"[DEBUG] unarray int offset:%d\n",(yyvsp[(1) - (1)].exexp_type).retvar->extra.var.offset);
			if((yyvsp[(1) - (1)].exexp_type).retvar->scope == SCOPE_GLOBAL){
				OUT_ESVAR_VALUE((yyvsp[(1) - (1)].exexp_type).retvar->extra.var.offset);
			}else{
				OUT_LOCVAR_VALUE((yyvsp[(1) - (1)].exexp_type).retvar->extra.var.offset);
			}
		}
		OUT_ASSIGN;
		OUT_POPS;
	}
    break;

  case 85:
#line 611 "sc.y"
    {
		(yyval.exexp_type) = (yyvsp[(1) - (1)].exexp_type);
	}
    break;

  case 86:
#line 616 "sc.y"
    {
		(yyval.exexp_type) = (yyvsp[(1) - (1)].exexp_type);
	}
    break;

  case 87:
#line 619 "sc.y"
    {
		if((yyvsp[(1) - (4)].exexp_type).retvar->extra.var.vartype->type != TYPE_ARRAY){
			errtext_ptr = (yyvsp[(1) - (4)].exexp_type).retvar->name;
			yyerror("Can't convert to array");
			printf("its type is %d\n",(yyvsp[(1) - (4)].exexp_type).retvar->extra.var.vartype->type);
			(yyval.exexp_type) = (yyvsp[(1) - (4)].exexp_type);
		}else{
			symtab_node_t *tmp = (yyvsp[(1) - (4)].exexp_type).retvar;
			tmp->extra.var.vartype = tmp->extra.var.vartype->extra.array.elemtype;
			OUT_LOCVAR((yyvsp[(1) - (4)].exexp_type).offsetvar->extra.var.offset);
			OUT_LOCVAR_VALUE((yyvsp[(1) - (4)].exexp_type).offsetvar->extra.var.offset);
			OUT_LOCVAR_VALUE((yyvsp[(3) - (4)].exp_type)->extra.var.offset);
			OUT_INDEX(tmp->extra.var.vartype->width,lineno);
			OUT_ASSIGN;
			OUT_POPS;
			(yyval.exexp_type).retvar = tmp;
			(yyval.exexp_type).offsetvar = (yyvsp[(1) - (4)].exexp_type).offsetvar;
		}
		/**/
	}
    break;

  case 88:
#line 639 "sc.y"
    {
		if((yyvsp[(1) - (3)].exexp_type).retvar->extra.var.vartype->type != TYPE_STRUCT){
			errtext_ptr = (yyvsp[(1) - (3)].exexp_type).retvar->name;
                        yyerror("Can't convert to struct:");
                        (yyval.exexp_type) = (yyvsp[(1) - (3)].exexp_type);
		}else{
			symtab_node_t *tmp = (yyvsp[(1) - (3)].exexp_type).retvar;
			tmp = find_symnode_by_name((yyvsp[(3) - (3)].id_val),tmp->extra.var.vartype->extra.struc.elemlist);
			if(tmp == NULL){
				errtext_ptr = (yyvsp[(3) - (3)].id_val);
				yyerror("No such member variable:");
				(yyval.exexp_type) = (yyvsp[(1) - (3)].exexp_type);
			}else{
				fprintf(stderr,"[DEBUG] +offset %d\n",tmp->extra.var.offset);
                        	OUT_LOCVAR((yyvsp[(1) - (3)].exexp_type).offsetvar->extra.var.offset);
                        	OUT_LOCVAR_VALUE((yyvsp[(1) - (3)].exexp_type).offsetvar->extra.var.offset);
                        	OUT_FIELD(tmp->extra.var.offset);
                        	OUT_ASSIGN;
                        	OUT_POPS;
				memcpy((yyvsp[(1) - (3)].exexp_type).retvar,tmp,sizeof(symtab_node_t));
                        	(yyval.exexp_type).retvar = (yyvsp[(1) - (3)].exexp_type).retvar;
                        	(yyval.exexp_type).offsetvar = (yyvsp[(1) - (3)].exexp_type).offsetvar;
			}
		}
		/*用新建一个symtab_node_t来保存加点后的变量*/
	}
    break;

  case 89:
#line 665 "sc.y"
    {
		int disp = (yyvsp[(1) - (4)].exexp_type).offsetvar->extra.func.offset-current_pc;
		OUT_FCALL(disp);
		OUT_ASSIGN;
		OUT_POPS;
		(yyval.exexp_type).retvar=(yyvsp[(1) - (4)].exexp_type).retvar;
		(yyval.exexp_type).offsetvar=NULL;
	}
    break;

  case 90:
#line 675 "sc.y"
    {
		(yyval.exexp_type).retvar=alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		OUT_LOCVAR((yyval.exexp_type).retvar->extra.var.offset);
		
		symtab_node_t *tmp = find_symnode_by_name((yyvsp[(1) - (1)].id_val),main_symtab);
                if(tmp == NULL){
                        errtext_ptr = (yyvsp[(1) - (1)].id_val);
                        yyerror("Undefined Function");
		}else{
			OUT_FCALLBEGIN(tmp->extra.func.rettype->width);
		}
		(yyval.exexp_type).offsetvar=tmp;
	}
    break;

  case 91:
#line 690 "sc.y"
    {
		symtab_node_t *tmp = find_symnode_by_name((yyvsp[(1) - (1)].id_val),main_symtab);
		if(tmp == NULL){
			errtext_ptr = (yyvsp[(1) - (1)].id_val);
			yyerror("Undefined Variable");
			tmp=alloc_loc_and_insert(INT_TYPE_POINTER,(yyvsp[(1) - (1)].id_val));
			(yyval.exexp_type).retvar = tmp;
			(yyval.exexp_type).offsetvar = NULL;
		}else{
			(yyval.exexp_type).retvar = get_new_symnode();
                	memcpy((yyval.exexp_type).retvar,tmp,sizeof(symtab_node_t));
			if((yyval.exexp_type).retvar->extra.var.vartype->type == TYPE_INT ||
				(yyval.exexp_type).retvar->extra.var.vartype->type == TYPE_CHAR){
				(yyval.exexp_type).offsetvar = NULL;
			}else{
				(yyval.exexp_type).offsetvar = alloc_loc_and_insert(INT_TYPE_POINTER,"czj");
				fprintf(stderr,"[DEBUG] base offset of %s : %d\n",(yyvsp[(1) - (1)].id_val),(yyval.exexp_type).retvar->extra.var.offset);
				OUT_LOCVAR((yyval.exexp_type).offsetvar->extra.var.offset);
				OUT_LOCVAR((yyval.exexp_type).retvar->extra.var.offset);
				OUT_ASSIGN;
				OUT_POPS;
			}
		}
	}
    break;

  case 92:
#line 715 "sc.y"
    {
		symtab_node_t *tmp=alloc_loc_and_insert(INT_TYPE_POINTER,NULL);
		fprintf(stderr,"[DEBUG] Find constant offset %d value %d\n",tmp->extra.var.offset,(yyvsp[(1) - (1)].num_val));
		OUT_LOCVAR(tmp->extra.var.offset);
		OUT_CONSTANT((yyvsp[(1) - (1)].num_val));
		OUT_ASSIGN;
		OUT_POPS;
		(yyval.exexp_type).retvar=get_new_symnode();
		memcpy((yyval.exexp_type).retvar,tmp,sizeof(symtab_node_t));
		(yyval.exexp_type).offsetvar=NULL;
	}
    break;

  case 93:
#line 726 "sc.y"
    {
		(yyval.exexp_type).retvar=(yyvsp[(2) - (3)].exp_type);
		(yyval.exexp_type).offsetvar=NULL;
	}
    break;

  case 94:
#line 732 "sc.y"
    {;}
    break;

  case 95:
#line 733 "sc.y"
    {
		OUT_LOCVAR_VALUE((yyvsp[(1) - (1)].exp_type)->extra.var.offset);
	}
    break;

  case 96:
#line 736 "sc.y"
    {
		OUT_LOCVAR_VALUE((yyvsp[(3) - (3)].exp_type)->extra.var.offset);
	}
    break;

  case 97:
#line 741 "sc.y"
    {
		(yyval.num_val)=(yyvsp[(1) - (1)].num_val);
	}
    break;

  case 98:
#line 744 "sc.y"
    {
		(yyval.num_val)=(yyvsp[(1) - (1)].num_val);
	}
    break;


/* Line 1267 of yacc.c.  */
#line 2459 "y.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 748 "sc.y"

extern FILE *yyin;
extern char *yytext;
void yyerror(const char *msg)
{
	error_count++;
	printf("ERROR[%d]:line %d,%s:%s.\n",error_count,lineno,msg,errtext_ptr);
}
int main(int argc, char **argv)
{
	FILE *compile_out;;
	if(argc > 1){
		yyin = fopen( argv[1], "r" );
	}
	else{
		yyin = stdin;
	}

	if(argc > 2){
		compile_out = fopen( argv[2], "w" );
	}
	else{
		compile_out = stdout;
	}
	lineno=1;
        init_all();
	yyparse();
	output_code(compile_out);
	return 0;
}

