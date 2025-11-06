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
    set_estado(&nuevo_mov, 1);

    //  Petición de datos al usuario
    printf("Nuevo Movimiento (ID: %d) \n", nuevo_mov.id_mov);
    printf("Ingrese CBU/Alias de destino: ");
    scanf(" %49[^\n]", nuevo_mov.cuenta_destino);

    // Validación de fecha.
    do {
        printf("Ingrese la fecha (dd mm) [ej: 25 10 para 25/Oct]: ");
        scanf("%d/%d", &nuevo_mov.fecha.dia, &nuevo_mov.fecha.mes);
        if (!((nuevo_mov.fecha.mes == 10 && nuevo_mov.fecha.dia > 10 && nuevo_mov.fecha.dia <= 31) ||
              (nuevo_mov.fecha.mes > 10 && nuevo_mov.fecha.mes <= 12 && nuevo_mov.fecha.dia >= 1 && nuevo_mov.fecha.dia <= 31))) {
             printf("Error: La fecha debe ser entre 11/10/2025 y 31/12/2025.\n");
        }
    } while (!((nuevo_mov.fecha.mes == 10 && nuevo_mov.fecha.dia > 10 && nuevo_mov.fecha.dia <= 31) ||
               (nuevo_mov.fecha.mes > 10 && nuevo_mov.fecha.mes <= 12 && nuevo_mov.fecha.dia >= 1 && nuevo_mov.fecha.dia <= 31)));

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
   if (opcion_tipo_mov < 1 || opcion_tipo_mov > 4) {
        opcion_tipo_mov = 1;
    }
    set_tipo_mov(&nuevo_mov, opcion_tipo_mov);


    printf("Movimiento cargado con exito.\n\n");
    return nuevo_mov;
}

// (c) Mostrar Movimiento Buscado (Pide ID, llama a 'buscar' y 'mostrar')
// (Esta función va en main.c, junto con funcion_cargarMovimiento)

// --- TAREA (c): Mostrar Movimiento Buscado ---
void funcion_mostrarMovimientoBuscado() {
int id_a_buscar;
Movimiento* mov_encontrado; // Un puntero para guardar el resultado

    printf("Buscar y Mostrar Movimiento\n");
    printf("Ingrese el ID del movimiento que desea ver: ");
    scanf("%d", &id_a_buscar);

    mov_encontrado = buscarMovimientoPorId(miBilletera, id_a_buscar);

    if (mov_encontrado != NULL) {
        printf("\n--- Movimiento Encontrado (ID: %d) ---\n", id_a_buscar);
        printf("  Fecha: %d/%d/2025\n", get_fecha_dia(*mov_encontrado), get_fecha_mes(*mov_encontrado));
        printf("  Origen: %s\n", mov_encontrado->cuenta_origen);
        printf("  Destino: %s\n", mov_encontrado->cuenta_destino);
        printf("  Motivo: %s\n", mov_encontrado->motivo);

        if (get_tipo_operacion(*mov_encontrado) == 1) { // 1 = DEBITO
            printf("  Tipo: DEBITO\n");
            printf("  Monto: -$%f\n", get_monto(*mov_encontrado));
        } else { // 2 = CREDITO
            printf("  Tipo: CREDITO\n");
            printf("  Monto: +$%f\n", get_monto(*mov_encontrado));
        }

        if (get_estado(*mov_encontrado) == 1) { // 1 = OK
            printf("  Estado: OK\n");
        } else { // 2 = ANULADO
            printf("  Estado: ANULADO\n");
        }

    } else {
        printf("No se encontro ningun movimiento con el ID %d.\n", id_a_buscar);
    }
}

// (m) Contar Movs a Contacto (Recursivo)


int funcion_contarRecursivo(Nodo *nodo_actual,char* cbu_alias_buscado) {
    if (nodo_actual == NULL) {
        return 0;
    }
    int contador_resto = funcion_contarRecursivo(nodo_actual->siguiente, cbu_alias_buscado);

    if (strcmp(nodo_actual->vipd.cuenta_destino, cbu_alias_buscado) == 0) {
        return 1 + contador_resto;
    } else {
        return 0 + contador_resto;
    }
}

void funcion_contarMovsContacto() {     //ai
    char cbu_buscado[50];

    printf("Contar Movimientos a Contacto \n");
    printf("Ingrese el CBU/Alias del contacto a contar: ");
    scanf(" %49s", cbu_buscado);

    int cantidad = funcion_contarRecursivo(miBilletera.acc, cbu_buscado);

    printf("Resultado: Se encontraron %d movimientos a esa cuenta.\n", cantidad);
}

