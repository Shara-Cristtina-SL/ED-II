#ifndef BINARY_TREE_H
#define BINARY_TREE_H

// Estrutura do nó da árvore binária
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Funções de criação e percurso
Node* newNode(int value);
void morrisInOrder(Node* root);
void morrisPreOrder(Node* root);

#endif // BINARY_TREE_H
