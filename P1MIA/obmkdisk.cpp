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
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obmkdisk::mostrardatos(Structs::MBR mbr){
    char date[16];
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&mbr.date));

    cout<<"\n-------------DISCO CREADO--------------------"<<endl;
    cout<<"Date: " <<date<<endl;
    cout<<"Signature: "<<mbr.signature <<endl;
    cout<<"Tamaño: "<<mbr.size <<endl;
    cout<<"Fit: " <<mbr.fit <<endl;
    cout << "Size of mbr :" << sizeof(mbr) << endl;
}

bool obmkdisk::validarParametros(){
    if(this->size <= 0){
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
        if(this->fit != "bf" && this->fit != "ff" && this->fit != "wf"){
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
        init();
    }
}

void obmkdisk::init(){
    char charPath[this->path.size() + 1];
    strcpy(charPath, this->path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "r");
    if(file != NULL){
        cout<<"\nYa existe el disco"<<endl;
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


    Structs::MBR mbr;
    mbr.size = size;
    mbr.signature = rand()%1000;
    if (this->fit == "wf") {
      mbr.fit = 'w';
    } else if (this->fit == "ff") {
      mbr.fit = 'f';
    } else {
      mbr.fit = 'b';
    }
    mbr.date = time(0);
    for(int i = 0; i < 4; i++){
        mbr.particiones[i].status = 'i';
        mbr.particiones[i].size = 0;
        mbr.particiones[i].fit = mbr.fit;
        mbr.particiones[i].start = size;
        mbr.particiones[i].type = 'x';
        strcpy(mbr.particiones[i].name,"");
    }

    mostrardatos(mbr);

    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(Structs::MBR), 1, file);
    fclose(file);
}


