// Archivo: listaE_Contacto.h
// --------------------------
// TDA Lista Estática de Contactos (Lógica Híbrida PMI, Puro)

#ifndef LISTAE_CONTACTO_H_INCLUDED
#define LISTAE_CONTACTO_H_INCLUDED

#include <stdio.h>    // Para NULL
#include <string.h>   // Para strcmp
#include "contacto.h" // Necesita la struct Contacto

#define MAX_CONTACTOS 100 // Constante de tamaño

// ESTRUCTURA CORREGIDA
typedef struct{
    Contacto arrayContactos[MAX_CONTACTOS]; // Un ARREGLO
    int ultimo; // Índice del último elemento (-1 si está vacía)
    int cur;    // Índice del cursor (para ops de lista)
} Lista_contactos;

// --- IMPLEMENTACIÓN DE FUNCIONES EN .h ---

void InitListaEs(Lista_contactos *l){
    l->ultimo = -1;
    l->cur = -1;
}

int IsEmptyListaEs(Lista_contactos l){
    return (l.ultimo == -1); // CORREGIDO
}

int isFullListaEs(Lista_contactos l){
    return (l.ultimo == MAX_CONTACTOS - 1); // CORREGIDO
}

int IsOosListaEs(Lista_contactos l){
    return (l->cur < 0 || l->cur > l->ultimo); // CORREGIDO
}

void ResetListaEs(Lista_contactos *l){
    if (IsEmptyListaEs(*l)) {
        l->cur = -1;
    } else {
        l->cur = 0; // Cursor al primer elemento
    }
}

void ForwardsListaEs(Lista_contactos *l){
    if (l->cur < l->ultimo) {
        l->cur++;
    } else {
        l->cur = -1; // Se fue "Out of Structure"
    }
}

Contacto CopyListaEs(Lista_contactos l){
    // (Asumimos que !IsOosListaEs(l) se chequeó en main)
    return l.arrayContactos[l.cur];
}

[cite_start]// INSERCIÓN TIPO PILA (PMI Punto D) [cite: 3466-3468]
// Inserta al final, ignora el cursor 'cur'.
void InsertListaEs(Lista_contactos *l, Contacto a){
    if (isFullListaEs(*l)) {
        return; // Error, lista llena (TDA mudo)
    }
    l->ultimo++;
    l->arrayContactos[l->ultimo] = a;
    l->cur = l->ultimo;
}

// SUPPRESS TIPO LISTA (PMI Punto D)
// Elimina en la posición del cursor 'cur' y desplaza.
void SupressListaEs(Lista_contactos *l){
    if (IsEmptyListaEs(*l) || IsOosListaEs(*l)) {
        return; // No se puede suprimir
    }

    int i;
    for(i = l->cur; i < l->ultimo; i++){
        l->arrayContactos[i] = l->arrayContactos[i + 1];
    }
    l->ultimo--;

    if (l->cur > l->ultimo && !IsEmptyListaEs(*l)) {
        l->cur = l->ultimo;
    } else if (IsEmptyListaEs(*l)) {
        InitListaEs(l);
    }
}

// Función de Búsqueda (necesaria para el main)
// Devuelve un puntero al contacto si lo encuentra, o NULL
Contacto* buscarContactoPorAlias(Lista_contactos *l, const char* alias_cbu) {
    int i;
    for (i = 0; i <= l->ultimo; i++) {
        if (strcmp(l->arrayContactos[i].alias_cbu, alias_cbu) == 0) {
            return &(l->arrayContactos[i]); // Devuelve la dirección
        }
    }
    return NULL; // No se encontró
}

#endif // LISTAE_CONTACTO_H_INCLUDED
