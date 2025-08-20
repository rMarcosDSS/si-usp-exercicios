/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2024                           **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   <Marcos Ruan da Silva Santos>               <14760209>   <04> **/
/**                                                                 **/
/*********************************************************************/

/*
A Maratona de Programacao que voce gerenciara tem um numero fixo de problemas definido na constante PROBLEMAS. Os problemas da maratona serao numerados de 0 (zero) ate PROBLEMAS-1. Havera uma lista ligada ordenada pela classificacao dos times, como discutido ao longo do enunciado.
*/

#include <stdlib.h>
#include <stdio.h>

#define false 0
#define true 1

#define PROBLEMAS 10

typedef int bool;

/*
A estrutura  TIME foi projetada para armazenar as informacoes de cada time participante da Maratona de Programacao. Ela e composta por quatro campos:
   id â€“ identificador numerico do time, comecando por 1 (um);
   resolvidos â€“ arranjo booleano com tamanho igual ao numero de problemas da maratona, que contera o valor true}, caso o tinha tenha resolvido (corretamente) o problema e false}, caso contrario;
   tentativas â€“ arranjo de inteiros com tamanho igual ao numero de problemas da maratona, que contera o numero de tentativas (submissoes) do respectivo problema que o time fez ate conseguir resolver o problema; e
   minutos â€“ arranjo de inteiros com tamanho igual ao numero de problemas da maratona, que contera o numero de minutos passados desde o inicio da maratona ate o momento em que o time submeteu a solucao correta do respectivo problema. Para os problemas em que o time nao submeteu uma solucao correta, o valor 0 (zero) deve ser armazenado na respectiva posicao do arranjo.
*/
typedef struct
{
    int id;
    bool resolvidos[PROBLEMAS];
    int tentativas[PROBLEMAS];
    int minutos[PROBLEMAS];
} TIME;

/*
A estrutura  ELEMENTO foi projetada para armazenar cada elemento da lista duplamente ligada, ordenada, com no cabeca e nao circular que voce gerenciara. Esta estrutura e composta por tres campos:
   time â€“ ponteiro (ou referencia) para o time participante da maratona;
   ant â€“ ponteiro (ou referencia) para o elemento anterior da lista ligada; e
   prox â€“ ponteiro (ou referencia) para o elemento seguinte da lista ligada.
*/
typedef struct aux
{
    TIME *time;
    struct aux *ant;
    struct aux *prox;
} ELEMENTO, *PONT;

/*
A estrutura  MARATONA foi projetada para representar a Maratona de Programacao. Esta estrutura e composta por dois campos:
   cabeca â€“ ponteiro (ou referencia) para o no cabeca da lista duplamente ligada;
   numTimes â€“ campo do tipo inteiro contendo o numero de times que estao participando da maratona.
*/
typedef struct
{
    PONT cabeca;
    int numTimes;
} MARATONA;

/*
Funcao usada em testes da correcao automatica
   NAO APAGAR OU MODIFICAR
*/
void print123()
{
}

/*
Funcao que recebe o endereco de um TIME e, se esse endereco for igual a NULL, retorna -1. Caso contrario, calcula e retorna a penalidade total (em minutos) recebida pelo time. A penalidade total de um time e dada pela soma dos minutos que o time levou para resolver cada problema (estes valores sao armazenados no arranjo minutos), considerando apenas os problemas efetivamente resolvidos, mais 20 minutos de penalizacao para cada submissao incorreta, considerando, novamente, apenas os problemas que o time conseguiu resolver. Por exemplo, se o time conseguiu resolver o problema numero 3 apenas na quinta tentativa e a tentativa correta ocorreu no minuto 110, havera uma penalizacao de 80 minutos referentes as tentativas incorretas, mais 110 minutos referentes ao tempo que o time levou para resolver esse problema. Assim, havera uma penalidade de 190 minutos referente ao problema de numero 3 (a penalidade total do time corresponde a soma das penalidades do time para todos os problemas da maratona). Destaca-se que problemas nao resolvidos corretamente tem penalidade igual a zero.
*/
int calcularPenalidade(TIME *time)
{
    // Verifica se o ponteiro para o time é nulo

    if (time == NULL) return -1;

    int penalidadeTotal = 0;
    for(int p = 0; p < PROBLEMAS; p++){
        if(time->resolvidos[p]){
            // Penalidade pelo tempo do problema resolvido
            // Penalidade por tentativas incorretas (cada tentativa incorreta adiciona 20 minutos)
            // A tentativa correta não adiciona penalidade, então subtrai-se 1
            
            penalidadeTotal += time->minutos[p];
            penalidadeTotal += (time->tentativas[p] - 1) * 20;
        }
    }
    return penalidadeTotal;
}

