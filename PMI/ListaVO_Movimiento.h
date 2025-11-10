#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED
#include "Movimiento.h"

// --- Estructura del Nodo ---
typedef struct nodo{
    Movimiento vipd;
    struct nodo *siguiente;
}Nodo;

// --- Estructura de la Lista ---
typedef struct{
    Nodo *acc; // Puntero de Acceso (cabeza)
    Nodo *cur; // Puntero Cursor (actual)
    Nodo *aux; // Puntero Auxiliar (anterior)
}Lista_movimiento;



void init_lista_movimiento(Lista_movimiento *l){
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}


void reset_lista_movimiento(Lista_movimiento *l){
    l->cur = l->acc;
    l->aux = NULL;
}

int isempty_lista_movimiento(Lista_movimiento l){
    return (l.acc == NULL);
}

int isOos_lista_movimiento(Lista_movimiento l){
    return (l.cur == NULL);
}


void forward_lista_movimiento(Lista_movimiento *l){
    if (l->cur != NULL) {
        l->aux = l->cur;
        l->cur = l->cur->siguiente;
    }
}


Movimiento copy_list_movimiento(Lista_movimiento l){
    if (l.cur != NULL) {
        return l.cur->vipd;
    }
    Movimiento mov_vacio; mov_vacio.id_mov = -1; return mov_vacio;
}


void suppress_lista_movimiento(Lista_movimiento *l) {
    Nodo *nodoAEliminar;
    if (isOos_lista_movimiento(*l)) { return; }

    nodoAEliminar = l->cur;

    if (l->cur == l->acc) {
        l->acc = l->cur->siguiente;
        l->cur = l->acc;
        l->aux = NULL;
    } else {
        l->aux->siguiente = l->cur->siguiente;
        l->cur = l->cur->siguiente;
    }
    free(nodoAEliminar);
}

// (Función 'insert' simple. La 'insertOrdenadoFecha' va en main.c)
void insert_lista_movimiento(Lista_movimiento *l, Movimiento m){
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) return;
    nuevoNodo->vipd = m;

    if((*l).cur == (*l).acc || l->acc == NULL){ // Al principio (o si está vacía)
        nuevoNodo->siguiente = l->acc;
        l->acc = nuevoNodo;
        l->cur = nuevoNodo; // Cursor queda en el nuevo
        l->aux = NULL;
    } else { // En el medio
        nuevoNodo->siguiente = l->cur;
        l->aux->siguiente = nuevoNodo;
        l->cur = nuevoNodo; // Cursor queda en el nuevo
    }
}

#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
