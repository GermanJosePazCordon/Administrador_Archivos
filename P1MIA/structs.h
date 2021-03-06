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
            int start; //posicion inicial de la particion en el archivo, utilizada para obtener el sb mas adelante
            string name;
            string id;
            time_t mtime;
            time_t umtime;
        } particionMontada;

    typedef struct{ //discos montados
            int number;//arrelo +1
            string path;
            char status = 'i'; //i de inhabilitado a habilitado
            particionMontada particiones[99];
        } Discos;

    typedef struct{ //Super Bloque
            int filesystem_type = 2; //Numero del sistema de archivos utilizado
            int inodes_count = 0; //Guarda el número total de inodos
            int blocks_count = 0; //Guarda el número total de bloques
            int free_blocks_count = 0; //Contiene el número de bloques libres
            int free_inodes_count = 0; //Contiene el número de inodos libres
            time_t mtime; //Última fecha en el que el sistema fue montado
            time_t umtime; //Última fecha en que el sistema fue desmontado
            int mnt_count = 1; //Indica cuantas veces se ha montado el sistema
            int magic = 0; //Valor que identifica al sistema de archivos, tendrá el valor 0xEF53
            int inode_size = 0; //Tamaño del inodo
            int block_size = 0; //Tamaño del bloque
            int firts_ino = 0; //Primer inodo libre
            int first_blo = 0; //Primer bloque libre
            int bm_inode_start = 0; //Guardará el inicio del bitmap de inodos
            int bm_block_start = 0; //Guardará el inicio del bitmap de bloques
            int inode_start = 0; //Guardará el inicio de la tabla de inodos
            int block_start = 0; //Guardará el inicio de la tabla de bloques
        } SB;

    typedef struct{ //Tabla Inodos
            int uid;
            int gid;
            int size;
            time_t atime;
            time_t ctime;
            time_t mtime;
            int block[15];
            char type;
            int perm;
        } TI;

    typedef struct{ //Content
            char name[12];
            int inodo = -1;
        } Content;

    typedef struct{ //Bloque de carpeta
            Content content[4];
        } BC;

    typedef struct{ //Bloque de Archivos
            char content[64];
        } BAR;

    typedef struct{ //Bloque de Apuntadores
            int pointers[16];
        } BAP;

    typedef struct
        {
            char operacion[10] = "";
            char tipo = 'x';
            char path[40] = "";
            char contenido[100] = ""; // Validar cuando espacio necesitan.
            time_t date;
            int next = -1;
            int start;
        }Journaling; //typedef

    typedef struct
        {
            int guid;
            int uid;
            string user;
            string pwd;
            string id;
            char status = 'i'; //i inhabilitado, h habilitado
        }Login; //typedef
};
#endif // STRUCTS_H
