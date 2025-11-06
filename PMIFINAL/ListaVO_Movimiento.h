// Archivo: ListaVO_Movimiento.h
// ----------------------------
// TDA Lista de Movimientos (Dinámica, Ordenada por Fecha, Pura)

#ifndef LISTAVO_MOVIMIENTO_H_INCLUDED
#define LISTAVO_MOVIMIENTO_H_INCLUDED

#include <stdio.h>  // Para NULL y FILE* (para Tareas K y N)
#include <stdlib.h> // Para malloc(), free()
#include <string.h> // Para strcmp
#include "Movimiento.h" // Necesita la struct Movimiento

// --- Estructura del Nodo ---
typedef struct nodo{
    Movimiento vipd;
    struct nodo *siguiente;
}Nodo;

// --- Estructura de la Lista ---
typedef struct{
    Nodo *acc; // Puntero de Acceso (cabeza)
    Nodo *cur; // Puntero Cursor (actual)
    Nodo *aux; // Puntero Auxiliar (anterior)
}Lista_movimiento;

// --- Implementación de Funciones TDA Básicas ---

void init_lista_movimiento(Lista_movimiento *l){
    l->acc = NULL;
    l->cur = NULL;
    l->aux = NULL;
}

void reset_lista_movimiento(Lista_movimiento *l){
    l->cur = l->acc;
    l->aux = NULL;  // CORREGIDO
}

int isempty_lista_movimiento(Lista_movimiento l){
    return (l.acc == NULL);
}

int isOos_lista_movimiento(Lista_movimiento l){
    return (l.cur == NULL);
}

void forward_lista_movimiento(Lista_movimiento *l){
    if (l->cur != NULL) { // CORREGIDO
        l->aux = l->cur;
        l->cur = l->cur->siguiente;
    }
}

Movimiento copy_list_movimiento(Lista_movimiento l){
    if (l.cur != NULL) { // CORREGIDO
        return l.cur->vipd;
    }
    Movimiento mov_vacio; mov_vacio.id_mov = -1; return mov_vacio;
}

void suppress_lista_movimiento(Lista_movimiento *l) {
    Nodo *nodoAEliminar;
    if (isOos_lista_movimiento(*l)) { return; }

    nodoAEliminar = l->cur;

    if (l->cur == l->acc) {
        l->acc = l->cur->siguiente;
        l->cur = l->acc;
        l->aux = NULL;
    } else {
        l->aux->siguiente = l->cur->siguiente;
        l->cur = l->cur->siguiente;
    }
    free(nodoAEliminar); // ¡Liberar memoria!
}

// --- Implementación de Funciones Específicas del PMI ---

// Función auxiliar para comparar fechas
int esMasRecienteOIgual(Movimiento mov1, Movimiento mov2) {
    if (mov1.fecha.mes > mov2.fecha.mes) return 1;
    if (mov1.fecha.mes == mov2.fecha.mes && mov1.fecha.dia >= mov2.fecha.dia) return 1;
    return 0;
}

[cite_start]// (Punto A) Inserta ordenado por fecha [cite: 3463-3465]
void insertOrdenadoFecha(Lista_movimiento *lista, Movimiento mov) {
    Nodo *nuevoNodo = (Nodo*) malloc(sizeof(Nodo));
    if (nuevoNodo == NULL) { return; } // Error de memoria
    nuevoNodo->vipd = mov;
    nuevoNodo->siguiente = NULL;

    if (isempty_lista_movimiento(*lista) || esMasRecienteOIgual(mov, lista->acc->vipd)) {
        nuevoNodo->siguiente = lista->acc;
        lista->acc = nuevoNodo;
    }
    else {
        Nodo *actual = lista->acc;
        while (actual->siguiente != NULL && esMasRecienteOIgual(actual->siguiente->vipd, mov)) {
            actual = actual->siguiente;
        }
        nuevoNodo->siguiente = actual->siguiente;
        actual->siguiente = nuevoNodo;
    }
    reset_lista_movimiento(lista);
}

