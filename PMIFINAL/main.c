#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contacto.h"
#include "ListaEContacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"

#define MI_ALIAS "mi.alias.mp"

// ===================================================================
// PROTOTIPOS (TODAS LAS TAREAS - TDA SEGUROS)
// ===================================================================

// --- Tareas de MODIFICACIÓN (usan Puntero *) ---
int busaca_alias(Lista_contactos *l, char alias[]);
void realizar_movimiento(Lista_movimiento *LMovimientos, Lista_contactos *LContactos, float *Saldo_en_cuenta, int *proximo_id_ptr);
int funcion_buscarMovimientoPorId(Lista_movimiento *LMovimientos, int idBuscado); // (b) Devuelve 1 o 0
void funcion_ingresarRetirarDinero(Lista_movimiento *LMovimientos, Lista_contactos *LContactos, float *Saldo_en_cuenta, int *proximo_id_ptr);
void funcion_modificarMotivoPorNombre(Lista_movimiento *LMovimientos, Lista_contactos *LContactos);
void funcion_eliminarAnulados(Lista_movimiento *LMovimientos);
void funcion_precarga_movimientos(Lista_movimiento *LMovimientos, int *proximo_id_ptr, float *Saldo_en_cuenta); // (s) Modificado
void modifica_motivo_por_id(Lista_movimiento *l, int id);
void anularMovimientoPorId(Lista_movimiento *m, int idBuscado, float *Saldo_en_cuenta);
void carga_contacto_teclado(Lista_contactos *l, Contacto *c);
void eliminarContactoPorAlias(Lista_contactos *c);
void precargarContactos(Lista_contactos *c);
void funcion_descargarMovimientos(Lista_movimiento *LMovimientos); // (n)

// --- Tareas de SÓLO LECTURA (usan Valor, sin *) ---
void funcion_mostrarMovimientoBuscado(Lista_movimiento LMovimientos); // (c)
void funcion_mostrarUltimos10(Lista_movimiento LMovimientos); // (e)
void funcion_mostrar_movimientos(Lista_movimiento LMovimientos); // (f)
void muestra_lista_mov_anulados(Lista_movimiento m); // (j)
void mostrar_mayores_A_350mil(Lista_movimiento m); // (l)
void funcion_contarMovsContacto(Lista_movimiento LMovimientos); // (m)
void mostrarContactos(Lista_contactos c); // (q)
void funcion_calcularMontoMes(Lista_movimiento LMovimientos); // (r)


