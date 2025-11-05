#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
   struct nodo *sig;
} Nodo;

typedef Nodo* Lista;

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

int main() {
    Lista listaMovimientos = NULL;
    printf("\n Movimientos con monto superior a 350.000 \n");
    mostrar_mayores_A_350mil(listaMovimientos);

    Nodo *aux;
    while (listaMovimientos != NULL) {
        aux = listaMovimientos;
        listaMovimientos = listaMovimientos->sig;
        free(aux);
    }

    return 0;
}
