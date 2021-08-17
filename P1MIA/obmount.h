#ifndef OBMOUNT_H
#define OBMOUNT_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obmount
{
public:
    obmount();

    string path = "";
    string name = "";

    void setPath(string path);

    void setName(string name);

    bool validarParametros();

    void exec();

    void mount(int diskPos);

    void mostrarDatos();

};

#endif // OBMOUNT_H
