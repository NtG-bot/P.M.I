// Archivo: listaE_Contacto.h
// --------------------------
// Define y implementa el TDA ListaContactosEstatica (Pila LIFO).
// *** Estructura con implementaci�n en .h seg�n indicaci�n de la c�tedra ***

#ifndef LISTAE_CONTACTO_H_INCLUDED
#define LISTAE_CONTACTO_H_INCLUDED

#include <stdio.h>    // Para printf, NULL
#include <string.h>   // Para strcpy
#include "contacto.h" // Necesitamos la definici�n de Contacto

// --- Constante para el tama�o M�XIMO del arreglo ---
#define MAX_CONTACTOS 100 // Tama�o fijo de la lista est�tica

// --- Definici�n de la Estructura de la Lista Est�tica ---
typedef struct {
    Contacto arrayContactos[MAX_CONTACTOS]; // Arreglo para guardar contactos
    int cantidad;                           // Cu�ntos contactos hay (funciona como tope + 1)
} ListaContactosEstatica;

// --- IMPLEMENTACI�N DE FUNCIONES DENTRO DEL .h ---

// Inicializa la lista est�tica para que est� vac�a.
void initListaContactosE(ListaContactosEstatica *lista) {
    lista->cantidad = 0; // Lista vac�a significa 0 elementos
}

// Verifica si la lista est�tica est� vac�a.
// Devuelve 1 si est� vac�a, 0 si no.
int isEmptyListaContactosE(ListaContactosEstatica lista) {
    return (lista.cantidad == 0);
}

// Verifica si la lista est�tica est� llena.
// Devuelve 1 si est� llena, 0 si no.
int isFullListaContactosE(ListaContactosEstatica lista) {
    return (lista.cantidad >= MAX_CONTACTOS); // Comprueba si ya se alcanz� el m�ximo
}

// Inserta un nuevo contacto en el tope de la pila (LIFO).
void insertContactoE(ListaContactosEstatica *lista, Contacto c) {
    // Verificar si hay espacio ANTES de insertar
    if (isFullListaContactosE(*lista)) {
        printf("Error: La lista de contactos est� llena. No se pudo insertar.\n");
        return; // Salir si est� llena
    }
    // Insertar en la posici�n indicada por 'cantidad'
    lista->arrayContactos[lista->cantidad] = c; // Copia la struct Contacto
    // Incrementar la cantidad DESPU�S de insertar
    lista->cantidad++;
}

// Elimina el contacto del tope de la pila (LIFO).
void suppressContactoE(ListaContactosEstatica *lista) {
    // Verificar si hay algo que eliminar ANTES
    if (isEmptyListaContactosE(*lista)) {
        printf("Advertencia: La lista de contactos est� vac�a. No se puede eliminar.\n");
        return; // Salir si est� vac�a
    }
    // "Eliminar" simplemente decrementando la cantidad.
    lista->cantidad--;
}

// Devuelve una copia del contacto que est� en el tope de la pila.
// PRECONDICI�N: La lista NO debe estar vac�a.
Contacto copyContactoE(ListaContactosEstatica lista) {
    // El tope est� en la posici�n cantidad - 1
    return lista.arrayContactos[lista.cantidad - 1];
}

// Muestra todos los contactos almacenados (del �ltimo insertado al primero - estilo LIFO).
void mostrarListaContactosE(ListaContactosEstatica lista) {
    int i;
    printf("--- Lista de Contactos (Pila - LIFO) ---\n");
    if (isEmptyListaContactosE(lista)) {
        printf(" (Lista vac�a)\n");
        return;
    }
    // Recorremos desde el tope (cantidad-1) hasta el fondo (0)
    for (i = lista.cantidad - 1; i >= 0; i--) {
        printf("Contacto en posicion %d (Tope=%d):\n", i, lista.cantidad-1);
        mostrarContacto(lista.arrayContactos[i]); // Reutiliza la funci�n del TDA Contacto
        printf("------------------------\n");
    }
    printf("--- Fin Lista Contactos ---\n");
}

#endif // LISTAE_CONTACTO_H_INCLUDED
