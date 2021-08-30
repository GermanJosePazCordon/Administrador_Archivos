#ifndef OBMKDIR_H
#define OBMKDIR_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obmkdir
{
public:
    obmkdir();

    string path = "";
    string letra = "";
    bool p = false;

    void setPath(string path);

    void setP(string letra);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    void saveSB(Structs::SB sb, string path, int pos);

    void saveInodo(Structs::TI inodo, string path, int pos);

    void saveBC(Structs::BC bc, string path, int pos);

    void saveBAR(Structs::BAR bar, string path, int pos);

    list<string> separar_carpetas(string path);

    void exec();

    void crearCarpeta(Structs::SB sb, int inodoPadre, int inodoAbuelo, string path, int start_particion);

};

#endif // OBMKDIR_H