// ===================================================================
// FUNCION MAIN (Con Menú Anidado y Controles)
// ===================================================================
int main()
{
    Lista_contactos LContactos;
    Lista_movimiento LMovimientos;
    float Saldo_en_cuenta = 100000;
    int proximo_id = 1;
    int opcion = -1;
    int opcion2 = -1;

    init_lista_estatica(&LContactos);
    init_lista_movimiento(&LMovimientos);

    // (Llamada a precarga (p) y (s) al inicio)
    // (Si te sacan las precargas, el 'if (isempty...)' te salva)
    precargarContactos(&LContactos);
    funcion_precarga_movimientos(&LMovimientos, &proximo_id, &Saldo_en_cuenta); // Modificado

    do {
        printf("\n\n====== BILLETERA VIRTUAL (Menu Principal) ======\n");
        printf("Saldo Actual: $%.2f\n", Saldo_en_cuenta);
        printf("--------------------------------------------------\n");
        printf(" 1. Gestionar Movimientos\n");
        printf(" 2. Gestionar Contactos\n");
        printf(" 0. Salir\n");
        printf("--------------------------------------------------\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
             int c; while ((c = getchar()) != '\n' && c != EOF); opcion = -1;
        }

        switch (opcion) {
            // --- CASO 1: SUB-MENÚ DE MOVIMIENTOS ---
            case 1: {
                do {
                    printf("\n--- Gestion de Movimientos ---\n");
                    printf(" 1. Realizar Movimiento (a)\n");
                    printf(" 2. Ingresar/Retirar Dinero (d)\n");
                    printf(" 3. Mostrar Historial (f)\n");
                    printf(" 4. Mostrar Ultimos 10 Movs (e)\n");
                    printf(" 5. Buscar Movimiento (c)\n");
                    printf(" 6. Anular Movimiento por ID (i)\n");
                    printf(" 7. Modificar Motivo por ID (g)\n");
                    printf(" 8. Modificar Motivo por Nombre (h)\n");
                    printf(" 9. Listar Movs Anulados (j)\n");
                    printf(" 10. Eliminar Anulados (k)\n");
                    printf(" 11. Mostrar Movs > 350k (l)\n");
                    printf(" 12. Contar Movs a Contacto (m)\n");
                    printf(" 13. Descargar Historial (n)\n");
                    printf(" 14. Calcular Monto por Mes (r)\n");
                    printf(" 0. Volver al menu principal\n");
                    printf("--------------------------------\n");
                    printf("Opcion: ");

                    if (scanf("%d", &opcion2) != 1) {
                         int c; while ((c = getchar()) != '\n' && c != EOF); opcion2 = -1;
                    }

                    // --- SWITCH MOVIMIENTOS (CON CONTROLES DE LISTA VACIA) ---
                    switch(opcion2) {
                        // Casos de ESCRITURA (pasan puntero &)
                        case 1: realizar_movimiento(&LMovimientos, &LContactos, &Saldo_en_cuenta, &proximo_id); break;
                        case 2: funcion_ingresarRetirarDinero(&LMovimientos, &LContactos, &Saldo_en_cuenta, &proximo_id); break;
                        case 6: {
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else { int id; printf("Ingrese ID a anular: "); scanf("%d", &id); anularMovimientoPorId(&LMovimientos, id, &Saldo_en_cuenta); }
                            break;
                        }
                        case 7: {
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else { int id; printf("Ingrese ID: "); scanf("%d", &id); modifica_motivo_por_id(&LMovimientos, id); }
                            break;
                        }
                        case 8:
                            if (isempty_lista_movimiento(LMovimientos) || isempty_lista_estatica(LContactos)) printf("Error: No hay movimientos o contactos.\n");
                            else funcion_modificarMotivoPorNombre(&LMovimientos, &LContactos);
                            break;
                        case 10:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_eliminarAnulados(&LMovimientos);
                            break;
                        case 13:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_descargarMovimientos(&LMovimientos);
                            break;

                        // Casos de LECTURA (pasan valor, sin &)
                        case 3:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_mostrar_movimientos(LMovimientos);
                            break;
                        case 4:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_mostrarUltimos10(LMovimientos);
                            break;
                        case 5:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_mostrarMovimientoBuscado(LMovimientos);
                            break;
                        case 9:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else muestra_lista_mov_anulados(LMovimientos);
                            break;
                        case 11:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else mostrar_mayores_A_350mil(LMovimientos);
                            break;
                        case 12:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_contarMovsContacto(LMovimientos);
                            break;
                        case 14:
                            if (isempty_lista_movimiento(LMovimientos)) printf("Error: No hay movimientos.\n");
                            else funcion_calcularMontoMes(LMovimientos);
                            break;

                        case 0: printf("Volviendo al menu principal...\n"); break;
                        default: printf("Opcion invalida.\n"); break;
                    }
                } while (opcion2 != 0);
                break;
            }

            // --- CASO 2: SUB-MENÚ DE CONTACTOS ---
            case 2: {
                 do {
                    printf("\n--- Gestion de Contactos ---\n");
                    printf(" 1. Cargar Contacto (nh)\n");
                    printf(" 2. Mostrar Contactos (q)\n");
                    printf(" 3. Eliminar Contacto (o)\n");
                    printf(" 0. Volver al menu principal\n");
                    printf("----------------------------\n");
                    printf("Opcion: ");

                    if (scanf("%d", &opcion2) != 1) {
                         int c; while ((c = getchar()) != '\n' && c != EOF); opcion2 = -1;
                    }

                    switch(opcion2) {
                        case 1: {
                            if (isfull_lista_estatica(LContactos)) printf("Error: Agenda llena.\n");
                            else { Contacto nuevoC; carga_contacto_teclado(&LContactos, &nuevoC); }
                            break;
                        }
                        case 2:
                            if (isempty_lista_estatica(LContactos)) printf("Error: No hay contactos.\n");
                            else mostrarContactos(LContactos); // Pasa por valor
                            break;
                        case 3:
                            if (isempty_lista_estatica(LContactos)) printf("Error: No hay contactos.\n");
                            else eliminarContactoPorAlias(&LContactos); // Pasa por puntero
                            break;
                        case 0: printf("Volviendo al menu principal...\n"); break;
                        default: printf("Opcion invalida.\n"); break;
                    }
                } while (opcion2 != 0);
                break;
            }

            // --- CASO 0: SALIR ---
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

    reset_lista_movimiento(&LMovimientos);
    while (!isempty_lista_movimiento(LMovimientos)) {
        suppress_lista_movimiento(&LMovimientos);
    }
    printf("Memoria liberada. Adios.\n");
    return 0;
}

// ===================================================================
// DEFINICION DE FUNCIONES DE TAREAS (A-S)
// ===================================================================

// TAREA (a) Realizar Movimiento
void realizar_movimiento(Lista_movimiento *LMovimientos, Lista_contactos *LContactos, float *Saldo_en_cuenta, int *proximo_id_ptr) {
    Movimiento NewMovimiento;
    Contacto temp_contacto;
    char destino_temp[50], motivo_temp[100], nombre_agendar_temp[50];
    int dia_temp, mes_temp, opcion_tipo_op, opcion_tipo_mov, tipo_agendar_temp;
    float monto_temp;
    char respuesta_agendar;

    printf("\n--- Nuevo Movimiento ---\n");
    printf("Ingrese CBU/Alias de destino: ");
    scanf(" %49[^\n]", destino_temp);

    int fchainvalida = 0;
    do {
        printf("Ingrese la fecha (dd mm): ");
        scanf("%d %d", &dia_temp, &mes_temp);
        if ((mes_temp < 10 || mes_temp > 12) || (dia_temp < 1 || dia_temp > 31) || (mes_temp == 10 && dia_temp <= 10)) {
            printf("Error: La fecha debe ser mayor a 10/10/2025 y menor a 01/01/2026.\n");
            fchainvalida = 0;
        } else { fchainvalida = 1; }
    } while (fchainvalida == 0);

    printf("Seleccione Tipo Movimiento (1:Transf, 2:QR, 3:Pago Servi, 4:Retiro): ");
    scanf("%d", &opcion_tipo_mov);

    if (opcion_tipo_mov == 4) {
        printf("Aviso: 'Retiro' seleccionado. La operacion se forzara a 'Debito'.\n");
        opcion_tipo_op = 1;
    } else {
        printf("Seleccione Tipo Operacion (1:Debito, 2:Credito): ");
        scanf("%d", &opcion_tipo_op);
    }

    int monto_valido = 0;
    do {
        printf("Ingrese el monto: ");
        scanf("%f", &monto_temp);
        if (opcion_tipo_op == 1 && monto_temp > *Saldo_en_cuenta) {
            printf("\nError: Saldo insuficiente. Saldo actual: $%.2f\n", *Saldo_en_cuenta);
            monto_valido = 0;
        } else { monto_valido = 1; }
    } while (monto_valido == 0);

    int c; while ((c = getchar()) != '\n' && c != EOF);
    printf("Ingrese el motivo (max 99 chars): ");
    scanf("%99[^\n]", motivo_temp);

    // Usa la función 'buscarContactoPorAlias' que SÍ es TDA-Segura
    if (busaca_alias(LContactos, destino_temp) == 0) { // 0 = No encontrado
        printf("El destinatario '%s' no está en su agenda.\n", destino_temp);
        printf("¿Desea agendarlo? (s/n): ");
        scanf(" %c", &respuesta_agendar);

        if (respuesta_agendar == 's' || respuesta_agendar == 'S') {
            if (isfull_lista_estatica(*LContactos)) {
                printf("No se pudo agendar: Agenda llena.\n");
            } else {
                printf("Ingrese nombre para el contacto (sin espacios): ");
                scanf("%49s", nombre_agendar_temp);
                printf("Ingrese Tipo (1:CA$, 2:CC$, 3:Billetera): ");
                scanf("%d", &tipo_agendar_temp);

                set_nombre_contacto(&temp_contacto, nombre_agendar_temp);
                set_alias_contacto(&temp_contacto, destino_temp);
                set_tipo_cuenta_contacto(&temp_contacto, tipo_agendar_temp);
                insert_lista_estatica(LContactos, temp_contacto);
                printf("Contacto agendado.\n");
            }
        }
    }

    set_id_mov(&NewMovimiento, *proximo_id_ptr);
    (*proximo_id_ptr)++;
    set_fecha_dia(&NewMovimiento, dia_temp);
    set_fecha_mes(&NewMovimiento, mes_temp);
    set_monto(&NewMovimiento, monto_temp);
    set_motivo(&NewMovimiento, motivo_temp);
    set_cuenta_origen(&NewMovimiento, MI_ALIAS);
    set_cuenta_destino(&NewMovimiento, destino_temp);
    set_tipo_operacion(&NewMovimiento, opcion_tipo_op);
    set_tipo_mov(&NewMovimiento, opcion_tipo_mov);
    set_estado(&NewMovimiento, 1);

    funcion_insertOrdenadoFecha(LMovimientos, NewMovimiento);

    if (opcion_tipo_op == 1) { *Saldo_en_cuenta -= monto_temp; }
    else { *Saldo_en_cuenta += monto_temp; }

    printf("Movimiento realizado con éxito. Saldo restante: $%.2f\n", *Saldo_en_cuenta);
}

// TAREA (f) Mostrar todos los Movimientos (TDA-SEGURO)
void funcion_mostrar_movimientos(Lista_movimiento LMovimientos) {
    printf("\n--- Historial de Movimientos ---\n");

    reset_lista_movimiento(&LMovimientos);
    int contador = 0;
    while (!isOos_lista_movimiento(LMovimientos)) {
        Movimiento mov = copy_list_movimiento(LMovimientos);
        char signo = (get_tipo_operacion(mov) == 1) ? '-' : '+';

        printf("----------------------------------\n");
        printf("  ID Movimiento: %d\n", get_id_mov(mov));
        printf("  Fecha:         %d/%d\n", get_fecha_dia(mov), get_fecha_mes(mov));

        printf("  Operacion:     ");
        if (get_tipo_operacion(mov) == 1) printf("Debito (%c)\n", signo);
        else printf("Credito (%c)\n", signo);

        printf("  Monto:         $%.2f\n", get_monto(mov));
        printf("  Motivo:        %s\n", get_motivo(mov));
        printf("  Origen:        %s\n", get_cuenta_origen(mov));
        printf("  Destino:       %s\n", get_cuenta_destino(mov));

        printf("  Tipo Mov:      ");
        switch(get_tipo_mov(mov)){
            case 1: printf("Transferencia\n"); break;
            case 2: printf("Pago QR\n"); break;
            case 3: printf("Servicio\n"); break;
            case 4: printf("Retiro/Ingreso\n"); break;
            default: printf("N/A\n");
        }

        printf("  Estado:        ");
        if (get_estado(mov) == 1) printf("OK\n");
        else printf("Anulado\n");

        forward_lista_movimiento(&LMovimientos);
        contador++;
    }
    if (contador == 0) printf("No hay movimientos para mostrar.\n");
}

// TAREA (b) Buscar Movimiento por ID (TDA-SEGURO)
// Devuelve 1 si lo encuentra y posiciona el cursor, 0 si no.
int funcion_buscarMovimientoPorId(Lista_movimiento *LMovimientos, int idBuscado) {
    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        Movimiento m = copy_list_movimiento(*LMovimientos);
        if (get_id_mov(m) == idBuscado) {
            return 1; // Encontrado, cursor posicionado
        }
        forward_lista_movimiento(LMovimientos);
    }
    return 0; // No encontrado
}

// TAREA (c) Mostrar Movimiento Buscado (TDA-SEGURO)
void funcion_mostrarMovimientoBuscado(Lista_movimiento LMovimientos) {
    int id;
    printf("Ingrese ID a buscar: "); scanf("%d", &id);

    if(funcion_buscarMovimientoPorId(&LMovimientos, id) == 1){
        Movimiento mov = copy_list_movimiento(LMovimientos);
        char signo = (get_tipo_operacion(mov) == 1) ? '-' : '+';

        printf("\n--- Movimiento Encontrado ---\n");
        printf("  ID Movimiento: %d\n", get_id_mov(mov));
        printf("  Fecha:         %d/%d\n", get_fecha_dia(mov), get_fecha_mes(mov));

        printf("  Operacion:     ");
        if (get_tipo_operacion(mov) == 1) printf("Debito (%c)\n", signo);
        else printf("Credito (%c)\n", signo);

        printf("  Monto:         $%.2f\n", get_monto(mov));
        printf("  Motivo:        %s\n", get_motivo(mov));
        printf("  Origen:        %s\n", get_cuenta_origen(mov));
        printf("  Destino:       %s\n", get_cuenta_destino(mov));

        printf("  Tipo Mov:      ");
        switch(get_tipo_mov(mov)){
            case 1: printf("Transferencia\n"); break;
            case 2: printf("Pago QR\n"); break;
            case 3: printf("Servicio\n"); break;
            case 4: printf("Retiro/Ingreso\n"); break;
            default: printf("N/A\n");
        }

        printf("  Estado:        ");
        if (get_estado(mov) == 1) printf("OK\n");
        else printf("Anulado\n");
        printf("----------------------------------\n");

    } else {
        printf("Movimiento no encontrado.\n");
    }
}

// TAREA (d) Ingresar o Retirar Dinero
void funcion_ingresarRetirarDinero(Lista_movimiento *LMovimientos, Lista_contactos *LContactos, float *Saldo_en_cuenta, int *proximo_id_ptr) {
    int opcion, fchainvalida = 0, dia_temp, mes_temp;
    float monto;
    Movimiento nuevo_mov;

    printf("--- Ingresar o Retirar Dinero ---\n");
    printf("1. Ingresar\n2. Retirar\nSeleccione: ");
    scanf("%d", &opcion);

    printf("Ingrese el monto: ");
    scanf("%f", &monto);

    if (opcion == 2 && monto > *Saldo_en_cuenta) {
        printf("Error: Saldo insuficiente.\n");
        return;
    }

    do {
        printf("Ingrese la fecha (dd mm): ");
        scanf("%d %d", &dia_temp, &mes_temp);
        if ((mes_temp < 10 || mes_temp > 12) || (dia_temp < 1 || dia_temp > 31) || (mes_temp == 10 && dia_temp <= 10)) {
            printf("Error: Fecha inválida.\n"); fchainvalida = 0;
        } else { fchainvalida = 1; }
    } while (fchainvalida == 0);

    set_id_mov(&nuevo_mov, *proximo_id_ptr); (*proximo_id_ptr)++;
    set_fecha_dia(&nuevo_mov, dia_temp);
    set_fecha_mes(&nuevo_mov, mes_temp);
    set_monto(&nuevo_mov, monto);
    set_estado(&nuevo_mov, 1);
    set_tipo_mov(&nuevo_mov, 4);
    set_cuenta_origen(&nuevo_mov, MI_ALIAS);

    if (opcion == 2) {
        *Saldo_en_cuenta -= monto;
        set_motivo(&nuevo_mov, "Retiro_en_efectivo");
        set_tipo_operacion(&nuevo_mov, 1);
        set_cuenta_destino(&nuevo_mov, "Cajero");
    } else {
        *Saldo_en_cuenta += monto;
        set_motivo(&nuevo_mov, "Ingreso_de_fondos");
        set_tipo_operacion(&nuevo_mov, 2);
        set_cuenta_destino(&nuevo_mov, "Ventanilla");
    }

    funcion_insertOrdenadoFecha(LMovimientos, nuevo_mov);
    printf("Operación exitosa. Nuevo saldo: $%.2f\n", *Saldo_en_cuenta);
}

// TAREA (e) Mostrar los últimos 10 movimientos
void funcion_mostrarUltimos10(Lista_movimiento LMovimientos) {
    printf("\n--- Ultimos 10 Movimientos ---\n");

    reset_lista_movimiento(&LMovimientos);
    int i = 1;
    while (!isOos_lista_movimiento(LMovimientos) && i <= 10) {
        Movimiento mov = copy_list_movimiento(LMovimientos);
        char signo = (get_tipo_operacion(mov) == 1) ? '-' : '+';

        printf("-------------------\n");
        printf(" %d. (ID: %d) - Fecha: %d/%d\n", i, get_id_mov(mov), get_fecha_dia(mov), get_fecha_mes(mov));
        printf("    Monto: %c $%.2f\n", signo, get_monto(mov));
        printf("    Motivo: %s\n", get_motivo(mov));
        printf("    Destino: %s\n", get_cuenta_destino(mov));

        forward_lista_movimiento(&LMovimientos);
        i++;
    }
}

// TAREA (h) Modificar Motivo por Nombre (TDA-SEGURO)
void funcion_modificarMotivoPorNombre(Lista_movimiento *LMovimientos, Lista_contactos *LContactos) {
    char nombre[50], cbu[50] = "", nuevo_mot[100];
    int encontrado = 0;
    printf("Nombre del contacto: "); scanf("%49s", nombre);

    // 1. Buscar el CBU del contacto (TDA-SEGURO)
    Lista_contactos copia_contactos = *LContactos;
    reset_lista_estatica(&copia_contactos);
    while(!isOos_lista_estatica(copia_contactos)){
        Contacto c = copy_lista_estatica(copia_contactos);
        if(strcmp(get_nombre_contacto(c), nombre) == 0){
            strcpy(cbu, get_alias_contacto(c));
            encontrado = 1;
            break;
        }
        forward_lista_estatica(&copia_contactos);
    }

    if (!encontrado) { printf("Contacto no encontrado.\n"); return; }

    // 2. Recorrer la lista de movimientos (TDA-SEGURO)
    reset_lista_movimiento(LMovimientos);
    int modificados = 0;
    while (!isOos_lista_movimiento(*LMovimientos)) {

        Movimiento mov_copia = copy_list_movimiento(*LMovimientos);

        if (strcmp(get_cuenta_destino(mov_copia), cbu) == 0) {
            printf("ID %d. Motivo actual: %s. Nuevo motivo: ", get_id_mov(mov_copia), get_motivo(mov_copia));
            int ch; while ((ch = getchar()) != '\n' && ch != EOF);
            scanf("%99[^\n]", nuevo_mot);

            // TDA-SEGURO: Borrar y re-insertar
            set_motivo(&mov_copia, nuevo_mot);
            suppress_lista_movimiento(LMovimientos);
            funcion_insertOrdenadoFecha(LMovimientos, mov_copia);
            modificados++;
        } else {
             forward_lista_movimiento(LMovimientos);
        }
    }
    if (modificados > 0) printf("%d movimientos modificados.\n", modificados);
    else printf("No se encontraron movimientos para ese contacto.\n");
}

// TAREA (k) Eliminar Anulados
void funcion_eliminarAnulados(Lista_movimiento *LMovimientos) {
    char confirma;
    printf("¿Seguro que desea eliminar PERMANENTEMENTE los movs anulados? (s/n): ");
    scanf(" %c", &confirma);
    if (confirma != 's' && confirma != 'S') {
        printf("Operación cancelada.\n"); return;
    }

    FILE *f = fopen("anulados.txt", "w");
    if (!f) { printf("Error al abrir anulados.txt\n"); return; }

    fprintf(f, "--- MOVIMIENTOS ANULADOS ELIMINADOS ---\n");
    int contador = 0;

    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        Movimiento m = copy_list_movimiento(*LMovimientos);
        if (get_estado(m) == 2) {
            fprintf(f, "------------------\n");
            fprintf(f, "ID: %d\n", get_id_mov(m));
            fprintf(f, "Fecha: %d/%d\n", get_fecha_dia(m), get_fecha_mes(m));
            fprintf(f, "Monto: %.2f\n", get_monto(m));
            fprintf(f, "Motivo: %s\n", get_motivo(m));
            fprintf(f, "Destino: %s\n", get_cuenta_destino(m));

            suppress_lista_movimiento(LMovimientos);
            contador++;
        } else {
            forward_lista_movimiento(LMovimientos);
        }
    }
    fclose(f);
    printf("%d anulados eliminados y guardados en 'anulados.txt'.\n", contador);
}

