#include "obmount.h"
#include "iostream"
#include "structs.h"

using namespace std;

obmount::obmount()
{

}

extern Structs::Discos discos[99];

//--------------------------SETERS-----------------------------------

void obmount::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obmount::setName(string name){
    if(name[0] == '"'){
        this->name = name.substr(1, path.size()-1);
        this->name = this->name.substr(0, this->name.size()-1);
    }else{
        this->name = name;
    }
}

bool obmount::validarParametros(){
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return true;
    }
    if(this->name == ""){
        cout<<"\nNombre vacio."<<endl;
        return true;
    }
}

void obmount::mostrarDatos(){
    cout << "\n-------------------------- MONTADAS ----------------------"<< endl;
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].status == 'h'){
                cout<<"\n"<<discos[i].path<<" | "<<discos[i].particiones[j].name<<" | "<<discos[i].particiones[j].id<<endl;
            }
        }
    }
}

void obmount::exec(){
    bool isNormal = false;//BOOLEANO PARA DETERMINAR SI LA PARTICION ES PRIMARIA O EXTENDIDA
    bool isLogic = false;//BOOLEANO PARA DETERMINAR SI LA PARTICION ES LOGICA
    if(validarParametros()){
        cout<<"\nNo pudo montarse la particion"<<endl;
        return;
    }
    //VERIFICANDO SI EL DISCO EXISTE
    char charPath[this->path.size() + 1];
    strcpy(charPath, this->path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    if(file == NULL){
        cout<<"\nNo existe el disco"<<endl;
        return;//error
    }
    int diskPos = 0;
    //VERIFICANDO SI EXISTE UN DISCO MONTADO O HAY ESPACIO PARA MONTAR OTRO
    for(int i = 0; i < 99; i++){
        if(discos[i].status == 'i' || discos[i].path == this->path){
            diskPos = i;
            break; //si hay un espacio libre, o si se encontro que ya esta montado
        }
    }
    if(diskPos == 99){
        cout<<"\nNo hay espacio para montar otro disco"<<endl;
        return;
    }
    //VALIDANDO SI LA PARTICION YA ESTA MONTADA
    for (int i = 0; i < 26; i++){
        for (int j = 0; j < 99; j++){
            if(discos[i].particiones[j].name == this->name && discos[i].path == this->path){
                cout<<"\nLa particion ya esta montada"<<endl;
                return;
            }
        }
    }
    //VERIFICANDO QUE LA PARTICION EXISTE, ES DECIR, QUE SU NOMBRE ESTE ENTRE LAS PRIMARIAS, EXSTENDIDAS O LOGICAS
    fseek(file, 0, SEEK_SET);
    Structs::MBR mbr;
    fread(&mbr, sizeof(Structs::MBR), 1, file);
    fclose(file);
    Structs::EBR previous_ebr;
    for(int i = 0; i < 4; i++){
        if(this->name == mbr.particiones[i].name){
            isNormal = true;
            break;
        }
        if(mbr.particiones[i].type == 'e'){
            //previous_ebr = obfdisk::getEBR(this->path, mbr.particiones[i].start);
            FILE * file = NULL;
            file = fopen(this->path.c_str(), "rb+");
            fseek(file, mbr.particiones[i].start, SEEK_SET);
            fread(&previous_ebr, sizeof(Structs::EBR), 1, file);
            fclose(file);
        }
    }
    if(isNormal){
        //MONTANDO PARTICIONES PRIMARIA Y EXTENDIDAS
        mount(diskPos);
        return;
    }
    bool seguimos = true;
    while(seguimos){
        if(previous_ebr.name == this->name){
            isLogic = true;
            break;
        }
        if(previous_ebr.next == -1){
            seguimos = false;
        }else{
            //previous_ebr = getEBR(this->path, previous_ebr.next);
            FILE * file = NULL;
            file = fopen(this->path.c_str(), "rb+");
            fseek(file, previous_ebr.next, SEEK_SET);
            fread(&previous_ebr, sizeof(Structs::EBR), 1, file);
            fclose(file);
        }
    }
    if(isLogic){
        //MONTANDO PARTICIONES LOGICAS
        mount(diskPos);
        return;
    }
    cout<<"\nNo existe la particion "<<this->name<<" en el disco "<<this->path<<endl;
    return;
}

void obmount::mount(int diskPos){
    discos[diskPos].status = 'h';
    discos[diskPos].path = this->path;
    discos[diskPos].number = diskPos + 1;
    string id1 = "34";
    string id2;
    for(int i = 0; i < 27; i++){
        Structs::particionMontada particion = discos[diskPos].particiones[i];
        if(particion.status == 'i'){
            discos[diskPos].particiones[i].status = 'h';
            discos[diskPos].particiones[i].name = this->name;
            discos[diskPos].particiones[i].letter = 'A' + i;
            id2 = std::to_string(discos[diskPos].number);
            id1 += id2;
            id2 = discos[diskPos].particiones[i].letter;
            id1 += id2;
            discos[diskPos].particiones[i].id = id1;
            break;
        }
    }
    mostrarDatos();
    return;
}


