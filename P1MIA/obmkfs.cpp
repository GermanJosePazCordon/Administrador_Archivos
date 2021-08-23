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

void obmkfs::exec(){
    if(false){
        xd();
        return;
    }
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
    //SETEAR LOS BITMAPS
    file = fopen(discoMontado.path.c_str(), "rb+");
    for(int i = sb.bm_inode_start; i < sb.bm_block_start; i++){
        fseek(file, i, SEEK_SET);
        fwrite("0", 1, 1, file);
    }
    for(int i = sb.bm_block_start; i < sb.inode_start; i++){
        fseek(file, i, SEEK_SET);
        fwrite("0", 1, 1, file);
    }
    fclose(file);
    //CREANDO LA CARPETA ROOT
    Structs::TI inodo;
    Structs::BC carpeta;
    //PADRE
    carpeta.content[0].inodo = 0;
    strcpy(carpeta.content[0].name, ".");
    //ABUELO
    carpeta.content[1].inodo = 0;
    strcpy(carpeta.content[1].name, "..");
    //USERS
    strcpy(carpeta.content[2].name, "user.txt");
    carpeta.content[2].inodo = 1;
    //CREANDO EL NUEVO INODO
    inodo.type = '0';
    inodo.uid = 1;
    inodo.gid = 1;
    inodo.size = 0;
    inodo.block[0] = 0;
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
    //GUARDANDO EL INODO
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.inode_start, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    //GUARDANDO LA CARPETA
    file = fopen(discoMontado.path.c_str(), "rb+");
    fseek(file, sb.block_start, SEEK_SET);
    fwrite(&carpeta, sizeof(Structs::BC), 1, file);
    fclose(file);

    cout<<"\nbm inode start : "<<sb.bm_inode_start<<endl;
    cout<<"\nbm block start : "<<sb.bm_block_start<<endl;
    cout<<"\ninode start : "<<sb.inode_start<<endl;
    cout<<"\nblock start : "<<sb.block_start<<endl;
}

void obmkfs::xd(){
    Structs::SB sb;
    Structs::TI inodo;
    Structs::BC carpeta;
    FILE * file = NULL;
    file = fopen("/home/monsterxd/Escritorio/Disco3.disk", "rb+");
    fseek(file, 136, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    cout<<"\nbm inode start : "<<sb.bm_inode_start<<endl;
    cout<<"\nbm block start : "<<sb.bm_block_start<<endl;
    cout<<"\ninode start : "<<sb.inode_start<<endl;
    cout<<"\nblock start : "<<sb.block_start<<endl;
    cout<<"\n-------------------------------------------------------------------"<<endl;
    file = fopen("/home/monsterxd/Escritorio/Disco3.disk", "rb+");
    fseek(file, sb.inode_start, SEEK_SET);
    fread(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    cout<<"\ninodo type : "<<inodo.type<<endl;
    cout<<"\ninodo uid : "<<inodo.uid<<endl;
    cout<<"\ninodo gid : "<<inodo.gid<<endl;
    cout<<"\ninodo size : "<<inodo.size<<endl;
    cout<<"\ninodo block[0] : "<<inodo.block[0]<<endl;
    cout<<"\n-------------------------------------------------------------------"<<endl;
    file = fopen("/home/monsterxd/Escritorio/Disco3.disk", "rb+");
    fseek(file, sb.block_start, SEEK_SET);
    fread(&carpeta, sizeof(Structs::BC), 1, file);
    fclose(file);
    cout<<"\ncarpeta inodo [0]: "<<carpeta.content[0].inodo<<endl;
    cout<<"\ncarpeta name  [0]: "<<carpeta.content[0].name<<endl;
    cout<<"\ncarpeta inodo [1]: "<<carpeta.content[1].inodo<<endl;
    cout<<"\ncarpeta name  [1]: "<<carpeta.content[1].name<<endl;
    cout<<"\ncarpeta inodo [2]: "<<carpeta.content[2].inodo<<endl;
    cout<<"\ncarpeta name  [2]: "<<carpeta.content[2].name<<endl;
}

