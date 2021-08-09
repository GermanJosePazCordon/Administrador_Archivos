#include "obfdisk.h"
#include "iostream"
#include "structs.h"

using namespace std;

obfdisk::obfdisk()
{

}

//--------------------------SETERS-----------------------------------

void obfdisk::setSize(int size){
    this->size = size;
}

void obfdisk::setAdd(int add){
    this->add = add;
}

void obfdisk::setFit(string fit){
    string data = fit;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    fit = data;
    this->fit = fit;
}

void obfdisk::setUnit(string unit){
    string data = unit;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    unit = data;
    this->unit = unit;
}

void obfdisk::setPath(string path){
    if(path[0] == '"'){
        this->path = path.substr(1, path.size()-1);
        this->path = this->path.substr(0, this->path.size()-1);
    }else{
        this->path = path;
    }
}

void obfdisk::setType(string type){
    string data = type;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    type = data;
    this->type = type;
}

void obfdisk::setDelet(string delet){
    string data = delet;
    std::transform(data.begin(), data.end(), data.begin(),
        [](unsigned char c){ return std::tolower(c); });
    delet = data;
    this->delet = delet;
}

void obfdisk::setName(string name){
    if(name[0] == '"'){
        this->name = name.substr(1, path.size()-1);
        this->name = this->name.substr(0, this->name.size()-1);
    }else{
        string data = name;
        std::transform(data.begin(), data.end(), data.begin(),
            [](unsigned char c){ return std::tolower(c); });
        name = data;
        //this->delet = delet;
        this->name = name;
    }
}

bool obfdisk::validarParametros(){
    if(this->path == ""){
        cout<<"\nRuta vacia."<<endl;
        return true;
    }
    if(this->name == ""){
        cout<<"\nNombre vacio."<<endl;
        return true;
    }
    if(this->fit != ""){
        if(this->fit != "bf" && this->fit != "ff" && this->fit != "wf"){
            cout<<"\nFit invalido."<<endl;
            return true;
        }
    }
    if(this->unit != ""){
        if(this->unit != "k" && this->unit != "m" && this->unit != "b"){
            cout<<"\nUnidad invalida."<<endl;
            return true;
        }
    }
    if(this->unit == "k"){
        this->size = this->size * 1024;
    }else if(this->unit == "m"){
        this->size = this->size * 1024 * 1024;
    }
    if(this->type != ""){
        if(this->type != "p" && this->type != "e" && this->type != "l"){
            cout<<"\nTipo invalido."<<endl;
            return true;
        }
    }
    if(this->delet != ""){
        if(this->delet != "full" && this->delet != "fast"){
            cout<<"\nTipo invalido."<<endl;
            return true;
        }
    }
    if(this->delet == "" || this->add != 0){
        if(this->size <= 0){
            cout<<"\nTamaño incorrecto de disco."<<endl;
            return true;
        }
    }
    return false;
}

bool obfdisk::validarTipo(){
    int primaria = 0;
    int extendida = 0;
    for(int i = 0; i < 4; i++){
        if(this->mbr.particiones[i].type == 'p'){
            primaria += 1;
        }else if(this->mbr.particiones[i].type == 'e'){
            extendida +=1;
        }
    }
    int tmp = primaria + extendida;
    if(tmp == 4 && this->type != "l"){
        cout<<"\nNumero maximo de particiones creadas"<<endl;
        return true;
    }
    if(this->type == "e" && extendida == 1){
        cout<<"\nYa existe una particion extendidae"<<endl;
        return true;
    }
    if(this->type == "l" && extendida != 1){
        cout<<"\nNo existe particion extendida"<<endl;
        return true;
    }
    return false;
}

bool obfdisk::getMBR(string path){
    Structs::MBR tmp_mbr;
    FILE * file = NULL;
    file = fopen(path.c_str(), "r");
    if (file != NULL){
        fread(&tmp_mbr, sizeof(Structs::MBR), 1, file);
        this->mbr = tmp_mbr;
        fclose(file);
        return false;
    }else{
        cout<<"\nEl disco no existe."<<endl;
        return true;
    }
}

void obfdisk::saveMBR(Structs::MBR mbr){
    char charPath[this->path.size() + 1];
    strcpy(charPath, this->path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "wb");
    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(Structs::MBR), 1, file);
    fclose(file);
}

