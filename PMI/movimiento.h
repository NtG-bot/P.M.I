// Archivo: movimiento.h
// -------------------
// Define y implementa el TDA Movimiento.
// *** Estructura con implementación en .h según indicación de la cátedra ***

#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

#include <stdio.h>      // Para printf, scanf
#include <string.h>     // Para strcpy

// --- Definición de Constantes Simbólicas ---
#define DEBITO 0
#define CREDITO 1

#define TRANSFERENCIA 10
#define PAGO_QR 11
#define PAGO_SERVICIO 12
#define RETIRA_EFECTIVO 13

#define OK 20
#define ANULADO 21

// --- Definición de la Estructura de Datos ---
typedef struct {
    long int id_mov;            // Identificador único
    char cuenta_origen[50];     // CBU/Alias origen
    char cuenta_destino[50];    // CBU/Alias destino
    int tipo_operacion;         // DEBITO o CREDITO
    int tipo_mov;               // TRANSFERENCIA, PAGO_QR, etc.
    double monto;               // Monto
    char motivo[100];           // Motivo (modificable)
    int dia;                    // Fecha
    int mes;
    int estado;                 // OK o ANULADO (modificable)
} Movimiento;

// --- IMPLEMENTACIÓN DE FUNCIONES DENTRO DEL .h ---

// Genera IDs únicos usando una variable estática local.
// ¡OJO! Problema si se incluye en varios .c -> múltiples contadores!
long int generarNuevoIdMovimiento() {
    static long int proximo_id = 1; // Se inicializa solo la primera vez EN ESTE ARCHIVO
    return proximo_id++;
}

// Carga los datos de un movimiento pidiendo la información al usuario.
Movimiento cargarMovimiento(const char* alias_origen_unipago) {
    Movimiento nuevo_mov;
    int opcion_tipo_op, opcion_tipo_mov;

    // --- Carga automática ---
    nuevo_mov.id_mov = generarNuevoIdMovimiento();
    strcpy(nuevo_mov.cuenta_origen, alias_origen_unipago);
    nuevo_mov.estado = OK;

    // --- Petición de datos al usuario ---
    printf("--- Nuevo Movimiento (ID: %ld) ---\n", nuevo_mov.id_mov);
    printf("Ingrese CBU/Alias de destino: ");
    scanf("%49s", nuevo_mov.cuenta_destino);

    // Validación de fecha.
    do {
        printf("Ingrese la fecha (dd mm) [ej: 25 10 para 25/Oct]: ");
        scanf("%d %d", &nuevo_mov.dia, &nuevo_mov.mes);
        if (!((nuevo_mov.mes == 10 && nuevo_mov.dia > 10 && nuevo_mov.dia <= 31) ||
              (nuevo_mov.mes > 10 && nuevo_mov.mes <= 12 && nuevo_mov.dia >= 1 && nuevo_mov.dia <= 31))) {
             printf("Error: La fecha debe ser entre 11/10/2025 y 31/12/2025.\n");
        }
    } while (!((nuevo_mov.mes == 10 && nuevo_mov.dia > 10 && nuevo_mov.dia <= 31) ||
               (nuevo_mov.mes > 10 && nuevo_mov.mes <= 12 && nuevo_mov.dia >= 1 && nuevo_mov.dia <= 31)));

    printf("Ingrese el monto: ");
    scanf("%lf", &nuevo_mov.monto);

    printf("Ingrese el motivo (use '_' para espacios, max 99 chars): ");
    scanf("%99s", nuevo_mov.motivo);

    // Selección de tipo de operación.
    printf("Seleccione el Tipo de Operacion:\n");
    printf("  %d - Debito (Sale)\n", DEBITO);
    printf("  %d - Credito (Entra)\n", CREDITO);
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_op);
    nuevo_mov.tipo_operacion = (opcion_tipo_op == CREDITO) ? CREDITO : DEBITO;

    // Selección de tipo de movimiento.
    printf("Seleccione el Tipo de Movimiento:\n");
    printf("  %d - Transferencia\n", TRANSFERENCIA);
    printf("  %d - Pago con QR\n", PAGO_QR);
    printf("  %d - Pago de Servicio\n", PAGO_SERVICIO);
    printf("  %d - Retiro de Efectivo\n", RETIRA_EFECTIVO);
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_mov);
    switch(opcion_tipo_mov) {
        case PAGO_QR: nuevo_mov.tipo_mov = PAGO_QR; break;
        case PAGO_SERVICIO: nuevo_mov.tipo_mov = PAGO_SERVICIO; break;
        case RETIRA_EFECTIVO: nuevo_mov.tipo_mov = RETIRA_EFECTIVO; break;
        default: nuevo_mov.tipo_mov = TRANSFERENCIA; break;
    }

    printf("Movimiento cargado con exito.\n\n");
    return nuevo_mov;
}

// Modifica el motivo (usa puntero y strcpy).
void modificarMotivo(Movimiento* mov, const char* nuevoMotivo) {
    strcpy(mov->motivo, nuevoMotivo);
}

// Modifica el estado (usa puntero).
void modificarEstado(Movimiento* mov, int nuevoEstado) {
    mov->estado = nuevoEstado;
}

// Muestra los datos del movimiento formateados.
void mostrarMovimiento(Movimiento mov) {
    printf("ID Movimiento: %ld\n", mov.id_mov);
    printf("  Fecha: %02d/%02d/2025\n", mov.dia, mov.mes);
    printf("  Origen: %s\n", mov.cuenta_origen);
    printf("  Destino: %s\n", mov.cuenta_destino);
    printf("  Tipo Mov: ");
    switch(mov.tipo_mov) {
        case TRANSFERENCIA: printf("Transferencia\n"); break;
        case PAGO_QR: printf("Pago QR\n"); break;
        case PAGO_SERVICIO: printf("Pago Servicio\n"); break;
        case RETIRA_EFECTIVO: printf("Retiro Efectivo\n"); break;
        default: printf("Desconocido\n"); break;
    }
    if (mov.tipo_operacion == DEBITO) {
        printf("  Monto: -$%.2f\n", mov.monto);
    } else {
        printf("  Monto: +$%.2f\n", mov.monto);
    }
    printf("  Motivo: %s\n", mov.motivo);
    printf("  Estado: %s\n", (mov.estado == OK) ? "OK" : "Anulado");
}

#endif // MOVIMIENTO_H_INCLUDED
