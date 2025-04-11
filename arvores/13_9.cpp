//Q13.1
#include "arv_expr.h"
#include <iostream>
#include <string>
#include <cctype> // Para isdigit
#include <stdexcept> // Para std::invalid_argument
#include <algorithm> // Para std::max

// Implementação das funções para árvore de inteiros (se você ainda as usa)
ArvoreInt arvoreInt(ArvoreInt e, int x, ArvoreInt d){
    ArvoreInt num = (struct arvore_int*)malloc(sizeof(struct arvore_int));
    num-> esq = e;
    num-> item = x;
    num-> dir = d;
    return num;
}

void percorre_preordem_int(ArvoreInt A){
    if(A != NULL){
        std::cout << A->item << std::endl;
        percorre_preordem_int(A->esq);
        percorre_preordem_int(A->dir);
    }
}

void percorre_inordem_int(ArvoreInt A){
    if(A != NULL){
        percorre_inordem_int(A->esq);
        std::cout << A->item << std::endl;
        percorre_inordem_int(A->dir);
    }
}

void percorre_posordem_int(ArvoreInt A){
    if(A != NULL){
        percorre_posordem_int(A->esq);
        percorre_posordem_int(A->dir);
        std::cout << A->item << std::endl;
    }
}

int nosInt(ArvoreInt A){
    if (A == NULL) {
        return 0;
    } else {
        return 1 + nosInt(A->esq) + nosInt(A->dir);
    }
}

int folhasInt(ArvoreInt A){
    if (A == NULL) {
        return 0;
    } else if (A->esq == NULL && A->dir == NULL) {
        return 1;
    } else {
        return folhasInt(A->esq) + folhasInt(A->dir);
    }
}

int alturaInt(ArvoreInt A){
    if (A == NULL) {
        return -1;
    } else {
        int altura_esquerda = alturaInt(A->esq);
        int altura_direita = alturaInt(A->dir);
        return 1 + std::max(altura_esquerda, altura_direita);
    }
}

bool temInt(ArvoreInt A, int x){
    if (A == NULL) {
        return false;
    } else if (A->item == x) {
        return true;
    } else {
        return temInt(A->esq, x) || temInt(A->dir, x);
    }
}

bool ebInt(ArvoreInt A){
    if (A == NULL) {
        return true;
    } else if (A->esq == NULL && A->dir == NULL) {
        return true;
    } else if (A->esq != NULL && A->dir != NULL) {
        return ebInt(A->esq) && ebInt(A->dir);
    } else {
        return false;
    }
}

bool igualInt(ArvoreInt A, ArvoreInt B){
    if (A == NULL && B == NULL) {
        return true;
    } else if (A != NULL && B != NULL) {
        return (A->item == B->item) &&
               igualInt(A->esq, B->esq) &&
               igualInt(A->dir, B->dir);
    } else {
        return false;
    }
}

// Implementação das funções específicas para árvore de expressão aritmética
ArvoreExpr arvoreExpr(ArvoreExpr e, std::string item, ArvoreExpr d){
    ArvoreExpr num = (struct arvore_expr*)malloc(sizeof(struct arvore_expr));
    num-> esq = e;
    num-> item = item;
    num-> dir = d;
    return num;
}

void percorre_preordem_expr(ArvoreExpr A){
    if(A != NULL){
        std::cout << A->item << std::endl;
        percorre_preordem_expr(A->esq);
        percorre_preordem_expr(A->dir);
    }
}

void percorre_inordem_expr(ArvoreExpr A){
    if(A != NULL){
        percorre_inordem_expr(A->esq);
        std::cout << A->item << std::endl;
        percorre_inordem_expr(A->dir);
    }
}

void percorre_posordem_expr(ArvoreExpr A){
    if(A != NULL){
        percorre_posordem_expr(A->esq);
        percorre_posordem_expr(A->dir);
        std::cout << A->item << std::endl;
    }
}

int nosExpr(ArvoreExpr A){
    if (A == NULL) {
        return 0;
    } else {
        return 1 + nosExpr(A->esq) + nosExpr(A->dir);
    }
}

