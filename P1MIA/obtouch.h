#ifndef OBTOUCH_H
#define OBTOUCH_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obtouch
{
public:
    obtouch();

    string path = "";
    string cont = "";
    int size = 0;
    bool r = false;
    bool stdi = false;

    void setPath(string path);

    void setCont(string cont);

    void setSize(int size);

    void setR();

    void setStdin();

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

    void crearInodoArchivo(Structs::SB sb, string content, string path, int start_particion, int inodoPadre);

    void crearArchivo(int inodoPadre, int bloque, string content, string path, int start);

};

#endif // OBTOUCH_H
