#include "obreporte.h"
#include "iostream"
#include "structs.h"
#include "fstream"
#include "list"

using namespace std;

obreporte::obreporte()
{

}

extern Structs::Discos discos[99];

//--------------------------SETERS-----------------------------------

void obreporte::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obreporte::setName(string name){
    if(name[0] == '"'){
        this->name = name.substr(1, name.size()-1);
        this->name = this->name.substr(0, this->name.size()-1);
    }else{
        this->name = name;
    }
    string data = this->name;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    name = data;
    this->name = name;
}

void obreporte::setID(string id){
    this->id = id;
}

void obreporte::setRuta(string ruta){
    if(ruta[0] == '"'){
        this->ruta = ruta.substr(1, ruta.size()-1);
        this->ruta = this->ruta.substr(0, this->ruta.size()-1);
    }else{
        this->ruta = ruta;
    }
}

void obreporte::setRoot(int root){
    this->root = root;
}

bool obreporte::validarName(){
    if(this->name == ""){
        return true;
    }else if(this->name == "mbr"){
        return false;
    }else if(this->name == "disk"){
        return false;
    }else if(this->name == "inode"){
        return false;
    }else if(this->name == "journaling"){
        return false;
    }else if(this->name == "block"){
        return false;
    }else if(this->name == "bm_inode"){
        return false;
    }else if(this->name == "bm_block"){
        return false;
    }else if(this->name == "tree"){
        return false;
    }else if(this->name == "sb"){
        return false;
    }else if(this->name == "file"){
        return false;
    }else if(this->name == "ls"){
        return false;
    }else{
        return true;
    }
    return false;
}

string obreporte::getExt(){
    int limit = this->path.length();
    string ext;
    ext = this->path[limit - 1];
    ext = this->path[limit - 2] + ext;
    ext = this->path[limit - 3] + ext;
    string data = ext;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    ext = data;
    return ext;
}

Structs::MBR obreporte::getMBR(string path){
    Structs::MBR tmp_mbr;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fread(&tmp_mbr, sizeof(Structs::MBR), 1, file);
    fclose(file);
    return tmp_mbr;
}

Structs::EBR obreporte::getEBR(string path, int pos){
    Structs::EBR tmp_ebr;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&tmp_ebr, sizeof(Structs::EBR), 1, file);
    fclose(file);
    return tmp_ebr;
}

Structs::SB obreporte::getSB(string path, int pos){
    Structs::SB sb;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&sb, sizeof(Structs::SB), 1, file);
    fclose(file);
    return sb;
}

Structs::TI obreporte::getInodo(string path, int pos){
    Structs::TI inodo_t;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&inodo_t, sizeof(Structs::TI), 1, file);
    fclose(file);
    return inodo_t;
}

Structs::BC obreporte::getBC(string path, int pos){
    Structs::BC bc;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bc, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bc;
}

Structs::BAR obreporte::getBAR(string path, int pos){
    Structs::BAR bar;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&bar, sizeof(Structs::BC), 1, file);
    fclose(file);
    return bar;
}

Structs::Journaling obreporte::getJournaling(string path, int pos){
    Structs::Journaling jng;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&jng, sizeof(Structs::Journaling), 1, file);
    fclose(file);
    return jng;
}