int folhasExpr(ArvoreExpr A){
    if (A == NULL) {
        return 0;
    } else if (A->esq == NULL && A->dir == NULL) {
        return 1;
    } else {
        return folhasExpr(A->esq) + folhasExpr(A->dir);
    }
}

int alturaExpr(ArvoreExpr A){
    if (A == NULL) {
        return -1;
    } else {
        int altura_esquerda = alturaExpr(A->esq);
        int altura_direita = alturaExpr(A->dir);
        return 1 + std::max(altura_esquerda, altura_direita);
    }
}

bool temExpr(ArvoreExpr A, std::string x){
    if (A == NULL) {
        return false;
    } else if (A->item == x) {
        return true;
    } else {
        return temExpr(A->esq, x) || temExpr(A->dir, x);
    }
}

bool ebExpr(ArvoreExpr A){
    if (A == NULL) {
        return true;
    } else if (A->esq == NULL && A->dir == NULL) {
        return true;
    } else if (A->esq != NULL && A->dir != NULL) {
        return ebExpr(A->esq) && ebExpr(A->dir);
    } else {
        return false;
    }
}

bool igualExpr(ArvoreExpr A, ArvoreExpr B){
    if (A == NULL && B == NULL) {
        return true;
    } else if (A != NULL && B != NULL) {
        return (A->item == B->item) &&
               igualExpr(A->esq, B->esq) &&
               igualExpr(A->dir, B->dir);
    } else {
        return false;
    }
}

// Função auxiliar para verificar se uma string representa um número inteiro
bool ehNumero(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

int valorExpr(ArvoreExpr A) {
    if (A == NULL) {
        throw std::invalid_argument("Árvore de expressão inválida (NULL).");
    }

    if (ehNumero(A->item)) {
        return std::stoi(A->item);
    } else {
        int esq_valor = valorExpr(A->esq);
        int dir_valor = valorExpr(A->dir);
        std::string operador = A->item;

        if (operador == "+") {
            return esq_valor + dir_valor;
        } else if (operador == "-") {
            return esq_valor - dir_valor;
        } else if (operador == "*") {
            return esq_valor * dir_valor;
        } else if (operador == "/") {
            if (dir_valor == 0) {
                throw std::runtime_error("Erro: Divisão por zero.");
            }
            return esq_valor / dir_valor;
        } else {
            throw std::invalid_argument("Operador inválido: " + operador);
        }
    }
}

int main() {
    std::cout << "Início do programa." << std::endl;
    std::cout << "Segunda linha." << std::endl;

    // Construindo a árvore de exemplo da imagem: ((5+3)/4)*(6-1)
    ArvoreExpr n5 = arvoreExpr(NULL, "5", NULL);
    ArvoreExpr n3 = arvoreExpr(NULL, "3", NULL);
    ArvoreExpr mais = arvoreExpr(n5, "+", n3);
    ArvoreExpr n4 = arvoreExpr(NULL, "4", NULL);
    ArvoreExpr divisao = arvoreExpr(mais, "/", n4);
    ArvoreExpr n6 = arvoreExpr(NULL, "6", NULL);
    ArvoreExpr n1 = arvoreExpr(NULL, "1", NULL);
    ArvoreExpr menos = arvoreExpr(n6, "-", n1);
    ArvoreExpr raiz = arvoreExpr(divisao, "*", menos);

    try {
        std::cout << "Valor da expressão (raiz): " << valorExpr(raiz) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exceção ao avaliar raiz: " << e.what() << std::endl;
    }

    // Outro exemplo: (10 - 2) * 3
    ArvoreExpr n10 = arvoreExpr(NULL, "10", NULL);
    ArvoreExpr n2 = arvoreExpr(NULL, "2", NULL);
    ArvoreExpr subtracao = arvoreExpr(n10, "-", n2);
    ArvoreExpr n3_mult = arvoreExpr(NULL, "3", NULL);
    ArvoreExpr raiz2 = arvoreExpr(subtracao, "*", n3_mult);

    try {
        std::cout << "Valor da expressão (raiz2): " << valorExpr(raiz2) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exceção ao avaliar raiz2: " << e.what() << std::endl;
    }

    std::cout << "Fim do programa." << std::endl;
    return 0;
}