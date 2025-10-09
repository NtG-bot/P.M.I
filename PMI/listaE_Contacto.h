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

void init(Lista_contactos *l){
    l->cur = -1;
    l->aux = -1;
}

void resetLista(Lista_contactos *l){
    l->cur = 0;
}

Contacto copyLista(Lista_contactos *l){
    return l.contactos[l.cur];
}

void insertLista(Lista_contactos *l, Contacto c){
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
        l->aux++:
    }











#endif // LISTAE_CONTACTO_H_INCLUDED
