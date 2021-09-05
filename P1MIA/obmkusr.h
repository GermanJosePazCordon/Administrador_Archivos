#ifndef OBMKUSR_H
#define OBMKUSR_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obmkusr
{
public:
    obmkusr();

    string usr = "";
    string pwd = "";
    string grp = "";

    void setUsr(string usr);

    void setPwd(string pwd);

    void setGrp(string grp);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    list<string> separar_carpetas(string path);

    list<string> separar_comas(string path);

    void exec();

};

#endif // OBMKUSR_H
