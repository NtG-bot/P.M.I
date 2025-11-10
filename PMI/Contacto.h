#ifndef CONTACTO_H_INCLUDED
#define CONTACTO_H_INCLUDED
#include "string.h"

typedef struct{
char nombre[22];
char alias_cbu[33];
int tipo_cuenta;
}Contacto;

void set_nombre_contacto(Contacto *c, char nombre[]){
    strcpy(c->nombre, nombre);
}

char* get_nombre_contacto(Contacto c){
    char *aux = (char*)malloc(strlen(c.nombre)+ 1);
    strcpy(aux, c.nombre);
    return aux;
}

void set_alias_contacto(Contacto *c, char alias[]){
    strcpy(c->alias_cbu, alias);
}

char* get_alias_contacto(Contacto c){
    char *aux = (char*)malloc(strlen(c.alias_cbu)+ 1);
    strcpy(aux, c.alias_cbu);
    return aux;
}

void set_tipo_cuenta_contacto(Contacto *c, int tipocuenta){
    c->tipo_cuenta = tipocuenta;
}

int get_tipo_cuenta_contacto(Contacto c){
    return c.tipo_cuenta;
}

#endif // CONTACTO_H_INCLUDED
