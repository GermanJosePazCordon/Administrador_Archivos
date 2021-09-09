#include "obloss.h"
#include "iostream"
#include "structs.h"
#include "fstream"

using namespace std;

obloss::obloss()
{

}

extern Structs::Discos discos[99];

//--------------------------SETERS-----------------------------------

void obloss::setID(string id){
    if(id[0] == '"'){
        this->id = id.substr(1, id.size()-1);
        this->id = this->id.substr(0, this->id.size()-1);
    }else{
        this->id = id;
    }
}

void obloss::exec(){
    if(this->id == ""){
        cout<<"\nid invalido"<<endl;
        return;
    }
    string id_particion = this->id;
    string path_particion = "";
    string name_particion = "";
    char type_particion = 'x';
    int start_particion;
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == id_particion){
                path_particion = discos[i].path;
                start_particion = discos[i].particiones[j].start;
                type_particion = discos[i].particiones[j].type;
                name_particion = discos[i].particiones[j].name;
                break;
            }
        }
    }
    if(path_particion == ""){
        cout<<"\nNo existe una particion con el id : "<<this->id<<endl;
        return;
    }
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path_particion.c_str(), "rb+");
    fseek(file, start_particion, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);

    file = fopen(path_particion.c_str(), "rb+");
    fseek(file, sb.bm_inode_start, SEEK_SET);
    fwrite("\0", 1, 1, file);
    fclose(file);

    for(int i = sb.inode_start; i < (sb.block_start + sb.blocks_count); i++){

    }
}
