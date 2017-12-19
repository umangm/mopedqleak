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

/* Substitute the variable and function names.  */
#define yyparse irparse
#define yylex   irlex
#define yyerror irerror
#define yylval  irlval
#define yychar  irchar
#define yydebug irdebug
#define yynerrs irnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DEFINE = 258,
     IDENT = 259,
     BVAR = 260,
     NUMBER = 261,
     FLOAT = 262,
     DEFAULT_INT_BITS = 263,
     DEFAULT_SIGNED_INT_BITS = 264,
     BOOL = 265,
     INT = 266,
     SGNINT = 267,
     ENUM = 268,
     STRUCT = 269,
     INIT = 270,
     ARROW = 271,
     IF = 272,
     FI = 273,
     ELSE = 274,
     DO = 275,
     OD = 276,
     PCHOICE = 277,
     CHOICEP = 278,
     DOUBLECOLON = 279,
     CONDARROW = 280,
     PDS_LGC_AND = 281,
     PDS_LGC_OR = 282,
     PDS_EQV = 283,
     PDS_LGC_XOR = 284,
     PDS_LGC_NOT = 285,
     PDS_FORALL = 286,
     PDS_EXISTS = 287,
     TOK_TRUE = 288,
     TOK_FALSE = 289,
     PDS_PLUS = 290,
     PDS_MINUS = 291,
     PDS_MULT = 292,
     PDS_DIV = 293,
     PDS_SHL = 294,
     PDS_SHR = 295,
     PDS_AND = 296,
     PDS_OR = 297,
     PDS_XOR = 298,
     QVAR = 299,
     PDS_LE = 300,
     PDS_CMPEQ = 301,
     PDS_NE = 302,
     PDS_GE = 303,
     PDS_EQ = 304,
     PRIME = 305,
     BREAK = 306,
     RETURN = 307,
     SKIP = 308,
     MODULE = 309,
     VOID = 310,
     LABEL = 311,
     UNDEF = 312,
     FORK = 313,
     SHARED = 314
   };
#endif
/* Tokens.  */
#define DEFINE 258
#define IDENT 259
#define BVAR 260
#define NUMBER 261
#define FLOAT 262
#define DEFAULT_INT_BITS 263
#define DEFAULT_SIGNED_INT_BITS 264
#define BOOL 265
#define INT 266
#define SGNINT 267
#define ENUM 268
#define STRUCT 269
#define INIT 270
#define ARROW 271
#define IF 272
#define FI 273
#define ELSE 274
#define DO 275
#define OD 276
#define PCHOICE 277
#define CHOICEP 278
#define DOUBLECOLON 279
#define CONDARROW 280
#define PDS_LGC_AND 281
#define PDS_LGC_OR 282
#define PDS_EQV 283
#define PDS_LGC_XOR 284
#define PDS_LGC_NOT 285
#define PDS_FORALL 286
#define PDS_EXISTS 287
#define TOK_TRUE 288
#define TOK_FALSE 289
#define PDS_PLUS 290
#define PDS_MINUS 291
#define PDS_MULT 292
#define PDS_DIV 293
#define PDS_SHL 294
#define PDS_SHR 295
#define PDS_AND 296
#define PDS_OR 297
#define PDS_XOR 298
#define QVAR 299
#define PDS_LE 300
#define PDS_CMPEQ 301
#define PDS_NE 302
#define PDS_GE 303
#define PDS_EQ 304
#define PRIME 305
#define BREAK 306
#define RETURN 307
#define SKIP 308
#define MODULE 309
#define VOID 310
#define LABEL 311
#define UNDEF 312
#define FORK 313
#define SHARED 314




/* Copy the first part of user declarations.  */
#line 1 "parse/irParse.y"


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "irInt.h"

int irlinenumber = 1;
int int_bits = 0;
int sgnint_bits = 0;
IrModule current_module = NULL;
IrModule called_module = NULL;
wIdent last_var = 0;
int shared_stmt = 0;
int else_cnt = 0;
int main_found = 0;

