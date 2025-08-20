/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2025                          **/
/**   Prof. Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Marcos Ruan da Silva Santos                  14760209         **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define INFINITO 999999

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
    int numVertices;
    int numArestas;
    bool** matriz;
} Grafo;


/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}



/* Estrutura para representar elementos de uma lista ligada de vertices */
typedef struct aux{
  int vertice;
  struct aux* prox;
} ElementoLista, *PONT;


/* Estrutura para representar elementos de uma lista ligada com arestas
   (pares de vertices)*/
typedef struct aux2{
  int origem;
  int destino;
  struct aux2* prox;
} ArestaLista, * PONT2;


/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencia (preenchida com ARESTAS_INVALIDAS),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
  }
  return true;
}


/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia. 
*/
bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->numArestas++;
  }
  return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->numArestas--;
  return true;
}


/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  int x, y, a, total;
  if (numVertices < 1 || numArestas >= numVertices*numVertices/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);

  a = 0;
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}



/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencias.
*/
void exibeGrafo(Grafo* g){
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (v=%i; a=%i)\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);  
    printf("\n");
  }
  printf("\n");
}


/* Funcao que calcula a distancia e o predecedor considerando todos os pares
   vertices (distancia de todos para todos), com base no algoritmo de 
   Floyd-Warshall.
*/
void calculaDistanciaFloydWarshall(Grafo* g, int** dist, int** pred){
  int i, j, k, n;
  n = g->numVertices;
  for(i=0;i<n;i++)
    for(j=0;j<n;j++)
      if(g->matriz[i][j] != false){
        dist[i][j] = g->matriz[i][j];
        pred[i][j] = i;
      }else{
        dist[i][j] = INFINITO;
        pred[i][j] = -1;
      }
  for(i=0;i<n;i++) {
    dist[i][i] = 0;
    pred[i][i] = i;
  }

  for(k=0;k<n;k++)
    for(i=0;i<n;i++)
      for(j=0;j<n;j++)
        if(dist[i][j] > dist[i][k] + dist[k][j]){
          dist[i][j] = dist[i][k] + dist[k][j];
          pred[i][j] = pred[k][j];
        }
}