// TAREA (m) Contar Movs (Recursivo TDA-SEGURO)
int _funcion_contarRecursivo(Lista_movimiento l, const char* cbu) {
    if (isOos_lista_movimiento(l)) {
        return 0;
    }

    Movimiento m = copy_list_movimiento(l);
    forward_lista_movimiento(&l);

    int resto = _funcion_contarRecursivo(l, cbu);

    if (strcmp(get_cuenta_destino(m), cbu) == 0) {
        return 1 + resto;
    } else {
        return 0 + resto;
    }
}
void funcion_contarMovsContacto(Lista_movimiento LMovimientos) {
    char cbu[50];
    printf("Ingrese CBU/Alias: "); scanf("%49s", cbu);

    reset_lista_movimiento(&LMovimientos);
    printf("Total movimientos: %d\n", _funcion_contarRecursivo(LMovimientos, cbu));
}

// TAREA (n) Descargar movimientos a historicos.txt
void funcion_descargarMovimientos(Lista_movimiento *LMovimientos_ptr) {
    Lista_movimiento l = *LMovimientos_ptr;

    int mes1, mes2, contador_copiados = 0;
    printf("--- Descargar Movimientos por Rango ---\n");
    printf("Ingrese mes de INICIO (10, 11 o 12): ");
    scanf("%d", &mes1);
    printf("Ingrese mes de FIN (10, 11 o 12): ");
    scanf("%d", &mes2);

    if (mes1 < 10 || mes2 > 12 || mes2 < mes1) {
        printf("Error: Rango de meses inválido.\n");
        return;
    }

    FILE *puntero = fopen("historicos.txt", "w");
    if (puntero == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    }

    fprintf(puntero, "%-10s | %-15s | %-15s | %-10s | %-40s | %s\n",
            "Fecha", "Operacion", "Movimiento", "Monto", "Motivo", "Estado");

    reset_lista_movimiento(&l);
    while (!isOos_lista_movimiento(l)) {
        Movimiento aux = copy_list_movimiento(l);

        if (get_fecha_mes(aux) >= mes1 && get_fecha_mes(aux) <= mes2) {
            char tipo_operacion[10];
            if (get_tipo_operacion(aux) == 1){ strcpy(tipo_operacion, "Debito"); }
            else { strcpy(tipo_operacion, "Credito"); }

            char tipo_movimiento[18];
            switch(get_tipo_mov(aux)) {
                case 1: strcpy(tipo_movimiento, "Transferencia"); break;
                case 2: strcpy(tipo_movimiento, "Pago QR"); break;
                case 3: strcpy(tipo_movimiento, "Servicio"); break;
                case 4: strcpy(tipo_movimiento, "Retiro"); break;
                default: strcpy(tipo_movimiento, "Desconocido"); break;
            }

            char tipo_estado[8];
            if (get_estado(aux) == 1){ strcpy(tipo_estado, "Ok"); }
            else { strcpy(tipo_estado, "Anulado"); }

            fprintf(puntero, "%02d/%02d     | %-15s | %-15s | $%-9.2f| %-40s | %s\n",
                    get_fecha_dia(aux), get_fecha_mes(aux),
                    tipo_operacion, tipo_movimiento, get_monto(aux), get_motivo(aux), tipo_estado);
            contador_copiados++;
        }
        forward_lista_movimiento(&l);
    }

    fclose(puntero);
    printf("\nProceso completado: Se copiaron %d movimientos al archivo 'historicos.txt'.\n", contador_copiados);
}


