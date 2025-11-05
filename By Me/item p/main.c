#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct{
    char nombre[21];
    char alias_cbu[23];
    int tipo_cuenta;
} Contacto;

typedef struct {
    Contacto contactos[MAX];
    int tope;
} ListaE_Contacto;

void precargarContactos(ListaE_Contacto *lista) {
    lista->tope = 0;

    /*Contacto 1*/
    strcpy(lista->contactos[lista->tope].nombre, "Pilar");
    strcpy(lista->contactos[lista->tope].alias_cbu, "gomitas.fanta.bdolca");
    lista->contactos[lista->tope].tipo_cuenta = 1;
    lista->tope++;

    /*Contacto 2*/
    strcpy(lista->contactos[lista->tope].nombre, "Axel");
    strcpy(lista->contactos[lista->tope].alias_cbu, "ntg3003");
    lista->contactos[lista->tope].tipo_cuenta = 2;
    lista->tope++;

    /*Contacto 3*/
    strcpy(lista->contactos[lista->tope].nombre, "Josefina");
    strcpy(lista->contactos[lista->tope].alias_cbu, "buteler05");
    lista->contactos[lista->tope].tipo_cuenta = 2;
    lista->tope++;

    /*Contacto 4*/
    strcpy(lista->contactos[lista->tope].nombre, "Daniel");
    strcpy(lista->contactos[lista->tope].alias_cbu, "cadaro1074");
    lista->contactos[lista->tope].tipo_cuenta = 3;
    lista->tope++;

    /*Contacto 5*/
    strcpy(lista->contactos[lista->tope].nombre, "Eugenia");
    strcpy(lista->contactos[lista->tope].alias_cbu, "eugebut300524");
    lista->contactos[lista->tope].tipo_cuenta = 1;
    lista->tope++;

     printf("Precarga de contactos realizada correctamente (%d contactos)\n", lista->tope);
}

int main() {
    ListaE_Contacto listaContactos;
    precargarContactos(&listaContactos);
    printf("\n Contactos precargados \n");
    for (int i = 0; i < listaContactos.tope; i++) {
        printf("%d,%s,%s,%d\n");
               i + 1;
               (listaContactos.contactos[i].nombre);
               (listaContactos.contactos[i].alias_cbu);
               (listaContactos.contactos[i].tipo_cuenta);
    }
}
