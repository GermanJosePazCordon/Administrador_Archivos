#include "obumount.h"
#include "iostream"
#include "structs.h"

using namespace std;

obumount::obumount()
{

}

extern Structs::Discos discos[99];

//--------------------------SETERS-----------------------------------

void obumount::setID(string id){
    if(id[0] == '"'){
        this->id = id.substr(1, id.size()-1);
        this->id = this->id.substr(0, this->id.size()-1);
    }else{
        this->id = id;
    }
}

void obumount::exec(){
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == this->id){
                cout<<"\nSe ha encontrado la particion montada"<<endl;
                cout<<"\nDesea eliminarlo? [s/n]"<<endl;
                char op;
                cin >> op;
                if(op == 's'){
                    cout<<"\nSe ha desmontado la particion : "<<discos[i].particiones[j].name<<endl;
                    Structs::particionMontada tmp_montada;
                    discos[i].particiones[j] = tmp_montada;
                    discos[i].particiones[j].umtime = time(0);
                }
                return;
            }
        }
    }
    cout<<"\nNo se ha encontrado la particion montada"<<endl;
    return;
}
