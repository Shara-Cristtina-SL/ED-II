#ifndef THREADED_TREE
#define THREADED_TREE
#include <iostream> 

template<class T>
class ThreadedNode {
public:
    T el;
    ThreadedNode *left, *right;
    unsigned int successor;

    ThreadedNode() {
        left = right = 0;
        successor = 0;
    }

    ThreadedNode(const T& e, ThreadedNode *l = 0, ThreadedNode *r = 0) {
        el = e;
        left = l;
        right = r;
        successor = 0;
    }
};

template<class T>
class ThreadedTree {
public:
    ThreadedTree() {
        root = 0;
    }

    void insert(const T& el); // Inserção 
    void inorder(); // Percurso em ordem 

protected:
    ThreadedNode<T>* root;
};

template<class T>
void ThreadedTree<T>::insert(const T& el) {
    ThreadedNode<T> *p = root, *prev = 0, *newNode;
    newNode = new ThreadedNode<T>(el);

    if (root == 0) {
        root = newNode;
        return;
    }

    p = root;

    while (p != 0) {
        prev = p;
        if (p->el > el)
            p = p->left;
        else if (p->successor == 0)
            p = p->right;
        else
            break;
    }

    if (prev->el > el) {
        prev->left = newNode;
        newNode->right = prev;
        newNode->successor = 1;
    } else if (prev->successor == 1) {
        newNode->right = prev->right;
        newNode->successor = 1;
        prev->right = newNode;
        prev->successor = 0;
    } else {
        prev->right = newNode;
    }
}

template<class T>
void ThreadedTree<T>::inorder() {
    ThreadedNode<T> *prev, *p = root;

    if (p != 0) {
        while (p->left != 0)
            p = p->left;

        while (p != 0) {
            std::cout << p->el << " ";
            prev = p;
            p = p->right;

            if (p != 0 && prev->successor == 0) {
                while (p->left != 0)
                    p = p->left;
            }
        }
    }
}

#endif