list<string> obreporte::separar_carpetas(string path) {
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


void obreporte::exec(){
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return;
    }
    if(validarName()){
        cout<<"\nNombre invalido."<<endl;
        return;
    }
    Structs::partition particion;
    string path_partition = "";
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == this->id){
                path_partition = discos[i].path;
                particion.start = discos[i].particiones[j].start;
                particion.type = discos[i].particiones[j].type;
                break;
            }
        }
    }
    if(path_partition == ""){
        cout<<"\nNo existe una particion con el id : "<<this->id<<endl;
        return;
    }
    if(this->name == "tree"){
        if(this->root < 0){
            cout<<"\nRoot invalido."<<endl;
            return;
        }
        string content;
        content +="\ndigraph rep{";
        content +="\nrankdir=LR";
        content += this->graphInodo(this->root, path_partition, particion.start);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "mbr"){
        string content;
        content +="\ndigraph rep{";
        content +="\nrankdir=TB";
        content += this->graphMBR(path_partition);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "disk"){
        string content;
        content +="\ndigraph rep{";
        content += this->graphDisk(path_partition);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "sb"){
        string content;
        content +="\ndigraph rep{";
        content += this->graphSB(path_partition, particion.start);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "inode"){
        string content;
        content +="\ndigraph rep{";
        content+= "\ninode[shape=none, margin=0, label=<";
        content += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
        content += "\n<TR><TD>Index</TD><TD>Tipo</TD><TD>Nombre</TD></TR>";
        content += this->graphUsedInode(0, "/", path_partition, particion.start);
        content += "\n</TABLE>>];";
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "block"){
        string content;
        content +="\ndigraph rep{";
        content+= "\nrankdir=TB";
        content += this->graphUsedBlockInode(0, path_partition, particion.start);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "bm_inode"){
        string content;
        content +="\ndigraph rep{";
        content += this->graphBMInode(path_partition, particion.start);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "bm_block"){
        string content;
        content +="\ndigraph rep{";
        content += this->graphBMBlock(path_partition, particion.start);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "journaling"){
        Structs::SB sb = this->getSB(path_partition, particion.start);
        if(sb.filesystem_type == 2){
            cout<<"\nSistema de archivos EXT2"<<endl;
            return;
        }
        string content;
        content +="\ndigraph rep{";
        content += this->graphJournaling(path_partition, particion.start);
        content +="\n}";
        this->generarDot(content);
    }else if(this->name == "file"){
        if(this->ruta == ""){
            cout<<"\nRuta del archivo invalida."<<endl;
            return;
        }
        list<string> lista_carpetas;
        list<string>::iterator it;
        lista_carpetas = separar_carpetas(this->ruta);
        Structs::SB sb;
        Structs::TI inodo_actual;
        Structs::BC bc_actual;
        int inodoPadre = 0;
        int inodoAbuelo = 0;
        string file_name;
        for(it = lista_carpetas.begin(); it != lista_carpetas.end(); it++){
            file_name = *it;
            bool carpeta_existente = false;
            sb = this->getSB(path_partition, particion.start);
            inodo_actual = this->getInodo(path_partition, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
            for(int i = 0; i < 15; i++){
                if(inodo_actual.block[i] != -1){
                    //POSICIONAMOS EL BLOQUE ACTUAL PARA PODER ACCEDER A SU CONTENIDO
                    bc_actual = this->getBC(path_partition, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BC)));
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
        sb = this->getSB(path_partition, particion.start);
        inodo_actual = this->getInodo(path_partition, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
        if(inodo_actual.type == '0'){
            cout<<"\nNo existe el archivo : "<<file_name<<endl;
            return;
        }
        string content;
        content +="\ndigraph rep{";
        content += this->graphFile(path_partition, this->ruta, particion.start, inodoPadre, file_name);
        content +="\n}";
        this->generarDot(content);
    }
}

string obreporte::graphMBR(string path){
    Structs::MBR mbr = this->getMBR(path);
    string mbr_name;
    char charPath[path.length() + 1];
    strcpy(charPath, path.c_str());
    for(int i = path.length(); i > 0; i--){
        if(charPath[i]== '/'){
            break;
        }
        mbr_name = charPath[i] + mbr_name;
    }
    string tmp = mbr_name.substr(0, mbr_name.length() - 1);
    string grafico;
    grafico += "\nmbr[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD color='white'>MBR " + tmp + "</TD></TR>";
    grafico += "\n<TR><TD>Nombre</TD><TD>Valor</TD></TR>";
    grafico += "\n<TR><TD>mbr_tamaño</TD><TD>" + to_string(mbr.size) + "</TD></TR>";
    char date[16];
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&mbr.date));
    tmp = date;
    grafico += "\n<TR><TD>mbr_fecha_creacion</TD><TD>" + tmp + "</TD></TR>";
    grafico += "\n<TR><TD>mbr_disk_signature</TD><TD>" + to_string(mbr.signature) + "</TD></TR>";
    if(mbr.fit == 'f'){
        tmp = "F";
    }else if(mbr.fit == 'b'){
        tmp = "B";
    }else{
        tmp = "W";
    }
    grafico += "\n<TR><TD>disk_fit</TD><TD>" + tmp + "</TD></TR>";
    int start_logic;
    for(int i = 0; i < 4; i++){
        if(mbr.particiones[i].status == 'h'){
            grafico += "\n<TR><TD>part_status_" + to_string(i + 1) + "</TD><TD>1</TD></TR>";
            if(mbr.particiones[i].type == 'p'){
                tmp = "P";
            }else{
                tmp = "L";
            }
            grafico += "\n<TR><TD>part_type_" + to_string(i + 1) + "</TD><TD>" + tmp + "</TD></TR>";
            if(mbr.particiones[i].fit == 'f'){
                tmp = "F";
            }else if(mbr.particiones[i].fit == 'b'){
                tmp = "B";
            }else{
                tmp = "W";
            }
            grafico += "\n<TR><TD>part_fit_" + to_string(i + 1) + "</TD><TD>" + tmp + "</TD></TR>";
            grafico += "\n<TR><TD>part_start_" + to_string(i + 1) + "</TD><TD>" + to_string(mbr.particiones[i].start) + "</TD></TR>";
            grafico += "\n<TR><TD>part_size_" + to_string(i + 1) + "</TD><TD>" + to_string(mbr.particiones[i].size) + "</TD></TR>";
            tmp = mbr.particiones[i].name;
            grafico += "\n<TR><TD>part_name_" + to_string(i + 1) + "</TD><TD>" + tmp + "</TD></TR>";
            if(mbr.particiones[i].type == 'e'){
                start_logic = mbr.particiones[i].start;
            }
        }
    }
    grafico += "\n</TABLE>>];";
    if(start_logic != 0){
        bool seguimos = true;
        int i = 0;
        grafico += "\nmbr->ebr1[arrowhead=none color=white]";
        while(seguimos){
            Structs::EBR ebr = this->getEBR(path, start_logic);
            if(ebr.next == -1){
                seguimos = false;
                break;
            }else{
                start_logic = ebr.next;
            }
            grafico += "\nebr" + to_string(i + 1) + "[shape=none, margin=0, label=<";
            grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
            grafico += "\n<TR><TD color='white'>EBR_" + to_string(i + 1) + "</TD></TR>";
            grafico += "\n<TR><TD>Nombre</TD><TD>Valor</TD></TR>";
            grafico += "\n<TR><TD>part_status_" + to_string(i + 1) + "</TD><TD>1</TD></TR>";
            if(ebr.fit == 'f'){
                tmp = "F";
            }else if(ebr.fit == 'b'){
                tmp = "B";
            }else{
                tmp = "W";
            }
            grafico += "\n<TR><TD>part_fit_" + to_string(i + 1) + "</TD><TD>" + tmp + "</TD></TR>";
            grafico += "\n<TR><TD>part_start_" + to_string(i + 1) + "</TD><TD>" + to_string(ebr.start) + "</TD></TR>";
            grafico += "\n<TR><TD>part_size_" + to_string(i + 1) + "</TD><TD>" + to_string(ebr.size) + "</TD></TR>";
            if(ebr.next != -1){
                Structs::EBR tmp = this->getEBR(path, ebr.next);
                if(tmp.next != -1){
                     grafico += "\n<TR><TD>part_next_" + to_string(i + 1) + "</TD><TD>" + to_string(ebr.next) + "</TD></TR>";
                }else{
                    grafico += "\n<TR><TD>part_next_" + to_string(i + 1) + "</TD><TD>-1</TD></TR>";
                }
            }
            tmp = ebr.name;
            grafico += "\n<TR><TD>part_name_" + to_string(i + 1) + "</TD><TD>" + tmp + "</TD></TR>";
            grafico +="\n</TABLE>>];";
            i +=1;
            if(ebr.next != -1){
                Structs::EBR tmp = this->getEBR(path, ebr.next);
                if(tmp.next != -1){
                    grafico += "\nebr" + to_string(i) + "->ebr" + to_string(i + 1) + "[arrowhead=none color=white]";
                }
            }
        }
    }
    return grafico;
}

