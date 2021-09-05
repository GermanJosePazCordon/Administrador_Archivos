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
%token<TEXT> REP;
%token<TEXT> CAT;
%token<TEXT> REN;
%token<TEXT> RM;
%token<TEXT> EDIT;
%token<TEXT> EXEC;
%token<TEXT> PAUSE;
%token<TEXT> MV;
%token<TEXT> CP;
%token<TEXT> FIND;
%token<TEXT> LOGIN;
%token<TEXT> LOGOUT;
%token<TEXT> MKGRP;
%token<TEXT> RMGRP;
%token<TEXT> MKUSR;
%token<TEXT> RMUSR;

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
%token<TEXT> RUTAS;
%token<TEXT> ROOT;
%token<TEXT> DEST;
%token<TEXT> USER;
%token<TEXT> PWD;
%token<TEXT> USR;
%token<TEXT> GRP;

//LETRAS
%token<TEXT> letF;
%token<TEXT> letU;
%token<TEXT> letR;

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
      MKDISK { mdisk = new obmkdisk();   /*objeto mkdisk*/} COMANDOMKDISK  { mdisk->exec();  /*ejecutar mkdisk*/}
    | RMDISK { rmdisk = new obrmdisk();  /*objeto rmdisk*/} COMANDORMDISK  { rmdisk->exec(); /*ejecutar rmdisk*/}
    | FDISK  { fdisk = new obfdisk();    /*objeto fdisk*/ } COMANDOFDISK   { fdisk->exec();  /*ejecutar fdisk*/ }
    | MOUNT  { mount = new obmount();    /*objeto mount*/ } COMANDOMOUNT   { mount->exec();  /*ejecutar mount*/ }
    | UMOUNT { umount = new obumount();  /*objeto umount*/} COMANDOUMOUNT  { umount->exec(); /*ejecutar umount*/}
    | MKFS   { mkfs = new obmkfs();        /*objeto mkfs*/} COMANDOMKFS    { mkfs->exec();     /*ejecutar mkfs*/}
    | TOUCH  { touch = new obtouch();     /*objeto touch*/} COMANDOTOUCH   { touch->exec();   /*ejecutar touch*/}
    | MKDIR  { mkdir = new obmkdir();     /*objeto mkdir*/} COMANDOMKDIR   { mkdir->exec();   /*ejecutar mkdir*/}
    | REP    { reporte = new obreporte();   /*objeto rep*/} COMANDOREPORTE { reporte->exec();   /*ejecutar rep*/}
    | CAT    { cat = new obcat();           /*objeto cat*/} COMANDOCAT     { cat->exec();       /*ejecutar cat*/}
    | REN    { ren = new obren();           /*objeto ren*/} COMANDOREN     { ren->exec();       /*ejecutar ren*/}
    | RM     { rm = new obrm();              /*objeto rm*/} COMANDORM      { rm->exec();         /*ejecutar rm*/}
    | EDIT   { edit = new obedit();        /*objeto edit*/} COMANDOEDIT    { edit->exec();     /*ejecutar edit*/}
    | EXEC   { exec = new obexec();        /*objeto exec*/} COMANDOEXEC    { exec->exec();     /*ejecutar exec*/}
    | MV     { mv = new obmv();              /*objeto mv*/} COMANDOMV      { mv->exec();         /*ejecutar mv*/}
    | CP     { cp = new obcp();              /*objeto cp*/} COMANDOCP      { cp->exec();         /*ejecutar cp*/}
    | FIND   { finds = new obfind();       /*objeto find*/} COMANDOFIND    { finds->exec();    /*ejecutar find*/}
    | LOGIN  { login = new oblogin();     /*objeto login*/} COMANDOLOGIN   { login->exec();   /*ejecutar login*/}
    | LOGOUT { logout = new oblogout();                                      logout->exec();    /*objeto login*/}
    | MKGRP  { mkgrp = new obmkgrp();     /*objeto mkgrp*/} COMANDOMKGRP   { mkgrp->exec();   /*ejecutar mkgrp*/}
    | RMGRP  { rmgrp = new obrmgrp();     /*objeto rmgrp*/} COMANDORMGRP   { rmgrp->exec();   /*ejecutar rmgrp*/}
    | MKUSR  { mkusr = new obmkusr();     /*objeto mkusr*/} COMANDOMKUSR   { mkusr->exec();   /*ejecutar mkusr*/}
    | RMUSR  { rmusr = new obrmusr();     /*objeto rmusr*/} COMANDORMUSR   { rmusr->exec();   /*ejecutar rmusr*/}
    | PAUSE  { system("read -p 'Presss <ENTER> to continue...' var"); }
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

