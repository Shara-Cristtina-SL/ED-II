#ifndef LISTA_H
#define LISTA_H

typedef struct no {
    int item;
    struct no *prox;
} *Lista;

// Cria um novo nó com o item x e o próximo nó p
Lista no(int item, Lista p);

// Verifica se o item x pertence à lista p
int pert(int x, Lista p);

// Exibe a lista p invertida
void exibe_inv(Lista p);

// Cria uma cópia da lista p
Lista clone(Lista p);

// Destroi a lista p liberando a memória
void destroi(Lista *p);

#endif