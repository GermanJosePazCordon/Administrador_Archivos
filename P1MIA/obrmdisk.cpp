#include "obrmdisk.h"
#include "iostream"
#include "structs.h"

using namespace std;

obrmdisk::obrmdisk()
{

}

//--------------------------SETERS-----------------------------------

void obrmdisk::setPath(string path){
    this->path = path;
}

void obrmdisk::exec(){
    if(this->path == ""){
        cout<<"\nRuta invalida"<<endl;
        cout<<"\nNo se pudo eliminar el disco"<<endl;
    }else{
        char charPath[this->path.size() + 1];
        strcpy(charPath, this->path.c_str());
        FILE *file = NULL;
        file = fopen(charPath, "r");
        if(file != NULL){
            string path = "rm \"" + this->path + "\"";
            system(path.c_str());
            cout << "\nSe elimino el disco : " << this->path << endl;
            fclose(file);
            return;
        }else{
            cout << "\nEl disco no existe." << endl;
            return;
        }
    }
}



