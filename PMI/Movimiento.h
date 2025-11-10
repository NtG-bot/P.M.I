#ifndef MOVIMIENTO_H_INCLUDED
#define MOVIMIENTO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    int dia;
    int mes;
} Fecha;

typedef struct
{
    int id_mov;
    char cuenta_origen[50];
    char cuenta_destino[50];
    int tipo_operacion; // 1:Debito, 2:Credito
    int tipo_mov;       // 1:Transf, 2:QR, 3:Servicio, 4:Retiro
    float monto;
    char motivo[100];   // CORREGIDO: char[]
    Fecha fecha;
    int estado; // 1:OK, 2:Anulado
} Movimiento;



// Generador de ID CORREGIDO
int generador_id_mov(){
    int proximo_id = 1;
    return proximo_id++;
}

void set_id_mov(Movimiento *a, int nuevo_id){
    a->id_mov = nuevo_id;
}

int get_id_mov(Movimiento a){
    return a.id_mov;
}

void set_cuenta_origen(Movimiento *a, const char cuentaorigen[]){
    strcpy(a->cuenta_origen, cuentaorigen);
}

char* get_cuenta_origen(Movimiento a){
    char *aux = (char*)malloc(strlen(a.cuenta_origen) + 1);
    if (aux != NULL) strcpy(aux, a.cuenta_origen);
    return aux;
}

void set_cuenta_destino(Movimiento *a, const char cuentadestino[]){
    strcpy(a->cuenta_destino, cuentadestino);
}

char* get_cuenta_destino(Movimiento a){
    char *aux = (char*)malloc(strlen(a.cuenta_destino) + 1);
    if (aux != NULL) strcpy(aux, a.cuenta_destino);
    return aux;
}

void set_tipo_operacion(Movimiento *a, int tipooperacion){
    a->tipo_operacion = tipooperacion;
}

int get_tipo_operacion(Movimiento a){
    return a.tipo_operacion;
}

void set_tipo_mov(Movimiento *a, int tipomov){
    a->tipo_mov = tipomov;
}

int get_tipo_mov(Movimiento a){
    return a.tipo_mov;
}

void set_monto(Movimiento *a, float monto){
    a->monto = monto;
}

float get_monto(Movimiento a){
    return a.monto;
}


void set_motivo(Movimiento *a, const char nuevo_motivo[]){
    strcpy(a->motivo, nuevo_motivo);
}

char* get_motivo(Movimiento a){
    char *aux = (char*)malloc(strlen(a.motivo) + 1);
    if (aux != NULL) strcpy(aux, a.motivo);
    return aux;
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

void set_estado(Movimiento *a, int nuevo_estado){
    a->estado = nuevo_estado;
}

int get_estado(Movimiento a){
    return a.estado;
}

#endif // MOVIMIENTO_H_INCLUDED
