#ifndef DONCEYKONGUSER_SERVER_H
#define DONCEYKONGUSER_SERVER_H

#include <stdio.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <string.h>

char SendBuff[512], RecvBuff[512];
WSADATA wsaData;
SOCKET conn_socket, comm_socket;
SOCKET comunicacion;
struct sockaddr_in server;
struct sockaddr_in client;
struct hostent *hp;
int resp, stsize;
int clientes[2];
int clientes_MAX;
int activity, sd, max_sd, i, valread;

int iniciar_server();
void iniciarComunicacion(fd_set readfds, char* message);
void nuevaConexion(fd_set readfds, char* message);
void estadoDeClientes(fd_set readfds);

#endif //DONCEYKONGUSER_SERVER_H
