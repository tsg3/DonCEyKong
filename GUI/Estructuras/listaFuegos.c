//
// Created by este0 on 13/6/2019.
//

#include "listaFuegos.h"
#include <stdlib.h>
#include <stdio.h>

FuegoE *fuegos = NULL;
int hay_fuego = 0;

void nuevoFuego(){
    if (fuegos == NULL) {
        fuegos = malloc(sizeof(FuegoE));
        fuegos->x = 40.0;
        fuegos->y = 494.0;
        fuegos->nivelPiso = 494.0;
        fuegos->id = 0;
        fuegos->direccion = 1;
        fuegos->siguiente = NULL;
    } else{
        FuegoE *temp = fuegos;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        FuegoE *nuevo_fuego = malloc(sizeof(FuegoE));
        nuevo_fuego->x = 40.0;
        nuevo_fuego->y = 494.0;
        nuevo_fuego->nivelPiso = 494.0;
        nuevo_fuego->id = 0;
        nuevo_fuego->direccion = 1;
        nuevo_fuego->siguiente = NULL;
        temp->siguiente = nuevo_fuego;
    }
    hay_fuego++;
}

void eliminarFuego(){
    if (fuegos != NULL) {
        if (hay_fuego == 1){
            free(fuegos);
            fuegos = NULL;
        }
        else{
            FuegoE *nuevo_fuego = fuegos;
            fuegos = fuegos->siguiente;
            free(nuevo_fuego);
        }
        hay_fuego--;
    }
}

FuegoE* ultimoFuego(){
    if (hay_fuego < 2){
        return fuegos;
    }
    else{
        FuegoE *temp = fuegos;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        return temp;
    }
}
