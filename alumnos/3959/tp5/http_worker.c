#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include "http_worker.h"
#include "func.h"

void * http_worker (void * fd_con){
	int sd_conn = (int)fd_con;
	if((pthread_mutex_unlock(&mtx))!=0){perror("MUTEX UNLOCK");}
	pthread_detach(pthread_self());

	char buf[BUF_REQ]={0}, buf_arch[BUF_ARCH]={0}, arch_pedido[BUF_NBR_ARCH]={0};
	char out_msj[BUF_ARCH]={0},pedido[BUF_ARCH]={0}, metodo[4]={0};		
	int n,fd_arch,chk=0;

	read (sd_conn, buf,sizeof buf);
	sscanf(buf, "%s /%s" ,metodo,arch_pedido);	//lee de buf con el formato indicado
	strncpy(pedido,d_con.ROOT,strlen(d_con.ROOT));	
	strcat(pedido, arch_pedido);			//completo la ruta del archivo pedido

	if((strncmp("GET",metodo,3)==0)){
		if((fd_arch=open(pedido,O_RDONLY,0666))==-1){
			strcpy(out_msj,NOTOK_404);
			write(sd_conn,out_msj, strlen(out_msj));
			strcpy(out_msj,MESS_404);
			write(sd_conn,out_msj, strlen(out_msj));
			}
		else{
			if ((strstr(arch_pedido,".jpeg"))!=NULL){
				strcpy(out_msj,OK_JPEG);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if ((strstr(arch_pedido,".html"))!=NULL){
				strcpy(out_msj,OK_HTML);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if ((strstr(arch_pedido,".txt"))!=NULL){
				strcpy(out_msj,OK_TXT);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if ((strstr(arch_pedido,".pdf"))!=NULL){
				strcpy(out_msj,OK_PDF);
				write(sd_conn,out_msj, strlen(out_msj));
				chk+=1;
			}
			if(chk==1){
				while((n=read(fd_arch,buf_arch, sizeof buf_arch))>0){
					write(sd_conn,buf_arch,n);
				}
				close (fd_arch);
			}else{
				strcpy(out_msj,NOTOK_500);
				write(sd_conn,out_msj, strlen(out_msj));
				strcpy(out_msj,MESS_500);
				write(sd_conn,out_msj, strlen(out_msj));
			}
		}
	}else{
		strcpy(out_msj,NOTOK_501);
		write(sd_conn,out_msj, strlen(out_msj));
		strcpy(out_msj,MESS_501);
		write(sd_conn,out_msj, strlen(out_msj));
	} 
	close (sd_conn);
	pthread_exit(NULL);
}
