#include "obrmusr.h"
#include "obedit.h"
#include "iostream"
#include "structs.h"
#include "list"
#include "sstream"

using namespace std;

obrmusr::obrmusr()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obrmusr::setUsr(string usr){
    if(usr[0] == '"'){
        this->usr = usr.substr(1, usr.size()-1);
        this->usr = this->usr.substr(0, this->usr.size()-1);
    }else{
        this->usr = usr;
    }
}

Structs::SB obrmusr::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obrmusr::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obrmusr::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obrmusr::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

list<string> obrmusr::separar_carpetas(string path) {
    list<string> lista_carpetas;
    char ruta[path.length() + 1];
    strcpy(ruta, path.c_str());
    string nombre_carpeta;
    for (int i = 0; i < path.length() + 1; i++) {
        if (ruta[i] == '\n') {
            lista_carpetas.push_back(nombre_carpeta);

            nombre_carpeta.clear();
            continue;
        }
        //cout<<nombre_carpeta<<endl;
        nombre_carpeta += ruta[i];
    }
    return lista_carpetas;
}

list<string> obrmusr::separar_comas(string path) {
    list<string> lista_carpetas;
    char ruta[path.length() + 1];
    strcpy(ruta, path.c_str());
    string nombre_carpeta;
    for (int i = 0; i < path.length() + 1; i++) {
        if (ruta[i] == ',' || i == path.length()) {
            lista_carpetas.push_back(nombre_carpeta);
            nombre_carpeta.clear();
            continue;
        }
        //cout<<nombre_carpeta<<endl;
        nombre_carpeta += ruta[i];
    }
    return lista_carpetas;
}

void obrmusr::exec(){
    if(this->usr == ""){
        cout<<"\nNombre invalido"<<endl;
        return;
    }
    if(log.status == 'i'){
        cout<<"\nNo existe usuario logueado"<<endl;
        return;
    }
    if(log.user != "root"){
        cout<<"\nSolo el usuario root puede ejecutar este comando"<<endl;
        return;
    }
    bool existe_particion = false;
    string path_particion;
    int start_particion;
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == log.id){
                path_particion = discos[i].path;
                start_particion = discos[i].particiones[j].start;
                existe_particion = true;
                break;
            }
        }
    }
    if(!existe_particion){
        cout<<"\nLa particion no se encuentra entre las particiones montadas"<<endl;
        return;
    }
    Structs::SB sb = this->getSB(path_particion, start_particion);
    Structs::TI inodo = this->getInodo(path_particion, (sb.inode_start + sizeof(Structs::TI)));
    Structs::BAR archivo;
    string usuarios;
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1 && i < 12){
            archivo = this->getBAR(path_particion, (sb.block_start + inodo.block[i] * sizeof(Structs::BAR)));
            string tmp = archivo.content;
            if(tmp.length() > 64){
                tmp = tmp.substr(0, 64);
            }
            usuarios += tmp;
        }
    }
    list<string> lista_archivo;
    list<string> lista_grupos;
    list<string>::iterator it;
    list<string>::iterator it2;
    lista_archivo = this->separar_carpetas(usuarios);
    string grupo[5];
    string grupos[lista_archivo.size()];
    bool match = false;
    int c = 0;
    int pos;
    for(it = lista_archivo.begin(); it != lista_archivo.end(); it++){
        string tmp = *it;
        grupos[c] = tmp;

        string tmp2;
        tmp2 = tmp[2];
        if(tmp2 == "U"){
            lista_grupos = this->separar_comas(tmp);
            int cont = 0;
            for(it2 = lista_grupos.begin(); it2 != lista_grupos.end(); it2++){
                string tmp3 = *it2;
                grupo[cont] = tmp3;
                cont++;
            }
            if(this->usr == grupo[3] && grupo[0] != "0"){
                match = true;
                pos = c;
            }
        }
        c++;
    }
    if(!match){
        cout<<"\nNo existe el usuario o ya esta eliminado"<<endl;
        return;
    }
    string content;
    for(int i = 0; i < lista_archivo.size(); i++){
        if(i == pos){
            string tmp = grupos[i];
            string tmp2 = tmp.substr(1, tmp.size()-1);
            tmp2 = "0" + tmp2;
            content += tmp2 + "\n";
        }else{
          content += grupos[i] + "\n";
        }
    }
    obedit * edit = new obedit();
    edit->setPath("/user.txt");
    edit->content = content;
    edit->exec();
}
