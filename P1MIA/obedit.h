#ifndef OBEDIT_H
#define OBEDIT_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obedit
{
public:
    obedit();

    string path = "";
    string cont = "";
    bool stdi = false;

    void setPath(string path);

    void setCont(string cont);

    void setStdin();

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    void saveBAR(Structs::BAR bar, string path, int pos);

    list<string> separar_carpetas(string path);

    void exec();

};

#endif // OBEDIT_H
