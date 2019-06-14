#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
int nivel = 1;
int puntaje = 0;
int posMarioX = 40;
int posMarioY = 494;
int tiempo = 60;
int vidas = 3;

char barril[3];

int contarDigitos(int num){
    int count = 0;

    while(num != 0){
        num = num/10;
        count++;
    }
    return count;
}
void agregarCeros(char* respuesta, int cantidad, int num){

    int count = contarDigitos(num);
    int cantidadCeros = cantidad - count;

    memset(respuesta, 0, cantidad);

    char transform[10];

    while (cantidadCeros != 0){
        strcat(respuesta, "0");
        cantidadCeros--;
    }

    itoa(num, transform, 10);


    strcat(respuesta, transform);

}

void crearTexto(char* SendBuff){


    char transform[20];

    itoa(nivel, transform, 10);

    strcat(SendBuff, transform);
    strcat(SendBuff, ");puntaje(");

    agregarCeros(transform, 6, puntaje);

    strcat(SendBuff, transform);
    strcat(SendBuff, ");tiempo(");

    itoa(tiempo, transform, 10);

    strcat(SendBuff, transform);
    strcat(SendBuff, ");barriles(");

    if(strcmp(barril, "1") == 0){
        strcat(SendBuff,"b11-0001.0001");
    }
    if(strcmp(barril, "2") == 0){
        strcat(SendBuff,"b21-0001.0001");
    }
    if(strcmp(barril, "3") == 0){
        strcat(SendBuff,"b31-0001.0001");
    }

    strcat(SendBuff, ");mario(");

    agregarCeros(transform, 4, posMarioX);

    strcat(SendBuff, transform);
    strcat(SendBuff, ".");

    agregarCeros(transform, 4, posMarioY);

    strcat(SendBuff, transform);
    strcat(SendBuff, ");fuegos();vidas(");

    itoa(vidas, transform, 10);

    strcat(SendBuff, transform);
    strcat(SendBuff, ")}");



}


DWORD WINAPI listenerBarriles(){

    while(1) {
        printf("Que barril desea lanzar?\n");
        printf("1: Barril normal\n");
        printf("2: Barril caida libre\n");
        printf("3: Barril mix\n");

        scanf("%s", barril);
        printf("Se spawneo un %s\n\n",barril);
    }

    return 0;

}



int main() {
    /*
    CreateThread(NULL, 0, listenerBarriles, NULL, 0, 0);

    while(1) {

        char SendBuff[512] = "{nivel(";
        crearTexto(SendBuff);
        printf("%s\n", SendBuff);
        Sleep(10000);

    }*/

    char a = '2';


    int b = a - '0';

    printf("%d", b);
}