int irlex();
void irerror (char*);



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
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
#line 24 "parse/irParse.y"
{
	char *string;
	int integer;
	float floating_point;
	wIdent name;
	IrDim y_dim;
	IrQvar qvar;
	IrVar y_var;
	IrEnum y_enum;
	IrStruct y_struct;
	IrVarList y_varlist;
	IrName y_name;
	IrFnode y_fnode;
	IrStmt y_stmt;
	IrRule y_rule;
	IrIfdo y_ifdo;
	IrPchoice y_pchoice;
	IrExprList y_exprlist;
	IrModule y_module;
}
/* Line 193 of yacc.c.  */
#line 265 "parse/irParse.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 278 "parse/irParse.c"

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
# if defined YYENABLE_NLS && YYENABLE_NLS
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
#define YYLAST   677

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  72
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  60
/* YYNRULES -- Number of rules.  */
#define YYNRULES  178
/* YYNRULES -- Number of states.  */
#define YYNSTATES  367

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   314

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      60,    61,     2,     2,    65,     2,    71,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    68,    62,
      69,     2,    70,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    66,     2,    67,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    63,     2,    64,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     7,     8,    13,    18,    23,    24,    27,
      31,    34,    37,    45,    49,    53,    57,    62,    67,    72,
      74,    79,    81,    83,    87,    91,    92,    94,    95,    97,
     100,   104,   110,   111,   115,   122,   129,   131,   135,   137,
     140,   141,   145,   146,   149,   152,   153,   156,   160,   162,
     166,   169,   172,   175,   178,   181,   182,   184,   195,   205,
     214,   215,   217,   221,   225,   229,   238,   243,   244,   247,
     252,   256,   260,   264,   268,   272,   276,   279,   283,   287,
     289,   291,   293,   295,   302,   306,   310,   314,   318,   322,
     326,   330,   334,   338,   342,   346,   350,   354,   358,   362,
     366,   368,   370,   372,   374,   378,   380,   385,   393,   395,
     398,   402,   404,   408,   410,   415,   423,   425,   428,   432,
     436,   440,   444,   448,   452,   456,   460,   464,   468,   472,
     474,   476,   478,   481,   486,   491,   493,   495,   498,   501,
     506,   507,   509,   511,   515,   517,   519,   521,   524,   527,
     528,   531,   533,   537,   541,   545,   549,   553,   557,   561,
     565,   571,   578,   579,   582,   584,   587,   591,   595,   599,
     603,   604,   606,   608,   612,   615,   618,   621,   625
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int16 yyrhs[] =
{
      73,     0,    -1,    74,    75,    91,    -1,    -1,    74,     3,
       4,   114,    -1,    74,     3,     8,   114,    -1,    74,     3,
       9,   114,    -1,    -1,    75,    77,    -1,    75,    59,    77,
      -1,    75,    86,    -1,    75,    76,    -1,    54,   128,     4,
      60,   129,    61,    62,    -1,    10,    80,    62,    -1,    11,
      80,    62,    -1,    12,    80,    62,    -1,    13,    78,    80,
      62,    -1,    14,    79,    80,    62,    -1,    82,    63,    87,
      64,    -1,     4,    -1,    82,    63,    88,    64,    -1,     4,
      -1,    81,    -1,    80,    65,    81,    -1,     4,    83,    85,
      -1,    -1,     4,    -1,    -1,    84,    -1,    84,    84,    -1,
      66,   114,    67,    -1,    66,   114,    65,   114,    67,    -1,
      -1,    60,   114,    61,    -1,    13,    82,    63,    87,    64,
      62,    -1,    14,    82,    63,    88,    64,    62,    -1,     4,
      -1,     4,    65,    87,    -1,    77,    -1,    88,    77,    -1,
      -1,    60,   104,    61,    -1,    -1,    92,    90,    -1,   125,
      90,    -1,    -1,   125,    91,    -1,     4,    68,    93,    -1,
      93,    -1,    95,    96,    89,    -1,    97,    94,    -1,    98,
      94,    -1,    99,    94,    -1,   116,    62,    -1,   123,    62,
      -1,    -1,    62,    -1,     4,    69,     4,    70,    16,     4,
      69,     4,     4,    70,    -1,     4,    69,     4,    70,    16,
       4,    69,     4,    70,    -1,     4,    69,     4,    70,    16,
       4,    69,    70,    -1,    -1,    56,    -1,    17,   100,    18,
      -1,    20,   101,    21,    -1,    22,   102,    23,    -1,    24,
     104,    25,    90,    24,    19,    25,    90,    -1,    24,   104,
      25,    90,    -1,    -1,   103,   102,    -1,    24,     7,    25,
      90,    -1,    60,   104,    61,    -1,   104,    26,   104,    -1,
     104,    27,   104,    -1,   104,    29,   104,    -1,   104,    28,
     104,    -1,   104,    46,   104,    -1,    30,   104,    -1,    31,
     105,   104,    -1,    32,   105,   104,    -1,   111,    -1,   106,
      -1,    33,    -1,    34,    -1,     4,    60,   114,    65,   114,
      61,    -1,   107,    69,   107,    -1,   107,    45,   107,    -1,
     107,    46,   107,    -1,   107,    47,   107,    -1,   107,    48,
     107,    -1,   107,    70,   107,    -1,    60,   107,    61,    -1,
     107,    35,   107,    -1,   107,    36,   107,    -1,   107,    37,
     107,    -1,   107,    38,   107,    -1,   107,    39,   107,    -1,
     107,    40,   107,    -1,   107,    41,   107,    -1,   107,    42,
     107,    -1,   107,    43,   107,    -1,   108,    -1,    44,    -1,
       6,    -1,   109,    -1,   109,    71,   109,    -1,   110,    -1,
     110,    66,   107,    67,    -1,   110,    66,   107,    67,    66,
     107,    67,    -1,     4,    -1,     4,    50,    -1,     4,    50,
      50,    -1,   112,    -1,   109,    71,   112,    -1,   113,    -1,
     113,    66,   107,    67,    -1,   113,    66,   107,    67,    66,
     107,    67,    -1,     5,    -1,     5,    50,    -1,     5,    50,
      50,    -1,   114,    35,   114,    -1,   114,    36,   114,    -1,
     114,    37,   114,    -1,   114,    38,   114,    -1,   114,    39,
     114,    -1,   114,    40,   114,    -1,   114,    41,   114,    -1,
     114,    42,   114,    -1,   114,    43,   114,    -1,    60,   114,
      61,    -1,     6,    -1,   104,    -1,   107,    -1,   117,   122,
      -1,   108,    49,   117,   122,    -1,   111,    49,   117,   122,
      -1,   121,    -1,    51,    -1,    53,    89,    -1,    58,   117,
      -1,     4,    60,   118,    61,    -1,    -1,   119,    -1,   120,
      -1,   120,    65,   119,    -1,   115,    -1,    57,    -1,    52,
      -1,    52,   104,    -1,    52,   107,    -1,    -1,    65,   123,
      -1,   124,    -1,   124,    65,   123,    -1,   108,    49,   107,
      -1,   111,    49,   104,    -1,   108,    49,    57,    -1,   111,
      49,    57,    -1,   108,    47,   107,    -1,    31,   105,   124,
      -1,    32,   105,   124,    -1,   126,    63,   127,    90,    64,
      -1,    54,   128,     4,    60,   129,    61,    -1,    -1,   127,
      77,    -1,    55,    -1,    10,    83,    -1,    11,    83,    85,
      -1,    12,    83,    85,    -1,    13,     4,    83,    -1,    14,
       4,    83,    -1,    -1,   130,    -1,   131,    -1,   131,    65,
     130,    -1,    10,    81,    -1,    11,    81,    -1,    12,    81,
      -1,    13,     4,    81,    -1,    14,     4,    81,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   143,   143,   159,   160,   164,   167,   172,   173,   179,
     192,   193,   196,   203,   210,   220,   231,   240,   256,   262,
     271,   277,   286,   291,   298,   303,   304,   307,   308,   309,
     315,   319,   326,   327,   333,   337,   343,   346,   351,   356,
     395,   396,   399,   400,   418,   440,   441,   463,   468,   473,
     479,   482,   485,   488,   489,   499,   500,   503,   513,   516,
     521,   522,   525,   534,   543,   569,   591,   630,   633,   639,
     650,   651,   654,   657,   660,   663,   666,   669,   675,   681,
     682,   683,   686,   691,   703,   706,   709,   712,   715,   718,
     723,   726,   729,   732,   735,   738,   741,   744,   747,   750,
     753,   756,   759,   764,   784,   821,   824,   828,   835,   839,
     843,   849,   869,   905,   908,   912,   919,   922,   925,   930,
     931,   932,   933,   939,   940,   941,   942,   943,   944,   945,
     948,   949,   952,   961,   979,   997,  1008,  1011,  1014,  1049,
    1063,  1064,  1067,  1070,  1075,  1078,  1083,  1088,  1097,  1108,
    1111,  1116,  1119,  1128,  1214,  1235,  1288,  1293,  1298,  1305,
    1314,  1349,  1373,  1374,  1385,  1388,  1392,  1399,  1407,  1420,
    1441,  1442,  1445,  1448,  1453,  1459,  1471,  1484,  1498
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DEFINE", "IDENT", "BVAR", "NUMBER",
  "FLOAT", "DEFAULT_INT_BITS", "DEFAULT_SIGNED_INT_BITS", "BOOL", "INT",
  "SGNINT", "ENUM", "STRUCT", "INIT", "ARROW", "IF", "FI", "ELSE", "DO",
  "OD", "PCHOICE", "CHOICEP", "DOUBLECOLON", "CONDARROW", "PDS_LGC_AND",
  "PDS_LGC_OR", "PDS_EQV", "PDS_LGC_XOR", "PDS_LGC_NOT", "PDS_FORALL",
  "PDS_EXISTS", "TOK_TRUE", "TOK_FALSE", "PDS_PLUS", "PDS_MINUS",
  "PDS_MULT", "PDS_DIV", "PDS_SHL", "PDS_SHR", "PDS_AND", "PDS_OR",
  "PDS_XOR", "QVAR", "PDS_LE", "PDS_CMPEQ", "PDS_NE", "PDS_GE", "PDS_EQ",
  "PRIME", "BREAK", "RETURN", "SKIP", "MODULE", "VOID", "LABEL", "UNDEF",
  "FORK", "SHARED", "'('", "')'", "';'", "'{'", "'}'", "','", "'['", "']'",
  "':'", "'<'", "'>'", "'.'", "$accept", "automaton", "defines",
  "gbldecls", "moduledecl", "vardecl", "enumname", "structname", "varlist",
  "varident", "optident", "optdim", "dim", "optbit", "typedecl",
  "enumlist", "structtypelist", "optboolexpr", "stmtlist", "modulelist",
  "lblstmt", "stmt", "optsemicolon", "rawtrans", "label", "ifstmt",
  "dostmt", "pchoicestmt", "ifclnstmtlist", "doclnstmtlist", "pstmtlist",
  "pstmt", "boolexpr", "quant", "intcomp", "intexpr", "structvaroptidx",
  "varoptidx", "varoptprime", "structbvaroptidx", "bvaroptidx",
  "bvaroptprime", "cnstexpr", "expr", "action", "callstmt", "args",
  "argslist", "exproptundef", "retstmt", "optassgnlist", "assgnlist",
  "assgn", "module", "modulehead", "localdecls", "rettype", "params",
  "paramlist", "param", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
      40,    41,    59,   123,   125,    44,    91,    93,    58,    60,
      62,    46
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    72,    73,    74,    74,    74,    74,    75,    75,    75,
      75,    75,    76,    77,    77,    77,    77,    77,    78,    78,
      79,    79,    80,    80,    81,    82,    82,    83,    83,    83,
      84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
      89,    89,    90,    90,    90,    91,    91,    92,    92,    93,
      93,    93,    93,    93,    93,    94,    94,    95,    95,    95,
      96,    96,    97,    98,    99,   100,   101,   102,   102,   103,
     104,   104,   104,   104,   104,   104,   104,   104,   104,   104,
     104,   104,   104,   105,   106,   106,   106,   106,   106,   106,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   110,   110,
     110,   111,   111,   112,   112,   112,   113,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     115,   115,   116,   116,   116,   116,   116,   116,   116,   117,
     118,   118,   119,   119,   120,   120,   121,   121,   121,   122,
     122,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     125,   126,   127,   127,   128,   128,   128,   128,   128,   128,
     129,   129,   130,   130,   131,   131,   131,   131,   131
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     3,     0,     4,     4,     4,     0,     2,     3,
       2,     2,     7,     3,     3,     3,     4,     4,     4,     1,
       4,     1,     1,     3,     3,     0,     1,     0,     1,     2,
       3,     5,     0,     3,     6,     6,     1,     3,     1,     2,
       0,     3,     0,     2,     2,     0,     2,     3,     1,     3,
       2,     2,     2,     2,     2,     0,     1,    10,     9,     8,
       0,     1,     3,     3,     3,     8,     4,     0,     2,     4,
       3,     3,     3,     3,     3,     3,     2,     3,     3,     1,
       1,     1,     1,     6,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     3,     1,     4,     7,     1,     2,
       3,     1,     3,     1,     4,     7,     1,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       1,     1,     2,     4,     4,     1,     1,     2,     2,     4,
       0,     1,     1,     3,     1,     1,     1,     2,     2,     0,
       2,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       5,     6,     0,     2,     1,     2,     3,     3,     3,     3,
       0,     1,     1,     3,     2,     2,     2,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     7,     1,     0,    45,     0,     0,     0,     0,
       0,     0,    25,    25,     0,     0,    11,     8,    10,     2,
      45,     0,   129,     0,     4,     5,     6,    27,     0,    22,
       0,     0,    19,     0,     0,    21,     0,     0,    27,    27,
      27,     0,     0,   164,     0,    25,    25,     9,     0,    46,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    32,    28,    13,     0,    14,    15,     0,     0,
       0,     0,   165,    32,    32,    27,    27,     0,     0,     0,
       0,    42,   128,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,     0,    24,    29,    23,    16,    36,     0,
      17,    38,     0,   166,   167,   168,   169,   170,     0,     0,
       0,   108,   116,     0,     0,    67,     0,     0,   136,   146,
      40,     0,   163,     0,    42,    48,    60,    55,    55,    55,
       0,   103,   105,     0,   111,   113,     0,   149,   135,     0,
     151,    42,     0,    30,     0,     0,    18,    20,    39,     0,
       0,     0,     0,     0,     0,   171,   172,     0,     0,   170,
     109,   140,     0,     0,   117,     0,     0,     0,     0,     0,
       0,    67,     0,     0,     0,   108,   102,     0,     0,     0,
      81,    82,   101,     0,   147,    80,   148,   100,    79,     0,
     137,     0,   138,   160,    43,    61,    40,    56,    50,    51,
      52,     0,     0,     0,     0,     0,     0,    53,     0,   132,
      54,     0,    44,     0,    33,    37,    34,    35,   174,   175,
     176,     0,     0,   161,     0,    18,    20,     0,   110,   145,
     130,   131,   144,     0,   141,   142,   108,    47,     0,   118,
       0,     0,    62,     0,    63,     0,    64,    68,     0,     0,
       0,   158,   159,    76,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,   157,   103,   108,   155,   153,   149,   104,   112,     0,
     156,   154,   149,     0,   150,   152,    31,   177,   178,    12,
     173,   161,   139,     0,     0,    42,    42,    42,     0,     0,
       0,    77,    78,    70,    90,    71,    72,    74,    73,    75,
      91,    92,    93,    94,    95,    96,    97,    98,    99,    85,
      86,    87,    88,    84,    89,    41,     0,     0,   133,   106,
     134,   114,   143,     0,     0,    66,    69,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,   107,   115,
       0,    59,    42,     0,    58,    65,    57
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,     5,    16,   101,    33,    36,    28,    29,
      34,    62,    63,    94,    18,    99,   102,   190,   123,    19,
     124,   125,   198,   126,   196,   127,   128,   129,   166,   168,
     170,   171,   230,   173,   185,   241,   187,   131,   132,   188,
     134,   135,    24,   232,   136,   137,   233,   234,   235,   138,
     209,   139,   140,   141,    21,    81,    44,   154,   155,   156
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -219
static const yytype_int16 yypact[] =
{
    -219,    13,    14,  -219,   124,    11,     0,     0,     0,    60,
      60,    60,   104,   145,   103,   239,  -219,  -219,  -219,  -219,
      41,    71,  -219,     0,   625,   625,   625,    96,    61,  -219,
     159,   258,   162,    60,   170,   162,    60,   176,    96,    96,
      96,   242,   259,  -219,   288,   104,   145,  -219,   103,  -219,
    -219,   553,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   231,    96,  -219,    60,  -219,  -219,   290,   296,
     309,   239,  -219,   231,   231,    96,    96,   244,   243,   249,
     301,   356,  -219,   -29,   -29,  -219,  -219,   130,   130,   390,
     487,   407,   453,     0,  -219,  -219,  -219,  -219,   253,   268,
    -219,  -219,    21,  -219,  -219,  -219,  -219,   369,   296,   239,
     262,   257,   284,   322,   326,   327,   352,   352,  -219,   305,
     304,   371,  -219,   334,   380,  -219,   335,   328,   328,   328,
      -6,   330,   333,   366,  -219,   355,   360,   370,  -219,   378,
     384,   380,     0,  -219,   562,   296,   399,   404,  -219,    60,
      60,    60,   463,   464,   408,  -219,   409,   411,    26,   369,
     423,   174,   419,   472,   465,   305,   498,   305,   500,   510,
     514,   327,   459,   132,   132,   516,  -219,   305,   352,   352,
    -219,  -219,  -219,   305,   201,  -219,   219,  -219,  -219,   305,
    -219,   507,  -219,  -219,  -219,  -219,   304,  -219,  -219,  -219,
    -219,    23,    22,    98,    23,   264,    23,  -219,   132,  -219,
    -219,   132,  -219,   134,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,    60,    60,   506,   369,  -219,  -219,   508,  -219,  -219,
     201,   219,  -219,   509,  -219,   517,   303,  -219,   502,  -219,
     367,   219,  -219,   391,  -219,   558,  -219,  -219,     0,    91,
     535,  -219,  -219,  -219,   305,   305,   287,   417,   305,   305,
     305,   305,   305,    23,    23,    23,    23,    23,    23,    23,
      23,    23,    23,    23,    23,    23,    23,    23,   316,  -219,
      23,   634,   515,   -30,  -219,   634,   370,  -219,  -219,   462,
    -219,   201,   370,   471,  -219,  -219,  -219,  -219,  -219,  -219,
    -219,  -219,  -219,   174,   569,   380,   380,   380,   522,    52,
     297,  -219,  -219,  -219,  -219,    16,   115,  -219,   189,  -219,
      84,    84,  -219,  -219,   368,   368,   496,   538,   444,   634,
     634,   634,   634,   634,   634,  -219,   589,   602,  -219,   541,
    -219,   542,  -219,   605,   586,  -219,  -219,     0,    23,    23,
     543,   592,   598,   504,   513,     1,   588,  -219,  -219,  -219,
       3,  -219,   380,   545,  -219,  -219,  -219
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -219,  -219,  -219,  -219,  -219,    -1,  -219,  -219,   212,   -62,
      85,    80,   554,   108,  -219,   -45,   511,   420,  -122,   599,
    -219,   456,    81,  -219,  -219,  -219,  -219,  -219,  -219,  -219,
     450,  -219,  -108,  -102,  -219,   -77,   -69,    10,  -219,   -63,
     439,  -219,    -7,  -219,  -219,  -111,  -219,   319,  -219,  -219,
    -218,   178,    46,    87,  -219,  -219,   595,   485,   421,  -219
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -27
static const yytype_int16 yytable[] =
{
      25,    26,   194,    96,    17,   360,    22,   363,    54,    55,
     192,   184,   130,     3,    47,   174,    51,     4,   133,   212,
     160,     9,    10,    11,    12,    13,   283,   175,   176,   176,
     161,     9,    10,    11,    45,    46,     9,    10,    11,    45,
      46,   201,   186,   202,   260,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,   130,   175,   240,   176,   243,
      23,   133,   262,   157,    27,    14,   182,   182,   338,   253,
      15,   361,   130,   364,   340,   256,   254,   255,   133,   284,
     122,   278,   280,   280,   231,   147,   144,   218,   219,   220,
     226,   286,    20,   130,   292,    48,   182,   291,    37,   133,
     215,   148,   175,   112,   249,   249,   257,    20,    32,   284,
     250,   250,   280,    38,    39,    40,    41,    42,    72,    73,
      74,   265,   266,    64,   281,   285,    65,   289,     6,   293,
      78,    79,     7,     8,    50,   213,   175,   112,   201,   249,
     309,   258,   249,   260,   261,   250,   311,   312,   250,    35,
     315,   316,   317,   318,   319,   105,   106,   148,    43,   297,
     298,   262,    61,   116,   117,    52,    53,    54,    55,    52,
      53,    54,    55,    56,    57,    58,    59,    60,   175,   112,
     176,   103,   104,   344,   345,   346,   320,   321,   322,   323,
     324,   325,   326,   327,   328,   329,   330,   331,   332,   333,
     334,   296,   291,   336,   177,   178,   179,   180,   181,   199,
     200,   282,   282,   287,   282,   258,   282,   260,   182,   251,
     252,    66,    30,    31,    65,   -26,   231,   258,   259,   260,
     261,   229,   285,    69,   183,   262,   130,   130,   130,    71,
     365,   308,   133,   133,   133,    68,    75,   262,    70,     9,
      10,    11,    45,    46,   263,   264,   265,   266,   267,   268,
     269,   270,   271,    76,   272,   273,   274,   275,   283,   112,
     176,   353,   354,   282,   282,   282,   282,   282,   282,   282,
     282,   282,   282,   282,   282,   282,   282,   282,   276,   277,
     282,    93,    77,   130,   177,   178,   179,   180,   181,   133,
      98,   175,   112,   176,   107,   110,   108,   160,   182,   175,
     112,   176,   109,   258,   259,   260,   261,   161,   145,   282,
      67,   290,   159,    65,   183,   162,   163,   177,   178,   179,
     180,   181,   146,   262,   164,   177,   178,   179,   180,   181,
     352,   182,   258,   259,   260,   261,   165,   287,   313,   182,
     167,   169,    97,   160,   290,    65,   172,   183,   282,   282,
     111,   112,   262,   161,   189,   183,     9,    10,    11,    45,
      46,   100,   163,   113,    65,   191,   114,   335,   115,   149,
     150,   151,   152,   153,   111,   112,   294,   116,   117,   295,
     197,   195,   305,   258,   259,   260,   261,   113,   193,   204,
     114,   203,   115,   263,   264,   265,   266,   118,   119,   120,
      48,   116,   117,   262,   121,   205,   306,   258,   259,   260,
     261,   206,   207,   236,   112,    52,    53,    54,    55,    56,
      57,   118,   119,   120,    48,   208,   113,   262,   121,   114,
     210,   115,    52,    53,    54,    55,    56,    57,    58,   211,
     116,   117,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   216,   272,   273,   274,   275,   217,   221,   222,   223,
     118,   119,   120,   228,   224,   225,   238,   121,   314,   263,
     264,   265,   266,   267,   268,   269,   276,   277,    52,    53,
      54,    55,    56,    57,    58,    59,    60,   263,   264,   265,
     266,   267,   268,   269,   270,   271,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   239,   242,   245,   142,   248,
     143,   244,    52,    53,    54,    55,    56,    57,    58,   339,
      60,   263,   264,   265,   266,   267,   268,   246,   341,   263,
     264,   265,   266,   267,   268,   269,   270,   271,   263,   264,
     265,   266,   267,   268,   269,   270,   271,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   160,   161,   299,   301,
     302,   358,   304,   263,   264,   265,   266,   267,   268,   269,
     359,   271,   303,   307,   310,   343,   337,   347,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    52,    53,    54,
      55,    56,    57,    58,    59,    60,   175,   348,   349,   350,
     351,   356,   355,   362,    82,   366,   279,    95,   237,    49,
     158,   247,   342,   214,   263,   264,   265,   266,   267,   268,
     269,   270,   271,    52,    53,    54,    55,    56,    57,    58,
      59,    60,   288,    80,   227,   300,     0,     0,     0,     0,
     314,     0,     0,     0,     0,     0,     0,     0,     0,   357,
      52,    53,    54,    55,    56,    57,    58,    59,    60,   263,
     264,   265,   266,   267,   268,   269,   270,   271
};

static const yytype_int16 yycheck[] =
{
       7,     8,   124,    65,     5,     4,     6,     4,    37,    38,
     121,   119,    81,     0,    15,   117,    23,     3,    81,   141,
      50,    10,    11,    12,    13,    14,     4,     4,     6,     6,
      60,    10,    11,    12,    13,    14,    10,    11,    12,    13,
      14,    47,   119,    49,    28,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,   124,     4,   165,     6,   167,
      60,   124,    46,   108,     4,    54,    44,    44,   286,   177,
      59,    70,   141,    70,   292,   183,   178,   179,   141,    57,
      81,   189,    60,    60,   161,    64,    93,   149,   150,   151,
      64,   202,     5,   162,   205,    54,    44,   205,    13,   162,
     145,   102,     4,     5,   173,   174,   183,    20,     4,    57,
     173,   174,    60,    10,    11,    12,    13,    14,    38,    39,
      40,    37,    38,    62,   201,   202,    65,   204,     4,   206,
      45,    46,     8,     9,    63,   142,     4,     5,    47,   208,
      49,    26,   211,    28,    29,   208,   254,   255,   211,     4,
     258,   259,   260,   261,   262,    75,    76,   158,    55,   221,
     222,    46,    66,    31,    32,    35,    36,    37,    38,    35,
      36,    37,    38,    39,    40,    41,    42,    43,     4,     5,
       6,    73,    74,   305,   306,   307,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,    67,   310,   280,    30,    31,    32,    33,    34,   128,
     129,   201,   202,   203,   204,    26,   206,    28,    44,   173,
     174,    62,    10,    11,    65,    63,   303,    26,    27,    28,
      29,    57,   309,    63,    60,    46,   305,   306,   307,    63,
     362,   248,   305,   306,   307,    33,     4,    46,    36,    10,
      11,    12,    13,    14,    35,    36,    37,    38,    39,    40,
      41,    42,    43,     4,    45,    46,    47,    48,     4,     5,
       6,   348,   349,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   274,   275,   276,   277,    69,    70,
     280,    60,     4,   362,    30,    31,    32,    33,    34,   362,
       4,     4,     5,     6,    60,     4,    63,    50,    44,     4,
       5,     6,    63,    26,    27,    28,    29,    60,    65,   309,
      62,    57,    60,    65,    60,    68,    69,    30,    31,    32,
      33,    34,    64,    46,    50,    30,    31,    32,    33,    34,
     347,    44,    26,    27,    28,    29,    24,   337,    61,    44,
      24,    24,    62,    50,    57,    65,     4,    60,   348,   349,
       4,     5,    46,    60,    60,    60,    10,    11,    12,    13,
      14,    62,    69,    17,    65,     4,    20,    61,    22,    10,
      11,    12,    13,    14,     4,     5,   208,    31,    32,   211,
      62,    56,    25,    26,    27,    28,    29,    17,    64,    66,
      20,    71,    22,    35,    36,    37,    38,    51,    52,    53,
      54,    31,    32,    46,    58,    49,    25,    26,    27,    28,
      29,    66,    62,     4,     5,    35,    36,    37,    38,    39,
      40,    51,    52,    53,    54,    65,    17,    46,    58,    20,
      62,    22,    35,    36,    37,    38,    39,    40,    41,    65,
      31,    32,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    62,    45,    46,    47,    48,    62,     4,     4,    61,
      51,    52,    53,    50,    65,    64,     4,    58,    61,    35,
      36,    37,    38,    39,    40,    41,    69,    70,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    50,    18,     7,    65,    60,
      67,    21,    35,    36,    37,    38,    39,    40,    41,    67,
      43,    35,    36,    37,    38,    39,    40,    23,    67,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    50,    60,    62,    61,
      61,    67,    70,    35,    36,    37,    38,    39,    40,    41,
      67,    43,    65,    25,    49,    16,    71,    65,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    35,    36,    37,
      38,    39,    40,    41,    42,    43,     4,    66,    66,     4,
      24,    19,    69,    25,    61,    70,   196,    63,   162,    20,
     109,   171,   303,    61,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    35,    36,    37,    38,    39,    40,    41,
      42,    43,   203,    48,   159,   224,    -1,    -1,    -1,    -1,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    35,
      36,    37,    38,    39,    40,    41,    42,    43
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    73,    74,     0,     3,    75,     4,     8,     9,    10,
      11,    12,    13,    14,    54,    59,    76,    77,    86,    91,
     125,   126,     6,    60,   114,   114,   114,     4,    80,    81,
      80,    80,     4,    78,    82,     4,    79,    82,    10,    11,
      12,    13,    14,    55,   128,    13,    14,    77,    54,    91,
      63,   114,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    66,    83,    84,    62,    65,    62,    62,    80,    63,
      80,    63,    83,    83,    83,     4,     4,     4,    82,    82,
     128,   127,    61,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,    60,    85,    84,    81,    62,     4,    87,
      62,    77,    88,    85,    85,    83,    83,    60,    63,    63,
       4,     4,     5,    17,    20,    22,    31,    32,    51,    52,
      53,    58,    77,    90,    92,    93,    95,    97,    98,    99,
     108,   109,   110,   111,   112,   113,   116,   117,   121,   123,
     124,   125,    65,    67,   114,    65,    64,    64,    77,    10,
      11,    12,    13,    14,   129,   130,   131,    87,    88,    60,
      50,    60,    68,    69,    50,    24,   100,    24,   101,    24,
     102,   103,     4,   105,   105,     4,     6,    30,    31,    32,
      33,    34,    44,    60,   104,   106,   107,   108,   111,    60,
      89,     4,   117,    64,    90,    56,    96,    62,    94,    94,
      94,    47,    49,    71,    66,    49,    66,    62,    65,   122,
      62,    65,    90,   114,    61,    87,    62,    62,    81,    81,
      81,     4,     4,    61,    65,    64,    64,   129,    50,    57,
     104,   107,   115,   118,   119,   120,     4,    93,     4,    50,
     104,   107,    18,   104,    21,     7,    23,   102,    60,   108,
     111,   124,   124,   104,   105,   105,   104,   107,    26,    27,
      28,    29,    46,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    45,    46,    47,    48,    69,    70,   104,    89,
      60,   107,   109,     4,    57,   107,   117,   109,   112,   107,
      57,   104,   117,   107,   123,   123,    67,    81,    81,    62,
     130,    61,    61,    65,    70,    25,    25,    25,   114,    49,
      49,   104,   104,    61,    61,   104,   104,   104,   104,   104,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,    61,   107,    71,   122,    67,
     122,    67,   119,    16,    90,    90,    90,    65,    66,    66,
       4,    24,   114,   107,   107,    69,    19,    61,    67,    67,
       4,    70,    25,     4,    70,    90,    70
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
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
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
#line 143 "parse/irParse.y"
    {
        /*
        IrStmt ml;
		for (ml = $3; ml->next; ml = ml->next){
		    if(ml->label==wIdentCreate("main")){
		        main_found = 1;
		        break;
		    }
		}
		*/
		if(main_found==0) irerror("Main not found");
		ir_stmt = (yyvsp[(3) - (3)].y_stmt);/*$4;*/
		irLabelUpdate(ir_stmt);
	;}
    break;

  case 4:
#line 160 "parse/irParse.y"
    {
		IrDef def = irDefCreate((yyvsp[(3) - (4)].name), (yyvsp[(4) - (4)].integer), ir_def);
		ir_def = def;
	;}
    break;

  case 5:
#line 164 "parse/irParse.y"
    {
		int_bits = (yyvsp[(4) - (4)].integer);
	;}
    break;

  case 6:
#line 167 "parse/irParse.y"
    {
		sgnint_bits = (yyvsp[(4) - (4)].integer);
	;}
    break;

  case 8:
#line 173 "parse/irParse.y"
    {
		IrVarList vl;
		for (vl = (yyvsp[(2) - (2)].y_varlist); vl->next; vl = vl->next) {}
		vl->next = ir_gbl;
		ir_gbl = (yyvsp[(2) - (2)].y_varlist);
	;}
    break;

  case 9:
#line 179 "parse/irParse.y"
    {
		IrGbl vl;
		for (vl = (yyvsp[(3) - (3)].y_varlist); vl->next; vl = vl->next) {}
		vl->next = ir_sgbl;
		ir_sgbl = (yyvsp[(3) - (3)].y_varlist);
		
		/* TODO: Insert list of shared global variables (ir_sgbl) 
		to the end of list of global variables (ir_gbl). */
		if (ir_gbl)
			for (vl = ir_gbl; vl->next; vl = vl->next) {}
		else
			ir_gbl = ir_sgbl;
	;}
    break;

  case 12:
#line 196 "parse/irParse.y"
    {
		IrModule module = irModuleCreate((yyvsp[(3) - (7)].name), (yyvsp[(2) - (7)].y_var), (yyvsp[(5) - (7)].y_varlist));
		module->next = ir_module;
		ir_module = module;
	;}
    break;

  case 13:
#line 203 "parse/irParse.y"
    {
		(yyval.y_varlist) = (yyvsp[(2) - (3)].y_varlist);
		IrVarList vl;
		for (vl = (yyval.y_varlist); vl; vl = vl->next) {
			vl->var->type = IR_BOOL;
		}
	;}
    break;

  case 14:
#line 210 "parse/irParse.y"
    {
		(yyval.y_varlist) = (yyvsp[(2) - (3)].y_varlist);
		IrVarList vl;
		for (vl = (yyval.y_varlist); vl; vl = vl->next) {
			vl->var->type = IR_INT;
			if (vl->var->bits) continue;
			if (!int_bits) irerror("unspecified integer range");
			vl->var->bits = int_bits;
		}
	;}
    break;

  case 15:
#line 220 "parse/irParse.y"
    {
		irerror("current implementation does not support signed int");
		(yyval.y_varlist) = (yyvsp[(2) - (3)].y_varlist);
		IrVarList vl;
		for (vl = (yyval.y_varlist); vl; vl = vl->next) {
			vl->var->type = IR_SGNINT;
			if (vl->var->bits) continue;
			if (!sgnint_bits) irerror("unspecified integer range");
			vl->var->bits = sgnint_bits;
		}
	;}
    break;

  case 16:
#line 231 "parse/irParse.y"
    {
		IrVarList vl;
		for (vl = (yyvsp[(3) - (4)].y_varlist); vl; vl = vl->next) {
			vl->var->type = IR_ENUM;
			vl->var->type_ptr = (yyvsp[(2) - (4)].y_enum);
			vl->var->bits = (yyvsp[(2) - (4)].y_enum)->bits;
		}
		(yyval.y_varlist) = (yyvsp[(3) - (4)].y_varlist);
	;}
    break;

  case 17:
#line 240 "parse/irParse.y"
    {
		IrVarList vl;
		IrVarList fields;
		for (vl = (yyvsp[(3) - (4)].y_varlist); vl; vl = vl->next) {
			for (fields = (yyvsp[(2) - (4)].y_struct)->fields; fields; fields = fields->next)
				if (vl->var->dim && fields->var->dim)
					irerror("array of struct of array not allowed");
			vl->var->type = IR_STRUCT;
			vl->var->type_ptr = (yyvsp[(2) - (4)].y_struct);

			irAddStructVar(vl->var);
		}
		(yyval.y_varlist) = (yyvsp[(3) - (4)].y_varlist);
	;}
    break;

  case 18:
#line 256 "parse/irParse.y"
    {
		if (!(yyvsp[(3) - (4)].y_name)) irerror("empty enum list");
		if (current_module) 
			irerror("enum declaration found inside a module");
		(yyval.y_enum) = irCreateTypeEnum((yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].y_name));
	;}
    break;

  case 19:
#line 262 "parse/irParse.y"
    {
		IrEnum en = NULL;
		for (en = ir_enum; en; en = en->next)
			if (en->name == (yyvsp[(1) - (1)].name)) break;
		if (!en) irerror("undefined enum type");
		(yyval.y_enum) = en;
	;}
    break;

  case 20:
#line 271 "parse/irParse.y"
    {
		if (current_module) 
			irerror("struct declaration found inside a module");
		(yyval.y_struct) = irStructCreate((yyvsp[(1) - (4)].name), (yyvsp[(3) - (4)].y_varlist), ir_struct);
		ir_struct = (yyval.y_struct);
	;}
    break;

  case 21:
#line 277 "parse/irParse.y"
    {
		IrStruct s = NULL;
		for (s = ir_struct; s; s = s->next)
			if (s->name == (yyvsp[(1) - (1)].name)) break;
		if (!s) irerror("undefined struct type");
		(yyval.y_struct) = s;
	;}
    break;

  case 22:
#line 286 "parse/irParse.y"
    {
		if (irVarGetUnformatted((yyvsp[(1) - (1)].y_var)->name, current_module, called_module))
			irerror("two variables have the same name");
		(yyval.y_varlist) = irVarListCreate((yyvsp[(1) - (1)].y_var), NULL);
	;}
    break;

  case 23:
#line 291 "parse/irParse.y"
    {
		if (irVarGetUnformatted((yyvsp[(3) - (3)].y_var)->name, current_module, called_module))
			irerror("two variables have the same name");
		(yyval.y_varlist) = irVarListCreate((yyvsp[(3) - (3)].y_var), (yyvsp[(1) - (3)].y_varlist));
	;}
    break;

  case 24:
#line 298 "parse/irParse.y"
    {
		(yyval.y_var) = irVarCreate((yyvsp[(1) - (3)].name), (yyvsp[(2) - (3)].y_dim), (yyvsp[(3) - (3)].integer));
	;}
    break;

  case 25:
#line 303 "parse/irParse.y"
    { (yyval.name) = 0; ;}
    break;

  case 26:
#line 304 "parse/irParse.y"
    { (yyval.name) = (yyvsp[(1) - (1)].name); ;}
    break;

  case 27:
#line 307 "parse/irParse.y"
    { (yyval.y_dim) = NULL; ;}
    break;

  case 28:
#line 308 "parse/irParse.y"
    { (yyval.y_dim) = (yyvsp[(1) - (1)].y_dim); ;}
    break;

  case 29:
#line 309 "parse/irParse.y"
    {
		(yyvsp[(1) - (2)].y_dim)->next = (yyvsp[(2) - (2)].y_dim);
		(yyval.y_dim) = (yyvsp[(1) - (2)].y_dim);
	;}
    break;

  case 30:
#line 315 "parse/irParse.y"
    {
		if ((yyvsp[(2) - (3)].integer) <= 0) irerror("invalid array size");
		(yyval.y_dim) = irDimCreate((yyvsp[(2) - (3)].integer), 0, (yyvsp[(2) - (3)].integer)-1, NULL);
	;}
    break;

  case 31:
#line 319 "parse/irParse.y"
    {
		if ((yyvsp[(2) - (5)].integer) < 0 || (yyvsp[(2) - (5)].integer) > (yyvsp[(4) - (5)].integer))
			irerror("invalid array range");
		(yyval.y_dim) = irDimCreate((yyvsp[(4) - (5)].integer)-(yyvsp[(2) - (5)].integer)+1, (yyvsp[(2) - (5)].integer), (yyvsp[(4) - (5)].integer), NULL);
	;}
    break;

  case 32:
#line 326 "parse/irParse.y"
    { (yyval.integer) = 0; ;}
    break;

  case 33:
#line 327 "parse/irParse.y"
    { 
		if ((yyvsp[(2) - (3)].integer) <= 0) irerror("positive integer expected");
		(yyval.integer) = (yyvsp[(2) - (3)].integer);
	;}
    break;

  case 34:
#line 333 "parse/irParse.y"
    {
		if (!(yyvsp[(4) - (6)].y_name)) irerror("empty enum list");
		irCreateTypeEnum((yyvsp[(2) - (6)].name), (yyvsp[(4) - (6)].y_name));
	;}
    break;

  case 35:
#line 337 "parse/irParse.y"
    {
		IrStruct st = irStructCreate((yyvsp[(2) - (6)].name), (yyvsp[(4) - (6)].y_varlist), ir_struct);
		ir_struct = st;
	;}
    break;

  case 36:
#line 343 "parse/irParse.y"
    {
		(yyval.y_name) = irNameCreate((yyvsp[(1) - (1)].name), NULL);
	;}
    break;

  case 37:
#line 346 "parse/irParse.y"
    {
		(yyval.y_name) = irNameCreate((yyvsp[(1) - (3)].name), (yyvsp[(3) - (3)].y_name));
	;}
    break;

  case 38:
#line 351 "parse/irParse.y"
    {
		if ((yyvsp[(1) - (1)].y_varlist)->var->type == IR_STRUCT)
			irerror("struct cannot be inside a struct");
		(yyval.y_varlist) = (yyvsp[(1) - (1)].y_varlist);
	;}
    break;

  case 39:
#line 356 "parse/irParse.y"
    {
		if ((yyvsp[(2) - (2)].y_varlist)->var->type == IR_STRUCT)
			irerror("struct cannot be inside a struct");
		(yyval.y_varlist) = (yyvsp[(2) - (2)].y_varlist);
		(yyval.y_varlist)->next = (yyvsp[(1) - (2)].y_varlist);
	;}
    break;

  case 40:
#line 395 "parse/irParse.y"
    { (yyval.y_fnode) = NULL; ;}
    break;

  case 41:
#line 396 "parse/irParse.y"
    { (yyval.y_fnode) = (yyvsp[(2) - (3)].y_fnode); ;}
    break;

  case 42:
#line 399 "parse/irParse.y"
    { (yyval.y_stmt) = NULL; ;}
    break;

  case 43:
#line 400 "parse/irParse.y"
    {
		if ((yyvsp[(1) - (2)].y_stmt)->next) {
			IrStmt stmt;
			for (stmt = (yyvsp[(1) - (2)].y_stmt); stmt->next; stmt = stmt->next)
				;
			stmt->next = (yyvsp[(2) - (2)].y_stmt);
		}
		else {
			(yyvsp[(1) - (2)].y_stmt)->next = (yyvsp[(2) - (2)].y_stmt);
		}

		// check if two labels have the same name
		if (((yyvsp[(1) - (2)].y_stmt)->label > 0) && (irLabelExist((yyvsp[(2) - (2)].y_stmt), (yyvsp[(1) - (2)].y_stmt)->label) > 0)) {
			irerror("two labels have the same name");
		}

		(yyval.y_stmt) = (yyvsp[(1) - (2)].y_stmt);
	;}
    break;

  case 44:
#line 418 "parse/irParse.y"
    {
		if ((yyvsp[(1) - (2)].y_stmt)->next) {
			IrStmt stmt;
			// FIXME: error will only be reported at the end of file.
			for (stmt = (yyvsp[(1) - (2)].y_stmt); stmt->next; stmt = stmt->next) {
				if (stmt->label > 0 && irLabelExist((yyvsp[(2) - (2)].y_stmt), stmt->label) > 0)
					irerror("two labels have the same name");
			}
			if (stmt->label > 0 && irLabelExist((yyvsp[(2) - (2)].y_stmt), stmt->label) > 0)
				irerror("two labels have the same name");
			stmt->next = (yyvsp[(2) - (2)].y_stmt);
		}
		else {
			if ((yyvsp[(1) - (2)].y_stmt)->label > 0 && irLabelExist((yyvsp[(2) - (2)].y_stmt), (yyvsp[(1) - (2)].y_stmt)->label) > 0)
				irerror("two labels have the same name");
			(yyvsp[(1) - (2)].y_stmt)->next = (yyvsp[(2) - (2)].y_stmt);
		}

		(yyval.y_stmt) = (yyvsp[(1) - (2)].y_stmt);	
	;}
    break;

  case 45:
#line 440 "parse/irParse.y"
    {(yyval.y_stmt) = NULL; ;}
    break;

  case 46:
#line 441 "parse/irParse.y"
    {
		if ((yyvsp[(1) - (2)].y_stmt)->next) {
			IrStmt stmt;
			// FIXME: error will only be reported at the end of file.
			for (stmt = (yyvsp[(1) - (2)].y_stmt); stmt->next; stmt = stmt->next) {
				if (stmt->label > 0 && irLabelExist((yyvsp[(2) - (2)].y_stmt), stmt->label) > 0)
					irerror("two labels have the same name");
			}
			if (stmt->label > 0 && irLabelExist((yyvsp[(2) - (2)].y_stmt), stmt->label) > 0)
				irerror("two labels have the same name");
			stmt->next = (yyvsp[(2) - (2)].y_stmt);
		}
		else {
			if ((yyvsp[(1) - (2)].y_stmt)->label > 0 && irLabelExist((yyvsp[(2) - (2)].y_stmt), (yyvsp[(1) - (2)].y_stmt)->label) > 0)
				irerror("two labels have the same name");
			(yyvsp[(1) - (2)].y_stmt)->next = (yyvsp[(2) - (2)].y_stmt);
		}
		(yyval.y_stmt) = (yyvsp[(1) - (2)].y_stmt);	
		
	;}
    break;

  case 47:
#line 463 "parse/irParse.y"
    {
        if((yyvsp[(1) - (3)].name)==wIdentCreate((char*)"main")) irerror("Label cannnot have name \"main\"");
		(yyvsp[(3) - (3)].y_stmt)->label = (yyvsp[(1) - (3)].name);
		(yyval.y_stmt) = (yyvsp[(3) - (3)].y_stmt);
	;}
    break;

  case 48:
#line 468 "parse/irParse.y"
    {
		(yyval.y_stmt) = (yyvsp[(1) - (1)].y_stmt);
	;}
    break;

  case 49:
#line 473 "parse/irParse.y"
    {
		(yyvsp[(1) - (3)].y_rule)->expr = (yyvsp[(3) - (3)].y_fnode);
		(yyval.y_stmt) = irStmtCreate(IR_RAWTRANS, (yyvsp[(1) - (3)].y_rule)->from_stack, (yyvsp[(1) - (3)].y_rule), NULL);
		
		called_module = NULL;
	;}
    break;

  case 50:
#line 479 "parse/irParse.y"
    {
		(yyval.y_stmt) = irStmtCreate(IR_IF, 0, (yyvsp[(1) - (2)].y_ifdo), NULL);
	;}
    break;

  case 51:
#line 482 "parse/irParse.y"
    {
		(yyval.y_stmt) = irStmtCreate(IR_DO, 0, (yyvsp[(1) - (2)].y_ifdo), NULL);
	;}
    break;

  case 52:
#line 485 "parse/irParse.y"
    {
		(yyval.y_stmt) = irStmtCreate(IR_P, 0, (yyvsp[(1) - (2)].y_pchoice), NULL);
	;}
    break;

  case 53:
#line 488 "parse/irParse.y"
    { (yyval.y_stmt) = (yyvsp[(1) - (2)].y_stmt); ;}
    break;

  case 54:
#line 489 "parse/irParse.y"
    {
		(yyval.y_stmt) = irStmtCreate(IR_ASSGN, 0, (yyvsp[(1) - (2)].y_exprlist), NULL);
		if (shared_stmt) {
			(yyval.y_stmt)->shared = 1;
			shared_stmt = 0;
		}
	;}
    break;

  case 57:
#line 503 "parse/irParse.y"
    {
		(yyval.y_rule) = irRuleCreate((yyvsp[(1) - (10)].name), (yyvsp[(3) - (10)].name), (yyvsp[(6) - (10)].name), (yyvsp[(8) - (10)].name), (yyvsp[(9) - (10)].name));
		
		IrModule module;
		for (module = ir_module; module; module = module->next) {
			if (module->name != (yyvsp[(8) - (10)].name)) continue;
			called_module = module;
			break;
		}
	;}
    break;

  case 58:
#line 513 "parse/irParse.y"
    {
		(yyval.y_rule) = irRuleCreate((yyvsp[(1) - (9)].name), (yyvsp[(3) - (9)].name), (yyvsp[(6) - (9)].name), (yyvsp[(8) - (9)].name), 0);
	;}
    break;

  case 59:
#line 516 "parse/irParse.y"
    {
		(yyval.y_rule) = irRuleCreate((yyvsp[(1) - (8)].name), (yyvsp[(3) - (8)].name), (yyvsp[(6) - (8)].name), 0, 0);
	;}
    break;

  case 60:
#line 521 "parse/irParse.y"
    { (yyval.string) = NULL; ;}
    break;

  case 61:
#line 522 "parse/irParse.y"
    { (yyval.string) = (yyvsp[(1) - (1)].string); ;}
    break;

  case 62:
#line 525 "parse/irParse.y"
    {
		if (!(yyvsp[(2) - (3)].y_ifdo)) irerror("empty if statement");
		//if (!$2->next && $2->cond->token == IR_ELSE)
		//	irerror("else without other statments");
		(yyval.y_ifdo) = (yyvsp[(2) - (3)].y_ifdo);
		else_cnt = 0;
	;}
    break;

  case 63:
#line 534 "parse/irParse.y"
    {
		if (!(yyvsp[(2) - (3)].y_ifdo)) irerror("empty do statement");
		//if (!$2->next && $2->cond->token == IR_ELSE)
		//	irerror("else without other statments");
		(yyval.y_ifdo) = (yyvsp[(2) - (3)].y_ifdo);
		else_cnt = 0;
	;}
    break;

  case 64:
#line 543 "parse/irParse.y"
    {
		pchoice_found = 1;
		if(!(yyvsp[(2) - (3)].y_pchoice)) irerror("empty pchoice statement");
		float prob_val = 0.0;
		IrPchoice irp = (yyvsp[(2) - (3)].y_pchoice);
		while(irp){
			prob_val += irp->probability;
			irp = irp->next;
		}
		if(prob_val != 1.0) irerror("Probability values do not add upto 1");
		(yyval.y_pchoice) = (yyvsp[(2) - (3)].y_pchoice);
		else_cnt = 0;
	;}
    break;

  case 65:
#line 569 "parse/irParse.y"
    {
        if (!(yyvsp[(4) - (8)].y_stmt)) irerror("invalid statement");
		// handles the case ":: cond -> x: ...;" by adding "skip"
		if ((yyvsp[(4) - (8)].y_stmt)->label) {
			IrStmt s = irStmtCreate(IR_SKIP, 0, NULL, NULL);
			s->next = (yyvsp[(4) - (8)].y_stmt);
			(yyvsp[(4) - (8)].y_stmt) = s;
		}
		(yyval.y_ifdo) = irIfdoCreate((yyvsp[(2) - (8)].y_fnode), (yyvsp[(4) - (8)].y_stmt), NULL);
		
        if (!(yyvsp[(8) - (8)].y_stmt)) irerror("invalid statement");
		if (else_cnt) irerror("second else found");
		else_cnt++;
		// handles the case ":: cond -> x: ...;" by adding "skip"
		if ((yyvsp[(8) - (8)].y_stmt)->label) {
			IrStmt s = irStmtCreate(IR_SKIP, 0, NULL, NULL);
			s->next = (yyvsp[(8) - (8)].y_stmt);
			(yyvsp[(8) - (8)].y_stmt) = s;
		}
		(yyval.y_ifdo)->next = irIfdoCreate(irFnodeCreate(IR_ELSE, 0 ,NULL, NULL), (yyvsp[(8) - (8)].y_stmt), NULL);
    ;}
    break;

  case 66:
#line 591 "parse/irParse.y"
    {
        if (!(yyvsp[(4) - (4)].y_stmt)) irerror("invalid statement");
		// handles the case ":: cond -> x: ...;" by adding "skip"
		if ((yyvsp[(4) - (4)].y_stmt)->label) {
			IrStmt s = irStmtCreate(IR_SKIP, 0, NULL, NULL);
			s->next = (yyvsp[(4) - (4)].y_stmt);
			(yyvsp[(4) - (4)].y_stmt) = s;
		}
		(yyval.y_ifdo) = irIfdoCreate((yyvsp[(2) - (4)].y_fnode), (yyvsp[(4) - (4)].y_stmt), NULL);
		
		(yyval.y_ifdo)->next =  irIfdoCreate(irFnodeCreate(IR_ELSE, 0 ,NULL, NULL), irStmtCreate(IR_BREAK, 0, NULL, NULL), NULL) ;
    ;}
    break;

  case 67:
#line 630 "parse/irParse.y"
    {
		(yyval.y_pchoice) = NULL;
	;}
    break;

  case 68:
#line 633 "parse/irParse.y"
    {
		(yyvsp[(1) - (2)].y_pchoice)->next = (yyvsp[(2) - (2)].y_pchoice);
		(yyval.y_pchoice) = (yyvsp[(1) - (2)].y_pchoice);
	;}
    break;

  case 69:
#line 639 "parse/irParse.y"
    {
		if (!(yyvsp[(4) - (4)].y_stmt)) irerror("invalid statement");
		if ((yyvsp[(2) - (4)].floating_point)>1 || (yyvsp[(2) - (4)].floating_point)<0) irerror("invalid value of probability");
		if ((yyvsp[(4) - (4)].y_stmt)->label) {
			IrStmt s = irStmtCreate(IR_SKIP, 0, NULL, NULL);
			s->next = (yyvsp[(4) - (4)].y_stmt);
			(yyvsp[(4) - (4)].y_stmt) = s;
		}
		(yyval.y_pchoice) = irPchoiceCreate((yyvsp[(2) - (4)].floating_point), (yyvsp[(4) - (4)].y_stmt), NULL);
	;}
    break;

  case 70:
#line 650 "parse/irParse.y"
    { (yyval.y_fnode) = (yyvsp[(2) - (3)].y_fnode); ;}
    break;

  case 71:
#line 651 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LGC_AND, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 72:
#line 654 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LGC_OR, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 73:
#line 657 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LGC_XOR, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 74:
#line 660 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LGC_EQV, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 75:
#line 663 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_CMPEQ, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 76:
#line 666 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LGC_NOT, 0, NULL, (yyvsp[(2) - (2)].y_fnode));
	;}
    break;

  case 77:
#line 669 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_FORALL, 0, (yyvsp[(2) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
		IrQvar qvar = ir_qvar;
		ir_qvar = ir_qvar->next;
		Free(qvar);
	;}
    break;

  case 78:
