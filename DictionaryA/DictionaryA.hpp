// File: DictionaryA/DictionaryA.hpp

#ifndef DICTIONARYA_HPP_
#define DICTIONARYA_HPP_

#include "ADictionary.hpp"
#include "ArrayP.hpp"

// ========= DictionaryA =========

template <class K, class V>
class DictionaryA : public ADictionary<K, V> {
private:
    ArrayP< DictPair<K, V> *> *_data;
    int _size; // Invariant: 0 <= _size <= _data->_cap().

public:

    DictionaryA(int cap) :
        _data(new ArrayP< DictPair<K, V> *>(cap)),
        _size(0) {
        for (int i = 0; i < _size; i++) {
            (*_data)[i] = nullptr;
        }

    }

    void clear() {
        for (int i = 0; i < _size; i++) {
            delete (*_data)[i];
            (*_data)[i] = nullptr;
        }
        _size = 0;
    }

    bool isFull() const {
        // Post: true is returned if this dictionary is full;
        // otherwise, false is returned.
        cerr << "isFull: Exercise for the student." << endl;
        throw -1;
    }

    void insert(K const &key, V const &val) {
        int lo = 0;
        int mid;
        int hi = _size - 1;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (key < (*_data)[mid]->key()) {
                hi = mid - 1;
            } else if (key > (*_data)[mid]->key()) {
                lo = mid + 1;
            } else {
                cerr << "DictionaryA<K, V>::insert: Exercise for the student." << endl;
                throw -1;
            }
        }
        if (isFull()) {
            cerr << "insert precondition violated: " <<
                "Cannot insert into a full dictionary." << endl;
            throw -1;
        }
        cerr << "DictionaryA<K, V>::insert: Exercise for the student." << endl;
        throw -1;
    }

    bool remove(K const &key, V &val) {
        cerr << "DictionaryA<K, V>::remove: Exercise for the student." << endl;
        throw -1;
    }

    bool contains(K const &key, V &val) const {
        int lo = 0;
        int mid;
        int hi = _size - 1;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (key < (*_data)[mid]->key()) {
                hi = mid - 1;
            } else if (key > (*_data)[mid]->key()) {
                lo = mid + 1;
            } else {
                val = (*_data)[mid]->val();
                return true;
            }
        }
        return false;
    }

    void toStream(ostream &os) const {
        for (int i = 0; i < _size; i++) {
            os << i << ": " << *(*_data)[i] << endl;
        }
    }
};

#endif
