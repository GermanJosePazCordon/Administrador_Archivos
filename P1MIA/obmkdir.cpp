#include "obmkdir.h"
#include "iostream"
#include "structs.h"
#include "list"

using namespace std;

obmkdir::obmkdir()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obmkdir::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obmkdir::setP(string letra){
    string data = letra;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    letra = data;
    this->letra = letra;
}

Structs::SB obmkdir::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obmkdir::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obmkdir::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obmkdir::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

void obmkdir::saveSB(Structs::SB sb, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}

void obmkdir::saveInodo(Structs::TI inodo, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
}

void obmkdir::saveBC(Structs::BC bc, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
}

void obmkdir::saveBAR(Structs::BAR bar, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
}

Structs::Journaling obmkdir::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

void obmkdir::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obmkdir::addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start){
    bool seguimos = true;
    int next = start + sizeof(Structs::SB);
    Structs::Journaling jng_tmp;
    while(seguimos){
        jng_tmp = this->getJournaling(path_paticion, next);
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

list<string> obmkdir::separar_carpetas(string path) {
    if (path[0] == '/') {
        path = path.substr(1, path.length());
    }
    list<string> lista_carpetas;
    char ruta[path.length() + 1];
    strcpy(ruta, path.c_str());
    string nombre_carpeta;
    for (int i = 0; i < path.length() + 1; i++) {
        if (ruta[i] == '/' /*|| i == path.length()*/) {
            lista_carpetas.push_back(nombre_carpeta);
            nombre_carpeta.clear();
            continue;
        }
        nombre_carpeta += ruta[i];
    }
    return lista_carpetas;
}

void obmkdir::exec(){
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return;
    }
    if(this->letra != "" && this->letra != "p"){
        cout<<"\nParametro 'p' incorrecto"<<endl;
        return;
    }else if(this->letra == "p"){
        this->p = true;
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
    Structs::SB sb;
    //OBTENEMOS LA RUTA SPLITEADA SEGUN EL '/';
    list<string> lista_carpetas;
    lista_carpetas = separar_carpetas(this->path);
    list<string>::iterator it;
    //EMPEZANDO EL FOR PARA NAVEGAR ENTRE CARPETAS
    Structs::TI inodo_actual; //INODO EN EL QUE NOS ENCONTRAMOS
    Structs::BC bc_actual; //BLOQUE DE CARPETA EN LA QUE NOS ENCONTRAMOS
    int inodoPadre = 0; //INODOS QUE TOCA REVISAR
    int inodoAbuelo = 0; //INODOS QUE REVISAMOS ANTERIORMENTE /home/carpeta/caeesa home
    //int journaling = start_particion + sizeof(Structs::SB) + sizeof(Structs::Journaling) * 2;
    bool todas_creadas = true; //VALIDA SI TODAS LAS CARPETAS DE LA RUTA ESTAN CREADAS, ESTO PARA DETERMINAR SI EL ARCHIVO PUEDE ESTAR CREADO O NO
    for (it = lista_carpetas.begin(); it != lista_carpetas.end(); it++) {
        //OBTENEMOS EL SUPER BLOQUE
        sb = this->getSB(path_particion, start_particion);
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        //PRIMER PASADA, SE VERIFICA SI LA CARPETA ACTUAL ESTA CREADA O NO, NO SE REALIZA NINGUNA ACCION MAS QUE VALIDACIONES
        bool carpeta_existente = false;
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
        //SEGUNDA PASADA, SE EJECUTAN ACCIONES DEPENDIENDO DE LAS VALIDACIONES HECHAS EN LA PRIMER PASADA
        if(!carpeta_existente){
            todas_creadas = false; //SE ACTUALIZO ESTA VARIBLE YA QUE AL EXISTIR UNA CARPETA SIN CREARSE NO PUEDE ESTAR CREADO EL ARCHIVO
            //LA CARPETA NO EXITE, SE DEBE VALIDAR SI EL PARAMETRO R ESTA ACTIVO PARA SABER SI CREAR O NO LA CARPETA
            if(this->p){
                //BUSCAR DONDE CREARLA, EL PRIMER ESPACIO LIBRE SIRVE
                bool carpeta_creada = false;
                for(int i = 0; i < 15; i++){
                    if(carpeta_creada){
                        break;
                    }
                    //PRIMERO REVISAMOS EN LOS BLOQUES ACTIVOS SI HAY ESPACIO PARA LA CARPETA, EN CASO CONTRARIO LA CREAMOS EN EL PRIMER BLOQUE INACTIVO
                    if(inodo_actual.block[i] != -1){
                        //POSICIONAMOS EL BLOQUE ACTUAL PARA PODER ACCEDER A SU CONTENIDO
                        bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                        for(int j = 0; j < 4; j++){
                            //VERIFICAMOS SI EL NODO ACTUAL ESTA INACTIVO, DE ESTARLO CREAMOS LA CARPETA
                            if(bc_actual.content[j].inodo == -1){
                                bc_actual.content[j].inodo = sb.firts_ino;
                                string name = *it;
                                strcpy(bc_actual.content[j].name, name.c_str());
                                //GUARDANDO LA CARPETA
                                this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                                inodoAbuelo = inodoPadre;
                                inodoPadre = sb.firts_ino;
                                this->crearCarpeta(sb, inodoPadre, inodoAbuelo, path_particion, start_particion);
                                carpeta_creada = true;
                                sb = this->getSB(path_particion, start_particion);
                                break;
                            }
                        }
                    }else{
                        //VALIDAMOS SI EL BLOQUE INACTIVO ES DIRECTO
                        if(i < 12){
                            //CREAMOS LA CARPETA EN EL BLOQUE INACTIVO
                            inodo_actual.block[i] = sb.first_blo;
                            //GUARDANDO EL INODO
                            this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
                            //CREANDO LA CARPETA
                            Structs::BC bc;
                            bc.content[0].inodo = sb.firts_ino;
                            string name = *it;
                            strcpy(bc.content[0].name, name.c_str());
                            for(int i = 1; i < 4; i++){
                                bc.content[i].inodo = -1;
                            }
                            //GUARDANDO LA CARPETA
                            this->saveBC(bc, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                            //ACTUALIZANDO EL SUPER BLOQUE
                            FILE * file = NULL;
                            file = fopen(path_particion.c_str(), "rb+");
                            fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
                            fwrite("1", 1, 1, file);
                            fclose(file);
                            sb.free_blocks_count = sb.blocks_count - 1;
                            sb.first_blo = sb.first_blo + 1;
                            inodoAbuelo = inodoPadre;
                            inodoPadre = sb.firts_ino;
                            this->crearCarpeta(sb, inodoPadre, inodoAbuelo, path_particion, start_particion);
                            carpeta_creada = true;
                        }else{
                            //ES INDIRECTO
                        }
                        sb = this->getSB(path_particion, start_particion);
                        break;
                    }
                }
            }else{
                //SIGNIFICA QUE NO SE DEBE CREAR LA CARPETA, POR LO TANTO LA RUTA ES UN ERROR, LA CARPETA A CREAR
                cout<<"\nNo existe la carpeta : "<<*it<<endl;
                return;
            }
        }
    }
    //CUANDO YA ESTEN CREADAS TODAS LAS CARPETAS PADRES DEBEMOS CREAR LA ULTIMA CARPETA DE LA RUTA, PARA ESTA NO IMPORTARA EL PARAMETRO P, SIEMPRE SE CREARA
    //PRIMERO OBTENEMOS EL NOMBRE DE LA ULTIMA CARPETA
    char charPath[this->path.length() + 1];
    strcpy(charPath, this->path.c_str());
    string last_name; //VAIABLE CON EL NOMBRE DE LA CARPETA
    for(int i = this->path.length(); i > 0; i--){
        if(charPath[i]== '/'){
            break;
        }
        last_name = charPath[i] + last_name;
    }
    while(!lista_carpetas.empty()){
        lista_carpetas.pop_front();
    }
    lista_carpetas.push_back(last_name);
    for (it = lista_carpetas.begin(); it != lista_carpetas.end(); it++) {
        //OBTENEMOS EL SUPER BLOQUE
        sb = this->getSB(path_particion, start_particion);
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        //PRIMER PASADA, SE VERIFICA SI LA CARPETA ACTUAL ESTA CREADA O NO, NO SE REALIZA NINGUNA ACCION MAS QUE VALIDACIONES
        bool carpeta_existente = false;
        for(int i = 0; i < 15; i++){
            if(inodo_actual.block[i] != -1){
                //POSICIONAMOS EL BLOQUE ACTUAL PARA PODER ACCEDER A SU CONTENIDO
                //bc_actual = inodo_actual.block[i];
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
        //SEGUNDA PASADA, SE EJECUTAN ACCIONES DEPENDIENDO DE LAS VALIDACIONES HECHAS EN LA PRIMER PASADA
        if(!carpeta_existente){
            todas_creadas = false; //SE ACTUALIZO ESTA VARIBLE YA QUE AL EXISTIR UNA CARPETA SIN CREARSE NO PUEDE ESTAR CREADO EL ARCHIVO
            //LA CARPETA NO EXITE, SE DEBE VALIDAR SI EL PARAMETRO R ESTA ACTIVO PARA SABER SI CREAR O NO LA CARPETA
                //SE DEBE CREAR LA CARPETA, SI ES EXT3 SE DEBE ACTUALIZAR EL JOURNALING
                //BUSCAR DONDE CREARLA, EL PRIMER ESPACIO LIBRE SIRVE
                bool carpeta_creada = false;
                for(int i = 0; i < 15; i++){
                    if(carpeta_creada){
                        //SE DEBE CREAR LA CARPETA, SI ES EXT3 SE DEBE ACTUALIZAR EL JOURNALING
                        if(sb.filesystem_type == 3){
                            this->addJournaling("--", this->path, path_particion, "mkdir", '0', start_particion);
                        }
                        break;
                    }
                    //PRIMERO REVISAMOS EN LOS BLOQUES ACTIVOS SI HAY ESPACIO PARA LA CARPETA, EN CASO CONTRARIO LA CREAMOS EN EL PRIMER BLOQUE INACTIVO
                    if(inodo_actual.block[i] != -1){
                        //POSICIONAMOS EL BLOQUE ACTUAL PARA PODER ACCEDER A SU CONTENIDO
                        bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                        for(int j = 0; j < 4; j++){
                            //VERIFICAMOS SI EL NODO ACTUAL ESTA INACTIVO, DE ESTARLO CREAMOS LA CARPETA
                            if(bc_actual.content[j].inodo == -1){
                                bc_actual.content[j].inodo = sb.firts_ino;
                                string name = *it;
                                strcpy(bc_actual.content[j].name, name.c_str());
                                //GUARDANDO LA CARPETA
                                this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                                inodoAbuelo = inodoPadre;
                                inodoPadre = sb.firts_ino;
                                this->crearCarpeta(sb, inodoPadre, inodoAbuelo, path_particion, start_particion);
                                carpeta_creada = true;
                                sb = this->getSB(path_particion, start_particion);
                                break;
                            }
                        }
                    }else{
                        //VALIDAMOS SI EL BLOQUE INACTIVO ES DIRECTO
                        if(i < 12){
                            //CREAMOS LA CARPETA EN EL BLOQUE INACTIVO
                            inodo_actual.block[i] = sb.first_blo;
                            //GUARDANDO EL INODO
                            this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
                            //CREANDO LA CARPETA
                            Structs::BC bc;
                            bc.content[0].inodo = sb.firts_ino;
                            string name = *it;
                            strcpy(bc.content[0].name, name.c_str());
                            for(int i = 1; i < 4; i++){
                                bc.content[i].inodo = -1;
                            }
                            //GUARDANDO LA CARPETA
                            this->saveBC(bc, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                            //ACTUALIZANDO EL SUPER BLOQUE
                            FILE * file = NULL;
                            file = fopen(path_particion.c_str(), "rb+");
                            fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
                            fwrite("1", 1, 1, file);
                            fclose(file);
                            sb.free_blocks_count = sb.blocks_count - 1;
                            sb.first_blo = sb.first_blo + 1;
                            inodoAbuelo = inodoPadre;
                            inodoPadre = sb.firts_ino;
                            this->crearCarpeta(sb, inodoPadre, inodoAbuelo, path_particion, start_particion);
                            carpeta_creada = true;
                        }else{
                            //ES INDIRECTO
                        }
                        sb = this->getSB(path_particion, start_particion);
                        break;
                    }
                }
        }
    }
}

void obmkdir::crearCarpeta(Structs::SB sb, int inodoPadre, int inodoAbuelo, string path, int start_particion){
    //CREANDO EL NUEVO INODO CARPETA
    Structs::TI inodo;
    inodo.type = '0';
    inodo.uid = log.uid;
    inodo.gid = log.guid;
    inodo.size = 0;
    inodo.block[0] = sb.first_blo;
    inodo.atime = time(0);
    inodo.ctime = time(0);
    inodo.mtime = time(0);
    inodo.perm = 664;
    for(int i = 1; i < 15; i++){
        inodo.block[i] = -1;
    }
    //GUARDANDO EL INODO
    this->saveInodo(inodo, path, (sb.inode_start + sb.firts_ino * sizeof(Structs::TI)));
    //CREANDO CARPETA
    Structs::BC carpeta;
    //PADRE
    carpeta.content[0].inodo = inodoPadre;
    strcpy(carpeta.content[0].name, ".");
    //ABUELO
    carpeta.content[1].inodo = inodoAbuelo;
    strcpy(carpeta.content[1].name, "..");
    //GUARDANDO LA CARPETA
    this->saveBC(carpeta, path, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));
    //SETEANDO LOS BITMAPS
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_inode_start + sb.firts_ino), SEEK_SET);
    fwrite("1", 1, 1, file);
    fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
    fwrite("1", 1, 1, file);
    fclose(file);
    //ACTUALIZANDO EL SUPER BLOQUE
    sb.free_inodes_count = sb.inodes_count - 1;
    sb.free_blocks_count = sb.blocks_count - 1;
    sb.firts_ino = sb.firts_ino + 1;
    sb.first_blo = sb.first_blo + 1;
    //GUARDANDO EL SUPER BLOQUE
    this->saveSB(sb, path, start_particion);
}
