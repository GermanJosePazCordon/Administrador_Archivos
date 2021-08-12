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
        this->add = this->add * 1024;
    }else if(this->unit == "m"){
        this->size = this->size * 1024 * 1024;
        this->add = this->add * 1024 * 1024;
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
    if(this->delet == "" && this->add == 0){
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
    if(delet != "" || add != 0){
        return false;
    }
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

//--------------------------GETERS-----------------------------------

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

Structs::EBR obfdisk::getEBR(string path, int pos){
    Structs::EBR tmp_ebr;
    FILE * file = NULL;
    file = fopen(path.c_str(), "rb+");
    fseek(file, pos, SEEK_SET);
    fread(&tmp_ebr, sizeof(Structs::EBR), 1, file);
    fclose(file);
    return tmp_ebr;
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

//--------------------------SAVE-------------------------------------

void obfdisk::saveMBR(Structs::MBR mbr){
    char charPath[this->path.size() + 1];
    strcpy(charPath, this->path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, 0, SEEK_SET);
    fwrite(&mbr, sizeof(Structs::MBR), 1, file);
    fclose(file);
}

void obfdisk::saveEBR(Structs::EBR ebr, int pos){
    char charPath[this->path.size() + 1];
    strcpy(charPath, this->path.c_str());
    FILE *file = NULL;
    file = fopen(charPath, "rb+");
    fseek(file, pos, SEEK_SET);
    fwrite(&ebr, sizeof(Structs::EBR), 1, file);
    fclose(file);
}

void obfdisk::modifyEBR(Structs::EBR ebr){
    ebr.fit = getFit(this->fit);
    strcpy(ebr.name, this->name.c_str());
    ebr.size = this->size;
    ebr.start = ebr.start + sizeof(Structs::EBR);
    ebr.status = 'h';
    ebr.next = ebr.start + ebr.size;
    saveEBR(ebr, ebr.start - sizeof(Structs::EBR));
    newEBR('i', 'w', ebr.next, 0, "", -1, ebr.next);
}

//--------------------------NEW-----------------------------------

void obfdisk::newPartition(int pos, char status, char type, char fit, int start, int size, string name){
    this->mbr.particiones[pos].status = status;
    this->mbr.particiones[pos].type = type;
    this->mbr.particiones[pos].fit = fit;
    this->mbr.particiones[pos].size = 0;
    this->mbr.particiones[pos].start = start;
    this->mbr.particiones[pos].size = size;
    strcpy(this->mbr.particiones[pos].name, name.c_str());
}

void obfdisk::newEBR(char status, char fit, int start, int size, string name, int next, int pos){
    Structs::EBR ebr;
    ebr.status = status;
    ebr.fit = fit;
    ebr.start = start;
    ebr.size = size;
    strcpy(ebr.name, name.c_str());
    ebr.next = next;
    saveEBR(ebr, pos);
}

//--------------------------MAIN-----------------------------------

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

void obfdisk::exec(){
    if(validarParametros()){
        cout<<"\nNo se pudo crear la particion"<<endl;
    }else{
        if(getMBR(this->path)){
            cout<<"\nNo se pudo crear la particion"<<endl;
            return;
        }
        init();
        int inicio = 0;
        for(int i = 0; i < 4; i++){
            cout<<"---------------- PARTICION "<<i<<" ----------------"<<endl;
            cout<<"name : "<<this->mbr.particiones[i].name<<endl;
            cout<<"size : "<<this->mbr.particiones[i].size<<endl;
            cout<<"type : "<<this->mbr.particiones[i].type<<endl;
            cout<<"fit : "<<this->mbr.particiones[i].fit<<endl;
            cout<<"start : "<<this->mbr.particiones[i].start<<endl;
            cout<<"status : "<<this->mbr.particiones[i].status<<endl;
            if(this->mbr.particiones[i].type == 'e'){
                inicio = this->mbr.particiones[i].start;
            }
        }
        if(inicio != 0){
            bool seguimos = true;
            int i = 0;
            while(seguimos){
                Structs::EBR ebr = getEBR(this->path, inicio);
                cout<<"---------------- EBR "<<i<<" ----------------"<<endl;
                cout<<"name : "<<ebr.name<<endl;
                cout<<"size : "<<ebr.size<<endl;
                cout<<"fit : "<<ebr.fit<<endl;
                cout<<"start : "<<ebr.start<<endl;
                cout<<"status : "<<ebr.status<<endl;
                cout<<"next : "<<ebr.next<<endl;
                if(ebr.next == -1){
                    seguimos = false;
                }else{
                    inicio = ebr.next;
                }
                i +=1;
            }
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
        return;
    }if(this->add != 0){
        addPartition();
        return;
    }else{
        createPartition();
        return;
    }

}

void obfdisk::deletePartition(){
    Structs::EBR previous_ebr;
    bool seguimos = true;
    bool logic = false;
    int pos = -1;
    for(int i = 0; i < 4; i++){
        if(this->name == this->mbr.particiones[i].name){
            pos = i;
        }
        if(this->mbr.particiones[i].type == 'e'){
            previous_ebr = getEBR(this->path, this->mbr.particiones[i].start);
        }
    }
    while(seguimos){
        if(previous_ebr.name == this->name){
            logic = true;
            break;
        }
        if(previous_ebr.next == -1){
            seguimos = false;
        }else{
            previous_ebr = getEBR(this->path, previous_ebr.next);
        }
    }
    if(logic){
        deleteLogic();
        return;
    }
    if(pos == -1){
        cout<<"\nNo existe la particion : "<<this->name<<endl;
        return;
    }
    cout<<"\nDesea eliminarlo [s/n]"<<endl;
    char op;
    cin >> op;
    if(op == 's'){
        if(this->delet == "fast"){
            cout<<"\nLa particion : '"<<this->name<<"' ha sido eliminada"<<endl;
            newPartition(pos, 'i', 'x', this->mbr.fit, this->mbr.size, 0, "");
            saveMBR(this->mbr);
            return;
        }else{
            char carac = '\0';
            char charPath[this->path.size() + 1];
            strcpy(charPath, this->path.c_str());
            FILE *file = NULL;
            file = fopen(charPath, "rb+");
            for(int i = this->mbr.particiones[pos].start; i < (this->mbr.particiones[pos].start + this->mbr.particiones[pos].size); i++){
                fseek(file, i, SEEK_SET);
                fwrite(&carac, 1, 1, file);
            }
            fclose(file);
            cout<<"\nLa particion : '"<<this->name<<"' ha sido eliminada"<<endl;
            newPartition(pos, 'i', 'x', this->mbr.fit, this->mbr.size, 0, "");
            saveMBR(this->mbr);
            return;
        }
    }else{
        cout<<"\nLa particion : '"<<this->name<<"' no fue eliminada"<<endl;
        return;
    }
}

void obfdisk::deleteLogic(){
    Structs::EBR previous_ebr;
    Structs::EBR current_ebr;
    int ext_start;//START DE LA PARTICION EXTENDIDA
    bool seguimos = true; //VARIABLE PARA MANTENER EL WHILE ACTIVO, ESTO PERMITE SEGUIR RECONOCIENDO EBRS
    for(int i = 0; i < 4; i++){
        if(this->mbr.particiones[i].type == 'e'){
            //OBTENEMOS EL PRIMER EBR QUE SE ENCUENTRA CON EL MISMO START QUE LA PARTICION EXTENDIDA
            previous_ebr = getEBR(this->path, this->mbr.particiones[i].start);
            ext_start = this->mbr.particiones[i].start;
        }
    }
    if(previous_ebr.name == this->name){
        cout<<"\nDesea eliminarlo [s/n]"<<endl;
        char op;
        cin >> op;
        if(op == 's'){
            //SI LA PARTICION A ELIMINAR ES LA PRIMERA SE DEBE DEJAR EL EBR INHABILITADO PERO CON LA REFERENCIA DEL SIGUIENTE EBR SI EXISTIERA
            if(this->delet == "fast"){
                newEBR('i', previous_ebr.fit, ext_start, 0, "", previous_ebr.next, ext_start);
                return;
            }else{
                char carac = '\0';
                char charPath[this->path.size() + 1];
                strcpy(charPath, this->path.c_str());
                FILE *file = NULL;
                file = fopen(charPath, "rb+");
                for(int i = (previous_ebr.start - sizeof(Structs::EBR)); i < (previous_ebr.start + previous_ebr.size); i++){
                    fseek(file, i, SEEK_SET);
                    fwrite(&carac, 1, 1, file);
                }
                fclose(file);
                newEBR('i', previous_ebr.fit, ext_start, 0, "", previous_ebr.next, ext_start);
                return;
            }
        }else{
            cout<<"\nLa particion : '"<<this->name<<"' no fue eliminada"<<endl;
            return;
        }
    }
    current_ebr = getEBR(this->path, previous_ebr.next);
    while(seguimos){
        if(current_ebr.name == this->name){
            cout<<"\nDesea eliminarlo [s/n]"<<endl;
            char op;
            cin >> op;
            if(op == 's'){
                cout<<"\nLa particion : '"<<this->name<<"' ha sido eliminada"<<endl;
                //VERIFICAR SI EL EBR ACTUAL APUNTA A OTRO EBR
                if(this->delet == "fast"){
                    previous_ebr.next = current_ebr.next;
                    saveEBR(previous_ebr, previous_ebr.start - sizeof(Structs::EBR));
                    return;
                }else{
                    char carac = '\0';
                    char charPath[this->path.size() + 1];
                    strcpy(charPath, this->path.c_str());
                    FILE *file = NULL;
                    file = fopen(charPath, "rb+");
                    for(int i = (current_ebr.start - sizeof(Structs::EBR)); i < (current_ebr.start + current_ebr.size); i++){
                        fseek(file, i, SEEK_SET);
                        fwrite(&carac, 1, 1, file);
                    }
                    fclose(file);
                    previous_ebr.next = current_ebr.next;
                    saveEBR(previous_ebr, previous_ebr.start - sizeof(Structs::EBR));
                    return;
                }
            }else{
                cout<<"\nLa particion : '"<<this->name<<"' no fue eliminada"<<endl;
                return;
            }
        }
        if(current_ebr.next == -1){
            seguimos = false;
        }else{
            previous_ebr = current_ebr;
            current_ebr = getEBR(this->path, current_ebr.next);
        }
    }
    cout<<"\nNo existe la particion : "<<this->name<<endl;
    return;
}

void obfdisk::addPartition(){
    Structs::EBR previous_ebr;
    bool seguimos = true;
    bool logic = false;
    int pos = -1;
    int tmp_space = 0;
    for(int i = 0; i < 4; i++){
        if(this->name == this->mbr.particiones[i].name){
            pos = i;
        }
        if(this->mbr.particiones[i].type == 'e'){
            previous_ebr = getEBR(this->path, this->mbr.particiones[i].start);
        }
    }
    while(seguimos){
        if(previous_ebr.name == this->name){
            logic = true;
            break;
        }
        if(previous_ebr.next == -1){
            seguimos = false;
        }else{
            previous_ebr = getEBR(this->path, previous_ebr.next);
        }
    }
    if(logic){
        addLogic();
        return;
    }
    if(pos == -1){
        cout<<"\nNo existe la particion : "<<this->name<<endl;
        return;
    }
    if(this->add < 0){
        tmp_space = this->mbr.particiones[pos].size + this->add;
        if(tmp_space <= 0){
            cout<<"\nEspacio a restar igual o menor que el tamaño de la particion : "<<this->name<<endl;
            cout<<"\nNo se pudo quitar espacio"<<endl;
            return;
        }else{
            int size = this->mbr.particiones[pos].size;
            this->mbr.particiones[pos].size = this->mbr.particiones[pos].size + this->add;
            cout<<"\nEspacio quitado correctamente"<<endl;
            cout<<"\nLa particion "<<this->name<<" paso de : "<<size<<" a : "<<this->mbr.particiones[pos].size<<endl;
            saveMBR(this->mbr);
            return;
        }
    }
    //VERIFICAMOS QUE PARTICION USAREMOS, YA QUE SI ES LA ULTIMA SE TIENE QUE COMPARA CON EL TAMAÑO DEL DISCO Y NO CON OTRA PARTICION
    if(pos != 3){
        //OBTENEMOS EL ESPACIO QUE HAY ENTRE LA PARTICION ACTUAL Y LA QUE LE SIGUE
        tmp_space = this->mbr.particiones[pos + 1].start - (this->mbr.particiones[pos].start + this->mbr.particiones[pos].size);
        //VERIFICAMOS QUE EL ADD ENTRE EN EL ESPACIO DISPONIBLE
        if(this->add <= tmp_space){
            int size = this->mbr.particiones[pos].size;
            this->mbr.particiones[pos].size = this->mbr.particiones[pos].size + this->add;
            cout<<"\nEspacio agregado correctamente"<<endl;
            cout<<"\nLa particion "<<this->name<<" paso de : "<<size<<" a : "<<this->mbr.particiones[pos].size<<endl;
            saveMBR(this->mbr);
            return;
        }
    }else{

        tmp_space = this->mbr.size - (this->mbr.particiones[pos].start + this->mbr.particiones[pos].size);
        //VERIFICAMOS QUE EL ADD ENTRE EN EL ESPACIO DISPONIBLE
        if(this->add <= tmp_space){
            int size = this->mbr.particiones[pos].size;
            this->mbr.particiones[pos].size = this->mbr.particiones[pos].size + this->add;
            cout<<"\nEspacio agregado correctamente"<<endl;
            cout<<"\nLa particion "<<this->name<<" paso de : "<<size<<" a : "<<this->mbr.particiones[pos].size<<endl;
            saveMBR(this->mbr);
            return;
        }
    }
    cout<<"\nEspacio insufucienta para agregar a la particion : "<<this->name<<endl;
    cout<<"\nNo se pudo agregar espacio"<<endl;
    return;
}

void obfdisk::addLogic(){
    Structs::EBR previous_ebr;
    Structs::EBR current_ebr;
    int tmp_space = 0;
    int ext_start;//START DE LA PARTICION EXTENDIDA
    int ext_size = 0;
    bool seguimos = true; //VARIABLE PARA MANTENER EL WHILE ACTIVO, ESTO PERMITE SEGUIR RECONOCIENDO EBRS
    for(int i = 0; i < 4; i++){
        if(this->mbr.particiones[i].type == 'e'){
            //OBTENEMOS EL PRIMER EBR QUE SE ENCUENTRA CON EL MISMO START QUE LA PARTICION EXTENDIDA
            current_ebr = getEBR(this->path, this->mbr.particiones[i].start);
            ext_start = this->mbr.particiones[i].start;
            ext_size = this->mbr.particiones[i].start + this->mbr.particiones[i].size;
        }
    }
    while(seguimos){
        if(current_ebr.next == -1){
            break;
        }
        if(current_ebr.name == this->name){
            if(this->add < 0){
                tmp_space = current_ebr.size + this->add;
                if(tmp_space <= 0){
                    cout<<"\nEspacio a restar igual o menor que el tamaño de la particion : "<<this->name<<endl;
                    cout<<"\nNo se pudo quitar espacio"<<endl;
                    return;
                }else{
                    int size = current_ebr.size;
                    current_ebr.size = current_ebr.size + this->add;
                    cout<<"\nEspacio quitado correctamente"<<endl;
                    cout<<"\nLa particion "<<current_ebr.name<<" paso de : "<<size<<" a : "<<current_ebr.size<<endl;
                    saveEBR(current_ebr, (current_ebr.start - sizeof(Structs::EBR)));
                    return;
                }
            }
            Structs::EBR post_ebr = getEBR(this->path, current_ebr.next);
            if(post_ebr.next == -1){
                tmp_space = ext_size - (current_ebr.size + current_ebr.start);
                if(this->add <= tmp_space){
                    int size = current_ebr.size;
                    current_ebr.size = current_ebr.size + this->add;
                    current_ebr.next = current_ebr.size + current_ebr.start;
                    cout<<"\nEspacio agregado correctamente"<<endl;
                    cout<<"\nLa particion "<<current_ebr.name<<" paso de : "<<size<<" a : "<<current_ebr.size<<endl;
                    saveEBR(current_ebr, (current_ebr.start - sizeof(Structs::EBR)));
                    newEBR('i', 'w', current_ebr.next, 0, "", -1, current_ebr.next);
                    return;
                }else{
                    cout<<"\nEspacio insufucienta para agregar a la particion : "<<this->name<<endl;
                    cout<<"\nNo se pudo agregar espacio"<<endl;
                    return;
                }
            }else{
                cout<<"\nEspacio insufucienta para agregar a la particion : "<<this->name<<endl;
                cout<<"\nNo se pudo agregar espacio"<<endl;
                return;
            }
        }
        current_ebr = getEBR(this->path, current_ebr.next);
    }
    cout<<"\nNo existe la particion : "<<this->name<<endl;
    return;
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
    if(this->type == "l"){
        createLogicPartition();
        return;
    }
    if(activas == 0){
        // CASO DONDE NO HAY NINGUNA PARTICION ACTIVA
        int sizeDisponible = this->mbr.size - sizeof(this->mbr);
        if(this->size > sizeDisponible){
            cout<<"\nEspacio insuficiente"<<endl;
            return;
        }
        newPartition(0, 'h', getType(this->type), getFit(this->fit), sizeof(Structs::MBR), this->size, this->name);
        saveMBR(this->mbr);
        if(this->type == "e"){
            newEBR('i', getFit(this->fit), sizeof(Structs::MBR), this->size, this->name, -1, sizeof(Structs::MBR));
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
                        newPartition(i, 'h', getType(this->type), getFit(this->fit), start, this->size, this->name);
                        saveMBR(this->mbr);
                        if(this->type == "e"){
                            newEBR('i', getFit(this->fit), start, this->size, this->name, -1, start);
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
                            if(this->type == "e"){
                                newEBR('i', getFit(this->fit), start, this->size, this->name, -1, start);
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
                    if(this->type == "e"){
                        newEBR('i', getFit(this->fit), start, this->size, this->name, -1, start);
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
                            if(this->type == "e"){
                                newEBR('i', getFit(this->fit), start, this->size, this->name, -1, start);
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
                                if(this->type == "e"){
                                    newEBR('i', getFit(this->fit), start, this->size, this->name, -1, start);
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
                if(this->type == "e"){
                    newEBR('i', getFit(this->fit), sizeof(Structs::MBR), this->size, this->name, -1, sizeof(Structs::MBR));
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
                        if(this->type == "e"){
                            newEBR('i', getFit(this->fit), start, this->size, this->name, -1, start);
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

void obfdisk::createLogicPartition(){
    Structs::EBR previous_ebr;
    Structs::EBR current_ebr;
    int tmp_space = 0;
    int ant_space = 0;
    int ext_size = 0; //SIZE DE LA PARTICION EXTENDIDA
    int ext_start = 0;
    bool seguimos = true; //VARIABLE PARA MANTENER EL WHILE ACTIVO, ESTO PERMITE SEGUIR RECONOCIENDO EBRS
    for(int i = 0; i < 4; i++){
        if(this->mbr.particiones[i].type == 'e'){
            //OBTENEMOS EL PRIMER EBR QUE SE ENCUENTRA CON EL MISMO START QUE LA PARTICION EXTENDIDA
            previous_ebr = getEBR(this->path, this->mbr.particiones[i].start);
            ext_start = this->mbr.particiones[i].start;
            ext_size = this->mbr.particiones[i].size + ext_start;
        }
    }
    current_ebr = previous_ebr;
    while(seguimos){
        if(previous_ebr.name == this->name){
            tmp_space += 1;
        }
        if(previous_ebr.next == -1){
            seguimos = false;
        }else{
            previous_ebr = getEBR(this->path, previous_ebr.next);
        }
    }
    if(tmp_space != 0){
        cout<<"\nYa existe una particion con el nombre : "<<this->name<<endl;
        return;
    }
    previous_ebr = current_ebr;
    tmp_space = 0;
    if(previous_ebr.status == 'i' && previous_ebr.next != -1){
        //CASO DONDE EL PRIMER EBR ESTA INHABILITADO PERO SI HAY MAS EBRS
        tmp_space = previous_ebr.next - (previous_ebr.start + sizeof(Structs::EBR));
        //VERIFICAMOS SI EL ESPACIO LIBRE ES SUFICIENTE PARA LA PARTICION
         if(this->size <= tmp_space){
             if(this->fit == "ff"){
                 previous_ebr.start = previous_ebr.start + sizeof(Structs::EBR);
                 newEBR('h', getFit(this->fit), previous_ebr.start, this->size, this->name, previous_ebr.next, (previous_ebr.start - sizeof(Structs::EBR)));
                 return;
             }
         }
    }
    //SI EL PRIMER EBR TIENE NEXT -1 SIGNIFICA QUE NO NINGUNA PARTICION LOGICA CREADA, EN CASO CONTRARIO ANALIZAR PARA FITS
    if(previous_ebr.next == -1){
        tmp_space = ext_size - sizeof(Structs::EBR);
        if(this->size <= tmp_space){
            modifyEBR(previous_ebr);
            return;
        }else{
            cout<<"\nEspacio insuficiente"<<endl;
            cout<<"\nNo pudo crearse la particion"<<endl;
            return;
        }
    }else{
        //CASO DONDE LA PRIMER PARTICION ESTA JUNTO CON EL SIGUIENTE EBR, ES DECIR NO HAY ESPACIO LIBRE
        current_ebr = getEBR(this->path, previous_ebr.next);
        if(current_ebr.start == (previous_ebr.start + previous_ebr.size) || current_ebr.start == (previous_ebr.start + previous_ebr.size + sizeof(Structs::EBR))){
            seguimos = true;
            while(seguimos){
                //SI EL EBR ACTUAL ESTA INHABILITADO Y SU NEXT ES -1 QUIERE DECIR QUE ES EL ULTIMO EBR
                if(current_ebr.status == 'i' && current_ebr.next == -1){
                    tmp_space = ext_size - ( current_ebr.start + sizeof(Structs::EBR) );
                    if(this->size <= tmp_space){
                        modifyEBR(current_ebr);
                        return;
                    }
                }else{
                    //CASO DONDE EL EBR ACTUAL ESTA ACTIVO, HAY QUE REVISAR SI HAY ESPACIO ENTRE LA PARTICION ANTERIOR
                    tmp_space = previous_ebr.next - (previous_ebr.start + previous_ebr.size);
                    //VERIFICAMOS SI EL ESPACIO LIBRE ES SUFICIENTE PARA LA PARTICION
                     if(this->size <= tmp_space){
                         if(this->fit == "ff"){
                             int start = previous_ebr.start + previous_ebr.size;
                             //current_ebr = getEBR(this->path, previous_ebr.next);
                             int next;
                             if(current_ebr.next == -1){
                                 next = current_ebr.start;
                             }else{
                                 next = current_ebr.start - sizeof(Structs::EBR);
                             }

                             newEBR('h', 'f', (start + sizeof(Structs::EBR)), this->size, this->name, next, start);
                             previous_ebr.next = start;
                             saveEBR(previous_ebr, (previous_ebr.start - sizeof(Structs::EBR)));
                             return;
                         }else{
                             break;
                         }
                     }
                }

                if(current_ebr.next == -1){
                    seguimos = false;
                }else{
                    previous_ebr = current_ebr;
                    current_ebr = getEBR(this->path, previous_ebr.next);
                }
            }
        }else{
            //CASO DONDE EXISTE ESPACIO ENTRE EL SEGUNDO EBR Y LA PRIMERA PARTICION
            tmp_space = previous_ebr.next - (previous_ebr.start + sizeof(Structs::EBR));
            //VERIFICAMOS SI EL ESPACIO LIBRE ES SUFICIENTE PARA LA PARTICION
             if(this->size <= tmp_space){
                 if(this->fit == "ff"){
                     int start = previous_ebr.start + previous_ebr.size;
                     current_ebr = getEBR(this->path, previous_ebr.next);
                     int next;
                     if(current_ebr.next == -1){
                         next = current_ebr.start;
                     }else{
                         next = current_ebr.start - sizeof(Structs::EBR);
                     }

                     newEBR('h', 'f', (start + sizeof(Structs::EBR)), this->size, this->name, next, start);
                     previous_ebr.next = start;
                     saveEBR(previous_ebr, (previous_ebr.start - sizeof(Structs::EBR)));
                     return;
                 }
             }else{
                 //SI LA PARTICION NO ENTRA EN EL ESPACIO ANTERIOR SE DEBE VERIFICAR SI HAY ESPACIO EN OTRO LADO
                 previous_ebr = getEBR(this->path, previous_ebr.next);
                 current_ebr = getEBR(this->path, previous_ebr.next);
                 seguimos = true;
                 while(seguimos){
                     tmp_space = previous_ebr.next - (previous_ebr.start + sizeof(Structs::EBR));
                     //VERIFICAMOS SI EL ESPACIO LIBRE ES SUFICIENTE PARA LA PARTICION
                      if(this->size <= tmp_space){
                          if(this->type == "ff"){
                              int start = previous_ebr.start + previous_ebr.size;
                              int next;
                              if(current_ebr.next == -1){
                                  next = current_ebr.start;
                              }else{
                                  next = current_ebr.start - sizeof(Structs::EBR);
                              }

                              newEBR('h', 'f', (start + sizeof(Structs::EBR)), this->size, this->name, next, start);
                              previous_ebr.next = start;
                              saveEBR(previous_ebr, (previous_ebr.start - sizeof(Structs::EBR)));
                              return;
                          }else{
                              break;
                          }
                      }

                     if(current_ebr.next == -1){
                         seguimos = false;
                     }else{
                         previous_ebr = current_ebr;
                         current_ebr = getEBR(this->path, previous_ebr.next);
                     }
                 }
             }
        }
    }
    ant_space = 0;
    seguimos = true;
    current_ebr = getEBR(this->path, ext_start);
    while(seguimos){
        if(current_ebr.next == -1){
            if(ant_space == 0){
                ant_space = ext_size - (current_ebr.start + sizeof(Structs::EBR));
            }
            seguimos = false;
        }else{
            tmp_space = current_ebr.next - (current_ebr.start + current_ebr.size );
            if(tmp_space != 0 && this->size <= tmp_space){
                if(ant_space == 0){
                    ant_space = tmp_space;
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
        previous_ebr = current_ebr;
        current_ebr = getEBR(this->path, previous_ebr.next);
    }
    current_ebr = getEBR(this->path, ext_start);
    if(ant_space != 0){
        seguimos = true;
        while(seguimos){
            if(current_ebr.next == -1){
                tmp_space = ext_size - ( current_ebr.start + sizeof(Structs::EBR) );
                if(this->size <= tmp_space){
                    modifyEBR(current_ebr);
                    return;
                }
                seguimos = false;
            }else{
                tmp_space = current_ebr.next - (current_ebr.start + current_ebr.size );
                if(tmp_space == ant_space){
                    previous_ebr = current_ebr;
                    current_ebr = getEBR(this->path, previous_ebr.next);
                    int start = previous_ebr.start + previous_ebr.size;
                    int next;
                    if(current_ebr.next == -1){
                        next = current_ebr.start;
                    }else{
                        next = current_ebr.start - sizeof(Structs::EBR);
                    }
                    newEBR('h', getFit(this->fit), (start + sizeof(Structs::EBR)), this->size, this->name, next, start);
                    previous_ebr.next = start;
                    saveEBR(previous_ebr, (previous_ebr.start - sizeof(Structs::EBR)));
                    return;
                }
            }
            previous_ebr = current_ebr;
            current_ebr = getEBR(this->path, previous_ebr.next);
        }
    }
    cout<<"\nEspacio insuficiente"<<endl;
    cout<<"\nNo pudo crearse la particion"<<endl;
    return;
}

