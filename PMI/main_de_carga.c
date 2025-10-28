//#include <stdio.h>
//#include <string.h> // Para strcpy en la precarga
//#include "contacto.h"
//#include "listaE_Contacto.h" // Incluye la lista ESTÁTICA de contactos (Pila)
//#include "movimiento.h"
//#include "listaVO_Movimiento.h" // Incluye la lista DINÁMICA ORDENADA de movimientos
//
//// --- Variables Globales para las listas (simplifica el paso a funciones) ---
//ListaContactosEstatica miAgenda;
//ListaMovimientos miBilletera;
//const char* MI_ALIAS_UNIPAGO = "mi.unipago.sl"; // Alias de nuestra billetera
//
//// --- Función de Precarga ---
//void precargarDatos() {
//    printf("Precargando datos de ejemplo...\n");
//
//    // Precarga Contactos (se insertan como Pila: el último insertado queda al tope)
//    Contacto c1 = {"Juan_Perez", "juan.perez.alias", BILLETERA_VIRTUAL};
//    Contacto c2 = {"Maria_Lopez", "0011223344556677889900", CAJA_AHORRO_PESOS};
//    Contacto c3 = {"Carlos_Garcia", "carlos.garcia.mp", BILLETERA_VIRTUAL};
//    insertContactoE(&miAgenda, c1); // Fondo
//    insertContactoE(&miAgenda, c2); // Medio
//    insertContactoE(&miAgenda, c3); // Tope
//
//    // Precarga Movimientos (se insertan ordenados por fecha)
//    Movimiento m1 = {generarNuevoIdMovimiento(), "mi.unipago.sl", "supermercado", DEBITO, PAGO_QR, 150.75, "Compras", 15, 10, OK};
//    Movimiento m2 = {generarNuevoIdMovimiento(), "mi.unipago.sl", "empresa_luz", DEBITO, PAGO_SERVICIO, 85.50, "Factura_Luz", 5, 11, OK};
//    Movimiento m3 = {generarNuevoIdMovimiento(), "cuenta_amigo", "mi.unipago.sl", CREDITO, TRANSFERENCIA, 200.00, "Devolucion", 20, 10, OK};
//    Movimiento m4 = {generarNuevoIdMovimiento(), "mi.unipago.sl", "cine", DEBITO, PAGO_QR, 40.00, "Entradas", 4, 11, OK};
//    insertOrdenadoFecha(&miBilletera, m1); // 15/10
//    insertOrdenadoFecha(&miBilletera, m2); // 05/11
//    insertOrdenadoFecha(&miBilletera, m3); // 20/10
//    insertOrdenadoFecha(&miBilletera, m4); // 04/11
//
//    printf("Datos precargados.\n\n");
//}
//
//
//// --- Función Principal ---
//int main() {
//    int opcion;
//    long int id_buscar;
//    char nuevo_motivo[100];
//
//    // Inicializar ambas listas
//    initListaContactosE(&miAgenda);
//    initListaMov(&miBilletera);
//
//    // Cargar datos de ejemplo
//    precargarDatos();
//
//    do {
//        // Mostrar Menú
//        printf("\n--- Billetera UniPago --- (Precargado)\n");
//        printf("1. Mostrar Contactos (Pila)\n");
//        printf("2. Mostrar Todos los Movimientos (Ordenados)\n");
//        printf("3. Mostrar Últimos 10 Movimientos\n");
//        printf("4. Modificar Motivo de Movimiento por ID\n");
//        printf("5. Anular Movimiento por ID\n");
//        printf("0. Salir\n");
//        printf("Seleccione una opción: ");
//        scanf("%d", &opcion);
//
//        switch (opcion) {
//            case 1:
//                mostrarListaContactosE(miAgenda);
//                break;
//            case 2:
//                mostrarTodaLaListaMov(miBilletera);
//                break;
//            case 3:
//                mostrarUltimos10Movimientos(miBilletera);
//                break;
//            case 4:
//                printf("Ingrese ID del movimiento a modificar: ");
//                scanf("%ld", &id_buscar);
//                printf("Ingrese nuevo motivo (use '_'): ");
//                scanf("%99s", nuevo_motivo);
//                if (modificarMotivoPorId(miBilletera, id_buscar, nuevo_motivo)) {
//                    printf("Motivo modificado.\n");
//                } else {
//                    printf("ID no encontrado.\n");
//                }
//                break;
//            case 5:
//                printf("Ingrese ID del movimiento a anular: ");
//                scanf("%ld", &id_buscar);
//                if (anularMovimientoPorId(miBilletera, id_buscar)) {
//                    printf("Movimiento anulado.\n");
//                } else {
//                    printf("ID no encontrado.\n");
//                }
//                break;
//            case 0:
//                printf("Saliendo...\n");
//                break;
//            default:
//                printf("Opción no válida.\n");
//                break;
//        }
//    } while (opcion != 0);
//
//    // Liberar memoria de la lista dinámica (si tuviéramos la función suppress/destroy)
//    // freeListaMov(&miBilletera); // <-- Necesitarías implementar esta función
//
//    return 0;
//}
