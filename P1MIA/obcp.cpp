#include "obcp.h"
#include "iostream"
#include "structs.h"
#include "list"

using namespace std;

obcp::obcp()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obcp::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obcp::setDest(string dest){
    if(dest[0] == '"'){
        this->dest = dest.substr(1, dest.size()-1);
        this->dest = this->dest.substr(0, this->dest.size()-1);
    }else{
        this->dest = dest;
    }
}

Structs::SB obcp::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obcp::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obcp::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obcp::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
    return bar;
}

void obcp::saveSB(Structs::SB sb, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}

void obcp::saveInodo(Structs::TI inodo, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
}

void obcp::saveBC(Structs::BC bc, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
}

void obcp::saveBAR(Structs::BAR bar, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
}

Structs::Journaling obcp::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

void obcp::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obcp::addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start){
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

list<string> obcp::separar_carpetas(string path) {
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

void obcp::exec(){
    if(this->path == ""){
        cout<<"\Ruta invalida"<<endl;
        return;
    }
    if(this->dest == ""){
        cout<<"\nDestino invalido"<<endl;
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
    Structs::TI inodo_anterior;
    int padreAnterior = inodoPadre;
    string fileAnterior = file_name;
    //BUSCAMOS EL NUEVO INODO
    inodo_anterior = inodo_actual;
    lista_carpetas = separar_carpetas(this->dest);
    inodoPadre = 0;
    inodoAbuelo = 0;
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
    //PRIMERO VALIDAR SI EL INODO A MOVER YA EXISTE O NO
    for(int i = 0; i < 15; i++){
        if(inodo_actual.block[i] != -1 && i < 12){
            bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
            for(int j = 0; j < 4; j++){
                if(strcmp(bc_actual.content[j].name, fileAnterior.c_str()) == 0){
                    cout<<"\nYa existe : "<<fileAnterior<<endl;
                    return;
                }
            }
        }
    }
    //MOVEMOS EL INODO, BUSCAMOS EN DONDE PONERLO
    for(int i = 0; i < 15; i++){
        if(inodo_actual.block[i] != -1 && i < 12){
            //CASO DONDE HAY ESPACIO EN EL BLOQUE CARPETA DESTINO
            bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
            for(int j = 0; j < 4; j++){
                if(bc_actual.content[j].inodo == -1){
                    //ACTIUALIZAMOS LA INFORMACION DEL BLOQUE CARPETA DESTINO
                    sb = this->getSB(path_particion, start_particion);
                    bc_actual.content[j].inodo = sb.firts_ino;
                    strcpy(bc_actual.content[j].name, fileAnterior.c_str());
                    this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                    this->changeInodo(padreAnterior, path_particion, start_particion, inodoPadre);
                    Structs::TI tmp = this->getInodo(path_particion, (sb.inode_start + padreAnterior * sizeof(Structs::TI)));
                    if(tmp.type == '0'){
                        //AGREGAMOS JOURNALING EN CASO DE TENER QUE HACERLO
                        if(sb.filesystem_type == 3){
                            this->addJournaling("--", this->path, path_particion, "cp", '0', start_particion);
                        }
                    }else{
                        if(sb.filesystem_type == 3){
                            this->addJournaling("--", this->path, path_particion, "cp", '1', start_particion);
                        }
                    }
                    return;
                }
            }
        }else if(inodo_actual.block[i] == -1 && i < 12){
            //CASO DONDE NO HAY ESPACIO EN EL BLOQUE CARPETA DESTINO, HAY QUE CREAR OTRO BLOQUE CARPETA EN UN BLOQUE LIBRE
            //ASIGNAMOS EL BLOQUE Y GUARDAMOS EL INODO
            inodo_actual.block[i] = sb.first_blo;
            this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
            //CREAMOS EL BLOQUE CARPETA Y ASIGNAMOS EL INODO QUE ESTAMOS MOVIENDO
            Structs::BC bc;
            bc.content[0].inodo = sb.firts_ino;
            strcpy(bc.content[0].name, fileAnterior.c_str());
            this->saveBC(bc, path_particion, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));

            FILE * file = NULL;
            file = fopen(path_particion.c_str(), "rb+");
            fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
            fwrite("1", 1, 1, file);
            fclose(file);

            sb.free_blocks_count--;
            sb.first_blo++;
            this->saveSB(sb, path_particion, start_particion);
            this->changeInodo(padreAnterior, path_particion, start_particion, inodoPadre);

            Structs::TI tmp = this->getInodo(path_particion, (sb.inode_start + padreAnterior * sizeof(Structs::TI)));
            if(tmp.type == '0'){
                //AGREGAMOS JOURNALING EN CASO DE TENER QUE HACERLO
                if(sb.filesystem_type == 3){
                    this->addJournaling("--", this->path, path_particion, "cp", '0', start_particion);
                }
            }else{
                if(sb.filesystem_type == 3){
                    this->addJournaling("--", this->path, path_particion, "cp", '1', start_particion);
                }
            }
            //ACTUALIZAMOS EL PADRE Y ABUELO DEL BLOQUE CARPETA DEL INODO MOVIDO
            return;
        }else{/*INDIRECTOS*/}
    }
}

void obcp::changeInodo(int root, string path, int start, int abuelo){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + root * sizeof(Structs::TI)));
    Structs::TI inodo_nuevo;
    inodo_nuevo.atime = time(0);
    inodo_nuevo.ctime = time(0);
    inodo_nuevo.mtime = time(0);
    inodo_nuevo.gid = inodo.gid;
    inodo_nuevo.size = inodo.size;
    inodo_nuevo.type = inodo.type;
    inodo_nuevo.uid = inodo.uid;
    for(int i = 0; i < 15; i++){
        inodo_nuevo.block[i] = -1;
    }
    int first = sb.firts_ino;

    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_inode_start + sb.firts_ino), SEEK_SET);
    fwrite("1", 1, 1, file);
    fclose(file);
    sb.free_inodes_count--;
    sb.firts_ino = sb.firts_ino + 1;
    this->saveSB(sb, path, start);
    this->saveInodo(inodo_nuevo, path, (sb.inode_start + first * sizeof(Structs::TI)));
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1 && i < 12){
            sb = this->getSB(path, start);
            if(inodo.type == '0'){
                inodo_nuevo.type = '0';
                inodo_nuevo.block[i] = sb.first_blo;
                this->saveInodo(inodo_nuevo, path, (sb.inode_start + first * sizeof(Structs::TI)));
                this->changeBC(inodo.block[i], path, start, first, abuelo);
                sb = this->getSB(path, start);
            }else{
                inodo_nuevo.type = '1';
                inodo_nuevo.block[i] = sb.first_blo;
                this->saveInodo(inodo_nuevo, path, (sb.inode_start + first * sizeof(Structs::TI)));
                this->changeBAR(inodo.block[i], path, start);
            }
        }
    }
    sb = this->getSB(path, start);
    this->saveSB(sb, path, start);
}

