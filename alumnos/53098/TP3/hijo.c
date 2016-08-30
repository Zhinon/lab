#include "hijo.h"
#include "contar.h"

void hijo(int *leido, char *txt, int *hist){
	
	contar(txt, leido, hist);
	
	*leido=-1;
	
}