/*
Funcao que recebe o endereco de um TIME e, se esse endereco for igual a NULL, retorna -1. Caso contrario, calcula e retorna o numero total de problemas resolvidos pelo respectivo time (o arranjo resolvidos armazena, para cada problema, se ele foi ou nao resolvido).
*/
int calcularProblemasResolvidosDoTime(TIME *time)
{
    // Verifica se o ponteiro para o time é nulo

    if (time == NULL) return -1;


    int contador = 0;

    for(int p = 0; p < PROBLEMAS; p++){
        // Se o problema foi resolvido, incrementa o contador
        if(time->resolvidos[p]){
            contador++;
        }
    }
    return contador;
}

/*
Funcao que recebe o endereco de uma MARATONA e, se esse endereco for igual a NULL, retorna -1. Caso contrario, calcula e retorna o numero total de problemas que nenhum time ainda conseguiu resolver. Isto e, se a maratona tem 10 problemas e ha tres problemas que nenhum time resolveu, devera retornar 3.
*/
int calcularProblemasNaoResolvidos(MARATONA *mar)
{
    // Verifica se o ponteiro para a maratona é nulo
    if (mar == NULL) return -1;

    int naoResolvidos = 0;
    for(int p = 0; p < PROBLEMAS; p++){
        bool resolvidoPorAlgumTime = false;
        PONT atual = mar->cabeca->prox;

        // Verifica todos os times na lista
        while(atual){

            // Se algum time resolveu o problema, atualiza a flag
            if(atual->time->resolvidos[p]){
                resolvidoPorAlgumTime = true;
                break;
            }
            atual = atual->prox;
        }

        // Se o problema não foi resolvido por nenhum time, incrementa o contador
        if(!resolvidoPorAlgumTime){
            naoResolvidos++;
        }
    }
    return naoResolvidos;
}

