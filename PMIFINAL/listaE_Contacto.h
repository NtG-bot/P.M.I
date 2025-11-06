#ifndef LISTAE_CONTACTO_H_INCLUDED
#define LISTAE_CONTACTO_H_INCLUDED
#include <string.h>
#include "malloc.h"
#include "contacto.h"
#define MAX 3

typedef struct{
Contacto contactos[MAX];
int cur;
int ultimo;
} Lista_contactos;

void InitListaEs(Lista_contactos *l){       //da valores "por defecto" a las variables
    l->cur = -1;
    l->ultimo = -1;
}

void ResetListaEs(Lista_contactos *l){      //envia al cursor al inicio del arreglo(en este caso)
    l->cur = 0;
}

int IsEmptyListaEs(Lista_contactos l){      //indica si la lista esta vacia
    return (l.ultimo == -1);
}

int isFullListaEs(Lista_contactos l){       //indica si la list esta llena
    return (l.ultimo == MAX - 1);
}

int IsOosListaEs(Lista_contactos l){        //indica si el cursor esta fuera de rango
   return (l.ultimo == l.ultimo + 1);
}

Contacto CopyListaEs(Lista_contactos *l){   //devuelve el valor(se usa para mostrar)
    return l->contactos[l->cur];
}

void InsertListaEs(Lista_contactos *l, Contacto a){                 //mueve uno hacia la derecha, recuerden que inserta tipo pila, y inserta
    if( l->ultimo == -1 )
    {
        l->ultimo++;
        l->cur++;
    }
    else
    {
        l->ultimo++;
        int i;
        for( i = l->ultimo ; i == l->cur ; i-- )
        {
            l->contactos[i] = l->contactos[ i-1 ] ;
        }
    }
    strcpy(l->contactos[l->cur].nombre,get_nombre(a));
    strcpy(l->contactos[l->cur].alias_cbu, get_alias_cbu(a));
    l->contactos[l->cur].tipo_cuenta = get_tipo_cuenta(a);

}


void ForwardsListaEs(Lista_contactos *l){     //mueve el cursor al siguiente
    l->cur++;
}

void SupressListaEs(Lista_contactos *l)      //elimina el elemento donde esta el cursor (hay que laburarlo)
{
    int i;
    for( i = l->ultimo ; i == l->cur ; i-- )
    {
        l->contactos[ i ] = l->contactos[ i - 1 ] ;
    }
    l->ultimo--;
}



#endif // LISTAE_CONTACTO_H_INCLUDED
