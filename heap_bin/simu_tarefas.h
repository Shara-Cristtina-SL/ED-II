#ifndef GERENCIAMENTO_TAREFAS_H
#define GERENCIAMENTO_TAREFAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar uma tarefa
typedef struct {
    int id;
    char nome[50];
    int prioridade;
} Tarefa;

// Estrutura para representar o heap binário
typedef struct {
    Tarefa *tarefas;
    int tamanho;
    int capacidade;
} HeapTarefas;

// Função para criar um novo heap de tarefas
HeapTarefas *criarHeap(int capacidade);

// Função para trocar duas tarefas no heap
void trocarTarefas(Tarefa *a, Tarefa *b);

// Função para "heapificar" um nó (garantir a propriedade do heap mínimo)
void heapify(HeapTarefas *heap, int i);

// Função para inserir uma nova tarefa no heap
void inserirTarefa(HeapTarefas *heap, int id, const char *nome, int prioridade);

// Função para obter a tarefa de maior prioridade (raiz do heap)
Tarefa obterProximaTarefa(HeapTarefas *heap);

// Função para verificar se o heap está vazio
int heapVazio(HeapTarefas *heap);

// Função para liberar a memória alocada para o heap
void liberarHeap(HeapTarefas *heap);

#endif // GERENCIAMENTO_TAREFAS_H