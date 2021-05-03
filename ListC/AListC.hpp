// File: AListC/ListC.hpp

#ifndef AListC_hpp
#define AListC_hpp

#include <iostream> // ostream.
using namespace std;

// ========= The abstract list =========
template<class T>
class AListC {

public:
    virtual ~AListC() = 0;
    // Pre: This list exists.
    // Post: This list is deallocated.

    virtual T const &first() const = 0;
    // Pre: This list is not empty.
    // Post: A reference to the first element of this list is returned.

    virtual AListC<T> const &rest() const = 0;
    // Pre: This list is not empty.
    // Post: A reference to the rest of this list is returned.

    virtual AListC<T> *clone() const = 0;
    // Post: A pointer to a copy of this list is returned.

    virtual AListC<T> *prepend(T val) const = 0;
    // Post: A pointer to a copy of this list with val prepended is returned.

    virtual AListC<T> *append(T val) const = 0;
    // Post: A pointer to a copy of this list with val appended is returned.

    virtual AListC<T> *concat(AListC<T> const *suffix) const = 0;
    // Post: A pointer to a copy of this list with suffix appended is returned.

    virtual AListC<T> *reverse() const = 0;
    // Post: A pointer to a copy of this list reversed is returned.

    virtual int length() const = 0;
    // Post: The length of this list is returned.

    virtual bool isEmpty() const = 0;
    // Post: true is returned if this list is empty; Otherwise, false is returned.

    virtual bool contains(T val) const = 0;
    // Post: true is returned if val is contained in this list; Otherwise, false
    // is returned

    virtual bool equals(AListC<T> const &rhs) const = 0;
    // Pre: Type T can be compared for equality using the operator==.
    // Post: true is returned if this list equals list rhs; Otherwise, false is returned.
    // Two lists are equal if they contain the same number of equal elements in the same order.

    virtual T const &max() const = 0;
    // Pre: This list is not empty. Type T has a total ordering.
    // Post: The maximum element of this list is returned.

    virtual AListC<T> *remFirst() const = 0;
    // Post: A pointer to a copy of this list with with the first element removed
    // is returned. An empty list is returned if this list is empty.

    virtual AListC<T> *remLast() const = 0;
    // Post: A pointer to a copy of this list with with the last element removed
    // is returned. An empty list is returned if this list is empty.

    virtual AListC<T> *remove(T val) const = 0;
    // Post: If val is in this list, a pointer to a copy of this list with with
    // the first occurrence of val is returned; Otherwise a copy of this list
    // unchanged is returned.

    virtual AListC<T> *zip(AListC<T> const *other) const = 0;
    // Post: A pointer to a copy of this list perfectly shuffled with with a copy
    // of other, starting with the first element of this, is returned.

    virtual AListC<T> *evenIndex() const = 0;
    // Post: A pointer to a copy of every other element of this list starting
    // with the first one is returned.

    virtual AListC<T> *oddIndex() const = 0;
    // Post: A pointer to a copy of every other element of this list starting
    // with the second one is returned.

    virtual void toStream(ostream &os) const = 0;
    // Post: A string representation of this list is returned.

    virtual T const &maxHelper(T const &m) const = 0;

};

// ========= operator== =========
template<class T>
bool operator==(AListC<T> const &lhs, AListC<T> const &rhs) {
    return lhs.equals(rhs);
}

// ========= operator<< =========
// Post: List rhs is output to ostream.
template<class T>
ostream &operator<<(ostream &os, AListC<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= Destructor =========
template<class T>
AListC<T>::~AListC() {
}

#endif
