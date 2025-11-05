#ifndef ITEM_I_H_INCLUDED
#define ITEM_I_H_INCLUDED
#include <stdio.h>
#include <string.h>
#include "ListaVO_Movimiento.h"

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;
typedef struct
{
    int id_mov;
    char cuenta_origen[23];
    char cuenta_destino[23];
    int tipo_operacion;
    int tipo_mov;
    float monto;
    int motivo;
    Fecha fecha;
    int estado;
} Movimiento;
typedef struct nodo {
    Movimiento dato;
    nodo *sig;
} Nodo;

typedef Nodo* Lista;

int anularMovimiento(Lista lista, int id) {
    Nodo *aux = lista;
    int encontrado = 0;

    while (aux != NULL && !encontrado) { /*El while recorre mientras haya nodos y no se haya encontrado el ID.*/
        if (aux->dato.id_mov == id) {
            encontrado = 1;
            if (strcmp(aux->dato.estado, "anulado") == 0) {
                printf("\nEl movimiento %d ya estaba anulado.\n", id); /*Si el ID coincide:Verifica si ya estaba anulado.Si no, copia "anulado" en el campo estado.Muestra el mensaje correspondiente.*/
                return 0;
            } else {
                strcpy(aux->dato.estado, "anulado");
                printf("\nMovimiento %d anulado correctamente.\n", id);
                return 1;
            }
        }
        aux = aux->sig;
    }

    if (!encontrado)
        printf("\nNo se encontro el movimiento con ID %d.\n", id);

    return 0;
}

#endif // ITEM_I_H_INCLUDED

int main{
    int id;
    printf("Ingrese el ID del movimiento a anular: ");
    scanf("%d", &id_mov);

        if (anularMovimiento(lista, id_mov)){
            printf("Operacion exitosa\n");
        }else{
            printf("No se pudo anular el movimiento\n");
        }
}
