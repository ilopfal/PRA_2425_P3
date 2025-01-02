#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>
using namespace std;

template <typename T>
class BSNode {
    public:
        T elem; // Elemento almacenado en el nodo
        BSNode<T>* left; // Puntero al nodo sucesor izquierdo
        BSNode<T>* right; // Puntero al nodo sucesor derecho

        BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr) 
            : elem(elem), left(left), right(right) {}

        friend ostream& operator<<(ostream& out, const BSNode<T>& bsn) {
            out << bsn.elem;
            return out;
        }
};

#endif

