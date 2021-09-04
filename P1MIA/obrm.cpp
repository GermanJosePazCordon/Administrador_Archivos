#include "obrm.h"
#include "iostream"
#include "structs.h"
#include "list"

using namespace std;

obrm::obrm()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obrm::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

Structs::SB obrm::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obrm::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obrm::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obrm::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

void obrm::saveBC(Structs::BC bc, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
}

Structs::Journaling obrm::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

void obrm::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obrm::addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start){
    bool seguimos = true;
    int next = start + sizeof(Structs::SB);
    Structs::Journaling jng_tmp;
    while(seguimos){
        jng_tmp = getJournaling(path_paticion, next);
        if(jng_tmp.next == -1){
            seguimos = false;
        }else{
            next = jng_tmp.next;
        }
    }
    jng_tmp.next = jng_tmp.start + sizeof(Structs::Journaling);
    Structs::SB sb = this->getSB(path_paticion, start);
    if(jng_tmp.next > (sb.bm_inode_start - sizeof(Structs::Journaling))){
        cout<<"\nEspacio insuficiente para el journaling"<<endl;
        return;
    }
    this->saveJournaling(jng_tmp, path_paticion, jng_tmp.start);
    Structs::Journaling jng;
    jng.date = time(0);
    strcpy(jng.path, path.c_str());
    strcpy(jng.operacion, operacion.c_str());
    jng.tipo = tipo;
    jng.next = -1;
    jng.start = jng_tmp.next;
    strcpy(jng.contenido, content.c_str());
    this->saveJournaling(jng, path_paticion, jng.start);
}

list<string> obrm::separar_carpetas(string path) {
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

void obrm::exec(){
    if(this->path == ""){
        cout<<"\Ruta invalida"<<endl;
        return;
    }
    //OBTENEMOS LA PARTICION A UTILIZAR
    if(log.status == 'i'){
        cout<<"\nNo existe usuario logueado"<<endl;
        return;
    }
    string id_particion = log.id;
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
    sb = this->getSB(path_particion, start_particion);
    inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    if(inodo_actual.type == '1'){
        //INODO TIPO ARCHIVO
        for(int i = 0; i < 15; i++){
            if(inodo_actual.block[i] != -1 && i < 12){
                FILE * file = NULL;
                file = fopen(path_particion.c_str(), "rb+");
                fseek(file, (sb.bm_block_start + inodo_actual.block[i]), SEEK_SET);
                fwrite("0", 1, 1, file);
                fclose(file);
            }
        }
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoAbuelo * sizeof(Structs::TI)));
        for(int i = 0; i < 15; i++){
            if(inodo_actual.block[i] != -1 && i < 12){
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    if(strcmp(bc_actual.content[j].name, file_name.c_str()) == 0){
                        string tmp = "";
                        strcpy(bc_actual.content[j].name, tmp.c_str());
                        bc_actual.content[j].inodo = -1;
                        cout<<"\nSea ha elimnado el archivo : "<<file_name<<endl;
                        FILE * file = NULL;
                        file = fopen(path_particion.c_str(), "rb+");
                        fseek(file, (sb.bm_inode_start + inodoPadre), SEEK_SET);
                        fwrite("0", 1, 1, file);
                        fclose(file);
                        this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                        if(sb.filesystem_type == 3){
                            this->addJournaling("--", this->path, path_particion, "rm", '1', start_particion);
                        }
                        return;
                    }
                }
            }else{
                //INDIRECTOS
            }
        }
    }else{
        //INODO TIPO CARPETA
        this->delInodo(inodoPadre, path_particion, start_particion);
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoAbuelo * sizeof(Structs::TI)));
        for(int i = 0; i < 15; i++){
            if(inodo_actual.block[i] != -1 && i < 12){
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    if(strcmp(bc_actual.content[j].name, file_name.c_str()) == 0){
                        string tmp = "";
                        strcpy(bc_actual.content[j].name, tmp.c_str());
                        bc_actual.content[j].inodo = -1;
                        cout<<"\nSea ha eliminado la carpeta : "<<file_name<<endl;
                        this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                        if(sb.filesystem_type == 3){
                            this->addJournaling("--", this->path, path_particion, "rm", '0', start_particion);
                        }
                        return;
                    }
                }
            }else{
                //INDIRECTOS
            }
        }
    }
}

void obrm::delInodo(int root, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + root * sizeof(Structs::TI)));
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1 && i < 12){
            if(inodo.type == '0'){
               this->delBC(inodo.block[i], path, start);
            }else{
                this->delBAR(inodo.block[i], path, start);
            }
        }
    }
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_inode_start + root), SEEK_SET);
    fwrite("0", 1, 1, file);
    fclose(file);
}

void obrm::delBC(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BC bc = this->getBC(path, (sb.block_start + bloque * sizeof(Structs::BC)));
    string tmp;
    for(int i = 0; i < 4; i++){
        tmp = bc.content[i].name;
        if(bc.content[i].inodo != -1 && tmp != "." && tmp != ".."){
            this->delInodo(bc.content[i].inodo, path, start);
        }
    }
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_block_start + bloque), SEEK_SET);
    fwrite("0", 1, 1, file);
    fclose(file);
}

void obrm::delBAR(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_block_start + bloque), SEEK_SET);
    fwrite("0", 1, 1, file);
    fclose(file);
}

