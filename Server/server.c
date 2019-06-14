#include <stdio.h>
#include <windows.h>
#include "server.h"
#include <ws2tcpip.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int nivel = 1;
int posMarioX = 40;
int posMarioY = 494;
int tiempo = 120;
int vidas = 3;
int key[5] = {0, 0, 0, 0, 0};
enum k {left, up, right, jump, down};

void searchC(char* message, char number){
    if (strchr(message, number) != NULL){

        int valor = number - '0';
        if(valor == 1){
            key[left] = 1;
        }
        else if(valor == 2){
            key[up] = 1;
        }
        else if(valor == 3){

            key[right] = 1;
        }
        else if(valor == 4){
            key[jump] = 1;
        }
        else if(valor == 5){
            key[down] = 1;
        }


    }else{

        int valor = number - '0';
        if(valor == 1){
            key[left] = 0;
        }
        else if(valor == 2){
            key[up] = 0;
        }
        else if(valor == 3){

            key[right] = 0;
        }
        else if(valor == 4){
            key[jump] = 0;
        }
        else if(valor == 5){
            key[down] = 0;
        }


    }

}

int iniciar_server(){

    clientes_MAX = 2;

    resp=WSAStartup(MAKEWORD(1,0),&wsaData);
    if(resp){
        printf("Error al inicializar socket\n");
        getchar();
        return resp;
    }

    hp=(struct hostent *)gethostbyname("localhost");
    if(!hp){
        printf("No se ha encontrado servidor...\n");
        getchar();
        WSACleanup();
        return WSAGetLastError();
    }

    conn_socket=socket(AF_INET,SOCK_STREAM, 0);
    if(conn_socket==INVALID_SOCKET) {
        printf("Error al crear socket\n");
        getchar();
        WSACleanup();
        return WSAGetLastError();
    }

    memset(&server, 0, sizeof(server));
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = htons(6000);

    resp = bind(conn_socket, (struct sockaddr *) &server, sizeof(server));
    if (resp == SOCKET_ERROR) {
        printf("Error al asociar puerto e ip al socket\n");
        closesocket(conn_socket);
        WSACleanup();
        getchar();
        return WSAGetLastError();
    }

    if (listen(conn_socket, 3) == SOCKET_ERROR) {
        printf("Error al habilitar conexiones entrantes\n");
        closesocket(conn_socket);
        WSACleanup();
        getchar();
        return WSAGetLastError();
    }

    for (i = 0; i < clientes_MAX; i++)
    {
        clientes[i] = 0;
    }

    printf("Esperando conexiones entrantes... \n");
    stsize = sizeof(struct sockaddr);

    return -666;
}

void iniciarComunicacion(fd_set readfds, char* message){
    while (1){
        /*
        pthread_t thread;
        pthread_create(thread, NULL, terminal(), NULL);
        pthread_join(thread, NULL);
*/
        FD_ZERO(&readfds);

        FD_SET(conn_socket, &readfds);
        max_sd = conn_socket;

        for ( i = 0 ; i < clientes_MAX ; i++)
        {
            sd = clientes[i];

            if(sd > 0)
                FD_SET( sd , &readfds);

            if(sd > max_sd)
                max_sd = sd;
        }

        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        nuevaConexion(readfds, message);

        estadoDeClientes(readfds);
    }
}

void nuevaConexion(fd_set readfds, char* message){
    if (FD_ISSET(conn_socket, &readfds))
    {
        if ((comm_socket = accept(conn_socket,(struct sockaddr *)&client, (socklen_t*)&stsize ))<0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , comm_socket , inet_ntoa(client.sin_addr) , ntohs, (client.sin_port));
/*
        if( send(comm_socket, message, strlen(message), 0) != strlen(message) )
        {
            perror("send");
        }
*/
        puts("Welcome message sent successfully");

        for (i = 0; i < clientes_MAX; i++)
        {
            if( clientes[i] == 0 )
            {
                clientes[i] = comm_socket;
                printf("Adding to list of sockets as %d\n" , i);

                break;
            }
        }
    }
}

void estadoDeClientes(fd_set readfds){

    for (i = 0; i < clientes_MAX; i++)
    {

        sd = clientes[i];
        if (FD_ISSET( sd , &readfds))
        {


            valread = recv( clientes[i] , RecvBuff, sizeof(RecvBuff), 0);

            if (strcmp(RecvBuff, ":exit") == 0) {
                getpeername(clientes[i], (struct sockaddr *) &client, (socklen_t *) &stsize);
                printf("Host disconnected , ip %s , port %d \n",
                       inet_ntoa(client.sin_addr), ntohs(client.sin_port));
                close(clientes[i]);
                clientes[i] = 0;
                printf("Closed\n");
            }else{

                searchC(RecvBuff, '1');
                searchC(RecvBuff, '2');
                searchC(RecvBuff, '3');
                searchC(RecvBuff, '4');
                searchC(RecvBuff, '5');
                printf("%d, %d, %d, %d, %d\n", key[left], key[up], key[right], key[jump], key[down]);


                //strcpy("0", buffer);
                //send(conn_socket, buffer, strlen(buffer), 0);

                //printf("Client: %s\n", RecvBuff);
                //scanf("%s", &SendBuff[0]);
                strcpy(SendBuff, "0\n");
                send(clientes[i], SendBuff, sizeof(SendBuff), 0);
                printf("Datos enviados: %s \n", SendBuff);
                memset(SendBuff, 0, 512);
                memset(RecvBuff, 0, 512);
            }
            /* logica de streaming
            else {
                printf("Client: %s\n", RecvBuff);
                if (strcmp (RecvBuff, "1") == 0){
                    strcpy(SendBuff, "izquierda");
                    send(clientes[i], SendBuff, sizeof(SendBuff), 0);
                }
                if (strcmp (RecvBuff, "2") == 0){
                    strcpy(SendBuff, "arriba");
                    send(clientes[i], SendBuff, sizeof(SendBuff), 0);
                }
                if (strcmp (RecvBuff, "3") == 0){
                    strcpy(SendBuff, "derecha");
                    send(clientes[i], SendBuff, sizeof(SendBuff), 0);
                }
                if (strcmp (RecvBuff, "4") == 0){
                    strcpy(SendBuff, "salto");
                    send(clientes[i], SendBuff, sizeof(SendBuff), 0);
                }
                //strcpy(SendBuff, "Hola\0");
                //send(clientes[i], SendBuff, sizeof(SendBuff), 0);
                printf("Datos enviados: %s \n", SendBuff);
                memset(SendBuff, 0, 512);
                memset(RecvBuff, 0, 512);
            }
             */
        }
    }
}

