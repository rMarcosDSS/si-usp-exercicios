#include <stdio.h>
#include <stdlib.h>


void hanoi(char ori, char dst, char aux, int nro) {
	if(nro == 1) {
		printf("Move de %c", ori);
		printf(" para %c\n", dst);
	}
	else {
		hanoi(ori, aux, dst, nro-1);
		hanoi(ori, dst, aux, 1);
		hanoi(aux, dst, ori, nro-1);
	}
}

void main (void) {
	hanoi('A', 'B', 'C', 4);
}