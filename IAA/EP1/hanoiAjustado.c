#include <stdio.h>
#include <stdlib.h>

int callOrder=0;

void indent(int n) {
  for (int i = 0; i < 4 - n; i++) {
    putchar('\t');
  }
}

void hanoi(char ori, char dst, char aux, int nro) {
    indent(nro);
    printf("%02d - Entrou na movimentação de %d discos de %c para %c usando %c. \n", ++callOrder, nro, ori, dst, aux);
    
    if (nro == 1) {
        indent(nro);
        printf("%02d - Move de %c para %c \n", ++callOrder, ori, dst);
    } else {
        hanoi(ori, aux, dst, nro-1); 
        hanoi(ori, dst, aux, 1);    
        hanoi(aux, dst, ori, nro-1); 
    }

    indent(nro);
    printf("%02d - Retornou da movimentação de %d discos de %c para %c usando %c. \n", ++callOrder, nro, ori, dst, aux);
}

void main(void) {
    hanoi('A', 'B', 'C', 4);
}
