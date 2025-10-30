#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "malloc.h"
#include "../contacto.h"
#include "../listaE_Contacto.h"
#include "../ListaVO_Movimiento.h"
#include "../Movimiento.h"

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
