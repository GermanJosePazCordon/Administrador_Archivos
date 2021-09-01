#ifndef OBREPORTE_H
#define OBREPORTE_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

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

    list<string> separar_carpetas(string path);

    bool validarName();

    string getExt();

    string graphInodo(int root, string path, int start);

    string graphBC(int bloque, string path, int start);

    string graphBAR(int bloque, string path, int start);

    string graphSB(string path, int start);

    string graphFile(string path, string ruta, int start, int inodoPadre, string file_name);

    string graphMBR(string path);

    string graphDisk(string path);

    string graphUsedInode(int root, string name, string path, int start);

    string graphUsedBlockInode(int root, string path, int start);

    string graphUsedBlockBC(int bloque, string path, int start);

    string graphUsedBlockBAR(int bloque, string path, int start);

    string graphBMInode(string path, int start);

    string graphBMBlock(string path, int start);

    void generarDot(string content);

    void exec();

};

#endif // OBREPORTE_H