/*
Funcao que recebe cinco parametros: mar - endereco de uma MARATONA, id â€“ identificador de um time, problema â€“ identificador de um problema, tempo â€“ tempo, em minutos, da submissao, acerto â€“ parametro booleano que indica se o problema foi resolvido corretamente ou nao. Esta funcao devera retornar false caso algum parametro seja invalido, isto e MAR igual a NULL, ou id fora do intervalo que vai de 1 ate o numero de times da respectiva maratona, ou problema fora do intervalo valido dos problemas (que vai de 0 a PROBLEMAS â€“ 1). A funcao tambem devera retornar false caso o respectivo time ja tenha resolvido corretamente o problema cujo numero e dado pelo parametro problema. Isto e, submissoes de problemas ja resolvidos pelo time devem ser ignoradas. Caso contrario, a funcao deve atualizar as seguintes informacoes do time:
(i) aumentar em uma unidade o numero de tentativas de resolucao pelo time para o respectivo problema;
(ii) caso o time tenha acertado a solucao (parametro acerto = true), (ii.a) atualizar para verdadeiro o respectivo valor do arranjo resolvidos};
(ii.b) atualizar o valor do arranjo minutos}, atualizando o valor correspondente ao problema atual com o tempo passado como parametro;
(ii.c) reposicionar, se necessario, o ELEMENTO correspondente ao time atual na lista duplamente ligada, ordenada, com no cabeca e nao circular.
 A lista e ordenada pela classificacao do time na maratona, a qual segue estas regras: a lista e ordenada de forma decrescente do time que resolveu mais problemas para o time que resolveu menos problemas e tendo como criterio de desempate as penalidades recebidas pelos times (dados dois times que resolveram a mesma quantidade de problemas, ficara na frente da lista [mais para o inicio da lista] aquele com menor penalidade).
Se dois times empatarem nestes dois criterios, deve ficar a frente da lista aquele que ja estava a frente antes da atualizacao (isto e, se o time A ja tinha resolvido dois problemas e tinha penalidade 200 e a funcao tratarSubmissao foi chamada para o time B que, agora, resolveu seu segundo problema e ficou com penalidade 200, o time A deve permanecer a frente na classificacao em relacao ao time B [como ja estava antes desta submissao]). Durante a atualizacao da posicao dos elementos da lista ligada preste bastante atencao para atualizar todos os ponteiros necessarios e nao esqueca que a lista e duplamente ligada e possui no cabeca.
*/
bool tratarSubmissao(MARATONA *mar, int id, int problema, int tempo, bool acerto)
{

    // Verifica se o ponteiro para a maratona é nulo
    // Verifica se o id do time está fora do intervalo válido
    // Verifica se o identificador do problema está fora do intervalo válido

    if (mar == NULL) return false;
    if (id < 1 || id > mar->numTimes) return false;
    if (problema < 0 || problema >= PROBLEMAS) return false;

    // Encontrar o ELEMENTO correspondente ao time com o id dado

    PONT elementoAtual = mar->cabeca->prox;
    while(elementoAtual != NULL && elementoAtual->time->id != id){
        elementoAtual = elementoAtual->prox;
    }


    // Time com o id especificado não encontrado
    if(elementoAtual == NULL){
        return false;
    }

    TIME* time = elementoAtual->time;

    // Verificar se o problema já foi resolvido
    if(time->resolvidos[problema]){
        return false;
    }

    // Atualizar tentativas
    time->tentativas[problema]++;

    if(acerto){
        // Atualizar para resolvido
        // Atualizar o tempo do problema


        time->resolvidos[problema] = true;
        time->minutos[problema] = tempo;

        // Reposicionar o ELEMENTO na lista de acordo com a nova classificação
        // Primeiro, remover o elemento atual da posição atual


        if(elementoAtual->ant){
            elementoAtual->ant->prox = elementoAtual->prox;
        }
        if(elementoAtual->prox){
            elementoAtual->prox->ant = elementoAtual->ant;
        }

        // Encontrar a nova posição
        PONT posicao = mar->cabeca;
        PONT temp = mar->cabeca->prox;
        while(temp != NULL){

            // Calcula o número de problemas resolvidos e penalidade para o time atual
          
            int problemasAtual = calcularProblemasResolvidosDoTime(time);
            int penalidadeAtual = calcularPenalidade(time);
            int problemasTemp = calcularProblemasResolvidosDoTime(temp->time);
            int penalidadeTemp = calcularPenalidade(temp->time);

            if(problemasAtual > problemasTemp){
                break;
            }
            else if(problemasAtual == problemasTemp){
                if(penalidadeAtual < penalidadeTemp){
                    break;
                }
            }


            // Se não entrou no if, continua procurando
            posicao = temp;
            temp = temp->prox;
        }

        // Inserir antes de 'posicao' se 'posicao' foi encontrado

        if(posicao == mar->cabeca){
            elementoAtual->prox = mar->cabeca->prox;
            elementoAtual->ant = mar->cabeca;
            if(mar->cabeca->prox){
                mar->cabeca->prox->ant = elementoAtual;
            }
            mar->cabeca->prox = elementoAtual;
        }
        else{
            // Inserir após 'posicao'

            elementoAtual->prox = posicao->prox;
            elementoAtual->ant = posicao;
            if(posicao->prox){
                posicao->prox->ant = elementoAtual;
            }
            posicao->prox = elementoAtual;
        }
    }

    return true;
}

