//
// Created by este0 on 13/6/2019.
//

#ifndef DONCEYKONGUSER_LISTABARRILES_H
#define DONCEYKONGUSER_LISTABARRILES_H

#include <stdlib.h>

typedef struct BarrilL
{
    float barril_x;
    float barril_y;
    float barril_nivel_piso;
    int barril_id;
    int direccion;
    struct BarrilL *siguiente;
} BarrilL;

BarrilL *lista_barriles;
int hay_barril_;

void nuevoBarril();
void eliminarBarril();
BarrilL* ultimo();

#endif //DONCEYKONGUSER_LISTABARRILES_H
