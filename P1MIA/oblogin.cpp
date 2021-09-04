#include "oblogin.h"
#include "iostream"
#include "structs.h"

using namespace std;

oblogin::oblogin()
{

}

extern Structs::Discos discos[99];
extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void oblogin::setUser(string user){
    if(user[0] == '"'){
        this->user = user.substr(1, user.size()-1);
        this->user = this->user.substr(0, this->user.size()-1);
    }else{
        this->user = user;
    }
}

void oblogin::setPwd(string pwd){
    if(pwd[0] == '"'){
        this->pwd = pwd.substr(1, pwd.size()-1);
        this->pwd = this->pwd.substr(0, this->pwd.size()-1);
    }else{
        this->pwd = pwd;
    }
}

void oblogin::setID(string id){
    if(id[0] == '"'){
        this->id = id.substr(1, id.size()-1);
        this->id = this->id.substr(0, this->id.size()-1);
    }else{
        this->id = id;
    }
}

void oblogin::exec(){
    if(this->user == ""){
        cout<<"\nUser invalido"<<endl;
        return;
    }
    if(this->pwd == ""){
        cout<<"\nPassword invalido"<<endl;
        return;
    }
    if(this->id == ""){
        cout<<"\nID invalido"<<endl;
        return;
    }
    if(log.status == 'h'){
        cout<<"\nYa se encuentra logueado el usuario : "<<log.user<<endl;
        return;
    }
    for (int i = 0; i < 99; i++){
        for (int j = 0; j < 26; j++){
            if (discos[i].particiones[j].id == this->id){
                log.id = this->id;
                log.pwd = this->pwd;
                log.user = this->user;
                log.status = 'h';
                cout<<"\nUsuario logueado correctamente"<<endl;
                return;
            }
        }
    }
    cout<<"\nLa particion no se encuentra entre las particiones montadas"<<endl;
    return;
}
