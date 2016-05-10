#include "lib.h"

int get_index(int value, int *array, int len)
{
    int i;
    for (i=0; i<len; i++) {
    	if(array[i]==value){
		return i;	
	}           
    }

    return -1;
}

int get_max_repeating_num(int *array, int len)
{
    int repeticiones[2][len];
	int mayor;
	for (int i=0;i<len;i++){
		repeticiones[0][i]=array[i];
		repeticiones[1][i]=0;
	}	
	for (int i=0;i<len;i++){
		for(int j=0;j<len;j++){
			if (i!=j && repeticiones[0][i]==repeticiones[0][j]){
				repeticiones[1][i]=repeticiones[1][i]+1;
			} 
		
		}
	}
	mayor=repeticiones[0][0];
	for (int i=0; i<len;i++){
		for (int j=i+1; j<len; j++){
			if (repeticiones[1][j]>repeticiones[1][i]){
			mayor=repeticiones[0][j];				
			}
		}
	}
		
    return mayor;
}
