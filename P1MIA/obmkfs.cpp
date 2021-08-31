#include "obmkfs.h"
#include "iostream"
#include "structs.h"

using namespace std;

obmkfs::obmkfs()
{

}

extern Structs::Discos discos[99];

//--------------------------SETERS-----------------------------------

void obmkfs::setID(string id){
    if(id[0] == '"'){
        this->id = id.substr(1, id.size()-1);
        this->id = this->id.substr(0, this->id.size()-1);
    }else{
        this->id = id;
    }
}

void obmkfs::setType(string type){
    string data = type;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    type = data;
    this->type = type;
}

void obmkfs::setFS(string fs){
    string data = fs;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    fs = data;
    this->fs = fs;
}

void obmkfs::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obmkfs::addJournaling(string content, string nombre, string path, string operacion, char tipo, int pos){
    Structs::Journaling jng;
    strcpy(jng.contenido, content.c_str());
    jng.date = time(0);
    strcpy(jng.path, nombre.c_str());
    jng.size = 0;
    strcpy(jng.operacion, operacion.c_str());
    jng.tipo = tipo;
    saveJournaling(jng, path, pos);
}

void obmkfs::exec(){
    Structs::Discos discoMontado;
    Structs::particionMontada particionMontada;
    Structs::partition particion;
    int ext_start;
    if(this->id == ""){
        cout<<"\nNo se ha ingresado ningun id"<<endl;
        return;
    }
    //VALIDANDO SI LA PARTICION YA ESTA MONTADA
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 99; j++){
            if(discos[i].particiones[j].id == this->id){
                discoMontado = discos[i];
                particionMontada = discos[i].particiones[j];
                break;
            }
        }
    }
    if(particionMontada.id == ""){
        cout<<"\nNo existe la particion montada con el id : "<<this->id<<endl;
        return;
    }
    //OBTENIENDO LA PARTICION DEL DISCO, LA QUE SE ENCUENTRA EN EL MBR O EL EBR
    Structs::MBR mbr;
    FILE * file = NULL;
    file = fopen(discoMontado.path.c_str(), "r");
    if (file != NULL){
        fread(&mbr, sizeof(Structs::MBR), 1, file);
        fclose(file);
    }
    for(int i = 0; i < 4; i++){
        if(mbr.particiones[i].name == particionMontada.name){
            particion = mbr.particiones[i];
        }
        if(mbr.particiones[i].type == 'e'){
            ext_start = mbr.particiones[i].start;
        }
    }
    if(particion.type == 'x'){
        //VALIDANDO SI LA PARTICION ES LOGICA
        Structs::EBR ebr;
        Structs::EBR pre_ebr;
        FILE * file = NULL;
        file = fopen(discoMontado.path.c_str(), "rb+");
        fseek(file, ext_start, SEEK_SET);
        fread(&ebr, sizeof(Structs::EBR), 1, file);
        fclose(file);
        bool seguimos = true;
        while(seguimos){
            if(ebr.next == -1){
                break;
            }
            if(ebr.name == particionMontada.name){
                particion.size = ebr.size;
                particion.start = ebr.start;
                particion.type = 'l';
            }
            pre_ebr = ebr;
            FILE * file = NULL;
            file = fopen(discoMontado.path.c_str(), "rb+");
            fseek(file, pre_ebr.next, SEEK_SET);
            fread(&ebr, sizeof(Structs::EBR), 1, file);
            fclose(file);
        }
    }
    int numInodos;
    if(this->fs == "2fs"){
        //SISTEMA DE ARCHIVOS EXT2
        numInodos = ((particion.size - sizeof(Structs::SB))/(4 + sizeof(Structs::TI) + 3 * sizeof(Structs::BAR)));
    }else{
        //SISTEMA DE ARCHIVOS EXT3
        numInodos = ((particion.size - sizeof(Structs::SB) - 100 * sizeof(Structs::BC))/(4 + sizeof(Structs::TI) + 3 * sizeof(Structs::BAR)));
    }
    //ESCRIBIENDO EL SUPER BLOQUE
    Structs::SB sb;
    sb.mnt_count = 1;
    sb.magic = 0xEF53;
    if(this->fs == "2fs"){
        sb.filesystem_type = 2;
    }else{
        sb.filesystem_type = 3;
    }
    sb.inodes_count = numInodos;
    sb.blocks_count = numInodos * 3;
    sb.free_blocks_count = numInodos * 3;
    sb.free_inodes_count = numInodos;
    sb.mtime = particionMontada.mtime;
    sb.umtime = particionMontada.umtime;
    sb.inode_size = sizeof(Structs::TI);
    sb.block_size = sizeof(Structs::BAR);
    sb.firts_ino = 0 ;
    sb.first_blo = 0;
    if(this->fs == "2fs"){
        sb.bm_inode_start = particion.start + sizeof(Structs::SB);
    }else{
        sb.bm_inode_start = particion.start + sizeof(Structs::SB) + 6400;
    }
    sb.bm_block_start = sb.bm_inode_start + numInodos;
    sb.inode_start = sb.bm_block_start + 3 * numInodos;
    sb.block_start = sb.inode_start + numInodos * sizeof(Structs::TI);
    if(this->type == "full"){
        file = fopen(discoMontado.path.c_str(), "rb+");
        for(int i = sb.inode_start; i < (particion.size + particion.start); i++){
            fseek(file, i, SEEK_SET);
            fwrite("\0", 1, 1, file);
        }
        fclose(file);
    }
    //CREANDO LA CARPETA ROOT
    Structs::Journaling journaling;
    Structs::TI inodo;
    Structs::BC carpeta;
    if(this->fs == "3fs"){
        addJournaling("-", "/", discoMontado.path, "mkdir", '0', (particion.start + sizeof(Structs::SB)));
    }
    //CREANDO EL NUEVO INODO CARPETA
    inodo.type = '0';
    inodo.uid = 1;
    inodo.gid = 1;
    inodo.size = 0;
    inodo.block[0] = 0;
    inodo.atime = time(0);
    inodo.ctime = time(0);
    inodo.mtime = time(0);
    inodo.perm = 664;
    for(int i = 1; i < 15; i++){
        inodo.block[i] = -1;
    }
    //GUARDANDO EL INODO
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.inode_start, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    //CREANDO CARPETA
    //PADRE
    carpeta.content[0].inodo = 0;
    strcpy(carpeta.content[0].name, ".");
    //ABUELO
    carpeta.content[1].inodo = 0;
    strcpy(carpeta.content[1].name, "..");
    //USERS
    carpeta.content[2].inodo = 1;
    strcpy(carpeta.content[2].name, "user.txt");
    //GUARDANDO LA CARPETA
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.block_start, SEEK_SET);
    fwrite(&carpeta, sizeof(Structs::BC), 1, file);
    fclose(file);
    //CREANDO EL ARCHIVO INICIAL
    if(this->fs == "3fs"){
        addJournaling("1,G,root\n1,U,root,root,123\n", "uset.txt", discoMontado.path, "touch", '1', (particion.start + sizeof(Structs::SB) + sizeof(Structs::Journaling)));
    }
    //INODO ARCHIVO
    inodo.type = '1';
    inodo.uid = 1;
    inodo.gid = 1;
    inodo.size = sizeof("1,G,root\n1,U,root,root,123\n");
    inodo.block[0] = 1;
    inodo.atime = time(0);
    inodo.ctime = time(0);
    inodo.mtime = time(0);
    inodo.perm = 664;
    for(int i = 1; i < 15; i++){
        inodo.block[i] = -1;
    }
    //GUARDANDO EL INODO
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.inode_start + sizeof(Structs::TI), SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    //CREANDO ARCHIVO USUARIOS
    Structs::BAR archivo;
    strcpy(archivo.content, "1,G,root\n1,U,root,root,123\n");
    //GUARDANDO EL ARCHIVO
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.block_start + sizeof(Structs::BC), SEEK_SET);
    fwrite(&archivo, sizeof(Structs::BAR), 1, file);
    fclose(file);
    //ACTUALIZANDO EL SUPER BLOQUE
    sb.free_inodes_count = sb.inodes_count - 2;
    sb.free_blocks_count = sb.blocks_count - 2;
    sb.firts_ino = 2;
    sb.first_blo = 2;
    //GUARDANDO EL SUPER BLOQUE
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, particion.start, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    //SETEANDO LOS BITMAPS
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.bm_inode_start, SEEK_SET);
    fwrite("1", 1, 1, file);
    fseek(file, sb.bm_block_start, SEEK_SET);
    fwrite("1", 1, 1, file);
    fseek(file, sb.bm_inode_start + 1, SEEK_SET);
    fwrite("1", 1, 1, file);
    fseek(file, sb.bm_block_start + 1, SEEK_SET);
    fwrite("1", 1, 1, file);
    for(int i = sb.bm_inode_start + 2; i < sb.bm_block_start; i++){
        fseek(file, i, SEEK_SET);
        fwrite("0", 1, 1, file);
    }
    for(int i = sb.bm_block_start + 2; i < sb.inode_start; i++){
        fseek(file, i, SEEK_SET);
        fwrite("0", 1, 1, file);
    }
    fclose(file);
}
