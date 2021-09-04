#ifndef OBFIND_H
#define OBFIND_H
#include <QString>
#include "string"
#include "structs.h"
#include "list"

using namespace std;

class obfind
{
public:
    obfind();

    string path = "";
    string name = "";

    void setPath(string path);

    void setName(string name);

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

    void exec();

    void searchInodo(string name, string regex, int root, string path, int start);

    void searchBC(string name, string regex, int bloque, string path, int start);

    string formarRegex(string name);

    bool verificarMatch(string nombre, string regex);

};

#endif // OBFIND_H
