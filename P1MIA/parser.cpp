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

using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

int yyerror(const char* mens)
{
std::cout << mens <<" "<<yytext<< std::endl;
return 0;
}

#line 128 "parser.cpp"

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
    SIZE = 271,
    PATH = 272,
    TYPE = 273,
    NAME = 274,
    ADD = 275,
    DELETE = 276,
    ID = 277,
    FS = 278,
    CONT = 279,
    STDIN = 280,
    RUTAS = 281,
    ROOT = 282,
    letF = 283,
    letU = 284,
    letR = 285,
    letP = 286,
    IGUAL = 287,
    MENOS = 288,
    POSITIVO = 289,
    RUTA = 290,
    LETRA = 291,
    CADENA = 292,
    IDENTIFICADOR = 293,
    IDMOUNT = 294,
    IDFS = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 62 "parser.y"

//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];


#line 229 "parser.cpp"

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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  112
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  209

#define YYUNDEFTOK  2
#define YYMAXUTOK   295


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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   126,   126,   130,   131,   134,   134,   135,   135,   136,
     136,   137,   137,   138,   138,   139,   139,   140,   140,   141,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   146,
     146,   150,   151,   155,   156,   157,   158,   159,   163,   164,
     168,   169,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   187,   188,   192,   193,   194,   195,   199,
     200,   204,   205,   209,   210,   211,   212,   216,   217,   221,
     222,   223,   224,   225,   226,   227,   231,   232,   236,   237,
     238,   242,   243,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   259,   260,   264,   265,   269,   270,   274,   275,
     276,   277,   281,   282,   286,   287,   291,   292,   296,   297,
     298,   299,   300
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MKDISK", "RMDISK", "FDISK", "MOUNT",
  "UMOUNT", "MKFS", "TOUCH", "MKDIR", "REP", "CAT", "REN", "RM", "EDIT",
  "SIZE", "PATH", "TYPE", "NAME", "ADD", "DELETE", "ID", "FS", "CONT",
  "STDIN", "RUTAS", "ROOT", "letF", "letU", "letR", "letP", "IGUAL",
  "MENOS", "POSITIVO", "RUTA", "LETRA", "CADENA", "IDENTIFICADOR",
  "IDMOUNT", "IDFS", "$accept", "INICIO", "INSTRUCCIONES", "INSTRUCCION",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "COMANDOMKDISK", "PARMKDISK", "COMANDORMDISK",
  "COMANDOFDISK", "PARFDISK", "COMANDOMOUNT", "PARMOUNT", "COMANDOUMOUNT",
  "COMANDOMKFS", "PARMKFS", "COMANDOTOUCH", "PARTOUCH", "COMANDOMKDIR",
  "PARMKDIR", "COMANDOREPORTE", "PARREP", "COMANDOCAT", "PARCAT",
  "COMANDOREN", "PARREN", "COMANDORM", "PARRM", "COMANDOEDIT", "PAREDIT", YY_NULLPTR
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
     295
};
# endif

