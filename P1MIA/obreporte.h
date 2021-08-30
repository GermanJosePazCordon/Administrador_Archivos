#ifndef OBREPORTE_H
#define OBREPORTE_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obreporte
{
public:
    obreporte();

    string path = "";
    string name = "";
    string id = "";
    string ruta = "";
    int root = 0;

    void setPath(string path);

    void setName(string name);

    void setID(string id);

    void setRuta(string ruta);

    void setRoot(int root);

    Structs::MBR getMBR(string path);

    Structs::EBR getEBR(string path, int pos);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    bool validarName();

    string getExt();

    string graphInodo(int root, string path, int start);

    string graphBC(int bloque, string path, int start);

    string graphBAR(int bloque, string path, int start);

    string graphMBR(string path);

    string graphDisk(string path);

    void generarDot(string content);

    void exec();

};

#endif // OBREPORTE_H