// TAREA (r) Calcular Monto por Mes
void funcion_calcularMontoMes(Lista_movimiento LMovimientos) {
    int mes; float deb = 0, cred = 0;
    printf("Ingrese mes (10, 11, 12): "); scanf("%d", &mes);
    reset_lista_movimiento(&LMovimientos);
    while (!isOos_lista_movimiento(LMovimientos)) {
        Movimiento m = copy_list_movimiento(LMovimientos);
        if (get_fecha_mes(m) == mes) {
            if (get_tipo_operacion(m) == 1) deb += get_monto(m);
            else cred += get_monto(m);
        }
        forward_lista_movimiento(&LMovimientos);
    }
    printf("Mes %d -> Total Debitad: $%.2f | Total Acreditado: $%.2f\n", mes, deb, cred);
}

// TAREA (s) Precarga automática de Movimientos
void funcion_precarga_movimientos(Lista_movimiento *LMovimientos, int *proximo_id_ptr, float *Saldo_en_cuenta) {
    FILE *fp = fopen("precarga_movimientos.txt", "r");
    if (fp == NULL) {
        printf("Error: 'precarga_movimientos.txt' no encontrado.\n");
        return;
    }
    if (!isempty_lista_movimiento(*LMovimientos)) {
        fclose(fp); return;
    }

    Movimiento temp;
    int dia, mes, tipo_op, tipo_mov, estado;
    float monto;
    char motivo[100], origen[50], destino[50];
    float debitos_totales = 0;
    int contador = 0;
    printf("Iniciando precarga de movimientos desde archivo...\n");

    while (fscanf(fp, "%d %d %f %s %s %s %d %d %d",
           &dia, &mes, &monto, motivo, origen, destino,
           &tipo_op, &tipo_mov, &estado) == 9)
    {
        if (tipo_op == 1 && (debitos_totales + monto) > 100000) {
            printf("Advertencia: Precarga detenida, se supero el limite de debitos de 100k.\n");
            break;
        }

        set_id_mov(&temp, (*proximo_id_ptr)++);
        set_fecha_dia(&temp, dia);
        set_fecha_mes(&temp, mes);
        set_monto(&temp, monto);
        set_motivo(&temp, motivo);
        if (strcmp(origen, "MI_ALIAS") == 0) set_cuenta_origen(&temp, MI_ALIAS);
        else set_cuenta_origen(&temp, origen);
        if (strcmp(destino, "MI_ALIAS") == 0) set_cuenta_destino(&temp, MI_ALIAS);
        else set_cuenta_destino(&temp, destino);
        set_tipo_operacion(&temp, tipo_op);
        set_tipo_mov(&temp, tipo_mov);
        set_estado(&temp, estado);

        // CORRECCIÓN: Actualiza el saldo solo si no está anulado
        if (estado == 1) {
            if (tipo_op == 1) {
                *Saldo_en_cuenta -= monto;
                debitos_totales += monto;
            } else {
                *Saldo_en_cuenta += monto;
            }
        }

        funcion_insertOrdenadoFecha(LMovimientos, temp);
        contador++;
    }
    fclose(fp);
    printf("Precarga de %d movimientos completada (Debitos: $%.2f).\n", contador, debitos_totales);
}

