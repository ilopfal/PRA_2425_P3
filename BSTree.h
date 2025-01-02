#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree {
private:
    int nelem; // Número de elementos almacenados en el árbol.
    BSNode<T>* root; // Nodo raíz del árbol.

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw runtime_error("Elemento no encontrado");
        } else if (n->elem < e) {
            return search(n->right, e);
        } else if (n->elem > e) {
            return search(n->left, e);
        } else {
            return n;
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            return new BSNode<T>(e);
        } else if (n->elem == e) {
            throw runtime_error("Elemento duplicado");
        } else if (n->elem < e) {
            n->right = insert(n->right, e);
        } else {
            n->left = insert(n->left, e);
        }
        return n;
    }

    void print_inorder(ostream& out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
        }
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw runtime_error("Elemento no encontrado");
        } else if (n->elem < e) {
            n->right = remove(n->right, e);
        } else if (n->elem > e) {
            n->left = remove(n->left, e);
        } else {
            if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } else {
                BSNode<T>* tmp = n;
                n = (n->left != nullptr) ? n->left : n->right;
                delete tmp;
            }
        }
        return n;
    }

    T max(BSNode<T>* n) const {
        if (n == nullptr) {
            throw runtime_error("Árbol vacío");
        } else if (n->right != nullptr) {
            return max(n->right);
        } else {
            return n->elem;
        }
    }

    BSNode<T>* remove_max(BSNode<T>* n) {
        if (n->right == nullptr) {
            return n->left;
        } else {
            n->right = remove_max(n->right);
            return n;
        }
    }

    void delete_cascade(BSNode<T>* n) {
        if (n != nullptr) {
            delete_cascade(n->left);
            delete_cascade(n->right);
            delete n;
        }
    }

public:
    BSTree() : nelem(0), root(nullptr) {}

    ~BSTree() {
        delete_cascade(root);
    }

    int size() const {
        return nelem;
    }

    T search(T e) const {
        return search(root, e)->elem;
    }

    T operator[](T e) const {
        return search(e);
    }

    void insert(T e) {
        root = insert(root, e);
        nelem++;
    }

    void remove(T e) {
        root = remove(root, e);
        nelem--;
    }

    friend ostream& operator<<(ostream& out, const BSTree<T>& bst) {
        out << "[";
        bst.print_inorder(out, bst.root);
        out << "]";
        return out;
    }
};

#endif

