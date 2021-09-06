/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.y"

#include "scanner.h"//se importa el header del analisis sintactico
#include <QString>
#include <string>
#include "qdebug.h"
#include <iostream>

#include "obmkdisk.h"
obmkdisk * mdisk;

#include "obrmdisk.h"
obrmdisk * rmdisk;

#include "obfdisk.h"
obfdisk * fdisk;

#include "obmount.h"
obmount * mount;

#include "obumount.h"
obumount * umount;

#include "obmkfs.h"
obmkfs * mkfs;

#include "obtouch.h"
obtouch * touch;

#include "obmkdir.h"
obmkdir * mkdir;

#include "obreporte.h"
obreporte * reporte;

#include "obcat.h"
obcat * cat;

#include "obren.h"
obren * ren;

#include "obrm.h"
obrm * rm;

#include "obedit.h"
obedit * edit;

#include "obexec.h"
obexec * exec;

#include "obmv.h"
obmv * mv;

#include "obcp.h"
obcp * cp;

#include "obfind.h"
obfind * finds;

#include "oblogin.h"
oblogin * login;

#include "oblogout.h"
oblogout * logout;

#include "obmkgrp.h"
obmkgrp * mkgrp;

#include "obrmgrp.h"
obrmgrp * rmgrp;

#include "obmkusr.h"
obmkusr * mkusr;

#include "obrmusr.h"
obrmusr * rmusr;

#include "obchgrp.h"
obchgrp * chgrp;

#include "obloss.h"
obloss * loss;

#include "obrecovery.h"
obrecovery * reco;

using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

int yyerror(const char* mens)
{
std::cout << mens <<" "<<yytext<< std::endl;
return 0;
}

#line 167 "parser.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MKDISK = 258,
    RMDISK = 259,
    FDISK = 260,
    MOUNT = 261,
    UMOUNT = 262,
    MKFS = 263,
    TOUCH = 264,
    MKDIR = 265,
    REP = 266,
    CAT = 267,
    REN = 268,
    RM = 269,
    EDIT = 270,
    EXEC = 271,
    PAUSE = 272,
    MV = 273,
    CP = 274,
    FIND = 275,
    LOGIN = 276,
    LOGOUT = 277,
    MKGRP = 278,
    RMGRP = 279,
    MKUSR = 280,
    RMUSR = 281,
    CHGRP = 282,
    LOSS = 283,
    RECO = 284,
    SIZE = 285,
    PATH = 286,
    TYPE = 287,
    NAME = 288,
    ADD = 289,
    DELETE = 290,
    ID = 291,
    FS = 292,
    CONT = 293,
    STDIN = 294,
    RUTAS = 295,
    ROOT = 296,
    DEST = 297,
    USER = 298,
    PWD = 299,
    USR = 300,
    GRP = 301,
    letF = 302,
    letU = 303,
    letR = 304,
    IGUAL = 305,
    MENOS = 306,
    POSITIVO = 307,
    RUTA = 308,
    LETRA = 309,
    CADENA = 310,
    IDENTIFICADOR = 311,
    IDMOUNT = 312,
    IDFS = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 101 "parser.y"

//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];


#line 286 "parser.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   370

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  76
/* YYNRULES -- Number of rules.  */
#define YYNRULES  210
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  371

