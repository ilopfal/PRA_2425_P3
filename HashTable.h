#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/ilopfal/PA/PRA_2425_P1/ListLinked.h"  

using namespace std;

template <typename V>
class HashTable : public Dict<V> {
private:
    int n; 
    int max; // Tamaño de la tabla hash (número total de cubetas).
    ListLinked<TableEntry<V>>* table; // Array de listas enlazadas para manejar colisiones.

    int h(const string& key) const {
        int sum = 0;
        for (char ch : key) {
            sum += static_cast<int>(ch); // Suma los valores ASCII de los caracteres de la clave.
        }
        return sum % max; // Resto de la división entre la suma y el tamaño de la tabla.
    }

public:
    HashTable(int size) : n(0), max(size) {
        if (size <= 0) {
            throw invalid_argument("El tamaño de la tabla debe ser mayor que 0.");
        }
        table = new ListLinked<TableEntry<V>>[size]; // Reservar memoria dinámica para la tabla.
    }

    ~HashTable() {
        delete[] table; // Liberar la memoria dinámica.
    }

    int capacity() const { // Eliminamos override
        return max; // Devolver el número total de cubetas.
    }

    int entries() override {
        return n; // Devolver el número de elementos almacenados.
    }

    void insert(string key, V value) override {
        try {
            search(key); // Comprobar si la clave ya existe.
        } catch (const runtime_error&) {
            table[h(key)].prepend(TableEntry<V>(key, value)); // Insertar el nuevo par clave-valor.
            n++;
            return;
        }
        throw runtime_error("La clave '" + key + "' ya existe.");
    }

    V search(string key) override {
        int bucket = h(key);
        for (int i = 0; i < table[bucket].size(); i++) {
            if (table[bucket].get(i).key == key) {
                return table[bucket].get(i).value; // Devolver el valor asociado a la clave.
            }
        }
        throw runtime_error("La clave '" + key + "' no se encontró.");
    }

    V remove(string key) override {
        int bucket = h(key);
        for (int i = 0; i < table[bucket].size(); i++) {
            if (table[bucket].get(i).key == key) {
                TableEntry<V> removed = table[bucket].remove(i); // Eliminar el par clave-valor.
                n--;
                return removed.value;
            }
        }
        throw runtime_error("La clave '" + key + "' no se encontró.");
    }

    V operator[](string key) {
        return search(key); // Sobrecarga del operador [] para buscar valores por clave.
    }

    friend ostream& operator<<(ostream &out, const HashTable<V> &th) {
        out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]" << std::endl;
        out << "==============" << endl << endl;
        for (int i = 0; i < th.max; i++) {
            out << "== Cubeta " << i << " ==" << std::endl << std::endl;
            out << "List => [";
            if (th.table[i].size() != 0) {
                out << endl;
                for (int j = 0; j < th.table[i].size(); j++) {
                    out << "  ('" << th.table[i].get(j).key << "' => " << th.table[i].get(j).value << ")" << endl;
                }
            }
            out << "]" << endl << endl;
        }
        out << "==============" << endl;
        return out;
    }
};

#endif




