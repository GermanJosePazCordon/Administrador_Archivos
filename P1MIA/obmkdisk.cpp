#include "obmkdisk.h"
#include "iostream"
#include "structs.h"
#include "time.h"

#include <algorithm>
#include <cctype>
#include <string>

using namespace std;

obmkdisk::obmkdisk()
{

}

//--------------------------SETERS-----------------------------------

void obmkdisk::setSize(int size){
    this->size = size;
}

void obmkdisk::setFit(string fit){
    string data = fit;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    fit = data;
    this->fit = fit;
}

void obmkdisk::setUnit(string unit){
    string data = unit;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    unit = data;
    this->unit = unit;
}

void obmkdisk::setPath(string path){
    this->path = path;
}

void obmkdisk::mostrardatos(Structs::MBR mbr){
    cout<<"\n-------------DISCO CREADO--------------------"<<endl;
    cout<<"Signature: "<<mbr.signature <<endl;
    cout<<"Tamaño: "<<mbr.size <<endl;
    cout<<"Fit: " <<mbr.fit <<endl;

}

bool obmkdisk::validarParametros(){
    if(this->size == 0){
        cout<<"\nTamaño incorrecto de disco."<<endl;
        return true;
    }
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return true;
    }
    if(this->unit != ""){
        if(this->unit != "k" && this->unit != "m"){
            cout<<"\nUnidad invalidad."<<endl;
            return true;
        }
    }
    if(this->fit != ""){
        if(this->fit != "b" && this->fit != "f" && this->fit != "w"){
            cout<<"\nFit invalido."<<endl;
            return true;
        }
    }
    return false;
}

void obmkdisk::exec(){
    if(validarParametros()){
        cout<<"\nNo se pudo crear el disco."<<endl;
    }else{
        //cout<<this->path<<endl;
        init();
        //mostrardatos();
    }
}

void obmkdisk::init(){
    char charPath[this->path.size() + 1];
    strcpy(charPath, this->path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "r");
    if(file != NULL){
        cout<<"Ya existe el disco"<<endl;
        return;//error
    }else{
        string create = "mkdir -p \"" + this->path + "\"";
        string del = "rmdir \"" + this->path + "\"";
        system(create.c_str());
        system(del.c_str());
    }
    int size;
    if(this->unit == "k"){ //kb
        size =  this->size * 1024;
    }
    else{ //mb
        size =  this->size * 1024 * 1024;
    }
    file = fopen(charPath, "wb");
    fwrite("\0", 1, 1, file);
    fseek(file, size, SEEK_SET);
    fwrite("\0", 1, 1, file);
    fclose(file);
    Structs::MBR mbr;
    mbr.size = size;
    mbr.signature = rand()%1000;
    strcpy(mbr.fit,this->fit.c_str());
    mostrardatos(mbr);
}