/*
Funcao que recebe como parametro o endereco de uma MARATONA e o numero de times que participarao da competicao e realiza a inicializacao da maratona. Isto e, cria a lista duplamente ligada com todos os times e o no cabeca, preenche o valor de todos os campos necessarios (valores dos times, elementos e da maratona propriamente dita) e retorna true. Porem, se os parametros recebidos forem invalidos, retorna false}, sem realizar a inicializacao. Destaca-se que durante a inicializacao, a lista ordenada dos times e criada e, neste momento, o time com id igual a 1 esta em primeiro lugar, com id igual a 2 em segundo e assim por diante (se a competicao acabar sem nenhuma resolucao dos problemas, esta sera a classificacao dos times).
*/
bool inicializarMaratona(MARATONA *mar, int numTimes)
{
    if (!mar || numTimes < 1)
        return false;
    int x, p;
    ELEMENTO *novoElem;
    TIME *novoTime;
    mar->numTimes = numTimes;
    mar->cabeca = (ELEMENTO *)malloc(sizeof(ELEMENTO));
    mar->cabeca->ant = NULL;
    mar->cabeca->prox = NULL;
    mar->cabeca->time = NULL;
    for (x = numTimes; x > 0; x--)
    {
        novoElem = (ELEMENTO *)malloc(sizeof(ELEMENTO));
        novoTime = (TIME *)malloc(sizeof(TIME));
        novoTime->id = x;
        for (p = 0; p < PROBLEMAS; p++)
        {
            novoTime->resolvidos[p] = false;
            novoTime->tentativas[p] = 0;
            novoTime->minutos[p] = 0;
        }
        novoElem->time = novoTime;
        novoElem->prox = mar->cabeca->prox;
        novoElem->ant = mar->cabeca;
        if (mar->cabeca->prox)
            mar->cabeca->prox->ant = novoElem;
        mar->cabeca->prox = novoElem;
    }
    return true;
}

/*
Funcao que recebe o endereco de uma MARATONA e exibe informacoes basicas dos times de acordo com a ordem de classificacao (que e a ordem em que os times estao na lista ligada).
*/
void mostrarClassificacao(MARATONA *mar)
{
    if (mar)
    {
        printf("\nClassificacao Atual:\n");
        printf("Time\tProb.\tPenalidadade\n");
        PONT atual = mar->cabeca->prox;
        int solucoes, penalidade;
        while (atual)
        {
            solucoes = calcularProblemasResolvidosDoTime(atual->time);
            penalidade = calcularPenalidade(atual->time);
            printf("%4i\t%4i\t%5i\n", atual->time->id, solucoes, penalidade);
            atual = atual->prox;
        }
    }
}

/*
Funcao que recebe o endereco de um TIME e exibe informacoes basicas do time (identificador, numero de problemas resolvidos e penalidade total).
*/
void exibirTime(TIME *t)
{
    if (t)
    {
        printf("Time: %3i; solucoes: %2i; penalidade: %5i\n", t->id, calcularProblemasResolvidosDoTime(t), calcularPenalidade(t));
        int p;
        for (p = 0; p < PROBLEMAS; p++)
        {
            printf("\t[%2i: %2i %3i %3i]\n", p, t->resolvidos[p], t->tentativas[p], t->minutos[p]);
        }
        printf("\n");
    }
}

/*
Funcao que recebe o endereco de uma MARATONA e exibe as informacoes de todos os times (utilizando a funcao exibirTime)
*/
void exibirTodosTimes(MARATONA *mar)
{
    if (mar)
    {
        printf("##### EXIBINDO TODOS OS TIMES #####\n");
        PONT atual = mar->cabeca->prox;
        while (atual)
        {
            exibirTime(atual->time);
            atual = atual->prox;
        }
    }
}

/*
Funcao main que realiza ALGUNS testes nas funcoes implementadas
seu EP sera avaliado utilizando um conjunto distinto de testes.
*/
int main()
{
    MARATONA m1;
    inicializarMaratona(&m1, 5);
    printf("Numero de problemas ainda nao resolvidos: %i\n", calcularProblemasNaoResolvidos(&m1));
    mostrarClassificacao(&m1);
    exibirTime(m1.cabeca->prox->time);
    if (!tratarSubmissao(&m1, 2, 3, 25, false))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 2, 3, 35, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 4, 2, 40, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 5, 4, 40, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 5, 2, 55, false))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 5, 2, 58, false))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 5, 2, 60, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 1, 7, 65, false))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 3, 8, 70, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 1, 8, 75, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 5, 7, 90, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (tratarSubmissao(&m1, 5, 7, 93, true))
        printf("A funcao retornou true. [PROBLEMA]\n");

    if (!tratarSubmissao(&m1, 1, 1, 95, true))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    if (!tratarSubmissao(&m1, 5, 1, 99, false))
        printf("A funcao retornou false. [PROBLEMA]\n");
    mostrarClassificacao(&m1);
    exibirTodosTimes(&m1);
    printf("Numero de problemas ainda nao resolvidos: %i\n", calcularProblemasNaoResolvidos(&m1));
    printf("\nCampeao:\n");
    exibirTime(m1.cabeca->prox->time);
    return 0;
}
