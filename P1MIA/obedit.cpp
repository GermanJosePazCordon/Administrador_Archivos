#include "obedit.h"
#include "iostream"
#include "structs.h"
#include "list"
#include "fstream"

using namespace std;

obedit::obedit()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obedit::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obedit::setCont(string cont){
    if(cont[0] == '"'){
        this->cont = path.substr(1, path.size()-1);
        this->cont = this->cont.substr(0, this->cont.size()-1);
    }else{
        this->cont = cont;
    }
}

void obedit::setStdin(){
    this->stdi = true;
}

Structs::SB obedit::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obedit::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obedit::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obedit::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

void obedit::saveSB(Structs::SB sb, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}

void obedit::saveInodo(Structs::TI inodo, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
}

void obedit::saveBAR(Structs::BAR bar, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
}

Structs::Journaling obedit::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

void obedit::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obedit::addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start){
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

list<string> obedit::separar_carpetas(string path) {
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

void obedit::exec(){
    if(this->path == ""){
        cout<<"\nRuta invalida"<<endl;
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
    if(inodo_actual.type == '0'){
        cout<<"\nLa ruta ingresada es de la carpeta : "<<file_name<<endl;
        return;
    }
    if(cont != ""){
        //RECUPERAMOS DE LA RUTA
        ifstream in(this->cont);
        string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        this->content = contents;
    }else if(this->stdi){
        //RECUPERAMOS LA ENTRADA
        cout<<"\nIngrese el texto a guardar en el archivo : \n"<<endl;
        cin>>this->content;
    }
    if(this->content == ""){
        cout<<"\nNo se ingresó ningun contenido para editar."<<endl;
        return;
    }
    int limite = this->content.length();
    int numeroBloques = limite / 64;
    if (numeroBloques * 64 < limite) ++numeroBloques;
    string contenido[numeroBloques];
    int cont = 0;
    for(int i = 0; i < numeroBloques; i++){
        for(int j = 0; j < 64; j++){
            if(cont == limite){
                break;
            }
            contenido[i] += this->content[cont];
            cont +=1;
        }
    }
    cont = 0;
    sb = this->getSB(path_particion, start_particion);
    inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    for(int i = 0; i < 15; i++){
        if(inodo_actual.block[i] != -1 && i < 12){
            cont += 1;
        }else{/*INDIRECTOS*/}
    }
    if(cont == numeroBloques){
        //CASO DONDE EL NUEVO CONTEIDO OCUPA LA MISMA CANTIDAD DE BLOQUES QUE EL ANTERIOR
        for(int i = 0; i < 15; i++){
            if(inodo_actual.block[i] != -1 && i < 12){
                inodo_actual.size = this->content.length();
                this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
                Structs::BAR archivo;
                strcpy(archivo.content, contenido[i].c_str());
                this->saveBAR(archivo, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BAR)));
            }else{/*INDIRECTOS*/}
        }
    }else if(cont > numeroBloques){
        //CASO DONDE EL NUEVO CONTEIDO OCUPA MENOS BLOQUES QUE EL ANTERIOR
        for(int i = 0; i < numeroBloques; i++){
            if(inodo_actual.block[i] != -1 && i < 12){
                Structs::BAR archivo;
                strcpy(archivo.content, contenido[i].c_str());
                this->saveBAR(archivo, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BAR)));
            }else{/*INDIRECTOS*/}
        }
        for(int i = numeroBloques; i < cont; i++){
            FILE * file = NULL;
            file = fopen(path_particion.c_str(), "rb+");
            fseek(file, (sb.bm_block_start + inodo_actual.block[i]), SEEK_SET);
            fwrite("0", 1, 1, file);
            fclose(file);
            inodo_actual.block[i] = -1;
            inodo_actual.size = this->content.length();
            this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        }
    }else{
        //CASO DONDE EL NUEVO CONTEIDO OCUPA MAS BLOQUES QUE EL ANTERIOR
        for(int i = 0; i < numeroBloques; i++){
            if(inodo_actual.block[i] != -1 && i < 12){
                Structs::BAR archivo;
                strcpy(archivo.content, contenido[i].c_str());
                this->saveBAR(archivo, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BAR)));
            }else{/*INDIRECTOS*/}
        }
        for(int i = (cont); i < numeroBloques; i++){
            if(i < 12){
                sb = this->getSB(path_particion, start_particion);
                inodo_actual.block[i] = sb.first_blo;
                inodo_actual.size = this->content.length();
                this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
                Structs::BAR archivo;
                strcpy(archivo.content, contenido[i].c_str());
                this->saveBAR(archivo, path_particion, (sb.block_start + sb.first_blo * sizeof(Structs::BAR)));
                FILE * file = NULL;
                file = fopen(path_particion.c_str(), "rb+");
                fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
                fwrite("1", 1, 1, file);
                fclose(file);
                sb.first_blo = sb.first_blo + 1;
                this->saveSB(sb, path_particion, start_particion);
            }else{/*INDIRECTOS*/}
        }
    }
    if(sb.filesystem_type == 3){
        string tmp;
        for(int i = 0; i < 100; i++){
            tmp += content[i];
        }
        this->addJournaling(tmp, this->path, path_particion, "edit", '1', start_particion);
    }
    cout<<"\Archivo modificado correctamente"<<endl;
}