COMANDOREPORTE:
      COMANDOREPORTE PARREP   {  }
    | PARREP                  {  }
;

PARREP: /*parametros para reporte*/
      MENOS PATH IGUAL RUTA              { reporte->setPath($4); }
    | MENOS PATH IGUAL CADENA            { reporte->setPath($4); }
    | MENOS ID IGUAL CADENA              { reporte->setID($4); }
    | MENOS ID IGUAL IDMOUNT             { reporte->setID($4); }
    | MENOS NAME IGUAL CADENA            { reporte->setName($4); }
    | MENOS NAME IGUAL IDENTIFICADOR     { reporte->setName($4); }
    | MENOS RUTAS IGUAL CADENA           { reporte->setRuta($4); }
    | MENOS RUTAS IGUAL RUTA             { reporte->setRuta($4); }
    | MENOS ROOT IGUAL POSITIVO          { reporte->setRoot(atoi($4)); }
;

COMANDOCAT:
        COMANDOCAT PARCAT     {  }
      | PARCAT                {  }
;

PARCAT: /*parametros para cat*/
      MENOS IDENTIFICADOR IGUAL RUTA     { cat->addFile($2, $4); }
    | MENOS IDENTIFICADOR IGUAL CADENA   { cat->addFile($2, $4); }
;

COMANDOREN:
      COMANDOREN PARREN     {  }
    | PARREN                {  }
;

PARREN: /*parametros para ren*/
      MENOS PATH IGUAL RUTA            { ren->setPath($4); }
    | MENOS PATH IGUAL CADENA          { ren->setPath($4); }
    | MENOS NAME IGUAL IDENTIFICADOR   { ren->setName($4); }
    | MENOS NAME IGUAL CADENA          { ren->setName($4); }
;

COMANDORM:
      COMANDORM PARRM     {  }
    | PARRM               {  }
;

PARRM: /*parametros para rm*/
      MENOS PATH IGUAL RUTA       { rm->setPath($4); }
    | MENOS PATH IGUAL CADENA     { rm->setPath($4); }
;

COMANDOEDIT:
      COMANDOEDIT PAREDIT   {  }
    | PAREDIT               {  }
;

PAREDIT: /*parametros para edit*/
      MENOS PATH IGUAL RUTA       { edit->setPath($4); }
    | MENOS PATH IGUAL CADENA     { edit->setPath($4); }
    | MENOS CONT IGUAL RUTA       { edit->setCont($4); }
    | MENOS CONT IGUAL CADENA     { edit->setCont($4); }
    | MENOS STDIN                 { edit->setStdin(); }
;

COMANDOEXEC: /*parametros para exec*/
      MENOS PATH IGUAL RUTA       { exec->setPath($4); }
    | MENOS PATH IGUAL CADENA     { exec->setPath($4); }
;

COMANDOMV:
      COMANDOMV PARMV     {  }
    | PARMV               {  }
;

PARMV: /*parametros para mv*/
      MENOS PATH IGUAL RUTA       { mv->setPath($4); }
    | MENOS PATH IGUAL CADENA     { mv->setPath($4); }
    | MENOS DEST IGUAL RUTA       { mv->setDest($4); }
    | MENOS DEST IGUAL CADENA     { mv->setDest($4); }
;