// ===================================================================
// TAREAS ADICIONALES (CORREGIDAS Y ADAPTADAS)
// ===================================================================

// ITEM B (Versión Axel, TDA-Seguro)
int buscar_por_id(Lista_movimiento *m, int IDbus){
    Movimiento aux;
    reset_lista_movimiento(m);
    while(!isOos_lista_movimiento(*m)){
        aux = copy_list_movimiento(*m);
        if (get_id_mov(aux) == IDbus){
            return 1;
        }
        forward_lista_movimiento(m);
    }
    return 0;
}

// ITEM J: LISTA MOVIMIENTOS ANULADOS (CON CARTELES MEJORADOS)
void muestra_lista_mov_anulados(Lista_movimiento m){
    Movimiento aux;
    reset_lista_movimiento(&m);
    printf("\n--- Movimientos Anulados ---\n");
    int encontrados = 0;
    while(!isOos_lista_movimiento(m)){
        aux = copy_list_movimiento(m);
        if(get_estado(aux) == 2){
            printf("-------------------\n");
            printf("  ID Movimiento: %d (ANULADO)\n", get_id_mov(aux));
            printf("  Fecha:         %d/%d\n", get_fecha_dia(aux), get_fecha_mes(aux));
            printf("  Monto:         $%.2f\n", get_monto(aux));
            printf("  Motivo:        %s\n", get_motivo(aux));
            printf("  Origen:        %s\n", get_cuenta_origen(aux));
            printf("  Destino:       %s\n", get_cuenta_destino(aux));

            printf("  Operacion:     ");
            switch(get_tipo_operacion(aux)){
                case 1: printf("Debito\n"); break;
                case 2: printf("Credito\n"); break;
                default: printf("N/A\n");
            }
            printf("  Tipo Mov:      ");
            switch(get_tipo_mov(aux)){
                case 1: printf("Transferencia\n"); break;
                case 2: printf("Pago QR\n"); break;
                case 3: printf("Servicio\n"); break;
                case 4: printf("Retiro/Ingreso\n"); break;
                default: printf("N/A\n");
            }
            encontrados++;
        }
        forward_lista_movimiento(&m);
    }
    if (encontrados == 0) printf("No hay movimientos anulados.\n");
}

