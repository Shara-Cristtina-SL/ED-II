Projeto heap_bin

Aplicação de heap binário

O código contém simulação simplificada de gerenciamento de tarefas em um sistema operacional usando um heap binário em C. Nesta simulação,
cada tarefa terá uma prioridade (um número inteiro, onde um valor menor indica maior prioridade). O heap binário será usado para armazenar 
as tarefas e sempre ter a tarefa de maior prioridade no topo.

Como a simulação funciona:

Estruturas de Dados:

Tarefa: Representa uma tarefa com um ID, nome e prioridade.
HeapTarefas: Representa o heap binário, contendo um array de tarefas, o tamanho atual e a capacidade máxima.
Criação do Heap:

criarHeap(capacidade): Aloca memória para a estrutura HeapTarefas e o array de tarefas com a capacidade especificada.
Operações no Heap:

trocarTarefas(): Uma função auxiliar para trocar duas tarefas de posição no array do heap.
heapify(heap, i): Mantém a propriedade do heap mínimo. Se um nó na posição i for maior que seus filhos, ele é trocado com o filho de menor prioridade,
e o processo se repete recursivamente.

inserirTarefa(heap, id, nome, prioridade): Insere uma nova tarefa no heap. A nova tarefa é adicionada ao final do array e, em seguida, "sobe" no heap 
trocando de lugar com seu pai enquanto sua prioridade for menor, mantendo a propriedade do heap mínimo.

obterProximaTarefa(heap): Remove e retorna a tarefa de maior prioridade (a raiz do heap). A última tarefa do heap é movida para a raiz, e heapify é 
chamada para restaurar a propriedade do heap mínimo.

heapVazio(heap): Verifica se o heap está vazio.

liberarHeap(heap): Libera a memória alocada para o heap.
Simulação no main():

Um heap de tarefas é criado com uma capacidade inicial.
Várias tarefas com diferentes prioridades são inseridas no heap.
O estado inicial da fila de prioridade (o heap) é impresso (para visualização).
As tarefas são "executadas" removendo-as do heap na ordem de prioridade (da maior para a menor prioridade) e imprimindo informações sobre a tarefa executada.

Para compilar e executar este código:

Salve o código em um arquivo com a extensão .c e outro.h (por exemplo, simu_tarefas.c e simu_tarefas.h).
-Modifique a iclusão do  arquivo de cabeçalho (#include "simu_tarefas.h") caso dê outro nome ao arquivo.
Abra um terminal ou prompt de comando.
Use um compilador C (como o GCC) para compilar o código:
Bash
gcc simu_tarefas.c -o simu_tarefas

Execute o programa:

Bash
./simu_tarefas
Você verá a saída mostrando as tarefas sendo adicionadas e, em seguida, sendo "executadas" na ordem de sua prioridade, demonstrando como um heap binário 
pode ser usado para gerenciar tarefas em um sistema operacional com base em prioridades. Em um sistema operacional real, essa estrutura seria usada pelo scheduler
para decidir qual processo executar em seguida.

Nesse caso específico da simulação de gerenciamento de tarefas com prioridades, estamos usando um heap mínimo (min-heap).

A razão para usar um min-heap é que definimos que quanto menor o valor da prioridade, maior a prioridade da tarefa. Queremos sempre extrair a tarefa com a menor 
prioridade (o valor numérico mais baixo) primeiro para simular a execução da tarefa de maior prioridade.

No nosso código:

A função heapify garante que o menor elemento (menor prioridade) sempre "suba" para a raiz.
A condição no while de inserirTarefa (heap->tarefas[(i - 1) / 2].prioridade > heap->tarefas[i].prioridade) move a nova tarefa para cima enquanto sua prioridade for
menor que a do seu pai.
A função obterProximaTarefa sempre remove o elemento da raiz, que é o elemento com a menor prioridade.
Se quiséssemos que um valor de prioridade maior indicasse maior prioridade, teríamos implementado um heap máximo (max-heap), onde a função heapify e a lógica de 
inserção seriam ajustadas para garantir que o maior elemento estivesse sempre na raiz.

Portanto, para essa simulação onde prioridades menores significam maior urgência, o min-heap é a estrutura correta a ser utilizada.

