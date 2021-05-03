// File: ListC/ListC.hpp

#ifndef LISTC_HPP_
#define LISTC_HPP_

#include <iostream> // ostream.
#include "AListC.hpp"
using namespace std;

// ========= The empty(MT) list =========
template<class T>
class MTListC :public AListC<T> {

private:
    MTListC(MTListC const &rhs); // Disabled.
    MTListC &operator=(MTListC const &rhs); // Disabled.

public:
    MTListC() {
    } // inline.

    T const &first() const override;
    AListC<T> const &rest() const override;

    AListC<T> *clone() const override;
    AListC<T> *prepend(T val) const override;
    AListC<T> *append(T val) const override;
    AListC<T> *concat(AListC<T> const *suffix) const override;

    AListC<T> *reverse() const override;
    AListC<T> *reverseHelper(AListC<T> *accumReverse) const override;

    int length() const override;
    bool isEmpty() const override;
    bool contains(T val) const override;

    bool equals(AListC<T> const &rhs) const override;
    bool equalsHelper(T first, AListC<T> const &rest) const override;

    T const &max() const override;
    T const &maxHelper(T const &m) const override;

    AListC<T> *remFirst() const override;

    AListC<T> *remLast() const override;
    AListC<T> *remLastHelper(T f) const override;

    AListC<T> *remove(T val) const override;
    AListC<T> *zip(AListC<T> const *other) const override;
    AListC<T> *evenIndex() const override;
    AListC<T> *oddIndex() const override;

    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;
};

// ========= The non-empty(NE) list =========
template<class T>
class NEListC :public AListC<T> {

private:
    T _first;
    AListC<T> *_rest;

private:
    NEListC(NEListC const &rhs); // Disabled.
    NEListC &operator=(NEListC const &rhs); // Disabled.

public:
    NEListC(T first);
    // Post: This list exists and contains exactly one element, first.

    NEListC(T first, AListC<T> const *rest);
    // Post: This list exists and contains first and a copy of rest.

    ~NEListC();
    // Pre: This list exists.
    // Post: This list is deallocated.

    T const &first() const override;
    AListC<T> const &rest() const override;

    AListC<T> *clone() const override;
    AListC<T> *prepend(T val) const override;
    AListC<T> *append(T val) const override;
    AListC<T> *concat(AListC<T> const *suffix) const override;

    AListC<T> *reverse() const override;
    AListC<T> *reverseHelper(AListC<T> *accumReverse) const override;

    int length() const override;
    bool isEmpty() const override;
    bool contains(T val) const override;

    bool equals(AListC<T> const &rhs) const override;
    bool equalsHelper(T first, AListC<T> const &rest) const override;

    T const &max() const override;
    T const &maxHelper(T const &m) const override;

    AListC<T> *remFirst() const override;

    AListC<T> *remLast() const override;
    AListC<T> *remLastHelper(T f) const override;

    AListC<T> *remove(T val) const override;
    AListC<T> *zip(AListC<T> const *other) const override;
    AListC<T> *evenIndex() const override;
    AListC<T> *oddIndex() const override;

    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;

};

// ========= Constructors =========
template<class T>
NEListC<T>::NEListC(T first) :_first(first), _rest(new MTListC<T>()) {
}
template<class T>
NEListC<T>::NEListC(T first, AListC<T> const *rest) :_first(first), _rest(rest->clone()) {
}

// ========= Destructors =========
template<class T>
NEListC<T>::~NEListC() {
    delete _rest;
}

// ========= first =========
template<class T>
T const &MTListC<T>::first() const {
    cerr << "first() precondition violated: An empty list has no first." << endl;
    throw -1;
}
template<class T>
T const &NEListC<T>::first() const {
    return _first;
}

// ========= rest =========
template<class T>
AListC<T> const &MTListC<T>::rest() const {
    cerr << "rest() precondition violated: An empty list has no rest." << endl;
    throw -1;
}
template<class T>
AListC<T> const &NEListC<T>::rest() const {
    return *_rest;
}

// ========= clone =========
template<class T>
AListC<T> *MTListC<T>::clone() const {
    return new MTListC<T>();
}
template<class T>
AListC<T> *NEListC<T>::clone() const {
    return new NEListC<T>(_first, _rest);
}

// ========= prepend =========
template<class T>
AListC<T> *MTListC<T>::prepend(T val) const {
    //  return new NEListC<T>(val, new NEListC<T>()); would be a memory leak.
    return new NEListC<T>(val, this);
}
template<class T>
AListC<T> *NEListC<T>::prepend(T val) const {
    return new NEListC<T>(val, this);
}

// ========= append =========
template<class T>
AListC<T> *MTListC<T>::append(T val) const {
    //  return new NEListC<T>(val, new NEListC<T>()); would be a memory leak.
    return new NEListC<T>(val, this);
}
template<class T>
AListC<T> *NEListC<T>::append(T val) const {
    //  return new NEListC<T>(_first, _rest->append(val)); would be a memory leak.
    AListC<T> *temp = _rest->append(val);
    NEListC<T> *result = new NEListC<T>(_first, temp);
    delete temp;
    return result;
}

// ========= concat =========
template<class T>
AListC<T> *MTListC<T>::concat(AListC<T> const *suffix) const {
    cerr << "MTListC<T>::concat: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::concat(AListC<T> const *suffix) const {
    //  return new NEListC<T>(_first, _rest->concat(suffix)); would be a memory leak.
    cerr << "NEListC<T>::concat: Exercise for the student." << endl;
    throw -1;
}

