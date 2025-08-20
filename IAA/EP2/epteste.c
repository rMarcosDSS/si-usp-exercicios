#include "ep.h"

int *grauDoVertice;  
int *arestaUsada;    
int encontrouSolucao;

char *autor(void) {
    return "Marcos Ruan ; 14760209";
}

int ehSolucao(struct grafo *G) {
    for (int i = 0; i < G->N; i++) {
        if (grauDoVertice[i] != 2) {
            return 0;
        }
    }
    return 1;
}

int ehAceitavel(struct grafo *G, int aresta, int verticeAtual) {
    if (arestaUsada[aresta]) {
        return 0;
    }
    if (G->A[3 * aresta] == verticeAtual || G->A[3 * aresta + 1] == verticeAtual) {
        int outroVertice;
        if (G->A[3 * aresta] == verticeAtual) {
            outroVertice = G->A[3 * aresta + 1];
        } else {
            outroVertice = G->A[3 * aresta];
        }
        if (grauDoVertice[outroVertice] < 2) {
            return 1;
        }
    }
    return 0;
}

int aumentaCaminho(struct grafo *G, int aresta, int verticeAtual) {
    arestaUsada[aresta] = 1;
    grauDoVertice[G->A[3 * aresta]]++;
    grauDoVertice[G->A[3 * aresta + 1]]++;
    if (G->A[3 * aresta] == verticeAtual) {
        return G->A[3 * aresta + 1];
    } else {
        return G->A[3 * aresta];
    }
}

void desfazCaminho(struct grafo *G, int aresta) {
    arestaUsada[aresta] = 0;
    grauDoVertice[G->A[3 * aresta]]--;
    grauDoVertice[G->A[3 * aresta + 1]]--;
}

void tenta(struct grafo *G, int verticeAtual, int profundidade) {
    if (encontrouSolucao) {
        return;
    }
    if (profundidade == G->N) {
        if (ehSolucao(G)) {
            encontrouSolucao = 1;
        }
        return;
    }

    for (int i = 0; i < G->M; i++) {
        if (ehAceitavel(G, i, verticeAtual)) {
            int proximoVertice = aumentaCaminho(G, i, verticeAtual);
            tenta(G, proximoVertice, profundidade + 1);
            if (encontrouSolucao) {
                return;
            }
            desfazCaminho(G, i);
        }
    }
}

int iniciaEexecuta(struct grafo *G, int verticeInicial) {
    grauDoVertice = calloc(G->N, sizeof(int));
    arestaUsada = calloc(G->M, sizeof(int));
    encontrouSolucao = 0;

    tenta(G, verticeInicial, 0);

    for (int i = 0; i < G->M; i++) {
        G->S[i] = arestaUsada[i];
    }

    return encontrouSolucao;
}

void termina() {
	free(grauDoVertice);
    free(arestaUsada);
}
