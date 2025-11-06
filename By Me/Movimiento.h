#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
#include "string.h"
#include "malloc.h"
typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;
typedef struct
{
    int id_mov; //no se repite
    char cuenta_origen[23]; //alias o CBU
    char cuenta_destino[23];    //alias o CBU
    int tipo_operacion; //debe ser DEBITO(se descuenta $) o CREDITO(se suma $)
    int tipo_mov;   //TRANSF, QR, PAGO SERVICIO O RETIRO
    float monto;    //cantidad de DINERO que MODIFICA el saldo
    char motivo[101] //describe el motivo, puede ser VACIO(OBLIGATORIO)
    Fecha fecha;    //indica la fecha del movimiento, solo se considera mes y dia, no año(se considera como 2025 por DEFECTO)
    int estado; //puede ser "ok" o "anulado"(OBLOGATORIO)
} Movimiento;

void generador_id_mov(Movimiento *a){
    a->id_mov = a->id_mov + 1;
    return a->id_mov;
}

int get_id_mov(Movimiento a){
    return a.id_mov;
}

void set_cuenta_origen(Movimiento *a, char cuentaorigen[]){
    strcpy(a->cuenta_origen, cuentaorigen);
}

char get_cuenta_origen(Movimiento a){
    char *aux = (char*)malloc(sizeof(strlen(a.cuenta_origen) + 1));
    strcpy(aux, a.cuenta_origen);
    return aux;
}

void set_cuenta_destino(Movimiento *a, char cuentadestino[]){
    strcpy(a->cuenta_destino, cuentadestino);
}

char get_cuenta_destino(Movimiento a){
    char *aux = (char*)malloc(sizeof(strlen(a.cuenta_destino) + 1));
    strcpy(aux, a.cuenta_destino);
    return aux;
}

void set_tipo_operacion(Movimiento *a, int tipomovimiento){
    a->tipo_mov = tipomovimiento;
}

int get_tipo_operacion(Movimiento a){
    return a.tipo_operacion;
}

void set_monto(Movimiento *a, float monto){
    a->monto = monto;
}

float get_monto(Movimiento a){
    return a.monto;
}

void set_motivo(Movimiento *a, int nuevo_motivo){
    a->motivo = nuevo_motivo;
}

int get_motivo(Movimiento a){
    return a.motivo;
}

void set_fecha_dia(Movimiento *a, int dia){
    a->fecha.dia = dia;
}

int get_fecha_dia(Movimiento a){
    return a.fecha.dia;
}

void set_fecha_mes(Movimiento *a, int mes){
    a->fecha.mes = mes;
}

int get_fecha_mes(Movimiento a){
    return a.fecha.mes;
}

void set_estado(Movimiento *a, int nuevo_estado)
{
    a->estado = nuevo_estado;
}

int get_estado(Movimiento a){
    return a.estado;
}

#endif // MOVIMIENTO_H_INCLUDED

