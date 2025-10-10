#ifndef LISTAE_CONTACTO_H_INCLUDED
#define LISTAE_CONTACTO_H_INCLUDED
#include <string.h>
typedef struct{
char nombre[21];
char alias[21];
int tipo_cuenta;
} Contacto;

typedef struct{
Contacto contactos;
int cur;
int aux;
} Lista_contactos;

void InitListaEs(Lista_contactos *l){       //da valores "por defecto" a las variables
    l->cur = -1;
    l->aux = -1;
}

void ResetListaEs(Lista_contactos *l){      //envia al cursor al inicio del arreglo(en este caso)
    l->cur = 0;
}

int IsEmptyListaEs(Lista_contactos l){      //indica si la lista esta vacia
    if (l->cur == -1){
        return 1;
    }
    else {
        return 0;
    }
}

int isFullListaEs(Lista_contactos l){       //indica si la list esta llena
    if (l->aux == MAX){
        return 1;
    }
    else {
        return 0;
    }
}

int IsOosListaEs(Lista_contactos l){        //indica si el cursor esta fuera de rango
    if (l->cur-1 == l->aux){
        return 1;
    }
    else {
        return 0;
    }
}

Contacto CopyListaEs(Lista_contactos *l){   //devuelve el valor(se usa para mostrar)
    return l.contactos[l.cur];
}

void InsertListaEs(Lista_contactos *l, Contacto c){    //se encarga del "carga"
    if(l->cur == -1){
        l->aux++;
        l->cur++;
        strcpy(l->contactos[l->cur].nombre,getListaEsNombre(c));
        strcpy(l->contactos[l->cur].alias,getListaEsAlias(c));
        l->contactos[l->cur].tipo_cuenta = getListaEsTipoCuenta(c);
    }
    else {
        strcpy(l->contactos[l->cur].nombre,getListaEsNombre(c));
        strcpy(l->contactos[l->cur].alias,getListaEsAlias(c));
        l->contactos[l->cur].tipo_cuenta = getListaEsTipoCuenta(c);
        l->aux++;
    }
}

void ForwardsListaEs(Lista_contactos *l){     //mueve el cursor al siguiente
    l->cur++;
}

void SupressListaEs(Lista_contactos *l){      //elimina el elemento donde esta el cursor

}







#endif // LISTAE_CONTACTO_H_INCLUDED
