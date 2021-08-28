#ifndef OBMKFS_H
#define OBMKFS_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obmkfs
{
public:
    obmkfs();

    string id = "";
    string type = "full";
    string fs = "2fs";

    void setID(string id);

    void setType(string type);

    void setFS(string fs);

    void save();

    void saveJournaling(Structs::Journaling journaling, string path,  int pos);

    Structs::Journaling getJournaling(string path, int pos);

    void addJournaling(string content, string nombre, string path, string operacion, char tipo, int pos);

    void exec();

    void xd();

};

#endif // OBMKFS_H
