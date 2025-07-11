#include <stdio.h>
#include <stdlib.h>  // Adicionado para malloc e free
#include "lista.h"
#include "fila.h"

// Busca em largura (BFS)
void bfs(int v, int w, Lista Adj[]) {
    Fila F = fila(100);
    enfileira(no(v, NULL), F);
    
    while (!vaziaf(F)) {
        Lista c = desenfileira(F);
        if (c->item == w) {
            exibe_inv(c);
            printf("\n");
        } else {
            for (Lista s = Adj[c->item]; s; s = s->prox) {
                if (!pert(s->item, c)) {
                    Lista nova = no(s->item, clone(c));
                    enfileira(nova, F);
                }
            }
        }
        destroi(&c);
    }
    destroif(&F);
}

// Ordenação Topológica
void ts(Lista Adj[], int n) {
    int *pred = malloc(n * sizeof(int));
    
    // Inicializa vetor de predecessores
    for (int v = 0; v < n; v++) pred[v] = 0;
    for (int v = 0; v < n; v++) {
        for (Lista s = Adj[v]; s; s = s->prox) {
            pred[s->item]++;
        }
    }
    
    Fila F = fila(n);
    for (int v = 0; v < n; v++) {
        if (pred[v] == 0) {
            Lista novo = no(v, NULL);
            enfileira(novo, F);
        }
    }
    
    while (!vaziaf(F)) {
        Lista v = desenfileira(F);
        printf("%d ", v->item);
        for (Lista s = Adj[v->item]; s; s = s->prox) {
            pred[s->item]--;
            if (pred[s->item] == 0) {
                Lista novo = no(s->item, NULL);
                enfileira(novo, F);
            }
        }
        destroi(&v);
    }
    free(pred);
    destroif(&F);
}

int main() {
    // Exercício 15.1
    Lista Adj[6];  // Definindo explicitamente o tamanho
    
    // Construção das listas de adjacência passo a passo
    Adj[0] = no(1, no(2, no(3, NULL)));    // 0 → 1, 2, 3
    Adj[1] = no(0, no(3, NULL));            // 1 → 0, 3
    Adj[2] = no(0, no(3, no(4, NULL)));     // 2 → 0, 3, 4
    // Para o vértice 3, vamos construir em etapas para evitar muitos parênteses
    Lista temp = no(5, NULL);
    temp = no(2, temp);
    temp = no(1, temp);
    temp = no(0, temp);
    Adj[3] = temp;                          // 3 → 0, 1, 2, 5
    Adj[4] = no(2, no(5, NULL));            // 4 → 2, 5
    Adj[5] = no(3, no(4, NULL));            // 5 → 3, 4

    /* representação do grafo para referência
0 → 1, 2, 3
1 → 0, 3
2 → 0, 3, 4
3 → 0, 1, 2, 5
4 → 2, 5
5 → 3, 4
    */
    
    printf("Busca em largura de 0 para 5:\n");
    bfs(0, 5, Adj);
    
    printf("\nOrdenação topológica:\n");
    ts(Adj, 6);
    
    // Liberar memória das listas de adjacência
    for (int i = 0; i < 6; i++) {
        destroi(&Adj[i]);
    }
    
    return 0;
}
// Caminhos esperados
/*
0 → 3 → 5

0 → 1 → 3 → 5

0 → 2 → 3 → 5

0 → 2 → 4 → 5

0 → 3 → 2 → 4 → 5

0 → 1 → 3 → 2 → 4 → 5
*/
