#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>>* tree; // Árbol binario de búsqueda para gestionar el diccionario.

public:
    BSTreeDict() {
        tree = new BSTree<TableEntry<V>>(); // Crear un ABB vacío.
    }

    ~BSTreeDict() {
        delete tree; // Liberar memoria dinámica ocupada por el ABB.
    }

    void insert(string key, V value) override {
        TableEntry<V> entry(key, value);
        tree->insert(entry); // Insertar el par clave-valor en el ABB.
    }

    V search(string key) override {
        TableEntry<V> entry(key);
        return tree->search(entry).value; // Buscar el valor asociado a la clave.
    }

    V remove(string key) override {
        TableEntry<V> entry(key);
        V value = tree->search(entry).value; // Obtener el valor antes de eliminarlo.
        tree->remove(entry); // Eliminar el par clave-valor del ABB.
        return value;
    }

    int entries() override {
        return tree->size(); // Devolver el número de elementos en el ABB.
    }

    V operator[](string key) {
        return search(key); // Interfaz al método search para buscar valores por clave.
    }

    friend ostream& operator<<(ostream& out, const BSTreeDict<V>& bs) {
        out << *(bs.tree); // Imprimir el contenido del ABB.
        return out;
    }
};

#endif

