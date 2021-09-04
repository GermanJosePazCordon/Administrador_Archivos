#ifndef OBLOGIN_H
#define OBLOGIN_H
#include <QString>
#include "string"
#include "structs.h"

using namespace std;

class oblogin
{
public:
    oblogin();

    string user = "";
    string pwd = "";
    string id = "";

    void setUser(string user);

    void setPwd(string pwd);

    void setID(string id);

    void exec();

};

#endif // OBLOGIN_H