#define YYPACT_NINF (-33)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      40,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,     1,    40,   -33,   -19,   -12,    -2,
      43,    64,    65,    66,    67,    68,    69,    70,    71,    72,
     -33,   -33,    13,   -19,   -33,    89,   -33,     7,    -2,   -33,
      -4,    43,   -33,    85,   -33,    15,    65,   -33,    -8,    66,
     -33,   -17,    67,   -33,   -15,    68,   -33,   -20,    69,   -33,
      39,    70,   -33,    91,    71,   -33,   -14,    72,   -33,    77,
      78,    79,    80,   -33,    81,    82,    83,    84,    86,    87,
      88,    90,    92,   -33,    93,    94,   -33,    95,    96,    97,
      98,   -33,    99,   100,   101,   -33,   -33,   -33,   102,   -33,
     -33,   103,   104,   105,   106,   107,   -33,   108,   -33,   109,
     110,   -33,   111,   -33,   112,   113,   -33,   -33,   114,    -3,
     115,   116,    22,   117,    25,   118,   -32,     6,   119,   120,
     123,    26,    52,    27,   122,    28,   121,   128,    33,    34,
      37,    38,    54,    41,   129,    56,    42,    46,    58,    47,
      50,    51,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   130,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     5,     7,     9,    11,    13,    15,    17,    19,    21,
      23,    25,    27,    29,     0,     2,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     3,     0,     6,    32,     0,     8,     0,    10,    41,
       0,    12,    54,     0,    14,     0,    16,    62,     0,    18,
      68,     0,    20,    77,     0,    22,    82,     0,    24,    93,
       0,    26,    97,     0,    28,   103,     0,    30,   107,     0,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,    53,     0,     0,     0,
       0,    61,     0,     0,     0,    75,    74,    67,     0,    80,
      76,     0,     0,     0,     0,     0,    81,     0,    92,     0,
       0,    96,     0,   102,     0,     0,   112,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    33,    34,    35,    37,    36,    38,    39,    42,
      43,    44,    47,    48,    49,     0,    50,    52,    46,    45,
      55,    56,    57,    58,    60,    59,    65,    64,    63,    66,
      73,    69,    70,    71,    72,    78,    79,    83,    84,    87,
      88,    85,    86,    91,    89,    90,    94,    95,    98,    99,
     101,   100,   104,   105,   108,   109,   110,   111,    51
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -33,   -33,   -33,   131,   -33,   -33,   -33,   -33,   -33,   -33,
     -33,   -33,   -33,   -33,   -33,   -33,   -33,   -33,   132,   -33,
     -33,   133,   -33,    76,   -33,   -33,    75,   -33,    74,   -33,
     124,   -33,   125,   -33,   126,   -33,   127,   -33,   134,   -33,
     135
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    33,    34,    36,
      38,    39,    41,    42,    44,    46,    47,    49,    50,    52,
      53,    55,    56,    58,    59,    61,    62,    64,    65,    67,
      68
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      98,    30,   101,   114,   102,   163,   164,   103,    92,    93,
     115,   116,   104,    84,    32,    85,    94,    95,   107,    99,
     105,    35,    96,    75,    76,    77,    78,    79,    80,    69,
      70,    37,   153,    88,   154,    81,    82,    89,    90,   165,
     166,    71,    72,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,   109,   157,   110,   158,
     160,   170,   161,   171,   174,   177,   175,   178,   181,   183,
     182,   184,   185,   187,   186,   188,    40,   196,   191,   197,
     192,   198,   202,   199,   203,   204,   206,   205,   207,   172,
     173,   189,   190,   194,   195,   200,   201,    43,    45,    48,
      51,    54,    57,    60,    63,    66,    74,    87,   112,   118,
     119,   120,   121,   122,   123,   124,   125,    86,   126,   127,
     128,    91,   129,    97,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   148,   149,   150,   151,    31,     0,   152,     0,
       0,   159,   156,   155,   162,     0,     0,   167,   168,   169,
     176,   179,   180,   193,   208,    73,     0,     0,     0,     0,
       0,    83,     0,     0,     0,     0,   100,     0,     0,     0,
     106,     0,     0,     0,   108,     0,     0,     0,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,     0,
       0,     0,   117
};

