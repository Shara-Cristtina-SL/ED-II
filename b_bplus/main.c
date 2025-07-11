#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ORDEM 3

typedef struct {
    int codigo;
    char nome[50];
} Cliente;

typedef struct BPlusNode {
    int chaves[ORDEM - 1];
    int rrn_filhos[ORDEM];
    int num_chaves;
    int eh_folha;
    int proximo_rrn_folha;
} BPlusNode;

// ==== PROTÓTIPOS DAS FUNÇÕES ====
void escrever_cliente(Cliente c, int rrn);
Cliente ler_cliente(int rrn);
void escrever_no(BPlusNode no, int rrn);
BPlusNode ler_no(int rrn);
void inicializar_arquivos();
void fechar_arquivos();
int criar_novo_no(int eh_folha);
int buscar_no_folha(int rrn_no_atual, int chave_busca);
void buscar_cliente(int codigo);
void inserir_em_no(BPlusNode *no, int chave, int rrn_dado_ou_filho);
int inserir_recursivo(int rrn_atual, int codigo, int rrn_cliente_dado, int *chave_promovida, int *rrn_novo_no_promovido);
void inserir_cliente(Cliente c);
void percorrer_em_ordem();
void imprimir_arvore(int rrn, int nivel);

FILE *arquivo_dados;
FILE *arquivo_indice;
int proximo_rrn_indice = 0;
int proximo_rrn_dados = 0;
int RRN_RAIZ = -1;

void escrever_cliente(Cliente c, int rrn) {
    fseek(arquivo_dados, rrn * sizeof(Cliente), SEEK_SET);
    fwrite(&c, sizeof(Cliente), 1, arquivo_dados);
    if (rrn == proximo_rrn_dados) proximo_rrn_dados++;
}

Cliente ler_cliente(int rrn) {
    Cliente c;
    fseek(arquivo_dados, rrn * sizeof(Cliente), SEEK_SET);
    fread(&c, sizeof(Cliente), 1, arquivo_dados);
    return c;
}

void escrever_no(BPlusNode no, int rrn) {
    fseek(arquivo_indice, rrn * sizeof(BPlusNode), SEEK_SET);
    fwrite(&no, sizeof(BPlusNode), 1, arquivo_indice);
    if (rrn == proximo_rrn_indice) proximo_rrn_indice++;
}

BPlusNode ler_no(int rrn) {
    BPlusNode no;
    fseek(arquivo_indice, rrn * sizeof(BPlusNode), SEEK_SET);
    fread(&no, sizeof(BPlusNode), 1, arquivo_indice);
    return no;
}

void inicializar_arquivos() {
    arquivo_dados = fopen("clientes.dat", "rb+");
    if (!arquivo_dados) {
        arquivo_dados = fopen("clientes.dat", "wb+");
        proximo_rrn_dados = 0;
    } else {
        fseek(arquivo_dados, 0, SEEK_END);
        proximo_rrn_dados = ftell(arquivo_dados) / sizeof(Cliente);
    }

    arquivo_indice = fopen("indice.dat", "rb+");
    if (!arquivo_indice) {
        arquivo_indice = fopen("indice.dat", "wb+");
        proximo_rrn_indice = 0;
        RRN_RAIZ = -1;
    } else {
        fseek(arquivo_indice, 0, SEEK_END);
        proximo_rrn_indice = ftell(arquivo_indice) / sizeof(BPlusNode);
        FILE *f_raiz = fopen("raiz.dat", "rb");
        if (f_raiz) {
            fread(&RRN_RAIZ, sizeof(int), 1, f_raiz);
            fclose(f_raiz);
        } else {
            RRN_RAIZ = proximo_rrn_indice > 0 ? 0 : -1;
        }
    }
}

void fechar_arquivos() {
    if (arquivo_dados) fclose(arquivo_dados);
    if (arquivo_indice) fclose(arquivo_indice);
    FILE *f_raiz = fopen("raiz.dat", "wb");
    if (f_raiz) {
        fwrite(&RRN_RAIZ, sizeof(int), 1, f_raiz);
        fclose(f_raiz);
    }
}


