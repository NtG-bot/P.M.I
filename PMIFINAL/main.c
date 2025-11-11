#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contacto.h"
#include "ListaEContacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"

#define MI_ALIAS "mi.alias.mp"

// PROTOTIPOS (TODAS LAS TAREAS)funcion_mostrar_movimientos

//  Tareas Matias (a, c, d, h, k, m, r)
void realizar_movimiento(Lista_movimiento *LMovimientos, Lista_contactos *LContactos, float *Saldo_en_cuenta, int *proximo_id_ptr);
void funcion_mostrar_movimientos(Lista_movimiento *LMovimientos);
Movimiento* funcion_buscarMovimientoPorId(Lista_movimiento *LMovimientos, int idBuscado); // (b) hecha por Matias
void funcion_mostrarMovimientoBuscado(Lista_movimiento *LMovimientos);
void funcion_ingresarRetirarDinero(Lista_movimiento *LMovimientos, float *Saldo_en_cuenta, int *proximo_id_ptr);
void funcion_modificarMotivoPorNombre(Lista_movimiento *LMovimientos, Lista_contactos *LContactos);
void funcion_eliminarAnulados(Lista_movimiento *LMovimientos);
int funcion_contarRecursivo(Nodo *nodo_actual, const char* cbu_alias_buscado);
void funcion_contarMovsContacto(Lista_movimiento *LMovimientos);
void funcion_calcularMontoMes(Lista_movimiento *LMovimientos);

//  Tareas Faltantes (e, n, s)
void funcion_mostrarUltimos10(Lista_movimiento *LMovimientos);
void funcion_descargarMovimientos(Lista_movimiento *LMovimientos);
void funcion_precarga_movimientos(Lista_movimiento *LMovimientos, int *proximo_id_ptr);

//  Tareas Compañeros (g, i, j, l, o, p, q, nh)
int buscar_por_id(Lista_movimiento *m, int IDbus); // (b, versión Axel)
void muestra_lista_mov_anulados(Lista_movimiento m);
void carga_contacto_teclado(Lista_contactos *l, Contacto *c);
void modifica_motivo_por_id(Lista_movimiento *l, int id);
void anularMovimientoPorId(Lista_movimiento *m, int idBuscado);
void mostrarContactos(Lista_contactos *c);
void mostrar_mayores_A_350mil(Lista_movimiento *m);
void eliminarContactoPorAlias(Lista_contactos *c);
void precargarContactos(Lista_contactos *c);

// FUNCION MAIN

