#ifndef OBRMUSR_H
#define OBRMUSR_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obrmusr
{
public:
    obrmusr();

    string usr = "";

    void setUsr(string usr);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    list<string> separar_carpetas(string path);

    list<string> separar_comas(string path);

    void exec();

};

#endif // OBRMUSR_H
