#ifndef LISTAENTEROS_H_INCLUDED
#define LISTAENTEROS_H_INCLUDED

#define MAXI 10
typedef struct
{
    int enteros[MAXI] ;
    int cursor;
    int ultimo;
} ListaEnt;

void InitLista(ListaEnt *a)
{
    a->cursor=-1;
    a->ultimo=-1;
}

int IsEmptyLista(ListaEnt a)
{
    if (a.cursor == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int IsFullLista(ListaEnt a)
{
    return (a.ultimo == MAXI - 1 ) ;
}

void ForwardLista(ListaEnt *a)
{
    a->cursor++;
}

int CopyLista(ListaEnt a)
{
    return a.enteros[a.cursor];

}

void ResetLista(ListaEnt *a){
   a->cursor = 0;
}

int IsOos(ListaEnt a){
    if(a.cursor == a.ultimo + 1){
        return 1;
    } else {
        return 0;
    }
}

void InsertLista(ListaEnt *a, int nuevo)
{

    if( a->ultimo == -1 )
    {
        a->ultimo++;
        a->cursor++;
    }
    else
    {
        a->ultimo++;
        int i;
        for( i = a->ultimo ; i == a->cursor ; i-- )
        {
            a->enteros[ i ] = a->enteros[ i-1 ] ;
        }
    }

    a->enteros[ a->cursor ] = nuevo;
}



#endif // LISTAENTEROS_H_INCLUDED
