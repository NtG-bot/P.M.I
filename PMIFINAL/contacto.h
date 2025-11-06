// Archivo: contacto.h
// -------------------
// TDA Contacto (Puro, sin printf/scanf)

#ifndef CONTACTO_H_INCLUDED
#define CONTACTO_H_INCLUDED

#include <stdlib.h>   // Para malloc, NULL
#include <string.h>   // Para strcpy, strlen

// --- Definición de la Estructura ---
typedef struct{
    char nombre[50];
    char alias_cbu[50];
    int tipo_cuenta; // 1:CA$, 2:CC$, 3:Billetera
} Contacto;

// --- Implementación de Funciones TDA ---

void set_alias_cbu(Contacto *c, const char aliascbu[]){
    strcpy(c->alias_cbu, aliascbu);
}

char* get_alias_cbu(Contacto c){
    // Devuelve una copia
    char *aux = (char*)malloc(strlen(c.alias_cbu) + 1); // CORREGIDO
    if(aux != NULL) {
        strcpy(aux, c.alias_cbu);
    }
    return aux;
}

void set_nombre(Contacto *c, const char nombre[]){
    strcpy(c->nombre, nombre);
}

char* get_nombre(Contacto c){
    // Devuelve una copia
    char *aux = (char*)malloc(strlen(c.nombre) + 1); // CORREGIDO
    if(aux != NULL) {
        strcpy(aux, c.nombre);
    }
    return aux;
}

void set_tipo_cuenta(Contacto *c, int cuenta){
    // Asumimos 1, 2, 3 son los tipos válidos
    if (cuenta >= 1 && cuenta <= 3) {
        c->tipo_cuenta = cuenta;
    } else {
        c->tipo_cuenta = 3; // Default a Billetera
    }
}

int get_tipo_cuenta(Contacto c){
    return c.tipo_cuenta;
}

#endif // CONTACTO_H_INCLUDED