string obreporte::graphDisk(string path){
    Structs::MBR mbr = this->getMBR(path);
    string grafico;
    grafico += "\ndisk[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD ROWSPAN='6'>MBR</TD>";
    float libre = 0;
    float size = 0;
    int start_logic = 0;
    int ext_size = 0;
    int activas = 0;
    int col = 2;
    for(int i = 0; i < 4; i++){
        if(mbr.particiones[i].type == 'e'){
            bool seguimos = true;
            start_logic = mbr.particiones[i].start;
            while(seguimos){
                Structs::EBR ebr = this->getEBR(path, start_logic);
                if(ebr.next == -1){
                    break;
                }
                if(ebr.next == -1){
                    seguimos = false;
                    break;
                }else{
                    col = col + 2;
                    start_logic = ebr.next;
                }
            }
            break;
        }
    }
    if(mbr.particiones[0].start != sizeof(Structs::MBR)){
        libre = mbr.particiones[0].start;
        grafico += "\n<TD ROWSPAN='6'>Libre<BR/>" + to_string(libre) + "% del disco</TD>";
    }else{
        activas += 1;
        if(mbr.particiones[0].type == 'p'){
            float a =(100 * mbr.particiones[0].size);
            float b = (mbr.size - sizeof(Structs::MBR));
            size = a/b;
            grafico += "\n<TD ROWSPAN='6'>Primaria<BR/>" + to_string(size) + "% del disco</TD>";
        }else{
            grafico += "\n<TD COLSPAN='" + to_string(col) + "'>Extendida</TD>";
            start_logic = mbr.particiones[0].start;
            ext_size = mbr.particiones[0].start +mbr.particiones[0].size;
        }
    }
    for(int i = 1; i < 4; i++){
        if(mbr.particiones[i].status == 'i'){
            libre = mbr.size - (mbr.particiones[i-1].start + mbr.particiones[i-1].size);
            libre = (100 * libre) / (mbr.size);
            grafico += "\n<TD ROWSPAN='6'>Libre<BR/>" + to_string(libre) + "% del disco</TD>";
            break;
        }else{
            activas += 1;
            libre = mbr.particiones[i].start - (mbr.particiones[i-1].start + mbr.particiones[i-1].size);
            if(libre != 0){
                libre = (100 * libre) / (mbr.size- sizeof(Structs::MBR));
                grafico += "\n<TD ROWSPAN='6'>Libre<BR/>" + to_string(libre) + "% del disco</TD>";
            }else{
                if(mbr.particiones[i].type == 'p'){
                    float a =(100 * mbr.particiones[i].size);
                    float b = (mbr.size - sizeof(Structs::MBR));
                    size = a/b;
                    grafico += "\n<TD ROWSPAN='6'>Primaria<BR/>" + to_string(size) + "% del disco</TD>";
                }else{
                    grafico += "\n<TD COLSPAN='" + to_string(col) + "'>Extendida</TD>";
                    start_logic = mbr.particiones[i].start;
                    ext_size = mbr.particiones[i].start + mbr.particiones[i].size;
                }
            }
        }
    }
    if(activas == 4){
       libre = mbr.size - (mbr.particiones[3].start + mbr.particiones[3].size);
       libre = (100 * libre) / mbr.size;
       grafico += "\n<TD ROWSPAN='6'>Libre<BR/>" + to_string(libre) + "% del disco</TD>";
    }
    grafico +="\n</TR>";
    if(start_logic != 0){
        bool seguimos = true;
        grafico +="\n<TR>";
        while(seguimos){
            Structs::EBR ebr = this->getEBR(path, start_logic);
            float a =(100 * ebr.size + sizeof(Structs::EBR));
            float b = mbr.size;
            size = a/b;
            if(ebr.next == -1){
                grafico += "\n<TD ROWSPAN='5'>EBR</TD>";
            }else{
                grafico += "\n<TD ROWSPAN='5'>EBR</TD>";
                Structs::EBR tmp = this->getEBR(path, ebr.next);
                if(tmp.next == -1){
                    grafico += "\n<TD ROWSPAN='5'>Logica<BR/>" + to_string(size) + "% del disco</TD>";
                    libre = ext_size - (ebr.size + ebr.start);
                    if(libre != 0){
                        libre = (100 * libre) / mbr.size;
                        grafico += "\n<TD ROWSPAN='5'>Libre<BR/>" + to_string(libre) + "% del disco</TD>";
                    }
                    break;
                }
            }
            if(ebr.next == -1){
                seguimos = false;
                break;
            }else{
                grafico += "\n<TD ROWSPAN='5'>Logica<BR/>" + to_string(size) + "% del disco</TD>";
                start_logic = ebr.next;
            }
        }
        grafico +="\n</TR>";
    }
    grafico +="\n</TABLE>>];";
    return grafico;
}

