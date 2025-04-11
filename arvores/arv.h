#ifndef ARV_H
#define ARV_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Definição da estrutura do nó da árvore
typedef struct arvore {
    struct arvore *esq;
    int item;
    struct arvore *dir;
} *Arvore;

// Função para criar um novo nó da árvore
Arvore arvore(Arvore esq, int item, Arvore dir);

// Função para percorrer a árvore em pré-ordem (raiz, esquerda, direita)
void percorre_preordem(Arvore A);

// Função para percorrer a árvore em in-ordem (esquerda, raiz, direita)
void percorre_inordem(Arvore A);

// Função para percorrer a árvore em pós-ordem (esquerda, direita, raiz)
void percorre_posordem(Arvore A);

// Função para contar o número total de nós na árvore (Q13.2)
int nos(Arvore A);

// Função para contar o número total de folhas na árvore(Q14.3)
int folhas(Arvore A);

// Função para calcular a altura da árvore binária(13.4)
int altura(Arvore A);

// Função para verificar se um item (x) existe na árvore binária (A) - (Q13.5)
bool tem(Arvore A, int x);

// Função para verificar se a árvore binária A é estritamente binária (Q13.6)
bool eb(Arvore A);

#endif // ARV_H