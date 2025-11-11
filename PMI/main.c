#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Contacto.h"
#include "listaEContacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"
#define MI_ALIAS "Mi.alias.mp"

// - TAREA (a)
void funcion_realizar_movimiento() {
    char destino_temp[50], motivo_temp[100];
    int dia_temp, mes_temp;
    float monto_temp;
    int opcion_tipo_op, opcion_tipo_mov;
    char respuesta_agendar;
    char nombre_agendar_temp[50];
    int tipo_agendar_temp;

    printf("\n--- Nuevo Movimiento ---\n");
    
    // --- Pedir CBU/Alias ---
    printf("Ingrese CBU/Alias de destino: ");
    scanf(" %49[^\n]", destino_temp); // Lee hasta 49 chars, incluyendo espacios

    // --- Pedir Fecha ---
    // (Bucle de validación de fecha)
    do {
        printf("Ingrese la fecha (dd mm) [ej: 25 10]: ");
        scanf("%d %d", &dia_temp, &mes_temp);
        
        // (Aquí iría tu lógica de validación de fecha)
        // if (fecha_es_invalida) {
        //     printf("Error: La fecha debe ser entre 11/10/2025 y 31/12/2025.\n");
        // }
    } while (0); // (Pongo 0 para que no sea un bucle infinito, reemplazalo con tu lógica)

    // --- Pedir Monto ---
    printf("Ingrese el monto: ");
    scanf("%f", &monto_temp);

    // --- Limpiar buffer ANTES de leer un string después de un número ---
    int c;
    while ((c = getchar()) != '\n' && c != EOF); 
    
    // --- Pedir Motivo ---
    printf("Ingrese el motivo (max 99 chars): ");
    scanf("%99[^\n]", motivo_temp); // Lee hasta 99 chars, incluyendo espacios

    // --- Pedir Tipo Operación ---
    printf("Seleccione Tipo Operacion (1:Debito, 2:Credito): ");
    scanf("%d", &opcion_tipo_op);

    // --- Pedir Tipo Movimiento ---
    printf("Seleccione Tipo Movimiento (1:Transf, 2:QR, 3:Serv, 4:Retiro): ");
    scanf("%d", &opcion_tipo_mov);

    // --- (Aquí iría tu lógica de validación de saldo) ---
    // if (opcion_tipo_op == 1 && monto_temp > saldo_billetera) {
    //     printf("\nError: Saldo insuficiente. Saldo actual: $%.2f\n", saldo_billetera);
    //     return; 
    // }

    // --- (Aquí iría tu lógica de búsqueda de contacto) ---
    // Contacto* contacto_encontrado = buscarContactoPorAlias(&miAgenda, destino_temp);
    // if (contacto_encontrado == NULL) {
        printf("El destinatario '%s' no está en su agenda.\n", destino_temp);
        printf("¿Desea agendarlo? (s/n): ");
        scanf(" %c", &respuesta_agendar);
        
        // if (respuesta_agendar == 's' || respuesta_agendar == 'S') {
            // (Aquí iría tu lógica de agenda llena)
            // if (isFullListaEs(miAgenda)) {
            //     printf("No se pudo agendar: Agenda llena.\n");
            // } else {
                printf("Ingrese nombre para el contacto (sin espacios): ");
                scanf("%49s", nombre_agendar_temp);
                printf("Ingrese Tipo (1:CA$, 2:CC$, 3:Billetera): ");
                scanf("%d", &tipo_agendar_temp);
                
                // (Aquí llamarías a los set_ y a InsertListaEs)
                
                printf("Contacto agendado.\n");
            // }
        // }
    // }

    // --- (Aquí iría toda la lógica final: set_movimiento, insertOrdenadoFecha, etc.) ---
    
    printf("Movimiento realizado con éxito.\n");
    // printf("Movimiento realizado. Saldo restante: $%.2f\n", saldo_billetera);
}

//ITEM B: FUNCION AUXILIAR, SOLO BUSCA, NO MUESTRA, DEVUELVE 1 SI ENCONTRO, 0 SI NO
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