void obfdisk::saveEBR(Structs::EBR){}

void obfdisk::newPartition(int pos, char status, char type, char fit, int start, int size, string name){
    this->mbr.particiones[pos].status = status;
    this->mbr.particiones[pos].type = type;
    this->mbr.particiones[pos].fit = fit;
    this->mbr.particiones[pos].size = 0;
    this->mbr.particiones[pos].start = start;
    this->mbr.particiones[pos].size = size;
    strcpy(this->mbr.particiones[pos].name, name.c_str());
}

char obfdisk::getFit(string fit){
    if(fit == "bf"){
        return 'b';
    }else if(fit == "ff"){
        return 'f';
    }else{
        return 'w';
    }
}

char obfdisk::getType(string type){
    if(type == "p"){
        return 'p';
    }else if(type == "e"){
        return 'e';
    }else{
        return 'l';
    }
}

void obfdisk::exec(){
    if(validarParametros()){
        cout<<"\nNo se pudo crear la particion"<<endl;
    }else{
        if(getMBR(this->path)){
            cout<<"\nNo se pudo crear la particion"<<endl;
            return;
        }
        init();
        for(int i = 0; i < 4; i++){
            cout<<"---------------- PARTICION "<<i<<" ----------------"<<endl;
            cout<<"name : "<<this->mbr.particiones[i].name<<endl;
            cout<<"size : "<<this->mbr.particiones[i].size<<endl;
            cout<<"type : "<<this->mbr.particiones[i].type<<endl;
            cout<<"fit : "<<this->mbr.particiones[i].fit<<endl;
            cout<<"start : "<<this->mbr.particiones[i].start<<endl;
            cout<<"status : "<<this->mbr.particiones[i].status<<endl;
        }
    }
}

void obfdisk::init(){
    if(validarTipo()){
        cout<<"\nNo pudo crearse la particion"<<endl;
        return;
    }
    if(this->delet != ""){
        deletePartition();
    }else{
        createPartition();
    }

}

void obfdisk::deletePartition(){
    int pos = 0;
    for(int i = 0; i < 4; i++){
        if(this->name == this->mbr.particiones[i].name){
            pos = i;
        }
    }
    cout<<"\nDesea eliminarlo [s/n]"<<endl;
    char op;
    cin >> op;
    if(op == 's'){
        newPartition(pos, 'i', 'x', this->mbr.fit, this->mbr.size, 0, "");
        saveMBR(this->mbr);
        return;
    }else{
        return;
    }
}

void obfdisk::bubbleSort(){
    Structs::partition aux_part;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if ((this->mbr.particiones[j].start > 0) && (this->mbr.particiones[j + 1].start > 0)) {
                if (this->mbr.particiones[j].start > this->mbr.particiones[j + 1].start) {
                    aux_part = this->mbr.particiones[j];
                    this->mbr.particiones[j] = this->mbr.particiones[j + 1];
                    this->mbr.particiones[j + 1] = aux_part;
                }
            }
        }
    }
}

