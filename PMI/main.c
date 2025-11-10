#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contacto.h"
#include "listaEContacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"

long int generarNuevoIdMovimiento() {
    static long int proximo_id = 1; // Se inicializa solo la primera vez EN ESTE ARCHIVO
    return proximo_id++;
}



int main()
{
    Lista_contacto Lcontactos;
    Lista_movimiento LMovimientos
    int IDbus,opcion,opcion2;

    printf("Hello world!\n");
    return 0;
}



