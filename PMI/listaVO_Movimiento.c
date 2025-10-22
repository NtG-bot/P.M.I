
/*
 * Archivo: listaVO_Movimiento.c
 * ----------------------------
 * Implementación de las funciones del TDA ListaMovimientos ordenado por fecha.
 */

#include <stdio.h>
#include <stdlib.h> // Para malloc() y free()
#include "listaVO_Movimiento.h" // Incluye la interfaz

// Inicializa la lista (cabeza a NULL).
void initListaMov(ListaMovimientos *lista) {
    lista->cabeza = NULL;
}

// Verifica si la lista está vacía.
int isEmptyListaMov(ListaMovimientos lista) {
    return (lista.cabeza == NULL);
}

// Compara dos fechas (devuelve 1 si fecha1 es más reciente o igual que fecha2, 0 si no).
// Función auxiliar para hacer más legible la inserción.
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
        printf("Error: No hay memoria para nuevo movimiento en la lista.\n");
        return;
    }
    nuevoNodo->datosDelMovimiento = mov;
    nuevoNodo->siguiente = NULL;

    // 2. Insertar.
    // Caso A: Lista vacía o el nuevo es MÁS RECIENTE que el primero actual.
    if (isEmptyListaMov(*lista) || esMasRecienteOIgual(mov, lista->cabeza->datosDelMovimiento)) {
        nuevoNodo->siguiente = lista->cabeza; // El nuevo apunta al antiguo primero.
        lista->cabeza = nuevoNodo;          // La cabeza ahora apunta al nuevo.
    }
    // Caso B: Insertar en medio o al final.
    else {
        NodoMovimiento *actual = lista->cabeza;
        // Avanzar 'actual' MIENTRAS el siguiente exista Y el nuevo sea MENOS RECIENTE que el siguiente.
        // Buscamos el nodo ANTERIOR a donde debemos insertar.
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

// Busca un movimiento por ID.
Movimiento* buscarMovimientoPorId(ListaMovimientos lista, long int idBuscado) {
    NodoMovimiento *actual = lista.cabeza;
    while (actual != NULL) {
        if (actual->datosDelMovimiento.id_mov == idBuscado) {
            return &(actual->datosDelMovimiento); // Devuelve puntero al dato dentro del nodo.
        }
        actual = actual->siguiente;
    }
    return NULL; // No encontrado.
}
