#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Movimiento.h"

//  Estructura del Nodo
typedef struct nodo{
    Movimiento vipd;
    struct nodo *siguiente;
}Nodo;

// Estructura de la Lista -
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


int funcion_esMasRecienteOIgual(Movimiento mov1, Movimiento mov2) {
    if (get_fecha_mes(mov1) > get_fecha_mes(mov2)) {
        return 1;
    }
    if (get_fecha_mes(mov1) == get_fecha_mes(mov2)) {
        if (get_fecha_dia(mov1) >= get_fecha_dia(mov2)) {
            return 1;
        }
    }

    return 0;
}



void funcion_insertOrdenadoFecha(Lista_movimiento *LMovs, Movimiento mov) {
    Nodo *nuevo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        printf("ERROR DE MEMORIA!\n");
        return;
    }
    nuevo->vipd = mov;


    if (isempty_lista_movimiento(*LMovs) || funcion_esMasRecienteOIgual(mov, LMovs->acc->vipd)) {
        nuevo->siguiente = LMovs->acc;
        LMovs->acc = nuevo;
    }

    else {
        Nodo *actual = LMovs->acc;


        while ( (actual->siguiente != NULL) &&
                (funcion_esMasRecienteOIgual(actual->siguiente->vipd, mov)) )
        {
            actual = actual->siguiente;
        }



        nuevo->siguiente = actual->siguiente;
        actual->siguiente = nuevo;
    }
}


#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