// ITEM NH: CARGA CONTACTO POR TECLADO
void carga_contacto_teclado(Lista_contactos *l, Contacto *c){
    if (isfull_lista_estatica(*l)) {
        printf("Error: Agenda llena.\n");
        return;
    }
    char aux_char[50];
    int aux_int;
    printf("\n--- NUEVO CONTACTO ---\n");
    printf("Ingrese nombre: ");
    int ch; while ((ch = getchar()) != '\n' && ch != EOF);
    scanf("%[^\n]s", aux_char);
    set_nombre_contacto(c, aux_char);

    printf("Ingrese alias/cbu: ");
    while ((ch = getchar()) != '\n' && ch != EOF);
    scanf("%[^\n]s", aux_char);
    set_alias_contacto(c, aux_char);

    printf("Tipo de cuenta (1:CA, 2:CC, 3:BV): ");
    scanf("%d", &aux_int);
    set_tipo_cuenta_contacto(c, aux_int);

    insert_lista_estatica(l, *c);
    printf("Contacto cargado.\n");
}

// ITEM G: MODIFICA MOTIVO POR ID (TDA-SEGURO)
void modifica_motivo_por_id(Lista_movimiento *l, int id){
    char aux_char[100];

    if (funcion_buscarMovimientoPorId(l, id) == 1){

         Movimiento mov_copia = copy_list_movimiento(*l);

         printf("Motivo actual: %s\n", get_motivo(mov_copia));
         printf("Ingrese nuevo motivo: ");
         int c; while ((c = getchar()) != '\n' && c != EOF);
         scanf("%[^\n]s", aux_char);

         set_motivo(&mov_copia, aux_char);

         suppress_lista_movimiento(l);
         funcion_insertOrdenadoFecha(l, mov_copia);

         printf("Motivo modificado.\n");
    } else {
        printf("Movimiento ID %d no encontrado.\n", id);
    }
}

