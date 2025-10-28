// Archivo: listaVO_Movimiento.h
// Define y implementa el TDA ListaMovimientos ordenada por fecha.

#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h> // Para malloc() y free()
#include "movimiento.h" // Necesitamos la definición de 'Movimiento'

//  Estructura del Nodo 
typedef struct NodoMovimiento {
    Movimiento datosDelMovimiento;
    struct NodoMovimiento *siguiente; // Puntero al próximo nodo
} NodoMovimiento;

//  Estructura de la Lista 
typedef struct {
    NodoMovimiento *cabeza; // Puntero al primer nodo de la lista
} ListaMovimientos;

// Inicializa la lista (cabeza a NULL).
void initListaMov(ListaMovimientos *lista) {
    lista->cabeza = NULL;
}

// Verifica si la lista está vacía.
int isEmptyListaMov(ListaMovimientos lista) {
    return (lista.cabeza == NULL);
}

// Función auxiliar: Compara dos fechas (devuelve 1 si mov1 es más reciente o igual).
int esMasRecienteOIgual(Movimiento mov1, Movimiento mov2) {
    if (mov1.mes > mov2.mes) {
        return 1;
    } else if (mov1.mes == mov2.mes) {
        return (mov1.dia >= mov2.dia);
    } else {
        return 0;
    }
}

// Inserta un movimiento manteniendo el orden: más reciente primero.
void insertOrdenadoFecha(ListaMovimientos *lista, Movimiento mov) {
    // 1. Crear nodo y pedir memoria.
    NodoMovimiento *nuevoNodo = (NodoMovimiento*) malloc(sizeof(NodoMovimiento));
    if (nuevoNodo == NULL) {
        printf("Error: No hay memoria disponible para nuevo movimiento en la lista.\n");
        return;
    }
    nuevoNodo->datosDelMovimiento = mov;
    nuevoNodo->siguiente = NULL;

    // 2. Insertar.
    // Caso A: Lista vacía o el nuevo es MÁS RECIENTE que el primero actual.
    if (isEmptyListaMov(*lista) || esMasRecienteOIgual(mov, lista->cabeza->datosDelMovimiento)) {
        nuevoNodo->siguiente = lista->cabeza;
        lista->cabeza = nuevoNodo;
    }
    // Caso B: Insertar en medio o al final.
    else {
        NodoMovimiento *actual = lista->cabeza;
        // Avanzar 'actual' MIENTRAS el siguiente exista Y el nuevo sea MENOS RECIENTE que el siguiente.
        while (actual->siguiente != NULL && esMasRecienteOIgual(actual->siguiente->datosDelMovimiento, mov)) {
            actual = actual->siguiente;
        }
        // Enganchar el nuevo nodo después de 'actual'.
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
}

// Muestra todos los movimientos usando la función del TDA Movimiento.
void mostrarTodaLaListaMov(ListaMovimientos lista) {
    NodoMovimiento *actual = lista.cabeza;
    printf("--- LISTA DE MOVIMIENTOS (Ordenados por fecha desc.) ---\n");
    if (isEmptyListaMov(lista)) {
        printf(" (La lista está vacía)\n");
        return;
    }
    while (actual != NULL) {
        mostrarMovimiento(actual->datosDelMovimiento); // Reutiliza la función del TDA Movimiento.
        printf("--------------------------\n");
        actual = actual->siguiente;
    }
    printf("--- FIN LISTA ---\n");
}

// Busca un movimiento por ID. Devuelve puntero al Movimiento o NULL.
Movimiento* buscarMovimientoPorId(ListaMovimientos lista, long int idBuscado) {
    NodoMovimiento *actual = lista.cabeza;
    while (actual != NULL) {
        if (actual->datosDelMovimiento.id_mov == idBuscado) {
            return &(actual->datosDelMovimiento); // Devuelve dirección del dato dentro del nodo.
        }
        actual = actual->siguiente;
    }
    return NULL; // No encontrado.
}

// Muestra los últimos 10 movimientos (o menos).
void mostrarUltimos10Movimientos(ListaMovimientos lista) {
    NodoMovimiento *actual = lista.cabeza;
    int contador = 0;

    printf("--- ÚLTIMOS 10 MOVIMIENTOS ---\n");
    if (isEmptyListaMov(lista)) {
        printf(" (No hay movimientos)\n");
        return;
    }
    while (actual != NULL && contador < 10) {
        mostrarMovimiento(actual->datosDelMovimiento);
        printf("--------------------------\n");
        actual = actual->siguiente;
        contador++;
    }
    printf("--- FIN ÚLTIMOS 10 ---\n");
}

// Busca por ID y modifica el motivo. Devuelve 1 si éxito, 0 si no.
int modificarMotivoPorId(ListaMovimientos lista, long int idBuscado, const char* nuevoMotivo) {
    Movimiento* movEncontrado = buscarMovimientoPorId(lista, idBuscado);
    if (movEncontrado != NULL) {
        modificarMotivo(movEncontrado, nuevoMotivo); // Llama a la función del TDA Movimiento
        return 1; // Éxito
    } else {
        return 0; // No encontrado
    }
}

// Busca por ID y anula el movimiento. Devuelve 1 si éxito, 0 si no.
int anularMovimientoPorId(ListaMovimientos lista, long int idBuscado) {
    Movimiento* movEncontrado = buscarMovimientoPorId(lista, idBuscado);
    if (movEncontrado != NULL) {
        modificarEstado(movEncontrado, ANULADO); // Llama a la función del TDA Movimiento
        return 1; // Éxito
    } else {
        return 0; // No encontrado
    }
}

// (Faltaría implementar funciones recursivas y de archivos aquí si las necesitaras en este TDA)

#endif // LISTAVO_MOVIMIENTO_H_INCLUDED

