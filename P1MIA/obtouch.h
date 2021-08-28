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

    void saveSB(Structs::SB sb, string path, int pos);

    Structs::SB getSB(string path, int pos);

    void saveJournaling(Structs::Journaling journaling, string path, int pos);

    void addJournaling(string content, string nombre, string path, string operacion, char tipo, int part_start);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    list<string> separar_carpetas(string path);

    void exec();

    void crearCarpeta(Structs::SB sb, int inodoPadre, int inodoAbuelo, string path, int start_particion);

    void crearInodoArchivo(Structs::SB sb, string content, string path, int start_particion, int inodoPadre);

    void crearArchivo(int inodoPadre, int bloque, string content, string path, int start);

};

#endif // OBTOUCH_H
