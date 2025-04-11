//Q13.1
#include "arv.h"

// Implementação da função para criar um novo nó
Arvore arvore (Arvore e, int x, Arvore d){
    Arvore num = (struct arvore*)malloc(sizeof(struct arvore));
    num-> esq = e;
    num-> item = x;
    num-> dir = d;
    return num;
}

// Implementação da função para percorrer em pré-ordem
void percorre_preordem (Arvore A){
    if(A != NULL){
        std::cout << A->item << std::endl;
        percorre_preordem(A->esq);
        percorre_preordem(A->dir);
    }
}

// Implementação da função para percorrer em in-ordem
void percorre_inordem (Arvore A){
    if(A != NULL){
        percorre_inordem(A->esq);
        std::cout << A->item << std::endl;
        percorre_inordem(A->dir);
    }
}

// Implementação da função para percorrer em pós-ordem
void percorre_posordem (Arvore A){
    if(A != NULL){
        percorre_posordem(A->esq);
        percorre_posordem(A->dir);
        std::cout << A->item << std::endl;
    }
}

// Função para contar o número total de nós na árvore (Q13.2)
int nos(Arvore A){
    if (A == NULL) {
        return 0; // Se a árvore (ou subárvore) é vazia, não há nós.
    } else {
        // O total de nós é 1 (o nó atual) mais o número de nós na subárvore esquerda
        // e o número de nós na subárvore direita.
        return 1 + nos(A->esq) + nos(A->dir);
    }
}

// Função para contar o número total de folhas na árvore (Q13.3)
int folhas(Arvore A){
    if (A == NULL) {
        return 0; // Se a árvore (ou subárvore) é vazia, não há folhas.
    } else if (A->esq == NULL && A->dir == NULL) {
        return 1; // Se o nó atual não tem filhos, é uma folha.
    } else {
        // O número de folhas é a soma do número de folhas na subárvore esquerda
        // e o número de folhas na subárvore direita.
        return folhas(A->esq) + folhas(A->dir);
    }
}

// Função para calcular a altura da árvore binária(Q13.4)
int altura(Arvore A){
    if (A == NULL) {
        return -1; // Altura de uma árvore vazia é -1
    } else {
        int altura_esquerda = altura(A->esq);
        int altura_direita = altura(A->dir);
        return 1 + std::max(altura_esquerda, altura_direita);
    }
}

// Função para verificar se um item (x) existe na árvore binária (A) - (Q13.5)
bool tem(Arvore A, int x){
    if (A == NULL) {
        return false; // Se a árvore (ou subárvore) é vazia, o item não está presente.
    } else if (A->item == x) {
        return true; // Se o item do nó atual é igual a x, encontramos o item.
    } else {
        // Caso contrário, procura recursivamente nas subárvores esquerda e direita.
        return tem(A->esq, x) || tem(A->dir, x);
    }
}

// Função para verificar se a árvore binária A é estritamente binária(13.6)
bool eb(Arvore A){
    if (A == NULL) {
        return true; // Uma árvore vazia é considerada estritamente binária (caso base da recursão).
    } else if (A->esq == NULL && A->dir == NULL) {
        return true; // Se o nó é uma folha (sem filhos), é estritamente binário.
    } else if (A->esq != NULL && A->dir != NULL) {
        // Se o nó tem dois filhos, precisamos verificar se suas subárvores também são estritamente binárias.
        return eb(A->esq) && eb(A->dir);
    } else {
        // Se o nó tem apenas um filho (esquerdo ou direito), a árvore não é estritamente binária.
        return false;
    }
}
 //13.7 em outro arquivo

int main(){
// Construindo uma ÁRVORE ESTRITAMENTE BINÁRIA
    Arvore n8 = arvore(NULL, 8, NULL);
    Arvore n9 = arvore(NULL, 9, NULL);
    Arvore n4 = arvore(n8, 4, n9);

    Arvore n10 = arvore(NULL, 10, NULL);
    Arvore n11 = arvore(NULL, 11, NULL);
    Arvore n5 = arvore(n10, 5, n11);

    Arvore n2 = arvore(n4, 2, n5);

    Arvore n7 = arvore(NULL, 7, NULL);
    Arvore n14 = arvore(NULL, 14, NULL);
    Arvore n3 = arvore(n7, 3, n14);

    Arvore raiz_estrita = arvore(n2, 1, n3);
  /* Estrutura da árvore estrita:
              1
           /    \
          2      3
         / \    / \
       4    5  7   14
      / \  / \
     8  9 10 11
     */

    // Construindo uma árvore NÃO ESTRITAMENTE BINÁRIA
    Arvore nn4 = arvore(NULL, 4, NULL);
    Arvore nn5 = arvore(NULL, 5, NULL);
    Arvore nn2 = arvore(nn4, 2, nn5);
    Arvore nn6 = arvore(NULL, 6, NULL);
    Arvore nn3 = arvore(NULL, 3, nn6);
    Arvore raiz_nao_estrita = arvore(nn2, 1, nn3);
    /* Estrutura da árvore não estrita:
         1
        / \
       2   3
      / \   \
     4  5    6
    */

    std::cout << "Percurso Pré-ordem (Estrita):" << std::endl;
    percorre_preordem(raiz_estrita);
    // Saída esperada (Pré-ordem): 1 2 4 8 9 5 10 11 3 7 14 6 12 13
    std::cout << "\nPercurso In-ordem (Estrita):" << std::endl;
    percorre_inordem(raiz_estrita);
    // Saída esperada (In-ordem): 8 4 9 2 10 5 11 1 7 3 14 12 6 13
    std::cout << "\nPercurso Pós-ordem (Estrita):" << std::endl;
    percorre_posordem(raiz_estrita);
    // Saída esperada (Pós-ordem): 8 9 4 10 11 5 2 7 14 3 12 13 6 1

    int total_nos_estrita = nos(raiz_estrita);
    std::cout << "\nTotal de nós na árvore estrita: " << total_nos_estrita << std::endl;
    // Saída esperada: 13

    int total_folhas_estrita = folhas(raiz_estrita);
    std::cout << "Total de folhas na árvore estrita: " << total_folhas_estrita << std::endl;
    // Saída esperada: 7 (8, 9, 10, 11, 7, 14, 12, 13) - Contei errado na estrutura visual! Corrigindo: 8, 9, 10, 11, 7, 14, 12, 13 são as folhas. São 8 folhas.
    // Correção na contagem visual: As folhas são 8, 9, 10, 11, 7, 14, 12, 13. Total 8.

    int h_estrita = altura(raiz_estrita);
    std::cout << "Altura da árvore estrita: " << h_estrita << std::endl;
    // Saída esperada: 3 (1 -> 2 -> 4 -> 8 ou 9, etc.)

    int item_procurado = 7;
    std::cout << "\nO item " << item_procurado << " está presente na árvore estrita? " << (tem(raiz_estrita, item_procurado) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Sim

    item_procurado = 15;
    std::cout << "O item " << item_procurado << " está presente na árvore estrita? " << (tem(raiz_estrita, item_procurado) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Não

    std::cout << "\nÁrvore Estrita:" << std::endl;
    std::cout << "É estritamente binária? " << (eb(raiz_estrita) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Sim

    std::cout << "\nÁrvore Não Estrita:" << std::endl;
    std::cout << "É estritamente binária? " << (eb(raiz_nao_estrita) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Não

    return 0;
}