#include "obmkdir.h"
#include "iostream"
#include "structs.h"
#include "list"

using namespace std;

obmkdir::obmkdir()
{

}

extern Structs::Discos discos[99];

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

list<string> obmkdir::separar_carpetas(string path) {
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
        cout<<"\nCARPETA DE LA LISTA : "<<*it<<endl;
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
            if(this->p){
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

}

void obmkdir::crearCarpeta(Structs::SB sb, int inodoPadre, int inodoAbuelo, string path, int start_particion){
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
