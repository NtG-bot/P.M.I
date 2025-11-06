#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED
#include "Movimiento.h"
#include "malloc.h"
#include "string.h"

typedef struct nodo{
    Movimiento vipd;
    struct nodo *siguiente;
}Nodo;
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

Movimiento copy_list_movimiento(Lista_movimiento l){        //a chekear
    Movimiento mov;
    mov = l.cur->vipd;
    return mov;
}

void forward_lista_movimiento(Lista_movimiento *l){
    l->aux = l->cur;
    l->cur = l->cur->siguiente;
}

void insert_lista_movimiento(Lista_movimiento *l, Movimiento m){
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->vipd.id_mov = get_id_mov(m);

    if (l->acc == l->cur){
        l->acc = nuevo;
        nuevo->siguiente = l->cur;
        l->cur = nuevo;
        l->aux = nuevo;
    } else {
        l->aux->siguiente = nuevo;
        nuevo->siguiente = l->cur;
        l->cur = nuevo;
    }

}

void suppress_lista_movimiento(Lista_movimiento *l){
    if(l->acc == l->cur){
        l->acc = l->cur->siguiente;
        free((void*)l->cur);
        l->cur = l->acc;
        l->aux = l->acc;
    }else{
        l->aux->siguiente = l->cur->siguiente;
        free((void*)l->cur);
        l->cur = l->aux->siguiente;
    }
}

#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
