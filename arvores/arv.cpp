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

// Função para verificar se um item (x) existe na árvore binária (A) - (Q13)
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

    int total_nos = nos(raiz);
    std::cout << "\nTotal de nós na árvore: " << total_nos << std::endl;
    //Saída: 6

    int total_folhas = folhas(raiz);
    std::cout << "Total de folhas na árvore: " << total_folhas << std::endl;
    //Saída: 3

    int h = altura(raiz);
    std::cout << "Altura da árvore: " << h << std::endl;
    //Saída: 2

    int item_procurado = 3;
    if (tem(raiz, item_procurado)) {
        std::cout << "\nO item " << item_procurado << " está presente na árvore." << std::endl;
    } else {
        std::cout << "\nO item " << item_procurado << " não está presente na árvore." << std::endl;
    }

    item_procurado = 7;
    if (tem(raiz, item_procurado)) {
        std::cout << "O item " << item_procurado << " está presente na árvore." << std::endl;
    } else {
        std::cout << "O item " << item_procurado << " não está presente na árvore." << std::endl;
    }

    //Saída: 3 está presente na árvore e 7 não está.
    return 0;
}