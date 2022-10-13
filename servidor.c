#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	
	if (argc != 2)
		error("\nParemetres erronis\nUs correcte: server num_port\n\n");
	
	//inicializacion
	//Abrimos el socket
	
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("Error creando socket");
	
	//Bind al puerto
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	//asocia el socket en cualquier IP de la maquina
	
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY); /* La IP local */
	
	//Escuchando en el puerto 9050
	
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		error("Error en bind");
	
	//Limitamos peticiones pendientes aka cola
	
	// Limitem el nombre de connexions pendents
	if (listen(sock_listen, 10) < 0)
		error("Error en listen");
	
	int i;
	//Atendemos cualquier peticion
	for(;;){
		
		printf("Escuchando \n");
		sock_conn = accept(sock_listen, NULL, NULL);
		printf("Conexion recibida \n");
		
		//sock_conn es el socket de nuestro cliente
		
		//Recibimos su nombre, que dejamos en el buff (buff=peticion)
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf("Recibido\n");
		
		//Indicativo del fin del buffer \0
		peticion[ret]='\0';
		
		close(sock_conn);
		
		
}

