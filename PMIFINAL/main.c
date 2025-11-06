#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacto.h"
#include "listaE_Contacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"
// ===================================
// TAREAS MATI
// ===================================
//
// --- PENDIENTES ---
// (a) Realizar Movimiento (Carga, valida saldo, verifica contacto, inserta)

Movimiento cargarMovimiento(char *cuentaorigen) {
    Movimiento nuevo_mov;

    int opcion_tipo_op, opcion_tipo_mov;

    set_id_mov(&nuevo_mov, generador_id_mov());
    set_cuenta_origen(&nuevo_mov, cuentaorigen);
    set_estado(&nuevo_mov, 1)

    //  Petición de datos al usuario
    printf("Nuevo Movimiento (ID: %d) \n", nuevo_mov.id_mov);
    printf("Ingrese CBU/Alias de destino: ");
    scanf(" %49[^\n]", nuevo_mov.cuenta_destino);

    // Validación de fecha.
    do {
        printf("Ingrese la fecha (dd mm) [ej: 25 10 para 25/Oct]: ");
        scanf("%d/%d", &nuevo_mov.dia, &nuevo_mov.mes);
        if (!((nuevo_mov.mes == 10 && nuevo_mov.dia > 10 && nuevo_mov.dia <= 31) ||
              (nuevo_mov.mes > 10 && nuevo_mov.mes <= 12 && nuevo_mov.dia >= 1 && nuevo_mov.dia <= 31))) {
             printf("Error: La fecha debe ser entre 11/10/2025 y 31/12/2025.\n");
        }
    } while (!((nuevo_mov.mes == 10 && nuevo_mov.dia > 10 && nuevo_mov.dia <= 31) ||
               (nuevo_mov.mes > 10 && nuevo_mov.mes <= 12 && nuevo_mov.dia >= 1 && nuevo_mov.dia <= 31)));

    printf("Ingrese el monto:\n ");
    scanf("%2f", &nuevo_mov.monto);

    printf("Ingrese el motivo (max 100 chars):\n ");
    scanf(" %99[^\n]", nuevo_mov.motivo);

    // Selección de tipo de operación.
    printf("Seleccione el Tipo de Operacion:\n");
    printf(" 1  Debito (Sale)\n");
    printf(" 2  Credito (Entra)\n");
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_op);

    set_tipo_operacion(&nuevo_mov, opcion_tipo_op) //1 debito 2 credito

    // Selección de tipo de movimiento.
    printf("Seleccione el Tipo de Movimiento:\n");
    printf("  1  Transferencia\n");
    printf("  2  Pago con QR\n");
    printf("  3  Pago de Servicio\n" );
    printf("  4  Retiro de Efectivo\n");
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_mov);
    switch(opcion_tipo_mov) {
        case 2: nuevo_mov.tipo_mov = 2; break;
        case 3: nuevo_mov.tipo_mov = 3; break;
        case 4: nuevo_mov.tipo_mov = 4; break;
        default: nuevo_mov.tipo_mov = 1; break;
    }



    printf("Movimiento cargado con exito.\n\n");
    return nuevo_mov;
}

// (c) Mostrar Movimiento Buscado (Pide ID, llama a 'buscar' y 'mostrar')
void funcion_mostrarMovimientoBuscado() {
    long int id_b;
    printf("Ingrese ID del movimiento a buscar: ");
    scanf("%ld", &id_b);

    Movimiento* mov_b = buscarMovimientoPorId(miBilletera, id_b); // Llama al TDA

    if (mov_b != NULL) {
        printf("--- Movimiento Encontrado ---\n");
        // Usamos Getters del TDA para mostrar
        printf("ID Movimiento: %ld\n", get_id_mov(*mov_b));
        printf("  Fecha: %02d/%02d/2025\n", get_fecha_dia(*mov_b), get_fecha_mes(*mov_b));
        // (No hacemos get_cuenta_origen/destino/motivo porque devuelven mallocs)
        // (Es más seguro acceder directo al struct devuelto por el puntero)
        printf("  Origen: %s\n", mov_b->cuenta_origen);
        printf("  Destino: %s\n", mov_b->cuenta_destino);
        printf("  Monto: %.2f\n", get_monto(*mov_b));
        printf("  Motivo: %s\n", mov_b->motivo);
        printf("  Estado: %d\n", get_estado(*mov_b));
    } else {
        printf("Error: Movimiento con ID %ld no encontrado.\n", id_b);
    }
}

