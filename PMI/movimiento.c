/*
 * Archivo: movimiento.c
 * Implementación de las funciones del TDA Movimiento.
 */

#include <stdio.h>      // Para printf, scanf.
#include <string.h>     // Para strcpy (manejo de strings).
#include "movimiento.h" // Se incluye la propia interfaz.

// Genera IDs únicos usando una variable estática local.
long int generarNuevoIdMovimiento() {
    static long int proximo_id = 1; // Se inicializa solo la primera vez.
    return proximo_id++;            // Devuelve el ID actual y luego lo incrementa.
}

// Carga los datos de un movimiento pidiendo la información al usuario.
Movimiento cargarMovimiento(const char* alias_origen_unipago) {
    Movimiento nuevo_mov;
    int opcion_tipo_op, opcion_tipo_mov;

    // --- Carga automática ---
    nuevo_mov.id_mov = generarNuevoIdMovimiento(); // ID automático.
    strcpy(nuevo_mov.cuenta_origen, alias_origen_unipago); // Origen es nuestra cuenta.
    nuevo_mov.estado = OK; // Estado inicial es OK.

    // --- Petición de datos al usuario ---
    printf("--- Nuevo Movimiento (ID: %ld) ---\n", nuevo_mov.id_mov);
    printf("Ingrese CBU/Alias de destino: ");
    scanf("%49s", nuevo_mov.cuenta_destino); // %49s para evitar desbordamiento del array.

    // Validación de fecha.
    do {
        printf("Ingrese la fecha (dd mm) [ej: 25 10 para 25/Oct]: ");
        scanf("%d %d", &nuevo_mov.dia, &nuevo_mov.mes);
        // Verifica si la fecha es válida según las reglas del proyecto[cite: 6457].
        if (!((nuevo_mov.mes == 10 && nuevo_mov.dia > 10 && nuevo_mov.dia <= 31) ||
              (nuevo_mov.mes > 10 && nuevo_mov.mes <= 12 && nuevo_mov.dia >= 1 && nuevo_mov.dia <= 31))) {
             printf("Error: La fecha debe ser entre 11/10/2025 y 31/12/2025.\n");
        }
    } while (!((nuevo_mov.mes == 10 && nuevo_mov.dia > 10 && nuevo_mov.dia <= 31) ||
               (nuevo_mov.mes > 10 && nuevo_mov.mes <= 12 && nuevo_mov.dia >= 1 && nuevo_mov.dia <= 31)));

    printf("Ingrese el monto: ");
    scanf("%lf", &nuevo_mov.monto); // %lf para leer un double.

    printf("Ingrese el motivo (puede usar '_' para espacios, max 99 chars): ");
    scanf(" %[^\n]s", nuevo_mov.motivo); // %99s para evitar desbordamiento.

    // Selección de tipo de operación.
    printf("Seleccione el Tipo de Operacion:\n");
    printf("  %d - Debito (Dinero que sale)\n", DEBITO);
    printf("  %d - Credito (Dinero que entra)\n", CREDITO);
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_op);
    nuevo_mov.tipo_operacion = (opcion_tipo_op == CREDITO) ? CREDITO : DEBITO; // Asigna DEBITO por defecto si no es CREDITO.

    // Selección de tipo de movimiento.
    printf("Seleccione el Tipo de Movimiento:\n");
    printf("  %d - Transferencia\n", TRANSFERENCIA);
    printf("  %d - Pago con QR\n", PAGO_QR);
    printf("  %d - Pago de Servicio\n", PAGO_SERVICIO);
    printf("  %d - Retiro de Efectivo\n", RETIRA_EFECTIVO);
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_mov);
    // Asigna el tipo elegido o TRANSFERENCIA por defecto si la opción no es válida.
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
    // Se usa '->' para acceder al campo a través del puntero[cite: 5240].
    // strcpy copia la cadena 'nuevoMotivo' en el campo 'motivo' de la estructura apuntada por 'mov'[cite: 392].
    strcpy(mov->motivo, nuevoMotivo);
}

// Modifica el estado (usa puntero).
void modificarEstado(Movimiento* mov, int nuevoEstado) {
    // Asigna el nuevo estado (OK o ANULADO) al campo 'estado'.
    mov->estado = nuevoEstado;
}

// Muestra los datos del movimiento formateados.
void mostrarMovimiento(Movimiento mov) {
    // Se recibe 'mov' por valor, ya que solo se lee[cite: 5110].
    printf("ID Movimiento: %ld\n", mov.id_mov); // %ld para long int.
    printf("  Fecha: %02d/%02d/2025\n", mov.dia, mov.mes); // %02d para mostrar siempre 2 dígitos (ej: 05).
    printf("  Origen: %s\n", mov.cuenta_origen);
    printf("  Destino: %s\n", mov.cuenta_destino);

    // Muestra el tipo de movimiento como texto.
    printf("  Tipo Mov: ");
    switch(mov.tipo_mov) {
        case TRANSFERENCIA: printf("Transferencia\n"); break;
        case PAGO_QR: printf("Pago QR\n"); break;
        case PAGO_SERVICIO: printf("Pago Servicio\n"); break;
        case RETIRA_EFECTIVO: printf("Retiro Efectivo\n"); break;
        default: printf("Desconocido\n"); break;
    }

    // Muestra el monto con signo + o -[cite: 6463, 6464].
    if (mov.tipo_operacion == DEBITO) {
        printf("  Monto: -$%.2f\n", mov.monto); // %.2f para mostrar 2 decimales.
    } else {
        printf("  Monto: +$%.2f\n", mov.monto);
    }

    printf("  Motivo: %s\n", mov.motivo);

    // Muestra el estado como texto.
    printf("  Estado: %s\n", (mov.estado == OK) ? "OK" : "Anulado");
}