#line 675 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_EXISTS, 0, (yyvsp[(2) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
		IrQvar qvar = ir_qvar;
		ir_qvar = ir_qvar->next;
		Free(qvar);
	;}
    break;

  case 79:
#line 681 "parse/irParse.y"
    { (yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode); ;}
    break;

  case 80:
#line 682 "parse/irParse.y"
    { (yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode); ;}
    break;

  case 81:
#line 683 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_TRUE, 0, NULL, NULL);
	;}
    break;

  case 82:
#line 686 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_FALSE, 0, NULL, NULL);
	;}
    break;

  case 83:
#line 691 "parse/irParse.y"
    {
		if ((yyvsp[(3) - (6)].integer) > (yyvsp[(5) - (6)].integer)) irerror("invalid integer range");
		(yyval.y_fnode) = irNamedFnodeCreate(IR_QUANT, (yyvsp[(1) - (6)].name), 0
			, irFnodeCreate(IR_NUMBER, (yyvsp[(3) - (6)].integer), NULL, NULL)
			, irFnodeCreate(IR_NUMBER, (yyvsp[(5) - (6)].integer), NULL, NULL)
		);
		IrQvar qvar = irQvarCreate((yyvsp[(1) - (6)].name), (yyvsp[(3) - (6)].integer), (yyvsp[(5) - (6)].integer));
		qvar->next = ir_qvar;
		ir_qvar = qvar;
	;}
    break;

  case 84:
