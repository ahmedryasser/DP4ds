// File: ListCSV/ListCSV.hpp

#ifndef LISTCSV_HPP_
#define LISTCSV_HPP_

template<class T> class AcsvNode; // Forward declaration.
template<class T> class MTcsvNode; // Forward declaration.
template<class T> class NEcsvNode; // Forward declaration.

#include <iostream>
#include "AListCSVVis.hpp"
using namespace std;

// ========= ListCSV =========

template<class T>
class ListCSV {
    friend class MTcsvNode<T>;
    friend class NEcsvNode<T>;

private:
    AcsvNode<T> *_head;

private:
    ListCSV(ListCSV<T> const &rhs);
    // Copy constructor disabled.

    ListCSV(AcsvNode<T> *node);
    // Pre: node != nullptr.
    // Post: _head points to node with no allocation.

public:
    ListCSV();
    // Post: This list is initialized to be empty.

    ~ListCSV();
    // Post: This list is deallocated.

public:
    void accept(AListCSVVis<T> &visitor);
    void accept(AListCSVVis<T> &visitor) const;

private:
    AcsvNode<T> *copyHead(ListCSV<T> const &rhs);
    // Post: A deep copy of the head of rhs is returned.

public:
    T &first();
    T const &first() const;
    // Pre: This list is not empty.
    // Post: The first element of this list is returned.

    ListCSV &operator=(ListCSV const &rhs);
    // Post: A deep copy of rhs is returned with garbage collection.

    void prepend(T const &data);
    // Post: data is prepended to this list.

    T remFirst();
    // Pre: This list is not empty.
    // Post: The first element is removed from this list and returned.

    ListCSV<T> &rest();
    ListCSV<T> const &rest() const;
    // Pre: This list is not empty.
    // Post: A reference to the rest of this list is returned.

    void setList(ListCSV<T> &list);
    // Post: This list is deallocated and set to list.
    // list is the empty list (cut setList, as opposed to copy setList).
};

// ========= AcsvNode =========

template<class T>
class AcsvNode {
    friend class ListCSV<T>;
    friend class MTcsvNode<T>;
    friend class NEcsvNode<T>;

public:
    virtual ~AcsvNode();
    // Virtual destructor necessary for subclassing.

protected:
    virtual void accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) = 0;
    virtual void accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) = 0;

private:
    virtual AcsvNode *copyHead() = 0;
    // Post: A deep copy of this node is returned.

protected:
    virtual T &first() = 0;
    virtual T const &first() const = 0;
    virtual void prepend(ListCSV<T> &owner, T const &data) = 0;
    virtual T remFirst(ListCSV<T> &owner) = 0;
    virtual ListCSV<T> &rest() = 0;
    virtual ListCSV<T> const &rest() const = 0;
    virtual void setList(ListCSV<T> &owner, ListCSV<T> &tail) = 0;
};

// ========= MTcsvNode =========

template<class T>
class MTcsvNode : public AcsvNode<T> {
    friend class ListCSV<T>;
    friend class NEcsvNode<T>;

private:
    MTcsvNode();
    MTcsvNode(MTcsvNode<T> const &rhs); // Disabled.
    MTcsvNode &operator=(MTcsvNode<T> const &rhs); // Disabled for node.

protected:
    void accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) override;
    void accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) override;

private:
    AcsvNode<T> *copyHead() override;

protected:
    T &first() override;
    T const &first() const override;
    void prepend(ListCSV<T> &owner, T const &data) override;
    T remFirst(ListCSV<T> &owner) override;
    ListCSV<T> &rest() override;
    ListCSV<T> const &rest() const override;
    void setList(ListCSV<T> &owner, ListCSV<T> &list) override;
};

// ========= NEcsvNode =========

template<class T>
class NEcsvNode : public AcsvNode<T> {
    friend class ListCSV<T>;
    friend class MTcsvNode<T>;

private:
    T _data;
    ListCSV<T> _rest;

private:
    NEcsvNode(T data, AcsvNode<T> *node);
    // Post: _data is data and _rest._head points to node.
    // _rest owns node and is responsible for garbage collection.

    NEcsvNode(NEcsvNode<T> const *rhs);
    // Post: _data is rhs->_data and _rest is rhs->_rest.

    NEcsvNode &operator=(NEcsvNode<T> const &rhs); // Disabled for node.

protected:
    void accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) override;
    void accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) override;

private:
    AcsvNode<T> *copyHead() override;

protected:
    T &first() override;
    T const &first() const override;
    void prepend(ListCSV<T> &owner, T const &data) override;
    T remFirst(ListCSV<T> &owner) override;
    ListCSV<T> &rest() override;
    ListCSV<T> const &rest() const override;
    void setList(ListCSV<T> &owner, ListCSV<T> &list) override;
};

// ========= Constructors =========

template<class T>
ListCSV<T>::ListCSV() :
    _head(new MTcsvNode<T>()) {
}

