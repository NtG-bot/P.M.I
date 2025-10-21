#include <stdio.h>
#include "movimiento.h" // Incluimos la interfaz de nuestro TDA Movimiento

int main() {
    Movimiento unMovimiento; // Variable para guardar el movimiento
    char nuevoMotivo[100]; // Variable temporal para leer el nuevo motivo

    // Constante para el alias de UniPago, como pide el enunciado
    const char* MI_ALIAS_UNIPAGO = "mi.billetera.unipago";

    printf("--- Iniciando Prueba del TDA Movimiento ---\n");

    // 1. Cargar un movimiento usando la función del TDA
    printf("Por favor, ingrese los datos para un nuevo movimiento:\n");
    unMovimiento = cargarMovimiento(MI_ALIAS_UNIPAGO);

    // 2. Mostrar el movimiento cargado
    printf("\n--- Movimiento Cargado ---\n");
    mostrarMovimiento(unMovimiento);
    printf("--------------------------\n");

    // 3. Modificar el motivo
    printf("\nIngrese un nuevo motivo para el movimiento (ID: %ld): ", unMovimiento.id_mov);
    scanf(" %[^\n]", nuevoMotivo); // Leemos el nuevo motivo
    modificarMotivo(&unMovimiento, nuevoMotivo); // Llamamos a la función para modificar
                                                 // Pasamos la dirección (&) porque la función espera un puntero

    // 4. Modificar el estado (vamos a anularlo como ejemplo)
    printf("Anulando el movimiento...\n");
    modificarEstado(&unMovimiento, ANULADO); // Pasamos la dirección (&) y la constante ANULADO

    // 5. Mostrar el movimiento modificado
    printf("\n--- Movimiento Modificado ---\n");
    mostrarMovimiento(unMovimiento);
    printf("--------------------------\n");

    printf("\n--- Fin de la Prueba ---\n");

    return 0; // Indica que el programa terminó correctamente
}
