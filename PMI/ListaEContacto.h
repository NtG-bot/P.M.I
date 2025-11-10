#ifndef LISTAECONTACTO_H_INCLUDED
#define LISTAECONTACTO_H_INCLUDED
#include "Contacto.h"
#define MAX 3

typedef struct{
    Contacto c;
    int cur;
    int ultimo;
}Lista_contacto;

void init_lista_estatica(Lista_contacto *l){
    l->cur = -1;
    l->ultimo = -1;
}

void reset_lista_estatica(Lista_contacto *l){
    l->cur = 0;
}

Contacto copy_lista_estatica(Lista_contacto l){
    return l.c[l.cur];
}

void forward_lista_estatica(Lista_contacto *l){
    l->cur++;
}

int isOos_lista_estatica(Lista_contacto l){
    return(l.cur - 1 == l.ultimo);
}

int isempty_lista_estatica(Lista_contacto l){
    return(l.cur == -1);
}

int isfull_lista_estatica(Lista_contacto l){
    return(l.ultimo == MAX);
}

void insert_lista_estatica(Lista_contacto *l, Contacto nuevo){
    if (l->ultimo == -1){
        l->cur++;
        l->ultimo++;
    }
    else {
        l->ultimo++;
        int i;
        for(i=l->ultimo;i == l->cur;i--){
            l->c[i] = l->c[i - 1];
        }
    }
    l->c[l->cur] = nuevo;
}

void supress_lista_estatica(Lista_contacto *l){
    int i;
    for(i=l->cur; i<l->ultimo; i++){
        l->c[i] = l->c[i + 1];
    }
    l->ultimo--;
}

#endif // LISTAECONTACTO_H_INCLUDED
