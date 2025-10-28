//#include <stdio.h>
//#include <string.h> // Necesario para strcpy en la creación simulada de movimientos
//#include "movimiento.h"         // Incluimos el TDA Movimiento
//#include "listaVO_Movimiento.h" // Incluimos el TDA ListaMovimientos
//
//int main() {
//    ListaMovimientos miBilletera; // Variable principal para nuestra lista
//    Movimiento mov1, mov2, mov3, mov4, mov5; // Variables para crear movimientos
//    Movimiento* movEncontrado; // Puntero para usar con la búsqueda
//
//    // Constante para el alias, como pide el proyecto
//    const char* MI_ALIAS_UNIPAGO = "unipago.alias.propio";
//
//    printf("--- INICIO: Prueba Integrada TDA Movimiento y ListaMovimientos ---\n");
//
//    // 1. Inicializar la lista
//    initListaMov(&miBilletera);
//    printf("Lista inicializada.\n");
//    mostrarTodaLaListaMov(miBilletera); // Debería mostrar que está vacía
//
//    // 2. Crear movimientos simulados con fechas desordenadas
//    printf("\n--- Creando movimientos de ejemplo ---\n");
//    // (Usamos strcpy y asignación directa para simular la carga)
//    mov1.id_mov = generarNuevoIdMovimiento(); strcpy(mov1.cuenta_origen, MI_ALIAS_UNIPAGO); strcpy(mov1.cuenta_destino, "supermercado"); mov1.tipo_operacion = DEBITO; mov1.tipo_mov = PAGO_QR; mov1.monto = 150.75; mov1.dia = 15; mov1.mes = 10; mov1.estado = OK; strcpy(mov1.motivo, "Compras_mes");
//    mov2.id_mov = generarNuevoIdMovimiento(); strcpy(mov2.cuenta_origen, MI_ALIAS_UNIPAGO); strcpy(mov2.cuenta_destino, "empresa_luz"); mov2.tipo_operacion = DEBITO; mov2.tipo_mov = PAGO_SERVICIO; mov2.monto = 85.50; mov2.dia = 5; mov2.mes = 11; mov2.estado = OK; strcpy(mov2.motivo, "Factura_Luz");
//    mov3.id_mov = generarNuevoIdMovimiento(); strcpy(mov3.cuenta_origen, "cuenta_amigo"); strcpy(mov3.cuenta_destino, MI_ALIAS_UNIPAGO); mov3.tipo_operacion = CREDITO; mov3.tipo_mov = TRANSFERENCIA; mov3.monto = 200.00; mov3.dia = 20; mov3.mes = 10; mov3.estado = OK; strcpy(mov3.motivo, "Devolucion_prestamo");
//    mov4.id_mov = generarNuevoIdMovimiento(); strcpy(mov4.cuenta_origen, MI_ALIAS_UNIPAGO); strcpy(mov4.cuenta_destino, "cine"); mov4.tipo_operacion = DEBITO; mov4.tipo_mov = PAGO_QR; mov4.monto = 40.00; mov4.dia = 4; mov4.mes = 11; mov4.estado = OK; strcpy(mov4.motivo, "Entradas_cine");
//    mov5.id_mov = generarNuevoIdMovimiento(); strcpy(mov5.cuenta_origen, MI_ALIAS_UNIPAGO); strcpy(mov5.cuenta_destino, "cajero_automatico"); mov5.tipo_operacion = DEBITO; mov5.tipo_mov = RETIRA_EFECTIVO; mov5.monto = 100.00; mov5.dia = 21; mov5.mes = 10; mov5.estado = OK; strcpy(mov5.motivo, "Retiro_finde");
//
//    printf("Movimientos creados (IDs 1 a 5).\n");
//
//    // 3. Insertar movimientos en la lista
//    printf("\n--- Insertando movimientos en la lista (ordenados por fecha) ---\n");
//    insertOrdenadoFecha(&miBilletera, mov1); // 15/10
//    insertOrdenadoFecha(&miBilletera, mov2); // 05/11
//    insertOrdenadoFecha(&miBilletera, mov3); // 20/10
//    insertOrdenadoFecha(&miBilletera, mov4); // 04/11
//    insertOrdenadoFecha(&miBilletera, mov5); // 21/10
//
//    // 4. Mostrar la lista completa (verificar orden)
//    printf("\n--- Mostrando lista completa ordenada ---\n");
//    mostrarTodaLaListaMov(miBilletera);
//    // Orden esperado: 05/11 (ID 2), 04/11 (ID 4), 21/10 (ID 5), 20/10 (ID 3), 15/10 (ID 1)
//
//    // 5. Mostrar últimos 10 (en este caso, los 5 que hay)
//    printf("\n--- Mostrando últimos 10 movimientos ---\n");
//    mostrarUltimos10Movimientos(miBilletera);
//
//    // 6. Buscar un movimiento por ID
//    printf("\n--- Buscando movimiento con ID 3 ---\n");
//    movEncontrado = buscarMovimientoPorId(miBilletera, 3);
//    if (movEncontrado != NULL) {
//        printf("Movimiento ID 3 encontrado:\n");
//        mostrarMovimiento(*movEncontrado); // Mostrarlo usando la función del TDA Movimiento
//    } else {
//        printf("Movimiento con ID 3 NO encontrado.\n");
//    }
//
//    // 7. Modificar motivo por ID
//    printf("\n--- Modificando motivo del ID 4 a 'Entradas_Cine_Estreno' ---\n");
//    if (modificarMotivoPorId(miBilletera, 4, "Entradas_Cine_Estreno")) {
//        printf("Motivo del ID 4 modificado.\n");
//    } else {
//        printf("ID 4 no encontrado para modificar.\n");
//    }
//
//    // 8. Anular movimiento por ID
//    printf("\n--- Anulando movimiento con ID 1 (Compras_mes) ---\n");
//    if (anularMovimientoPorId(miBilletera, 1)) {
//        printf("Movimiento ID 1 anulado.\n");
//    } else {
//        printf("ID 1 no encontrado para anular.\n");
//    }
//
//    // 9. Mostrar lista final con cambios
//    printf("\n--- Mostrando lista final con modificaciones ---\n");
//    mostrarTodaLaListaMov(miBilletera); // Verificar motivo cambiado en ID 4 y estado Anulado en ID 1
//
//    // 10. Intentar anular un ID que no existe
//    printf("\n--- Intentando anular movimiento con ID 99 (no existe) ---\n");
//    if (!anularMovimientoPorId(miBilletera, 99)) {
//        printf("Correcto: No se encontró el ID 99 para anular.\n");
//    }
//
//    // (Aquí faltaría liberar la memoria de la lista si tuviéramos una función para eso)
//
//    printf("\n--- Fin de la Prueba Integrada ---\n");
//    return 0;
//}
