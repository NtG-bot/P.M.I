// Archivo: contacto.h
// -------------------
// Define y implementa el TDA Contacto.
// *** Estructura con implementaci�n en .h seg�n indicaci�n de la c�tedra ***

#ifndef CONTACTO_H_INCLUDED
#define CONTACTO_H_INCLUDED

#include <stdio.h>
#include <string.h>

// --- Constantes para Tipo de Cuenta ---
#define CAJA_AHORRO_PESOS 1
#define CUENTA_CORRIENTE_PESOS 2
#define BILLETERA_VIRTUAL 3
// Puedes a�adir m�s tipos si lo consideras necesario

// --- Definici�n de la Estructura ---
typedef struct {
    char nombre[50];       // Nombre del contacto
    char cbu_alias[50];    // CBU o Alias
    int tipo_cuenta;       // Guarda una de las constantes de arriba
} Contacto;

// --- IMPLEMENTACI�N DE FUNCIONES DENTRO DEL .h ---

// Carga/Modifica el nombre de un contacto.
void setNombreContacto(Contacto *c, const char* nuevoNombre) {
    // Se usa -> porque 'c' es un puntero a Contacto.
    strcpy(c->nombre, nuevoNombre);
}

// Carga/Modifica el CBU/Alias y pregunta por el tipo de cuenta.
void setCbuAliasContacto(Contacto *c, const char* nuevoCbuAlias) {
    int tipo_temp;
    strcpy(c->cbu_alias, nuevoCbuAlias);
    // L�gica para confirmar el tipo de cuenta al modificar CBU/Alias
    printf("--> Se modific� el CBU/Alias de %s a %s.\n", c->nombre, nuevoCbuAlias);
    printf("--> Por favor, confirme/actualice el Tipo de Cuenta (%d: CA $, %d: CC $, %d: Billetera): ",
           CAJA_AHORRO_PESOS, CUENTA_CORRIENTE_PESOS, BILLETERA_VIRTUAL);
    scanf("%d", &tipo_temp);
    // Reutilizamos la funci�n setTipoCuentaContacto para validar y asignar
    setTipoCuentaContacto(c, tipo_temp);
}

// Carga/Modifica el tipo de cuenta, validando.
void setTipoCuentaContacto(Contacto *c, int nuevoTipoCuenta) {
    // Validar si el tipo de cuenta es uno de los definidos
    if (nuevoTipoCuenta == CAJA_AHORRO_PESOS ||
        nuevoTipoCuenta == CUENTA_CORRIENTE_PESOS ||
        nuevoTipoCuenta == BILLETERA_VIRTUAL) {
        c->tipo_cuenta = nuevoTipoCuenta;
    } else {
        printf("Advertencia: Tipo de cuenta desconocido (%d). Se asignar� BILLETERA_VIRTUAL por defecto.\n", nuevoTipoCuenta);
        c->tipo_cuenta = BILLETERA_VIRTUAL; // Manejo de error simple
    }
}

// Devuelve el nombre del contacto.
const char* getNombreContacto(Contacto c) {
    // Se usa . porque 'c' es una copia (paso por valor).
    return c.nombre;
}

// Devuelve el CBU/Alias del contacto.
const char* getCbuAliasContacto(Contacto c) {
    return c.cbu_alias;
}

// Devuelve el tipo de cuenta del contacto (el n�mero).
int getTipoCuentaContacto(Contacto c) {
    return c.tipo_cuenta;
}

// Muestra todos los datos de un contacto.
void mostrarContacto(Contacto c) {
    printf("Nombre: %s\n", c.nombre);
    printf("  CBU/Alias: %s\n", c.cbu_alias);
    printf("  Tipo Cuenta: ");
    switch (c.tipo_cuenta) {
        case CAJA_AHORRO_PESOS:       printf("Caja Ahorro $\n"); break;
        case CUENTA_CORRIENTE_PESOS:  printf("Cta Corriente $\n"); break;
        case BILLETERA_VIRTUAL:       printf("Billetera Virtual\n"); break;
        default:                      printf("Desconocido (%d)\n", c.tipo_cuenta); break;
    }
}

// Carga un contacto pidiendo datos.
Contacto cargarNuevoContacto() {
    Contacto nuevo;
    char nombre_temp[50];
    char cbu_alias_temp[50];
    int tipo_temp;

    printf("--- Nuevo Contacto ---\n");
    printf("Ingrese Nombre: ");
    scanf("%49s", nombre_temp);
    setNombreContacto(&nuevo, nombre_temp); // Usamos el setter

    printf("Ingrese CBU/Alias: ");
    scanf("%49s", cbu_alias_temp);
    // Asignamos directamente aqu�, el tipo se pide despu�s
    strcpy(nuevo.cbu_alias, cbu_alias_temp);

    printf("Ingrese Tipo de Cuenta (%d: CA $, %d: CC $, %d: Billetera): ",
           CAJA_AHORRO_PESOS, CUENTA_CORRIENTE_PESOS, BILLETERA_VIRTUAL);
    scanf("%d", &tipo_temp);
    setTipoCuentaContacto(&nuevo, tipo_temp); // Usamos el setter que valida

    printf("Contacto cargado.\n\n");
    return nuevo;
}

#endif // CONTACTO_H_INCLUDED
