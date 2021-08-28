#include "obtouch.h"
#include "iostream"
#include "structs.h"
#include "list"
#include "fstream"

using namespace std;

obtouch::obtouch()
{

}

extern Structs::Discos discos[99];

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

void obtouch::saveSB(Structs::SB sb, string path, int pos){
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
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

void obtouch::saveJournaling(Structs::Journaling journaling, string path, int pos){
    char charPath[path.size() + 1];
    strcpy(charPath, path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&journaling, sizeof(Structs::Journaling), 1, file);
    fclose(file);
}

void obtouch::addJournaling(string content, string nombre, string path, string operacion, char tipo, int part_start){
    Structs::Journaling jng;
    strcpy(jng.contenido, content.c_str());
    jng.date = time(0);
    strcpy(jng.path, nombre.c_str());
    jng.size = 0;
    strcpy(jng.operacion, operacion.c_str());
    jng.tipo = tipo;
    Structs::Journaling jng_tmp;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (part_start + sizeof(Structs::SB)), SEEK_SET);
    fread(&jng_tmp, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    saveJournaling(jng, path, (part_start + sizeof(Structs::SB) + jng_tmp.number *sizeof(Structs::Journaling)));
    jng_tmp.number = jng_tmp.number + sizeof(Structs::Journaling);
    saveJournaling(jng_tmp, path, (part_start + sizeof(Structs::SB)));
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
    cout<<"\nEMPEZANDO"<<endl;
    for (it = lista_carpetas.begin(); it != lista_carpetas.end(); it++) {
        //OBTENEMOS EL SUPER BLOQUE
        sb = this->getSB(path_particion, start_particion);
        //cout<<"\nCARPETA DE LA LISTA : "<<*it<<endl;
        cout<<"\ninodo : "<<inodoPadre<<endl;
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
                    cout<<bc_actual.content[j].name<<" apunta a "<<bc_actual.content[j].inodo<<endl;
                    if(strcmp(bc_actual.content[j].name, name.c_str()) == 0){
                        //cout<<"\ncarpeta encontrada : "<<*it<<endl;
                        //CARPETA ENCONTRADA EN LA POSICION i DEL PRIMER BLOQUE DEL NODOD
                        carpeta_existente = true;
                        inodoAbuelo = inodoPadre;
                        inodoPadre = bc_actual.content[j].inodo;
                    }
                }
                cout<<"\n---------------------------------"<<endl;
            }
        }
        //SEGUNDA PASADA, SE EJECUTAN ACCIONES DEPENDIENDO DE LAS VALIDACIONES HECHAS EN LA PRIMER PASADA
        if(!carpeta_existente){
            todas_creadas = false; //SE ACTUALIZO ESTA VARIBLE YA QUE AL EXISTIR UNA CARPETA SIN CREARSE NO PUEDE ESTAR CREADO EL ARCHIVO
            //LA CARPETA NO EXITE, SE DEBE VALIDAR SI EL PARAMETRO R ESTA ACTIVO PARA SABER SI CREAR O NO LA CARPETA
            if(this->r){
                //SE DEBE CREAR LA CARPETA, SI ES EXT3 SE DEBE ACTUALIZAR EL JOURNALING
                /*cout<<"\ntype : "<<type_particion<<endl;
                if(sb.filesystem_type == 3){
                    string name = *it;
                    this->addJournaling("-", name, path_particion, "mkdir", '0', start_particion);
                }*/
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
                                FILE * file = NULL;
                                file = fopen(path_particion.c_str(), "rb+");
                                fseek(file, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)), SEEK_SET);
                                fwrite(&bc_actual, sizeof(Structs::BC), 1, file);
                                fclose(file);
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
                            FILE * file = NULL;
                            file = fopen(path_particion.c_str(), "rb+");
                            fseek(file, (sb.inode_start + inodoPadre * sizeof(Structs::TI)), SEEK_SET);
                            fwrite(&inodo_actual, sizeof(Structs::TI), 1, file);
                            fclose(file);
                            inodoAbuelo = inodoPadre;
                            inodoPadre = sb.firts_ino;
                            this->crearCarpeta(sb, inodoPadre, inodoAbuelo, path_particion, start_particion);
                            carpeta_creada = true;
                            //cout<<"\ncarpeta : "<<*it<<" apunta "<<inodo_actual.block[i]<<endl;
                            //break;
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
    strcpy(charPath, path.c_str());
    string file_name; //VAIABLE CON EL NOMBRE DEL ARCHIVO
    for(int i = path.length(); i > 0; i--){
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
    if(!todas_creadas){
        //YA QUE EXISTIA ALMENOS UNA CARPETA SIN CREAR ES POR SEGURO QUE EL ARCHIVO NO ESTA CREADO
        //AHORA DEBEMOS BUSCAR UN ESPACIO LIBRE PARA CREAR EL INODO CARPETA
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        sb = this->getSB(path_particion, start_particion);
        for(int i = 0; i < 15; i++){
            //VERIFICAMOS EN LOS BLOQUES DEL INODO
            if(inodo_actual.block[i] != -1){
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    //VERIFICAMOS SI EL NODO ACTUAL ESTA INACTIVO, DE ESTARLO CREAMOS LA CARPETA
                    if(bc_actual.content[j].inodo == -1){
                        bc_actual.content[j].inodo = sb.firts_ino;
                        strcpy(bc_actual.content[j].name, file_name.c_str());

                        //GUARDANDO LA CARPETA
                        FILE * file = NULL;
                        file = fopen(path_particion.c_str(), "rb+");
                        fseek(file, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)), SEEK_SET);
                        fwrite(&bc_actual, sizeof(Structs::BC), 1, file);
                        fclose(file);
                        this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                        break;
                    }
                }
            }else{
                //VALIDAMOS SI EL BLOQUE INACTIVO ES DIRECTO
                if(i < 12){
                    //CREAMOS LA CARPETA EN EL BLOQUE INACTIVO
                    inodo_actual.block[i] = sb.first_blo;
                    //GUARDANDO EL INODO
                    FILE * file = NULL;
                    file = fopen(path_particion.c_str(), "rb+");
                    fseek(file, (sb.inode_start + inodoPadre * sizeof(Structs::TI)), SEEK_SET);
                    fwrite(&inodo_actual, sizeof(Structs::TI), 1, file);
                    fclose(file);
                    inodoAbuelo = inodoPadre;
                    inodoPadre = sb.firts_ino;
                    this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                }else{
                    //INDIRECTOS
                }
                break;
            }
        }
    }else{
        inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        sb = this->getSB(path_particion, start_particion);
        //YA QUE TODAS LAS CARPETAS ESTABAN CREADAS DESDE UN INICIO SE TIENE QUE VALIDAR QUE EL ARCHIVO NO ESTE CREADO
        for(int i = 0; i < 15; i++){
            //VERIFICAMOS EN LOS BLOQUES DEL INODO
            if(inodo_actual.block[i] != -1){
                bc_actual = this->getBC(path_particion, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    cout<<bc_actual.content[j].name <<" == "<<file_name<<endl;
                    if(strcmp(bc_actual.content[j].name, file_name.c_str()) == 0){
                        cout<<"\nYa existe el archivo : "<<file_name<<endl;
                        return;
                    }
                    //VERIFICAMOS SI EL NODO ACTUAL ESTA INACTIVO, DE ESTARLO CREAMOS LA CARPETA
                    if(bc_actual.content[j].inodo == -1){
                        bc_actual.content[j].inodo = sb.firts_ino;
                        strcpy(bc_actual.content[j].name, file_name.c_str());
                        //GUARDANDO LA CARPETA
                        FILE * file = NULL;
                        file = fopen(path_particion.c_str(), "rb+");
                        fseek(file, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)), SEEK_SET);
                        fwrite(&bc_actual, sizeof(Structs::BC), 1, file);
                        fclose(file);
                        this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                        break;
                    }
                }
            }else{
                //VALIDAMOS SI EL BLOQUE INACTIVO ES DIRECTO
                if(i < 12){
                    //CREAMOS LA CARPETA EN EL BLOQUE INACTIVO
                    inodo_actual.block[i] = sb.first_blo;
                    //GUARDANDO EL INODO
                    FILE * file = NULL;
                    file = fopen(path_particion.c_str(), "rb+");
                    fseek(file, (sb.inode_start + inodoPadre * sizeof(Structs::TI)), SEEK_SET);
                    fwrite(&inodo_actual, sizeof(Structs::TI), 1, file);
                    fclose(file);
                    inodoAbuelo = inodoPadre;
                    inodoPadre = sb.firts_ino;
                    this->crearInodoArchivo(sb, content, path_particion, start_particion, sb.firts_ino);
                }else{
                    //INDIRECTOS
                }
                break;
            }
        }
    }
    sb = this->getSB(path_particion, start_particion);
    inodo_actual = this->getInodo(path_particion, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    Structs::BAR archivos;
    FILE * file = NULL;
    file = fopen(path_particion.c_str(), "rb+");
    for(int i = 0; i < 15; i++){
        if(inodo_actual.block[i] != -1){
            fseek(file, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BAR)), SEEK_SET);
            fread(&archivos, sizeof(Structs::BAR), 1, file);
            cout<<"\nblock ["<<i<<"] : "<<inodo_actual.block[i]<<endl;
            cout<<"\ncontent : "<<archivos.content<<endl;
            cout<<"\n-----------------------------------"<<endl;
        }
    }
    fclose(file);
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
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.inode_start + sb.firts_ino * sizeof(Structs::TI)), SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    //CREANDO CARPETA
    Structs::BC carpeta;
    //PADRE
    carpeta.content[0].inodo = inodoPadre;
    strcpy(carpeta.content[0].name, ".");
    //ABUELO
    carpeta.content[1].inodo = inodoAbuelo;
    strcpy(carpeta.content[1].name, "..");
    //GUARDANDO LA CARPETA
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.block_start + sb.first_blo * sizeof(Structs::BC)), SEEK_SET);
    fwrite(&carpeta, sizeof(Structs::BC), 1, file);
    fclose(file);
    //SETEANDO LOS BITMAPS
    file = fopen(path.c_str(), "rb+");
    fseek(file, sb.firts_ino, SEEK_SET);
    fwrite("1", 1, 1, file);
    fseek(file, sb.first_blo, SEEK_SET);
    fwrite("1", 1, 1, file);
    fclose(file);
    //ACTUALIZANDO EL SUPER BLOQUE
    sb.free_inodes_count = sb.inodes_count - 1;
    sb.free_blocks_count = sb.blocks_count - 1;
    sb.firts_ino = sb.firts_ino + 1;
    sb.first_blo = sb.first_blo + 1;
    //GUARDANDO EL SUPER BLOQUE
    file = fopen(path.c_str(), "rb+");
    fseek(file, start_particion, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}

