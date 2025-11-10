#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contacto.h"
#include "listaEContacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"
#define MI_ALIAS "Mi.alias.mp"

// - TAREA (a)
void funcion_realizar_movimiento() {
    char destino_temp[50], motivo_temp[100];
    int dia_temp, mes_temp;
    float monto_temp;
    int opcion_tipo_op, opcion_tipo_mov;
    char respuesta_agendar;
    char nombre_agendar_temp[50];
    int tipo_agendar_temp;

    printf("\n--- Nuevo Movimiento ---\n");
    
    // --- Pedir CBU/Alias ---
    printf("Ingrese CBU/Alias de destino: ");
    scanf(" %49[^\n]", destino_temp); // Lee hasta 49 chars, incluyendo espacios

    // --- Pedir Fecha ---
    // (Bucle de validación de fecha)
    do {
        printf("Ingrese la fecha (dd mm) [ej: 25 10]: ");
        scanf("%d %d", &dia_temp, &mes_temp);
        
        // (Aquí iría tu lógica de validación de fecha)
        // if (fecha_es_invalida) {
        //     printf("Error: La fecha debe ser entre 11/10/2025 y 31/12/2025.\n");
        // }
    } while (0); // (Pongo 0 para que no sea un bucle infinito, reemplazalo con tu lógica)

    // --- Pedir Monto ---
    printf("Ingrese el monto: ");
    scanf("%f", &monto_temp);

    // --- Limpiar buffer ANTES de leer un string después de un número ---
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    // --- Pedir Motivo ---
    printf("Ingrese el motivo (max 99 chars): ");
    scanf("%99[^\n]", motivo_temp); // Lee hasta 99 chars, incluyendo espacios

    // --- Pedir Tipo Operación ---
    printf("Seleccione Tipo Operacion (1:Debito, 2:Credito): ");
    scanf("%d", &opcion_tipo_op);

    // --- Pedir Tipo Movimiento ---
    printf("Seleccione Tipo Movimiento (1:Transf, 2:QR, 3:Serv, 4:Retiro): ");
    scanf("%d", &opcion_tipo_mov);

    // --- (Aquí iría tu lógica de validación de saldo) ---
    // if (opcion_tipo_op == 1 && monto_temp > saldo_billetera) {
    //     printf("\nError: Saldo insuficiente. Saldo actual: $%.2f\n", saldo_billetera);
    //     return; 
    // }

    // --- (Aquí iría tu lógica de búsqueda de contacto) ---
    // Contacto* contacto_encontrado = buscarContactoPorAlias(&miAgenda, destino_temp);
    // if (contacto_encontrado == NULL) {
        printf("El destinatario '%s' no está en su agenda.\n", destino_temp);
        printf("¿Desea agendarlo? (s/n): ");
        scanf(" %c", &respuesta_agendar);
        
        // if (respuesta_agendar == 's' || respuesta_agendar == 'S') {
            // (Aquí iría tu lógica de agenda llena)
            // if (isFullListaEs(miAgenda)) {
            //     printf("No se pudo agendar: Agenda llena.\n");
            // } else {
                printf("Ingrese nombre para el contacto (sin espacios): ");
                scanf("%49s", nombre_agendar_temp);
                printf("Ingrese Tipo (1:CA$, 2:CC$, 3:Billetera): ");
                scanf("%d", &tipo_agendar_temp);
                
                // (Aquí llamarías a los set_ y a InsertListaEs)
                
                printf("Contacto agendado.\n");
            // }
        // }
    // }

    // --- (Aquí iría toda la lógica final: set_movimiento, insertOrdenadoFecha, etc.) ---
    
    printf("Movimiento realizado con éxito.\n");
    // printf("Movimiento realizado. Saldo restante: $%.2f\n", saldo_billetera);
}




int main()
{
    Lista_contacto Lcontactos;
    Lista_movimiento LMovimientos;
    Movimiento NewMovimiento;
    Contacto NewContacto;
    int IDbus,opcion,opcion2;
    float Saldo_en_cuenta=100000;

do{
    switch(opcion){

    }


}while(opcion<=5);

    return 0;
}