string obreporte::graphUsedInode(int root, string name, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + root * sizeof(Structs::TI)));
    Structs::BC bc;
    string grafico;
    string tmp = name;
    if(name != "/"){
        tmp = name.substr(0, name.length() - 1);
    }
    if(inodo.type == '0'){
        grafico += "<TR><TD>" + to_string(root) + "</TD><TD>Folder</TD><TD>" + tmp + "</TD></TR>";
    }else{
        grafico += "<TR><TD>" + to_string(root) + "</TD><TD>Archivo</TD><TD>" + tmp + "</TD></TR>";
    }
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1 && i < 12){
            if(inodo.type == '0'){
                bc = this->getBC(path, (sb.block_start + inodo.block[i] * sizeof(Structs::BC)));
                for(int j = 0; j < 4; j++){
                    tmp = bc.content[j].name;
                    if(bc.content[j].inodo != -1 && tmp != "." && tmp != ".."){
                        string tmp2 = name + tmp + "/";
                        grafico += this->graphUsedInode(bc.content[j].inodo, tmp2, path, start);
                    }
                }
            }
        }else{/*INDIRECTO*/}
    }
    return grafico;
}

string obreporte::graphUsedBlockInode(int root, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + root * sizeof(Structs::TI)));
    string grafico;
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1 && i < 12){
            if(inodo.type == '0'){
                grafico += this->graphUsedBlockBC(inodo.block[i], path, start);
            }else{
                grafico += this->graphUsedBlockBAR(inodo.block[i], path, start);
            }
        }else{/*INDIRECTO*/}
    }
    return grafico;
}