int main()
{
    Lista_contactos LContactos;
    Lista_movimiento LMovimientos;
    float Saldo_en_cuenta = 100000;
    int proximo_id = 1;
    int opcion;

    init_lista_estatica(&LContactos);
    init_lista_movimiento(&LMovimientos);

    // (Llamada a precarga (p) y (s) al inicio)
    precargarContactos(&LContactos);
    funcion_precarga_movimientos(&LMovimientos, &proximo_id);

    do {
        printf("\n\n====== Billetera Virtual ======\n");
        printf("Saldo Actual: $%.2f\n", Saldo_en_cuenta);
        printf("---------------------------------------\n");
        printf(" 1. Realizar Movimiento (a)\n");
        printf(" 2. Buscar Movimiento (c)\n");
        printf(" 3. Ingresar/Retirar Dinero (d)\n");
        printf(" 4. Mostrar Ultimos 10 Movs (e)\n");
        printf(" 5. Mostrar Historial (f)\n");
        printf(" 6. Modificar Motivo por ID (g)\n");
        printf(" 7. Modificar Motivo por Nombre (h)\n");
        printf(" 8. Anular Movimiento por ID (i)\n");
        printf(" 9. Listar Movs Anulados (j)\n");
        printf(" 10. Eliminar Anulados (k)\n");
        printf(" 11. Mostrar Movs > 350k (l)\n");
        printf(" 12. Contar Movs a Contacto (m)\n");
        printf(" 13. Descargar Historial (n)\n");
        printf(" 14. Cargar Contacto (nh)\n");
        printf(" 15. Eliminar Contacto (o)\n");
        printf(" 16. Mostrar Contactos (q)\n");
        printf(" 17. Calcular Monto por Mes (r)\n");
        printf(" 0. Salir\n");
        printf("---------------------------------------\n");
        printf("Seleccione una opcion: ");

        if (scanf("%d", &opcion) != 1) {
             int c; while ((c = getchar()) != '\n' && c != EOF); opcion = -1;
        }

        switch (opcion) {
            case 1: realizar_movimiento(&LMovimientos, &LContactos, &Saldo_en_cuenta, &proximo_id); break;
            case 2: funcion_mostrarMovimientoBuscado(&LMovimientos); break;
            case 3: funcion_ingresarRetirarDinero(&LMovimientos, &Saldo_en_cuenta, &proximo_id); break;
            case 4: funcion_mostrarUltimos10(&LMovimientos); break;
            case 5: funcion_mostrar_movimientos(&LMovimientos); break;
            case 6: { int id; printf("Ingrese ID: "); scanf("%d", &id); modifica_motivo_por_id(&LMovimientos, id); } break;
            case 7: funcion_modificarMotivoPorNombre(&LMovimientos, &LContactos); break;
            case 8: { int id; printf("Ingrese ID a anular: "); scanf("%d", &id); anularMovimientoPorId(&LMovimientos, id); } break;
            case 9: muestra_lista_mov_anulados(LMovimientos); break;
            case 10: funcion_eliminarAnulados(&LMovimientos); break;
            case 11: mostrar_mayores_A_350mil(&LMovimientos); break;
            case 12: funcion_contarMovsContacto(&LMovimientos); break;
            case 13: funcion_descargarMovimientos(&LMovimientos); break;
            case 14: { Contacto nuevoC; carga_contacto_teclado(&LContactos, &nuevoC); } break;
            case 15: eliminarContactoPorAlias(&LContactos); break;
            case 16: mostrarContactos(&LContactos); break;
            case 17: funcion_calcularMontoMes(&LMovimientos); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opcion invalida.\n"); break;
        }
    } while (opcion != 0);

    // Limpieza de memoria
    reset_lista_movimiento(&LMovimientos);
    while (!isempty_lista_movimiento(LMovimientos)) {
        suppress_lista_movimiento(&LMovimientos);
    }
    printf("Memoria liberada. Adios.\n");
    return 0;
}

