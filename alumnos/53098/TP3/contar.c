#include <string.h>

void contar(char *txt, int *leido, int *hist){

	int largo=0;
	char *token=NULL;
	const char *delim = " !?¿¡!.,;:()-_\t\r\n";
	for (token=strtok(txt, delim); token != NULL; token=strtok(NULL, delim)) {
		largo = strlen(token);
		if (largo > 15){
			hist[14]++;
		}else {
			hist[largo-1]++;
		}
	}
} 

