#include "obfind.h"
#include "iostream"
#include "structs.h"
#include "regex"
#include "list"

using namespace std;

obfind::obfind()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obfind::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obfind::setName(string name){
    if(name[0] == '"'){
        this->name = name.substr(1, name.size()-1);
        this->name = this->name.substr(0, this->name.size()-1);
    }else{
        this->name = name;
    }
}

Structs::SB obfind::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obfind::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obfind::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obfind::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
    return bar;
}

void obfind::saveSB(Structs::SB sb, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}

void obfind::saveInodo(Structs::TI inodo, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
}

void obfind::saveBC(Structs::BC bc, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
}

void obfind::saveBAR(Structs::BAR bar, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
}

Structs::Journaling obfind::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

void obfind::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obfind::addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start){
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

list<string> obfind::separar_carpetas(string path) {
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

void obfind::exec(){
    if(this->path == ""){
        cout<<"\nRuta invalida"<<endl;
        return;
    }
    if(this->path == ""){
        cout<<"\nNombre invalido"<<endl;
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
    lista_carpetas = separar_carpetas(this->path);
    Structs::SB sb;
    Structs::TI inodo_actual;
    Structs::BC bc_actual;
    int inodoPadre = 0;
    int inodoAbuelo = 0;
    string file_name;
    for(it = lista_carpetas.begin(); it != lista_carpetas.end(); it++){
        if(this->path == "/"){
            break;
        }
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
        cout<<"\nNo pudo realizarse la busqueda"<<endl;
        return;
    }
    string rx = this->formarRegex(this->name);
    this->searchInodo(this->path, rx, inodoPadre, path_particion, start_particion);
}

void obfind::searchInodo(string name, string regex, int root, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + root * sizeof(Structs::TI)));
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1 && i < 12){
            if(inodo.type == '0'){
                this->searchBC(name, regex, inodo.block[i], path, start);
            }
        }
    }
}

void obfind::searchBC(string name, string regex, int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BC bc = this->getBC(path, (sb.block_start + bloque * sizeof(Structs::BC)));
    for(int i = 0; i < 4; i++){
        if(bc.content[i].inodo != -1){
            string tmp = bc.content[i].name;
            string tmp2 = bc.content[i].name;
            if(this->verificarMatch(tmp, regex)){
                Structs::TI inodo_tmp = this->getInodo(path, (sb.inode_start + bc.content[i].inodo * sizeof(Structs::TI)));
                if(name == "/"){
                    tmp = name + tmp;
                }else{
                   tmp = name + "/" + tmp;
                }
                if(inodo_tmp.type == '0'){
                   cout<<"\n"<<tmp<<"|"<<to_string(bc.content[i].inodo)<<"|"<<"0"<<endl;
                }else{
                   cout<<"\n"<<tmp<<"|"<<to_string(bc.content[i].inodo)<<"|"<<"1"<<endl;
                }
            }
            if(tmp2 != "." && tmp2 != ".."){
                this->searchInodo(tmp, regex, bc.content[i].inodo, path, start);
            }
        }
    }
}

string obfind::formarRegex(string name){
    string regex = "^(";
    for (char i : name) {
        if(i == '*'){
            regex += "([a-zA-Z0-9]+)";
        } else if (i == '?'){
            regex += "([a-zA-Z0-9]{1})";
        } else {
            regex += i;
        }
    }
    regex += ")$";

    return regex;
}

bool obfind::verificarMatch(string nombre, string regex){

    std::regex word_regex(regex);
    auto words_begin = std::sregex_iterator(nombre.begin(), nombre.end(), word_regex);
    auto words_end = std::sregex_iterator();

    if(distance(words_begin, words_end) == 1){
        return true;
    }
    return false;
}
