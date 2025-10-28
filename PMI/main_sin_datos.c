#include <stdio.h>
#include <string.h>
#include "contacto.h"
#include "listaE_Contacto.h" // Incluye la lista ESTÁTICA de contactos (Pila)
#include "movimiento.h"
#include "listaVO_Movimiento.h" // Incluye la lista DINÁMICA ORDENADA de movimientos

// --- Variables Globales ---
ListaContactosEstatica miAgenda;
ListaMovimientos miBilletera;
const char* MI_ALIAS_UNIPAGO = "mi.unipago.sl";

// --- Función Principal ---
int main() {
    int opcion;
    Contacto nuevo_contacto;
    Movimiento nuevo_movimiento;
    long int id_buscar;
    char nuevo_motivo[100];

    // Inicializar ambas listas
    initListaContactosE(&miAgenda);
    initListaMov(&miBilletera);

    do {
        // Mostrar Menú
        printf("\n--- Billetera UniPago --- (Interactivo)\n");
        printf("1. Agregar Contacto\n");
        printf("2. Mostrar Contactos (Pila)\n");
        printf("3. Realizar Movimiento\n");
        printf("4. Mostrar Todos los Movimientos (Ordenados)\n");
        printf("5. Mostrar Últimos 10 Movimientos\n");
        printf("6. Modificar Motivo de Movimiento por ID\n");
        printf("7. Anular Movimiento por ID\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (isFullListaContactosE(miAgenda)) {
                    printf("La agenda está llena.\n");
                } else {
                    nuevo_contacto = cargarNuevoContacto(); // Llama a la función de carga
                    insertContactoE(&miAgenda, nuevo_contacto); // Inserta en la pila
                }
                break;
            case 2:
                mostrarListaContactosE(miAgenda);
                break;
            case 3:
                // Aquí faltaría la lógica de verificar saldo antes de cargar y guardar
                nuevo_movimiento = cargarMovimiento(MI_ALIAS_UNIPAGO); // Llama a la función de carga
                insertOrdenadoFecha(&miBilletera, nuevo_movimiento); // Inserta en la lista ordenada
                break;
            case 4:
                mostrarTodaLaListaMov(miBilletera);
                break;
            case 5:
                mostrarUltimos10Movimientos(miBilletera);
                break;
            case 6:
                printf("Ingrese ID del movimiento a modificar: ");
                scanf("%ld", &id_buscar);
                printf("Ingrese nuevo motivo (use '_'): ");
                scanf("%99s", nuevo_motivo);
                if (modificarMotivoPorId(miBilletera, id_buscar, nuevo_motivo)) {
                    printf("Motivo modificado.\n");
                } else {
                    printf("ID no encontrado.\n");
                }
                break;
            case 7:
                printf("Ingrese ID del movimiento a anular: ");
                scanf("%ld", &id_buscar);
                if (anularMovimientoPorId(miBilletera, id_buscar)) {
                    printf("Movimiento anulado.\n");
                } else {
                    printf("ID no encontrado.\n");
                }
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida.\n");
                break;
        }
    } while (opcion != 0);

    // Liberar memoria de la lista dinámica
    // freeListaMov(&miBilletera); // <-- Necesitarías implementar esta función

    return 0;
}
