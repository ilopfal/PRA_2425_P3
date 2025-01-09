#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree {
private:
    BSNode<T>* root;
    int nelem;

    BSNode<T>* search(BSNode<T>* n, T e) const {
        if (n == nullptr) {
            throw runtime_error("Elemento no encontrado.");
        } else if (e < n->elem) {
            return search(n->left, e);
        } else if (e > n->elem) {
            return search(n->right, e);
        } else {
            return n;
        }
    }

    BSNode<T>* insert(BSNode<T>* n, T e) {
        if (n == nullptr) {
            nelem++;
            return new BSNode<T>(e);
        } else if (e < n->elem) {
            n->left = insert(n->left, e);
        } else if (e > n->elem) {
            n->right = insert(n->right, e);
        } else {
            throw runtime_error("Elemento duplicado.");
        }
        return n;
    }

    BSNode<T>* remove(BSNode<T>* n, T e) {
        if (n == nullptr) {
            throw runtime_error("Elemento no encontrado.");
        } else if (e < n->elem) {
            n->left = remove(n->left, e);
        } else if (e > n->elem) {
            n->right = remove(n->right, e);
        } else {
            if (n->left != nullptr && n->right != nullptr) {
                n->elem = max(n->left);
                n->left = remove_max(n->left);
            } else {
                BSNode<T>* temp = (n->left != nullptr) ? n->left : n->right;
                delete n;
                nelem--;
                return temp;
            }
        }
        return n;
    }

    T max(BSNode<T>* n) const {
        if (n->right != nullptr) {
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

    void print_inorder(ostream& out, BSNode<T>* n) const {
        if (n != nullptr) {
            print_inorder(out, n->left);
            out << n->elem << " ";
            print_inorder(out, n->right);
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
    BSTree() : root(nullptr), nelem(0) {}

    ~BSTree() {
        delete_cascade(root);
    }

    int size() const {
        return nelem;
    }

    T search(T e) const {
        return search(root, e)->elem;
    }

    void insert(T e) {
        root = insert(root, e);
    }

    void remove(T e) {
        root = remove(root, e);
    }

    friend ostream& operator<<(ostream& out, const BSTree<T>& bst) {
        out << "Elementos del ABB (inorden): ";
        bst.print_inorder(out, bst.root);
        return out;
    }
};

#endif



