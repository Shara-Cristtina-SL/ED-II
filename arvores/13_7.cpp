#include "arv.h"

// Implementação da função para criar um novo nó
Arvore arvore (Arvore e, int x, Arvore d){
    Arvore num = (struct arvore*)malloc(sizeof(struct arvore));
    num-> esq = e;
    num-> item = x;
    num-> dir = d;
    return num;
}

// Função para verificar se duas árvores binárias A e B são iguais
bool igual(Arvore A, Arvore B){
    if (A == NULL && B == NULL) {
        return true; // Ambas são vazias, portanto iguais.
    } else if (A != NULL && B != NULL) {
        // Ambas não são vazias, verificar se a raiz tem o mesmo item
        // e se as subárvores esquerda e direita são iguais recursivamente.
        return (A->item == B->item) &&
               igual(A->esq, B->esq) &&
               igual(A->dir, B->dir);
    } else {
        // Uma é NULL e a outra não, portanto não são iguais.
        return false;
    }
}

int main(){
    // Construindo árvores de exemplo para comparação
    Arvore n8a = arvore(NULL, 8, NULL);
    Arvore n9a = arvore(NULL, 9, NULL);
    Arvore n4a = arvore(n8a, 4, n9a);
    Arvore n10a = arvore(NULL, 10, NULL);
    Arvore n11a = arvore(NULL, 11, NULL);
    Arvore n5a = arvore(n10a, 5, n11a);
    Arvore raiz_a = arvore(n4a, 2, n5a);
    // Estrutura de A:
    //        2
    //       / \
    //      4   5
    //     / \ / \
    //    8  9 10 11

    Arvore n8b = arvore(NULL, 8, NULL);
    Arvore n9b = arvore(NULL, 9, NULL);
    Arvore n4b = arvore(n8b, 4, n9b);
    Arvore n10b = arvore(NULL, 10, NULL);
    Arvore n11b = arvore(NULL, 11, NULL);
    Arvore n5b = arvore(n10b, 5, n11b);
    Arvore raiz_b = arvore(n4b, 2, n5b);
    // Estrutura de B (igual a A):
    //        2
    //       / \
    //      4   5
    //     / \ / \
    //    8  9 10 11

    Arvore n8c = arvore(NULL, 8, NULL);
    Arvore n9c = arvore(NULL, 9, NULL);
    Arvore n4c = arvore(n8c, 4, n9c);
    Arvore n10c = arvore(NULL, 11, NULL); // Intencionalmente diferente
    Arvore n11c = arvore(NULL, 10, NULL); // Intencionalmente diferente
    Arvore n5c = arvore(n10c, 5, n11c);
    Arvore raiz_c = arvore(n4c, 2, n5c);
    // Estrutura de C (forma igual a A, itens diferentes em alguns nós):
    //        2
    //       / \
    //      4   5
    //     / \ / \
    //    8  9 11 10

    Arvore n8d = arvore(NULL, 8, NULL);
    Arvore n9d = arvore(NULL, 9, NULL);
    Arvore n4d = arvore(n8d, 4, n9d);
    Arvore raiz_d = arvore(n4d, 2, NULL); // Forma diferente de A e B
    // Estrutura de D (forma diferente de A e B):
    //        2
    //       /
    //      4
    //     / \
    //    8   9

    std::cout << "A é igual a B? " << (igual(raiz_a, raiz_b) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Sim

    std::cout << "A é igual a C? " << (igual(raiz_a, raiz_c) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Não

    std::cout << "A é igual a D? " << (igual(raiz_a, raiz_d) ? "Sim" : "Não") << std::endl;
    // Saída esperada: Não

    return 0;
}