//ITEM J: LISTA LOS MOVIMIENTOS ANULADOS
void muestra_lista_mov_anulados(Lista_movimiento m){
    Movimiento aux;
    reset_lista_movimiento(&m);
    while(!isOos_lista_movimiento(m)){
        aux = copy_list_movimiento(m);
        if(get_estado(aux) == 2){
            printf("ID:%d\n", get_id_mov(aux));
            printf("Cuenta Origen:%s\n", get_cuenta_origen(aux));
            printf("Cuenta Destino:%s\n", get_cuenta_destino(aux));
            switch(get_tipo_operacion(aux)){
            case 1: printf("Tipo de Operacion:Debito\n"); break;
            case 2: printf("Tipo de Operacion:Credito\n"); break;
            }
            switch(get_tipo_mov(aux)){
            case 1: printf("Tipo de Movimiento:Transferencia\n"); break;
            case 2: printf("Tipo de Movimiento:Pago QR\n"); break;
            case 3: printf("Tipo de Movimiento:Servicio\n"); break;
            case 4: printf("Tipo de Movimiento:Retiro\n"); break;
            }
            printf("Monto:%.2f\n", get_monto(aux));
            printf("Motivo:%s\n", get_motivo(aux));
            printf("Dia:%d\n", get_fecha_dia(aux));
            printf("Mes:%d\n", get_fecha_mes(aux));
            printf("Anio:2025\n");
            switch(get_estado(aux)){
            case 1: printf("Estado:Ok\n"); break;
            case 2: printf("Estado:Anulado\n"); break;
            }
        }
        forward_lista_movimiento(&m);
    }
}


//ITEM ENHE: CARGA UN CONTACTO POR TECLADO   NO TE OLVIDES DE CONTROLAR QUE NO ES ESTE LLENA
void carga_contacto_teclado(Lista_contacto *l, Contacto *c){
    char aux_char[22];
    int aux_int;
    system("cls");
    printf("--------------- NUEVO CONTACTO ---------------\n");
    printf("Ingrese nombre:\n");
    getchar();
    scanf("%[^\n]s", aux_char);
    set_nombre_contacto(c, aux_char);
    printf("Ingrese alias/cbu:\n");
    getchar();
    scanf("%[^\n]s", aux_char);
    set_alias_contacto(c, aux_char);
    printf("Ingrese el tipo de cuenta:<1>Caja de Ahorro\n<2>Cuenta Corriente\n<3>Billetera Virtual\n");

    scanf("%d", &aux_int);
    set_tipo_cuenta_contacto(c, aux_int);
    insert_lista_estatica(l, *c);
}

//ITEM G: MODIFICA EL MOTIVO DE UN MOVIMIENTO POR ID
void modifica_motivo_por_id(Movimiento *m, Lista_movimiento *l, int id){
    char aux_char[100];
    Movimiento aux;
    if (buscar_por_id(l, id) == 1){
        aux = copy_list_movimiento(*l);  
        printf("ingrese el nuevo motivo:\n");
        getchar();
        scanf("%[^\n]s", aux_char);
        set_motivo(&aux, aux_char);
        insert_lista_movimiento(l, aux);
        printf("Motivo del movimiento ID %d modificado con exito.\n", id);

    } else {
        printf("Movimiento con ID %d no encontrado.\n", id);
    }
}

//ITEM F: MOSTRAR MOVIMIENTOS HISTORICOS, DEL MAS ACTUAL AL MAS ANTIGUO
void mostrar_movimientos_historicos(Lista_movimiento l) {
    char signo;
    reset_lista_movimiento(&l);
    while (!isOos_lista_movimiento(l)) {
        Movimiento aux = copy_list_movimiento(l);
        if (get_tipo_operacion(aux) == 2) {
            signo = '+';
        } else {                                // 1:Debito, 2:Credito
            signo = '-';
        }
        printf("fecha:%d/%d\n", get_fecha_dia(aux), get_fecha_mes(aux));
        switch (get_tipo_operacion(aux)){
        case 1:{printf("Tipo de Operacion:Debito\n");}
        case 2:{printf("Tipo de Operacion:Credito\n");}
        }
        printf("Motivo:%s\n", get_motivo(aux));
        printf("Monto:%c%f", signo, get_monto(aux));
        forward_lista_movimiento(&l);
    }
}

