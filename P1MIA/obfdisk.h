#ifndef OBFDISK_H
#define OBFDISK_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obfdisk
{
public:
    obfdisk();

    Structs::MBR mbr;

    int size = 0;
    int add = 0;
    string fit = "";
    string unit = "";
    string path = "";
    string type = "";
    string delet = "";
    string name = "";

    void setSize(int size);

    void setAdd(int add);

    void setFit(string fit);

    void setUnit(string unit);

    void setPath(string path);

    void setType(string type);

    void setDelet(string delet);

    void setName(string name);

    void exec();

    void init();

    bool validarParametros();

    void getMBR(string path);

    void createPartition();

};

#endif // OBFDISK_H