void obtouch::crearInodoArchivo(Structs::SB sb, string content, string path, int start_particion, int inodoPadre){
    Structs::TI inodo = this->getInodo(path, (sb.block_start + inodoPadre * sizeof(Structs::TI)));
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
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.inode_start + sb.first_blo * sizeof(Structs::TI)), SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    //ACTUALIZANDO EL SUPER BLOQUE
    sb.free_inodes_count = sb.inodes_count - 1;
    sb.firts_ino = sb.firts_ino + 1;
    //GUARDANDO EL SUPER BLOQUE
    file = fopen(path.c_str(), "rb+");
    fseek(file, start_particion, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
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
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.inode_start + inodoPadre * sizeof(Structs::TI)), SEEK_SET);
    fwrite(&inodo, sizeof(Structs::TI), 1, file);
    fclose(file);
    Structs::BAR archivo;
    strcpy(archivo.content, content.c_str());
    //GUARDANDO EL ARCHIVO
    file = fopen(path.c_str(), "rb+");
    fseek(file, (sb.block_start + sb.first_blo * sizeof(Structs::BAR)), SEEK_SET);
    fwrite(&archivo, sizeof(Structs::BAR), 1, file);
    fclose(file);
    //ACTUALIZANDO EL SUPER BLOQUE
    sb.free_blocks_count = sb.blocks_count - 1;
    sb.first_blo = sb.first_blo + 1;
    //GUARDANDO EL SUPER BLOQUE
    file = fopen(path.c_str(), "rb+");
    fseek(file, start, SEEK_SET);
    fwrite(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
}
