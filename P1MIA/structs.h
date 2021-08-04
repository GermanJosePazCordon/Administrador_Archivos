#ifndef STRUCTS_H
#define STRUCTS_H

#include "string"

using namespace std;

class Structs{
public:
    typedef struct{ //Struct de la particion principal y extendida
            char status = 'i'; //i de inhabilitado a habilitado
            char type = 'x';
            char fit;
            int start;
            int size;
            char name[16];

        } partition;

    typedef struct //MBR para los discos
        {
            int size;
            time_t date;
            char fit;
            int signature;
            partition particiones[4];

        } MBR;
};

#endif // STRUCTS_H