void obfdisk::createPartition(){
    bool name = false;
    int activas = 0;
    for(int i = 0; i < 4; i++){
        //VALIDANDO SI EL NOMBRE YA EXISTE
        if(this->mbr.particiones[i].name == this->name){
            name = true;
        }
         //REVISANDO SI HAY POR LO MENOS UNA PARTICION ACTIVA
        if(this->mbr.particiones[i].status == 'h'){
            activas += 1;
        }
    }
    if(name){
        cout<<"\nYa existe una particion con el nombre : "<<this->name<<endl;
        return;
    }
    /*if(this->type == 'l'){

    }*/
    if(activas == 0){
        // CASO DONDE NO HAY NINGUNA PARTICION ACTIVA
        int sizeDisponible = this->mbr.size - sizeof(this->mbr);
        if(this->size > sizeDisponible){
            cout<<"\nEspacio insuficiente"<<endl;
            return;
        }
        newPartition(0, 'h', getType(this->type), getFit(this->fit), sizeof(Structs::MBR), this->size, this->name);
        saveMBR(this->mbr);
        if(this->type == 'e'){
            firstEBR('i', getFit(this->fit), sizeof(Structs::MBR), this->size, this->name, -1);
        }
        return;
    }else{
        bubbleSort();
        int tmp_space;
        int ant_space = 0;
        if(this->mbr.particiones[0].start == sizeof(Structs::MBR)){//CASO DONDE LA PRIMER PARTICION ESTA JUNTO CON EL MBR, ES DECIR NO HAY ESPACIO LIBRE
            for(int i = 1; i < 4; i++){
                //VERIFICA SI LA PARTICION ESTA JUNTO A LA ANTERIOR, ES DECIR SIN ESPACIOS LIBRES ENTRE ELLAS
                if(this->mbr.particiones[i].status == 'i'){
                    //SI LA PARTICION ES NULA SIGNIFICA QUE NO HAY MAS PARTICIONES DESPUES DE ESTA POR LO QUE AGREGA LA NUEVA PARTICION SIN ESPACIO LIBRE
                    tmp_space = this->mbr.size - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                    if(this->size <= tmp_space){
                        int start = (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                        cout<<"\nstart : "<<start<<endl;
                        newPartition(i, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                        saveMBR(this->mbr);
                        if(this->type == 'e'){
                            firstEBR('i', getFit(this->fit), start, this->size, this->name, -1);
                        }
                        return;
                    }else{
                        cout<<"\nEspacio insuficiente"<<endl;
                        cout<<"\nNo pudo crearse la particion"<<endl;
                        return;
                    }
                }
                //SI LA PARTICION ESTA ACTIVA HAY QUE VERIFICAR SI HAY ESPACIO LIBRE CON LA ANTERIOR, 0 = NO HAY ESPACIO LIBRE,
                tmp_space = this->mbr.particiones[i].start - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                if(tmp_space != 0){
                    if(this->fit == "ff"){
                        if(this->size <= tmp_space){
                            int start = (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                            newPartition(3, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                            bubbleSort();
                            saveMBR(this->mbr);
                            if(this->type == 'e'){
                                firstEBR('i', getFit(this->fit), start, this->size, this->name, -1);
                            }
                            return;
                        }
                    }else{
                        if(this->size <= tmp_space){
                            //SI EL ESPACIO ANTERIOR ES CERO SIGNIFICA QUE ES EL PRIMER ESPACIO EN GUARDASR
                            if(ant_space == 0){
                                ant_space = tmp_space;
                                break;
                            }else{
                                //SI EL ESPACIO ANTERIOR ES MENOR QUE EL TEMPORAL SE TIENE QUE SUSTITUIR POR SER WORST FIT, Y AL CONTRARIO PARA EL MEJRO FIT
                                if(this->fit == "wf"){
                                    if(ant_space < tmp_space){
                                        ant_space = tmp_space;
                                    }
                                }else{
                                    if(ant_space > tmp_space){
                                        ant_space = tmp_space;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //UNA VEZ SE TIENE EL ESPACIO DONDE CREAR LA PARTICION SE RECORREN LOS ESPACIOS DE NUEVO PARA ENCONTRAR SU POSICION Y CREAR LA PARTICION ALLI
            for(int i = 1; i < 4; i++){
                tmp_space = this->mbr.particiones[i].start - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                if(tmp_space == ant_space){
                    int start = this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size;
                    newPartition(3, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                    bubbleSort();
                    saveMBR(this->mbr);
                    if(this->type == 'e'){
                        firstEBR('i', getFit(this->fit), start, this->size, this->name, -1);
                    }
                    ant_space = 0;
                    return;
                }
            }
        }
        //CASO DONDE EXISTE ESPACIO LIBRE ENTRE EL MBR Y LA PRIMER PARTICION
        tmp_space = this->mbr.particiones[0].start - sizeof(Structs::MBR);
        if(this->fit == "ff"){
            //FIRST FIT, SOLAMENTE VERIFICAR SI ENTRA EN EL ESPACIO LIBRE, EN CASO CONTRARIO BUSCAR OTRO LUGAR
            if(this->size <= tmp_space){
                newPartition(3, 'h', getType(this->type), getFit(this->fit), sizeof(Structs::MBR), this->size, this->name);
                bubbleSort();
                saveMBR(this->mbr);
                return;
            }else{
                for(int i = 0; i < 4; i++){
                    //CUANDO ENCONTRAMOS LA PARTICION INHABILITADA UTILIZAMOS LA ANTERIOR PARA CALCULAR EL ESPACIO DISPONIBLE
                    if(this->mbr.particiones[i].status == 'i'){
                        tmp_space = this->mbr.size - (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                        if(this->size <= tmp_space){
                            int start = (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                            newPartition(3, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                            bubbleSort();
                            saveMBR(this->mbr);
                            if(this->type == 'e'){
                                firstEBR('i', getFit(this->fit), start, this->size, this->name, -1);
                            }
                            return;
                        }
                    }else{
                        if(i != 2){
                            tmp_space = this->mbr.particiones[i+1].start - this->mbr.particiones[i].start;
                            if(this->size <= tmp_space){
                                int start = (this->mbr.particiones[i].start + this->mbr.particiones[i].size);
                                newPartition(3, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                                bubbleSort();
                                saveMBR(this->mbr);
                                if(this->type == 'e'){
                                    firstEBR('i', getFit(this->fit), start, this->size, this->name, -1);
                                }
                                return;
                            }
                        }
                    }
                }
                cout<<"\nEspacio insuficiente"<<endl;
                cout<<"\nNo pudo crearse la particion"<<endl;
                return;
            }
        }else{
            if(this->size <= tmp_space ){
                ant_space = tmp_space;
            }else{
                ant_space = 0;
            }
            for(int i = 1; i < 4; i++){
                if(this->mbr.particiones[i].status == 'i'){
                    tmp_space = this->mbr.size - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                    if(this->size <= tmp_space){
                        //SI EL ESPACIO ANTERIOR ES CERO SIGNIFICA QUE ES EL PRIMER ESPACIO EN GUARDASR
                        if(ant_space == 0){
                            ant_space = tmp_space;
                            break;
                        }else{
                            //SI EL ESPACIO ANTERIOR ES MENOR QUE EL TEMPORAL SE TIENE QUE SUSTITUIR POR SER WORST FIT
                            if(this->fit == "wf"){
                                if(ant_space < tmp_space){
                                    ant_space = tmp_space;
                                }
                            }else{
                                if(ant_space > tmp_space){
                                    ant_space = tmp_space;
                                }
                            }
                        }
                    }
                }else{
                    tmp_space = this->mbr.particiones[i].start - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                    if(tmp_space != 0){
                        if(this->size <= tmp_space){
                            //SI EL ESPACIO ANTERIOR ES CERO SIGNIFICA QUE ES EL PRIMER ESPACIO EN GUARDASR
                            if(ant_space == 0){
                                ant_space = tmp_space;
                                break;
                            }else{
                                //SI EL ESPACIO ANTERIOR ES MENOR QUE EL TEMPORAL SE TIENE QUE SUSTITUIR POR SER WORST FIT
                                if(this->fit == "wf"){
                                    if(ant_space < tmp_space){
                                        ant_space = tmp_space;
                                    }
                                }else{
                                    if(ant_space > tmp_space){
                                        ant_space = tmp_space;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if(ant_space == 0){
                cout<<"\nEspacio insuficiente"<<endl;
                cout<<"\nNo pudo crearse la particion"<<endl;
                return;
            }
            tmp_space = this->mbr.particiones[0].start - sizeof(Structs::MBR);
            if(ant_space == tmp_space){
                newPartition(3, 'h', getType(this->type), getFit(this->fit), sizeof(Structs::MBR), this->size, this->name);
                bubbleSort();
                saveMBR(this->mbr);
                if(this->type == 'e'){
                    firstEBR('i', getFit(this->fit), sizeof(Structs::MBR), this->size, this->name, -1);
                }
                ant_space = 0;
                return;
            }else{
                for(int i = 1; i < 4; i++){
                    tmp_space = this->mbr.particiones[i].start - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                    if(tmp_space == ant_space){
                        int start = this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size;
                        newPartition(3, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                        bubbleSort();
                        saveMBR(this->mbr);
                        if(this->type == 'e'){
                            firstEBR('i', getFit(this->fit), start, this->size, this->name, -1);
                        }
                        ant_space = 0;
                        return;
                    }
                }
            }
        }
    }
    return;
}

void obfdisk::firstEBR(char status, char fit, int start, int size, string name, int next){
    Structs::EBR ebr;
    ebr.status = status;
    ebr.fit = fit;
    ebr.start = start;
    ebr.size = size;
    strcpy(ebr.name, name);
    ebr.next = next;
    saveEBR(ebr);
}