/* Funcao que exibe uma matriz de distancias.
   Caso a distancia seja INFINITO, imprime '-'.
*/
void exibeMatrizDistancias(int** matriz, int n){
  printf("Exibindo matriz de distancias.\n");
  int x, y;
  for (x=0; x<n; x++) printf("\t%3i", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%i", x);
    for (y=0; y<n; y++){
      if (matriz[x][y] == INFINITO) printf("\t-");
      else printf("\t%3i",matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe uma matriz de predecessores.
   Caso a distancia seja INFINITO, imprime '-'.
*/
void exibeMatrizPredecessores(int** matriz, int n){
  printf("Exibindo matriz de predecessores.\n");
  int x, y;
  for (x=0; x<n; x++) printf("\t%3i", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%i", x);
    for (y=0; y<n; y++){
      printf("\t%3i",matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(double* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%4.3f\t",arranjo[x]);
  }
  printf("\n\n");
}




/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep2/ep2.pdf        */


//Inicializa o array com zeros
void IniciaArrayComZeros(double* valores, int numVertices) {
  int i;
  for (i = 0; i < numVertices; i++) {
    valores[i] = 0.0;
  }
}


/* Funcao que calcula a Centralidade de Grau de todos os vertices. */
void centralidadeDeGrau(Grafo* g, double* valores) {

  IniciaArrayComZeros(valores, g->numVertices);

  //Visita cada vertice i
  int i;
  for (i = 0; i < g->numVertices ; i++){
    double grau = 0;

    //Visita todos os vertices calculando o grau de entrada
    int j;
    for (j = 0; j < g->numVertices; j++){
      if (i!=j){
        if (g->matriz[j][i]) grau++;
      }

      //Calcula a centralidade
      valores[i] = grau / (g->numVertices - 1);
    }
    
    // printf ("\n Vertice: %i, Grau: %f, \n ", i, grau);

  }
}


/* Funcao que calcula a Centralidade de Proximidade de todos os vertices. */
void centralidadeDeProximidade(Grafo* g, double* valores) {

  IniciaArrayComZeros(valores, g->numVertices);

  //Cria um grafo de distância
  Grafo dist;
  inicializaGrafo(&dist, g->numVertices);

  //Cria um grafo de predecessores
  Grafo pred;
  inicializaGrafo(&pred, g->numVertices);

  calculaDistanciaFloydWarshall(g, dist.matriz, pred.matriz);

  // exibeMatrizDistancias(dist.matriz, g->numVertices);


  //Visita cada vertice i
  int i;
  for (i = 0; i < g->numVertices; i++) {
    double soma = 0;

    //Visita todos os vertices, somando a distancia da matriz
    int j;
    for (j = 0; j < g->numVertices; j++){

        soma = soma + dist.matriz[i][j];

    }

    //Calcula a centralidade
    valores[i] = (g->numVertices -1) / soma;
  }

  //Libera a memoria dos grafos que foram criados
  liberaGrafo(&dist);
  liberaGrafo(&pred);
}


/* Funcao que calcula a Centralidade de Intermediacao de todos os vertices. */
void centralidadeDeIntermediacao(Grafo* g, double* valores) {

  IniciaArrayComZeros(valores, g->numVertices);

  //Cria um grafo de distância
  Grafo dist;
  inicializaGrafo(&dist, g->numVertices);

  //Cria um grafo de predecessores
  Grafo pred;
  inicializaGrafo(&pred, g->numVertices);

  calculaDistanciaFloydWarshall(g, dist.matriz, pred.matriz);

  // exibeMatrizPredecessores(pred.matriz, g->numVertices);
  
  //Visita cada vertice i
  int i;
  for (i = 0; i < g->numVertices; i++) {
    double contador = 0;

    //Visita todos os vertices
    int j;
    for (j = 0; j < g->numVertices; j++){

      //Visita todos os verticos salvando o anterior
        int k;
        for (k = 0; k < g->numVertices; k++){
          if (i != j || i != k || j != k){

            int anterior = pred.matriz[j][k];

            //Percorre a lista de predecessores e soma no contador
            while(anterior != j) {
              if(anterior == i) contador++;
              anterior = pred.matriz[j][anterior];
            }
        }
      }
    }

    //Calcula a centralidade
    valores[i] = contador / ((g->numVertices - 1) * (g->numVertices - 2));

    // printf ("\nContador: %f\n", contador);
  }

  //Libera a memoria dos grafos que foram criados
  liberaGrafo(&dist);
  liberaGrafo(&pred);

}


/* Funcao que calcula a Centralidade Page Rank de todos os vertices. */
void centralidadePageRank(Grafo* g, double* valores, int iteracoes) {
  
  //Inicializa o array 
  int i;
  for (i = 0; i < g->numVertices; i++) {
    valores[i] = 1.0 / g->numVertices;
  }

  double d = 0.85;


  //Loop de acordo com o valor de iteração
  int j;
  for (j = 0; j < iteracoes; j++) {
    double valoresNovos[g->numVertices];


    //Visita Cada Vertice
    int k;
    for (k=0;k<g->numVertices;k++){
      double somatorio = 0;


      // Percorre todos os vértices, verificando quem aponta pra k
      int l;
      for (l=0;l<g->numVertices;l++){
        if (g->matriz[l][k] && l != k){

          int grau = 0;

          //Calcula o grau de saida do vertice l
          int m;
          for (m=0;m<g->numVertices;m++){
            if (g->matriz[l][m] && l != m) grau++;
          }

          if (grau > 0) somatorio += valores[l] / grau;
        } 
      }

    //Calcula a centralidade
     valoresNovos[k] = (1 - d)/g->numVertices + d * somatorio;
    }

    //Atualiza os novos valores
    int n;
    for (n = 0; n < g->numVertices; n++) {
      valores[n] = valoresNovos[n];
    }
  }
}


/* FIM DAS FUNCOES QUE DEVEM SER COMPLETADAS */


/* Funcao que invoca e exibe os valores de cada uma das funcoes que voces
   devem implementar neste EP.
*/
void testaFuncoes(Grafo* g, int n){

  double* valoresReais = (double*)malloc(sizeof(double)*n);

  printf("Centralidade de Grau:\n");
  centralidadeDeGrau(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Proximidade:\n");
  centralidadeDeProximidade(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Intermediacao:\n");
  centralidadeDeIntermediacao(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 0 iteracoes\n");
  centralidadePageRank(g, valoresReais, 0);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 1 iteracao\n");
  centralidadePageRank(g, valoresReais, 1);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 10 iteracoes\n");
  centralidadePageRank(g, valoresReais, 10);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 100 iteracoes\n");
  centralidadePageRank(g, valoresReais, 100);
  exibeArranjoReais(valoresReais, n);

  free(valoresReais);
}


/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  double* valoresReais = (double*)malloc(sizeof(double)*n);
  
  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,1,2);
  insereAresta(&g1,2,3);
  insereAresta(&g1,3,4);
  insereAresta(&g1,4,0);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);


  printf("\n\nSEGUNDO EXEMPLO [auto-lacos]\n");
  insereAresta(&g1,0,0);
  insereAresta(&g1,2,2);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);


  printf("\n\nTERCEIRO EXEMPLO\n");
  Grafo g2;
  inicializaGrafo(&g2, n);
  insereAresta(&g2,0,2);
  insereAresta(&g2,1,2);
  insereAresta(&g2,3,2);
  insereAresta(&g2,4,2);
  insereAresta(&g2,2,0);
  insereAresta(&g2,2,1);
  insereAresta(&g2,2,3);
  insereAresta(&g2,2,4);

  exibeGrafo(&g2);

  testaFuncoes(&g2, n);


  printf("\n\nQUARTO EXEMPLO (grafo aleatorio)\n\n");
  n = 10;
  int arestas = 40;
  
  Grafo* g3 = criaGrafoAleatorio(n,arestas);

  exibeGrafo(g3);
 
  testaFuncoes(g3, n);

  return 0;  
}