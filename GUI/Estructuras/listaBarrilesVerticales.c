//
// Created by este0 on 13/6/2019.
//

#include "listaBarrilesVerticales.h"
#include <stdio.h>
#include <stdlib.h>

BarrilVertical *lista_barriles_verticales = NULL;
int hay_barril_vertical = 0;

void nuevoBarrilVertical(){
    if (lista_barriles_verticales == NULL) {
        lista_barriles_verticales = malloc(sizeof(BarrilVertical));
        lista_barriles_verticales->barril_x = 256.0;
        lista_barriles_verticales->barril_y = 104.0;
        lista_barriles_verticales->barril_nivel_piso = 196.0;
        lista_barriles_verticales->barril_id = 0;
        lista_barriles_verticales->direccion = 1;
        lista_barriles_verticales->siguiente = NULL;
    } else{
        BarrilVertical *temp = lista_barriles_verticales;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        BarrilVertical *nuevo_barril = malloc(sizeof(BarrilVertical));
        nuevo_barril->barril_x = 256.0;
        nuevo_barril->barril_y = 104.0;
        nuevo_barril->barril_nivel_piso = 196.0;
        nuevo_barril->barril_id = 0;
        nuevo_barril->direccion = 1;
        nuevo_barril->siguiente = NULL;
        temp->siguiente = nuevo_barril;
    }
    hay_barril_vertical++;
}

void eliminarUnBarrilVertical(){
    if (lista_barriles_verticales != NULL) {
        if (hay_barril_vertical == 1){
            free(lista_barriles_verticales);
            lista_barriles_verticales = NULL;
        }
        else{
            if (lista_barriles_verticales->barril_x <= 0){
                BarrilVertical *nuevo_barril = lista_barriles_verticales;
                lista_barriles_verticales = lista_barriles_verticales->siguiente;
                free(nuevo_barril);
            }
            else {
                BarrilVertical *temp = lista_barriles_verticales;
                while (temp->siguiente->barril_x > 0) {
                    temp = temp->siguiente;
                }
                BarrilVertical *aEliminar = temp->siguiente;
                temp->siguiente = aEliminar->siguiente;
                free(aEliminar);
            }
        }
        hay_barril_vertical--;
    }
}

void eliminarBarrilVertical(){
    if (lista_barriles_verticales != NULL) {
        if (hay_barril_vertical == 1){
            free(lista_barriles_verticales);
            lista_barriles_verticales = NULL;
        }
        else{
            BarrilVertical *nuevo_barril = lista_barriles_verticales;
            lista_barriles_verticales = lista_barriles_verticales->siguiente;
            free(nuevo_barril);
        }
        hay_barril_vertical--;
    }
}

BarrilVertical* ultimoBarrilVertical(){
    if (hay_barril_vertical < 2){
        return lista_barriles_verticales;
    }
    else{
        BarrilVertical *temp = lista_barriles_verticales;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        return temp;
    }
}