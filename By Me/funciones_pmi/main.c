#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contacto.h"
#include "listaE_Contacto.h"
#include "ListaVO_Movimiento.h"
#include "Movimiento.h"
Movimiento cargarMovimiento(char cuentaorigen) {
    Movimiento nuevo_mov;

    nuevo_mov.id_mov = generador_id_mov();

    strcpy(nuevo_mov.cuenta_origen, cuentaorigen);

    nuevo_mov.estado = OK;

    //  Petición de datos al usuario
    printf("Nuevo Movimiento (ID: %d) \n", nuevo_mov.id_mov);
    printf("Ingrese CBU/Alias de destino: ");
    scanf("%[^\n]", nuevo_mov.cuenta_destino);

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
    scanf("[^\n]", nuevo_mov.motivo);

    // Selección de tipo de operación.
    printf("Seleccione el Tipo de Operacion:\n");
    printf(" 1  Debito (Sale)\n", DEBITO);
    printf(" 2  Credito (Entra)\n", CREDITO);
    printf("Opcion: ");
    scanf("%d", &opcion_tipo_op);

    nuevo_mov.tipo_operacion = opcion_tipo_op //1 debito 2 credito

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


//ITEM´s: J, N, B, Ñ, F, G, S.

Movimiento lista_movimientos_anulados(Lista_movimiento m){         //Item J : "Listar los movimientos anulados"
    reset_lista_movimiento(m);
    while(!isOos_lista_movimiento(m)){
        if (m.cur.vipd.estado == /*numero a definir*/ ){
            copy_list_movimiento(m);
        }
        forward_lista_movimiento(m);
    }
}

void descarga_movimientos_historicos(Lista_movimiento *m){          //Item N : "Descarga movimientos desde un archivo, e informa la cantidad de movimientos copiados por pantalla"

}

Movimiento busca_movimiento_por_id(Lista_movimiento m){                   //ITEM B : "Busca un movimiento por id, no figura en menu y tampoco muestra"
    reset_lista_movimiento(m);
    while(!isOos_lista_movimiento(m)){
        if (m.cur.vipd.id_mov == /*numero a asignar*/){
            get_id_mov(m);
        }
        forward_lista_movimiento(m);
    }
}

void carga_contacto(Lista_contactos *c){                            //ITEM Ñ : "Permite la carga por teclado de UN contacto"
    Contacto *aux = (Contacto*)malloc(sizeof(Contacto));
    if (aux == NULL){
        printf("No se pudo asignar memoria\nSaliendo...");
        break;
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
    }
}

Movimiento muestra_movimientos_historicos(Lista_movimiento m){      //ITEM F : "Muestra movimientos historicos, ordenados del mas actual, al mas antiguo"

}

void modifica_motivo_por_id(Lista_movimiento *m){                   //ITEM G : "modifica el motivo de un movimiento por id"

}

int main()
{
    Lista_contactos contactos;
    Lista_movimiento movimientos;

    return 0;
}