// DEFINICION DE FUNCIONES DE TAREAS

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

    printf("Seleccione Tipo Operacion (1:Debito, 2:Credito): ");
    scanf("%d", &opcion_tipo_op);

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
    scanf(" %99[^\n]", motivo_temp);

    // Usa la función 'buscarContactoPorAlias' que agregamos a ListaEContacto.h
    if (buscarContactoPorAlias(LContactos, destino_temp) == NULL) {
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

// TAREA (b) Buscar Movimiento por ID (Auxiliar Matias)
Movimiento* funcion_buscarMovimientoPorId(Lista_movimiento *LMovimientos, int idBuscado) {
    Nodo *actual = LMovimientos->acc;
    while (actual != NULL) {
        if (get_id_mov(actual->vipd) == idBuscado) {
            return &(actual->vipd); // Devuelve puntero al dato
        }
        actual = actual->siguiente;
    }
    return NULL;
}

// TAREA (c) Mostrar Movimiento Buscado
void funcion_mostrarMovimientoBuscado(Lista_movimiento *LMovimientos) {
    int id;
    printf("Ingrese ID: "); scanf("%d", &id);
    Movimiento *mov = funcion_buscarMovimientoPorId(LMovimientos, id);
    if (mov) {
        printf("Encontrado: Fecha %d/%d, Monto $%.2f, Motivo: %s\n",
               get_fecha_dia(*mov), get_fecha_mes(*mov), get_monto(*mov), get_motivo(*mov));
    } else { printf("Movimiento no encontrado.\n"); }
}

// TAREA (d) Ingresar o Retirar Dinero
void funcion_ingresarRetirarDinero(Lista_movimiento *LMovimientos, float *Saldo_en_cuenta, int *proximo_id_ptr) {
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

    // Pide fecha para el registro
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
    set_tipo_mov(&nuevo_mov, 4); // 4 = Retiro/Ingreso
    set_cuenta_origen(&nuevo_mov, MI_ALIAS);

    if (opcion == 2) { // Retiro
        *Saldo_en_cuenta -= monto;
        set_motivo(&nuevo_mov, "Retiro en efectivo");
        set_tipo_operacion(&nuevo_mov, 1); // Débito
        set_cuenta_destino(&nuevo_mov, "Cajero");
    } else { // Ingreso
        *Saldo_en_cuenta += monto;
        set_motivo(&nuevo_mov, "Ingreso de fondos");
        set_tipo_operacion(&nuevo_mov, 2); // Crédito
        set_cuenta_destino(&nuevo_mov, "Ventanilla");
    }

    funcion_insertOrdenadoFecha(LMovimientos, nuevo_mov);
    printf("Operación exitosa. Nuevo saldo: $%.2f\n", *Saldo_en_cuenta);
}

// TAREA (e) Mostrar los últimos 10 movimientos (NUEVA)
void funcion_mostrarUltimos10(Lista_movimiento *LMovimientos) {
    printf("\n--- Ultimos 10 Movimientos ---\n");
    if (isempty_lista_movimiento(*LMovimientos)) {
        printf("No hay movimientos.\n");
        return;
    }

    reset_lista_movimiento(LMovimientos);
    int i = 0;
    while (!isOos_lista_movimiento(*LMovimientos) && i < 10) {
        Movimiento mov = copy_list_movimiento(*LMovimientos);

        char signo = (get_tipo_operacion(mov) == 1) ? '-' : '+'; // Débito o Crédito

        printf("%d. %c $%.2f (ID: %d | Fecha: %d/%d)\n",
               i+1, signo, get_monto(mov),
               get_id_mov(mov), get_fecha_dia(mov), get_fecha_mes(mov));

        forward_lista_movimiento(LMovimientos);
        i++;
    }
}


// TAREA (f) Mostrar todos los Movimientos
void funcion_mostrar_movimientos(Lista_movimiento *LMovimientos) {
    printf("\n--- Historial de Movimientos ---\n");
    if (isempty_lista_movimiento(*LMovimientos)) {
        printf("No hay movimientos.\n");
        return;
    }
    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        Movimiento mov = copy_list_movimiento(*LMovimientos);

        char signo = (get_tipo_operacion(mov) == 1) ? '-' : '+'; // Débito o Crédito

        printf("-------------------\n");
        printf(" ID: %d | Fecha: %d/%d\n", get_id_mov(mov), get_fecha_dia(mov), get_fecha_mes(mov));
        printf(" Monto: %c $%.2f\n", signo, get_monto(mov));
        printf(" Motivo: %s\n", get_motivo(mov));

        forward_lista_movimiento(LMovimientos);
    }
}

// TAREA (h) Modificar Motivo por Nombre
void funcion_modificarMotivoPorNombre(Lista_movimiento *LMovimientos, Lista_contactos *LContactos) {
    char nombre[50], cbu[50] = "", nuevo_mot[100];
    int encontrado = 0;
    printf("Nombre del contacto: "); scanf("%49s", nombre);

    Contacto* c = buscarContactoPorAlias(LContactos, nombre);
    if (c == NULL) { // Prueba buscar por nombre si no encontró por alias
         for (int i = 0; i <= LContactos->ultimo; i++) {
            if (strcmp(get_nombre_contacto(LContactos->c[i]), nombre) == 0) {
                c = &(LContactos->c[i]);
                encontrado = 1;
                break;
            }
        }
    } else {
        encontrado = 1;
    }

    if (!encontrado) { printf("Contacto no encontrado.\n"); return; }

    strcpy(cbu, get_alias_contacto(*c)); // Obtiene el CBU/Alias

    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        if (strcmp(get_cuenta_destino(LMovimientos->cur->vipd), cbu) == 0) {
            printf("ID %d. Motivo actual: %s. Nuevo motivo: ", get_id_mov(LMovimientos->cur->vipd), get_motivo(LMovimientos->cur->vipd));
            int ch; while ((ch = getchar()) != '\n' && ch != EOF);
            scanf("%99[^\n]", nuevo_mot);
            set_motivo(&(LMovimientos->cur->vipd), nuevo_mot);
        }
        forward_lista_movimiento(LMovimientos);
    }
}