string obreporte::graphUsedBlockBC(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BC bc = this->getBC(path, (sb.block_start + bloque * sizeof(Structs::BC)));
    string grafico;
    grafico += "\nbloque" + to_string(bloque) + "[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD colspan='2'>Bloque Carpeta " + to_string(bloque) + "</TD></TR>";
    grafico += "\n<TR><TD>Name</TD><TD>Inodo</TD></TR>";
    string tmp;
    for(int i = 0; i < 4; i++){
        tmp = bc.content[i].name;
        if(bc.content[i].inodo != -1){
            grafico += "\n<TR><TD>" + tmp + "</TD><TD>" + to_string(bc.content[i].inodo) + "</TD></TR>";
        }else{
            grafico += "\n<TR><TD>--</TD><TD>-1</TD></TR>";
        }

    }
    grafico +="\n</TABLE>>];";
    for(int i = 0; i < 4; i++){
        tmp = bc.content[i].name;
        if(bc.content[i].inodo != -1 && tmp != "." && tmp != ".."){
            grafico += this->graphUsedBlockInode(bc.content[i].inodo, path, start);
        }
    }
    return grafico;
}

string obreporte::graphUsedBlockBAR(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BAR archivo = this->getBAR(path, (sb.block_start + bloque * sizeof(Structs::BAR)));
    string grafico;
    grafico += "\nbloque" + to_string(bloque) + "[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD>Bloque Archivo " + to_string(bloque) +"</TD></TR>";
    string tmp = archivo.content;
    grafico += "\n<TR><TD>" + tmp + "</TD></TR>";
    grafico +="\n</TABLE>>];";
    return grafico;
}

