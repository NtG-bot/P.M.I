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
    return (a.cursor == -1);
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

void ResetLista(ListaEnt *a)
{
    a->cursor = 0;
}

int IsOos(ListaEnt a)
{
    return (a.cursor == a.ultimo + 1);
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

void SupressLista(ListaEnt *a)
{
    int i;
    for( i = a->cursor ; i == a->ultimo-1 ; i++ )
    {
        a->enteros[ i ] = a->enteros[ i+1 ] ;
    }
    a->ultimo--;
}



#endif // LISTAENTEROS_H_INCLUDED
