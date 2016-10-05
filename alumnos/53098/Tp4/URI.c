#include "pagina.h"

char *URI (char *buffer,char *archivo, char *mime, char *ruta, long *longitud){

	int fd;
	int leido;

	char *buffer2 = malloc(1024*sizeof(char));
	char *buffer3 = malloc(256*sizeof(char));
	char *buffer4 = malloc(256*sizeof(char));
	
	char bufferleido[256];
	memset(bufferleido,0,sizeof(bufferleido));

	char *version = malloc(256*sizeof(char));
	//char *cabecera = malloc(256*sizeof(char));
	
	char *archivo2;

	char extensionaux[256];
	memset(extensionaux,0,sizeof(extensionaux));
	
	char *extension = malloc(256*sizeof(char));

	strncpy(buffer2,buffer,strlen(buffer));

	printf("---------------------------------------\n");
	printf ("%s\n",buffer);
	printf("---------------------------------------\n");
	
	strtok_r(buffer2," ",&version);
	//printf("El metodo es: %s\n",buffer2); // get | post
	strtok_r(NULL," ",&version);

	strtok(version,"");  // parseo solo HTTP/1.1
	strtok(version,"\n");

	
	buffer3 = strtok(buffer,"/"); 
	buffer3 = strtok(NULL," "); 
	archivo2 = buffer3; // archivo2 = index.html o cualquier otro pedido 

	strncpy(extensionaux,archivo2,strlen(archivo2));

	buffer4 = strtok(extensionaux,".");
	//printf("1-buffer 4 %s\n",buffer4);
	buffer4 = strtok(NULL," ");
	//printf("2-buffer 4 %s\n",buffer4);
	if (buffer4 == NULL){
	extension = "error";
	}else {
		extension = buffer4;
	}


	
	printf("ruta: %s\n",ruta);
	/*printf("archivo2: %s\n",archivo2);
	printf("version: %s\n",version);
	printf("Extension: %s\n",extension);
	*/

	if (strcmp(extension,"html") == 0){
			strncpy(mime,"text/html",256);
	}

	if (strcmp(extension,"jpg") == 0){
			strncpy(mime,"image/jpeg",256);
	}

	if (strcmp(extension,"pdf") == 0){
			strncpy(mime,"application/pdf",256);
	}

	if (strcmp(extension,"txt") == 0){
			strncpy(mime,"text/plain",256);
	}

	if (strcmp(extension,"png") == 0){
			strncpy(mime,"image/png",256);
	}

	if (strcmp(extension,"error") == 0){
		strncpy(mime,"error",256);
	}

	strncpy(archivo,ruta,256);
	strncat(archivo,archivo2,256);

	//printf("archivo %s\n",archivo);


	if ((fd = open(archivo,O_RDONLY)) != -1){ // si el archivo existe
			
		while ((leido = read(fd,bufferleido,sizeof(bufferleido))) > 0)

			*longitud = *longitud + leido;
			
			close (fd);
	}

	return version;
}
