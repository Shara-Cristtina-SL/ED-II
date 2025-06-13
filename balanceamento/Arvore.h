#ifndef ARVORE_H
#define ARVORE_H

#include <iostream> // necessário para std::cout

template <typename T>
struct ArvoreNo {
    T valor;
    ArvoreNo* esquerdo;
    ArvoreNo* direito;

    ArvoreNo(T val) : valor(val), esquerdo(nullptr), direito(nullptr) {}
};

template <typename T>
class ArvoreBinaria {
private:
    ArvoreNo<T>* raiz;

    void rotacaoDireita(ArvoreNo<T>*& p);
    void rotacaoEsquerda(ArvoreNo<T>*& p);
    void criarEspinhaDorsal(); // Fase 1 do DSW
    void balancearEspinha();   // Fase 2 do DSW
    int contarNos();
    void inserirRec(ArvoreNo<T>*& no, T val);
    void emOrdem(ArvoreNo<T>* no); // auxiliar para emOrdem
    void imprimirEstrutura(ArvoreNo<T>* no, int nivel); // auxiliar para impressão
    

public:
    ArvoreBinaria();
    void inserir(T val);
    void balancearDSW();
    void emOrdem();
    void imprimirEstrutura();  // função pública
};

#endif
