#ifndef CONTACTO_H_INCLUDED
#define CONTACTO_H_INCLUDED
#include "malloc.h"
#include "string.h"

typedef struct{
char nombre[21];
char alias_cbu[23];
int tipo_cuenta;
} Contacto;

void set_alias_cbu(Lista_contactos *l, int aliascbu){           //guarda la info de alias o CBU
    strcpy(l->contactos[l->cur].alias_cbu,aliascbu);
}

char* get_alias_cbu(Lista_contactos l){                  //devuelve la info de alias o CBU, corte copy
    char *aux = (char*)malloc(sizeof(strlen(l->contactos[l->cur].alias_cbu) + 1));
    strcpy(aux, l->contactos[l->cur].alias_cbu);
    return aux;
}

void set_nombre(Lista_contactos *l, char nombre[]){             //lo mismo pero con el nombre
    strcpy(l->contactos[l->cur].nombre, nombre);
}

char* get_nombre(Lista_contactos l){                 //devuelve el nombre
    char *aux = (char*)malloc(sizeof(strlen(l->contactos[l->cur].nombre) + 1));
    strcpy(aux, l->contactos[l->cur].nombre);
    return aux;
}

void set_tipo_cuenta(Lista_contactos *l, int cuenta){               //lo mismo pero con el tipo, recuerden que esta codificado
    l->contactos[l->cur].tipo_cuenta = cuenta;
}

int get_tipo_cuenta(Lista_contactos l){                    //devuelve tipo de cuenta
    return l->contactos[l->cur].tipo_cuenta;
}

#endif // CONTACTO_H_INCLUDED
