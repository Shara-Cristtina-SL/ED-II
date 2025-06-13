#include <iostream>
#include <cmath>
#include "Arvore.h"

template <typename T>
ArvoreBinaria<T>::ArvoreBinaria() : raiz(nullptr) {}

template <typename T>
void ArvoreBinaria<T>::inserir(T val) {
    inserirRec(raiz, val);
}

template <typename T>
void ArvoreBinaria<T>::inserirRec(ArvoreNo<T>*& no, T val) {
    if (!no) {
        no = new ArvoreNo<T>(val);
    } else if (val < no->valor) {
        inserirRec(no->esquerdo, val);
    } else {
        inserirRec(no->direito, val);
    }
}

template <typename T>
void ArvoreBinaria<T>::rotacaoDireita(ArvoreNo<T>*& p) {
    ArvoreNo<T>* q = p->esquerdo;
    p->esquerdo = q->direito;
    q->direito = p;
    p = q;
}

template <typename T>
void ArvoreBinaria<T>::rotacaoEsquerda(ArvoreNo<T>*& p) {
    ArvoreNo<T>* q = p->direito;
    p->direito = q->esquerdo;
    q->esquerdo = p;
    p = q;
}

template <typename T>
void ArvoreBinaria<T>::criarEspinhaDorsal() {
    ArvoreNo<T>* tmp = raiz;
    ArvoreNo<T>* pai = nullptr;

    while (tmp != nullptr) {
        if (tmp->esquerdo != nullptr) {
            ArvoreNo<T>* filho = tmp->esquerdo;
            tmp->esquerdo = filho->direito;
            filho->direito = tmp;
            tmp = filho;
            if (pai == nullptr)
                raiz = tmp;
            else
                pai->direito = tmp;
        } else {
            pai = tmp;
            tmp = tmp->direito;
        }
    }
}

template <typename T>
int ArvoreBinaria<T>::contarNos() {
    int count = 0;
    ArvoreNo<T>* tmp = raiz;
    while (tmp != nullptr) {
        count++;
        tmp = tmp->direito;
    }
    return count;
}

template <typename T>
void ArvoreBinaria<T>::balancearEspinha() {
    int n = contarNos();
    int m = pow(2, floor(log2(n + 1))) - 1;

    ArvoreNo<T>* tmp = raiz;
    ArvoreNo<T>* pai = nullptr;

    for (int i = 0; i < n - m; ++i) {
        ArvoreNo<T>* filho = tmp->direito;
        tmp->direito = filho->esquerdo;
        filho->esquerdo = tmp;
        tmp = filho;
        if (pai == nullptr)
            raiz = tmp;
        else
            pai->direito = tmp;
        pai = tmp;
        tmp = tmp->direito;
    }

    while (m > 1) {
        m /= 2;
        pai = nullptr;
        tmp = raiz;
        for (int i = 0; i < m; ++i) {
            ArvoreNo<T>* filho = tmp->direito;
            tmp->direito = filho->esquerdo;
            filho->esquerdo = tmp;
            tmp = filho;
            if (pai == nullptr)
                raiz = tmp;
            else
                pai->direito = tmp;
            pai = tmp;
            tmp = tmp->direito;
        }
    }
}

template <typename T>
void ArvoreBinaria<T>::balancearDSW() {
    criarEspinhaDorsal();
    balancearEspinha();
}

template <typename T>
void ArvoreBinaria<T>::emOrdem() {
    emOrdem(raiz);
    std::cout << std::endl;
}

template <typename T>
void ArvoreBinaria<T>::emOrdem(ArvoreNo<T>* no) {
    if (!no) return;
    emOrdem(no->esquerdo);
    std::cout << no->valor << " ";
    emOrdem(no->direito);
}


template <typename T>
void ArvoreBinaria<T>::imprimirEstrutura(ArvoreNo<T>* no, int nivel) {
    if (no == nullptr)
        return;

    imprimirEstrutura(no->direito, nivel + 1);

    for (int i = 0; i < nivel; ++i)
        std::cout << "    ";
    std::cout << no->valor << std::endl;

    imprimirEstrutura(no->esquerdo, nivel + 1);
}

// Instanciando os templates explicitamente
template class ArvoreBinaria<int>;

int main() {
    ArvoreBinaria<int> arv;

    int valores[] = {8, 25, 20, 14, 32, 30, 28, 31, 40};
    for (int val : valores) {
        arv.inserir(val);
    }

    std::cout << "Antes do balanceamento:\n";
    arv.emOrdem();

    arv.balancearDSW();

    std::cout << "Depois do balanceamento:\n";
    arv.emOrdem();

    return 0;
}
