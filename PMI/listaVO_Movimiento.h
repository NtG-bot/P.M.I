/*
 * Archivo: listaVO_Movimiento.h
 * ----------------------------
 * Define la interfaz del TDA ListaMovimientos.
 * Es una lista enlazada din�mica, ordenada por fecha (m�s reciente primero).
 */

#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED

#include "movimiento.h" // Necesitamos la definici�n de 'Movimiento'

// --- Estructura del Nodo ---
typedef struct NodoMovimiento {
    Movimiento datosDelMovimiento;
    struct NodoMovimiento *siguiente; // Puntero al pr�ximo nodo
} NodoMovimiento;

// --- Estructura de la Lista ---
typedef struct {
    NodoMovimiento *cabeza; // Puntero al primer nodo de la lista
} ListaMovimientos;


// --- Prototipos de las Operaciones ---

/** @brief Inicializa la lista para que est� vac�a. */
void initListaMov(ListaMovimientos *lista);

/** @brief Verifica si la lista no tiene movimientos.
 * @return 1 si est� vac�a, 0 si tiene al menos uno. */
int isEmptyListaMov(ListaMovimientos lista);

/** @brief Inserta un movimiento en la lista manteniendo el orden por fecha
 * (de m�s reciente a m�s antiguo). */
void insertOrdenadoFecha(ListaMovimientos *lista, Movimiento mov);

/** @brief Muestra todos los movimientos de la lista. */
void mostrarTodaLaListaMov(ListaMovimientos lista);

/** @brief Busca un movimiento por su ID.
 * @return Un puntero al Movimiento si se encuentra, NULL si no. */
Movimiento* buscarMovimientoPorId(ListaMovimientos lista, long int idBuscado);

// (Aqu� podr�as agregar m�s prototipos si necesit�s, como eliminar, etc.)


#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