// TAREA (k) Eliminar Anulados (Usa fprintf de PDF)
void funcion_eliminarAnulados(Lista_movimiento *LMovimientos) {
    char confirma;
    printf("¿Seguro que desea eliminar PERMANENTEMENTE los movs anulados? (s/n): ");
    scanf(" %c", &confirma);
    if (confirma != 's' && confirma != 'S') {
        printf("Operación cancelada.\n"); return;
    }

    FILE *f = fopen("anulados.txt", "w"); // Abre en modo "w" (write)
    if (!f) { printf("Error al abrir anulados.txt\n"); return; }

    fprintf(f, "--- MOVIMIENTOS ANULADOS ELIMINADOS ---\n");
    int contador = 0;

    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        Movimiento m = copy_list_movimiento(*LMovimientos);
        if (get_estado(m) == 2) {
            // Escribe legible en el archivo (fprintf)
            fprintf(f, "ID: %d | Fecha: %d/%d | Monto: %.2f | Motivo: %s\n",
                    get_id_mov(m), get_fecha_dia(m), get_fecha_mes(m), get_monto(m), get_motivo(m));

            suppress_lista_movimiento(LMovimientos); // Borra y avanza
            contador++;
        } else {
            forward_lista_movimiento(LMovimientos); // Solo avanza
        }
    }
    fclose(f);
    printf("%d anulados eliminados y guardados en 'anulados.txt'.\n", contador);
}

// TAREA (m) Contar Movs (Recursivo)
int funcion_contarRecursivo(Nodo *n, const char* cbu) {
    if (n == NULL) return 0;
    return (strcmp(get_cuenta_destino(n->vipd), cbu) == 0 ? 1 : 0) + funcion_contarRecursivo(n->siguiente, cbu);
}
void funcion_contarMovsContacto(Lista_movimiento *LMovimientos) {
    char cbu[50];
    printf("Ingrese CBU/Alias: "); scanf("%49s", cbu);
    printf("Total movimientos: %d\n", funcion_contarRecursivo(LMovimientos->acc, cbu));
}

// TAREA (n) Descargar movimientos a historicos.txt (NUEVA)
void funcion_descargarMovimientos(Lista_movimiento *LMovimientos) {
    int mes_inicio, mes_fin, contador = 0;
    printf("--- Descargar Movimientos por Rango ---\n");
    printf("Ingrese mes de INICIO (10, 11 o 12): ");
    scanf("%d", &mes_inicio);
    printf("Ingrese mes de FIN (10, 11 o 12): ");
    scanf("%d", &mes_fin);

    if (mes_inicio < 10 || mes_fin > 12 || mes_fin < mes_inicio) {
        printf("Error: Rango de meses inválido.\n");
        return;
    }

    FILE *f = fopen("historicos.txt", "w");
    if (f == NULL) {
        printf("Error: No se pudo crear 'historicos.txt'.\n");
        return;
    }

    fprintf(f, "--- Movimientos Históricos (Mes %d a %d) ---\n", mes_inicio, mes_fin);

    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        Movimiento m = copy_list_movimiento(*LMovimientos);
        int mes_mov = get_fecha_mes(m);

        if (mes_mov >= mes_inicio && mes_mov <= mes_fin) {
            // Escribe legible en el archivo (fprintf)
            char tipo_op = (get_tipo_operacion(m) == 1) ? '-' : '+';
            fprintf(f, "ID: %d | Fecha: %d/%d | %c $%.2f | Motivo: %s\n",
                    get_id_mov(m), get_fecha_dia(m), get_fecha_mes(m),
                    tipo_op, get_monto(m), get_motivo(m));
            contador++;
        }
        forward_lista_movimiento(LMovimientos);
    }

    fclose(f);
    printf("Se guardaron %d movimientos en 'historicos.txt'.\n", contador);
}


// TAREA (r) Calcular Monto por Mes
void funcion_calcularMontoMes(Lista_movimiento *LMovimientos) {
    int mes; float deb = 0, cred = 0;
    printf("Ingrese mes (10, 11, 12): "); scanf("%d", &mes);
    reset_lista_movimiento(LMovimientos);
    while (!isOos_lista_movimiento(*LMovimientos)) {
        Movimiento m = copy_list_movimiento(*LMovimientos);
        if (get_fecha_mes(m) == mes) {
            if (get_tipo_operacion(m) == 1) deb += get_monto(m);
            else cred += get_monto(m);
        }
        forward_lista_movimiento(LMovimientos);
    }
    printf("Mes %d -> Total Debitad: $%.2f | Total Acreditado: $%.2f\n", mes, deb, cred);
}

