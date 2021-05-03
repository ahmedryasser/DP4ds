// File: NTree/NTree.hpp

#ifndef NTREE_HPP_
#define NTREE_HPP_

#include <iostream>
#include "VectorP.hpp"
#include "VectorT.hpp"
#include "ANTreeVis.hpp"
using namespace std;

template<class T>
class NTree {
private:
    VectorT<T> *_data;
    VectorP<NTree<T> *> *_children;

private:
    NTree(NTree<T> const &rhs);
    // Copy constructor disabled.

    NTree(NTree<T> *left, T const &val, NTree<T> *right);
    // Pre: left and right are allocated.
    // Post: this tree has one root element with left the left subtree and right the right subtree.

    NTree(VectorT<T> *data, VectorP<NTree<T> *> *children);
    // Pre: data and children are allocated.
    // Post: The data vector are the data and the children vector are the children of this tree.

    NTree &operator=(NTree const &rhs); // to do

public:
    NTree();
    // Post: This tree is initialized to be empty.

    NTree(T const &val);
    // Post: This tree is initialized to have a single value val and no children.

    ~NTree();
    // Post: This tree is deallocated.

    T const &getData(int i) const;
    // Post: The data value at position i is returned.

    NTree<T> *getChild(int i) const;
    // Post: A pointer to the child tree at position i is returned.

    void spliceAt(int i, NTree<T>* tree);
    // Pre: 0 =< i <= _data->size().
    // Pre: tree is allocated.
    // Post: tree is spliced into this tree at position i.
    //       If tree is empty, this tree is unchanged.
    // Post: tree becomes the empty tree.
    // Post: The original tree at position i is not deallocated, which is the caller's responsibility.

    void splitUpAt(int i);
    // Post: If _data->size() <= 1 nothing is done. Otherwise,
    // Assert: 0 <= i < _data->size().
    // The element at position i is split up, becoming the root with a single value.

    void splitDownAt(int i);
    // Post: If _data->size() == 0 nothing is done. Otherwise,
    // Assert: 0 <= i < _data->size().
    // If _data->size() == 1 the single value is deleted and this tree is empty.
    // Otherwise, the element at position i is split down.

    void accept(ANTreeVis<T> &visitor);
    void accept(ANTreeVis<T> &visitor) const;
};

// ========= Private constructors =========
template<class T>
NTree<T>::NTree(NTree<T> *left, T const &val, NTree<T> *right) :
    _data(new VectorT<T> ()), _children(new VectorP<NTree<T> *> ()) {
    _data->append(val);
    _children->append(left);
    _children->append(right);
}

template<class T>
NTree<T>::NTree(VectorT<T> *data, VectorP<NTree<T> *> *children) :
    _data(data), _children(children) {
}

// ========= Public constructors =========
template<class T>
NTree<T>::NTree() :
    _data(new VectorT<T> ()), _children(new VectorP<NTree<T> *> ()) {
}

template<class T>
NTree<T>::NTree(T const &val) :
    _data(new VectorT<T> ()), _children(new VectorP<NTree<T>*> ()) {
    _data->append(val);
    _children->append(new NTree());
    _children->append(new NTree());
}

// ========= Destructor =========

template<class T>
NTree<T>::~NTree() {
    delete _data;
    _data = nullptr;
    delete _children;
    _children = nullptr;
}

// ========= Getters =========

template<class T>
T const &NTree<T>::getData(int i) const {
    return (*_data)[i];
}

template<class T>
NTree<T> *NTree<T>::getChild(int i) const {
    return (*_children)[i];
}

// ========= spliceAt =========
template<class T>
void NTree<T>::spliceAt(int i, NTree<T>* tree) {
    if (i < 0 || _data->size() < i) {
        cerr << "spliceAt precondition 0 =< i <= _data->size() violated." << endl;
        cerr << "i == " << i << ", _data->size() == " << _data->size() << endl;
        throw -1;
    }
    int treeSize = tree->_data->size();
    if (treeSize == 0) { // Tree being inserted is empty.
        return;
    }
    if (_data->size() == 0) { // Receiver tree is empty. There is no (*_children)[0], so insert instead.
        _children->insert(i, tree->_children->remove(treeSize--));
    } else {
        (*_children)[i] = tree->_children->remove(treeSize--);
    }
    for (int k = treeSize; k >= 0; k--) {
        _data->insert(i, tree->_data->remove(k));
        _children->insert(i, tree->_children->remove(k));
    }
}

// ========= splitUpAt =========
template<class T>
void NTree<T>::splitUpAt(int i) {
    if (_data->size() <= 1) {
        return;
    }
    if (i < 0 || _data->size() <= i) {
        cerr << "splitUpAt precondition 0 <= i < _data->size() violated." << endl;
        cerr << "i == " << i << ", _data->size() == " << _data->size() << endl;
        throw -1;
    }
    VectorT<T> *newData = new VectorT<T > ();
    VectorP<NTree<T>*> *newChildren = new VectorP<NTree<T>*> ();
    T rootDat = _data->remove(i); // This element will be at the new root.
    for (int k = 0; k < i; k++) {
        newData->append(_data->remove(k));
        newChildren->append(_children->remove(k));
    }
    newChildren->append(_children->remove(0));
    NTree<T> *left, *right;
    if (newData->size() > 0) {
        left = new NTree(newData, newChildren);
    } else {
        left = newChildren->remove(0);
        delete newChildren;
        delete newData;
    }
    if (_data->size() > 0) {
        right = new NTree(_data, _children);
    } else {
        right = _children->remove(0);
        delete _children;
        delete _data;
    }
    _data = new VectorT<T> ();
    _data->append(rootDat);
    _children = new VectorP<NTree<T>*>();
    _children->append(left);
    _children->append(right);
}

// ========= splitDownAt =========
template<class T>
void NTree<T>::splitDownAt(int i) {
    if (_data->size() == 0) {
        return;
    }
    if (i < 0 || _data->size() <= i) {
        cerr << "splitDownAt precondition 0 <= i < _data->size() violated." << endl;
        cerr << "i == " << i << ", _data->size() == " << _data->size() << endl;
        throw -1;
    }
    if (_data->size() == 1) {
        _data->remove(0); // _data is now empty.
        delete (_children->remove(0));
        delete (_children->remove(0));
    } else {
        NTree<T> *newChild = new NTree(getChild(i), _data->remove(i), getChild(i + 1));
        _children->remove(i);
        _children->insert(i, newChild);
    }
}

// ========= accept =========
template<class T>
void NTree<T>::accept(ANTreeVis<T> &visitor) {
    visitor.caseAt(_data->size(), *this);
}

// ========= accept const =========
template<class T>
void NTree<T>::accept(ANTreeVis<T>& visitor) const {
    visitor.caseAt(_data->size(), *this);
}

// ========= operator= =========

// to do.

#endif
