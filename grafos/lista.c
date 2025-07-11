#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista no(int item, Lista p) {
    Lista novo = malloc(sizeof(struct no));
    novo->item = item;
    novo->prox = p;
    return novo;
}

int pert(int x, Lista p) {
    if (p == NULL) return 0;
    if (p->item == x) return 1;
    return pert(x, p->prox);
}

void exibe_inv(Lista p) {
    if (p == NULL) return;
    exibe_inv(p->prox);
    printf("%d ", p->item);
}

Lista clone(Lista p) {
    if (p == NULL) return NULL;
    return no(p->item, clone(p->prox));
}

void destroi(Lista *p) {
    if (*p == NULL) return;
    destroi(&(*p)->prox);
    free(*p);
    *p = NULL;
}