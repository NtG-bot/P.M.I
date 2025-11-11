#ifndef LISTAECONTACTO_H_INCLUDED
#define LISTAECONTACTO_H_INCLUDED
#include "Contacto.h"
#define MAX 100

typedef struct{
    Contacto c[MAX];
    int cur;
    int ultimo;
}Lista_contactos;

void init_lista_estatica(Lista_contactos *l){
    l->cur = -1;
    l->ultimo = -1;
}

void reset_lista_estatica(Lista_contactos *l){
    l->cur = 0;
}

Contacto copy_lista_estatica(Lista_contactos l){
    return l.c[l.cur];
}

void forward_lista_estatica(Lista_contactos *l){
    l->cur++;
}

int isOos_lista_estatica(Lista_contactos l){
    return(l.cur - 1 == l.ultimo);
}

int isempty_lista_estatica(Lista_contactos l){
    return(l.cur == -1);
}

int isfull_lista_estatica(Lista_contactos l){
    return(l.ultimo == MAX);
}

void insert_lista_estatica(Lista_contactos *l, Contacto nuevo){
    if (l->ultimo == -1){
        l->cur = 0;
        l->ultimo = 0;
    }
    else {
        l->ultimo++;

    }
    l->c[l->ultimo] = nuevo;
}

void supress_lista_estatica(Lista_contactos *l){
    int i;
    for(i=l->cur; i<l->ultimo; i++){
        l->c[i] = l->c[i + 1];
    }
    l->ultimo--;
    if (l->ultimo == -1) { // Si quedo vacía
        l->cur = -1;
    }
}


// Devuelve puntero al contacto si lo encuentra, NULL si no.
Contacto* buscarContactoPorAlias(Lista_contactos *l, char alias_buscado[]) {
    int i;
    for (i = 0; i <= l->ultimo; i++) {
        if (strcmp(l->c[i].alias_cbu, alias_buscado) == 0) {
            return &(l->c[i]);
        }
    }
    return NULL;
}

#endif // LISTAECONTACTO_H_INCLUDED
