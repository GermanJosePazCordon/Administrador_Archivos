#include "obmkdir.h"
#include "iostream"

using namespace std;

obmkdir::obmkdir()
{

}

void obmkdir::mostrar(obmkdir *disco){

    printf("\n\n---------DATOS----------\n\n");
    cout<<"El tamaño es "<<disco->size<<endl;
    cout<<"El espacio es "<<disco->space<<endl;
}
