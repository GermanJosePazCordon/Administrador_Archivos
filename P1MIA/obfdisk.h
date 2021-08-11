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
    string fit = "wf";
    string unit = "k";
    string type = "p";
    string path = "";
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

    char getFit(string fit);

    char getType(string type);

    void exec();

    void init();

    bool validarParametros();

    bool getMBR(string path);

    Structs::EBR getEBR(string path, int pos);

    void saveMBR(Structs::MBR);

    void saveEBR(Structs::EBR, int pos);

    void modifyEBR(Structs::EBR ebr);

    void newPartition(int pos, char status, char type, char fit, int start, int size, string name);

    void createPartition();

    void createLogicPartition();

    void deletePartition();

    void deleteLogic();

    void bubbleSort();

    bool validarTipo();

    void newEBR(char status, char fit, int start, int size, string name, int next, int pos);

};

#endif // OBFDISK_H