#line 703 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LT, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 85:
#line 706 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_LE, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 86:
#line 709 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_EQ, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 87:
#line 712 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_NE, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 88:
#line 715 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_GE, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 89:
#line 718 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_GT, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 90:
#line 723 "parse/irParse.y"
    {
		(yyval.y_fnode) = (yyvsp[(2) - (3)].y_fnode);
	;}
    break;

  case 91:
#line 726 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_PLUS, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 92:
#line 729 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_MINUS, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 93:
#line 732 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_MULT, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 94:
#line 735 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_DIV, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 95:
#line 738 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_SHL, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 96:
#line 741 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_SHR, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 97:
#line 744 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_AND, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 98:
#line 747 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_OR, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 99:
#line 750 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_XOR, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 100:
#line 753 "parse/irParse.y"
    {
		(yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode);
	;}
    break;

  case 101:
#line 756 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_QVAR, (yyvsp[(1) - (1)].qvar)->name, 0, NULL, NULL);
	;}
    break;

  case 102:
#line 759 "parse/irParse.y"
    {
		(yyval.y_fnode) = irFnodeCreate(IR_NUMBER, (yyvsp[(1) - (1)].integer), NULL, NULL);
	;}
    break;

  case 103:
#line 764 "parse/irParse.y"
    { 
		IrVar v = irVarGetUnformatted((yyvsp[(1) - (1)].y_fnode)->name, current_module, called_module);
		if (!v) irerror("unknown variable");

		if ((yyvsp[(1) - (1)].y_fnode)->left) {
			if (!v->dim || !v->dim->next)
				irerror("array dimension mismatched");
		} else {
			if ((yyvsp[(1) - (1)].y_fnode)->right && (!v->dim || (v->dim && v->dim->next)))
				irerror("array dimension mismatched");
		}

		if ((yyvsp[(1) - (1)].y_fnode)->left) 
			(yyvsp[(1) - (1)].y_fnode)->right = irTwoDimIndex2Fnode(v, (yyvsp[(1) - (1)].y_fnode)->left, (yyvsp[(1) - (1)].y_fnode)->right);
		else if ((yyvsp[(1) - (1)].y_fnode)->right)
			(yyvsp[(1) - (1)].y_fnode)->right = irFnodeCreate(IR_INDEX, 0, NULL, (yyvsp[(1) - (1)].y_fnode)->right);

		(yyvsp[(1) - (1)].y_fnode)->left = NULL;
		(yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode);
	;}
    break;

  case 104:
#line 784 "parse/irParse.y"
    {
		wIdent n = irNameStructCreate((yyvsp[(1) - (3)].y_fnode)->name, (yyvsp[(3) - (3)].y_fnode)->name);
		IrVar v = irVarGet(n, current_module, called_module);
		if (!v) irerror("unknown struct variable");

		if ((yyvsp[(1) - (3)].y_fnode)->right && (yyvsp[(3) - (3)].y_fnode)->right)
			irerror("invalid array index");

		if ((yyvsp[(1) - (3)].y_fnode)->left || (yyvsp[(3) - (3)].y_fnode)->left) {
			if (!v->dim || !v->dim->next)
				irerror("array dimension mismatched");
		} else {
			if (((yyvsp[(1) - (3)].y_fnode)->right || (yyvsp[(1) - (3)].y_fnode)->right) 
					&& (!v->dim || (v->dim && v->dim->next))) 
				irerror("array dimension mismatched");
		}

		IrFnode idx = NULL;
		if ((yyvsp[(1) - (3)].y_fnode)->right && (yyvsp[(3) - (3)].y_fnode)->right)
			irerror("invalid array index");
		if ((yyvsp[(1) - (3)].y_fnode)->left) 
			idx = irTwoDimIndex2Fnode(v, (yyvsp[(1) - (3)].y_fnode)->left, (yyvsp[(1) - (3)].y_fnode)->right);
		else if ((yyvsp[(1) - (3)].y_fnode)->right) 
			idx = irFnodeCreate(IR_INDEX, 0, NULL, (yyvsp[(1) - (3)].y_fnode)->right);
		else if ((yyvsp[(3) - (3)].y_fnode)->left) 
			idx = irTwoDimIndex2Fnode(v, (yyvsp[(3) - (3)].y_fnode)->left, (yyvsp[(3) - (3)].y_fnode)->right);
		else if ((yyvsp[(3) - (3)].y_fnode)->right) 
			idx = irFnodeCreate(IR_INDEX, 0, NULL, (yyvsp[(3) - (3)].y_fnode)->right);

		(yyval.y_fnode) = irNamedFnodeCreate(
			IR_IDENT, n, (yyvsp[(3) - (3)].y_fnode)->value, NULL, NULL);
		(yyval.y_fnode)->right = irFnodeCopy(idx);
		irFnodeFree((yyvsp[(1) - (3)].y_fnode));
		irFnodeFree((yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 105:
#line 821 "parse/irParse.y"
    {
		(yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode);
	;}
    break;

  case 106:
#line 824 "parse/irParse.y"
    {
		(yyvsp[(1) - (4)].y_fnode)->right = (yyvsp[(3) - (4)].y_fnode);
		(yyval.y_fnode) = (yyvsp[(1) - (4)].y_fnode);
	;}
    break;

  case 107:
#line 828 "parse/irParse.y"
    {
		(yyvsp[(1) - (7)].y_fnode)->left = (yyvsp[(3) - (7)].y_fnode);
		(yyvsp[(1) - (7)].y_fnode)->right = (yyvsp[(6) - (7)].y_fnode);
		(yyval.y_fnode) = (yyvsp[(1) - (7)].y_fnode);
	;}
    break;

  case 108:
#line 835 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_IDENT, (yyvsp[(1) - (1)].name), 0, NULL, NULL);
		last_var = (yyvsp[(1) - (1)].name);
	;}
    break;

  case 109:
#line 839 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_IDENT, (yyvsp[(1) - (2)].name), 1, NULL, NULL);
		last_var = (yyvsp[(1) - (2)].name);
	;}
    break;

  case 110:
#line 843 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_IDENT, (yyvsp[(1) - (3)].name), 2, NULL, NULL);
		last_var = (yyvsp[(1) - (3)].name);
	;}
    break;

  case 111:
#line 849 "parse/irParse.y"
    { 
		IrVar v = irVarGetUnformatted((yyvsp[(1) - (1)].y_fnode)->name, current_module, called_module);
		if (!v) irerror("unknown variable");

		if ((yyvsp[(1) - (1)].y_fnode)->left) {
			if (!v->dim || !v->dim->next)
				irerror("array dimension mismatched");
		} else {
			if ((yyvsp[(1) - (1)].y_fnode)->right && (!v->dim || (v->dim && v->dim->next)))
				irerror("array dimension mismatched");
		}	

		if ((yyvsp[(1) - (1)].y_fnode)->left) 
			(yyvsp[(1) - (1)].y_fnode)->right = irTwoDimIndex2Fnode(v, (yyvsp[(1) - (1)].y_fnode)->left, (yyvsp[(1) - (1)].y_fnode)->right);
		else if ((yyvsp[(1) - (1)].y_fnode)->right)
			(yyvsp[(1) - (1)].y_fnode)->right = irFnodeCreate(IR_INDEX, 0, NULL, (yyvsp[(1) - (1)].y_fnode)->right);

		(yyvsp[(1) - (1)].y_fnode)->left = NULL;
		(yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode);
	;}
    break;

  case 112:
#line 869 "parse/irParse.y"
    {
		wIdent n = irNameStructCreate((yyvsp[(1) - (3)].y_fnode)->name, (yyvsp[(3) - (3)].y_fnode)->name);
		IrVar v = irVarGet(n, current_module, called_module);
		if (!v) irerror("unknown struct variable");

		if ((yyvsp[(1) - (3)].y_fnode)->right && (yyvsp[(3) - (3)].y_fnode)->right)
			irerror("invalid array index");
		if ((yyvsp[(1) - (3)].y_fnode)->left || (yyvsp[(3) - (3)].y_fnode)->left) {
			if (!v->dim || !v->dim->next)
				irerror("array dimension mismatched");
		} else {
			if (((yyvsp[(1) - (3)].y_fnode)->right || (yyvsp[(1) - (3)].y_fnode)->right) 
					&& (!v->dim || (v->dim && v->dim->next))) 
				irerror("array dimension mismatched");
		}	

		IrFnode idx = NULL;
		if ((yyvsp[(1) - (3)].y_fnode)->right && (yyvsp[(3) - (3)].y_fnode)->right)
			irerror("invalid array index");
		if ((yyvsp[(1) - (3)].y_fnode)->left) 
			idx = irTwoDimIndex2Fnode(v, (yyvsp[(1) - (3)].y_fnode)->left, (yyvsp[(1) - (3)].y_fnode)->right);
		else if ((yyvsp[(1) - (3)].y_fnode)->right) 
			idx = irFnodeCreate(IR_INDEX, 0, NULL, (yyvsp[(1) - (3)].y_fnode)->right);
		else if ((yyvsp[(3) - (3)].y_fnode)->left) 
			idx = irTwoDimIndex2Fnode(v, (yyvsp[(3) - (3)].y_fnode)->left, (yyvsp[(3) - (3)].y_fnode)->right);
		else if ((yyvsp[(3) - (3)].y_fnode)->right) 
			idx = irFnodeCreate(IR_INDEX, 0, NULL, (yyvsp[(3) - (3)].y_fnode)->right);

		(yyval.y_fnode) = irNamedFnodeCreate(
			IR_BVAR, n, (yyvsp[(3) - (3)].y_fnode)->value, NULL, NULL);
		(yyval.y_fnode)->right = irFnodeCopy(idx);
		irFnodeFree((yyvsp[(1) - (3)].y_fnode));
		irFnodeFree((yyvsp[(3) - (3)].y_fnode));
	;}
    break;

  case 113:
#line 905 "parse/irParse.y"
    {
		(yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode);
	;}
    break;

  case 114:
#line 908 "parse/irParse.y"
    {
		(yyvsp[(1) - (4)].y_fnode)->right = (yyvsp[(3) - (4)].y_fnode);
		(yyval.y_fnode) = (yyvsp[(1) - (4)].y_fnode);
	;}
    break;

  case 115:
#line 912 "parse/irParse.y"
    {
		(yyvsp[(1) - (7)].y_fnode)->left = (yyvsp[(3) - (7)].y_fnode);
		(yyvsp[(1) - (7)].y_fnode)->right = (yyvsp[(6) - (7)].y_fnode);
		(yyval.y_fnode) = (yyvsp[(1) - (7)].y_fnode);
	;}
    break;

  case 116:
#line 919 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_BVAR, (yyvsp[(1) - (1)].name), 0, NULL, NULL);
	;}
    break;

  case 117:
#line 922 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_BVAR, (yyvsp[(1) - (2)].name), 1, NULL, NULL);
	;}
    break;

  case 118:
#line 925 "parse/irParse.y"
    {
		(yyval.y_fnode) = irNamedFnodeCreate(IR_BVAR, (yyvsp[(1) - (3)].name), 2, NULL, NULL);
	;}
    break;

  case 119:
#line 930 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) + (yyvsp[(3) - (3)].integer); ;}
    break;

  case 120:
#line 931 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) - (yyvsp[(3) - (3)].integer); ;}
    break;

  case 121:
#line 932 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) * (yyvsp[(3) - (3)].integer); ;}
    break;

  case 122:
#line 933 "parse/irParse.y"
    { 
		if ((yyvsp[(3) - (3)].integer) == 0) {
			irerror("division by zero");
		}
		(yyval.integer) = (yyvsp[(1) - (3)].integer) / (yyvsp[(3) - (3)].integer); 
	;}
    break;

  case 123:
#line 939 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) << (yyvsp[(3) - (3)].integer); ;}
    break;

  case 124:
#line 940 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) >> (yyvsp[(3) - (3)].integer); ;}
    break;

  case 125:
#line 941 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) & (yyvsp[(3) - (3)].integer); ;}
    break;

  case 126:
#line 942 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) | (yyvsp[(3) - (3)].integer); ;}
    break;

  case 127:
#line 943 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (3)].integer) ^ (yyvsp[(3) - (3)].integer); ;}
    break;

  case 128:
#line 944 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(2) - (3)].integer); ;}
    break;

  case 129:
#line 945 "parse/irParse.y"
    { (yyval.integer) = (yyvsp[(1) - (1)].integer); ;}
    break;

  case 130:
#line 948 "parse/irParse.y"
    { (yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode); ;}
    break;

  case 131:
#line 949 "parse/irParse.y"
    { (yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode); ;}
    break;

  case 132:
#line 952 "parse/irParse.y"
    {
		irUpdateCallExprList((yyvsp[(1) - (2)].y_stmt), (yyvsp[(2) - (2)].y_exprlist));
		if (shared_stmt) {
			(yyvsp[(1) - (2)].y_stmt)->shared = 1;
			shared_stmt = 0;
		}
		(yyval.y_stmt) = (yyvsp[(1) - (2)].y_stmt);
		called_module = NULL;
	;}
    break;

  case 133:
#line 961 "parse/irParse.y"
    {
		irUpdateCallExprList((yyvsp[(3) - (4)].y_stmt), (yyvsp[(4) - (4)].y_exprlist));
		if (shared_stmt) {
			(yyvsp[(3) - (4)].y_stmt)->shared = 1;
			shared_stmt = 0;
		}

		char *msg = 0;
		IrStmt stmt = irStmtCreate(IR_ASSGN, 0, NULL, NULL); 
		stmt->content = irCreateRetExprList(2, called_module, 
			current_module, (yyvsp[(1) - (4)].y_fnode), &msg);
		if (msg) irerror(msg);

		if (isSharedGlobal((yyvsp[(1) - (4)].y_fnode)->name)) stmt->shared = 1;
		(yyvsp[(3) - (4)].y_stmt)->next = stmt;
		(yyval.y_stmt) = (yyvsp[(3) - (4)].y_stmt);
		called_module = NULL;
	;}
    break;

  case 134:
#line 979 "parse/irParse.y"
    {
		irUpdateCallExprList((yyvsp[(3) - (4)].y_stmt), (yyvsp[(4) - (4)].y_exprlist));
		if (shared_stmt) {
			(yyvsp[(3) - (4)].y_stmt)->shared = 1;
			shared_stmt = 0;
		}

		char *msg = 0;
		IrStmt stmt = irStmtCreate(IR_ASSGN, 0, NULL, NULL);
		stmt->content = irCreateRetExprList(2, called_module, 
			current_module, (yyvsp[(1) - (4)].y_fnode), &msg);
		if (msg) irerror(msg);

		if (isSharedGlobal((yyvsp[(1) - (4)].y_fnode)->name)) stmt->shared = 1;
		(yyvsp[(3) - (4)].y_stmt)->next = stmt;
		(yyval.y_stmt) = (yyvsp[(3) - (4)].y_stmt);
		called_module = NULL;
	;}
    break;

  case 135:
#line 997 "parse/irParse.y"
    { 
		if (!current_module) irerror("return must be in module");
		(yyval.y_stmt) = (yyvsp[(1) - (1)].y_stmt);
	;}
    break;

  case 136:
#line 1008 "parse/irParse.y"
    {
		(yyval.y_stmt) = irStmtCreate(IR_BREAK, 0, NULL, NULL);
	;}
    break;

  case 137:
#line 1011 "parse/irParse.y"
    {
		(yyval.y_stmt) = irStmtCreate(IR_SKIP, 0, (yyvsp[(2) - (2)].y_fnode), NULL);
	;}
    break;

  case 138:
#line 1014 "parse/irParse.y"
    {
		wIdent midName = irNameStackFresh();
		IrCall forked = (IrCall) (yyvsp[(2) - (2)].y_stmt)->content;
		
		IrExprList forkedParam = irExprListCopy(forked->params);
		IrExprList paramPtr = forkedParam;
		IrFnode param;
		for (; paramPtr; paramPtr = paramPtr->next) {
			param = paramPtr->expr;
			if ((param->token == IR_EQ) || (param->token == IR_CMPEQ)) {
				irFnodeFree(param->right);
				param->right = irNamedFnodeCreate(
					IR_IDENT, param->left->name, 0, NULL, NULL);
			} else if (param->token == IR_FORALL) {
				param->right->right->name = param->right->left->name;
			} else {
				irerror("unexpected parameter");
			}
		}
		
		IrFork irfork = irForkCreate(midName, forked);
			
		IrCall midCall = irCallCreate(forked->module, forkedParam);
		IrStmt midStmt = irStmtCreate(IR_CALL, midName, midCall, NULL);
		IrModule midModule = irModuleCopy(forked->module);
		midModule->name = midName;
		midModule->first_stmt = midStmt;
		midModule->last_stmt = midStmt;
		midModule->next = ir_module;
		ir_module = midModule;
		
		(yyval.y_stmt) = irStmtCreate(IR_FORK, 0, irfork, NULL);
	;}
    break;

  case 139:
#line 1049 "parse/irParse.y"
    {
		IrModule m;
		for (m = ir_module; m; m = m->next) 
			if (m->name == (yyvsp[(1) - (4)].name)) break;
		if (!m) irerror("module not found");
		
		called_module = m;
		char *msg = 0;
		(yyval.y_stmt) = irCreateCallStmt(current_module, m, (yyvsp[(3) - (4)].y_exprlist), &msg);
		if (msg) irerror(msg);
		irExprlistFree((yyvsp[(3) - (4)].y_exprlist));
	;}
    break;

  case 140:
#line 1063 "parse/irParse.y"
    { (yyval.y_exprlist) = NULL; ;}
    break;

  case 141:
#line 1064 "parse/irParse.y"
    { (yyval.y_exprlist) = (yyvsp[(1) - (1)].y_exprlist); ;}
    break;

  case 142:
#line 1067 "parse/irParse.y"
    {
		(yyval.y_exprlist) = irExprListCreate((yyvsp[(1) - (1)].y_fnode), NULL);
	;}
    break;

  case 143:
#line 1070 "parse/irParse.y"
    {
		(yyval.y_exprlist) = irExprListCreate((yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_exprlist));
	;}
    break;

  case 144:
#line 1075 "parse/irParse.y"
    {
		(yyval.y_fnode) = (yyvsp[(1) - (1)].y_fnode);
	;}
    break;

  case 145:
#line 1078 "parse/irParse.y"
    {
		(yyval.y_fnode) = NULL;
	;}
    break;

  case 146:
#line 1083 "parse/irParse.y"
    {
		if (current_module->retvar->type != IR_VOID)
			irerror("invalid return type");
		(yyval.y_stmt) = irStmtCreate(IR_RET, 0, NULL, NULL);
	;}
    break;

  case 147:
#line 1088 "parse/irParse.y"
    {
		if (current_module->retvar->type != IR_BOOL)
			irerror("invalid return type");
		(yyval.y_stmt) = irStmtCreate(IR_RET, 0, NULL, NULL);
		char *msg = 0;
		(yyval.y_stmt)->content = irCreateRetExprList(1, current_module, 
			current_module, (yyvsp[(2) - (2)].y_fnode), &msg);
		if (msg) irerror(msg);
	;}
    break;

  case 148:
#line 1097 "parse/irParse.y"
    {
		if (current_module->retvar->type == IR_VOID)
			irerror("invalid return type");
		(yyval.y_stmt) = irStmtCreate(IR_RET, 0, NULL, NULL);
		char *msg = 0;
		(yyval.y_stmt)->content = irCreateRetExprList(1, current_module, 
			current_module, (yyvsp[(2) - (2)].y_fnode), &msg);
		if (msg) irerror(msg);	
	;}
    break;

  case 149:
#line 1108 "parse/irParse.y"
    {
		(yyval.y_exprlist) = NULL;
	;}
    break;

  case 150:
#line 1111 "parse/irParse.y"
    {
		(yyval.y_exprlist) = (yyvsp[(2) - (2)].y_exprlist);
	;}
    break;

  case 151:
#line 1116 "parse/irParse.y"
    {
		(yyval.y_exprlist) = (yyvsp[(1) - (1)].y_exprlist);
	;}
    break;

  case 152:
#line 1119 "parse/irParse.y"
    {
		IrExprList exprlist;
		for (exprlist = (yyvsp[(1) - (3)].y_exprlist); exprlist->next; exprlist = exprlist->next)
			;
		exprlist->next = (yyvsp[(3) - (3)].y_exprlist);
		(yyval.y_exprlist) = (yyvsp[(1) - (3)].y_exprlist);
	;}
    break;

  case 153:
#line 1128 "parse/irParse.y"
    {
		
		/* aray = array */
		IrVar lvar = irVarGetUnformatted((yyvsp[(1) - (3)].y_fnode)->name, current_module, called_module);
		IrVar rvar = NULL;
		if ((yyvsp[(3) - (3)].y_fnode)->token == IR_IDENT) 
			rvar = irVarGetUnformatted((yyvsp[(3) - (3)].y_fnode)->name, current_module, called_module);

		if (lvar && lvar->dim && !(yyvsp[(1) - (3)].y_fnode)->right) {

			if (!rvar || !rvar->dim || (yyvsp[(3) - (3)].y_fnode)->right 
					|| irDimEquals(lvar->dim, rvar->dim) == 0)
				irerror("invalid array assignment");

			int i, j;
			irFlattenDim(lvar->dim, &i, &j);
			IrFnode eqnode;
			IrExprList exprlist = NULL;
			if (lvar->type == IR_STRUCT) {
				IrVar slvar = lvar->extra;
				IrVar srvar = rvar->extra;
				while(slvar) {
					int type, op;
					if (slvar->type == IR_BOOL) {
						type = IR_BVAR;
						op = IR_CMPEQ;
					} else {
						type = IR_IDENT;
						op = IR_EQ;
					}
					eqnode = irFnodeAllAssgn(type, op, slvar->name, srvar->name, i, j);
					exprlist = irExprListCreate(eqnode, exprlist);
					slvar = slvar->extra;
					srvar = srvar->extra;
				}
			} else {
				eqnode = irFnodeAllAssgn(IR_IDENT, IR_EQ, lvar->name, rvar->name, i, j);
				exprlist = irExprListCreate(eqnode, NULL);
			}
			(yyval.y_exprlist) = exprlist;
		} 

		/* struct = struct */
		else if (lvar && lvar->type == IR_STRUCT && (yyvsp[(3) - (3)].y_fnode)->token == IR_IDENT) {
			if (rvar && rvar->type == IR_STRUCT) {

				if (lvar->type_ptr != rvar->type_ptr)
					irerror("struct type mismatched");

				IrVar slvar = lvar->extra;
				IrVar srvar = rvar->extra;
				IrFnode eqnode;
				IrExprList exprlist = NULL;
				while(slvar) {
					int type, op;
					if (slvar->type == IR_BOOL) {
						type = IR_BVAR;
						op = IR_CMPEQ;
					} else {
						type = IR_IDENT;
						op = IR_EQ;
					}
					if (slvar->dim) {
						int i, j;
						irFlattenDim(slvar->dim, &i, &j);
						eqnode = irFnodeAllAssgn(type, op, slvar->name, srvar->name, i, j);
					} else {
						IrFnode lnode = irNamedFnodeCreate(type, slvar->name, 1, NULL, NULL);
						IrFnode rnode = irNamedFnodeCreate(type, srvar->name, 0, NULL, NULL);
						eqnode = irFnodeCreate(op, 0, lnode, rnode);
					}
					exprlist = irExprListCreate(eqnode, exprlist);
					slvar = slvar->extra;
					srvar = srvar->extra;
				}

				irFnodeFree((yyvsp[(1) - (3)].y_fnode));
				irFnodeFree((yyvsp[(3) - (3)].y_fnode));
				(yyval.y_exprlist) = exprlist;
			}
		} else {
			(yyvsp[(1) - (3)].y_fnode)->value = 1;
			(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_EQ, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode)), NULL);
			if (isSharedGlobal((yyvsp[(1) - (3)].y_fnode)->name)) shared_stmt = 1;
		}
	;}
    break;

  case 154:
#line 1214 "parse/irParse.y"
    {

		/* aray = array */
		IrVar lvar = irVarGetUnformatted((yyvsp[(1) - (3)].y_fnode)->name, current_module, called_module);
		if (lvar && lvar->dim && !(yyvsp[(1) - (3)].y_fnode)->right && (yyvsp[(3) - (3)].y_fnode)->token == IR_BVAR) {
			IrVar rvar = irVarGetUnformatted((yyvsp[(3) - (3)].y_fnode)->name, current_module, called_module);

			if (!rvar->dim || (yyvsp[(3) - (3)].y_fnode)->right 
					|| irDimEquals(lvar->dim, rvar->dim) == 0)
				irerror("invalid array assignment");

			int i, j;
			irFlattenDim(lvar->dim, &i, &j);
			IrFnode eqnode = irFnodeAllAssgn(IR_BVAR, IR_CMPEQ, lvar->name, rvar->name, i, j);
			(yyval.y_exprlist) = irExprListCreate(eqnode, NULL);
		} else {
			(yyvsp[(1) - (3)].y_fnode)->value = 1;
			(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_CMPEQ, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode)), NULL);
			if (isSharedGlobal((yyvsp[(1) - (3)].y_fnode)->name)) shared_stmt = 1;
		}
	;}
    break;

  case 155:
#line 1235 "parse/irParse.y"
    {
		IrVar var = irVarGetUnformatted((yyvsp[(1) - (3)].y_fnode)->name, current_module, called_module);
		if (!var) var = irVarGet((yyvsp[(1) - (3)].y_fnode)->name, current_module, called_module);

		/* struct = undef */
		if (var && var->type == IR_STRUCT) {
			IrVar sv;
			IrFnode vnode, eq;
			IrExprList exprlist = NULL;
			for (sv = var->extra; sv; sv = sv->extra) {
				vnode = irNamedFnodeCreate(IR_IDENT, sv->name, 1, 
					irFnodeCopy((yyvsp[(1) - (3)].y_fnode)->left),
					irFnodeCopy((yyvsp[(1) - (3)].y_fnode)->right));
				if (sv->type == IR_ENUM) {
					int size = ((IrEnum) sv->type_ptr)->size;
					if (sv->dim) {
						int i,j;
						irFlattenDim(sv->dim, &i, &j);
						eq = irFnodeAllLt(sv->name, i, j, size);
					} else {
						IrFnode snode = irFnodeCreate(IR_NUMBER, size, NULL, NULL);
						eq = irFnodeCreate(IR_LT, 0, vnode, snode);
					}
				} else {
					int token = (sv->type == IR_BOOL) ? IR_CMPEQ : IR_EQ;
					eq = irFnodeCreate(token, 0, vnode, NULL);
				}
				exprlist = irExprListCreate(eq, exprlist);
			}
			(yyval.y_exprlist) = exprlist;
			if (isSharedGlobal((yyvsp[(1) - (3)].y_fnode)->name)) shared_stmt = 1;
			irFnodeFree((yyvsp[(1) - (3)].y_fnode));
		} /* enum = undef */
		else if (var && var->type == IR_ENUM) {
			int size = ((IrEnum) var->type_ptr)->size;
			IrFnode fnode;
			if (var->dim) {
				int i,j;
				irFlattenDim(var->dim, &i, &j);
				fnode = irFnodeAllLt(var->name, i, j, size);
				irFnodeFree((yyvsp[(1) - (3)].y_fnode));
			} else {
				IrFnode snode = irFnodeCreate(IR_NUMBER, size, NULL, NULL);
				(yyvsp[(1) - (3)].y_fnode)->value = 1;
				fnode = irFnodeCreate(IR_LT, 0, (yyvsp[(1) - (3)].y_fnode), snode);
			}
			(yyval.y_exprlist) = irExprListCreate(fnode, NULL);
		} else {
			(yyvsp[(1) - (3)].y_fnode)->value = 1;
			(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_EQ, 0, (yyvsp[(1) - (3)].y_fnode), NULL), NULL);
			if (isSharedGlobal((yyvsp[(1) - (3)].y_fnode)->name)) shared_stmt = 1;
		}
	;}
    break;

  case 156:
#line 1288 "parse/irParse.y"
    {
		(yyvsp[(1) - (3)].y_fnode)->value = 1;
		(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_CMPEQ, 0, (yyvsp[(1) - (3)].y_fnode), NULL), NULL);
		if (isSharedGlobal((yyvsp[(1) - (3)].y_fnode)->name)) shared_stmt = 1;
	;}
    break;

  case 157:
#line 1293 "parse/irParse.y"
    {
		(yyvsp[(1) - (3)].y_fnode)->value = 1;
		(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_NE, 0, (yyvsp[(1) - (3)].y_fnode), (yyvsp[(3) - (3)].y_fnode)), NULL);
		if (isSharedGlobal((yyvsp[(1) - (3)].y_fnode)->name)) shared_stmt = 1;
	;}
    break;

  case 158:
#line 1298 "parse/irParse.y"
    {
		if ((yyvsp[(3) - (3)].y_exprlist)->next) irerror("parallel assignment inside quantification");
		(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_FORALL, 0, (yyvsp[(2) - (3)].y_fnode), (yyvsp[(3) - (3)].y_exprlist)->expr), NULL);
		IrQvar qvar = ir_qvar;
		ir_qvar = ir_qvar->next;
		Free(qvar);
	;}
    break;

  case 159:
#line 1305 "parse/irParse.y"
    {
		if ((yyvsp[(3) - (3)].y_exprlist)->next) irerror("parallel assignment inside quantification");
		(yyval.y_exprlist) = irExprListCreate(irFnodeCreate(IR_EXISTS, 0, (yyvsp[(2) - (3)].y_fnode), (yyvsp[(3) - (3)].y_exprlist)->expr), NULL);
		IrQvar qvar = ir_qvar;
		ir_qvar = ir_qvar->next;
		Free(qvar);
	;}
    break;

  case 160:
#line 1314 "parse/irParse.y"
    {
		if ((yyvsp[(4) - (5)].y_stmt)) {
			if ((yyvsp[(4) - (5)].y_stmt)->label && ((yyvsp[(4) - (5)].y_stmt)->label != (yyvsp[(1) - (5)].y_module)->name)) {
				(yyvsp[(4) - (5)].y_stmt) = irStmtCreate(IR_SKIP, 0, NULL, (yyvsp[(4) - (5)].y_stmt));
			}
			(yyvsp[(4) - (5)].y_stmt)->label = (yyvsp[(1) - (5)].y_module)->name;
			(yyvsp[(1) - (5)].y_module)->first_stmt = (yyvsp[(4) - (5)].y_stmt);
			IrStmt last_stmt;
			for (last_stmt = (yyvsp[(4) - (5)].y_stmt); last_stmt->next; last_stmt = last_stmt->next)
				;
			
			/* implicit return */
			if ((current_module->retvar->type == IR_VOID)
					&& (last_stmt->type != IR_RET)) {
				IrStmt ret_stmt = irStmtCreate(IR_RET, 0, NULL, NULL);
				last_stmt->next = ret_stmt;
				last_stmt = ret_stmt;
			}
			(yyvsp[(1) - (5)].y_module)->last_stmt = last_stmt;

			/* if the last statement is not a return statment*/
			if (!irIsReturnInside(last_stmt)) {
				irerror("return statement expected");
			}
		} else if (current_module->retvar->type == IR_VOID) {
			(yyvsp[(4) - (5)].y_stmt) = irStmtCreate(IR_RET, (yyvsp[(1) - (5)].y_module)->name, NULL, NULL);
			(yyvsp[(1) - (5)].y_module)->first_stmt = (yyvsp[(4) - (5)].y_stmt);
			(yyvsp[(1) - (5)].y_module)->last_stmt = (yyvsp[(4) - (5)].y_stmt);
		}
		(yyval.y_stmt) = (yyvsp[(4) - (5)].y_stmt);
		
		current_module = NULL; //current_module->next;
	;}
    break;

  case 161:
#line 1349 "parse/irParse.y"
    {
		if((yyvsp[(3) - (6)].name)==wIdentCreate((char*)"main")) main_found=1;
		
		if((yyvsp[(3) - (6)].name)==wIdentCreate((char*)"main") && (yyvsp[(5) - (6)].y_varlist)) irerror("Main cannot have arguments");
		
		IrModule module;
		
		for (module = ir_module; module; module = module->next) {
			if (module->name == (yyvsp[(3) - (6)].name))
				break;
		}
		
		if (!module) {
			module = irModuleCreate((yyvsp[(3) - (6)].name), (yyvsp[(2) - (6)].y_var), (yyvsp[(5) - (6)].y_varlist));
			module->next = ir_module;
			ir_module = module;
		}
		(yyval.y_module) = module;
		
		current_module = module;
		
	;}
    break;

  case 163:
#line 1374 "parse/irParse.y"
    {
		IrVarList vl;
		for (vl = (yyvsp[(2) - (2)].y_varlist); vl->next; vl = vl->next) 
			;	
		vl->next = current_module->localvar;
		current_module->localvar = (yyvsp[(2) - (2)].y_varlist);
	  ;}
    break;

  case 164:
#line 1385 "parse/irParse.y"
    { 
		(yyval.y_var) = irVarTypeCreate(IR_VOID);
	;}
    break;

  case 165:
#line 1388 "parse/irParse.y"
    { 
		(yyval.y_var) = irVarTypeCreate(IR_BOOL);
		(yyval.y_var)->dim = (yyvsp[(2) - (2)].y_dim);
	;}
    break;

  case 166:
#line 1392 "parse/irParse.y"
    { 
		(yyval.y_var) = irVarTypeCreate(IR_INT);
		(yyval.y_var)->dim = (yyvsp[(2) - (3)].y_dim);
		if ((yyvsp[(3) - (3)].integer)) (yyval.y_var)->bits = (yyvsp[(3) - (3)].integer);
		else if (int_bits) (yyval.y_var)->bits = int_bits;
		else irerror("unspecified integer range");
	;}
    break;

  case 167:
#line 1399 "parse/irParse.y"
    { 
		irerror("current implementation does not support signed int");
		(yyval.y_var) = irVarTypeCreate(IR_SGNINT);
		(yyval.y_var)->dim = (yyvsp[(2) - (3)].y_dim);
		if ((yyvsp[(3) - (3)].integer)) (yyval.y_var)->bits = (yyvsp[(3) - (3)].integer); 
		else if (sgnint_bits) (yyval.y_var)->bits = sgnint_bits;
		else irerror("unspecified integer range");
	;}
    break;

  case 168:
#line 1407 "parse/irParse.y"
    { 
		(yyval.y_var) = irVarTypeCreate(IR_ENUM);
		IrEnum e;
		for (e = ir_enum; e; e = e->next)
			if (e->name == (yyvsp[(2) - (3)].name))
				break;
		if (!e)
			irerror("invalid enum type");
		
		(yyval.y_var)->type_ptr = e;
		(yyval.y_var)->bits = e->bits;
		(yyval.y_var)->dim = (yyvsp[(3) - (3)].y_dim);
	;}
    break;

  case 169:
#line 1420 "parse/irParse.y"
    { 
		(yyval.y_var) = irVarTypeCreate(IR_STRUCT);
		IrStruct s;
		for (s = ir_struct; s; s = s->next)
			if (s->name == (yyvsp[(2) - (3)].name))
				break;
		if (s)
			(yyval.y_var)->type_ptr = s;
		else
			irerror("invalid struct type");

		if ((yyvsp[(3) - (3)].y_dim)) {
			IrVarList f = s->fields;
			for (; f; f = f->next)
				if (f->var->dim)
					irerror("struct cannot keep an array as member data");
			(yyval.y_var)->dim = (yyvsp[(3) - (3)].y_dim);
		}
	;}
    break;

  case 170:
#line 1441 "parse/irParse.y"
    { (yyval.y_varlist) = NULL; ;}
    break;

  case 171:
#line 1442 "parse/irParse.y"
    { (yyval.y_varlist) = (yyvsp[(1) - (1)].y_varlist); ;}
    break;

  case 172:
#line 1445 "parse/irParse.y"
    {
		(yyval.y_varlist) = irVarListCreate((yyvsp[(1) - (1)].y_var), NULL);
	;}
    break;

  case 173:
#line 1448 "parse/irParse.y"
    {
		(yyval.y_varlist) = irVarListCreate((yyvsp[(1) - (3)].y_var), (yyvsp[(3) - (3)].y_varlist));
	;}
    break;

  case 174:
#line 1453 "parse/irParse.y"
    {
		if (irVarGetUnformatted((yyvsp[(2) - (2)].y_var)->name, NULL, NULL))
			irerror("two variables have the same name");
		(yyvsp[(2) - (2)].y_var)->type = IR_BOOL;
		(yyval.y_var) = (yyvsp[(2) - (2)].y_var);
	;}
    break;

  case 175:
#line 1459 "parse/irParse.y"
    {
		if (irVarGetUnformatted((yyvsp[(2) - (2)].y_var)->name, NULL, NULL))
			irerror("two variables have the same name");
		(yyvsp[(2) - (2)].y_var)->type = IR_INT;
		if (!(yyvsp[(2) - (2)].y_var)->bits) {
			if (!int_bits)
				irerror("unspecified integer range");
			else
				(yyvsp[(2) - (2)].y_var)->bits = int_bits;
		}
		(yyval.y_var) = (yyvsp[(2) - (2)].y_var);
	;}
    break;

  case 176:
#line 1471 "parse/irParse.y"
    {
		irerror("current implementation does not support signed int");
		if (irVarGetUnformatted((yyvsp[(2) - (2)].y_var)->name, NULL, NULL))
			irerror("two variables have the same name");
		(yyvsp[(2) - (2)].y_var)->type = IR_SGNINT;
		if (!(yyvsp[(2) - (2)].y_var)->bits) {
			if (!sgnint_bits)
				irerror("unspecified integer range");
			else
				(yyvsp[(2) - (2)].y_var)->bits = sgnint_bits;
		}
		(yyval.y_var) = (yyvsp[(2) - (2)].y_var);
	;}
    break;

  case 177:
#line 1484 "parse/irParse.y"
    {
		if (irVarGetUnformatted((yyvsp[(3) - (3)].y_var)->name, NULL, NULL))
			irerror("two variables have the same name");
		(yyvsp[(3) - (3)].y_var)->type = IR_ENUM;
		IrEnum e;
		for (e = ir_enum; e; e = e->next)
			if (e->name == (yyvsp[(2) - (3)].name))
				break;
		if (!e)
			irerror("invalid enum type");
		else
			(yyvsp[(3) - (3)].y_var)->type_ptr = e;
		(yyval.y_var) = (yyvsp[(3) - (3)].y_var);
	;}
    break;

  case 178:
#line 1498 "parse/irParse.y"
    {
		if (irVarGetUnformatted((yyvsp[(3) - (3)].y_var)->name, NULL, NULL))
			irerror("two variables have the same name");
		(yyvsp[(3) - (3)].y_var)->type = IR_STRUCT;
		IrStruct s;
		for (s = ir_struct; s; s = s->next)
			if (s->name == (yyvsp[(2) - (3)].name))
				break;
		if (!s)
			irerror("invalid struct type");
		else
			(yyvsp[(3) - (3)].y_var)->type_ptr = s;
		
		irAddStructVar((yyvsp[(3) - (3)].y_var));
		(yyval.y_var) = (yyvsp[(3) - (3)].y_var);
	;}
    break;


/* Line 1267 of yacc.c.  */
#line 3725 "parse/irParse.c"
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


#line 1516 "parse/irParse.y"


#include "irLex.c"

void irerror (char *info) { 
	printf("\nsyntax error in Remopla: %s, line %d\n",
		info, irlinenumber);
	irFree();
	finish_ir();
	exit(1);
}

void irParse (char *filename) {
	if (!(irin = fopen(filename,"r"))) {
		fprintf(stderr,"modelfile %s not found\n", filename);
		exit(1);
	}

	if (irparse())
		printf("parse errors encountered while reading input\n");

	fclose(irin);
}

//This is a comment !

