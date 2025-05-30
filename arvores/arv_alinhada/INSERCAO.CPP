#include "arv_ali.h"
#include <iostream>

int main() {
    ThreadedTree<int> tree;

    // Inserção de elementos na árvore
    tree.insert(15);
    tree.insert(17);
    tree.insert(4);
    tree.insert(20);
    tree.insert(19);

    std::cout << "Percurso em ordem (in-order): ";
    tree.inorder();  // Saída esperada: 4 15 17 19 20
    std::cout << std::endl;

    return 0;
}