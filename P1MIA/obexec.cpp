#include "obexec.h"
#include "iostream"
#include "structs.h"
#include "fstream"
#include <parser.h>  // Nuestro parser
#include <scanner.h>  // Nuestro scanner

using namespace std;

obexec::obexec()
{

}
extern int yyparse(); //
extern int linea; // Linea del token
extern int columna; // Columna de los tokens
extern int yylineno;

//--------------------------SETERS-----------------------------------

void obexec::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obexec::exec(){
    if(this->path == ""){
        cout<<"\nRuta vacia"<<endl;
        return;
    }
    FILE * file = NULL;
    file = fopen(this->path.c_str(), "rb+");
    if(!file){
        cout<<"\nNo existe el archivo"<<endl;
        return;
    }
    fclose(file);
    ifstream script(this->path);
    string str;
    while (getline(script, str)) {
        cout<<str<< endl;
        if (str != "exit") {
            if (str != "") {
                YY_BUFFER_STATE buffer = yy_scan_string(str.c_str());

                if(yyparse()==0) // Si nos da un número negativo, signifca error.
                {
                    printf("\n********************************");
                    printf("\nComando ejecutado correctamente\n");
                    printf("********************************\n\n");

                }else {
                    printf("\n*******************************");
                    printf("\nNo se pudo ejecutar el comando\n");
                    printf("*******************************\n\n");
                }
            }
        }else{
            exit(1);
        }
    }
}
