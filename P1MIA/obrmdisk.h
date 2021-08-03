#ifndef OBRMDISK_H
#define OBRMDISK_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obrmdisk
{
public:
    obrmdisk();

    string path = "";

    void setPath(string path);

    void exec();

};

#endif // OBRMDISK_H