// ITEM I: ANULAR MOVIMIENTO POR ID (TDA-SEGURO)
void anularMovimientoPorId(Lista_movimiento *m, int idBuscado, float *Saldo_en_cuenta) {

    if (funcion_buscarMovimientoPorId(m, idBuscado) == 1) {

        Movimiento mov_copia = copy_list_movimiento(*m);

        if (get_estado(mov_copia) == 1) {

             float monto = get_monto(mov_copia);

             if (get_tipo_operacion(mov_copia) == 1) {
                *Saldo_en_cuenta += monto;
                printf("Se reintegraron $%.2f a su saldo.\n", monto);
             } else {
                *Saldo_en_cuenta -= monto;
                printf("Se debitaron $%.2f de su saldo por la anulacion.\n", monto);
             }

             set_estado(&mov_copia, 2);
             suppress_lista_movimiento(m);
             funcion_insertOrdenadoFecha(m, mov_copia);

             printf("Movimiento ID %d anulado.\n", idBuscado);
             printf("Nuevo saldo: $%.2f\n", *Saldo_en_cuenta);

        } else {
            printf("El movimiento ya estaba anulado.\n");
        }
    } else {
        printf("ID %d no encontrado.\n", idBuscado);
    }
}

// (q) Mostrar Todos los Contactos (TDA-SEGURO)
void mostrarContactos(Lista_contactos c) {
    if (isempty_lista_estatica(c)) {
        printf("No hay contactos cargados.\n");
        return;
    }
    printf("\n--- LISTA DE CONTACTOS (Orden de insercion) ---\n");

    reset_lista_estatica(&c);
    int i = 1;
    while(!isOos_lista_estatica(c)) {
        Contacto aux = copy_lista_estatica(c);

        printf("-------------------\n");
        printf(" Contacto %d:\n", i);
        printf("   Nombre:       %s\n", get_nombre_contacto(aux));
        printf("   Alias/CBU:    %s\n", get_alias_contacto(aux));
        printf("   Tipo de Cuenta: ");

        // Decodificar Tipo de Cuenta
        switch(get_tipo_cuenta_contacto(aux)) {
            case 1: printf("Caja de Ahorro\n"); break;
            case 2: printf("Cuenta Corriente\n"); break;
            case 3: printf("Billetera Virtual\n"); break;
            default: printf("No especificado (%d)\n", get_tipo_cuenta_contacto(aux));
        }

        forward_lista_estatica(&c);
        i++;
    }
}

