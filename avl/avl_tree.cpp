#include <iostream>
#include <algorithm> // Para std::max
#include <queue>     // Para travessia por nível (imprimir fatores de balanceamento)

using namespace std;

// --- Estrutura do Nó ---
struct Node {
    int key;
    Node* left;
    Node* right;
    int height; // Altura do nó na árvore
};

// --- Funções Auxiliares ---

// Retorna a altura de um nó (0 se for nulo)
int height(Node* N) {
    return N ? N->height : 0;
}

// Retorna o maior de dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Cria um novo nó com a chave fornecida
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr; // Ponteiros para filhos nulos
    node->height = 1; // Novo nó é uma folha, altura 1
    return node;
}

// Obtém o fator de balanceamento de um nó
// Fator de balanceamento = altura(subárvore esquerda) - altura(subárvore direita)
int getBalance(Node* N) {
    return N ? height(N->left) - height(N->right) : 0;
}

// --- Rotações ---

Node* rightRotate(Node* y) {
    Node* x = y->left;   // 'x' é o filho esquerdo de 'y'
    Node* T2 = x->right; // 'T2' é a subárvore direita de 'x'

    // Realiza a rotação
    x->right = y;
    y->left = T2;

    // Atualiza as alturas dos nós afetados
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Retorna o novo nó raiz da subárvore rotacionada
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right; // 'y' é o filho direito de 'x'
    Node* T2 = y->left;  // 'T2' é a subárvore esquerda de 'y'

    // Realiza a rotação
    y->left = x;
    x->right = T2;

    // Atualiza as alturas dos nós afetados
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Retorna o novo nó raiz da subárvore rotacionada
    return y;
}

// Rotação Esquerda-Direita (LR Case)
Node* leftRightRotate(Node* node) {
    node->left = leftRotate(node->left); // Primeiro, rotação à esquerda no filho esquerdo
    return rightRotate(node);            // Depois, rotação à direita no nó atual
}

// Rotação Direita-Esquerda (RL Case)
Node* rightLeftRotate(Node* node) {
    node->right = rightRotate(node->right); // Primeiro, rotação à direita no filho direito
    return leftRotate(node);                 // Depois, rotação à esquerda no nó atual
}

// --- Inserção na Árvore AVL ---
Node* insert(Node* node, int key) {
    // 1. Inserção padrão de BST
    if (!node)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Chaves duplicadas não são permitidas em AVL
        return node;

    // 2. Atualiza a altura do nó ancestral
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Obtém o fator de balanceamento deste nó
    int balance = getBalance(node);

    // 4. Se o nó se tornou desbalanceado, aplica as rotações apropriadas

    // Caso LL (Left Left Case)
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Caso RR (Right Right Case)
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Caso LR (Left Right Case)
    if (balance > 1 && key > node->left->key)
        return leftRightRotate(node);

    // Caso RL (Right Left Case)
    if (balance < -1 && key < node->right->key)
        return rightLeftRotate(node);

    return node;
}

