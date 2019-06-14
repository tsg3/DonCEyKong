//
// Created by este0 on 13/6/2019.
//

#ifndef DONCEYKONGUSER_LISTAFUEGOS_H
#define DONCEYKONGUSER_LISTAFUEGOS_H

#include <stdlib.h>

typedef struct FuegoE{
    float x;
    float y;
    float nivelPiso;
    int id;
    int direccion;
    struct FuegoE *siguiente;
} FuegoE;

FuegoE *fuegos;

int hay_fuego;

void nuevoFuego();
void eliminarFuego();
FuegoE* ultimoFuego();

#endif //DONCEYKONGUSER_LISTAFUEGOS_H