#define YYUNDEFTOK  2
#define YYMAXUTOK   313


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   183,   183,   187,   188,   191,   191,   192,   192,   193,
     193,   194,   194,   195,   195,   196,   196,   197,   197,   198,
     198,   199,   199,   200,   200,   201,   201,   202,   202,   203,
     203,   204,   204,   205,   205,   206,   206,   207,   207,   208,
     208,   209,   210,   210,   211,   211,   212,   212,   213,   213,
     214,   214,   215,   215,   216,   216,   217,   221,   222,   226,
     227,   228,   229,   230,   234,   235,   239,   240,   244,   245,
     246,   247,   248,   249,   250,   251,   252,   253,   254,   258,
     259,   263,   264,   265,   266,   270,   271,   275,   276,   280,
     281,   282,   283,   287,   288,   292,   293,   294,   295,   296,
     297,   298,   302,   303,   307,   308,   309,   313,   314,   318,
     319,   320,   321,   322,   323,   324,   325,   326,   330,   331,
     335,   336,   340,   341,   345,   346,   347,   348,   352,   353,
     357,   358,   362,   363,   367,   368,   369,   370,   371,   375,
     376,   380,   381,   385,   386,   387,   388,   392,   393,   397,
     398,   399,   400,   404,   405,   409,   410,   411,   412,   416,
     417,   421,   422,   423,   424,   425,   426,   427,   428,   432,
     433,   437,   438,   439,   443,   444,   448,   449,   450,   454,
     455,   459,   460,   461,   462,   463,   464,   465,   466,   467,
     471,   472,   476,   477,   478,   482,   483,   487,   488,   489,
     490,   491,   492,   496,   497,   501,   502,   506,   507,   511,
     512
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MKDISK", "RMDISK", "FDISK", "MOUNT",
  "UMOUNT", "MKFS", "TOUCH", "MKDIR", "REP", "CAT", "REN", "RM", "EDIT",
  "EXEC", "PAUSE", "MV", "CP", "FIND", "LOGIN", "LOGOUT", "MKGRP", "RMGRP",
  "MKUSR", "RMUSR", "CHGRP", "LOSS", "RECO", "SIZE", "PATH", "TYPE",
  "NAME", "ADD", "DELETE", "ID", "FS", "CONT", "STDIN", "RUTAS", "ROOT",
  "DEST", "USER", "PWD", "USR", "GRP", "letF", "letU", "letR", "IGUAL",
  "MENOS", "POSITIVO", "RUTA", "LETRA", "CADENA", "IDENTIFICADOR",
  "IDMOUNT", "IDFS", "$accept", "INICIO", "INSTRUCCIONES", "INSTRUCCION",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "$@15", "$@16", "$@17", "$@18", "$@19",
  "$@20", "$@21", "$@22", "$@23", "$@24", "$@25", "COMANDOMKDISK",
  "PARMKDISK", "COMANDORMDISK", "COMANDOFDISK", "PARFDISK", "COMANDOMOUNT",
  "PARMOUNT", "COMANDOUMOUNT", "COMANDOMKFS", "PARMKFS", "COMANDOTOUCH",
  "PARTOUCH", "COMANDOMKDIR", "PARMKDIR", "COMANDOREPORTE", "PARREP",
  "COMANDOCAT", "PARCAT", "COMANDOREN", "PARREN", "COMANDORM", "PARRM",
  "COMANDOEDIT", "PAREDIT", "COMANDOEXEC", "COMANDOMV", "PARMV",
  "COMANDOCP", "PARCP", "COMANDOFIND", "PARFIND", "COMANDOLOGIN",
  "PARLOGIN", "COMANDOMKGRP", "PARMKGRP", "COMANDORMGRP", "PARRMGRP",
  "COMANDOMKUSR", "PARMKUSR", "COMANDORMUSR", "PARRMUSR", "COMANDOCHGRP",
  "PARCHGRP", "COMANDOLOSS", "PARLOSS", "COMANDORECO", "PARRECO", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF (-12)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -3,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,    34,    -3,
     -12,    24,   117,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   -12,   -12,     1,    24,
     -12,    32,   -12,     8,   124,   -12,     2,   125,   -12,   122,
     -12,    51,   127,   -12,    -2,   128,   -12,    -4,   129,   -12,
      49,   130,   -12,    40,   131,   -12,    74,   132,   -12,   167,
     133,   -12,    53,   134,   -12,   168,   -12,    27,   136,   -12,
      39,   137,   -12,    75,   138,   -12,    50,   139,   -12,   169,
     140,   -12,   170,   141,   -12,    58,   142,   -12,   155,   143,
     -12,   115,   144,   -12,   165,   145,   -12,   171,   146,   -12,
     154,   156,   158,   159,   -12,   160,   161,   162,   163,   164,
     166,   172,   173,   174,   -12,   175,   176,   -12,   177,   178,
     179,   180,   -12,   181,   182,   183,   -12,   -12,   -12,   184,
     -12,   -12,   185,   186,   187,   188,   189,   -12,   190,   -12,
     191,   192,   -12,   193,   -12,   194,   195,   -12,   -12,   196,
     197,   198,   -12,   199,   200,   -12,   201,   202,   -12,   203,
     204,   205,   -12,   206,   -12,   207,   -12,   208,   209,   210,
     -12,   211,   -12,   212,   213,   -12,   214,   -12,   215,   -12,
     153,    -1,   216,   217,    56,   218,    57,   219,   107,   113,
     220,   221,   224,    60,   111,    59,   223,    62,   157,   222,
      65,    68,    69,    72,   114,    71,    76,   228,    77,    80,
     116,    81,    84,    85,    88,    89,    92,    93,    96,    97,
     118,    98,   -11,    43,     5,    10,    45,    12,    16,    18,
      21,    23,    99,   102,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   229,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     5,     7,     9,    11,    13,    15,    17,    19,    21,
      23,    25,    27,    29,    31,    56,    33,    35,    37,    39,
      41,    42,    44,    46,    48,    50,    52,    54,     0,     2,
       4,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     1,     3,     0,     6,
      58,     0,     8,     0,    10,    67,     0,    12,    80,     0,
      14,     0,    16,    88,     0,    18,    94,     0,    20,   103,
       0,    22,   108,     0,    24,   119,     0,    26,   123,     0,
      28,   129,     0,    30,   133,     0,    32,     0,    34,   142,
       0,    36,   148,     0,    38,   154,     0,    40,   160,     0,
      43,   170,     0,    45,   175,     0,    47,   180,     0,    49,
     191,     0,    51,   196,     0,    53,   204,     0,    55,   208,
       0,     0,     0,     0,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,     0,     0,    79,     0,     0,
       0,     0,    87,     0,     0,     0,   101,   100,    93,     0,
     106,   102,     0,     0,     0,     0,     0,   107,     0,   118,
       0,     0,   122,     0,   128,     0,     0,   138,   132,     0,
       0,     0,   141,     0,     0,   147,     0,     0,   153,     0,
       0,     0,   159,     0,   169,     0,   174,     0,     0,     0,
     179,     0,   190,     0,     0,   195,     0,   203,     0,   207,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    59,    60,    61,    63,    62,    64,
      65,    68,    69,    70,    73,    74,    75,     0,    76,    78,
      72,    71,    81,    82,    83,    84,    86,    85,    91,    90,
      89,    92,    99,    95,    96,    97,    98,   104,   105,   109,
     110,   113,   114,   111,   112,   116,   115,   117,   120,   121,
     124,   125,   127,   126,   130,   131,   134,   135,   136,   137,
     139,   140,   143,   144,   145,   146,   149,   150,   151,   152,
     155,   156,   158,   157,   168,   167,   163,   162,   161,   165,
     166,   164,   173,   172,   171,   178,   177,   176,   186,   185,
     184,   183,   182,   181,   189,   187,   188,   194,   193,   192,
     199,   198,   197,   202,   200,   201,   206,   205,   210,   209,
      77
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -12,   -12,   -12,   237,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,   -12,
     225,   -12,   -12,   226,   -12,   150,   -12,   -12,   147,   -12,
     227,   -12,   230,   -12,   231,   -12,   232,   -12,   233,   -12,
     234,   -12,   235,   -12,   -12,   120,   -12,   119,   -12,   236,
     -12,   238,   -12,   239,   -12,   108,   -12,   151,   -12,   149,
     -12,   240,   -12,   241,   -12,   242
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    59,
      60,    62,    64,    65,    67,    68,    70,    72,    73,    75,
      76,    78,    79,    81,    82,    84,    85,    87,    88,    90,
      91,    93,    94,    96,    98,    99,   101,   102,   104,   105,
     107,   108,   110,   111,   113,   114,   116,   117,   119,   120,
     122,   123,   125,   126,   128,   129
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       1,     2,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,   159,   153,   154,
     336,   130,   131,   145,    56,   146,   155,   156,   136,   137,
     138,   139,   140,   141,   337,   338,   342,   157,   132,   133,
     160,   345,   265,   351,   266,   142,   143,   354,   180,   357,
     343,   344,   360,   135,   363,   346,   347,   352,   353,   181,
     183,   355,   356,   358,   359,    58,   361,   362,   364,   365,
     162,   184,   163,   149,   175,   164,   189,   150,   151,   165,
     166,   176,   177,   190,   191,   339,   168,   348,   340,   341,
     349,   350,   197,   198,   199,   170,   186,   171,   187,   269,
     272,   270,   273,   282,   286,   283,   287,   289,   293,   290,
     294,   295,   297,   296,   298,   299,   303,   300,   304,   305,
     308,   306,   309,   310,   314,   311,   315,   316,   318,   317,
     319,   320,   322,   321,   323,   324,   326,   325,   327,   328,
     330,   329,   331,   334,   366,   335,   367,   368,   148,   369,
     203,   204,   275,   276,   277,   278,   284,   285,    61,   301,
     302,   312,   313,   332,   333,    63,    66,    69,    71,    74,
      77,    80,    83,    86,    89,    92,    95,    97,   100,   103,
     106,   109,   112,   115,   118,   121,   124,   127,   173,   179,
     201,   206,   193,   195,   210,   264,   211,   208,   212,   213,
     214,   215,   216,   217,   218,   291,   219,   147,   182,   152,
     185,   196,   220,   221,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   260,   261,   262,   263,    57,   200,   202,     0,
     271,   268,   267,   274,   292,     0,   279,   280,   281,   288,
     307,   370,     0,     0,   134,     0,     0,     0,     0,     0,
     144,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   158,     0,     0,     0,     0,     0,   161,     0,
       0,     0,   167,     0,     0,     0,   169,     0,     0,     0,
     172,     0,     0,     0,   174,     0,     0,     0,   178,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     188,     0,     0,     0,     0,   192,     0,     0,     0,   194,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   205,     0,     0,     0,   207,     0,     0,     0,
     209
};