// (Punto B) Busca un movimiento por ID
Movimiento* buscarMovimientoPorId(Lista_movimiento lista, long int idBuscado) {
    Nodo *actual = lista.acc;
    while (actual != NULL) {
        if (actual->vipd.id_mov == idBuscado) {
            return &(actual->vipd); // Devuelve dirección del dato
        }
        actual = actual->siguiente;
    }
    return NULL; // No encontrado
}

// (Punto M) Contar Movimientos a Contacto (Recursivo)
int contarMovimientosRecursivo(Nodo *nodo_actual, const char* cbu_alias_buscado) {
    if (nodo_actual == NULL) { // Caso Base
        return 0;
    }
    int contador_resto = contarMovimientosRecursivo(nodo_actual->siguiente, cbu_alias_buscado);
    if (strcmp(nodo_actual->vipd.cuenta_destino, cbu_alias_buscado) == 0) {
        return 1 + contador_resto;
    } else {
        return 0 + contador_resto;
    }
}
int contarMovimientosAContacto(Lista_movimiento lista, const char* cbu_alias_buscado) {
    return contarMovimientosRecursivo(lista.acc, cbu_alias_buscado); // Envoltura
}

// (Punto R) Calcular Monto Mes
void calcularMontosPorMes(Lista_movimiento lista, int mes_buscado, double *total_debito, double *total_credito) {
    *total_debito = 0.0;
    *total_credito = 0.0;
    Nodo *actual = lista.acc;
    while (actual != NULL) {
        if (actual->vipd.fecha.mes == mes_buscado) {
            if (actual->vipd.tipo_operacion == 1) { // 1 = DEBITO
                *total_debito += actual->vipd.monto;
            } else { // 2 = CREDITO
                *total_credito += actual->vipd.monto;
            }
        }
        actual = actual->siguiente;
    }
}

// (Punto K) Eliminar Movimientos Anulados (Esta SÍ usa archivos)
int eliminarAnuladosYGuardar(Lista_movimiento *lista) {
    FILE *archivo = fopen("anulados.txt", "w");
    if (archivo == NULL) {
        return -1; // Error al abrir archivo
    }
    int contador = 0;
    reset_lista_movimiento(lista);
    while (!isOos_lista_movimiento(*lista)) {
        if (copy_list_movimiento(*lista).estado == 2) { // 2 = ANULADO
            // Escribir en archivo (TDA SÍ puede escribir en archivos, no en consola)
            fprintf(archivo, "ID: %ld | Dest: %s | Monto: %.2f\n",
                    copy_list_movimiento(*lista).id_mov,
                    copy_list_movimiento(*lista).vipd.cuenta_destino,
                    copy_list_movimiento(*lista).monto);
            contador++;
            suppress_lista_movimiento(lista); // Borra y avanza cursor
        } else {
            forward_lista_movimiento(lista); // Avanza si no borra
        }
    }
    fclose(archivo);
    return contador; // Devuelve la cantidad borrada
}

// (Punto N) Descargar movimientos a historicos.txt (Esta SÍ usa archivos)
int descargarMovimientosPorFecha(Lista_movimiento lista, int mes_inicio, int mes_fin) {
    FILE *archivoHistoricos = fopen("historicos.txt", "w");
    if (archivoHistoricos == NULL) {
        return -1; // Error
    }
    fprintf(archivoHistoricos, "--- Reporte Histórico (Mes %d a %d) ---\n\n", mes_inicio, mes_fin);

    int contador = 0;
    Nodo *actual = lista.acc;
    while (actual != NULL) {
        Movimiento mov = actual->vipd;
        if (mov.fecha.mes >= mes_inicio && mov.fecha.mes <= mes_fin) {
            fprintf(archivoHistoricos, "ID: %ld | Fecha: %02d/%02d | Monto: %.2f | Motivo: %s\n",
                    mov.id_mov, mov.fecha.dia, mov.fecha.mes, mov.monto, mov.motivo);
            contador++;
        }
        actual = actual->siguiente;
    }
    fclose(archivoHistoricos);
    return contador; // Devuelve la cantidad copiada
}

#endif // LISTAVO_MOVIMIENTO_H_INCLUDED
