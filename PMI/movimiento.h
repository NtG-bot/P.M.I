/*
 * Archivo: movimiento.h
 * Define la interfaz del TDA Movimiento, utilizando solo conceptos
 * vistos en la c�tedra de Programaci�n I - UNSL.
 */

#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED

// --- Definici�n de Constantes Simb�licas ---
// Usamos #define para representar tipos y estados.
#define DEBITO 0
#define CREDITO 1

#define TRANSFERENCIA 10
#define PAGO_QR 11
#define PAGO_SERVICIO 12
#define RETIRA_EFECTIVO 13

#define OK 20
#define ANULADO 21

// --- Definici�n de la Estructura de Datos ---
typedef struct {
    long int id_mov;            // Identificador �nico (long int es suficiente).
    char cuenta_origen[50];     // CBU/Alias origen.
    char cuenta_destino[50];    // CBU/Alias destino.
    int tipo_operacion;         // Almacena DEBITO o CREDITO.
    int tipo_mov;               // Almacena TRANSFERENCIA, PAGO_QR, etc.
    double monto;               // Monto de la operaci�n.
    char motivo[100];           // Motivo (modificable).
    int dia;                    // Fecha (d�a y mes).
    int mes;
    int estado;                 // Almacena OK o ANULADO (modificable).
} Movimiento;


// --- Prototipos de las Operaciones ---
// Declaraciones de las funciones que se implementar�n en movimiento.c.

/** @brief Genera un ID �nico para un nuevo movimiento. */
long int generarNuevoIdMovimiento();

/** @brief Carga datos para un nuevo movimiento pidi�ndolos por teclado.
 * @param alias_origen_unipago El alias de la cuenta UniPago que realiza el movimiento.
 * @return Una variable Movimiento con los datos cargados. */
Movimiento cargarMovimiento(const char* alias_origen_unipago);

/** @brief Modifica el motivo de un movimiento existente.
 * @param mov Puntero al Movimiento a modificar.
 * @param nuevoMotivo El nuevo texto para el motivo. */
void modificarMotivo(Movimiento* mov, const char* nuevoMotivo);

/** @brief Modifica el estado de un movimiento existente (OK o ANULADO).
 * @param mov Puntero al Movimiento a modificar.
 * @param nuevoEstado El nuevo estado (usar las constantes OK o ANULADO). */
void modificarEstado(Movimiento* mov, int nuevoEstado);

/** @brief Muestra todos los datos de un movimiento en la consola.
 * @param mov El Movimiento a mostrar. */
void mostrarMovimiento(Movimiento mov);


#endif // MOVIMIENTO_H_INCLUDED
