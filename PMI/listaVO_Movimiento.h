/*
 * Archivo: listaVO_Movimiento.h
 * ----------------------------
 * Define la interfaz del TDA ListaMovimientos.
 * Es una lista enlazada dinámica, ordenada por fecha (más reciente primero).
 */

#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED

#include "movimiento.h" // Necesitamos la definición de 'Movimiento'

// --- Estructura del Nodo ---
typedef struct NodoMovimiento {
    Movimiento datosDelMovimiento;
    struct NodoMovimiento *siguiente; // Puntero al próximo nodo
} NodoMovimiento;

// --- Estructura de la Lista ---
typedef struct {
    NodoMovimiento *cabeza; // Puntero al primer nodo de la lista
} ListaMovimientos;


// --- Prototipos de las Operaciones ---

/** @brief Inicializa la lista para que esté vacía. */
void initListaMov(ListaMovimientos *lista);

/** @brief Verifica si la lista no tiene movimientos.
 * @return 1 si está vacía, 0 si tiene al menos uno. */
int isEmptyListaMov(ListaMovimientos lista);

/** @brief Inserta un movimiento en la lista manteniendo el orden por fecha
 * (de más reciente a más antiguo). */
void insertOrdenadoFecha(ListaMovimientos *lista, Movimiento mov);

/** @brief Muestra todos los movimientos de la lista. */
void mostrarTodaLaListaMov(ListaMovimientos lista);

/** @brief Busca un movimiento por su ID.
 * @return Un puntero al Movimiento si se encuentra, NULL si no. */
Movimiento* buscarMovimientoPorId(ListaMovimientos lista, long int idBuscado);

// (Aquí podrías agregar más prototipos si necesitás, como eliminar, etc.)


#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
