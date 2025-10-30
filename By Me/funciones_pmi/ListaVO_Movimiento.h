#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED
#include "Movimiento.h"
#include "malloc.h"
#include "string.h"

struct nodo{
    Movimiento vipd;
    struct nodo *siguiente;
};
typedef struct nodo Nodo;
typedef struct{
    Nodo *acc;
    Nodo *cur;
    Nodo *aux;
}Lista_movimiento;

void init_lista_movimiento(Lista_movimiento *l){
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

void reset_lista_movimiento(Lista_movimiento *l){
    l->cur = l->acc;
    l->aux = l->acc;
}

int isempty_lista_movimiento(Lista_movimiento l){
    return (l.acc == NULL);
}

int isfull_lista_movimiento(Lista_movimiento l){
    return (l.acc != l.cur && l.acc == NULL);
}

int isOos_lista_movimiento(Lista_movimiento l){
    return (l.cur == NULL);
}

Movimiento copy_list_movimiento(Lista_movimiento l){
    return l.cur.vipd;
}

void forward_lista_movimiento(Lista_movimiento *l){
    l->aux = l->cur;
    l->cur = l->cur->siguiente;
}

#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
