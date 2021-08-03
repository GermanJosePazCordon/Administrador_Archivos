%{
#include "scanner.h"//se importa el header del analisis sintactico
#include <QString>
#include <string>
#include "qdebug.h"
#include <iostream>

#include "obmkdisk.h"
obmkdisk * mdisk;

#include "obrmdisk.h"
obrmdisk * rmdisk;

using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

int yyerror(const char* mens)
{
std::cout << mens <<" "<<yytext<< std::endl;
return 0;
}
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
%locations
%union{
//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];

}
//TERMINALES DE TIPO TEXT, SON STRINGS

%token<TEXT> MKDISK;
%token<TEXT> RMDISK;

%token<TEXT> SIZE;
%token<TEXT> PATH;

%token<TEXT> letF;
%token<TEXT> letU;

%token<TEXT> IGUAL;
%token<TEXT> MENOS;

%token<TEXT> POSITIVO;

%token<TEXT> RUTA;
%token<TEXT> LETRA;
%token<TEXT> CADENA;
%token<TEXT> COMILLA;
%token<TEXT> IDENTIFICADOR;
%token<TEXT> CARACTER;


%start INICIO
%%

INICIO:
    INSTRUCCIONES {  }
;

INSTRUCCIONES:
      INSTRUCCIONES INSTRUCCION     {  }
    | INSTRUCCION                   {  }

INSTRUCCION:
      MKDISK { mdisk = new obmkdisk(); /*objeto mkdisk*/} COMANDOMKDISK     { mdisk->exec(); /*ejecutar mkdisk*/}
    | RMDISK { rmdisk = new obrmdisk(); /*objeto rmdisk*/} COMANDORMDISK    { rmdisk->exec(); /*ejecutar rmdisk*/}
;

COMANDOMKDISK:
        COMANDOMKDISK PARMKDISK     {  }
      | PARMKDISK                   {  }
;

PARMKDISK: /*parametros para mkdisk*/
        MENOS SIZE IGUAL POSITIVO   { mdisk->setSize(atoi($4)); }
      | MENOS PATH IGUAL RUTA       { mdisk->setPath($4); }
      | MENOS letU IGUAL LETRA      { mdisk->setUnit($4); }
      | MENOS letF IGUAL LETRA      { mdisk->setFit($4); }
;

COMANDORMDISK:
        MENOS PATH IGUAL RUTA       { rmdisk->setPath($4); }
;
