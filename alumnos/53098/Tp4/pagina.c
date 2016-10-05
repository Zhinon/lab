#include "pagina.h"

void pagina(int sd_conn, struct sockaddr * cliente, char *ruta){
	
	int fd;
	int leido;
	int leido2;

	long longitud = 0;

	char buffer[1024];
	memset(buffer,0,sizeof(buffer));

	char buffer2[1024];
	memset(buffer2,0,sizeof(buffer2));
	
	char archivo[256];

	char mime[256]; 
	char *version = NULL;
	char *estado = NULL;
	char cabecera[512];
	char *version2 = "HTTP/1.1";
	if ((leido = read(sd_conn, buffer, sizeof(buffer))) > 0){
		memset(archivo,0,sizeof(archivo));
		memset(mime,0,sizeof(mime));
		//memset(cabecera,0,sizeof(cabecera));

		version = URI(buffer,archivo,mime,ruta, &longitud);
		// buffer = GET 
		
		if (!(strncmp(buffer,"GET",3) == 0)){
			estado = "500 INTERNAL SERVER ERROR\n";
			write(sd_conn,estado,strlen(estado));
			exit(0);
		} else if (!(strncmp(version,"HTTP/1.1",8) == 0)){
			estado = "ERROR VERSION --> HTTP/1.1\n";
			write(sd_conn,estado,strlen(estado));
			exit(0);
		}

		else if ((fd = open(archivo, O_RDONLY)) < 0){
			estado = "404 NOT FOUND\n";
			write(sd_conn,estado,strlen(estado));
		}

		else { // 200 ok
			estado = "200 OK";
//			printf("estado %s\n",estado);
//			printf("version %s\n",version);	
			//printf("la version es: %s\n",version);
			
			
			leido2 = snprintf(cabecera, sizeof cabecera, "%s %s\nContent-Length: %ld\nContent-Type: %s\n\n", version2, estado, longitud, mime);

			//printf("cabecera %s\n",cabecera);
			write(sd_conn,cabecera,leido2);

			while((leido2 = read(fd, buffer2, sizeof buffer2)) > 0){
				write(sd_conn,buffer2,leido2);
				memset(buffer2,0,sizeof(buffer2));
			}// fin while
			close(fd);
			close(sd_conn);
		} // fin else

	} // fin if leido

	close(fd);
	close(sd_conn);

} // fin funcion