string obreporte::graphBMInode(string path, int start){
    Structs::SB sb = this->getSB(path, start);
    string grafico;
    grafico += "\nbminode[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD>Bit Map Inodos</TD></TR>";
    string tmp;
    char carac;
    int cont = 0;
    for(int i = sb.bm_inode_start; i < sb.bm_block_start; i++){
        FILE * file = NULL;
        file = fopen(path.c_str(), "rb+");
        fseek(file, i, SEEK_SET);
        fread(&carac, 1, 1, file);
        fclose(file);
        if(cont > 32){
            grafico += "\n<TR><TD>" + tmp + "</TD></TR>";
            cont = 0;
            tmp = "";
        }
        tmp += carac;
        cont += 1;
    }
    grafico += "\n</TABLE>>];";
    return grafico;
}

string obreporte::graphBMBlock(string path, int start){
    Structs::SB sb = this->getSB(path, start);
    string grafico;
    grafico += "\nbminode[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD>Bit Map Bloques</TD></TR>";
    string tmp;
    char carac;
    int cont = 0;
    for(int i = sb.bm_block_start; i < sb.inode_start; i++){
        FILE * file = NULL;
        file = fopen(path.c_str(), "rb+");
        fseek(file, i, SEEK_SET);
        fread(&carac, 1, 1, file);
        fclose(file);
        if(cont > 32){
            grafico += "\n<TR><TD>" + tmp + "</TD></TR>";
            cont = 0;
            tmp = "";
        }
        tmp += carac;
        cont += 1;
    }
    grafico += "\n</TABLE>>];";
    return grafico;
}

string obreporte::graphInodo(int root, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo = this->getInodo(path, (sb.inode_start + root * sizeof(Structs::TI)));
    string grafico;
    grafico += "\ninodo" + to_string(root) + "[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD color='blue'>INODO</TD><TD color='blue'>" + to_string(root) + "</TD></TR>";
    grafico += "\n<TR><TD>UID :</TD><TD>" + to_string(inodo.uid) + "</TD></TR>";
    grafico += "\n<TR><TD>GUID :</TD><TD>" + to_string(inodo.gid) + "</TD></TR>";
    grafico += "\n<TR><TD>SIZE :</TD><TD>" + to_string(inodo.size) + "</TD></TR>";
    char date[16];
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&inodo.atime));
    string tmp;
    tmp = date;
    grafico += "\n<TR><TD>LECTURA :</TD><TD>" + tmp + "</TD></TR>";
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&inodo.ctime));
    tmp = date;
    grafico += "\n<TR><TD>CREACION :</TD><TD>" + tmp + "</TD></TR>";
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&inodo.mtime));
    tmp = date;
    grafico += "\n<TR><TD>MODIFICACION :</TD><TD>" + tmp + "</TD></TR>";
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1){
            grafico += "\n<TR><TD>BLOCK " + to_string(i) + " :</TD><TD port='i" + to_string(i) + to_string(root) + "'>" + to_string(inodo.block[i]) + "</TD></TR>";
        }else{
            grafico +="\n<TR><TD>BLOCK "  + to_string(i) + " :</TD><TD>-1</TD></TR>";
        }
    }
    if(inodo.type == '0'){
        tmp = "0";
    }else{
        tmp = "1";
    }
    grafico +="\n<TR><TD>TIPO :</TD><TD>" + tmp + "</TD></TR>";
    grafico +="\n<TR><TD>PERMISOS :</TD><TD>" + to_string(inodo.perm) + "</TD></TR>";
    grafico +="\n</TABLE>>];";
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1){
            grafico +="\ninodo" + to_string(root) + ":i" + to_string(i) + to_string(root) + "->bloque" + to_string(inodo.block[i]);
        }
    }
    for(int i = 0; i < 15; i++){
        if(inodo.block[i] != -1){
            if(inodo.type == '0'){
                grafico += this->graphBC(inodo.block[i], path, start);
            }else{
                grafico += this->graphBAR(inodo.block[i], path, start);
            }
        }
    }
    return grafico;
}

