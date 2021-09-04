#include "obtouch.h"
#include "iostream"
#include "structs.h"
#include "list"
#include "fstream"
#include "obedit.h"

using namespace std;

obtouch::obtouch()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void obtouch::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obtouch::setCont(string cont){
    if(cont[0] == '"'){
        this->cont = path.substr(1, path.size()-1);
        this->cont = this->cont.substr(0, this->cont.size()-1);
    }else{
        this->cont = cont;
    }
}

void obtouch::setSize(int size){
    this->size = size;
}

void obtouch::setR(){
    this->r = true;
}

void obtouch::setStdin(){
    this->stdi = true;
}

Structs::SB obtouch::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obtouch::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obtouch::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obtouch::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

void obtouch::saveSB(Structs::SB sb, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}

void obtouch::saveInodo(Structs::TI inodo, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
}

void obtouch::saveBC(Structs::BC bc, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
}

void obtouch::saveBAR(Structs::BAR bar, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&bar, sizeof(Structs::BAR), 1, file);
    fclose(file);
}

Structs::Journaling obtouch::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

void obtouch::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obtouch::addJournaling(string content, string path, string path_paticion, string operacion, char tipo, int start){
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

list<string> obtouch::separar_carpetas(string path) {
    if (path[0] == '/') {
        path = path.substr(1, path.length());
    }
    list<string> lista_carpetas;
    char ruta[path.length() + 1];
    strcpy(ruta, path.c_str());
    string nombre_carpeta;
    for (int i = 0; i < path.length() + 1; i++) {
        if (ruta[i] == '/') {
            lista_carpetas.push_back(nombre_carpeta);
            nombre_carpeta.clear();
            continue;
        }
        nombre_carpeta += ruta[i];
    }
    return lista_carpetas;
}

void obtouch::exec(){
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return;
    }
    if(this->size < 0){
        cout<<"\nTamaño del archivo negativo."<<endl;
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
    if(lista_carpetas.empty()){
        todas_creadas = false;
    }
    for(it = lista_carpetas.begin(); it != lista_carpetas.end(); it++){
        //OBTENEMOS EL SUPER BLOQUE
        sb = this->getSB(path_particion, start_particion);
        //cout<<"\nCARPETA DE LA LISTA : "<<*it<<endl;
        //cout<<"\ninodo : "<<inodoPadre<<endl;
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
                    //cout<<bc_actual.content[j].name<<" apunta a "<<bc_actual.content[j].inodo<<endl;
                    if(strcmp(bc_actual.content[j].name, name.c_str()) == 0){
                        //cout<<"\ncarpeta encontrada : "<<*it<<endl;
                        //CARPETA ENCONTRADA EN LA POSICION i DEL PRIMER BLOQUE DEL NODOD
                        carpeta_existente = true;
                        inodoAbuelo = inodoPadre;
                        inodoPadre = bc_actual.content[j].inodo;
                    }
                }
                //cout<<"\n---------------------------------"<<endl;
            }
        }
        //SEGUNDA PASADA, SE EJECUTAN ACCIONES DEPENDIENDO DE LAS VALIDACIONES HECHAS EN LA PRIMER PASADA
        if(!carpeta_existente){
            todas_creadas = false; //SE ACTUALIZO ESTA VARIBLE YA QUE AL EXISTIR UNA CARPETA SIN CREARSE NO PUEDE ESTAR CREADO EL ARCHIVO
            //LA CARPETA NO EXITE, SE DEBE VALIDAR SI EL PARAMETRO R ESTA ACTIVO PARA SABER SI CREAR O NO LA CARPETA

            if(this->r){
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
                                //cout<<"\ncarpeta : "<<*it<<" esta en "<<inodo_actual.block[i]<<endl;
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
                            for(int i = 0; i < 4; i++){
                                bc.content[i].inodo = -1;
                            }
                            bc.content[0].inodo = sb.firts_ino;
                            string name = *it;
                            strcpy(bc.content[0].name, name.c_str());

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
                        break;
                    }
                }
            }else{
                //SIGNIFICA QUE NO SE DEBE CREAR LA CARPETA, POR LO TANTO LA RUTA ES UN ERROR
                cout<<"\nNo existe la carpeta : "<<*it<<endl;
                return;
            }
        }
    }
    //UNA VEZ CREADAS TODAS LAS CARPETAS NECESARIAS DEL PATH PROCEDEMOS A CREAR EL ARCHIVO
    //PRIMERO OBTENEMOS EL NOMBRE DEL ARCHIVO
    char charPath[this->path.length() + 1];
    strcpy(charPath, this->path.c_str());
    string file_name; //VAIABLE CON EL NOMBRE DEL ARCHIVO
    for(int i = this->path.length(); i > 0; i--){
        if(charPath[i]== '/'){
            break;
        }
        file_name = charPath[i] + file_name;
    }
    //PARA EMPEZAR OBTENEMOS EL CONTENIDO DEL ARCHIVO, PUEDE SER POR CONT, STDIN O SIZE
    string content = "";//VARIABLE CON EL CONTENIDO A GUARDAR
    if(cont != ""){
        //RECUPERAMOS DE LA RUTA
        ifstream in(this->cont);
        string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        content = contents;
    }else if(this->stdi){
        //RECUPERAMOS LA ENTRADA
        cout<<"\nIngrese el texto a guardar en el archivo : \n"<<endl;
        cin>>content;
    }else if(this->size != 0){
        //CREAMOS EL CONTENIDO SEGUN EL TAMAÑO
        int contador = 0;
        for(int i = 0; i < this->size; i++){
            content += to_string(contador);
            contador += 1;
            if(contador > 9){
                contador = 0;
            }
        }
    }
    bool bloque_creado = false;
    if(!todas_creadas){
        cout<<"1"<<endl;
        //YA QUE EXISTIA ALMENOS UNA CARPETA SIN CREAR ES POR SEGURO QUE EL ARCHIVO NO ESTA CREADO
        //AHORA DEBEMOS BUSCAR UN ESPACIO LIBRE PARA CREAR EL INODO CARPETA
        sb = this->getSB(path_particion, start_particion);
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));

        for(int i = 0; i < 15; i++){
            if(bloque_creado){
                if(sb.filesystem_type == 3){
                    string tmp;
                    for(int i = 0; i < 100; i++){
                        tmp += content[i];
                    }
                    this->addJournaling(tmp, this->path, path_particion, "touch", '1', start_particion);
                }
                return;
            }
            //VERIFICAMOS EN LOS BLOQUES DEL INODO
            cout<<i<<" : "<<inodo_actual.block[i]<<endl;
            if(inodo_actual.block[i] != -1){
                cout<<"2"<<endl;
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    //VERIFICAMOS SI EL NODO ACTUAL ESTA INACTIVO, DE ESTARLO CREAMOS LA CARPETA
                    if(bc_actual.content[j].inodo == -1){
                        bc_actual.content[j].inodo = sb.firts_ino;
                        strcpy(bc_actual.content[j].name, file_name.c_str());
                        //GUARDANDO LA CARPETA
                        this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                        this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                        bloque_creado = true;
                        break;
                    }
                }
            }else{
                //VALIDAMOS SI EL BLOQUE INACTIVO ES DIRECTO
                if(i < 12){
                    cout<<"3"<<endl;
                    //CREAMOS LA CARPETA EN EL BLOQUE INACTIVO
                    inodo_actual.block[i] = sb.first_blo;
                    //GUARDANDO EL INODO
                    this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
                    inodoAbuelo = inodoPadre;
                    inodoPadre = sb.firts_ino;
                    //CREANDO CARPETA
                    Structs::BC carpeta;
                    //PADRE
                    carpeta.content[0].inodo = inodoPadre;
                    strcpy(carpeta.content[0].name, file_name.c_str());
                    //GUARDANDO LA CARPETA
                    this->saveBC(carpeta, path_particion, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));
                    FILE * file = NULL;
                    file = fopen(path_particion.c_str(), "rb+");
                    fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
                    fwrite("1", 1, 1, file);
                    fclose(file);
                    sb.free_blocks_count = sb.blocks_count - 1;
                    sb.first_blo = sb.first_blo + 1;
                    this->saveSB(sb, path_particion, start_particion);
                    this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                }else{
                    //INDIRECTOS
                }
                bloque_creado = true;
                break;
            }
        }
    }else{
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        sb = this->getSB(path_particion, start_particion);
        //YA QUE TODAS LAS CARPETAS ESTABAN CREADAS DESDE UN INICIO SE TIENE QUE VALIDAR QUE EL ARCHIVO NO ESTE CREADO
        for(int i = 0; i < 15; i++){
            if(bloque_creado){
                if(sb.filesystem_type == 3){
                    string tmp;
                    for(int i = 0; i < 100; i++){
                        tmp += content[i];
                    }
                    this->addJournaling(tmp, this->path, path_particion, "touch", '1', start_particion);
                }
                return;
            }
            //VERIFICAMOS EN LOS BLOQUES DEL INODO
            if(inodo_actual.block[i] != -1){
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    if(strcmp(bc_actual.content[j].name, file_name.c_str()) == 0){
                        cout<<"\nYa existe el archivo : "<<file_name<<endl;
                        cout<<"\nDesea sobreescribirlo? [s/n]"<<endl;
                        string tmp;
                        cin>>tmp;
                        if(tmp == "s" || tmp == "S"){
                            if(this->cont == "" && !this->stdi && this->size == 0){
                                cout<<"\nNo hay informacion para escribir en el archivo"<<endl;
                                return;
                            }
                            obedit * edit = new obedit();
                            edit->setPath(this->path);
                            edit->content = content;
                            edit->exec();
                            return;
                        }
                        cout<<"\nEl archivo no fue modificado"<<endl;
                        return;
                    }
                    //VERIFICAMOS SI EL NODO ACTUAL ESTA INACTIVO, DE ESTARLO CREAMOS LA CARPETA
                    if(bc_actual.content[j].inodo == -1){
                        bc_actual.content[j].inodo = sb.firts_ino;
                        strcpy(bc_actual.content[j].name, file_name.c_str());
                        //GUARDANDO LA CARPETA
                        this->saveBC(bc_actual, path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                        this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                        bloque_creado = true;
                        break;
                    }
                }
            }else{
                //VALIDAMOS SI EL BLOQUE INACTIVO ES DIRECTO
                if(i < 12){
                    inodo_actual.block[i] = sb.first_blo;
                    //GUARDANDO EL INODO
                    this->saveInodo(inodo_actual, path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
                    inodoAbuelo = inodoPadre;
                    inodoPadre = sb.firts_ino;
                    //CREANDO CARPETA
                    Structs::BC carpeta;
                    //PADRE
                    carpeta.content[0].inodo = inodoPadre;
                    strcpy(carpeta.content[0].name, file_name.c_str());
                    //GUARDANDO LA CARPETA
                    this->saveBC(carpeta, path_particion, (sb.block_start + sb.first_blo * sizeof(Structs::BC)));
                    FILE * file = NULL;
                    file = fopen(path_particion.c_str(), "rb+");
                    fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
                    fwrite("1", 1, 1, file);
                    fclose(file);
                    sb.free_blocks_count = sb.blocks_count - 1;
                    sb.first_blo = sb.first_blo + 1;
                    this->saveSB(sb, path_particion, start_particion);
                    this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                }else{
                    //INDIRECTOS
                }
                bloque_creado = true;
                break;
            }
        }
    }
}

