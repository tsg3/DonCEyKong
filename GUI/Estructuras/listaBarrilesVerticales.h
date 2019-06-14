//
// Created by este0 on 13/6/2019.
//

#ifndef DONCEYKONGUSER_LISTABARRILESVERTICALES_H
#define DONCEYKONGUSER_LISTABARRILESVERTICALES_H

#include <stdlib.h>

typedef struct BarrilV
{
    float barril_x;
    float barril_y;
    float barril_nivel_piso;
    int barril_id;
    struct BarrilV *siguiente;
} BarrilVertical;

BarrilVertical *lista_barriles_verticales;
int hay_barril_vertical;

void nuevoBarrilVertical();
void eliminarUnBarrilVertical();
void eliminarBarrilVertical();
BarrilVertical* ultimoBarrilVertical();

#endif //DONCEYKONGUSER_LISTABARRILESVERTICALES_H
