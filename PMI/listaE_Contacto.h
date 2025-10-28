// Archivo: listaE_Contacto.h
// --------------------------
// Define y implementa el TDA ListaContactosEstatica (Pila LIFO).
// *** Estructura con implementación en .h según indicación de la cátedra ***

#ifndef LISTAE_CONTACTO_H_INCLUDED
#define LISTAE_CONTACTO_H_INCLUDED

#include <stdio.h>    // Para printf, NULL
#include <string.h>   // Para strcpy
#include "contacto.h" // Necesitamos la definición de Contacto

// --- Constante para el tamaño MÁXIMO del arreglo ---
#define MAX_CONTACTOS 100 // Tamaño fijo de la lista estática

// --- Definición de la Estructura de la Lista Estática ---
typedef struct {
    Contacto arrayContactos[MAX_CONTACTOS]; // Arreglo para guardar contactos
    int cantidad;                           // Cuántos contactos hay (funciona como tope + 1)
} ListaContactosEstatica;

// --- IMPLEMENTACIÓN DE FUNCIONES DENTRO DEL .h ---

// Inicializa la lista estática para que esté vacía.
void initListaContactosE(ListaContactosEstatica *lista) {
    lista->cantidad = 0; // Lista vacía significa 0 elementos
}

// Verifica si la lista estática está vacía.
// Devuelve 1 si está vacía, 0 si no.
int isEmptyListaContactosE(ListaContactosEstatica lista) {
    return (lista.cantidad == 0);
}

// Verifica si la lista estática está llena.
// Devuelve 1 si está llena, 0 si no.
int isFullListaContactosE(ListaContactosEstatica lista) {
    return (lista.cantidad >= MAX_CONTACTOS); // Comprueba si ya se alcanzó el máximo
}

// Inserta un nuevo contacto en el tope de la pila (LIFO).
void insertContactoE(ListaContactosEstatica *lista, Contacto c) {
    // Verificar si hay espacio ANTES de insertar
    if (isFullListaContactosE(*lista)) {
        printf("Error: La lista de contactos está llena. No se pudo insertar.\n");
        return; // Salir si está llena
    }
    // Insertar en la posición indicada por 'cantidad'
    lista->arrayContactos[lista->cantidad] = c; // Copia la struct Contacto
    // Incrementar la cantidad DESPUÉS de insertar
    lista->cantidad++;
}

// Elimina el contacto del tope de la pila (LIFO).
void suppressContactoE(ListaContactosEstatica *lista) {
    // Verificar si hay algo que eliminar ANTES
    if (isEmptyListaContactosE(*lista)) {
        printf("Advertencia: La lista de contactos está vacía. No se puede eliminar.\n");
        return; // Salir si está vacía
    }
    // "Eliminar" simplemente decrementando la cantidad.
    lista->cantidad--;
}

// Devuelve una copia del contacto que está en el tope de la pila.
// PRECONDICIÓN: La lista NO debe estar vacía.
Contacto copyContactoE(ListaContactosEstatica lista) {
    // El tope está en la posición cantidad - 1
    return lista.arrayContactos[lista.cantidad - 1];
}

// Muestra todos los contactos almacenados (del último insertado al primero - estilo LIFO).
void mostrarListaContactosE(ListaContactosEstatica lista) {
    int i;
    printf("--- Lista de Contactos (Pila - LIFO) ---\n");
    if (isEmptyListaContactosE(lista)) {
        printf(" (Lista vacía)\n");
        return;
    }
    // Recorremos desde el tope (cantidad-1) hasta el fondo (0)
    for (i = lista.cantidad - 1; i >= 0; i--) {
        printf("Contacto en posicion %d (Tope=%d):\n", i, lista.cantidad-1);
        mostrarContacto(lista.arrayContactos[i]); // Reutiliza la función del TDA Contacto
        printf("------------------------\n");
    }
    printf("--- Fin Lista Contactos ---\n");
}

#endif // LISTAE_CONTACTO_H_INCLUDED
