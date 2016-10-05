#ifndef _PAGINA_H_
#define _PAGINA_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>


void pagina(int sd_conn, struct sockaddr *, char *ruta);

char *URI (char *buffer,char *archivo, char *mime, char *ruta, long *longitud);

#endif
