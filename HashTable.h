#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "/home/ilopfal/PA/PRA_2425_P1/ListLinked.h"

using namespace std;

template <typename V>
class HashTable : public Dict<V> {
    private:
        int n;
        int max;
        ListLinked<TableEntry<V>>* table;

        int h(string key) {
            int hash = 0;
            for (char c : key) {
                hash += int(c);
            }
            return hash % max;
        }

    public:
        HashTable(int size) {
            max = size;
            n = 0;
            table = new ListLinked<TableEntry<V>>[max];
        }

        ~HashTable() {
            delete[] table;
        }

        void insert(string key, V value) override {
            int bucket = h(key);
            TableEntry<V> entry(key, value);

            try {
                table[bucket].search(entry);
                throw runtime_error("La llave ya existe en la tabla");
            } catch (runtime_error&) {
                table[bucket].insert(0, entry);
                n++;
            }
        }

        V search(string key) override {
            int bucket = h(key);
            TableEntry<V> entry(key);

            try {
                TableEntry<V> found = table[bucket].search(entry);
                return found.value;
            } catch (runtime_error&) {
                throw runtime_error("Llave ya no encontrada en la tabla");
            }
        }

        V remove(string key) override {
            int bucket = h(key);
            TableEntry<V> entry(key);

            try {
                TableEntry<V> found = table[bucket].remove(table[bucket].search(entry));
                n--;
                return found.value;
            } catch (runtime_error&) {
                throw runtime_error("Llave ya no encontrada en la tabla");
            }
        }

        int entries() override {
            return n;
        }

        int capacity() {
            return max;
        }

        V operator[](string key) {
            return search(key);
        }

        friend ostream& operator<<(ostream& out, const HashTable<V>& ht) {
            for (int i = 0; i < ht.max; i++) {
                out << "Bucket " << i << ": ";
                ListLinked<TableEntry<V>> bucket = ht.table[i];
                if (!bucket.empty()) {
                    for (int j = 0; j < bucket.size(); j++) {
                        out << bucket[j] << " ";
                    }
                }
                out << endl;
            }
            return out;
        }
};

#endif

