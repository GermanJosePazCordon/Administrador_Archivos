/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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


#line 124 "parser.h"

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
