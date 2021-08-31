#ifndef OBRM_H
#define OBRM_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obrm
{
public:
    obrm();

    string path = "";

    void setPath(string path);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    void saveBC(Structs::BC bc, string path, int pos);

    list<string> separar_carpetas(string path);

    void exec();

    void delInodo(int root, string path, int start);

    void delBC(int bloque, string path, int start);

    void delBAR(int bloque, string path, int start);

};

#endif // OBRM_H