//ITEM N: DESCARGAR MOVIMIENTOS REALIZADOS EN UN PERIODO A UN ARCHIVO
void descargar_movimientos_por_periodo(Lista_movimiento l, int mes1, int mes2 ) {
    int contador_copiados = 0;
    FILE *puntero = fopen("historicos.txt", "w");
    if (puntero == NULL) {
        printf("No se pudo abrir el archivo\n");
        return;
    } else {
    fprintf(puntero, "%-10s | %-15s | %-15s | %-10s | %-40s | %s\n",
            "Fecha", "Operacion", "Movimiento", "Monto", "Motivo", "Estado");
    reset_lista_movimiento(&l);

    while (!isOos_lista_movimiento(l)) {
        Movimiento aux = copy_list_movimiento(l);
          char tipo_operacion[10];
            if (get_tipo_operacion(aux) == 1){
                strcpy(tipo_operacion, "Debito");
            } else {
                strcpy(tipo_operacion, "Credito");
            }
            char tipo_movimiento[18];
            switch(get_tipo_mov(aux)) {
                case 1: strcpy(tipo_movimiento, "Transferencia"); break;
                case 2: strcpy(tipo_movimiento, "Pago QR"); break;
                case 3: strcpy(tipo_movimiento, "Servicio"); break;
                case 4: strcpy(tipo_movimiento, "Retiro"); break;
                default: strcpy(tipo_movimiento, "Desconocido"); break;
            }
            char tipo_estado[8];
            if (get_estado(aux) == 1){
                strcpy(tipo_estado, "Ok");
            } else {
                strcpy(tipo_estado, "Anulado");
            }

        if (get_fecha_mes(aux)>= mes1 && get_fecha_mes(aux)<= mes2) {

            fprintf(puntero, "%02d/%02d   | %-15s | %-15s | $%-9.2f| %-40s | %s\n",get_fecha_dia(aux), get_fecha_mes(aux),
            tipo_operacion,tipo_movimiento, get_monto(aux), get_motivo(aux), tipo_estado);
            //lo baje sino muy largo XD
            contador_copiados++;
        }
        forward_lista_movimiento(&l);
    }

    fclose(puntero);
    printf("\nProceso completado: Se copiaron %d movimientos al archivo 'historicos.txt'.\n", contador_copiados);
    }
}

//ITEM S: PRECARGAR DE UN ARCHIVO 10 MOVIMIENTOS CON DIFERENTES MOVIMIENTOS
void precarga_automatica_movimientos(Lista_movimiento *l) {
    Movimiento m;
    int contador = 0;
    FILE *puntero = fopen("precarga_movimientos.txt", "r");
    if (puntero == NULL) {
        printf("No se pudoa abrir el archivo\n");
        return;
    } else {
         while (fscanf(puntero, "%d,%[^,],%[^,],%d,%d,%f,%[^,],%d,%d,%d\n", &m.id_mov, m.cuenta_origen, m.cuenta_destino, &m.tipo_operacion, &m.tipo_mov,
        &m.monto, m.motivo, &m.fecha.dia, &m.fecha.mes, &m.estado) == 10) {
        set_id_mov(&m, m.id_mov);
        set_cuenta_origen(&m, m.cuenta_origen);
        set_cuenta_destino(&m, m.cuenta_destino);
        set_tipo_operacion(&m, m.tipo_operacion);
        set_tipo_mov(&m, m.tipo_mov);
        set_monto(&m, m.monto);
        set_motivo(&m, m.motivo);
        set_fecha_dia(&m, m.fecha.dia);
        set_fecha_mes(&m, m.fecha.mes);
        set_estado(&m, m.estado);
        insert_lista_movimiento(l, m);
        contador++;
    }
    }

    fclose(puntero);
    printf("Precarga realizada, %d movimentos cargados\n", contador);
}

