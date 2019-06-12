#include "GUI/window.h"
#include <stdio.h>
#include <windows.h>
#include "Server/server.h"

int main(){

    int execution = initialize();

    switch (execution){
        case 1: break;
        case 0: return 0;
        case -1: return -1;
        default: return 1;
    }

    reading();

    finishExecution();

    /*int inicio = iniciar_server();

    if (inicio == -666) {

        fd_set readfds;
        char *message = "ECHO Daemon v1.0 \r\n";

        iniciarComunicacion(readfds, message);

        //Aun no llega
        return (EXIT_SUCCESS);
    }
    else{
        return (EXIT_FAILURE);
    }*/
}