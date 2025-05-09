#include "simu_tarefas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para criar um novo heap de tarefas
HeapTarefas *criarHeap(int capacidade) {
    HeapTarefas *heap = (HeapTarefas *)malloc(sizeof(HeapTarefas));
    heap->tarefas = (Tarefa *)malloc(capacidade * sizeof(Tarefa));
    heap->tamanho = 0;
    heap->capacidade = capacidade;
    return heap;
}

// Função para trocar duas tarefas no heap
void trocarTarefas(Tarefa *a, Tarefa *b) {
    Tarefa temp = *a;
    *a = *b;
    *b = temp;
}

// Função para "heapificar" um nó (garantir a propriedade do heap mínimo)
void heapify(HeapTarefas *heap, int i) {
    int menor = i;
    int esquerda = 2 * i + 1;
    int direita = 2 * i + 2;

    if (esquerda < heap->tamanho && heap->tarefas[esquerda].prioridade < heap->tarefas[menor].prioridade) {
        menor = esquerda;
    }

    if (direita < heap->tamanho && heap->tarefas[direita].prioridade < heap->tarefas[menor].prioridade) {
        menor = direita;
    }

    if (menor != i) {
        trocarTarefas(&heap->tarefas[i], &heap->tarefas[menor]);
        heapify(heap, menor);
    }
}

// Função para inserir uma nova tarefa no heap
void inserirTarefa(HeapTarefas *heap, int id, const char *nome, int prioridade) {
    if (heap->tamanho == heap->capacidade) {
        printf("Heap cheio! Não é possível inserir mais tarefas.\n");
        return;
    }

    int i = heap->tamanho;
    heap->tamanho++;
    heap->tarefas[i].id = id;
    strcpy(heap->tarefas[i].nome, nome);
    heap->tarefas[i].prioridade = prioridade;

    // Ajustar a posição da nova tarefa para manter a propriedade do heap mínimo
    while (i > 0 && heap->tarefas[(i - 1) / 2].prioridade > heap->tarefas[i].prioridade) {
        trocarTarefas(&heap->tarefas[i], &heap->tarefas[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Função para obter a tarefa de maior prioridade (raiz do heap)
Tarefa obterProximaTarefa(HeapTarefas *heap) {
    if (heap->tamanho <= 0) {
        Tarefa tarefaVazia = {-1, "", -1};
        printf("Heap vazio! Nenhuma tarefa para obter.\n");
        return tarefaVazia;
    }

    Tarefa raiz = heap->tarefas[0];
    heap->tarefas[0] = heap->tarefas[heap->tamanho - 1];
    heap->tamanho--;
    heapify(heap, 0);
    return raiz;
}

// Função para verificar se o heap está vazio
int heapVazio(HeapTarefas *heap) {
    return heap->tamanho == 0;
}

// Função para liberar a memória alocada para o heap
void liberarHeap(HeapTarefas *heap) {
    free(heap->tarefas);
    free(heap);
}

int main() {
    int capacidade = 10;
    HeapTarefas *heap = criarHeap(capacidade);

    // Adicionando algumas tarefas com diferentes prioridades
    inserirTarefa(heap, 1, "Navegador", 3);
    inserirTarefa(heap, 2, "Editor de Texto", 1);
    inserirTarefa(heap, 3, "Compilador", 2);
    inserirTarefa(heap, 4, "Serviço de Email", 5);
    inserirTarefa(heap, 5, "Reprodutor de Música", 4);

    printf("Simulação de Gerenciamento de Tarefas:\n\n");

    printf("Estado inicial da fila de prioridade:\n");
    HeapTarefas *tempHeap = criarHeap(capacidade);
    for (int i = 0; i < heap->tamanho; i++) {
        tempHeap->tarefas[i] = heap->tarefas[i];
    }
    tempHeap->tamanho = heap->tamanho;

    while (!heapVazio(tempHeap)) {
        Tarefa tarefa = obterProximaTarefa(tempHeap);
        printf("ID: %d, Nome: %s, Prioridade: %d\n", tarefa.id, tarefa.nome, tarefa.prioridade);
    }
    liberarHeap(tempHeap);

    printf("\nExecutando tarefas na ordem de prioridade:\n");
    while (!heapVazio(heap)) {
        Tarefa proximaTarefa = obterProximaTarefa(heap);
        printf("Executando tarefa: ID %d (%s) com prioridade %d\n", proximaTarefa.id, proximaTarefa.nome, proximaTarefa.prioridade);
    }

    liberarHeap(heap);

    return 0;
}