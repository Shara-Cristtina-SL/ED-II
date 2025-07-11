#include <stdlib.h>
#include "fila.h"

Fila fila(int n) {
    Fila F = malloc(sizeof(struct fila));
    F->itens = malloc(n * sizeof(Lista));
    F->inicio = -1;
    F->fim = -1;
    F->tamanho = 0;
    F->capacidade = n;
    return F;
}

int vaziaf(Fila F) {
    return F->tamanho == 0;
}

void enfileira(Lista item, Fila F) {
    if (F->tamanho == F->capacidade) return;
    if (F->inicio == -1) F->inicio = 0;
    F->fim = (F->fim + 1) % F->capacidade;
    F->itens[F->fim] = item;
    F->tamanho++;
}

Lista desenfileira(Fila F) {
    if (vaziaf(F)) return NULL;
    Lista item = F->itens[F->inicio];
    F->inicio = (F->inicio + 1) % F->capacidade;
    F->tamanho--;
    if (F->tamanho == 0) {
        F->inicio = -1;
        F->fim = -1;
    }
    return item;
}

void destroif(Fila *F) {
    free((*F)->itens);
    free(*F);
    *F = NULL;
}