// ========= reverse =========
template<class T>
AListC<T> *MTListC<T>::reverse() const {
    return new MTListC<T>();
}
template<class T>
AListC<T> *NEListC<T>::reverse() const {
    AListC<T> *accRev = new NEListC<T>(_first);
    AListC<T> *result = _rest->reverseHelper(accRev);
    delete accRev;
    return result;
}
template<class T>
AListC<T> *MTListC<T>::reverseHelper(AListC<T> *accumReverse) const {
    return accumReverse->clone();
}
template<class T>
AListC<T> *NEListC<T>::reverseHelper(AListC<T> *accumReverse) const {
    AListC<T> *accRev = new NEListC<T>(_first, accumReverse);
    AListC<T> *result = _rest->reverseHelper(accRev);
    delete accRev;
    return result;
}

// ========= length =========
template<class T>
int MTListC<T>::length() const {
    cerr << "MTListC<T>::length: Exercise for the student." << endl;
    throw -1;
}
template<class T>
int NEListC<T>::length() const {
    cerr << "NEListC<T>::length: Exercise for the student." << endl;
    throw -1;
}

// ========= isEmpty =========
template<class T>
bool MTListC<T>::isEmpty() const {
    cerr << "MTListC<T>::isEmpty: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::isEmpty() const {
    cerr << "NEListC<T>::isEmpty: Exercise for the student." << endl;
    throw -1;
}

// ========= contains =========
template<class T>
bool MTListC<T>::contains(T val) const {
    cerr << "MTListC<T>::contains: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::contains(T val) const {
    cerr << "bool NEListC<T>::contains: Exercise for the student." << endl;
    throw -1;
}

// ========= equals =========
template<class T>
bool MTListC<T>::equals(AListC<T> const &rhs) const {
    cerr << "MTListC<T>::equals: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::equals(AListC<T> const &rhs) const {
    cerr << "NEListC<T>::equals: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool MTListC<T>::equalsHelper(T, AListC<T> const &) const {
    cerr << "MTListC<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}
template<class T>
bool NEListC<T>::equalsHelper(T first, AListC<T> const &rest) const {
    cerr << "NEListC<T>::equalsHelper: Exercise for the student." << endl;
    throw -1;
}

// ========= max =========
template<class T>
T const &MTListC<T>::max() const {
    cerr << "Precondition violated: An empty list has no maximum." << endl;
    throw -1;
}
template<class T>
T const &NEListC<T>::max() const {
    return _rest->maxHelper(_first);
}
template<class T>
T const &MTListC<T>::maxHelper(T const &m) const {
    return m;
}
template<class T>
T const &NEListC<T>::maxHelper(T const &m) const {
    return _first <= m ? _rest->maxHelper(m) : _rest->maxHelper(_first);
}

// ========= remFirst =========
template<class T>
AListC<T> *MTListC<T>::remFirst() const {
    return new MTListC<T>();
}
template<class T>
AListC<T> *NEListC<T>::remFirst() const {
    return _rest->clone();
}

// ========= remLast =========
template<class T>
AListC<T> *MTListC<T>::remLast() const {
    cerr << "MTListC<T>::remLast: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::remLast() const {
    cerr << "NEListC<T>::remLast: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *MTListC<T>::remLastHelper(T f) const {
    cerr << "MTListC<T>::remLastHelper: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::remLastHelper(T f) const {
    cerr << "NEListC<T>::remLastHelper: Exercise for the student." << endl;
    throw -1;
}

// ========= remove =========
template<class T>
AListC<T> *MTListC<T>::remove(T val) const {
    cerr << "MTListC<T>::remove: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::remove(T val) const {
    cerr << "NEListC<T>::remove: Exercise for the student." << endl;
    throw -1;
}

// ========= zip =========
template<class T>
AListC<T> *MTListC<T>::zip(AListC<T> const *other) const {
    cerr << "MTListC<T>::zip: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::zip(AListC<T> const *other) const {
    cerr << "NEListC<T>::zip: Exercise for the student." << endl;
    throw -1;
}

// ========= evenIndex =========
template<class T>
AListC<T> *MTListC<T>::evenIndex() const {
    cerr << "MTListC<T>::evenIndex: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::evenIndex() const {
    cerr << "NEListC<T>::evenIndex: Exercise for the student." << endl;
    throw -1;
}

// ========= oddIndex =========
template<class T>
AListC<T> *MTListC<T>::oddIndex() const {
    cerr << "MTListC<T>::oddIndex: Exercise for the student." << endl;
    throw -1;
}
template<class T>
AListC<T> *NEListC<T>::oddIndex() const {
    cerr << "NEListC<T>::oddIndex: Exercise for the student." << endl;
    throw -1;
}

// ========= toStream =========
template<class T>
void MTListC<T>::toStream(ostream &os) const {
    os << "()";
}
template<class T>
void NEListC<T>::toStream(ostream &os) const {
    cerr << "NEListC<T>::toStream: Exercise for the student." << endl;
    throw -1;
}
template<class T>
void MTListC<T>::toStreamHelper(ostream &os) const {
    cerr << "MTListC<T>::toStreamHelper: Exercise for the student." << endl;
    throw -1;
}
template<class T>
void NEListC<T>::toStreamHelper(ostream &os) const {
    cerr << "NEListC<T>::toStreamHelper: Exercise for the student." << endl;
    throw -1;
}

#endif
