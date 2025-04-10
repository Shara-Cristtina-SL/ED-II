#include "arv.h"

using namespace std;

Arvore arvore (Arvore e, int x, Arvore d){
    Arvore num = (struct arvore*)malloc(sizeof(struct arvore));
    num-> esq = e;
    num-> item = x;
    num-> dir = d;
    return num;
}

// raiz, esquerda, direita (Pré-ordem)
void percorre_preordem (Arvore A){
    if(A != NULL){
        cout << A->item << endl;
        percorre_preordem
    (A->esq);
        percorre_preordem
    (A->dir);
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

int main(){
    // Construindo uma árvore de exemplo
    Arvore n4 = arvore(NULL, 4, NULL);
    Arvore n5 = arvore(NULL, 5, NULL);
    Arvore n2 = arvore(n4, 2, n5);
    Arvore n6 = arvore(NULL, 6, NULL);
    Arvore n3 = arvore(NULL, 3, n6);
    Arvore raiz = arvore(n2, 1, n3);

    std::cout << "Percurso Pré-ordem:" << std::endl;
    percorre_preordem(raiz);
    std::cout << "\nPercurso In-ordem:" << std::endl;
    percorre_inordem(raiz);
    std::cout << "\nPercurso Pós-ordem:" << std::endl;
    percorre_posordem(raiz);

    return 0;
}