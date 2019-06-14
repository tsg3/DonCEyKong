//
// Created by este0 on 13/6/2019.
//

#ifndef DONCEYKONGUSER_LISTABARRILESMIXTOS_H
#define DONCEYKONGUSER_LISTABARRILESMIXTOS_H

#include <stdlib.h>

typedef struct BarrilMixto
{
    float barril_x;
    float barril_y;
    float barril_nivel_piso;
    int barril_id;
    int en_plataforma;
    int despues_escalera;
    int direccion;
    struct BarrilMixto *siguiente;
} BarrilMixto;

typedef struct Escalera
{
    float x;
    float arriba_y;
    float abajo_y;
    int siguiente;
} Escalera;

Escalera *escaleras_rangos[12];

BarrilMixto *lista_barriles_mixtos;

int hay_barril_mixto;

void crearEscaleras();
void nuevoBarrilMixto();
void eliminarUnBarrilMixto();
void eliminarBarrilMixto();
BarrilMixto* ultimoBarrilMixto();

#endif //DONCEYKONGUSER_LISTABARRILESMIXTOS_H