// (m) Contar Movs a Contacto (Recursivo)

// Esta es la función recursiva interna
int contarMovimientosRecursivo(Nodo *nodo_actual, const char* cbu_alias_buscado) {
    // Caso Base: Se terminó la lista
    if (nodo_actual == NULL) {
        return 0;
    }

    // Llamada recursiva: Contar el resto de la lista
    int contador_resto = contarMovimientosRecursivo(nodo_actual->siguiente, cbu_alias_buscado);

    // Caso recursivo: Comparar el nodo actual
    if (strcmp(nodo_actual->vipd.cuenta_destino, cbu_alias_buscado) == 0) {
        return 1 + contador_resto; // Lo encontré, sumo 1 + lo que encontró el resto
    } else {
        return 0 + contador_resto; // No lo encontré, sumo 0 + lo que encontró el resto
    }
}

// Esta es la función "envoltura" que llama el main
int contarMovimientosAContacto(Lista_movimiento lista, const char* cbu_alias_buscado) {
    // Inicia la recursividad desde el primer nodo (acceso)
    return contarMovimientosRecursivo(lista.acc, cbu_alias_buscado);
}

// (r) Calcular Monto (Ingresado/Debitado) por Mes

void calcularMontosPorMes(Lista_movimiento lista, int mes_buscado, double *total_debito, double *total_credito) {
    *total_debito = 0.0; // Inicializamos los punteros a 0
    *total_credito = 0.0;

    Nodo *actual = lista.acc; // Empezamos por el primero

    while (actual != NULL) {
        // Si el movimiento es del mes que buscamos
        if (actual->vipd.mes == mes_buscado) {
            // Sumamos donde corresponda
            if (actual->vipd.tipo_operacion == DEBITO) {
                *total_debito += actual->vipd.monto;
            } else {
                *total_credito += actual->vipd.monto;
            }
        }
        actual = actual->siguiente; // Avanzamos
    }
}

// (d) Ingresar o Retirar Dinero (Actualiza saldo, crea movimiento)



// (k) Eliminar Movs Anulados (Guarda en .txt, pide confirmación, elimina)

void eliminarAnuladosYGuardar(Lista_movimiento *lista) {
    FILE *archivo = fopen("anulados.txt", "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear anulados.txt\n");
        return;
    }

    Nodo *actual = lista->acc;
    Nodo *anterior = NULL;
    int contador = 0;

    printf("Buscando movimientos anulados para eliminar...\n");

    while (actual != NULL) {
        if (actual->vipd.estado == ANULADO) {
            // 1. Guardar en el archivo
            fprintf(archivo, "ID: %ld | Destino: %s | Monto: %.2f\n",
                    actual->vipd.id_mov,
                    actual->vipd.cuenta_destino,
                    actual->vipd.monto);
            contador++;

            // 2. Eliminar de la lista
            Nodo *nodoAEliminar = actual;
            if (anterior == NULL) { // Si es el primer nodo
                lista->acc = actual->siguiente;
                actual = lista->acc; // Avanzamos al nuevo primero
            } else { // Si es uno del medio o el final
                anterior->siguiente = actual->siguiente;
                actual = actual->siguiente; // Avanzamos
            }
            free(nodoAEliminar); // Liberamos memoria
        } else {
            // Solo avanzamos si NO borramos
            anterior = actual;
            actual = actual->siguiente;
        }
    }

    fclose(archivo);
    printf("Se guardaron y eliminaron %d movimientos anulados.\n", contador);
}

// (h) Modificar Motivo por Nombre de Contacto (Busca contacto -> Busca movs)



// ===================================
// TAREAS AXEL
// ===================================
//
// --- PENDIENTES ---
// (n) Descargar Movs a historicos.txt (Pide fechas, recorre lista, guarda en .txt)

void descarga_movimientos_historicos(Lista_movimiento *m){          //Item N : "Descarga movimientos desde un archivo, e informa la cantidad de movimientos copiados por pantalla"

}