// <<-------------------------pessoa 2 ------------------------------->>

int criar_novo_no(int eh_folha) {
    BPlusNode novo_no = {};
    novo_no.eh_folha = eh_folha;
    novo_no.proximo_rrn_folha = -1;
    escrever_no(novo_no, proximo_rrn_indice);
    return proximo_rrn_indice - 1;
}

int buscar_no_folha(int rrn_no_atual, int chave_busca) {
    if (rrn_no_atual == -1) return -1;
    BPlusNode no_atual = ler_no(rrn_no_atual);
    while (!no_atual.eh_folha) {
        int i = 0;
        while (i < no_atual.num_chaves && chave_busca >= no_atual.chaves[i]) i++;
        rrn_no_atual = no_atual.rrn_filhos[i];
        no_atual = ler_no(rrn_no_atual);
    }
    return rrn_no_atual;
}

void buscar_cliente(int codigo) {
    if (RRN_RAIZ == -1) {
        printf("Árvore vazia. Cliente não encontrado.\n");
        return;
    }
    int rrn_folha = buscar_no_folha(RRN_RAIZ, codigo);
    if (rrn_folha == -1) {
        printf("Cliente com código %d não encontrado.\n", codigo);
        return;
    }
    BPlusNode folha = ler_no(rrn_folha);
    for (int i = 0; i < folha.num_chaves; i++) {
        if (folha.chaves[i] == codigo) {
            Cliente cliente = ler_cliente(folha.rrn_filhos[i]);
            printf("Código: %d | Nome: %s\n", cliente.codigo, cliente.nome);
            return;
        }
    }
    printf("Cliente com código %d não encontrado.\n", codigo);
}


void inserir_em_no(BPlusNode *no, int chave, int rrn_dado_ou_filho) {
    int i = no->num_chaves - 1;
    while (i >= 0 && chave < no->chaves[i]) {
        no->chaves[i + 1] = no->chaves[i];
        no->rrn_filhos[i + 1] = no->rrn_filhos[i];
        i--;
    }
    no->chaves[i + 1] = chave;
    no->rrn_filhos[i + 1] = rrn_dado_ou_filho;
    no->num_chaves++;
}

// <<-------------------------pessoa 3 ------------------------------->>

