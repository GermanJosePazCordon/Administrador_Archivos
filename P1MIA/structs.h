#ifndef STRUCTS_H
#define STRUCTS_H

#include "string"

using namespace std;

class Structs{
public:
    typedef struct{ //Struct de la particion principal y extendida
            char part_status = 'i'; //i de inhabilitado a habilitado
            char part_type = 'x';
            char part_fit;
            int part_start;
            int part6_size;
            char part_name[16];

        } partition;

    typedef struct //MBR para los discos
        {
            int size;
            char date[16];
            char fit[1];
            int signature;
            partition particiones[4];

        } MBR;
};

#endif // STRUCTS_H
