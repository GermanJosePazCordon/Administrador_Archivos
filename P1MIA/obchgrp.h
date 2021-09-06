#ifndef OBCHGRP_H
#define OBCHGRP_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obchgrp
{
public:
    obchgrp();

    string usr = "";
    string grp = "";

    void setUsr(string usr);

    void setGrp(string grp);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    list<string> separar_carpetas(string path);

    list<string> separar_comas(string path);

    void exec();

};

#endif // OBCHGRP_H