// Encontra o nó com o menor valor em uma subárvore (sucessor in-order)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// --- Remoção na Árvore AVL ---
Node* deleteNode(Node* root, int key) {
    // 1. Remoção padrão de BST
    if (!root)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else { // Nó com a chave a ser deletada encontrado
        // Caso 1: Nó com um filho ou nenhum filho
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;

            // Nenhum filho
            if (!temp) {
                delete root; // Libera a memória do nó
                return nullptr;
            } else { // Um filho
                Node* newRoot = temp; // O filho se torna o novo nó na posição
                delete root; // Libera a memória do nó a ser deletado
                return newRoot;
            }
        } else {
            // Caso 2: Nó com dois filhos
            // Encontra o sucessor in-order (menor nó na subárvore direita)
            Node* temp = minValueNode(root->right);
            // Copia a chave do sucessor in-order para este nó
            root->key = temp->key;
            // Deleta o sucessor in-order recursivamente da subárvore direita
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // Se a árvore ficou vazia após a remoção (era o único nó), retorna nulo
    if (!root)
        return root;

    // 2. Atualiza a altura do nó atual
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Obtém o fator de balanceamento
    int balance = getBalance(root);

    // 4. Se o nó se tornou desbalanceado, aplica as rotações apropriadas

    // Caso LL (Left Left Case)
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Caso LR (Left Right Case)
    if (balance > 1 && getBalance(root->left) < 0)
        return leftRightRotate(root);

    // Caso RR (Right Right Case)
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Caso RL (Right Left Case)
    if (balance < -1 && getBalance(root->right) > 0)
        return rightLeftRotate(root);

    return root;
}

// --- Travessia In-ordem ---
void inOrder(Node* root) {
    if (root) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

// --- Travessia Pré-ordem (Para visualização rápida da estrutura) ---
void preOrder(Node* root) {
    if (root) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// --- Imprimir Fatores de Balanceamento ---
// Imprime os fatores de balanceamento usando uma travessia em nível (BFS)
void printBalanceFactors(Node* root) {
    if (!root) {
        cout << "A arvore esta vazia." << endl;
        return;
    }

    queue<Node*> q;
    q.push(root);

    cout << "Fatores de Balanceamento (No: Fator): ";
    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->key << ": " << getBalance(current) << " | ";

        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
    cout << endl;
}

// --- Liberação de Memória da Árvore ---
void deleteTree(Node* node) {
    if (node == nullptr) {
        return;
    }
    deleteTree(node->left);   // Deleta recursivamente a subárvore esquerda
    deleteTree(node->right);  // Deleta recursivamente a subárvore direita
    delete node;              // Libera a memória do nó atual
}

// --- Função Principal ---
int main() {
    // --- Caso 1: Rotação Simples (Inclusão) ---
    cout << "--- Caso 1: Rotacao Simples (Inclusao) ---\n";
    Node* root_rs_incl_rr = nullptr;
    cout << "\nConstruindo arvore para RR Case (inserindo 10, 20, 30): \n";
    root_rs_incl_rr = insert(root_rs_incl_rr, 10);
    root_rs_incl_rr = insert(root_rs_incl_rr, 20);
    root_rs_incl_rr = insert(root_rs_incl_rr, 30);
    cout << "  Árvore em in-ordem: ";
    inOrder(root_rs_incl_rr);
    cout << "\n  Altura da arvore: " << height(root_rs_incl_rr) << endl;
    printBalanceFactors(root_rs_incl_rr);
    deleteTree(root_rs_incl_rr);
    cout << "-------------------------------------------\n";

    Node* root_rs_incl_ll = nullptr;
    cout << "\nConstruindo arvore para LL Case (inserindo 30, 20, 10): \n";
    root_rs_incl_ll = insert(root_rs_incl_ll, 30);
    root_rs_incl_ll = insert(root_rs_incl_ll, 20);
    root_rs_incl_ll = insert(root_rs_incl_ll, 10);
    cout << "  Árvore em in-ordem: ";
    inOrder(root_rs_incl_ll);
    cout << "\n  Altura da arvore: " << height(root_rs_incl_ll) << endl;
    printBalanceFactors(root_rs_incl_ll);
    deleteTree(root_rs_incl_ll);
    cout << "-------------------------------------------\n";

    // --- Caso 1: Rotação Simples (Remoção) ---
    cout << "\n--- Caso 1: Rotacao Simples (Remocao) ---\n";
    Node* root_rs_rem = nullptr;
    root_rs_rem = insert(root_rs_rem, 50);
    root_rs_rem = insert(root_rs_rem, 40);
    root_rs_rem = insert(root_rs_rem, 30);
    root_rs_rem = insert(root_rs_rem, 60);

    cout << "\nÁrvore antes da remoção (esperado in-ordem: 30 40 50 60): \n";
    cout << "  "; inOrder(root_rs_rem); cout << "\n";
    printBalanceFactors(root_rs_rem);

    cout << "\nRemovendo 60 (causara rotacao simples a direita):\n";
    root_rs_rem = deleteNode(root_rs_rem, 60);
    cout << "  Árvore após remoção de 60 (esperado in-ordem: 30 40 50): \n";
    cout << "  "; inOrder(root_rs_rem); cout << "\n";
    cout << "  Altura da arvore: " << height(root_rs_rem) << endl;
    printBalanceFactors(root_rs_rem);
    deleteTree(root_rs_rem);
    cout << "-------------------------------------------\n";

    // --- Caso 2: Rotação Dupla (Inclusão) ---
    cout << "\n--- Caso 2: Rotacao Dupla (Inclusao) ---\n";
    Node* root_rd_incl_lr = nullptr;
    cout << "\nConstruindo arvore para LR Case (inserindo 30, 10, 20): \n";
    root_rd_incl_lr = insert(root_rd_incl_lr, 30);
    root_rd_incl_lr = insert(root_rd_incl_lr, 10);
    root_rd_incl_lr = insert(root_rd_incl_lr, 20);
    cout << "  Árvore em in-ordem: ";
    inOrder(root_rd_incl_lr);
    cout << "\n  Altura da arvore: " << height(root_rd_incl_lr) << endl;
    printBalanceFactors(root_rd_incl_lr);
    deleteTree(root_rd_incl_lr);
    cout << "-------------------------------------------\n";

    Node* root_rd_incl_rl = nullptr;
    cout << "\nConstruindo arvore para RL Case (inserindo 10, 30, 20): \n";
    root_rd_incl_rl = insert(root_rd_incl_rl, 10);
    root_rd_incl_rl = insert(root_rd_incl_rl, 30);
    root_rd_incl_rl = insert(root_rd_incl_rl, 20);
    cout << "  Árvore em in-ordem: ";
    inOrder(root_rd_incl_rl);
    cout << "\n  Altura da arvore: " << height(root_rd_incl_rl) << endl;
    printBalanceFactors(root_rd_incl_rl);
    deleteTree(root_rd_incl_rl);
    cout << "-------------------------------------------\n";

    // --- Caso 2: Rotação Dupla (Remoção) ---
    cout << "\n--- Caso 2: Rotacao Dupla (Remocao) ---\n";
    Node* root_rd_rem = nullptr;
    root_rd_rem = insert(root_rd_rem, 30);
    root_rd_rem = insert(root_rd_rem, 15);
    root_rd_rem = insert(root_rd_rem, 40);
    root_rd_rem = insert(root_rd_rem, 10);
    root_rd_rem = insert(root_rd_rem, 20);
    root_rd_rem = insert(root_rd_rem, 5);

    cout << "\nÁrvore antes da remoção (exemplo para possivel RL apos remocao): \n";
    cout << "  "; inOrder(root_rd_rem); cout << "\n";
    printBalanceFactors(root_rd_rem);

    cout << "\nRemovendo 40 (pode causar rotacao dupla direita-esquerda, RL case):\n";
    root_rd_rem = deleteNode(root_rd_rem, 40);
    cout << "  Árvore após remoção de 40: \n";
    cout << "  "; inOrder(root_rd_rem); cout << "\n";
    cout << "  Altura da arvore: " << height(root_rd_rem) << endl;
    printBalanceFactors(root_rd_rem);
    deleteTree(root_rd_rem);
    cout << "-------------------------------------------\n";

    // Exemplo de remoção para demonstrar LR após remoção
    Node* root_rd_rem_lr = nullptr;
    root_rd_rem_lr = insert(root_rd_rem_lr, 20);
    root_rd_rem_lr = insert(root_rd_rem_lr, 10);
    root_rd_rem_lr = insert(root_rd_rem_lr, 30);
    root_rd_rem_lr = insert(root_rd_rem_lr, 5);
    root_rd_rem_lr = insert(root_rd_rem_lr, 15);
    root_rd_rem_lr = insert(root_rd_rem_lr, 25);

    cout << "\nÁrvore antes da remoção (exemplo para possivel LR apos remocao): \n";
    cout << "  "; inOrder(root_rd_rem_lr); cout << "\n";
    printBalanceFactors(root_rd_rem_lr);

    cout << "\nRemovendo 5 (pode causar rotacao dupla esquerda-direita, LR case):\n";
    root_rd_rem_lr = deleteNode(root_rd_rem_lr, 5);
    cout << "  Árvore após remoção de 5: \n";
    cout << "  "; inOrder(root_rd_rem_lr); cout << "\n";
    cout << "  Altura da arvore: " << height(root_rd_rem_lr) << endl;
    printBalanceFactors(root_rd_rem_lr);
    deleteTree(root_rd_rem_lr);
    cout << "-------------------------------------------\n";


    return 0;
}