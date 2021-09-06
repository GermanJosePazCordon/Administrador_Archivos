#ifndef OBLOSS_H
#define OBLOSS_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obloss
{
public:
    obloss();

    string id = "";

    void setID(string id);

    void exec();

};

#endif // OBLOSS_H