static const yytype_int16 yycheck[] =
{
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    31,    30,    31,
      41,    30,    31,    31,     0,    33,    38,    39,    30,    31,
      32,    33,    34,    35,    55,    56,    41,    49,    47,    48,
      54,    41,    53,    41,    55,    47,    48,    41,    31,    41,
      55,    56,    41,    31,    41,    55,    56,    55,    56,    42,
      31,    55,    56,    55,    56,    51,    55,    56,    55,    56,
      31,    42,    33,    32,    31,    36,    36,    36,    37,    40,
      41,    38,    39,    43,    44,    52,    56,    52,    55,    56,
      55,    56,    44,    45,    46,    31,    31,    33,    33,    53,
      53,    55,    55,    53,    55,    55,    57,    55,    53,    57,
      55,    53,    53,    55,    55,    53,    55,    55,    57,    53,
      53,    55,    55,    53,    53,    55,    55,    53,    53,    55,
      55,    53,    53,    55,    55,    53,    53,    55,    55,    53,
      53,    55,    55,    55,    55,    57,    57,    55,    36,    57,
      45,    46,    55,    56,    51,    52,    55,    56,    51,    55,
      56,    55,    56,    55,    56,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    31,    31,
      45,    36,    33,    33,    50,    52,    50,    36,    50,    50,
      50,    50,    50,    50,    50,    58,    50,    67,    98,    72,
     101,   113,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    29,   116,   119,    -1,
      52,    54,    56,    54,    52,    -1,    56,    56,    54,    56,
      52,    52,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    -1,    -1,    -1,    -1,    -1,    78,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    84,    -1,    -1,    -1,
      87,    -1,    -1,    -1,    90,    -1,    -1,    -1,    93,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     104,    -1,    -1,    -1,    -1,   107,    -1,    -1,    -1,   110,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   122,    -1,    -1,    -1,   125,    -1,    -1,    -1,
     128
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,     0,    62,    51,    88,
      89,    51,    90,    51,    91,    92,    51,    93,    94,    51,
      95,    51,    96,    97,    51,    98,    99,    51,   100,   101,
      51,   102,   103,    51,   104,   105,    51,   106,   107,    51,
     108,   109,    51,   110,   111,    51,   112,    51,   113,   114,
      51,   115,   116,    51,   117,   118,    51,   119,   120,    51,
     121,   122,    51,   123,   124,    51,   125,   126,    51,   127,
     128,    51,   129,   130,    51,   131,   132,    51,   133,   134,
      30,    31,    47,    48,    89,    31,    30,    31,    32,    33,
      34,    35,    47,    48,    92,    31,    33,    94,    36,    32,
      36,    37,    97,    30,    31,    38,    39,    49,    99,    31,
      54,   101,    31,    33,    36,    40,    41,   103,    56,   105,
      31,    33,   107,    31,   109,    31,    38,    39,   111,    31,
      31,    42,   114,    31,    42,   116,    31,    33,   118,    36,
      43,    44,   120,    33,   122,    33,   124,    44,    45,    46,
     126,    45,   128,    45,    46,   130,    36,   132,    36,   134,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    52,    53,    55,    56,    54,    53,
      55,    52,    53,    55,    54,    55,    56,    51,    52,    56,
      56,    54,    53,    55,    55,    56,    55,    57,    56,    55,
      57,    58,    52,    53,    55,    53,    55,    53,    55,    53,
      55,    55,    56,    55,    57,    53,    55,    52,    53,    55,
      53,    55,    55,    56,    53,    55,    53,    55,    53,    55,
      53,    55,    53,    55,    53,    55,    53,    55,    53,    55,
      53,    55,    55,    56,    55,    57,    41,    55,    56,    52,
      55,    56,    41,    55,    56,    41,    55,    56,    52,    55,
      56,    41,    55,    56,    41,    55,    56,    41,    55,    56,
      41,    55,    56,    41,    55,    56,    55,    57,    55,    57,
      52
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    61,    63,    62,    64,    62,    65,
      62,    66,    62,    67,    62,    68,    62,    69,    62,    70,
      62,    71,    62,    72,    62,    73,    62,    74,    62,    75,
      62,    76,    62,    77,    62,    78,    62,    79,    62,    80,
      62,    62,    81,    62,    82,    62,    83,    62,    84,    62,
      85,    62,    86,    62,    87,    62,    62,    88,    88,    89,
      89,    89,    89,    89,    90,    90,    91,    91,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      93,    94,    94,    94,    94,    95,    95,    96,    96,    97,
      97,    97,    97,    98,    98,    99,    99,    99,    99,    99,
      99,    99,   100,   100,   101,   101,   101,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     105,   105,   106,   106,   107,   107,   107,   107,   108,   108,
     109,   109,   110,   110,   111,   111,   111,   111,   111,   112,
     112,   113,   113,   114,   114,   114,   114,   115,   115,   116,
     116,   116,   116,   117,   117,   118,   118,   118,   118,   119,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   122,   122,   122,   123,   123,   124,   124,   124,   125,
     125,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     127,   127,   128,   128,   128,   129,   129,   130,   130,   130,
     130,   130,   130,   131,   131,   132,   132,   133,   133,   134,
     134
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     1,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     1,     2,     1,     4,
       4,     4,     4,     4,     4,     4,     2,     1,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     5,     4,     2,
       1,     4,     4,     4,     4,     4,     4,     2,     1,     4,
       4,     4,     4,     2,     1,     4,     4,     4,     4,     4,
       2,     2,     2,     1,     4,     4,     2,     2,     1,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     2,     1,
       4,     4,     2,     1,     4,     4,     4,     4,     2,     1,
       4,     4,     2,     1,     4,     4,     4,     4,     2,     4,
       4,     2,     1,     4,     4,     4,     4,     2,     1,     4,
       4,     4,     4,     2,     1,     4,     4,     4,     4,     2,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     2,
       1,     4,     4,     4,     2,     1,     4,     4,     4,     2,
       1,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       2,     1,     4,     4,     4,     2,     1,     4,     4,     4,
       4,     4,     4,     2,     1,     4,     4,     2,     1,     4,
       4
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 183 "parser.y"
                  {  }
#line 1851 "parser.cpp"
    break;

  case 3:
#line 187 "parser.y"
                                    {  }
#line 1857 "parser.cpp"
    break;

  case 4:
#line 188 "parser.y"
                                    {  }
#line 1863 "parser.cpp"
    break;

  case 5:
#line 191 "parser.y"
             { mdisk = new obmkdisk();   /*objeto mkdisk*/}
#line 1869 "parser.cpp"
    break;

  case 6:
#line 191 "parser.y"
                                                                           { mdisk->exec();  /*ejecutar mkdisk*/}
#line 1875 "parser.cpp"
    break;

  case 7:
#line 192 "parser.y"
             { rmdisk = new obrmdisk();  /*objeto rmdisk*/}
#line 1881 "parser.cpp"
    break;

  case 8:
#line 192 "parser.y"
                                                                           { rmdisk->exec(); /*ejecutar rmdisk*/}
#line 1887 "parser.cpp"
    break;

  case 9:
#line 193 "parser.y"
             { fdisk = new obfdisk();    /*objeto fdisk*/ }
#line 1893 "parser.cpp"
    break;

  case 10:
#line 193 "parser.y"
                                                                           { fdisk->exec();  /*ejecutar fdisk*/ }
#line 1899 "parser.cpp"
    break;

  case 11:
#line 194 "parser.y"
             { mount = new obmount();    /*objeto mount*/ }
#line 1905 "parser.cpp"
    break;

  case 12:
#line 194 "parser.y"
                                                                           { mount->exec();  /*ejecutar mount*/ }
#line 1911 "parser.cpp"
    break;

  case 13:
#line 195 "parser.y"
             { umount = new obumount();  /*objeto umount*/}
#line 1917 "parser.cpp"
    break;

  case 14:
#line 195 "parser.y"
                                                                           { umount->exec(); /*ejecutar umount*/}
#line 1923 "parser.cpp"
    break;

  case 15:
#line 196 "parser.y"
             { mkfs = new obmkfs();        /*objeto mkfs*/}
#line 1929 "parser.cpp"
    break;

  case 16:
#line 196 "parser.y"
                                                                           { mkfs->exec();     /*ejecutar mkfs*/}
#line 1935 "parser.cpp"
    break;

  case 17:
#line 197 "parser.y"
             { touch = new obtouch();     /*objeto touch*/}
#line 1941 "parser.cpp"
    break;

  case 18:
#line 197 "parser.y"
                                                                           { touch->exec();   /*ejecutar touch*/}
#line 1947 "parser.cpp"
    break;

  case 19:
#line 198 "parser.y"
             { mkdir = new obmkdir();     /*objeto mkdir*/}
#line 1953 "parser.cpp"
    break;

  case 20:
#line 198 "parser.y"
                                                                           { mkdir->exec();   /*ejecutar mkdir*/}
#line 1959 "parser.cpp"
    break;

  case 21:
#line 199 "parser.y"
             { reporte = new obreporte();   /*objeto rep*/}
#line 1965 "parser.cpp"
    break;

  case 22:
#line 199 "parser.y"
                                                                           { reporte->exec();   /*ejecutar rep*/}
#line 1971 "parser.cpp"
    break;

  case 23:
#line 200 "parser.y"
             { cat = new obcat();           /*objeto cat*/}
#line 1977 "parser.cpp"
    break;

  case 24:
#line 200 "parser.y"
                                                                           { cat->exec();       /*ejecutar cat*/}
#line 1983 "parser.cpp"
    break;

  case 25:
#line 201 "parser.y"
             { ren = new obren();           /*objeto ren*/}
#line 1989 "parser.cpp"
    break;

  case 26:
#line 201 "parser.y"
                                                                           { ren->exec();       /*ejecutar ren*/}
#line 1995 "parser.cpp"
    break;

  case 27:
#line 202 "parser.y"
             { rm = new obrm();              /*objeto rm*/}
#line 2001 "parser.cpp"
    break;

  case 28:
#line 202 "parser.y"
                                                                           { rm->exec();         /*ejecutar rm*/}
#line 2007 "parser.cpp"
    break;

  case 29:
#line 203 "parser.y"
             { edit = new obedit();        /*objeto edit*/}
#line 2013 "parser.cpp"
    break;

  case 30:
#line 203 "parser.y"
                                                                           { edit->exec();     /*ejecutar edit*/}
#line 2019 "parser.cpp"
    break;

  case 31:
#line 204 "parser.y"
             { exec = new obexec();        /*objeto exec*/}
#line 2025 "parser.cpp"
    break;

  case 32:
#line 204 "parser.y"
                                                                           { exec->exec();     /*ejecutar exec*/}
#line 2031 "parser.cpp"
    break;

  case 33:
#line 205 "parser.y"
             { mv = new obmv();              /*objeto mv*/}
#line 2037 "parser.cpp"
    break;

  case 34:
#line 205 "parser.y"
                                                                           { mv->exec();         /*ejecutar mv*/}
#line 2043 "parser.cpp"
    break;

  case 35:
#line 206 "parser.y"
             { cp = new obcp();              /*objeto cp*/}
#line 2049 "parser.cpp"
    break;

  case 36:
#line 206 "parser.y"
                                                                           { cp->exec();         /*ejecutar cp*/}
#line 2055 "parser.cpp"
    break;

  case 37:
#line 207 "parser.y"
             { finds = new obfind();       /*objeto find*/}
#line 2061 "parser.cpp"
    break;

  case 38:
#line 207 "parser.y"
                                                                           { finds->exec();    /*ejecutar find*/}
#line 2067 "parser.cpp"
    break;

  case 39:
#line 208 "parser.y"
             { login = new oblogin();     /*objeto login*/}
#line 2073 "parser.cpp"
    break;

  case 40:
#line 208 "parser.y"
                                                                           { login->exec();   /*ejecutar login*/}
#line 2079 "parser.cpp"
    break;

  case 41:
#line 209 "parser.y"
             { logout = new oblogout();                                      logout->exec();    /*objeto login*/}
#line 2085 "parser.cpp"
    break;

  case 42:
#line 210 "parser.y"
             { mkgrp = new obmkgrp();     /*objeto mkgrp*/}
#line 2091 "parser.cpp"
    break;

  case 43:
#line 210 "parser.y"
                                                                           { mkgrp->exec();   /*ejecutar mkgrp*/}
#line 2097 "parser.cpp"
    break;

  case 44:
#line 211 "parser.y"
             { rmgrp = new obrmgrp();     /*objeto rmgrp*/}
#line 2103 "parser.cpp"
    break;

  case 45:
#line 211 "parser.y"
                                                                           { rmgrp->exec();   /*ejecutar rmgrp*/}
#line 2109 "parser.cpp"
    break;

  case 46:
#line 212 "parser.y"
             { mkusr = new obmkusr();     /*objeto mkusr*/}
#line 2115 "parser.cpp"
    break;

  case 47:
#line 212 "parser.y"
                                                                           { mkusr->exec();   /*ejecutar mkusr*/}
#line 2121 "parser.cpp"
    break;

  case 48:
#line 213 "parser.y"
             { rmusr = new obrmusr();     /*objeto rmusr*/}
#line 2127 "parser.cpp"
    break;

  case 49:
#line 213 "parser.y"
                                                                           { rmusr->exec();   /*ejecutar rmusr*/}
#line 2133 "parser.cpp"
    break;

  case 50:
#line 214 "parser.y"
             { chgrp = new obchgrp();     /*objeto chgrp*/}
#line 2139 "parser.cpp"
    break;

  case 51:
#line 214 "parser.y"
                                                                           { chgrp->exec();   /*ejecutar chgrp*/}
#line 2145 "parser.cpp"
    break;

  case 52:
#line 215 "parser.y"
             { loss = new obloss();        /*objeto loss*/}
#line 2151 "parser.cpp"
    break;

  case 53:
#line 215 "parser.y"
                                                                           { loss->exec();     /*ejecutar loss*/}
#line 2157 "parser.cpp"
    break;

  case 54:
#line 216 "parser.y"
             { reco = new obrecovery();/*objeto recovery*/}
#line 2163 "parser.cpp"
    break;

  case 55:
#line 216 "parser.y"
                                                                           { reco->exec(); /*ejecutar recovery*/}
#line 2169 "parser.cpp"
    break;

  case 56:
#line 217 "parser.y"
             { system("read -p 'Presss <ENTER> to continue...' var"); }
#line 2175 "parser.cpp"
    break;

  case 57:
#line 221 "parser.y"
                                  {  }
#line 2181 "parser.cpp"
    break;

  case 58:
#line 222 "parser.y"
                                  {  }
#line 2187 "parser.cpp"
    break;

  case 59:
#line 226 "parser.y"
                                      { mdisk->setSize(atoi((yyvsp[0].TEXT))); }
#line 2193 "parser.cpp"
    break;

  case 60:
#line 227 "parser.y"
                                      { mdisk->setPath((yyvsp[0].TEXT)); }
#line 2199 "parser.cpp"
    break;

  case 61:
#line 228 "parser.y"
                                      { mdisk->setPath((yyvsp[0].TEXT)); }
#line 2205 "parser.cpp"
    break;

  case 62:
#line 229 "parser.y"
                                      { mdisk->setUnit((yyvsp[0].TEXT)); }
#line 2211 "parser.cpp"
    break;

  case 63:
#line 230 "parser.y"
                                      { mdisk->setFit((yyvsp[0].TEXT)); }
#line 2217 "parser.cpp"
    break;

  case 64:
#line 234 "parser.y"
                                      { rmdisk->setPath((yyvsp[0].TEXT)); }
#line 2223 "parser.cpp"
    break;

  case 65:
#line 235 "parser.y"
                                      { rmdisk->setPath((yyvsp[0].TEXT)); }
#line 2229 "parser.cpp"
    break;

  case 66:
#line 239 "parser.y"
                                {  }
#line 2235 "parser.cpp"
    break;

  case 67:
#line 240 "parser.y"
                                {  }
#line 2241 "parser.cpp"
    break;

  case 68:
#line 244 "parser.y"
                                         { fdisk->setSize(atoi((yyvsp[0].TEXT))); }
#line 2247 "parser.cpp"
    break;

  case 69:
#line 245 "parser.y"
                                         { fdisk->setPath((yyvsp[0].TEXT)); }
#line 2253 "parser.cpp"
    break;

  case 70:
#line 246 "parser.y"
                                         { fdisk->setPath((yyvsp[0].TEXT)); }
#line 2259 "parser.cpp"
    break;

  case 71:
#line 247 "parser.y"
                                         { fdisk->setUnit((yyvsp[0].TEXT)); }
#line 2265 "parser.cpp"
    break;

  case 72:
#line 248 "parser.y"
                                         { fdisk->setFit((yyvsp[0].TEXT)); }
#line 2271 "parser.cpp"
    break;

  case 73:
#line 249 "parser.y"
                                         { fdisk->setType((yyvsp[0].TEXT)); }
#line 2277 "parser.cpp"
    break;

  case 74:
#line 250 "parser.y"
                                         { fdisk->setName((yyvsp[0].TEXT)); }
#line 2283 "parser.cpp"
    break;

  case 75:
#line 251 "parser.y"
                                         { fdisk->setName((yyvsp[0].TEXT)); }
#line 2289 "parser.cpp"
    break;

  case 76:
#line 252 "parser.y"
                                         { fdisk->setAdd(atoi((yyvsp[0].TEXT))); }
#line 2295 "parser.cpp"
    break;

  case 77:
#line 253 "parser.y"
                                         { fdisk->setAdd(atoi((yyvsp[0].TEXT)) * -1); }
#line 2301 "parser.cpp"
    break;

  case 78:
#line 254 "parser.y"
                                         { fdisk->setDelet((yyvsp[0].TEXT)); }
#line 2307 "parser.cpp"
    break;

  case 79:
#line 258 "parser.y"
                                {  }
#line 2313 "parser.cpp"
    break;

  case 80:
#line 259 "parser.y"
                                {  }
#line 2319 "parser.cpp"
    break;

  case 81:
#line 263 "parser.y"
                                         { mount->setPath((yyvsp[0].TEXT)); }
#line 2325 "parser.cpp"
    break;

  case 82:
#line 264 "parser.y"
                                         { mount->setPath((yyvsp[0].TEXT)); }
#line 2331 "parser.cpp"
    break;

  case 83:
#line 265 "parser.y"
                                         { mount->setName((yyvsp[0].TEXT)); }
#line 2337 "parser.cpp"
    break;

  case 84:
#line 266 "parser.y"
                                         { mount->setName((yyvsp[0].TEXT)); }
#line 2343 "parser.cpp"
    break;

  case 85:
#line 270 "parser.y"
                               { umount->setID((yyvsp[0].TEXT)); }
#line 2349 "parser.cpp"
    break;

  case 86:
#line 271 "parser.y"
                               { umount->setID((yyvsp[0].TEXT)); }
#line 2355 "parser.cpp"
    break;

  case 87:
#line 275 "parser.y"
                           {  }
#line 2361 "parser.cpp"
    break;

  case 88:
#line 276 "parser.y"
                           {  }
#line 2367 "parser.cpp"
    break;

  case 89:
#line 280 "parser.y"
                                      { mkfs->setID((yyvsp[0].TEXT)); }
#line 2373 "parser.cpp"
    break;

  case 90:
#line 281 "parser.y"
                                      { mkfs->setID((yyvsp[0].TEXT)); }
#line 2379 "parser.cpp"
    break;

  case 91:
#line 282 "parser.y"
                                      { mkfs->setType((yyvsp[0].TEXT)); }
#line 2385 "parser.cpp"
    break;

  case 92:
#line 283 "parser.y"
                                      { mkfs->setFS((yyvsp[0].TEXT)); }
#line 2391 "parser.cpp"
    break;

  case 93:
#line 287 "parser.y"
                              {  }
#line 2397 "parser.cpp"
    break;

  case 94:
#line 288 "parser.y"
                              {  }
#line 2403 "parser.cpp"
    break;

  case 95:
#line 292 "parser.y"
                                         { touch->setPath((yyvsp[0].TEXT)); }
#line 2409 "parser.cpp"
    break;

  case 96:
#line 293 "parser.y"
                                         { touch->setPath((yyvsp[0].TEXT)); }
#line 2415 "parser.cpp"
    break;

  case 97:
#line 294 "parser.y"
                                         { touch->setCont((yyvsp[0].TEXT)); }
#line 2421 "parser.cpp"
    break;

  case 98:
#line 295 "parser.y"
                                         { touch->setCont((yyvsp[0].TEXT)); }
#line 2427 "parser.cpp"
    break;

  case 99:
#line 296 "parser.y"
                                         { touch->setSize(atoi((yyvsp[0].TEXT))); }
#line 2433 "parser.cpp"
    break;

  case 100:
#line 297 "parser.y"
                                         { touch->setR(); }
#line 2439 "parser.cpp"
    break;

  case 101:
#line 298 "parser.y"
                                         { touch->setStdin(); }
#line 2445 "parser.cpp"
    break;

  case 102:
#line 302 "parser.y"
                              {  }
#line 2451 "parser.cpp"
    break;

  case 103:
#line 303 "parser.y"
                              {  }
#line 2457 "parser.cpp"
    break;

  case 104:
#line 307 "parser.y"
                                         { mkdir->setPath((yyvsp[0].TEXT)); }
#line 2463 "parser.cpp"
    break;

  case 105:
#line 308 "parser.y"
                                         { mkdir->setPath((yyvsp[0].TEXT)); }
#line 2469 "parser.cpp"
    break;

  case 106:
#line 309 "parser.y"
                                         { mkdir->setP((yyvsp[0].TEXT)); }
#line 2475 "parser.cpp"
    break;

  case 107:
#line 313 "parser.y"
                              {  }
#line 2481 "parser.cpp"
    break;

  case 108:
#line 314 "parser.y"
                              {  }
#line 2487 "parser.cpp"
    break;

  case 109:
#line 318 "parser.y"
                                         { reporte->setPath((yyvsp[0].TEXT)); }
#line 2493 "parser.cpp"
    break;

  case 110:
#line 319 "parser.y"
                                         { reporte->setPath((yyvsp[0].TEXT)); }
#line 2499 "parser.cpp"
    break;

  case 111:
#line 320 "parser.y"
                                         { reporte->setID((yyvsp[0].TEXT)); }
#line 2505 "parser.cpp"
    break;

  case 112:
#line 321 "parser.y"
                                         { reporte->setID((yyvsp[0].TEXT)); }
#line 2511 "parser.cpp"
    break;

  case 113:
#line 322 "parser.y"
                                         { reporte->setName((yyvsp[0].TEXT)); }
#line 2517 "parser.cpp"
    break;

  case 114:
#line 323 "parser.y"
                                         { reporte->setName((yyvsp[0].TEXT)); }
#line 2523 "parser.cpp"
    break;

  case 115:
#line 324 "parser.y"
                                         { reporte->setRuta((yyvsp[0].TEXT)); }
#line 2529 "parser.cpp"
    break;

  case 116:
#line 325 "parser.y"
                                         { reporte->setRuta((yyvsp[0].TEXT)); }
#line 2535 "parser.cpp"
    break;

  case 117:
#line 326 "parser.y"
                                         { reporte->setRoot(atoi((yyvsp[0].TEXT))); }
#line 2541 "parser.cpp"
    break;

  case 118:
#line 330 "parser.y"
                              {  }
#line 2547 "parser.cpp"
    break;

  case 119:
#line 331 "parser.y"
                              {  }
#line 2553 "parser.cpp"
    break;

  case 120:
#line 335 "parser.y"
                                         { cat->addFile((yyvsp[-2].TEXT), (yyvsp[0].TEXT)); }
#line 2559 "parser.cpp"
    break;

  case 121:
#line 336 "parser.y"
                                         { cat->addFile((yyvsp[-2].TEXT), (yyvsp[0].TEXT)); }
#line 2565 "parser.cpp"
    break;

  case 122:
#line 340 "parser.y"
                            {  }
#line 2571 "parser.cpp"
    break;

  case 123:
#line 341 "parser.y"
                            {  }
#line 2577 "parser.cpp"
    break;

  case 124:
#line 345 "parser.y"
                                       { ren->setPath((yyvsp[0].TEXT)); }
#line 2583 "parser.cpp"
    break;

  case 125:
#line 346 "parser.y"
                                       { ren->setPath((yyvsp[0].TEXT)); }
#line 2589 "parser.cpp"
    break;

  case 126:
#line 347 "parser.y"
                                       { ren->setName((yyvsp[0].TEXT)); }
#line 2595 "parser.cpp"
    break;

  case 127:
#line 348 "parser.y"
                                       { ren->setName((yyvsp[0].TEXT)); }
#line 2601 "parser.cpp"
    break;

  case 128:
#line 352 "parser.y"
                          {  }
#line 2607 "parser.cpp"
    break;

  case 129:
#line 353 "parser.y"
                          {  }
#line 2613 "parser.cpp"
    break;

  case 130:
#line 357 "parser.y"
                                  { rm->setPath((yyvsp[0].TEXT)); }
#line 2619 "parser.cpp"
    break;

  case 131:
#line 358 "parser.y"
                                  { rm->setPath((yyvsp[0].TEXT)); }
#line 2625 "parser.cpp"
    break;

  case 132:
#line 362 "parser.y"
                            {  }
#line 2631 "parser.cpp"
    break;

  case 133:
#line 363 "parser.y"
                            {  }
#line 2637 "parser.cpp"
    break;

  case 134:
#line 367 "parser.y"
                                  { edit->setPath((yyvsp[0].TEXT)); }
#line 2643 "parser.cpp"
    break;

  case 135:
#line 368 "parser.y"
                                  { edit->setPath((yyvsp[0].TEXT)); }
#line 2649 "parser.cpp"
    break;

  case 136:
#line 369 "parser.y"
                                  { edit->setCont((yyvsp[0].TEXT)); }
#line 2655 "parser.cpp"
    break;

  case 137:
#line 370 "parser.y"
                                  { edit->setCont((yyvsp[0].TEXT)); }
#line 2661 "parser.cpp"
    break;

  case 138:
#line 371 "parser.y"
                                  { edit->setStdin(); }
#line 2667 "parser.cpp"
    break;

  case 139:
#line 375 "parser.y"
                                  { exec->setPath((yyvsp[0].TEXT)); }
#line 2673 "parser.cpp"
    break;

  case 140:
#line 376 "parser.y"
                                  { exec->setPath((yyvsp[0].TEXT)); }
#line 2679 "parser.cpp"
    break;

  case 141:
#line 380 "parser.y"
                          {  }
#line 2685 "parser.cpp"
    break;

  case 142:
#line 381 "parser.y"
                          {  }
#line 2691 "parser.cpp"
    break;

  case 143:
#line 385 "parser.y"
                                  { mv->setPath((yyvsp[0].TEXT)); }
#line 2697 "parser.cpp"
    break;

  case 144:
#line 386 "parser.y"
                                  { mv->setPath((yyvsp[0].TEXT)); }
#line 2703 "parser.cpp"
    break;

  case 145:
#line 387 "parser.y"
                                  { mv->setDest((yyvsp[0].TEXT)); }
#line 2709 "parser.cpp"
    break;

  case 146:
#line 388 "parser.y"
                                  { mv->setDest((yyvsp[0].TEXT)); }
#line 2715 "parser.cpp"
    break;

  case 147:
#line 392 "parser.y"
                          {  }
#line 2721 "parser.cpp"
    break;

  case 148:
#line 393 "parser.y"
                          {  }
#line 2727 "parser.cpp"
    break;

  case 149:
#line 397 "parser.y"
                                  { cp->setPath((yyvsp[0].TEXT)); }
#line 2733 "parser.cpp"
    break;

  case 150:
#line 398 "parser.y"
                                  { cp->setPath((yyvsp[0].TEXT)); }
#line 2739 "parser.cpp"
    break;

  case 151:
#line 399 "parser.y"
                                  { cp->setDest((yyvsp[0].TEXT)); }
#line 2745 "parser.cpp"
    break;

  case 152:
#line 400 "parser.y"
                                  { cp->setDest((yyvsp[0].TEXT)); }
#line 2751 "parser.cpp"
    break;

  case 153:
#line 404 "parser.y"
                              {  }
#line 2757 "parser.cpp"
    break;

  case 154:
#line 405 "parser.y"
                              {  }
#line 2763 "parser.cpp"
    break;

  case 155:
#line 409 "parser.y"
                                           { finds->setPath((yyvsp[0].TEXT)); }
#line 2769 "parser.cpp"
    break;

  case 156:
#line 410 "parser.y"
                                           { finds->setPath((yyvsp[0].TEXT)); }
#line 2775 "parser.cpp"
    break;

  case 157:
#line 411 "parser.y"
                                           { finds->setName((yyvsp[0].TEXT)); }
#line 2781 "parser.cpp"
    break;

  case 158:
#line 412 "parser.y"
                                           { finds->setName((yyvsp[0].TEXT)); }
#line 2787 "parser.cpp"
    break;

  case 159:
#line 416 "parser.y"
                                {  }
#line 2793 "parser.cpp"
    break;

  case 160:
#line 417 "parser.y"
                                {  }
#line 2799 "parser.cpp"
    break;

  case 161:
#line 421 "parser.y"
                                       { login->setUser((yyvsp[0].TEXT)); }
#line 2805 "parser.cpp"
    break;

  case 162:
#line 422 "parser.y"
                                       { login->setUser((yyvsp[0].TEXT)); }
#line 2811 "parser.cpp"
    break;

  case 163:
#line 423 "parser.y"
                                       { login->setUser((yyvsp[0].TEXT)); }
#line 2817 "parser.cpp"
    break;

  case 164:
#line 424 "parser.y"
                                       { login->setPwd((yyvsp[0].TEXT)); }
#line 2823 "parser.cpp"
    break;

  case 165:
#line 425 "parser.y"
                                       { login->setPwd((yyvsp[0].TEXT)); }
#line 2829 "parser.cpp"
    break;

  case 166:
#line 426 "parser.y"
                                       { login->setPwd((yyvsp[0].TEXT)); }
#line 2835 "parser.cpp"
    break;

  case 167:
#line 427 "parser.y"
                                       { login->setID((yyvsp[0].TEXT)); }
#line 2841 "parser.cpp"
    break;

  case 168:
#line 428 "parser.y"
                                       { login->setID((yyvsp[0].TEXT)); }
#line 2847 "parser.cpp"
    break;

  case 169:
#line 432 "parser.y"
                                {  }
#line 2853 "parser.cpp"
    break;

  case 170:
#line 433 "parser.y"
                                {  }
#line 2859 "parser.cpp"
    break;

  case 171:
#line 437 "parser.y"
                                       { mkgrp->setName((yyvsp[0].TEXT)); }
#line 2865 "parser.cpp"
    break;

  case 172:
#line 438 "parser.y"
                                       { mkgrp->setName((yyvsp[0].TEXT)); }
#line 2871 "parser.cpp"
    break;

  case 173:
#line 439 "parser.y"
                                       { mkgrp->setName((yyvsp[0].TEXT)); }
#line 2877 "parser.cpp"
    break;

  case 174:
#line 443 "parser.y"
                                {  }
#line 2883 "parser.cpp"
    break;

  case 175:
#line 444 "parser.y"
                                {  }
#line 2889 "parser.cpp"
    break;

  case 176:
#line 448 "parser.y"
                                       { rmgrp->setName((yyvsp[0].TEXT)); }
#line 2895 "parser.cpp"
    break;

  case 177:
#line 449 "parser.y"
                                       { rmgrp->setName((yyvsp[0].TEXT)); }
#line 2901 "parser.cpp"
    break;

  case 178:
#line 450 "parser.y"
                                       { rmgrp->setName((yyvsp[0].TEXT)); }
#line 2907 "parser.cpp"
    break;

  case 179:
#line 454 "parser.y"
                                {  }
#line 2913 "parser.cpp"
    break;

  case 180:
#line 455 "parser.y"
                                {  }
#line 2919 "parser.cpp"
    break;

  case 181:
#line 459 "parser.y"
                                      { mkusr->setUsr((yyvsp[0].TEXT)); }
#line 2925 "parser.cpp"
    break;

  case 182:
#line 460 "parser.y"
                                      { mkusr->setUsr((yyvsp[0].TEXT)); }
#line 2931 "parser.cpp"
    break;

  case 183:
#line 461 "parser.y"
                                      { mkusr->setUsr((yyvsp[0].TEXT)); }
#line 2937 "parser.cpp"
    break;

  case 184:
#line 462 "parser.y"
                                      { mkusr->setPwd((yyvsp[0].TEXT)); }
#line 2943 "parser.cpp"
    break;

  case 185:
#line 463 "parser.y"
                                      { mkusr->setPwd((yyvsp[0].TEXT)); }
#line 2949 "parser.cpp"
    break;

  case 186:
#line 464 "parser.y"
                                      { mkusr->setPwd((yyvsp[0].TEXT)); }
#line 2955 "parser.cpp"
    break;

  case 187:
#line 465 "parser.y"
                                      { mkusr->setGrp((yyvsp[0].TEXT)); }
#line 2961 "parser.cpp"
    break;

  case 188:
#line 466 "parser.y"
                                      { mkusr->setGrp((yyvsp[0].TEXT)); }
#line 2967 "parser.cpp"
    break;

  case 189:
#line 467 "parser.y"
                                      { mkusr->setGrp((yyvsp[0].TEXT)); }
#line 2973 "parser.cpp"
    break;

  case 190:
#line 471 "parser.y"
                                {  }
#line 2979 "parser.cpp"
    break;

  case 191:
#line 472 "parser.y"
                                {  }
#line 2985 "parser.cpp"
    break;

  case 192:
#line 476 "parser.y"
                                      { rmusr->setUsr((yyvsp[0].TEXT)); }
#line 2991 "parser.cpp"
    break;

  case 193:
#line 477 "parser.y"
                                      { rmusr->setUsr((yyvsp[0].TEXT)); }
#line 2997 "parser.cpp"
    break;

  case 194:
#line 478 "parser.y"
                                      { rmusr->setUsr((yyvsp[0].TEXT)); }
#line 3003 "parser.cpp"
    break;

  case 195:
#line 482 "parser.y"
                                {  }
#line 3009 "parser.cpp"
    break;

  case 196:
#line 483 "parser.y"
                                {  }
#line 3015 "parser.cpp"
    break;

  case 197:
#line 487 "parser.y"
                                      { chgrp->setUsr((yyvsp[0].TEXT)); }
#line 3021 "parser.cpp"
    break;

  case 198:
#line 488 "parser.y"
                                      { chgrp->setUsr((yyvsp[0].TEXT)); }
#line 3027 "parser.cpp"
    break;

  case 199:
#line 489 "parser.y"
                                      { chgrp->setUsr((yyvsp[0].TEXT)); }
#line 3033 "parser.cpp"
    break;

  case 200:
#line 490 "parser.y"
                                      { chgrp->setGrp((yyvsp[0].TEXT)); }
#line 3039 "parser.cpp"
    break;

  case 201:
#line 491 "parser.y"
                                      { chgrp->setGrp((yyvsp[0].TEXT)); }
#line 3045 "parser.cpp"
    break;

  case 202:
#line 492 "parser.y"
                                      { chgrp->setGrp((yyvsp[0].TEXT)); }
#line 3051 "parser.cpp"
    break;

  case 203:
#line 496 "parser.y"
                              {  }
#line 3057 "parser.cpp"
    break;

  case 204:
#line 497 "parser.y"
                              {  }
#line 3063 "parser.cpp"
    break;

  case 205:
#line 501 "parser.y"
                                     { loss->setID((yyvsp[0].TEXT)); }
#line 3069 "parser.cpp"
    break;

  case 206:
#line 502 "parser.y"
                                     { loss->setID((yyvsp[0].TEXT)); }
#line 3075 "parser.cpp"
    break;

  case 207:
#line 506 "parser.y"
                              {  }
#line 3081 "parser.cpp"
    break;

  case 208:
#line 507 "parser.y"
                              {  }
#line 3087 "parser.cpp"
    break;

  case 209:
#line 511 "parser.y"
                                     { reco->setID((yyvsp[0].TEXT)); }
#line 3093 "parser.cpp"
    break;

  case 210:
#line 512 "parser.y"
                                     { reco->setID((yyvsp[0].TEXT)); }
#line 3099 "parser.cpp"
    break;


#line 3103 "parser.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