void obtouch::crearCarpeta(Structs::SB sb, int inodoPadre, int inodoAbuelo, string path, int start_particion){
    //CREANDO EL NUEVO INODO CARPETA
    Structs::TI inodo;
    inodo.type = '0';
    inodo.uid = 1;
    inodo.gid = 1;
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
    FILE * file = NULL;
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

void obtouch::crearInodoArchivo(Structs::SB sb, string content, string path, int start_particion, int inodoPadre){
    Structs::TI inodo; /*this->getInodo(path, (sb.inode_start + inodoPadre * sizeof(Structs::TI)))*/;
    //CREANDO INODO ARCHIVO
    inodo.type = '1';
    inodo.uid = 1;
    inodo.gid = 1;
    inodo.size = content.length();
    inodo.block[0] = sb.first_blo;
    inodo.atime = time(0);
    inodo.ctime = time(0);
    inodo.mtime = time(0);
    inodo.perm = 664;
    for(int i = 1; i < 15; i++){
        inodo.block[i] = -1;
    }
    //GUARDANDO EL INODO
    this->saveInodo(inodo, path, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    //FILE * file = NULL;
    //ACTUALIZANDO EL SUPER BLOQUE
    //SETEANDO LOS BITMAPS
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_inode_start + sb.firts_ino), SEEK_SET);
    fwrite("1", 1, 1, file);
    fclose(file);
    sb.free_inodes_count = sb.inodes_count - 1;
    sb.firts_ino = sb.firts_ino + 1;
    //GUARDANDO EL SUPER BLOQUE
    this->saveSB(sb, path, start_particion);
    //COSAS PARA CREAR EL BLOQUE ARCHIVO
    int limite = content.length();
    int numeroBloques = limite / 64;
    if (numeroBloques * 64 < limite) ++numeroBloques;
    string contenido[numeroBloques];
    int cont = 0;
    for(int i = 0; i < numeroBloques; i++){
        for(int j = 0; j < 64; j++){
            if(cont == limite){
                break;
            }
            contenido[i] += content[cont];
            cont +=1;
        }
    }
    string cnt;
    for(int i = 0; i < numeroBloques; i++){
        cnt = contenido[i];
        this->crearArchivo(inodoPadre, i, cnt, path, start_particion);
    }
}

void obtouch::crearArchivo(int inodoPadre, int bloque, string content, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    inodo.block[bloque] = sb.first_blo;
    //GUARDANDO EL INODO
    this->saveInodo(inodo, path, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    Structs::BAR archivo;
    strcpy(archivo.content, content.c_str());
    //GUARDANDO EL ARCHIVO
    this->saveBAR(archivo, path, (sb.block_start + sb.first_blo * sizeof(Structs::BAR)));
    //SETEANDO LOS BITMAPS
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.bm_block_start + sb.first_blo), SEEK_SET);
    fwrite("1", 1, 1, file);
    fclose(file);
    //ACTUALIZANDO EL SUPER BLOQUE
    sb.free_blocks_count = sb.blocks_count - 1;
    sb.first_blo = sb.first_blo + 1;
    //GUARDANDO EL SUPER BLOQUE
    this->saveSB(sb, path, start);
}
