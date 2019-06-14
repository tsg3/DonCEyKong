//
// Created by este0 on 13/6/2019.
//

#include "listaBarriles.h"
#include <stdio.h>
#include <stdlib.h>

BarrilL *lista_barriles = NULL;
int hay_barril_ = 0;

void nuevoBarril(){
    if (lista_barriles == NULL) {
        lista_barriles = malloc(sizeof(BarrilL));
        lista_barriles->barril_x = 256.0;
        lista_barriles->barril_y = 104.0;
        lista_barriles->barril_nivel_piso = 196.0;
        lista_barriles->barril_id = 0;
        lista_barriles->direccion = 1;
        lista_barriles->siguiente = NULL;
    } else{
        BarrilL *temp = lista_barriles;
        while (temp->siguiente != NULL){
           temp = temp->siguiente;
        }
        BarrilL *nuevo_barril = malloc(sizeof(BarrilL));
        nuevo_barril->barril_x = 256.0;
        nuevo_barril->barril_y = 104.0;
        nuevo_barril->barril_nivel_piso = 196.0;
        nuevo_barril->barril_id = 0;
        nuevo_barril->direccion = 1;
        nuevo_barril->siguiente = NULL;
        temp->siguiente = nuevo_barril;
    }
    hay_barril_++;
}

void eliminarBarril(){
    if (lista_barriles != NULL) {
        if (hay_barril_ == 1){
            free(lista_barriles);
            lista_barriles = NULL;
        }
        else{
            BarrilL *nuevo_barril = lista_barriles;
            lista_barriles = lista_barriles->siguiente;
            free(nuevo_barril);
        }
        hay_barril_--;
    }
}

BarrilL* ultimo(){
    if (hay_barril_ < 2){
        return lista_barriles;
    }
    else{
        BarrilL *temp = lista_barriles;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        return temp;
    }
}