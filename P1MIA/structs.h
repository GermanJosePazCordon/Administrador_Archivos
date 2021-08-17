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

    typedef struct{ //MBR para los discos
            int size;
            time_t date;
            char fit;
            int signature;
            partition particiones[4];

        } MBR;

    typedef struct{
            char status = 'i'; //i de inhabilitado a habilitado
            char fit = 'x';
            int start = 0;
            int size = 0;
            int next = -1;
            char name[16];
        } EBR;

    typedef struct{
            char letter; // a b c
            char status = 'i';//i de inhabilitado a habilitado
            char type = 'x';//tipo de mkfs ext2='2' ex3='3'
            string name;
            string id;
        } particionMontada;

    typedef struct{ //discos montados
            int number;//arrelo +1
            string path;
            char status = 'i'; //i de inhabilitado a habilitado
            particionMontada particiones[99];
        } Discos;
};
#endif // STRUCTS_H
