#include <stdio.h>
#include <stdlib.h>
#include "listaenteros.h"

void CargaInt(ListaEnt *b)
{
    int  n, p;
    while(!IsFullLista(*b))
    {
        printf("ingrese entero:\n");
        scanf("%d",&p);
        InsertLista(b,p);
        ForwardLista(b);
    }
}

int MuestraInt(ListaEnt *b)
{
    int i;
    ResetLista(b);
    while(!IsOos(*b))
    {
        printf("entero:%d\n", CopyLista(*b));
        ForwardLista(b);
    }
}

int main()
{
    ListaEnt b[MAXI];
    InitLista(b);
    int n;
    do
    {
        printf("1)cargar\n2)mostrar\n3)borrar\n4)salir\n");
        printf("ingrese n:\n");
        scanf("%d",&n);
        switch (n)
        {
        case 1:
        {
            CargaInt(&b);
            break;
        }
        case 2:
        {
            MuestraInt(b);
            break;
        }
        case 3:
        {
            SupressLista(&b);
            break;
        }
        case 4:
        {
            exit(1);
        }
        }
    }
    while ( n!=4);
    return 0;
}
