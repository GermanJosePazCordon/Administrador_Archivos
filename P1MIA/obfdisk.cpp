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
    if(this->unit == "k"){
        this->size = this->size * 1024;
    }else if(this->unit == "m"){
        this->size = this->size * 1024 * 1024;
    }
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
    if(fit == "b"){
        return 'b';
    }else if(fit == "k"){
        return 'k';
    }else{
        return 'm';
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
        this->mbr.particiones[pos].status = 'i';
        this->mbr.particiones[pos].size = 0;
        this->mbr.particiones[pos].fit = this->mbr.fit;
        this->mbr.particiones[pos].start = this->mbr.size;
        this->mbr.particiones[pos].type = 'x';
        strcpy(this->mbr.particiones[pos].name,"");
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
    for(int i = 0; i < 4; i++){
        if(this->mbr.particiones[i].name == this->name){
            name = true;
        }
    }
    if(name){
        cout<<"\nYa existe una particion con el nombre : "<<this->name<<endl;
        return;
    }
    int activas = 0;
    for(int i = 0; i < 4; i++){
        if(this->mbr.particiones[i].status == 'h'){
            activas += 1;
        }
    }
    if(activas == 0){
        caso1(); // CASO DONDE NO HAY NINGUNA PARTICION ACTIVA
        return;
    }else{
        bubbleSort();
        int tmp_space;
        if(this->mbr.particiones[0].start == sizeof(Structs::MBR)){//CASO DONDE LA PRIMER PARTICION ESTA JUNTO CON EL MBR, ES DECIR NO HAY ESPACIO LIBRE
            for(int i = 1; i < 4; i++){
                //VERIFICA SI LA PARTICION ESTA JUNTO A LA ANTERIOR, ES DECIR SIN ESPACIOS LIBRES ENTRE ELLAS
                if(this->mbr.particiones[i].status == 'i'){
                    //SI LA PARTICION ES NULA SIGNIFICA QUE NO HAY MAS PARTICIONES DESPUES DE ESTA POR LO QUE AGREGA LA NUEVA PARTICION SIN ESPACIO LIBRE
                    tmp_space = this->mbr.size - ( this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size );
                    if(this->size <= tmp_space){
                        strcpy(this->mbr.particiones[i].name, this->name.c_str());
                        this->mbr.particiones[i].fit = getFit(this->fit);
                        this->mbr.particiones[i].start = (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                        this->mbr.particiones[i].size = this->size;
                        this->mbr.particiones[i].type = getType(this->type);
                        this->mbr.particiones[i].status = 'h';
                        saveMBR(this->mbr);
                        return;
                    }else{
                        cout<<"\nEspacio insuficiente"<<endl;
                        cout<<"\nNo pudo crearse la particion"<<endl;
                        return;
                    }
                }
                //SI LA PARTICION ESTA ACTIVA HAY QUE VERIFICAR SI HAY ESPACIO LIBRE CON LA ANTERIOR
            }
        }
        //CASO DONDE EXISTE ESPACIO LIBRE ENTRE EL MBR Y LA PRIMER PARTICION
        tmp_space = this->mbr.particiones[0].start - sizeof(Structs::MBR);
        if(this->fit == "ff"){
            //FIRST FIT, SOLAMENTE VERIFICAR SI ENTRA EN EL ESPACIO LIBRE, EN CASO CONTRARIO BUSCAR OTRO LUGAR
            if(this->size <= tmp_space){
                strcpy(this->mbr.particiones[3].name, this->name.c_str());
                this->mbr.particiones[3].fit = getFit(this->fit);
                this->mbr.particiones[3].start = sizeof(Structs::MBR);
                this->mbr.particiones[3].size = this->size;
                this->mbr.particiones[3].type = getType(this->type);
                this->mbr.particiones[3].status = 'h';
                bubbleSort();
                saveMBR(this->mbr);
                return;
            }else{
                for(int i = 0; i < 4; i++){
                    //CUANDO ENCONTRAMOS LA PARTICION INHABILITADA UTILIZAMOS LA ANTERIOR PARA CALCULAR EL ESPACIO DISPONIBLE
                    if(this->mbr.particiones[i].status == 'i'){
                        tmp_space = this->mbr.size - (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                        cout<<"\ntmp_space = "<<this->mbr.size<<" - ("<<this->mbr.particiones[i-1].start<<" + "<<this->mbr.particiones[i-1].size<<endl;
                        if(this->size <= tmp_space){
                            strcpy(this->mbr.particiones[3].name, this->name.c_str());
                            this->mbr.particiones[3].fit = getFit(this->fit);
                            this->mbr.particiones[3].start = (this->mbr.particiones[i-1].start + this->mbr.particiones[i-1].size);
                            this->mbr.particiones[3].size = this->size;
                            this->mbr.particiones[3].type = getType(this->type);
                            this->mbr.particiones[3].status = 'h';
                            bubbleSort();
                            saveMBR(this->mbr);
                            return;
                        }
                    }else{
                        if(i != 2){
                            tmp_space = this->mbr.particiones[i+1].start - this->mbr.particiones[i].start;
                            if(this->size <= tmp_space){
                                strcpy(this->mbr.particiones[3].name, this->name.c_str());
                                this->mbr.particiones[3].fit = getFit(this->fit);
                                this->mbr.particiones[3].start = (this->mbr.particiones[i].start + this->mbr.particiones[i].size);
                                this->mbr.particiones[3].size = this->size;
                                this->mbr.particiones[3].type = getType(this->type);
                                this->mbr.particiones[3].status = 'h';
                                bubbleSort();
                                saveMBR(this->mbr);
                                return;
                            }
                        }
                    }
                }
                cout<<"\nEspacio insuficiente"<<endl;
                cout<<"\nNo pudo crearse la particion"<<endl;
                return;
            }
        }
    }
    return;
}

void obfdisk::caso1(){
    int sizeDisponible = this->mbr.size - sizeof(this->mbr);
    if(this->size > sizeDisponible){
        cout<<"\nEspacio insuficiente"<<endl;
        return;
    }
    strcpy(this->mbr.particiones[0].name, this->name.c_str());
    this->mbr.particiones[0].fit = getFit(this->fit);
    this->mbr.particiones[0].start = sizeof(Structs::MBR);
    this->mbr.particiones[0].size = this->size;
    this->mbr.particiones[0].type = getType(this->type);
    this->mbr.particiones[0].status = 'h';
    saveMBR(this->mbr);
}
