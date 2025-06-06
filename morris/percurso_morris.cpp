#include <iostream>
#include "arv_bi_morris.h"
#include <iostream> 


Node* newNode(int value) {
    return new Node(value);
}

void morrisInOrder(Node* root) {
    Node* current = root;
    while (current != nullptr) {
        if (current->left == nullptr) {
            std::cout << current->value << " ";
            current = current->right;
        } else {
            Node* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current)
                predecessor = predecessor->right;

            if (predecessor->right == nullptr) {
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                std::cout << current->value << " ";
                current = current->right;
            }
        }
    }
}

void morrisPreOrder(Node* root) {
    Node* current = root;
    while (current != nullptr) {
        if (current->left == nullptr) {
            std::cout << current->value << " ";
            current = current->right;
        } else {
            Node* predecessor = current->left;
            while (predecessor->right != nullptr && predecessor->right != current)
                predecessor = predecessor->right;

            if (predecessor->right == nullptr) {
                std::cout << current->value << " ";
                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                current = current->right;
            }
        }
    }
}

int main() {
    // Construção da árvore exemplo:
     Node * root = newNode(10);
    root->left = newNode(5);
    root->right = newNode(20);
    root->left->left = newNode(3);
    root->left->right = newNode(7);
    root->right->left = newNode(15);
    root->right->right = newNode(24);

    std::cout << "Morris In-Order Traversal (LVR):\n";
    morrisInOrder(root);  // Saída esperada: 3 5 7 10 15 20 24



    

    std::cout << std::endl;
    return 0;
}

//*int main() {
    // Construção da árvore exemplo:
  //   Node * root = newNode(10);
  //  root->left = newNode(5);
  //  root->right = newNode(20);
  //  root->left->left = newNode(3);
    //root->left->right = newNode(7);

  //  std::cout << "Morris In-Order Traversal (LVR):\n";
   // morrisInOrder(root);  // Saída esperada: 3 5 7 10 20

   // std::cout << "\n\nMorris Pre-Order Traversal (VLR):\n";
    //morrisPreOrder(root);  // Saída esperada: 10 5 3 7 20*\


    

    //std::cout << std::endl;
   // return 0;
//} *\