template<class T>
ListCSV<T>::ListCSV(AcsvNode<T> *node) :
    _head(node) {
}

template<class T>
MTcsvNode<T>::MTcsvNode() {
}

template<class T>
NEcsvNode<T>::NEcsvNode(T data, AcsvNode<T> *node) :
    _data(data) {
    _rest._head = node;
}

template<class T>
NEcsvNode<T>::NEcsvNode(NEcsvNode const *rhs) :
    _data(rhs->_data),
    _rest(rhs->_rest) {
}

// ========= Destructors =========

template<class T> // Recursively deletes this list.
ListCSV<T>::~ListCSV() {
    delete _head;
}

template < class T >
AcsvNode<T>::~AcsvNode() {
}

// ========= accept =========

template<class T>
void ListCSV<T>::accept(AListCSVVis<T> &visitor) {
    _head->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(ListCSV<T> &owner, AListCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= accept const =========

template<class T>
void ListCSV<T>::accept(AListCSVVis<T> &visitor) const {
    _head->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(ListCSV<T> const &owner, AListCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= copyHead =========

template<class T>
AcsvNode<T> *ListCSV<T>::copyHead(ListCSV<T> const &rhs) {
    return rhs._head->copyHead();
}

template<class T>
AcsvNode<T> *MTcsvNode<T>::copyHead() {
    return new MTcsvNode<T > ();
}

template<class T>
AcsvNode<T> *NEcsvNode<T>::copyHead() {
    return new NEcsvNode<T > (_data, _rest._head->copyHead());
}

// ========= first =========

template<class T>
T &ListCSV<T>::first() {
    return _head->first();
}

template<class T>
T &MTcsvNode<T>::first() {
    cerr << "Precondition violated: No first in empty list" << endl;
    throw -1;
}

template<class T>
T &NEcsvNode<T>::first() {
    return _data;
}

// ========= first const =========

template<class T>
T const &ListCSV<T>::first() const {
    return _head->first();
}

template<class T>
T const &MTcsvNode<T>::first() const {
    cerr << "Precondition violated: No first in empty list" << endl;
    throw -1;
}

template<class T>
T const &NEcsvNode<T>::first() const {
    return _data;
}

// ========= prepend =========

template<class T>
void ListCSV<T>::prepend(T const &data) {
    _head->prepend(*this, data);
}

template < class T >
void MTcsvNode<T>::prepend(ListCSV<T> &owner, T const &data) {
    // Assert: owner._head is this MTcsNode
    // No memory leak as the constructor does not allocate a node.
    owner._head = new NEcsvNode<T > (data, this);
}

template < class T >
void NEcsvNode<T>::prepend(ListCSV<T> &owner, T const &data) {
    owner._head = new NEcsvNode<T > (data, this);
}

// ========= remFirst =========

template < class T >
T ListCSV<T>::remFirst() {
    return _head->remFirst(*this);
}

template<class T>
T MTcsvNode<T>::remFirst(ListCSV<T> &owner) {
    cerr << "MTcsvNode<T>::remFirst: Exercise for the student." << endl;
    throw -1;
}

template<class T>
T NEcsvNode<T>::remFirst(ListCSV<T> &owner) {
    T result = _data;
    owner._head = _rest._head;
    _rest._head = nullptr;
    delete this;
    return result;
}

// ========= rest =========

template < class T >
ListCSV<T> &ListCSV<T>::rest() {
    return _head->rest();
}

template<class T>
ListCSV<T> &MTcsvNode<T>::rest() {
    cerr << "rest precondition violated: "
         << "An empty list has no rest." << endl;
    throw -1;
}

template<class T>
ListCSV<T> &NEcsvNode<T>::rest() {
    return _rest;
}

// ========= rest const =========

template < class T >
ListCSV<T> const &ListCSV<T>::rest() const {
    return _head->rest();
}

template<class T>
ListCSV<T> const &MTcsvNode<T>::rest() const {
    cerr << "rest precondition violated: "
         << "An empty list has no rest." << endl;
    throw -1;
}

template<class T>
ListCSV<T> const &NEcsvNode<T>::rest() const {
    return _rest;
}

// ========= setList =========

template<class T>
void ListCSV<T>::setList(ListCSV<T> &list) {
    _head->setList(*this, list);
}

template<class T>
void MTcsvNode<T>::setList(ListCSV<T> &owner, ListCSV<T> &list) {
    delete owner._head;
    owner._head = list._head;
    list._head = new MTcsvNode<T > ();
}

template<class T>
void NEcsvNode<T>::setList(ListCSV<T> &owner, ListCSV<T> &list) {
    delete owner._head;
    owner._head = list._head;
    list._head = new MTcsvNode<T > ();
}

// ========= operator= =========

template<class T>
ListCSV<T> &ListCSV<T>::operator=(ListCSV const &rhs) {
    if (this != &rhs) { // In case someone writes myList = myList;
        delete _head;
        _head = copyHead(rhs);
    }
    return *this;
}

#endif
