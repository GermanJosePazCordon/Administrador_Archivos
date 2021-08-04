#include "obfdisk.h"
#include "iostream"
#include "structs.h"

using namespace std;

obfdisk::obfdisk()
{

}

//--------------------------SETERS-----------------------------------

void obfdisk::setSize(int size){
    this->size = size;
}

void obfdisk::setAdd(int add){
    this->add = add;
}

void obfdisk::setFit(string fit){
    string data = fit;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    fit = data;
    this->fit = fit;
}

void obfdisk::setUnit(string unit){
    string data = unit;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    unit = data;
    this->unit = unit;
}

void obfdisk::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obfdisk::setType(string type){
    string data = type;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    type = data;
    this->type = type;
}

void obfdisk::setDelet(string delet){
    string data = delet;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    delet = data;
    this->delet = delet;
}

void obfdisk::setName(string name){
    if(name[0] == '"'){
        this->name = name.substr(1, path.size()-1);
        this->name = this->name.substr(0, this->name.size()-1);
    }else{
        string data = name;
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });
        name = data;
        //this->delet = delet;
        this->name = name;
    }
}

bool obfdisk::validarParametros(){
    if(this->size <= 0){
        cout<<"\nTamaño incorrecto de disco."<<endl;
        return true;
    }
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return true;
    }
    if(this->name == ""){
        cout<<"\nNombre vacio."<<endl;
        return true;
    }
    if(this->fit != ""){
        if(this->fit != "bf" && this->fit != "ff" && this->fit != "wf"){
            cout<<"\nFit invalido."<<endl;
            return true;
        }
    }
    if(this->unit != ""){
        if(this->unit != "k" && this->unit != "m" && this->unit != "b"){
            cout<<"\nUnidad invalida."<<endl;
            return true;
        }
    }
    if(this->type != ""){
        if(this->type != "p" && this->type != "e" && this->type != "l"){
            cout<<"\nTipo invalido."<<endl;
            return true;
        }
    }
    if(this->delet != ""){
        if(this->delet != "full" && this->delet != "fast"){
            cout<<"\nTipo invalido."<<endl;
            return true;
        }
    }
    return false;
}

void obfdisk::getMBR(string path){
    Structs::MBR tmp_mbr;
    FILE * file = NULL;
    file = fopen(path.c_str(), "r");
    if (file != NULL){
        fread(&tmp_mbr, sizeof(Structs::MBR), 1, file);
        this->mbr = tmp_mbr;
        fclose(file);
        init();
    }else{
        cout<<"\nEl disco no existe."<<endl;
        return;
    }
}

void obfdisk::exec(){
    if(validarParametros()){
        cout<<"\nNo se pudo crear la particion"<<endl;
    }else{
        getMBR(this->path);
    }
}

void obfdisk::init(){
    createPartition();
}

void obfdisk::createPartition(){

}
