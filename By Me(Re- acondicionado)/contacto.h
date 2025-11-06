#ifndef CONTACTO_H_INCLUDED
#define CONTACTO_H_INCLUDED
#include "malloc.h"
#include "string.h"

typedef struct{
char nombre[21];
char alias_cbu[23];
int tipo_cuenta;
} Contacto;

void set_alias_cbu(Contacto *l, int aliascbu){           //guarda la info de alias o CBU
    strcpy(l->alias_cbu,aliascbu);
}

char* get_alias_cbu(Contacto l){                  //devuelve la info de alias o CBU, corte copy
    char *aux = (char*)malloc(sizeof(strlen(l.alias_cbu) + 1));
    strcpy(aux,l.alias_cbu);
    return aux;
}

void set_nombre(Contacto *l, char nombre[]){             //lo mismo pero con el nombre
    strcpy(l->nombre, nombre);
}

char* get_nombre(Contacto l){                 //devuelve el nombre
    char *aux = (char*)malloc(sizeof(strlen(l.nombre) + 1));
    strcpy(aux, l.nombre);
    return aux;
}

void set_tipo_cuenta(Contacto *l, int cuenta){               //lo mismo pero con el tipo, recuerden que esta codificado
    l->tipo_cuenta = cuenta;
}

int get_tipo_cuenta(Contacto l){                    //devuelve tipo de cuenta
    return l.tipo_cuenta;
}

#endif // CONTACTO_H_INCLUDED