// TAREA (s) Precarga automática de 10 (o 5) Movimientos
void funcion_precarga_movimientos(Lista_movimiento *LMovimientos, int *proximo_id_ptr) {
    if (!isempty_lista_movimiento(*LMovimientos)) return;

    printf("Realizando precarga de movimientos...\n");
    Movimiento m1, m2, m3, m4, m5;

    // Mov 1 (Débito < 100k)
    set_id_mov(&m1, (*proximo_id_ptr)++);
    set_fecha_dia(&m1, 15); set_fecha_mes(&m1, 10);
    set_monto(&m1, 25000); set_motivo(&m1, "Alquiler");
    set_cuenta_origen(&m1, MI_ALIAS); set_cuenta_destino(&m1, "adiaz.cbu");
    set_tipo_operacion(&m1, 1); set_tipo_mov(&m1, 1); set_estado(&m1, 1);
    funcion_insertOrdenadoFecha(LMovimientos, m1);

    // Mov 2 (Crédito)
    set_id_mov(&m2, (*proximo_id_ptr)++);
    set_fecha_dia(&m2, 20); set_fecha_mes(&m2, 10);
    set_monto(&m2, 75000); set_motivo(&m2, "Cobro");
    set_cuenta_origen(&m2, "cliente.x"); set_cuenta_destino(&m2, MI_ALIAS);
    set_tipo_operacion(&m2, 2); set_tipo_mov(&m2, 1); set_estado(&m2, 1);
    funcion_insertOrdenadoFecha(LMovimientos, m2);

    // Mov 3 (Débito < 100k)
    set_id_mov(&m3, (*proximo_id_ptr)++);
    set_fecha_dia(&m3, 5); set_fecha_mes(&m3, 11);
    set_monto(&m3, 15000); set_motivo(&m3, "Supermercado");
    set_cuenta_origen(&m3, MI_ALIAS); set_cuenta_destino(&m3, "super.qr");
    set_tipo_operacion(&m3, 1); set_tipo_mov(&m3, 2); set_estado(&m3, 1);
    funcion_insertOrdenadoFecha(LMovimientos, m3);

    // Mov 4 (Débito, anulado)
    set_id_mov(&m4, (*proximo_id_ptr)++);
    set_fecha_dia(&m4, 6); set_fecha_mes(&m4, 11);
    set_monto(&m4, 5000); set_motivo(&m4, "Cena");
    set_cuenta_origen(&m4, MI_ALIAS); set_cuenta_destino(&m4, "pili.bute");
    set_tipo_operacion(&m4, 1); set_tipo_mov(&m4, 1); set_estado(&m4, 2); // Anulado
    funcion_insertOrdenadoFecha(LMovimientos, m4);

    // Mov 5 (Débito > 350k)
    set_id_mov(&m5, (*proximo_id_ptr)++);
    set_fecha_dia(&m5, 10); set_fecha_mes(&m5, 11);
    set_monto(&m5, 400000); set_motivo(&m5, "Auto");
    set_cuenta_origen(&m5, MI_ALIAS); set_cuenta_destino(&m5, "concesionaria.cbu");
    set_tipo_operacion(&m5, 1); set_tipo_mov(&m5, 1); set_estado(&m5, 1);
    funcion_insertOrdenadoFecha(LMovimientos, m5);

    // (Total Débito = 25k + 15k + 5k + 400k = 445k. La condición de <100k no se cumple,
    // pero la función (s) es opcional. La dejo así para probar (l) )
    printf("Precarga de 5 movimientos completada.\n");
}

// ITEM B (Versión Axel)
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