void obcp::changeBC(int bloque, string path, int start, int padre, int abuelo){
    Structs::SB sb = this->getSB(path, start);
    Structs::BC bc = this->getBC(path, (sb.block_start + bloque * sizeof(Structs::BC)));
    Structs::BC bc_nuevo;
    for(int i = 0; i < 4; i++){
        string tmp = bc.content[i].name;
        if(bc.content[i].inodo != -1){
            if(tmp == "."){
                strcpy(bc_nuevo.content[i].name, ".");
                bc_nuevo.content[i].inodo = padre;
                this->saveBC(bc_nuevo, path, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));
            }else if(tmp == ".."){
                strcpy(bc_nuevo.content[i].name, "..");
                bc_nuevo.content[i].inodo = abuelo;
                this->saveBC(bc_nuevo, path, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));
            }else{
                string tmp = bc.content[i].name;
                strcpy(bc_nuevo.content[i].name, tmp.c_str());
                bc_nuevo.content[i].inodo = sb.firts_ino;
                this->saveBC(bc_nuevo, path, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));

                FILE * file = NULL;
                file = fopen(path.c_str(), "rb+");
                fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
                fwrite("1", 1, 1, file);
                fclose(file);

                sb.free_blocks_count--;
                sb.first_blo = sb.first_blo + 1;
                this->saveSB(sb, path, start);
                this->changeInodo(bc.content[i].inodo, path, start, padre);
            }
        }
    }
    sb = this->getSB(path, start);
    this->saveSB(sb, path, start);
}

void obcp::changeBAR(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BAR bar = this->getBAR(path, (sb.block_start + bloque * sizeof(Structs::BAR)));
    Structs::BAR bar_nuevo;
    string tmp = bar.content;
    strcpy(bar_nuevo.content, tmp.c_str());
    this->saveBAR(bar_nuevo, path, (sb.block_start + sb.first_blo * sizeof(Structs::BAR)));

    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
    fwrite("1", 1, 1, file);
    fclose(file);

    sb.free_blocks_count--;
    sb.first_blo = sb.first_blo + 1;
    this->saveSB(sb, path, start);
}