static const yytype_int8 yycheck[] =
{
      17,     0,    17,    17,    19,    37,    38,    22,    16,    17,
      24,    25,    27,    17,    33,    19,    24,    25,    38,    36,
      35,    33,    30,    16,    17,    18,    19,    20,    21,    16,
      17,    33,    35,    18,    37,    28,    29,    22,    23,    33,
      34,    28,    29,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    17,    35,    19,    37,
      35,    35,    37,    37,    37,    37,    39,    39,    35,    35,
      37,    37,    35,    35,    37,    37,    33,    35,    37,    37,
      39,    35,    35,    37,    37,    35,    35,    37,    37,    37,
      38,    37,    38,    37,    38,    37,    38,    33,    33,    33,
      33,    33,    33,    33,    33,    33,    17,    22,    17,    32,
      32,    32,    32,    32,    32,    32,    32,    41,    32,    32,
      32,    46,    32,    49,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    15,    -1,    34,    -1,
      -1,    34,    36,    38,    36,    -1,    -1,    38,    38,    36,
      38,    40,    34,    34,    34,    33,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    58,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    67
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
       0,    44,    33,    58,    59,    33,    60,    33,    61,    62,
      33,    63,    64,    33,    65,    33,    66,    67,    33,    68,
      69,    33,    70,    71,    33,    72,    73,    33,    74,    75,
      33,    76,    77,    33,    78,    79,    33,    80,    81,    16,
      17,    28,    29,    59,    17,    16,    17,    18,    19,    20,
      21,    28,    29,    62,    17,    19,    64,    22,    18,    22,
      23,    67,    16,    17,    24,    25,    30,    69,    17,    36,
      71,    17,    19,    22,    27,    35,    73,    38,    75,    17,
      19,    77,    17,    79,    17,    24,    25,    81,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    32,    32,    32,    32,    32,    32,    32,    32,
      32,    32,    34,    35,    37,    38,    36,    35,    37,    34,
      35,    37,    36,    37,    38,    33,    34,    38,    38,    36,
      35,    37,    37,    38,    37,    39,    38,    37,    39,    40,
      34,    35,    37,    35,    37,    35,    37,    35,    37,    37,
      38,    37,    39,    34,    37,    38,    35,    37,    35,    37,
      37,    38,    35,    37,    35,    37,    35,    37,    34
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    45,    44,    46,    44,    47,
      44,    48,    44,    49,    44,    50,    44,    51,    44,    52,
      44,    53,    44,    54,    44,    55,    44,    56,    44,    57,
      44,    58,    58,    59,    59,    59,    59,    59,    60,    60,
      61,    61,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    63,    63,    64,    64,    64,    64,    65,
      65,    66,    66,    67,    67,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    71,    71,
      71,    72,    72,    73,    73,    73,    73,    73,    73,    73,
      73,    73,    74,    74,    75,    75,    76,    76,    77,    77,
      77,    77,    78,    78,    79,    79,    80,    80,    81,    81,
      81,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     0,     3,     0,     3,     0,     3,     0,     3,     0,
       3,     2,     1,     4,     4,     4,     4,     4,     4,     4,
       2,     1,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     5,     4,     2,     1,     4,     4,     4,     4,     4,
       4,     2,     1,     4,     4,     4,     4,     2,     1,     4,
       4,     4,     4,     4,     2,     2,     2,     1,     4,     4,
       2,     2,     1,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     2,     1,     4,     4,     2,     1,     4,     4,
       4,     4,     2,     1,     4,     4,     2,     1,     4,     4,
       4,     4,     2
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
#line 126 "parser.y"
                  {  }
#line 1662 "parser.cpp"
    break;

  case 3:
#line 130 "parser.y"
                                    {  }
#line 1668 "parser.cpp"
    break;

  case 4:
#line 131 "parser.y"
                                    {  }
#line 1674 "parser.cpp"
    break;

  case 5:
#line 134 "parser.y"
             { mdisk = new obmkdisk();   /*objeto mkdisk*/}
#line 1680 "parser.cpp"
    break;

  case 6:
#line 134 "parser.y"
                                                                           { mdisk->exec();  /*ejecutar mkdisk*/}
#line 1686 "parser.cpp"
    break;

  case 7:
#line 135 "parser.y"
             { rmdisk = new obrmdisk();  /*objeto rmdisk*/}
#line 1692 "parser.cpp"
    break;

  case 8:
#line 135 "parser.y"
                                                                           { rmdisk->exec(); /*ejecutar rmdisk*/}
#line 1698 "parser.cpp"
    break;

  case 9:
#line 136 "parser.y"
             { fdisk = new obfdisk();    /*objeto fdisk*/ }
#line 1704 "parser.cpp"
    break;

  case 10:
#line 136 "parser.y"
                                                                           { fdisk->exec();  /*ejecutar fdisk*/ }
#line 1710 "parser.cpp"
    break;

  case 11:
#line 137 "parser.y"
             { mount = new obmount();    /*objeto mount*/ }
#line 1716 "parser.cpp"
    break;

  case 12:
#line 137 "parser.y"
                                                                           { mount->exec();  /*ejecutar mount*/ }
#line 1722 "parser.cpp"
    break;

  case 13:
#line 138 "parser.y"
             { umount = new obumount();  /*objeto umount*/}
#line 1728 "parser.cpp"
    break;

  case 14:
#line 138 "parser.y"
                                                                           { umount->exec(); /*ejecutar umount*/}
#line 1734 "parser.cpp"
    break;

  case 15:
#line 139 "parser.y"
             { mkfs = new obmkfs();        /*objeto mkfs*/}
#line 1740 "parser.cpp"
    break;

  case 16:
#line 139 "parser.y"
                                                                           { mkfs->exec();     /*ejecutar mkfs*/}
#line 1746 "parser.cpp"
    break;

  case 17:
#line 140 "parser.y"
             { touch = new obtouch();     /*objeto touch*/}
#line 1752 "parser.cpp"
    break;

  case 18:
#line 140 "parser.y"
                                                                           { touch->exec();   /*ejecutar touch*/}
#line 1758 "parser.cpp"
    break;

  case 19:
#line 141 "parser.y"
             { mkdir = new obmkdir();     /*objeto mkdir*/}
#line 1764 "parser.cpp"
    break;

  case 20:
#line 141 "parser.y"
                                                                           { mkdir->exec();   /*ejecutar mkdir*/}
#line 1770 "parser.cpp"
    break;

  case 21:
#line 142 "parser.y"
             { reporte = new obreporte();   /*objeto rep*/}
#line 1776 "parser.cpp"
    break;

  case 22:
#line 142 "parser.y"
                                                                           { reporte->exec();   /*ejecutar rep*/}
#line 1782 "parser.cpp"
    break;

  case 23:
#line 143 "parser.y"
             { cat = new obcat();           /*objeto cat*/}
#line 1788 "parser.cpp"
    break;

  case 24:
#line 143 "parser.y"
                                                                           { cat->exec();       /*ejecutar cat*/}
#line 1794 "parser.cpp"
    break;

  case 25:
#line 144 "parser.y"
             { ren = new obren();           /*objeto ren*/}
#line 1800 "parser.cpp"
    break;

  case 26:
#line 144 "parser.y"
                                                                           { ren->exec();       /*ejecutar ren*/}
#line 1806 "parser.cpp"
    break;

  case 27:
#line 145 "parser.y"
             { rm = new obrm();              /*objeto rm*/}
#line 1812 "parser.cpp"
    break;

  case 28:
#line 145 "parser.y"
                                                                           { rm->exec();         /*ejecutar rm*/}
#line 1818 "parser.cpp"
    break;

  case 29:
#line 146 "parser.y"
             { edit = new obedit();        /*objeto edit*/}
#line 1824 "parser.cpp"
    break;

  case 30:
#line 146 "parser.y"
                                                                           { edit->exec();     /*ejecutar edit*/}
#line 1830 "parser.cpp"
    break;

  case 31:
#line 150 "parser.y"
                                    {  }
#line 1836 "parser.cpp"
    break;

  case 32:
#line 151 "parser.y"
                                    {  }
#line 1842 "parser.cpp"
    break;

  case 33:
#line 155 "parser.y"
                                        { mdisk->setSize(atoi((yyvsp[0].TEXT))); }
#line 1848 "parser.cpp"
    break;

  case 34:
#line 156 "parser.y"
                                        { mdisk->setPath((yyvsp[0].TEXT)); }
#line 1854 "parser.cpp"
    break;

  case 35:
#line 157 "parser.y"
                                        { mdisk->setPath((yyvsp[0].TEXT)); }
#line 1860 "parser.cpp"
    break;

  case 36:
#line 158 "parser.y"
                                        { mdisk->setUnit((yyvsp[0].TEXT)); }
#line 1866 "parser.cpp"
    break;

  case 37:
#line 159 "parser.y"
                                        { mdisk->setFit((yyvsp[0].TEXT)); }
#line 1872 "parser.cpp"
    break;

  case 38:
#line 163 "parser.y"
                                        { rmdisk->setPath((yyvsp[0].TEXT)); }
#line 1878 "parser.cpp"
    break;

  case 39:
#line 164 "parser.y"
                                        { rmdisk->setPath((yyvsp[0].TEXT)); }
#line 1884 "parser.cpp"
    break;

  case 40:
#line 168 "parser.y"
                                  {  }
#line 1890 "parser.cpp"
    break;

  case 41:
#line 169 "parser.y"
                                  {  }
#line 1896 "parser.cpp"
    break;

  case 42:
#line 173 "parser.y"
                                           { fdisk->setSize(atoi((yyvsp[0].TEXT))); }
#line 1902 "parser.cpp"
    break;

  case 43:
#line 174 "parser.y"
                                           { fdisk->setPath((yyvsp[0].TEXT)); }
#line 1908 "parser.cpp"
    break;

  case 44:
#line 175 "parser.y"
                                           { fdisk->setPath((yyvsp[0].TEXT)); }
#line 1914 "parser.cpp"
    break;

  case 45:
#line 176 "parser.y"
                                           { fdisk->setUnit((yyvsp[0].TEXT)); }
#line 1920 "parser.cpp"
    break;

  case 46:
#line 177 "parser.y"
                                           { fdisk->setFit((yyvsp[0].TEXT)); }
#line 1926 "parser.cpp"
    break;

  case 47:
#line 178 "parser.y"
                                           { fdisk->setType((yyvsp[0].TEXT)); }
#line 1932 "parser.cpp"
    break;

  case 48:
#line 179 "parser.y"
                                           { fdisk->setName((yyvsp[0].TEXT)); }
#line 1938 "parser.cpp"
    break;

  case 49:
#line 180 "parser.y"
                                           { fdisk->setName((yyvsp[0].TEXT)); }
#line 1944 "parser.cpp"
    break;

  case 50:
#line 181 "parser.y"
                                           { fdisk->setAdd(atoi((yyvsp[0].TEXT))); }
#line 1950 "parser.cpp"
    break;

  case 51:
#line 182 "parser.y"
                                           { fdisk->setAdd(atoi((yyvsp[0].TEXT)) * -1); }
#line 1956 "parser.cpp"
    break;

  case 52:
#line 183 "parser.y"
                                           { fdisk->setDelet((yyvsp[0].TEXT)); }
#line 1962 "parser.cpp"
    break;

  case 53:
#line 187 "parser.y"
                                  {  }
#line 1968 "parser.cpp"
    break;

  case 54:
#line 188 "parser.y"
                                  {  }
#line 1974 "parser.cpp"
    break;

  case 55:
#line 192 "parser.y"
                                           { mount->setPath((yyvsp[0].TEXT)); }
#line 1980 "parser.cpp"
    break;

  case 56:
#line 193 "parser.y"
                                           { mount->setPath((yyvsp[0].TEXT)); }
#line 1986 "parser.cpp"
    break;

  case 57:
#line 194 "parser.y"
                                           { mount->setName((yyvsp[0].TEXT)); }
#line 1992 "parser.cpp"
    break;

  case 58:
#line 195 "parser.y"
                                           { mount->setName((yyvsp[0].TEXT)); }
#line 1998 "parser.cpp"
    break;

  case 59:
#line 199 "parser.y"
                                 { umount->setID((yyvsp[0].TEXT)); }
#line 2004 "parser.cpp"
    break;

  case 60:
#line 200 "parser.y"
                                 { umount->setID((yyvsp[0].TEXT)); }
#line 2010 "parser.cpp"
    break;

  case 61:
#line 204 "parser.y"
                             {  }
#line 2016 "parser.cpp"
    break;

  case 62:
#line 205 "parser.y"
                             {  }
#line 2022 "parser.cpp"
    break;

  case 63:
#line 209 "parser.y"
                                        { mkfs->setID((yyvsp[0].TEXT)); }
#line 2028 "parser.cpp"
    break;

  case 64:
#line 210 "parser.y"
                                        { mkfs->setID((yyvsp[0].TEXT)); }
#line 2034 "parser.cpp"
    break;

  case 65:
#line 211 "parser.y"
                                        { mkfs->setType((yyvsp[0].TEXT)); }
#line 2040 "parser.cpp"
    break;

  case 66:
#line 212 "parser.y"
                                        { mkfs->setFS((yyvsp[0].TEXT)); }
#line 2046 "parser.cpp"
    break;

  case 67:
#line 216 "parser.y"
                                {  }
#line 2052 "parser.cpp"
    break;

  case 68:
#line 217 "parser.y"
                                {  }
#line 2058 "parser.cpp"
    break;

  case 69:
#line 221 "parser.y"
                                           { touch->setPath((yyvsp[0].TEXT)); }
#line 2064 "parser.cpp"
    break;

  case 70:
#line 222 "parser.y"
                                           { touch->setPath((yyvsp[0].TEXT)); }
#line 2070 "parser.cpp"
    break;

  case 71:
#line 223 "parser.y"
                                           { touch->setCont((yyvsp[0].TEXT)); }
#line 2076 "parser.cpp"
    break;

  case 72:
#line 224 "parser.y"
                                           { touch->setCont((yyvsp[0].TEXT)); }
#line 2082 "parser.cpp"
    break;

  case 73:
#line 225 "parser.y"
                                           { touch->setSize(atoi((yyvsp[0].TEXT))); }
#line 2088 "parser.cpp"
    break;

  case 74:
#line 226 "parser.y"
                                           { touch->setR(); }
#line 2094 "parser.cpp"
    break;

  case 75:
#line 227 "parser.y"
                                           { touch->setStdin(); }
#line 2100 "parser.cpp"
    break;

  case 76:
#line 231 "parser.y"
                                {  }
#line 2106 "parser.cpp"
    break;

  case 77:
#line 232 "parser.y"
                                {  }
#line 2112 "parser.cpp"
    break;

  case 78:
#line 236 "parser.y"
                                           { mkdir->setPath((yyvsp[0].TEXT)); }
#line 2118 "parser.cpp"
    break;

  case 79:
#line 237 "parser.y"
                                           { mkdir->setPath((yyvsp[0].TEXT)); }
#line 2124 "parser.cpp"
    break;

  case 80:
#line 238 "parser.y"
                                           { mkdir->setP((yyvsp[0].TEXT)); }
#line 2130 "parser.cpp"
    break;

  case 81:
#line 242 "parser.y"
                                {  }
#line 2136 "parser.cpp"
    break;

  case 82:
#line 243 "parser.y"
                                {  }
#line 2142 "parser.cpp"
    break;

  case 83:
#line 247 "parser.y"
                                           { reporte->setPath((yyvsp[0].TEXT)); }
#line 2148 "parser.cpp"
    break;

  case 84:
#line 248 "parser.y"
                                           { reporte->setPath((yyvsp[0].TEXT)); }
#line 2154 "parser.cpp"
    break;

  case 85:
#line 249 "parser.y"
                                           { reporte->setID((yyvsp[0].TEXT)); }
#line 2160 "parser.cpp"
    break;

  case 86:
#line 250 "parser.y"
                                           { reporte->setID((yyvsp[0].TEXT)); }
#line 2166 "parser.cpp"
    break;

  case 87:
#line 251 "parser.y"
                                           { reporte->setName((yyvsp[0].TEXT)); }
#line 2172 "parser.cpp"
    break;

  case 88:
#line 252 "parser.y"
                                           { reporte->setName((yyvsp[0].TEXT)); }
#line 2178 "parser.cpp"
    break;

  case 89:
#line 253 "parser.y"
                                           { reporte->setRuta((yyvsp[0].TEXT)); }
#line 2184 "parser.cpp"
    break;

  case 90:
#line 254 "parser.y"
                                           { reporte->setRuta((yyvsp[0].TEXT)); }
#line 2190 "parser.cpp"
    break;

  case 91:
#line 255 "parser.y"
                                           { reporte->setRoot(atoi((yyvsp[0].TEXT))); }
#line 2196 "parser.cpp"
    break;

  case 92:
#line 259 "parser.y"
                              {  }
#line 2202 "parser.cpp"
    break;

  case 93:
#line 260 "parser.y"
                              {  }
#line 2208 "parser.cpp"
    break;

  case 94:
#line 264 "parser.y"
                                           { cat->addFile((yyvsp[-2].TEXT), (yyvsp[0].TEXT)); }
#line 2214 "parser.cpp"
    break;

  case 95:
#line 265 "parser.y"
                                           { cat->addFile((yyvsp[-2].TEXT), (yyvsp[0].TEXT)); }
#line 2220 "parser.cpp"
    break;

  case 96:
#line 269 "parser.y"
                              {  }
#line 2226 "parser.cpp"
    break;

  case 97:
#line 270 "parser.y"
                              {  }
#line 2232 "parser.cpp"
    break;

  case 98:
#line 274 "parser.y"
                                         { ren->setPath((yyvsp[0].TEXT)); }
#line 2238 "parser.cpp"
    break;

  case 99:
#line 275 "parser.y"
                                         { ren->setPath((yyvsp[0].TEXT)); }
#line 2244 "parser.cpp"
    break;

  case 100:
#line 276 "parser.y"
                                         { ren->setName((yyvsp[0].TEXT)); }
#line 2250 "parser.cpp"
    break;

  case 101:
#line 277 "parser.y"
                                         { ren->setName((yyvsp[0].TEXT)); }
#line 2256 "parser.cpp"
    break;

  case 102:
#line 281 "parser.y"
                            {  }
#line 2262 "parser.cpp"
    break;

  case 103:
#line 282 "parser.y"
                            {  }
#line 2268 "parser.cpp"
    break;

  case 104:
#line 286 "parser.y"
                                    { rm->setPath((yyvsp[0].TEXT)); }
#line 2274 "parser.cpp"
    break;

  case 105:
#line 287 "parser.y"
                                    { rm->setPath((yyvsp[0].TEXT)); }
#line 2280 "parser.cpp"
    break;

  case 106:
#line 291 "parser.y"
                              {  }
#line 2286 "parser.cpp"
    break;

  case 107:
#line 292 "parser.y"
                              {  }
#line 2292 "parser.cpp"
    break;

  case 108:
#line 296 "parser.y"
                                    { edit->setPath((yyvsp[0].TEXT)); }
#line 2298 "parser.cpp"
    break;

  case 109:
#line 297 "parser.y"
                                    { edit->setPath((yyvsp[0].TEXT)); }
#line 2304 "parser.cpp"
    break;

  case 110:
#line 298 "parser.y"
                                    { edit->setCont((yyvsp[0].TEXT)); }
#line 2310 "parser.cpp"
    break;

  case 111:
#line 299 "parser.y"
                                    { edit->setCont((yyvsp[0].TEXT)); }
#line 2316 "parser.cpp"
    break;

  case 112:
#line 300 "parser.y"
                                    { edit->setStdin(); }
#line 2322 "parser.cpp"
    break;


#line 2326 "parser.cpp"

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
