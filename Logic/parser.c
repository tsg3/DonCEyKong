#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <math.h>
#include "parser.h"

struct Barril{
    char* nombre;
    unsigned int x : 14;
    unsigned int y : 14;
};

struct Fuego{
    char* nombre;
    unsigned int x : 14;
    unsigned int y : 14;
};

void actualizarDatos(char* instruccion){
    char id = *instruccion;
    switch (id){
        case 'n': {
            int nivel = *(instruccion+6) - '0';
            printf("Nivel    = %d\n", nivel);
            break;
        }
        case 'p': {
            char points[7];
            points[6] = '\0';
            memcpy(points, instruccion+7,6);
            int puntos = atoi(points);
            printf("Puntos   = %d\n", puntos);
            break;
        }
        case 't': {
            char strTiempo[3];
            strTiempo[2] = '\0';
            memcpy(strTiempo, instruccion+7,2);
            int tiempo = atoi(strTiempo);
            printf("Tiempo   = %d\n", tiempo);
            break;
        }
        case 'b': {
            printf("Barriles = ");
            int largo = strlen(instruccion);
            char strBarriles[largo-9];
            memcpy(strBarriles, instruccion+9,largo-10);
            strBarriles[largo-10] = '\0';
            int comas = 0;
            for (int i = 0; *(strBarriles+i) != '\0'; i++){
                if ( *(strBarriles+i) == ','){
                    comas++;
                }
            }
            int n = comas + 1;
            struct Barril barriles[n];
            int largoNombre = 0;
            int pos = 0;
            for (int i = 0; i < n; i++){
                for (int j = 0; *(strBarriles+j+pos) != '-'; j++){
                    largoNombre++;
                }
                struct Barril barril;
                barril.nombre = (char *) malloc(largoNombre+1);
                char strX[5], strY[5];
                memcpy(strX, strBarriles + pos + largoNombre + 1 ,4);
                memcpy(strY, strBarriles + pos + largoNombre + 6 ,4);
                memcpy(barril.nombre, strBarriles + pos ,largoNombre);
                strX[4] = '\0';
                strY[4] = '\0';
                barril.nombre[largoNombre] = '\0';
                int x = atoi(strX);
                int y = atoi(strY);
                barril.x = x;
                barril.y = y;
                barriles[i] = barril;
                pos += 13 + largoNombre - 2;
                largoNombre = 0;
            }
            for (int i = 0; i < n; i++) {
                printf("\n           --> Barril = %s ~ PosX %d ~ PosY = %d ",barriles[i].nombre,barriles[i].x,barriles[i].y);
            }
            printf("\n");
            break;
        }
        case 'm': {
            char strX[5], strY[5];
            memcpy(strX, instruccion+6,4);
            memcpy(strY, instruccion+11,4);
            strX[4] = '\0';
            strY[4] = '\0';
            int x = atoi(strX);
            int y = atoi(strY);
            printf("MarioX   = %d\nMarioY   = %d\n", x, y);
            break;
        }
        case 'f': {
            printf("Fuegos   = ");
            int largo = strlen(instruccion);
            char strFuegos[largo-7];
            memcpy(strFuegos, instruccion+7,largo-8);
            strFuegos[largo-8] = '\0';
            int comas = 0;
            for (int i = 0; *(strFuegos+i) != '\0'; i++){
                if ( *(strFuegos+i) == ','){
                    comas++;
                }
            }
            int n = comas + 1;
            struct Fuego fuegos[n];
            int largoNombre = 0;
            int pos = 0;
            for (int i = 0; i < n; i++){
                for (int j = 0; *(strFuegos+j+pos) != '-'; j++){
                    largoNombre++;
                }
                struct Fuego fuego;
                fuego.nombre = (char *) malloc(largoNombre+1);
                char strX[5], strY[5];
                memcpy(strX, strFuegos + pos + largoNombre + 1 ,4);
                memcpy(strY, strFuegos + pos + largoNombre + 6 ,4);
                memcpy(fuego.nombre, strFuegos + pos ,largoNombre);
                strX[4] = '\0';
                strY[4] = '\0';
                fuego.nombre[largoNombre] = '\0';
                int x = atoi(strX);
                int y = atoi(strY);
                fuego.x = x;
                fuego.y = y;
                fuegos[i] = fuego;
                pos += 13 + largoNombre - 2;
                largoNombre = 0;
            }
            for (int i = 0; i < n; i++) {
                printf("\n           --> Fuego = %s ~ PosX %d ~ PosY = %d ",fuegos[i].nombre,fuegos[i].x,fuegos[i].y);
            }
            printf("\n");
            break;
        }
        case 'v': {
            int vidas = *(instruccion+6) - '0';
            printf("Vidas    = %d\n", vidas);
            break;
        }
        default: printf("ERROR\n");
    }
}

void analizarInstruccion(char instruccion[]){

    char* p = strtok(instruccion, ";");
    while (p) {
        actualizarDatos(p);
        p = strtok(NULL, ";");
    }

}

void borrarCorchetes(char* instruccion){
    int i;
    for (i = 0; instruccion[i+1] != '}' ; i++){
        *(instruccion+i) = *(instruccion + i + 1);
    }
    *(instruccion+i) = '\0';
    *(instruccion+i+1) = '\0';
}