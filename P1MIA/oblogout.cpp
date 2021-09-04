#include "oblogout.h"
#include "iostream"
#include "structs.h"

using namespace std;

oblogout::oblogout()
{

}

extern Structs::Login log;

//--------------------------SETERS-----------------------------------

void oblogout::exec(){
    if(log.status == 'i'){
        cout<<"\nNo hay sesion iniciada"<<endl;
        return;
    }else{
        log.status = 'i';
        cout<<"\nSesion cerrada"<<endl;
        return;
    }
}
