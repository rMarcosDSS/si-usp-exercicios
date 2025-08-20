/*********************************************************************/
/** ACH 2001 - Introdução à Programação                             **/
/** EACH-USP - Primeiro Semestre de 2023                            **/
/** Turma 02 - Prof. Marcos Lordello Chaim                          **/
/**                                                                 **/
/** Segundo Exercício-Programa                                      **/
/**                                                                 **/
/** <Marcos Ruan da Silva Santos> <14760209>                        **/
/**                                                                 **/
/** <19/07/2023>                                                    **/
/*********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NumeroMaxTimes 20
#define NumeroMaxRodadas 38
#define NumeroMaxJogos NumeroMaxTimes * NumeroMaxRodadas

typedef struct auxtime {
  int PontosGanhos;
  int GolsMarcados;
  int GolsSofridos;
  int SaldoDeGols;
  int Vitorias;
  int Empates;
  int Derrotas;
  float GolAverage;
  char nome[31];
} time;

typedef struct auxjogo {
  char local[30];
  char visitante[30];
  int golslocal;
  int golsvisitante;
} jogo;

void lenometime(char * s) {
  int i;
  s[0] = '\0';
  char c;
  c = getchar();
  for(i = 0; c != ',' && i < 30;++i)
    {
      // if(c == '\n')
      //   continue;
      s[i] = c;
      c = getchar();
    }
  s[i] = '\0';
  //printf("%s\n",s);
}

// Ordena por Pontos

void ordenaPontos(time * timescampeonato, int notimes)
{
  // Adicione seu código para ordenar em ordem decrescente de pontos ganhos
     int i, j;
    time temp;

    for (i = 0; i < notimes - 1; i++) {
        for (j = 0; j < notimes - i - 1; j++) {
            if (timescampeonato[j].PontosGanhos < timescampeonato[j + 1].PontosGanhos ||
                (timescampeonato[j].PontosGanhos == timescampeonato[j + 1].PontosGanhos &&
                 timescampeonato[j].SaldoDeGols < timescampeonato[j + 1].SaldoDeGols)) {

                temp = timescampeonato[j];
                timescampeonato[j] = timescampeonato[j + 1];
                timescampeonato[j + 1] = temp;
            }
        }
    }
}

// Ordena por saldo de gols

void ordenaSaldoGols(time * timescampeonato, int notimes)
{
  // Adicione seu código para ordenar em ordem decrescente de saldo de gols
}

// Encontra se o time já está no arranjo de times do campeonato

int encontratime(time *timescampeonato, char * nome, int notimes) {
  for(int i = 0; i<notimes;i++){
      if (nome == timescampeonato[i].nome) {
          return i;
      }
  }

  return -1; // retorna -1 se o time com o nome "nome" não existe
}

int crialistatimes(time * timescampeonato, jogo * dadosjogos, int numerojogos) {
    char nomesTimes[numerojogos * 2][31];

    for (int j = 0; j < numerojogos; j++) {
        strcpy(nomesTimes[j], dadosjogos[j].local);
    }

    for (int j = 0; j < numerojogos; j++) {
        strcpy(nomesTimes[j + numerojogos], dadosjogos[j].visitante);
    }

    int numUniqueTeams = 0;
    char conjuntoAuxiliar[numerojogos * 2][31];

    for (int j = 0; j < numerojogos * 2; j++) {
        int nomeExiste = 0;
        for (int k = 0; k < numUniqueTeams; k++) {
            if (strcmp(nomesTimes[j], conjuntoAuxiliar[k]) == 0) {
                nomeExiste = 1;
                break;
            }
        }

        if (!nomeExiste) {
            strcpy(timescampeonato[numUniqueTeams].nome, nomesTimes[j]);
            strcpy(conjuntoAuxiliar[numUniqueTeams], nomesTimes[j]);
            numUniqueTeams++;
        }
    }

  
    return numUniqueTeams; // retorna o número de times únicos
}

// Computa dados times

void computadadostimes(time * timescampeonato,int notimes,jogo * dadosjogos,int numerojogos) {
// Preenche os campos dos elementos do arranjo timescampeonato: Vitorias,
// GolsSofridos, GolsMarcados, Golsaverage, SaldoDeGols, PontosGanhos.
// Adicione seu código

     

    for (int i = 0; i < notimes; i++) {
        
        timescampeonato[i].PontosGanhos = 0; 
        timescampeonato[i].GolsMarcados = 0; 
        timescampeonato[i].GolsSofridos = 0; 
        timescampeonato[i].SaldoDeGols = 0; 
        timescampeonato[i].Vitorias = 0; 
        timescampeonato[i].Empates = 0; 
        timescampeonato[i].Derrotas = 0; 
        timescampeonato[i].GolAverage = 0; 
        
        for (int j = 0; j < numerojogos; j++) {
              if(strcmp(timescampeonato[i].nome, dadosjogos[j].local) == 0) {
                  
                  timescampeonato[i].GolsMarcados += dadosjogos[j].golslocal;
                  timescampeonato[i].GolsSofridos += dadosjogos[j].golsvisitante;
            
                  
                  if (dadosjogos[j].golslocal>dadosjogos[j].golsvisitante) {
                      timescampeonato[i].Vitorias++;
                  }else if (dadosjogos[j].golslocal<dadosjogos[j].golsvisitante) {
                      timescampeonato[i].Derrotas++;
                  } else {
                      timescampeonato[i].Empates++;
                  }
                  
              } else if (strcmp(timescampeonato[i].nome, dadosjogos[j].visitante) == 0) {
                  
                  timescampeonato[i].GolsSofridos += dadosjogos[j].golslocal;
                  timescampeonato[i].GolsMarcados += dadosjogos[j].golsvisitante;
                  
                  if (dadosjogos[j].golslocal<dadosjogos[j].golsvisitante) {
                      timescampeonato[i].Vitorias++;
                  }else if (dadosjogos[j].golslocal>dadosjogos[j].golsvisitante) {
                      timescampeonato[i].Derrotas++;
                  } else {
                      timescampeonato[i].Empates++;
                  }
                  
              }
         
    }
      
      timescampeonato[i].SaldoDeGols = timescampeonato[i].GolsMarcados - timescampeonato[i].GolsSofridos;
       
      timescampeonato[i].PontosGanhos = (3 * timescampeonato[i].Vitorias) + timescampeonato[i].Empates;
       
      if (timescampeonato[i].GolsSofridos == 0 ){
          timescampeonato[i].GolAverage = timescampeonato[i].GolsMarcados;
      }
      else {
      timescampeonato[i].GolAverage = (float) timescampeonato[i].GolsMarcados /  timescampeonato[i].GolsSofridos;
      }
    }
 }

// Imprime classificação

void imprimeclassificacao(time * timescampeonato,int notimes){
 // Adicione seu código
  printf("Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average");
 
 
 for (int i = 0; i < notimes; i++) {
    printf("\n%i,%s,%i,%i,%i,%i,%i,%.3lf", i+1,
           timescampeonato[i].nome, timescampeonato[i].PontosGanhos,
           timescampeonato[i].Vitorias, timescampeonato[i].Empates,
           timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols,
           timescampeonato[i].GolAverage);
 }

}

// Salva os dados da classificação dos tipos em arquivo no disco

void salvaclassificacao(time * timescampeonato,int notimes, char * arquivo){
// Adicione seu código
    FILE *file = fopen(arquivo, "w");
    if (file == NULL) {
        printf("Erro %s\n", arquivo);
        return;
    }

    fprintf(file, "Posicao,Nome,Pontos Ganhos,Vitorias,Empates,Derrotas,Saldo de Gols,Gol Average\n");

    for (int i = 0; i < notimes; i++) {
        fprintf(file, "%d,%s,%d,%d,%d,%d,%d,%.3lf\n", i + 1,
                timescampeonato[i].nome, timescampeonato[i].PontosGanhos,
                timescampeonato[i].Vitorias, timescampeonato[i].Empates,
                timescampeonato[i].Derrotas, timescampeonato[i].SaldoDeGols,
                timescampeonato[i].GolAverage);
    }

    fclose(file);

}

int main() {
  time times[NumeroMaxTimes];
  jogo jogos[NumeroMaxJogos];
  int i, nojogos, golslocal = 0, golsvisitante = 0;
  char local[30],visitante[30];

  printf("Entre os jogos no formato \"time local, time visitante, golslocal, golsvisitante\" (gols local negativo encerra a entrada de dados)\n");
  for(i = 0; i < NumeroMaxJogos; ++i) {
    lenometime(local);
    lenometime(visitante);
    scanf("%d,%d",&golslocal,&golsvisitante);
    getchar(); // consome o enter do scanf
    // printf("local %s visitante %s ", local, visitante);
    // printf("golslocal %d, golsvisitante %d\n", golslocal,golsvisitante);
    if (golslocal < 0)
      break; // termina a entrada de dados

    if(strcmp(local,visitante) == 0)
      continue; // possui o mesmo nome time local e visitante

    strncpy(jogos[i].local,local,30);
    strncpy(jogos[i].visitante,visitante,30);

    jogos[i].golslocal = golslocal;
    jogos[i].golsvisitante = golsvisitante;
  }
  nojogos = i;

//   Confirmando os valores lidos
//   for(i=0; i < nojogos;++i)
//      printf("%d:%s,%s,%d,%d\n",i+1,jogos[i].local,jogos[i].visitante,jogos[i].golslocal,jogos[i].golsvisitante);

  int notimes = crialistatimes(times,jogos,nojogos);
  // printf("Notimes: %d\n", notimes);
  // printf("\nTimes:\n");
  // for(i=0; i < notimes;++i)
  //   printf("%2d:%s\n",i+1,times[i].nome);

  computadadostimes(times,notimes,jogos,nojogos);
  // printf("\nResultado da computação dos dados dos jogos:\n");
  // for(i=0; i < notimes;++i)
  //   {
  //   printf("%d:%s\n",i,times[i].nome);
  //   printf("Pontos ganhos: %d\n",times[i].PontosGanhos);
  //   printf("Gols marcados: %d\n",times[i].GolsMarcados);
  //   printf("Gols sofridos: %d\n",times[i].GolsSofridos);
  //   printf("Vitorias: %d\n",times[i].Vitorias);
  //   printf("Saldo de gols: %d\n",times[i].SaldoDeGols);
  //   printf("Gols average: %2.3f\n",times[i].GolAverage);
  // }
    ordenaPontos(times,notimes);
  imprimeclassificacao(times,notimes);

  // Opcional
  salvaclassificacao(times,notimes,"campeonatoIP.dat");
  

}