string obreporte::graphBC(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BC bc = this->getBC(path, (sb.block_start + bloque * sizeof(Structs::BC)));
    string grafico;
    grafico += "\nbloque" + to_string(bloque) + "[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD color='green'>BLOCK</TD><TD color='green'>" + to_string(bloque) + "</TD></TR>";
    grafico += "\n<TR><TD>NAME</TD><TD>INODO</TD></TR>";
    string tmp;
    for(int i = 0; i < 4; i++){
        tmp = bc.content[i].name;
        if(tmp == "." || tmp == ".."){
            grafico += "\n<TR><TD>" + tmp + "</TD><TD>" + to_string(bc.content[i].inodo) + "</TD></TR>";
        }else if(bc.content[i].inodo != -1){
            tmp = bc.content[i].name;
            grafico += "\n<TR><TD>" + tmp + "</TD><TD port='c" + to_string(bc.content[i].inodo) + to_string(bloque) + "'>" + to_string(bc.content[i].inodo) + "</TD></TR>";
        }else{
            grafico +="\n<TR><TD> -- </TD><TD>-1</TD></TR>";
        }
    }
    grafico +="\n</TABLE>>];";
    for(int i = 0; i < 4; i++){
        tmp = bc.content[i].name;
        if(bc.content[i].inodo != -1 && tmp != "." && tmp != ".."){
            grafico +="\nbloque" + to_string(bloque) + ":c" + to_string(bc.content[i].inodo) + to_string(bloque) + "->inodo" + to_string(bc.content[i].inodo);
        }
    }
    for(int i = 0; i < 4; i++){
        tmp = bc.content[i].name;
        if(bc.content[i].inodo != -1 && tmp != "." && tmp != ".."){
            grafico += this->graphInodo(bc.content[i].inodo, path, start);
        }
    }
    return grafico;
}

string obreporte::graphBAR(int bloque, string path, int start){
    Structs::SB sb = this->getSB(path, start);
    Structs::BAR archivo = this->getBAR(path, (sb.block_start + bloque * sizeof(Structs::BAR)));
    string grafico;
    grafico += "\nbloque" + to_string(bloque) + "[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD color='yellow'>BLOCK</TD><TD color='yellow'>" + to_string(bloque) + "</TD></TR>";
    string tmp = archivo.content;
    grafico += "\n<TR><TD>" + tmp +  "</TD><TD></TD></TR>";
    grafico +="\n</TABLE>>];";
    return grafico;
}

string obreporte::graphSB(string path, int start){
    Structs::SB sb = this->getSB(path, start);
    string grafico;
    grafico += "\nmbr[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD>Nombre</TD><TD>Valor</TD></TR>";
    grafico += "\n<TR><TD>s_inodes_count</TD><TD>" + to_string(sb.inodes_count) + "</TD></TR>";
    grafico += "\n<TR><TD>s_blocks_count</TD><TD>" + to_string(sb.blocks_count) + "</TD></TR>";
    grafico += "\n<TR><TD>s_free_blocks_count</TD><TD>" + to_string(sb.free_blocks_count) + "</TD></TR>";
    grafico += "\n<TR><TD>s_free_inodes_count</TD><TD>" + to_string(sb.free_inodes_count) + "</TD></TR>";
    string tmp;
    char date[16];
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&sb.mtime));
    tmp = date;
    sb.umtime = time(0);
    grafico += "\n<TR><TD>s_mtime</TD><TD>" + tmp + "</TD></TR>";
    strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&sb.umtime));
    tmp = date;
    grafico += "\n<TR><TD>s_umtime</TD><TD>" + tmp + "</TD></TR>";
    grafico += "\n<TR><TD>s_mnt_count</TD><TD>" + to_string(sb.mnt_count) + "</TD></TR>";
    grafico += "\n<TR><TD>s_magic</TD><TD>0xEF53</TD></TR>";
    grafico += "\n<TR><TD>s_inode_size</TD><TD>" + to_string(sb.inode_size) + "</TD></TR>";
    grafico += "\n<TR><TD>s_block_size</TD><TD>" + to_string(sb.block_size) + "</TD></TR>";
    grafico += "\n<TR><TD>s_first_ino</TD><TD>" + to_string(sb.firts_ino) + "</TD></TR>";
    grafico += "\n<TR><TD>s_first_blo</TD><TD>" + to_string(sb.first_blo) + "</TD></TR>";
    grafico += "\n<TR><TD>s_bm_inode_start</TD><TD>" + to_string(sb.bm_inode_start) + "</TD></TR>";
    grafico += "\n<TR><TD>s_bm_block_start</TD><TD>" + to_string(sb.bm_block_start) + "</TD></TR>";
    grafico += "\n<TR><TD>s_inode_start</TD><TD>" + to_string(sb.inode_start) + "</TD></TR>";
    grafico += "\n<TR><TD>s_block_start</TD><TD>" + to_string(sb.block_start) + "</TD></TR>";
    grafico +="\n</TABLE>>];";
    return grafico;
}

