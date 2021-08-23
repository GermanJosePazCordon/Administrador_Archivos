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

    void exec();

    void xd();

};

#endif // OBMKFS_H