int inserir_recursivo(int rrn_atual, int codigo, int rrn_cliente_dado, int *chave_promovida, int *rrn_novo_no_promovido) {
    // Lê o nó atual do arquivo de índice
    BPlusNode no_atual = ler_no(rrn_atual);

    // Caso base: se o nó for uma folha
    if (no_atual.eh_folha) {
        // Verifica se o nó folha está cheio
        if (no_atual.num_chaves == ORDEM - 1) {
            // Cria novo nó folha
            BPlusNode novo_no = {};
            novo_no.eh_folha = 1;

            // Arrays temporários para reordenar as chaves e filhos (dados)
            int temp_chaves[ORDEM];
            int temp_rrn_filhos[ORDEM];

            // Insere a nova chave e rrn no array temporário na posição correta
            int i = 0;
            while (i < no_atual.num_chaves && codigo > no_atual.chaves[i]) {
                temp_chaves[i] = no_atual.chaves[i];
                temp_rrn_filhos[i] = no_atual.rrn_filhos[i];
                i++;
            }
            temp_chaves[i] = codigo;
            temp_rrn_filhos[i] = rrn_cliente_dado;

            // Copia o restante dos elementos antigos
            for (int j = i; j < no_atual.num_chaves; j++) {
                temp_chaves[j + 1] = no_atual.chaves[j];
                temp_rrn_filhos[j + 1] = no_atual.rrn_filhos[j];
            }

            // Divide os elementos entre os dois nós
            no_atual.num_chaves = 0;
            for (i = 0; i < ORDEM / 2; i++) {
                inserir_em_no(&no_atual, temp_chaves[i], temp_rrn_filhos[i]);
            }
            for (i = ORDEM / 2; i < ORDEM; i++) {
                inserir_em_no(&novo_no, temp_chaves[i], temp_rrn_filhos[i]);
            }

            // Ajusta ponteiros entre folhas
            novo_no.proximo_rrn_folha = no_atual.proximo_rrn_folha;
            no_atual.proximo_rrn_folha = proximo_rrn_indice;

            // Escreve os nós de volta no arquivo
            escrever_no(no_atual, rrn_atual);
            int novo_rrn = criar_novo_no(1);
            escrever_no(novo_no, novo_rrn);

            // Prepara a chave promovida e o novo RRN para retornar ao pai
            *chave_promovida = novo_no.chaves[0];
            *rrn_novo_no_promovido = novo_rrn;

            return 1; // Indica que houve divisão
        } else {
            // Se o nó não está cheio, apenas insere e salva
            inserir_em_no(&no_atual, codigo, rrn_cliente_dado);
            escrever_no(no_atual, rrn_atual);
            return 0;
        }
    } else {
        // Caso recursivo: nó interno
        int i = 0;
        while (i < no_atual.num_chaves && codigo >= no_atual.chaves[i]) i++;

        // Chamada recursiva para o filho apropriado
        int divisao_filho = inserir_recursivo(no_atual.rrn_filhos[i], codigo, rrn_cliente_dado, chave_promovida, rrn_novo_no_promovido);

        if (divisao_filho) {
            // Se o nó atual estiver cheio, precisa dividir
            if (no_atual.num_chaves == ORDEM - 1) {
                BPlusNode novo_no = {};
                novo_no.eh_folha = 0;

                int temp_chaves[ORDEM];
                int temp_rrn_filhos[ORDEM + 1];

                // Copia chaves e ponteiros
                for (i = 0; i < ORDEM - 1; i++) {
                    temp_chaves[i] = no_atual.chaves[i];
                    temp_rrn_filhos[i] = no_atual.rrn_filhos[i];
                }
                temp_rrn_filhos[ORDEM - 1] = no_atual.rrn_filhos[ORDEM - 1];

                // Insere a nova chave promovida na posição correta
                int j = 0;
                while (j < ORDEM - 1 && *chave_promovida > temp_chaves[j]) j++;
                for (int k = ORDEM - 1; k > j; k--) {
                    temp_chaves[k] = temp_chaves[k - 1];
                    temp_rrn_filhos[k + 1] = temp_rrn_filhos[k];
                }
                temp_chaves[j] = *chave_promovida;
                temp_rrn_filhos[j + 1] = *rrn_novo_no_promovido;

                // Divide as chaves
                no_atual.num_chaves = 0;
                for (i = 0; i < ORDEM / 2; i++) {
                    inserir_em_no(&no_atual, temp_chaves[i], -1);
                    no_atual.rrn_filhos[i] = temp_rrn_filhos[i];
                }
                no_atual.rrn_filhos[i] = temp_rrn_filhos[i];

                for (int k = ORDEM / 2 + 1, j = 0; k < ORDEM; k++, j++) {
                    inserir_em_no(&novo_no, temp_chaves[k], -1);
                    novo_no.rrn_filhos[j] = temp_rrn_filhos[k];
                }
                novo_no.rrn_filhos[ORDEM / 2] = temp_rrn_filhos[ORDEM];

                *chave_promovida = temp_chaves[ORDEM / 2];

                escrever_no(no_atual, rrn_atual);
                int novo_rrn = criar_novo_no(0);
                escrever_no(novo_no, novo_rrn);
                *rrn_novo_no_promovido = novo_rrn;

                return 1;
            } else {
                // Se há espaço, insere a chave promovida normalmente
                inserir_em_no(&no_atual, *chave_promovida, -1);
                int pos_filho = 0;
                while (pos_filho < no_atual.num_chaves && *chave_promovida > no_atual.chaves[pos_filho]) pos_filho++;
                for (int j = no_atual.num_chaves; j > pos_filho; j--) {
                    no_atual.rrn_filhos[j] = no_atual.rrn_filhos[j - 1];
                }
                no_atual.rrn_filhos[pos_filho + 1] = *rrn_novo_no_promovido;
                escrever_no(no_atual, rrn_atual);
                return 0;
            }
        } else {
            return 0;
        }
    }
}


