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
    Movimiento NewMovimiento;
    Contacto NewContacto;
    int IDbus,opcion,opcion2;
    float Saldo_en_cuenta;
    
    printf("Hello world!\n");
    return 0;
}
