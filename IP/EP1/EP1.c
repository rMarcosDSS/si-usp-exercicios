/*********************************************************************/
/**   ACH2001 - Introducao a Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2022                          **/
/**   Turma 02 - Prof. Marcos Lordello Chaim                        **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Marcos Ruan da Silva Santos                   14760209        **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>


int verificaAnoBissexto(int an) {
    if ((an%4==0) && (an%100!=0 || an%400==0)) {
        return 1;
    } 
}

int verificaDataValida(int d, int m, int a) {
    if ((d>31)||(d<1)||(m>12)||(m<1)) {
       return 0;
    } 
}

int main() {
    int dia, mes, ano, dayear, fev, dconv;

    printf("Entre com a data de inicio do ano letivo:\n");
    printf("Entre com o dia: ");
    scanf("%d", &dia);
    printf("Entre com o mes: ");
    scanf("%d", &mes);
    printf("Entre com o ano: ");
    scanf("%d", &ano);

    if(!verificaDataValida(dia, mes, ano))
      {
        printf("Dados incorretos\n");
        exit(1); 
      }

    dayear = verificaAnoBissexto(ano);
    if (dayear == 1) {
        dayear = 366;
        fev = 29;
    } else {
         dayear = 365;
         fev = 28;
    }
    
    
    
    printf("Data de inicio do ano letivo: %i/%i/%i", dia, mes, ano);  
      
    printf("\nProximos dias de encontro de todos os clubes:");
    
    for (int i = 1; i <= dayear; i++) {
        dia++;
        
        switch(mes) {
        case 2:
            if (dia > fev) {
                dia = 1;
                mes++;
                }
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            if (dia > 31) {
                dia = 1;
                mes++;
                }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            if (dia > 30) {
                dia = 1;
                mes++;
                }
            break;
            }

            if (mes > 12) {
                    break;
                }
        
    //   Esporte - 2
    //   Literatura - 3
    //   Fotografia - 4
    //   Xadrez - 5
    //   Musica - 6
       
        if (i % 2 == 0 && i % 3 == 0 && i % 4 == 0 && i % 5 == 0 && i % 6 == 0) {
            printf("\n%i/%i/%i", dia, mes, ano);
        }
    }

  }