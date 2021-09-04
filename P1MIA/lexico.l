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

comentario [#]([^\n])*
numero [0-9]+
letra [a-zA-ZÑñáéíóúÁÉÍÓÚ]
positivo ([1-9]|0?)+


identificador ({letra}|"*"|"?")({letra}|{numero}|"_"|"."|"*"|"?")*
idmount {numero}{numero}{numero}({letra})+
idfs {numero}("fs"|"FS"|"Fs"|"fS")
cadena [\"][^\"\n]*[\"\n]
ruta (([/]([a-zA-Z]|[0-9]|"_"|".")+)+)

%x COM


%%

"MKDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MKDISK;}
"RMDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return RMDISK;}
"FDISK" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return FDISK;}
"MOUNT" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MOUNT;}
"UMOUNT" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return UMOUNT;}
"MKFS" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MKFS;}
"TOUCH" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return TOUCH;}
"MKDIR" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MKDIR;}
"REP" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return REP;}
"CAT" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return CAT;}
"REN" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return REN;}
"RM" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return RM;}
"EDIT" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return EDIT;}
"EXEC" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return EXEC;}
"PAUSE" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return PAUSE;}
"MV" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MV;}
"CP" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return CP;}
"FIND" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return FIND;}
"LOGIN" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return LOGIN;}
"LOGOUT" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return LOGOUT;}

"SIZE" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return SIZE;}
"PATH" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return PATH;}
"TYPE" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return TYPE;}
"NAME" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return NAME;}
"ADD" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ADD;}
"DELETE" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return DELETE;}
"ID" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ID;}
"FS" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return FS;}
"CONT" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return CONT;}
"STDIN" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return STDIN;}
"RUTA" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return RUTAS;}
"ROOT" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return ROOT;}
"DEST" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return DEST;}
"USER" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return USER;}
"PWD" {columna=columna+ anterior;  anterior = strlen(yytext); strcpy(yylval.TEXT, yytext);return PWD;}

"U" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return letU;}
"F" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return letF;}
"R" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return letR;}

{positivo} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return POSITIVO;}
{ruta} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return RUTA;}

{letra} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return LETRA;}
{cadena} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return CADENA;}

{identificador} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return IDENTIFICADOR;}
{idmount} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return IDMOUNT;}
{idfs} {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext); return IDFS;}

"=" {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return IGUAL;}
("-"|"–") {columna=columna+ anterior;  anterior = strlen(yytext);strcpy(yylval.TEXT, yytext);return MENOS;}

"\n" {linea++; columna=0; anterior=0;}
[[:blank:]] { columna++; }

. {

std::cout<<"Error Lexico: "<<linea<<"\n";
//printf("Error lexico en linea %d",linea);

}
