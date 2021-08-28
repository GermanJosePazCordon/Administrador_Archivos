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

//COMANDOS
%token<TEXT> MKDISK;
%token<TEXT> RMDISK;
%token<TEXT> FDISK;
%token<TEXT> MOUNT;
%token<TEXT> UMOUNT;
%token<TEXT> MKFS;
%token<TEXT> TOUCH;
%token<TEXT> MKDIR;

//PARAMETROS
%token<TEXT> SIZE;
%token<TEXT> PATH;
%token<TEXT> TYPE;
%token<TEXT> NAME;
%token<TEXT> ADD;
%token<TEXT> DELETE;
%token<TEXT> ID;
%token<TEXT> FS;
%token<TEXT> CONT;
%token<TEXT> STDIN;

//LETRAS
%token<TEXT> letF;
%token<TEXT> letU;
%token<TEXT> letR;
%token<TEXT> letP;

//SIMBOLOS
%token<TEXT> IGUAL;
%token<TEXT> MENOS;

//NUMEROS
%token<TEXT> POSITIVO;

//TEXTO
%token<TEXT> RUTA;
%token<TEXT> LETRA;
%token<TEXT> CADENA;
%token<TEXT> IDENTIFICADOR;
%token<TEXT> IDMOUNT;
%token<TEXT> IDFS;


%start INICIO
%%

INICIO:
    INSTRUCCIONES {  }
;

INSTRUCCIONES:
      INSTRUCCIONES INSTRUCCION     {  }
    | INSTRUCCION                   {  }

INSTRUCCION:
      MKDISK { mdisk = new obmkdisk();  /*objeto mkdisk*/} COMANDOMKDISK   { mdisk->exec();  /*ejecutar mkdisk*/}
    | RMDISK { rmdisk = new obrmdisk(); /*objeto rmdisk*/} COMANDORMDISK   { rmdisk->exec(); /*ejecutar rmdisk*/}
    | FDISK  { fdisk = new obfdisk();   /*objeto fdisk*/ } COMANDOFDISK    { fdisk->exec();  /*ejecutar fdisk*/ }
    | MOUNT  { mount = new obmount();   /*objeto mount*/ } COMANDOMOUNT    { mount->exec();  /*ejecutar mount*/ }
    | UMOUNT { umount = new obumount(); /*objeto umount*/} COMANDOUMOUNT   { umount->exec(); /*ejecutar umount*/}
    | MKFS   { mkfs = new obmkfs();       /*objeto mkfs*/} COMANDOMKFS     { mkfs->exec();     /*ejecutar mkfs*/}
    | TOUCH  { touch = new obtouch();    /*objeto touch*/} COMANDOTOUCH    { touch->exec();   /*ejecutar touch*/}
    | MKDIR  { mkdir = new obmkdir();    /*objeto mkdir*/} COMANDOMKDIR    { mkdir->exec();   /*ejecutar mkdir*/}
;

COMANDOMKDISK:
        COMANDOMKDISK PARMKDISK     {  }
      | PARMKDISK                   {  }
;

PARMKDISK: /*parametros para mkdisk*/
        MENOS SIZE IGUAL POSITIVO       { mdisk->setSize(atoi($4)); }
      | MENOS PATH IGUAL RUTA           { mdisk->setPath($4); }
      | MENOS PATH IGUAL CADENA         { mdisk->setPath($4); }
      | MENOS letU IGUAL LETRA          { mdisk->setUnit($4); }
      | MENOS letF IGUAL IDENTIFICADOR  { mdisk->setFit($4); }
;

COMANDORMDISK: /*parametros para rmdisk*/
        MENOS PATH IGUAL RUTA           { rmdisk->setPath($4); }
      | MENOS PATH IGUAL CADENA         { rmdisk->setPath($4); }
;

COMANDOFDISK:
        COMANDOFDISK PARFDISK     {  }
      | PARFDISK                  {  }
;

PARFDISK: /*parametros para fdisk*/
        MENOS SIZE IGUAL POSITIVO          { fdisk->setSize(atoi($4)); }
      | MENOS PATH IGUAL RUTA              { fdisk->setPath($4); }
      | MENOS PATH IGUAL CADENA            { fdisk->setPath($4); }
      | MENOS letU IGUAL LETRA             { fdisk->setUnit($4); }
      | MENOS letF IGUAL IDENTIFICADOR     { fdisk->setFit($4); }
      | MENOS TYPE IGUAL LETRA             { fdisk->setType($4); }
      | MENOS NAME IGUAL CADENA            { fdisk->setName($4); }
      | MENOS NAME IGUAL IDENTIFICADOR     { fdisk->setName($4); }
      | MENOS ADD  IGUAL POSITIVO          { fdisk->setAdd(atoi($4)); }
      | MENOS ADD  IGUAL MENOS POSITIVO    { fdisk->setAdd(atoi($5) * -1); }
      | MENOS DELETE IGUAL IDENTIFICADOR   { fdisk->setDelet($4); }
;

COMANDOMOUNT:
        COMANDOMOUNT PARMOUNT     {  }
      | PARMOUNT                  {  }
;

PARMOUNT:  /*parametros para mount*/
        MENOS PATH IGUAL RUTA              { mount->setPath($4); }
      | MENOS PATH IGUAL CADENA            { mount->setPath($4); }
      | MENOS NAME IGUAL CADENA            { mount->setName($4); }
      | MENOS NAME IGUAL IDENTIFICADOR     { mount->setName($4); }
;

COMANDOUMOUNT: /*parametros para umount*/
        MENOS ID IGUAL IDMOUNT   { umount->setID($4); }
      | MENOS ID IGUAL CADENA    { umount->setID($4); }
;

COMANDOMKFS:
        COMANDOMKFS PARMKFS  {  }
      | PARMKFS              {  }
;

PARMKFS:
        MENOS ID IGUAL IDMOUNT          { mkfs->setID($4); }
      | MENOS ID IGUAL CADENA           { mkfs->setID($4); }
      | MENOS TYPE IGUAL IDENTIFICADOR  { mkfs->setType($4); }
      | MENOS FS IGUAL IDFS             { mkfs->setFS($4); }
;

COMANDOTOUCH:
        COMANDOTOUCH PARTOUCH   {  }
      | PARTOUCH                {  }
;

PARTOUCH: /*parametros para touch*/
        MENOS PATH IGUAL RUTA              { touch->setPath($4); }
      | MENOS PATH IGUAL CADENA            { touch->setPath($4); }
      | MENOS CONT IGUAL RUTA              { touch->setCont($4); }
      | MENOS CONT IGUAL CADENA            { touch->setCont($4); }
      | MENOS SIZE IGUAL POSITIVO          { touch->setSize(atoi($4)); }
      | MENOS letR                         { touch->setR(); }
      | MENOS STDIN                        { touch->setStdin(); }
;

COMANDOMKDIR:
        COMANDOMKDIR PARMKDIR   {  }
      | PARMKDIR                {  }
;

PARMKDIR: /*parametros para mkdir*/
        MENOS PATH IGUAL RUTA              { mkdir->setPath($4); }
      | MENOS PATH IGUAL CADENA            { mkdir->setPath($4); }
      | MENOS LETRA                        { mkdir->setP($2); }
;
