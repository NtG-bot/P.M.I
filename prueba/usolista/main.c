#include <stdio.h>
#include <stdlib.h>
#include "listaenteros.h"

void CargaInt(ListaEnt *b){
    int i, n, p;
    printf("ingrese cant a cargar:\n");
    scanf("%d", &n);
    while(!IsFullLista(b)){

            printf("ingrese entero:\n");
            scanf("%d",&p);
            InsertLista( b, p );
        }
}

ListaEnt MuestraInt(ListaEnt b){
    int i;
    ResetLista(*b);
    while(!IsOos(b)){
        printf("entero:%d\n", CopyLista(b));
        ForwardLista(b);
    }
}

int main()
{
    ListaEnt b[MAXI];
    CargaInt(&b);
    MuestraInt(b);
    return 0;
}