// (f) Mostrar Movimientos Históricos (Recorre y muestra toda la lista)

Movimiento muestra_movimientos_historicos(Lista_movimiento m){      //ITEM F : "Muestra movimientos historicos, ordenados del mas actual, al mas antiguo"

}

// (s) Precarga Automática de 10 Movimientos




// --- HECHAS ---
// (j) Listar los movimientos anulados

void lista_movimientos_anulados(Lista_movimiento m){         //Item J : "Listar los movimientos anulados"
    Movimiento aux;
    reset_lista_movimiento(&m);
    do{
    aux = copy_list_movimiento(m);
        if (get_estado(aux) == 2 ){
            //mostrar campo a campo
        }
        else{
        forward_lista_movimiento(&m);
        }
    }while(!isOos_lista_movimiento(m));
}

// (b) Buscar un movimiento por id_mov (Función interna)

int busca_movimiento_por_id(Lista_movimiento *m,int id){                   //ITEM B : "Busca un movimiento por id, no figura en menu y tampoco muestra"
    Movimiento aux;
    reset_lista_movimiento(&m);
    do{
        aux = copy_list_movimiento(*m);
        if (get_id_mov(aux) == id){
            return 1;
        }
        else{
         forward_lista_movimiento(m);
        }
    }while(!isOos_lista_movimiento(*m));
    return 0;
}

// (ñ) Cargar un contacto por teclado

void carga_contacto(Lista_contactos *c){                            //ITEM  : "Permite la carga por teclado de UN contacto"
    Contacto *aux = (Contacto*)malloc(sizeof(Contacto));
    if (aux == NULL){
        printf("No se pudo asignar memoria\nSaliendo...");
        exit(1);
    }
    else{
        ResetListaEs(c);
        printf("ingrese el nombre del contacto:\n");
        scanf("%[\n]s", aux->nombre);
        set_nombre(c,aux);
        printf("ingrese el Alias/CBU:\n");
        scanf("%[\n]s", aux->alias_cbu);
        set_alias_cbu(c,aux);
        printf("ingrese el tipo de cuenta:<1>...\n<2>...\n");
        scanf("%d", &aux->tipo_cuenta);
        set_tipo_cuenta(c,aux);
       // InsertListaEs(c,aux);
    }
}

// (g) Modificar el motivo por id_mov

void modifica_motivo_por_id(Lista_movimiento *m, int id, int motivo){                   //ITEM G : "modifica el motivo de un movimiento por id"
    int nuevo_id;
    if (busca_movimiento_por_id(m,id) == 1){
        Movimiento aux = copy_list_movimiento(m);
        nuevo_id = get_id_mov(aux);
        set_motivo(m,motivo);
        printf("exito");
    }
    else {
        printf("el id no existe\n");
    }
}


// ===================================
// TAREAS PILAR
// ===================================
//
// --- PENDIENTES ---
// (i) Anular Movimiento por ID (Busca por ID y usa set_estado)



// (q) Mostrar Todos los Contactos (Recorre la lista estática y muestra)



// (p) Precarga Automática de 5 Contactos



// (l) Mostrar Movs > 350k (Recursivo)

void mostrar_mayores_A_350mil(Lista lista) {
    if (lista == NULL)
        return;

    /* Si el movimiento supera los 350 mil, lo muestro*/
    if (lista->dato.monto > 350000) {
        printf("Datos:\n");
        printf("ID Movimiento: %d\n", lista->dato.id_mov);
        printf("Cuenta origen: %s\n", lista->dato.cuenta_origen);
        printf("Cuenta destino: %s\n", lista->dato.cuenta_destino);
        printf("Monto: %.2f\n", lista->dato.monto);
        printf("Tipo operacion: %s\n", lista->dato.tipo_operacion);
        printf("Estado: %s\n", lista->dato.estado);
    }
    mostrar_mayores_A_350mil(lista->sig); /*recursion*/
}


// (o) Eliminar un Contacto (Pide nombre/alias, busca y llama a SupressListaEs)



// (s) Precarga Automática de 10 Movimientos (Duplicada con Axel, coordinen)




int main()
{
    Lista_contactos contactos;
    Lista_movimiento movimientos;


    return 0;
}