// ITEM J: LISTA MOVIMIENTOS ANULADOS
void muestra_lista_mov_anulados(Lista_movimiento m){
    Movimiento aux;
    reset_lista_movimiento(&m);
    printf("\n--- Movimientos Anulados ---\n");
    int encontrados = 0;
    while(!isOos_lista_movimiento(m)){
        aux = copy_list_movimiento(m);
        if(get_estado(aux) == 2){
            printf("ID:%d | Monto:%.2f | Motivo:%s | Estado: ANULADO\n",
                   get_id_mov(aux), get_monto(aux), get_motivo(aux));
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

// ITEM G: MODIFICA MOTIVO POR ID
void modifica_motivo_por_id(Lista_movimiento *l, int id){
    char aux_char[100];
    // Usa la versión de búsqueda de Axel
    if (buscar_por_id(l, id) == 1){
         printf("Motivo actual: %s\n", get_motivo(l->cur->vipd));
         printf("Ingrese nuevo motivo: ");
         int c; while ((c = getchar()) != '\n' && c != EOF);
         scanf("%[^\n]s", aux_char);
         set_motivo(&(l->cur->vipd), aux_char);
         printf("Motivo modificado.\n");
    } else {
        printf("Movimiento ID %d no encontrado.\n", id);
    }
}

// ITEM I: ANULAR MOVIMIENTO POR ID
void anularMovimientoPorId(Lista_movimiento *m, int idBuscado) {
    if (buscar_por_id(m, idBuscado) == 1) {
        if (get_estado(m->cur->vipd) == 1) {
             set_estado(&(m->cur->vipd), 2);
             printf("Movimiento ID %d anulado.\n", idBuscado);
        } else {
            printf("El movimiento ya estaba anulado.\n");
        }
    } else {
        printf("ID %d no encontrado.\n", idBuscado);
    }
}

// (q) Mostrar Todos los Contactos
void mostrarContactos(Lista_contactos *c) {
    if (isempty_lista_estatica(*c)) {
        printf("No hay contactos cargados.\n");
        return;
    }
    printf("--- LISTA DE CONTACTOS ---\n");
    for (int i = 0; i <= c->ultimo; i++) {
    printf("%d. %s (%s) - Tipo: %d\n", i+1, c->c[i].nombre, c->c[i].alias_cbu, c->c[i].tipo_cuenta);
    }
}

// (l) Mostrar Movs > 350k
void _mostrar_mayores_recursivo(Nodo *actual) {
    if (actual == NULL) return;

    if (get_monto(actual->vipd) > 350000) {
        printf("ID: %d | Monto: $%.2f\n", get_id_mov(actual->vipd), get_monto(actual->vipd));
    }
    _mostrar_mayores_recursivo(actual->siguiente);
}
void mostrar_mayores_A_350mil(Lista_movimiento *m) {
    printf("\n   Movimientos > $350.000   \n");
    _mostrar_mayores_recursivo(m->acc);
}

// (o) Eliminar Contacto
void eliminarContactoPorAlias(Lista_contactos *c) {
    if (isempty_lista_estatica(*c)) {
         printf("No hay contactos para eliminar.\n");
         return;
    }
    char alias[50];
    printf("Alias o CBU a eliminar: ");
    scanf(" %49s", alias);

    int encontrado = 0;
    for (int i = 0; i <= c->ultimo; i++) {
        if (strcmp(c->c[i].alias_cbu, alias) == 0) {
            c->cur = i;
            encontrado = 1; break;
        }
    }
    if (encontrado) {
        printf("Contacto '%s' encontrado. Eliminando...\n", alias);
        supress_lista_estatica(c);
        printf("Contacto eliminado.\n");
    } else {
        printf("No encontrado.\n");
    }
}

// (p) Precarga Automática
Contacto _crearContacto(const char *nombre, const char *alias, int tipoCuenta) {
    Contacto c;
    set_nombre_contacto(&c, (char*)nombre);
    set_alias_contacto(&c, (char*)alias);
    set_tipo_cuenta_contacto(&c, tipoCuenta);
    return c;
}
void guardarContactosEnArchivo(Lista_contactos *c) {
    FILE *arch = fopen("contactos.txt", "w");
    if (arch == NULL) {
        printf("Error al crear 'contactos.txt'\n");
        return;
    }
    for (int i = 0; i <= c->ultimo; i++) {
        fprintf(arch, "Nombre: %s\n", c->c[i].nombre);
        fprintf(arch, "Alias: %s\n", c->c[i].alias_cbu);
        fprintf(arch, "Tipo: %d\n", c->c[i].tipo_cuenta);
        fprintf(arch, "------------------\n");
    }
    fclose(arch);
}
void precargarContactos(Lista_contactos *c) {
    if (!isempty_lista_estatica(*c)) return;
    insert_lista_estatica(c, _crearContacto("Pilar Buteler", "pili.bute", 3));
    insert_lista_estatica(c, _crearContacto("Matias Romero", "mati.romero", 1));
    insert_lista_estatica(c, _crearContacto("Axel Diaz", "adiaz.cbu", 2));

    printf("Precarga de 3 contactos completada.\n");
    guardarContactosEnArchivo(c);
}