COMANDOCP:
      COMANDOCP PARCP     {  }
    | PARCP               {  }
;

PARCP: /*parametros para cp*/
      MENOS PATH IGUAL RUTA       { cp->setPath($4); }
    | MENOS PATH IGUAL CADENA     { cp->setPath($4); }
    | MENOS DEST IGUAL RUTA       { cp->setDest($4); }
    | MENOS DEST IGUAL CADENA     { cp->setDest($4); }
;

COMANDOFIND:
      COMANDOFIND PARFIND     {  }
    | PARFIND                 {  }
;

PARFIND: /*parametros para find*/
      MENOS PATH IGUAL RUTA                { finds->setPath($4); }
    | MENOS PATH IGUAL CADENA              { finds->setPath($4); }
    | MENOS NAME IGUAL IDENTIFICADOR       { finds->setName($4); }
    | MENOS NAME IGUAL CADENA              { finds->setName($4); }
;

COMANDOLOGIN:
      COMANDOLOGIN PARLOGIN     {  }
    | PARLOGIN                  {  }
;

PARLOGIN: /*parametros para login*/
      MENOS USER IGUAL IDENTIFICADOR   { login->setUser($4); }
    | MENOS USER IGUAL CADENA          { login->setUser($4); }
    | MENOS USER IGUAL ROOT            { login->setUser($4); }
    | MENOS PWD IGUAL IDENTIFICADOR    { login->setPwd($4); }
    | MENOS PWD IGUAL POSITIVO         { login->setPwd($4); }
    | MENOS PWD IGUAL CADENA           { login->setPwd($4); }
    | MENOS ID IGUAL IDMOUNT           { login->setID($4); }
    | MENOS ID IGUAL CADENA            { login->setID($4); }
;

COMANDOMKGRP:
      COMANDOMKGRP PARMKGRP     {  }
    | PARMKGRP                  {  }
;

PARMKGRP: /*parametros para mkgrp*/
      MENOS NAME IGUAL IDENTIFICADOR   { mkgrp->setName($4); }
    | MENOS NAME IGUAL CADENA          { mkgrp->setName($4); }
    | MENOS NAME IGUAL ROOT            { mkgrp->setName($4); }
;

COMANDORMGRP:
      COMANDORMGRP PARRMGRP     {  }
    | PARRMGRP                  {  }
;

PARRMGRP: /*parametros para rmgrp*/
      MENOS NAME IGUAL IDENTIFICADOR   { rmgrp->setName($4); }
    | MENOS NAME IGUAL CADENA          { rmgrp->setName($4); }
    | MENOS NAME IGUAL ROOT            { rmgrp->setName($4); }
;

COMANDOMKUSR:
      COMANDOMKUSR PARMKUSR     {  }
    | PARMKUSR                  {  }
;

PARMKUSR: /*parametros para mkusr*/
      MENOS USR IGUAL IDENTIFICADOR   { mkusr->setUsr($4); }
    | MENOS USR IGUAL CADENA          { mkusr->setUsr($4); }
    | MENOS USR IGUAL ROOT            { mkusr->setUsr($4); }
    | MENOS PWD IGUAL IDENTIFICADOR   { mkusr->setPwd($4); }
    | MENOS PWD IGUAL CADENA          { mkusr->setPwd($4); }
    | MENOS PWD IGUAL POSITIVO        { mkusr->setPwd($4); }
    | MENOS GRP IGUAL CADENA          { mkusr->setGrp($4); }
    | MENOS GRP IGUAL IDENTIFICADOR   { mkusr->setGrp($4); }
;

COMANDORMUSR:
      COMANDORMUSR PARRMUSR     {  }
    | PARRMUSR                  {  }
;

PARRMUSR: /*parametros para rmusr*/
      MENOS USR IGUAL IDENTIFICADOR   { rmusr->setUsr($4); }
    | MENOS USR IGUAL CADENA          { rmusr->setUsr($4); }
    | MENOS USR IGUAL ROOT            { rmusr->setUsr($4); }
;

