#include <unistd.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "hijo.h"
#define MAX_SIZE 500000

int main(int argc, char *argv[]) {
	int pid, fd;
	int i,k; 
	int *leido;
//	int *aux;
	int *hist;
	sem_t *semhijo;
	sem_t *sempadre;
	char *txt;
//	char *txt2;
	char buffer[MAX_SIZE];
	
	fd = open(argv[1],O_RDONLY);
	
	txt = mmap(NULL,MAX_SIZE,PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON,-1,0);
	sempadre = mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON,-1,0);
	semhijo = mmap(NULL,sizeof(sem_t),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON,-1,0);
	leido = mmap(NULL,sizeof(int),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON,-1,0);
	hist = mmap(NULL,sizeof(int)*15,PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON,-1,0);
	
	*leido= -1;
	memset(txt, 0, MAX_SIZE);
	memset(hist, 0, (sizeof(int)*15));

	pid = fork();
	
	sem_init(sempadre,1,1);
	sem_init(semhijo,1,0);
	//Hijo
	if( pid == 0 ){
		while (1){
			sem_wait(semhijo);//esperando que el padre lea
//			printf("Al hijo entro \n");
			if (*leido == 0){
//				printf("soy el hijo y termino \n");
				return 0;
			}else if (*leido > 0){
//				printf("soy el hijo y proceso %d bytes \n",*leido);
				hijo(leido,txt,hist);
				sem_post(sempadre);
			}
		}
	}
	//Padre
	while (1){
		sem_wait(sempadre); 
		if(*leido==-1 && (*leido = read( fd, buffer, MAX_SIZE)) > 0){
			
			for(i=0; i < *leido ; i++){
				*(txt+i)=buffer[i];
			}
			sem_post(semhijo);
		}
		if(*leido==0){
				break;
			} 
	}
	sem_post(semhijo);
	wait(NULL);
	for(i=1,k=0;i<16; i++){
		printf("Hay %d palabras de %d letras \n",hist[i-1],i);
		k=k+hist[i-1];
	}
	printf("total: %d palabras \n",k);
	return 0;
}
