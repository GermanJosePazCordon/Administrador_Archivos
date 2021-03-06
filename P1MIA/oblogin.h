#ifndef OBLOGIN_H
#define OBLOGIN_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class oblogin
{
public:
    oblogin();

    string user = "";
    string pwd = "";
    string id = "";

    void setUser(string user);

    void setPwd(string pwd);

    void setID(string id);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    list<string> separar_carpetas(string path);

    list<string> separar_comas(string path);

    void exec();

};

#endif // OBLOGIN_H
