#include "pagina.h"

int main(int argc, char * const *argv) {
	int sd;
	int sd_conn;
	int opt = 1;
	int optlen = sizeof(opt);
	socklen_t addrlen;
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;

	addrlen = sizeof(cli_addr);

	int opcion;
	int puerto;
	char ruta[24] = "/home/zhinon/Documentos/";

	
	while ((opcion = getopt(argc,argv, "p:")) != -1){
		switch (opcion){
			case 'p':  
				puerto=atoi(optarg);	
				break;
		} 
	} 

	if (puerto < 1){
		write (STDERR_FILENO , "Puerto erroneo\n",15 );
		return -1;
	}

	sd = socket (AF_INET,SOCK_STREAM,0);

	if (sd < -1){
		perror("Error en la creacion del socket\n");
		return -1;
	}

	srv_addr.sin_family=AF_INET;
	srv_addr.sin_port = htons(puerto);
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, optlen);

	if (bind(sd,(struct sockaddr*) &srv_addr,sizeof(srv_addr))==-1){
		perror("Error en bind\n");
		return -1;
	}

	if(listen(sd,10)<0){
		perror("Error en listen\n");
		return -1;
	}

	signal(SIGCHLD,SIG_IGN);

	while( (sd_conn = accept(sd, (struct sockaddr *) &cli_addr, &addrlen)) > 0) {
		switch (fork()) {
			case 0: // hijo
				//printf("cliente: %s en el puerto %d \n",inet_ntoa((struct in_addr) cli_addr.sin_addr),puerto);
				pagina(sd_conn, (struct sockaddr *) &cli_addr,ruta);
				return 0;

			case -1: // error
				perror("Error en la creacion de fork\n");
				break;

			default: // padre
				break;
		} 
		close(sd_conn);
	} 


	return 0;
} 
