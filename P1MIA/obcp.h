#ifndef OCP_H
#define OBCP_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obcp
{
public:
    obcp();

    string path = "";
    string dest = "";

    void setPath(string path);

    void setDest(string dest);

    Structs::SB getSB(string path, int pos);

    Structs::TI getInodo(string path, int pos);

    Structs::BC getBC(string path, int pos);

    Structs::BAR getBAR(string path, int pos);

    void saveSB(Structs::SB sb, string path, int pos);

    void saveInodo(Structs::TI inodo, string path, int pos);

    void saveBC(Structs::BC bc, string path, int pos);

    void saveBAR(Structs::BAR bar, string path, int pos);

    Structs::Journaling getJournaling(string path, int pos);

    void saveJournaling(Structs::Journaling journaling, string path, int pos);

    void addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start);

    list<string> separar_carpetas(string path);

    void changeInodo(int root, string path, int start, int abuelo);

    void changeBC(int bloque, string path, int start, int padre, int abuelo);

    void changeBAR(int bloque, string path, int start);

    void exec();

};

#endif // OBCP_H
