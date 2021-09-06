#ifndef OBRECOVERY_H
#define OBRECOVERY_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class obrecovery
{
public:
    obrecovery();

    string id = "";

    void setID(string id);

    void exec();

};

#endif // OBRECOVERY_H
