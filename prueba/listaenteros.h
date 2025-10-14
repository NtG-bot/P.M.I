#ifndef LISTAENTEROS_H_INCLUDED
#define LISTAENTEROS_H_INCLUDED

#define MAXI 10
typedef struct
{
    int esteros[MAXI] ;
    int cursor;
    int ultimo;
} ListaEnt;

void InitLista(ListaEnt *a)
{
    a->cursor=-1;
    a->aux=-1;
}

int IsEmptyLista(ListaEnt a)
{
    if (a->cursor == -1)
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
    if (a->cant == MAXI)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void ForwardLista(ListaEnt *a)
{
    a->cursor++;
}

ListaEnt CopyLista(ListaEnt a)
{
    return a->vipd[a->cursor];
}

void ResetLista(ListaEnt *a)(
    a->cursor = 0;
)

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
            a->esteros[ i ] = a->esteros[ i-1 ]
        }
    }

    a->esteros[ a->cursor ] = nuevo;
}



#endif // LISTAENTEROS_H_INCLUDED
