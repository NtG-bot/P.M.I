#include <stdio.h>
#include <stdlib.h>
#include "listaenteros.h"

void CargaInt(ListaEnt *b){
    int  n, p;
    while(!IsFullLista(*b)){
            printf("ingrese entero:\n");
            scanf("%d",&p);
            InsertLista(b,p);
            ForwardLista(b);
        }
}

int MuestraInt(ListaEnt *b){
    int i;
    ResetLista(b);
    while(!IsOos(*b)){
        printf("entero:%d\n", CopyLista(*b));
        ForwardLista(b);
    }
}

int main()
{
    ListaEnt b[MAXI];
    InitLista(b);
    CargaInt(&b);
    MuestraInt(b);
    return 0;
}