void anularMovimientoPorId(Lista_movimiento *m, int idBuscado) {
    Movimiento aux;

    if (buscar_por_id(m, idBuscado) == 1) { // Busca y posiciona el cursor de 'm'
        aux = copy_list_movimiento(*m); // Copia el elemento donde quedó el cursor

        if (get_estado(aux) == 1) { // 1:OK
             suppress_lista_movimiento(m); // Elimina el nodo posicionado
             
             set_estado(&aux, 2); // 2:Anulado
             insert_lista_movimiento(m, aux);

             printf("Movimiento con ID %d fue anulado correctamente.\n", idBuscado);
        } else {
            printf("El movimiento con ID %d ya estaba anulado.\n", idBuscado);
        }
    } else {
        printf("No se encontró el movimiento con ID %d.\n", idBuscado);
    }
}
// (q) Mostrar Todos los Contactos (Recorre la lista estática y muestra)
oid mostrarContactos(Lista_contacto c) { 
    if (isempty_lista_estatica(c)) { 
        printf("No hay contactos cargados.\n");
        return;
    }
    printf("--- LISTA DE CONTACTOS: ---\n");
    reset_lista_estatica(&c);
    while (!isOos_lista_estatica(c)) { 
        Contacto aux = copy_lista_estatica(c);
        printf("Nombre: %s\n", get_nombre_contacto(aux)); 
        printf("Alias/CBU: %s\n", get_alias_contacto(aux));
        printf("Tipo Cuenta: ");
        switch(get_tipo_cuenta_contacto(aux)) {
            case 1: printf("Caja de Ahorro\n"); break;
            case 2: printf("Cuenta Corriente\n"); break;
            case 3: printf("Billetera Virtual\n"); break;
            default: printf("Desconocido\n");
        }
        printf(" \n");
        forward_lista_estatica(&c);
    }
    printf("---------------------------\n");
}
// (l) Mostrar Movs > 350k (Recursivo)
void mostrar_mayores_A_350mil(Lista_movimiento m) {
    Movimiento aux;
    if (isempty_lista_movimiento(m)) { 
        printf("La lista de movimientos esta vacia.\n");
        return;
    }
    printf("\n--- Movimientos Mayores a $350,000.00 ---\n");
    reset_lista_movimiento(&m); 
    while (!isOos_lista_movimiento(m)) { 
        aux = copy_list_movimiento(m);
        if (get_monto(aux) > 350000.00) {
            printf("----------------------------------------\n");
            printf("Datos:\n");
            printf("ID Movimiento: %d\n", get_id_mov(aux)); 
            printf("Cuenta origen: %s\n", get_cuenta_origen(aux));
            printf("Cuenta destino: %s\n", get_cuenta_destino(aux));
            printf("Monto: %.2f\n", get_monto(aux));
            switch(get_tipo_operacion(aux)){
                case 1: printf("Tipo de Operacion:Debito\n"); break;
                case 2: printf("Tipo de Operacion:Credito\n"); break;
                }
            switch(get_estado(aux)){
                case 1: printf("Estado:Ok\n"); break;
                case 2: printf("Estado:Anulado\n"); break;
                }
        }
        forward_lista_movimiento(&m); 
    }
    printf("----------------------------------------\n");
}
// (o) Eliminar un Contacto 
int busaca_alias(Lista_contactos *l, char alias[]){
    Contacto aux;
    reset_lista_estatica(l);
    while(!isOos_lista_estatica(*l)){
        aux = copy_lista_estatica(*l);\
        if ( strcmp(get_alias_contacto(aux), alias) == 0 ){
            return 1;
        }
        forward_lista_estatica(l);
    }
    return 0;
}

void eliminarContactoPorTeclado(Lista_contacto *l) {
    char aliasBuscado[33];
    printf("\n--- Eliminar Contacto ---\n");
    printf("Ingrese el Alias o CBU del contacto a eliminar:\n");
    getchar();
    scanf("%[^\n]s", aliasBuscado);
    if (busaca_alias(l,aliasBuscado) == 1) {
        supress_lista_estatica(l);
        printf("Contacto con alias/cbu '%s' eliminado exitosamente.\n", aliasBuscado);
    } else {
        printf("Error: No se encontro ningun contacto con el alias/cbu '%s'.\n", aliasBuscado);
    }
}

int main()
{
    Lista_contacto Lcontactos;
    Lista_movimiento LMovimientos;
    Movimiento NewMovimiento;
    Contacto NewContacto;
    int IDbus,opcion,opcion2;
    float Saldo_en_cuenta=100000;

do{
    switch(opcion){

    }


}while(opcion<=5);

    return 0;
}