void inserir_cliente(Cliente c) {
    int rrn_cliente = proximo_rrn_dados;
    escrever_cliente(c, rrn_cliente);
    if (RRN_RAIZ == -1) {
        int folha = criar_novo_no(1);
        BPlusNode no = ler_no(folha);
        inserir_em_no(&no, c.codigo, rrn_cliente);
        escrever_no(no, folha);
        RRN_RAIZ = folha;
    } else {
        int chave_promovida, rrn_novo_no;
        int cresceu = inserir_recursivo(RRN_RAIZ, c.codigo, rrn_cliente, &chave_promovida, &rrn_novo_no);
        if (cresceu) {
            int nova_raiz = criar_novo_no(0);
            BPlusNode raiz = ler_no(nova_raiz);
            raiz.chaves[0] = chave_promovida;
            raiz.rrn_filhos[0] = RRN_RAIZ;
            raiz.rrn_filhos[1] = rrn_novo_no;
            raiz.num_chaves = 1;
            escrever_no(raiz, nova_raiz);
            RRN_RAIZ = nova_raiz;
        }
    }
    imprimir_arvore(RRN_RAIZ, 0); // NOVO: imprimir após inserção
}

// <<-------------------------pessoa 2 ------------------------------->>

void percorrer_em_ordem() {
    if (RRN_RAIZ == -1) {
        printf("Árvore vazia.\n");
        return;
    }

    int rrn_folha = RRN_RAIZ;
    while (!ler_no(rrn_folha).eh_folha) {
        rrn_folha = ler_no(rrn_folha).rrn_filhos[0];  // Navegar até a primeira folha
    }

    while (rrn_folha != -1) {
        BPlusNode folha = ler_no(rrn_folha);
        for (int i = 0; i < folha.num_chaves; i++) {
            Cliente c = ler_cliente(folha.rrn_filhos[i]);
            printf("Código: %d | Nome: %s\n", c.codigo, c.nome);
        }
        rrn_folha = folha.proximo_rrn_folha;  
    }
}


void imprimir_arvore(int rrn, int nivel) {
    if (rrn == -1) return;
    BPlusNode no = ler_no(rrn);
    printf("%*s[Nó %d | %s]: ", nivel * 4, "", rrn, no.eh_folha ? "Folha" : "Interno");
    for (int i = 0; i < no.num_chaves; i++) printf("%d ", no.chaves[i]);
    printf("\n");
    if (!no.eh_folha) {
        for (int i = 0; i <= no.num_chaves; i++)
            imprimir_arvore(no.rrn_filhos[i], nivel + 1);
    }
}

// <<-------------------------TODOS ------------------------------->>
int main() {
    inicializar_arquivos();

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Inserir cliente\n");
        printf("2. Buscar cliente por código\n");
        printf("3. Listar clientes em ordem\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer

        if (opcao == 1) {
            Cliente c;
            printf("Digite o código do cliente: ");
            scanf("%d", &c.codigo);
            getchar();
            printf("Digite o nome do cliente: ");
            fgets(c.nome, sizeof(c.nome), stdin);
            c.nome[strcspn(c.nome, "\n")] = '\0'; // remover \n
            inserir_cliente(c);
        } else if (opcao == 2) {
            int cod;
            printf("Digite o código a buscar: ");
            scanf("%d", &cod);
            buscar_cliente(cod);
        } else if (opcao == 3) {
            printf("\n--- Clientes em ordem crescente ---\n");
            percorrer_em_ordem();
        }
    } while (opcao != 0);

    fechar_arquivos();
    return 0;
}