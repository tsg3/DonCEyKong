//
// Created by este0 on 13/6/2019.
//

#include "listaBarrilesMixtos.h"
#include <stdio.h>
#include <stdlib.h>

BarrilMixto *lista_barriles_mixtos = NULL;
int hay_barril_mixto = 0;

void crearEscaleras(){
    escaleras_rangos[0] = malloc(sizeof(Escalera));
    escaleras_rangos[1] = malloc(sizeof(Escalera));
    escaleras_rangos[2] = malloc(sizeof(Escalera));
    escaleras_rangos[3] = malloc(sizeof(Escalera));
    escaleras_rangos[4] = malloc(sizeof(Escalera));
    escaleras_rangos[5] = malloc(sizeof(Escalera));
    escaleras_rangos[6] = malloc(sizeof(Escalera));
    escaleras_rangos[7] = malloc(sizeof(Escalera));
    escaleras_rangos[8] = malloc(sizeof(Escalera));
    escaleras_rangos[9] = malloc(sizeof(Escalera));
    escaleras_rangos[10] = malloc(sizeof(Escalera));
    escaleras_rangos[11] = malloc(sizeof(Escalera));

    escaleras_rangos[0]->x = 352.0;
    escaleras_rangos[0]->arriba_y = 104.0;
    escaleras_rangos[0]->abajo_y = 188.0;
    escaleras_rangos[0]->siguiente = 3;
    escaleras_rangos[1]->x = 736.0;
    escaleras_rangos[1]->arriba_y = 114.0;
    escaleras_rangos[1]->abajo_y = 176.0;
    escaleras_rangos[1]->siguiente = 2;

    escaleras_rangos[2]->x = 672.0;
    escaleras_rangos[2]->arriba_y = 178.0;
    escaleras_rangos[2]->abajo_y = 268.0;
    escaleras_rangos[2]->siguiente = 7;
    escaleras_rangos[3]->x = 288.0;
    escaleras_rangos[3]->arriba_y = 190.0;
    escaleras_rangos[3]->abajo_y = 256.0;
    escaleras_rangos[3]->siguiente = 6;
    escaleras_rangos[4]->x = 128.0;
    escaleras_rangos[4]->arriba_y = 194.0;
    escaleras_rangos[4]->abajo_y = 252.0;
    escaleras_rangos[4]->siguiente = 5;

    escaleras_rangos[5]->x = 256.0;
    escaleras_rangos[5]->arriba_y = 256.0;
    escaleras_rangos[5]->abajo_y = 346.0;
    escaleras_rangos[5]->siguiente = 9;
    escaleras_rangos[6]->x = 448.0;
    escaleras_rangos[6]->arriba_y = 262.0;
    escaleras_rangos[6]->abajo_y = 340.0;
    escaleras_rangos[6]->siguiente = 8;
    escaleras_rangos[7]->x = 736.0;
    escaleras_rangos[7]->arriba_y = 270.0;
    escaleras_rangos[7]->abajo_y = 332.0;
    escaleras_rangos[7]->siguiente = 8;

    escaleras_rangos[8]->x = 384.0;
    escaleras_rangos[8]->arriba_y = 342.0;
    escaleras_rangos[8]->abajo_y = 416.0;
    escaleras_rangos[8]->siguiente = 11;
    escaleras_rangos[9]->x = 128.0;
    escaleras_rangos[9]->arriba_y = 350.0;
    escaleras_rangos[9]->abajo_y = 408.0;
    escaleras_rangos[9]->siguiente = 10;

    escaleras_rangos[10]->x = 320.0;
    escaleras_rangos[10]->arriba_y = 414.0;
    escaleras_rangos[10]->abajo_y = 494.0;
    escaleras_rangos[10]->siguiente = 12;
    escaleras_rangos[11]->x = 736.0;
    escaleras_rangos[11]->arriba_y = 426.0;
    escaleras_rangos[11]->abajo_y = 484.0;
    escaleras_rangos[11]->siguiente = 12;
}

void nuevoBarrilMixto(){
    if (lista_barriles_mixtos == NULL) {
        lista_barriles_mixtos = malloc(sizeof(BarrilMixto));
        lista_barriles_mixtos->barril_x = 256.0;
        lista_barriles_mixtos->barril_y = 104.0;
        lista_barriles_mixtos->barril_nivel_piso = 196.0;
        lista_barriles_mixtos->barril_id = 0;
        lista_barriles_mixtos->en_plataforma = 1;
        lista_barriles_mixtos->direccion = 1;
        lista_barriles_mixtos->despues_escalera = 0;
        lista_barriles_mixtos->siguiente = NULL;
    } else{
        BarrilMixto *temp = lista_barriles_mixtos;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        BarrilMixto *nuevo_barril = malloc(sizeof(BarrilMixto));
        nuevo_barril->barril_x = 256.0;
        nuevo_barril->barril_y = 104.0;
        nuevo_barril->barril_nivel_piso = 196.0;
        nuevo_barril->barril_id = 0;
        nuevo_barril->en_plataforma = 1;
        nuevo_barril->direccion = 1;
        nuevo_barril->despues_escalera = 0;
        nuevo_barril->siguiente = NULL;
        temp->siguiente = nuevo_barril;
    }
    hay_barril_mixto++;
}

void eliminarUnBarrilMixto(){
    if (lista_barriles_mixtos != NULL) {
        if (hay_barril_mixto == 1){
            free(lista_barriles_mixtos);
            lista_barriles_mixtos = NULL;
        }
        else{
            if (lista_barriles_mixtos->barril_x <= 0){
                BarrilMixto *nuevo_barril = lista_barriles_mixtos;
                lista_barriles_mixtos = lista_barriles_mixtos->siguiente;
                free(nuevo_barril);
            }
            else {
                BarrilMixto *temp = lista_barriles_mixtos;
                while (temp->siguiente->barril_x > 0) {
                    temp = temp->siguiente;
                }
                BarrilMixto *aEliminar = temp->siguiente;
                temp->siguiente = aEliminar->siguiente;
                free(aEliminar);
            }
        }
        hay_barril_mixto--;
    }
}

void eliminarBarrilMixto(){
    if (lista_barriles_mixtos != NULL) {
        if (hay_barril_mixto == 1){
            free(lista_barriles_mixtos);
            lista_barriles_mixtos = NULL;
        }
        else{
            BarrilMixto *nuevo_barril = lista_barriles_mixtos;
            lista_barriles_mixtos = lista_barriles_mixtos->siguiente;
            free(nuevo_barril);
        }
        hay_barril_mixto--;
    }
}

BarrilMixto* ultimoBarrilMixto(){
    if (hay_barril_mixto < 2){
        return lista_barriles_mixtos;
    }
    else{
        BarrilMixto *temp = lista_barriles_mixtos;
        while (temp->siguiente != NULL){
            temp = temp->siguiente;
        }
        return temp;
    }
}
