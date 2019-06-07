#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

char SendBuff[512],RecvBuff[512];

int main(int argc, char *argv[]){
  
  WSADATA wsaData;
  SOCKET conn_socket;
  struct sockaddr_in server;
  struct hostent *hp;
  int resp;
  
  //Inicializamos la DLL de sockets
  resp=WSAStartup(MAKEWORD(1,0),&wsaData);
  if(resp){
    printf("Error al inicializar socket\n");
    getchar();return -1;
  }

  //Obtenemos la IP del servidor... en este caso
  // localhost indica nuestra propia máquina...
  hp=(struct hostent *)gethostbyname("localhost");

  if(!hp){
    printf("No se ha encontrado servidor...\n");
    getchar();WSACleanup();return WSAGetLastError();
  }

  // Creamos el socket...
  conn_socket=socket(AF_INET,SOCK_STREAM, 0);
  if(conn_socket==INVALID_SOCKET) {
    printf("Error al crear socket\n");
    getchar();WSACleanup();return WSAGetLastError();
  }
   
  memset(&server, 0, sizeof(server)) ;
  memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
  server.sin_family = hp->h_addrtype;
  server.sin_port = htons(6000);

  // Nos conectamos con el servidor...
  if(connect(conn_socket,(struct sockaddr *)&server,sizeof(server))==SOCKET_ERROR){
    printf("Fallo al conectarse con el servidor\n");
    closesocket(conn_socket);
    WSACleanup();getchar();return WSAGetLastError();
  }
  printf("Conexión establecida con: %s\n", inet_ntoa(server.sin_addr));
  
  /*strcpy(SendBuff,"Hola");
  send(conn_socket,SendBuff,sizeof(SendBuff),0);
  printf("Datos enviados: %s \n", SendBuff);*/
  
  recv(conn_socket,RecvBuff, sizeof(RecvBuff), 0);
  printf("Mensaje recibido: %s \n", RecvBuff);
  
  char *message = "TESTEO\0";
  strcpy(SendBuff,message);
  
  char buffer[512];
  
  while(1){
	printf("Enter a message :\n");
	scanf("%s", &buffer[0]);
	send(conn_socket, buffer, strlen(buffer), 0);
	printf("Data enviada : %s\n",buffer);
	if(strcmp(buffer, ":exit") == 0){
		close(conn_socket);
		printf("[-]Disconnected from server.\n");
		return 1;
	}
	if(recv(conn_socket, buffer, 1024, 0) < 0){
		printf("[-]Error in receiving data.\n");
	}
	else{
		printf("Server: \t%s\n", buffer);
	}
  }
  
  // Cerramos el socket y liberamos la DLL de sockets
  close(conn_socket);
  WSACleanup();
  return EXIT_SUCCESS;
} 