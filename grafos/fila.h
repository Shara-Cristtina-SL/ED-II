#ifndef FILA_H
#define FILA_H

#include "lista.h"

typedef struct fila {
    Lista *itens;
    int inicio, fim, tamanho, capacidade;
} *Fila;

// Cria uma fila com capacidade para n itens
Fila fila(int n);

// Verifica se a fila F está vazia
int vaziaf(Fila F);

// Enfileira um item na fila F
void enfileira(Lista item, Fila F);

// Desenfileira um item da fila F
Lista desenfileira(Fila F);

// Destroi a fila F liberando a memória
void destroif(Fila *F);

#endif