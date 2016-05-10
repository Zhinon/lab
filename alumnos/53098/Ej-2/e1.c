/**
 * Ejercicio 1) Implementar una función que retorne la posición de un
 * número dado. Si el número se repite, al volver a buscar por ese
 * número, la función debería devolver la siguiente posición del
 * número buscado.
 */
#include <unistd.h>
#include <stdio.h>
#include "lib.h"
#include <stdlib.h>
#define SIZE 14

int main(int argc, char **argv)
{
    int sample[SIZE] = {0, 9, 8, 2, 2, 2, 5, 9, 5, 0, 3, 2, 3, 7};    
    int idx,idx2;
	int buscar;
	int buscar2;
	if (argc == 2){
		buscar = atoi(argv[1]);
    }else if (argc == 3){
		buscar = atoi(argv[1]);
		buscar2 = atoi(argv[2]);
	}else {
		printf("Numero de parametros erroneo\n");
		return 0;
	}
	
	for(int i=0;i<SIZE;i++){
 		printf("%d ",sample[i]);
	}
	
	idx = get_index(buscar,sample,SIZE);
	printf("\nel numero buscado se encuentra en la pos %d\n", idx);
    if (argv[2]!=NULL){ 
		if (buscar==buscar2){
			int k=0;
			int sampleaux[SIZE-idx];
			for (int i = idx+1; i<SIZE; i++){
				sampleaux[k]=sample[i];
				k=k+1;
			}
			idx2 = get_index(buscar2,sampleaux,(SIZE-idx))+idx+1;
		}else{
		idx2=get_index(buscar2,sample,SIZE);
		}
	printf("el segundo numero buscado se encuentra en la pos %d\n", idx2);
    }
	return 0;
	}