// (r) Calcular Monto (Ingresado/Debitado) por Mes

void funcion_calcularMontosPorMes(int mes_buscado, float *p_total_debito, float *p_total_credito) {


    *p_total_debito = 0.0;
    *p_total_credito = 0.0;


    Nodo *nodo_actual = miBilletera.acc;

    while (nodo_actual != NULL) {

        Movimiento mov_actual = nodo_actual->vipd;

        if (get_fecha_mes(mov_actual) == mes_buscado) {

            if (get_tipo_operacion(mov_actual) == 1) { // 1 = DEBITO
                *p_total_debito += get_monto(mov_actual);

        } else { // 2 = CREDITO
                *p_total_credito += get_monto(mov_actual);
    }}
        nodo_actual = nodo_actual->siguiente;
}}

// (d) Ingresar o Retirar Dinero (Actualiza saldo, crea movimiento)

void funcion_ingresarRetirarDinero() {
    int op_saldo;
    float monto_saldo;

    printf("\n--- Ingresar/Retirar Dinero ---\n");
    printf("Saldo Actual: $%.2f\n", saldo_billetera);
    printf("Seleccione la operacion:\n");
    printf("  1. Ingresar Dinero (Crédito)\n");
    printf("  2. Retirar Efectivo (Débito)\n");
    printf("Opcion: ");
    scanf("%d", &op_saldo);

    if (op_saldo != 1 && op_saldo != 2) {
        printf("Error: Opción no válida.\n");
        return;
    }

    printf("Ingrese el Monto: ");
    scanf("%f", &monto_saldo);

    if (op_saldo == 2 && monto_saldo > saldo_billetera) { // 2 = Retirar
        printf("Error: Saldo insuficiente. No se puede retirar $%.2f\n", monto_saldo);
        return;
    }

    Movimiento mov_saldo;

    set_id_mov(&mov_saldo, generador_id_mov());
    set_monto(&mov_saldo, monto_saldo);
    set_estado(&mov_saldo, 1); // 1 = OK

    // (El PMI no dice que pidamos la fecha acá, así que ponemos una genérica)
    // (Lo ideal sería pedirla, pero seguimos el ejemplo de 'cargar')
    set_fecha_dia(&mov_saldo, 15);
    set_fecha_mes(&mov_saldo, 10);

    if (op_saldo == 1) { // --- Es un INGRESO ---
        set_tipo_operacion(&mov_saldo, 2); // 2 = CREDITO
        set_tipo_mov(&mov_saldo, 1); // 1 = TRANSFERENCIA (es lo más parecido)
        set_cuenta_origen(&mov_saldo, "Banco_Externo");
        set_cuenta_destino(&mov_saldo, MI_ALIAS_UNIPAGO);
        set_motivo(&mov_saldo, "Ingreso_de_fondos");

        saldo_billetera += monto_saldo;

    } else { // --- Es un RETIRO ---
        set_tipo_operacion(&mov_saldo, 1); // 1 = DEBITO
        set_tipo_mov(&mov_saldo, 4); // 4 = RETIRA_EFECTIVO
        set_cuenta_origen(&mov_saldo, MI_ALIAS_UNIPAGO);
        set_cuenta_destino(&mov_saldo, "Cajero_Automatico");
        set_motivo(&mov_saldo, "Retiro_en_efectivo");
        saldo_billetera -= monto_saldo;
    }

    insertOrdenadoFecha(&miBilletera, mov_saldo);

    printf("Operacion exitosa. Nuevo Saldo: $%.2f\n", saldo_billetera);
}

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

void Mod_Motivo_Nombr (Lista_contactos l,Lista_movimiento *l){
char motiv1[100];
char contactb[50];
char cbu_alias[50]
strcopy(cbu_alias,l->)
int encontrado ;

strcmp(contactb,get_alias_cbu(c))
scanf(" %99[^\n]",motiv1);


printf("¿De qué contacto querés modificar los movimientos? Ingrese el nombre: ");

scanf("%s", nombre_buscado);
if (strcmp(nombre_buscado,)==0)
    strcopy(cbu_alias,l->arrayContactos[i].alias_cbu)
}

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
    Mod_Motivo_Nombr(&c,&m)

    return 0;
}