// (l) Mostrar Movs > 350k (Recursivo TDA-SEGURO)
int _mostrar_mayores_recursivo(Lista_movimiento l) {
    if (isOos_lista_movimiento(l)) {
        return 0;
    }

    Movimiento m = copy_list_movimiento(l);
    forward_lista_movimiento(&l);

    int contador_resto = _mostrar_mayores_recursivo(l);

    if (get_monto(m) > 350000) {
        printf("-------------------\n");
        printf("  ID Movimiento: %d\n", get_id_mov(m));
        printf("  Monto:         $%.2f\n", get_monto(m));
        printf("  Motivo:        %s\n", get_motivo(m));
        printf("  Destino:       %s\n", get_cuenta_destino(m));
        return 1 + contador_resto;
    }

    return 0 + contador_resto;
}
void mostrar_mayores_A_350mil(Lista_movimiento m) {
    printf("\n--- Movimientos > $350.000 ---\n");
    reset_lista_movimiento(&m);
    int total = _mostrar_mayores_recursivo(m);
    if (total == 0) {
        printf("No se encontraron movimientos que superen ese monto.\n");
    }
}

// (o) Eliminar Contacto
int busaca_alias(Lista_contactos *l, char alias[]){
    Contacto aux;
    reset_lista_estatica(l);
    while(!isOos_lista_estatica(*l)){
        aux = copy_lista_estatica(*l);
        if ( strcmp(get_alias_contacto(aux), alias) == 0 ){
            return 1; // Deja el cursor posicionado
        }
        forward_lista_estatica(l);
    }
    return 0;
}


void eliminarContactoPorAlias(Lista_contactos *c) {
    if (isempty_lista_estatica(*c)) {
         printf("No hay contactos para eliminar.\n");
         return;
    }
    char alias[50];
    printf("Alias a eliminar: ");
    scanf("%49s", alias);

    if (busaca_alias(c, alias) == 1) {
        printf("Contacto '%s' encontrado. Eliminando...\n", alias);
        supress_lista_estatica(c);
        printf("Contacto eliminado.\n");
    } else {
        printf("No encontrado.\n");
    }
}

// (p) Precarga Automática
void precargarContactos(Lista_contactos *c) {
    FILE *fp = fopen("precarga_contactos.txt", "r");
    if (fp == NULL) {
        printf("Error: No se pudo encontrar 'precarga_contactos.txt'.\n");
        return;
    }
    if (!isempty_lista_estatica(*c)) {
        fclose(fp); return;
    }

    Contacto temp;
    char nombre_temp[50];
    char alias_temp[50];
    int tipo_temp;
    int contador = 0;
    printf("Iniciando precarga de contactos desde archivo...\n");

    while (fscanf(fp, "%s %s %d", nombre_temp, alias_temp, &tipo_temp) == 3) {
        if (isfull_lista_estatica(*c)) {
            printf("Advertencia: La lista de contactos se lleno.\n");
            break;
        }
        set_nombre_contacto(&temp, nombre_temp);
        set_alias_contacto(&temp, alias_temp);
        set_tipo_cuenta_contacto(&temp, tipo_temp);
        insert_lista_estatica(c, temp);
        contador++;
    }
    fclose(fp);
    printf("Precarga completada. Se cargaron %d contactos.\n", contador);
}
