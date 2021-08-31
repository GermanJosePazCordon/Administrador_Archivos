#include "obcat.h"
#include "iostream"
#include "structs.h"
#include "list"

using namespace std;

obcat::obcat()
{

}

extern Structs::Discos discos[99];

//--------------------------SETERS-----------------------------------

void obcat::addFile(string filen, string path){
    string data = filen;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    string file = data.substr(0, data.length() - 1);
    if(file != "file"){
        cout<<"\nParametro filen mal escrito"<<endl;
        return;
    }
    if(path[0] == '"'){
        path = path.substr(1, path.size()-1);
        path = path.substr(0, path.size()-1);
    }else{
        path = path;
    }
    this->lista_file.push_back(path);
}

Structs::SB obcat::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obcat::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obcat::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obcat::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

list<string> obcat::separar_carpetas(string path) {
    if (path[0] == '/') {
        path = path.substr(1, path.length());
    }
    list<string> lista_carpetas;
    char ruta[path.length() + 1];
    strcpy(ruta, path.c_str());
    string nombre_carpeta;
    for (int i = 0; i < path.length() + 1; i++) {
        if (ruta[i] == '/' || i == path.length()) {
            lista_carpetas.push_back(nombre_carpeta);
            nombre_carpeta.clear();
            continue;
        }
        nombre_carpeta += ruta[i];
    }
    return lista_carpetas;
}

void obcat::exec(){
    //OBTENEMOS LA PARTICION A UTILIZAR
    string id_particion = "341A";
    string path_particion = "";
    char type_particion = 'x';
    int start_particion;
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == id_particion){
                path_particion = discos[i].path;
                start_particion = discos[i].particiones[j].start;
                type_particion = discos[i].particiones[j].type;
                break;
            }
        }
    }
    list<string>::iterator it;
    for(it = this->lista_file.begin(); it != this->lista_file.end(); it++){
        string tmp = *it;
        this->getInodoArchivo(tmp, path_particion, start_particion);
    }
}

void obcat::getInodoArchivo(string path, string path_particion, int start_particion){
    list<string> lista_carpetas;
    list<string>::iterator it;
    lista_carpetas = separar_carpetas(path);
    Structs::SB sb;
    Structs::TI inodo_actual;
    Structs::BC bc_actual;
    int inodoPadre = 0;
    int inodoAbuelo = 0;
    string file_name;
    for(it = lista_carpetas.begin(); it != lista_carpetas.end(); it++){
        file_name = *it;
        bool carpeta_existente = false;
        sb = this->getSB(path_particion, start_particion);
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        for(int i = 0; i < 15; i++){
            if(inodo_actual.block[i] != -1){
                //POSICIONAMOS EL BLOQUE ACTUAL PARA PODER ACCEDER A SU CONTENIDO
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    string name = *it;
                    if(strcmp(bc_actual.content[j].name, name.c_str()) == 0){
                        //CARPETA ENCONTRADA EN LA POSICION i DEL PRIMER BLOQUE DEL NODOD
                        carpeta_existente = true;
                        inodoAbuelo = inodoPadre;
                        inodoPadre = bc_actual.content[j].inodo;
                    }
                }
            }
        }
        if(!carpeta_existente){
            cout<<"\nNo existe la carpeta : "<<*it<<endl;
            return;
        }else{
            continue;
        }
    }
    string content;
    inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    if(inodo_actual.type == '0'){
        cout<<"\nLa ruta ingresada es de la carpeta : "<<file_name<<endl;
        return;
    }
    for(int i = 0; i < 15; i++){
        if(inodo_actual.block[i] != -1 && i < 12){
            Structs::BAR archivo = this->getBAR(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BAR)));
            string tmp = archivo.content;
            content += tmp;
        }else{
            //VAILDAR PA INDIRECTOS
        }
    }
    cout<<content<<endl;
}
