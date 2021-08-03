#ifndef OBMKDISK_H
#define OBMKDISK_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obmkdisk
{
public:
    obmkdisk();

    int size = 0;
    string fit = "";
    string unit = "";
    string path = "";

    void setSize(int size);

    void setFit(string fit);

    void setUnit(string unit);

    void setPath(string path);

    void mostrardatos(Structs::MBR mbr);

    void exec();

    void init();

    bool validarParametros();

};

#endif // OBMKDISK_H
