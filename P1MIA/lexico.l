%option case-insensitive
%option yylineno

%{
#include <iostream>
#include <QString>
#include "parser.h"

#include <string>
#include <QList>
    int yylex();
    void yyerror(const char *s);
    int linea = 0;
    int columna = 1;
    int anterior = 0;
%}
%option noyywrap
%option nounput


numero [0-9]+
letra [a-zA-ZÑñáéíóúÁÉÍÓÚ]+
positivo ([1-9]|0?)+


identificador {letra}({letra}|numero|"_")*
caracter "\'"("\\")?({letra}|numero)"\'"
cadena \"(\\\"|\\n|\\t|\\r|\\\\|[^\"])*\"
ruta (([/]([a-zA-Z]|[0-9]|"_"|".")+)+)

%x COM


%%

"MKDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MKDISK;}
"RMDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return RMDISK;}

"SIZE" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return SIZE;}
"PATH" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return PATH;}

"U" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return letU;}
"F" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return letF;}

{positivo} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return POSITIVO;}
{ruta} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return RUTA;}

{letra} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return LETRA;}
{cadena} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return CADENA;}

{identificador} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return IDENTIFICADOR;}
{caracter} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return CARACTER;}

"=" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return IGUAL;}
"-" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MENOS;}
"\\\"" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return COMILLA;}

"\n" {linea++; columna=0; anterior=0;}
[[:blank:]] { columna++; }

. {

std::cout<<"Error Lexico: "<<linea<<"\n";
//printf("Error lexico en linea %d",linea);

}
