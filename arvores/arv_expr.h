#ifndef ARV_H
#define ARV_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <cctype> // Para isdigit
#include <stdexcept> // Para std::invalid_argument
#include <algorithm> // Para std::max

// Definição da struct original para árvore de inteiros
typedef struct arvore_int {
    struct arvore_int *esq;
    int item;
    struct arvore_int *dir;
} *ArvoreInt;

// Definição da struct para árvore de expressão aritmética (strings para item)
typedef struct arvore_expr {
    struct arvore_expr *esq;
    std::string item;
    struct arvore_expr *dir;
} *ArvoreExpr;

// Funções para árvore de inteiros (manter para compatibilidade se necessário)
ArvoreInt arvoreInt(ArvoreInt e, int x, ArvoreInt d);
void percorre_preordem_int(ArvoreInt A);
void percorre_inordem_int(ArvoreInt A);
void percorre_posordem_int(ArvoreInt A);
int nosInt(ArvoreInt A);
int folhasInt(ArvoreInt A);
int alturaInt(ArvoreInt A);
bool temInt(ArvoreInt A, int x);
bool ebInt(ArvoreInt A);
bool igualInt(ArvoreInt A, ArvoreInt B);

// Funções específicas para árvore de expressão aritmética
ArvoreExpr arvoreExpr(ArvoreExpr e, std::string item, ArvoreExpr d);
void percorre_preordem_expr(ArvoreExpr A);
void percorre_inordem_expr(ArvoreExpr A);
void percorre_posordem_expr(ArvoreExpr A);
int nosExpr(ArvoreExpr A);
int folhasExpr(ArvoreExpr A);
int alturaExpr(ArvoreExpr A);
bool temExpr(ArvoreExpr A, std::string x);
bool ebExpr(ArvoreExpr A);
bool igualExpr(ArvoreExpr A, ArvoreExpr B);
int valorExpr(ArvoreExpr A);

#endif // ARV_H