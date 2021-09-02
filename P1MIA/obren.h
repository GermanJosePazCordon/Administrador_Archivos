#ifndef OBREN_H
#define OBREN_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obren
{
public:
    obren();

    string path = "";
    string name = "";

    void setPath(string path);

    void setName(string name);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    void saveBC(Structs::BC bc, string path, int pos);

    Structs::Journaling getJournaling(string path, int pos);

    void saveJournaling(Structs::Journaling journaling, string path, int pos);

    void addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start);

    list<string> separar_carpetas(string path);

    void getInodoArchivo(string path, string path_particion, int start_particion);

    void exec();

};

#endif // OBREN_H
