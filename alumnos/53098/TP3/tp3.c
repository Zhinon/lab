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
	int i; 
	int *leido;
//	int *aux;
	int *hist;
	sem_t *sem;
	char *txt;
	char buffer[MAX_SIZE];
	
	fd = open(argv[1],O_RDONLY);
	
	txt=mmap(NULL,MAX_SIZE+sizeof(sem_t)+ sizeof(int)+(sizeof(int)*15),PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON,-1,0);
	sem=(sem_t *)(txt + MAX_SIZE);
	leido=(int *)(txt + MAX_SIZE + sizeof(sem_t));
	*leido= -1;
	hist=(int *)(txt + MAX_SIZE + sizeof(sem_t) +sizeof(int));	
	memset(hist, 0, (sizeof(int)*15));

	pid = fork();
	
	sem_init(sem,1,1);
	//Hijo
	if( pid == 0 ){
		while (1){
			sem_wait(sem);
			if (*leido == -1) {
//				printf("soy hijo y entre en el case -1 \n");
				sem_post(sem);
			}else if (*leido == 0){
//				printf("soy hijo y entre en el case 0 \n");
				break;
			}else if (*leido > 0){
				hijo(leido,txt,hist);
				sem_post(sem);
//				printf("soy hijo y tengo que procesar %d bytes\n", *leido);

			}
		}
		sem_post(sem);
//		printf("soy hijo y termine\n");
		return 0;
	}
	//Padre
	while (1){
		sem_wait(sem); 
		if(*leido == -1 && (*leido = read( fd, buffer, MAX_SIZE)) > 0){
			for(i=0; i < *leido ; i++){
				*(txt+i)=buffer[i];
			}
			sem_post(sem);
		}else if (*leido == 0){
			break;
		}
	}
	
	sem_post(sem);
	for(i=1;i<16; i++){
		printf("Hay %d palabras de %d letras \n",hist[i-1],i);
	}
	return 0;
}
