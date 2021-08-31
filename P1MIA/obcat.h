#ifndef OBCAT_H
#define OBCAT_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obcat
{
public:
    obcat();

    list<string> lista_file;

    void addFile(string filen, string path);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    list<string> separar_carpetas(string path);

    void getInodoArchivo(string path, string path_particion, int start_particion);

    void exec();

};

#endif // OBCAT_H