string obreporte::graphJournaling(string path, int start){
    string grafico;
    grafico += "\njng[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD colspan='6'>Journaling</TD></TR>";
    grafico += "\n<TR><TD>#</TD><TD>Operacion</TD><TD>Tipo</TD><TD>Ruta</TD><TD>Fecha</TD><TD>Contenido</TD></TR>";
    bool seguimos = true;
    int next = start + sizeof(Structs::SB);
    int i = 1;
    while(seguimos){
        Structs::Journaling jng = getJournaling(path, next);
        string op = jng.operacion;
        string tipo;
        if(jng.tipo == '0'){
            tipo = "0";
        }else{
            tipo = "1";
        }
        string name = jng.path;
        string cont = jng.contenido;
        char date[16];
        strftime(date, 20, "%d/%m/%Y %H:%M", localtime(&jng.date));
        string dates = date;
        grafico += "\n<TR><TD>" + to_string(i) + "</TD><TD>" + op + "</TD><TD>" + tipo + "</TD><TD>" + name + "</TD><TD>" + dates + "</TD><TD>" + cont + "</TD></TR>";
        i += 1;
        if(jng.next == -1){
            seguimos = false;
        }else{
            next = jng.next;
        }
    }
    grafico += "</TABLE>>];";
    return grafico;
}

string obreporte::graphFile(string path, string ruta, int start, int inodoPadre, string file_name){
    string grafico;
    grafico += "\nfile[shape=none, margin=0, label=<";
    grafico += "\n<TABLE BORDER='3' CELLBORDER='2' CELLSPACING='2'>";
    grafico += "\n<TR><TD>Nombre : </TD><TD>" + file_name + "</TD></TR>";
    grafico += "\n<TR><TD>Ruta : </TD><TD>" + ruta + "</TD></TR>";
    Structs::SB sb = this->getSB(path, start);
    Structs::TI inodo_actual = this->getInodo(path, (sb.inode_start + inodoPadre * sizeof(Structs::TI)));
    Structs::BAR archivo;
    string content;
    for(int i = 0; i < 15; i++){
        if(inodo_actual.block[i] != -1 && i < 12){
            archivo = this->getBAR(path, (sb.block_start + inodo_actual.block[i] * sizeof(Structs::BAR)));
            string tmp = archivo.content;
            tmp = tmp.substr(0, tmp.length() - 1);
            content += tmp;
        }else{/*INDIRECTOS*/}
    }
    grafico += "\n<TR><TD>Contenido :</TD><TD>" + content + "</TD></TR>";
    grafico += "\n</TABLE>>];";
    cout<<grafico<<endl;
    return grafico;
}

void obreporte::generarDot(string content) {
    string path_carpeta = this->path.substr(0, this->path.length() - 4) + ".dot";
    FILE *searchFile = fopen(path_carpeta.c_str(), "wb+");
    cout << path_carpeta << endl;
    cin;
    if (searchFile == NULL) {
        string create_command = "mkdir -p \"" + this->path + "\"";
        system(create_command.c_str());
        create_command = "rmdir \'" + this->path + "\'";
        system(create_command.c_str());
    }
    ofstream graphFile;
    graphFile.open(path_carpeta);
    graphFile << content;
    graphFile.close();
    string filePath;
    string extension = this->getExt();
    string salida = this->path.substr(0, this->path.length() - 3) + extension;
    if (extension == "png") {
        filePath = "dot -Tpng \"" + path_carpeta + "\" -o \"" + salida + "\"";
    } else if (extension == "jpg") {
        filePath = "dot -Tjpg \"" + path_carpeta + "\" -o \"" + salida + "\"";
    } else if (extension == "pdf") {
        filePath = "dot -Tpdf \"" + path_carpeta + "\" -o \"" + salida + "\"";
    }
    system(filePath.c_str());
    cout << "Reporte Generado con éxito." << endl;
}
