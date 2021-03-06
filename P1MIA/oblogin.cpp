#include "oblogin.h"
#include "iostream"
#include "structs.h"
#include "list"
#include "sstream"

using namespace std;

oblogin::oblogin()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void oblogin::setUser(string user){
    if(user[0] == '"'){
        this->user = user.substr(1, user.size()-1);
        this->user = this->user.substr(0, this->user.size()-1);
    }else{
        this->user = user;
    }
}

void oblogin::setPwd(string pwd){
    if(pwd[0] == '"'){
        this->pwd = pwd.substr(1, pwd.size()-1);
        this->pwd = this->pwd.substr(0, this->pwd.size()-1);
    }else{
        this->pwd = pwd;
    }
}

void oblogin::setID(string id){
    if(id[0] == '"'){
        this->id = id.substr(1, id.size()-1);
        this->id = this->id.substr(0, this->id.size()-1);
    }else{
        this->id = id;
    }
}

Structs::SB oblogin::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI oblogin::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC oblogin::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR oblogin::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

list<string> oblogin::separar_carpetas(string path) {
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

list<string> oblogin::separar_comas(string path) {
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

void oblogin::exec(){
    if(this->user == ""){
        cout<<"\nUser invalido"<<endl;
        return;
    }
    if(this->pwd == ""){
        cout<<"\nPassword invalido"<<endl;
        return;
    }
    if(this->id == ""){
        cout<<"\nID invalido"<<endl;
        return;
    }
    if(log.status == 'h'){
        cout<<"\nYa se encuentra logueado el usuario : "<<log.user<<endl;
        return;
    }
    bool existe_particion = false;
    string path_particion;
    int start_particion;
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == this->id){
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
    list<string> lista_usuarios;
    list<string> lista_tmp;
    list<string>::iterator it;
    list<string>::iterator it2;
    lista_usuarios = this->separar_carpetas(usuarios);
    string usuario[5];
    bool match = false;
    string grupo;
    for(it = lista_usuarios.begin(); it != lista_usuarios.end(); it++){
        string tmp = *it;
        string tmp2;
        tmp2 = tmp[2];
        if(tmp2 == "U"){
            lista_tmp = this->separar_comas(tmp);
            int cont = 0;
            for(it2 = lista_tmp.begin(); it2 != lista_tmp.end(); it2++){
                string tmp3 = *it2;
                usuario[cont] = tmp3;
                cont++;
            }
            if(usuario[0] != "0" && this->user == usuario[3] && this->pwd == usuario[4]){
                 stringstream convert(usuario[0]);
                 int x = 0;
                 convert >> x;
                 log.uid = x;
                 grupo = usuario[2];
                 match = true;
                 break;
            }
        }
    }
    if(match){
        log.id = this->id;
        log.pwd = this->pwd;
        log.user = this->user;
        log.status = 'h';
        cout<<"\nUsuario logueado correctamente"<<endl;
        for(it = lista_usuarios.begin(); it != lista_usuarios.end(); it++){
            string tmp = *it;
            string tmp2;
            tmp2 = tmp[2];
            if(tmp2 == "G"){
                lista_tmp = this->separar_comas(tmp);
                int cont = 0;
                for(it2 = lista_tmp.begin(); it2 != lista_tmp.end(); it2++){
                    string tmp3 = *it2;
                    usuario[cont] = tmp3;
                    cont++;
                }
                if(usuario[2] == grupo && usuario[0] != "0"){
                    stringstream convert(usuario[0]);
                    int x = 0;
                    convert >> x;
                    log.guid = x;
                    cout<<x<<endl;
                    match = true;
                    break;
                }
            }
        }
    }else{
        cout<<"\nUsuario y/o contrase??a incorrectos"<<endl;
        cout<<"\nNo pudo iniciarse sesion"<<endl;
    }
}
