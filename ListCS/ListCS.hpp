// File: ListCS/ListCS.hpp

#ifndef LISTCS_HPP_
#define LISTCS_HPP_

#include <iostream> // ostream.
using namespace std;

template<class T> class AcsNode; // Forward declaration.
template<class T> class NEcsNode; // Forward declaration.
template<class T> class MTcsNode; // Forward declaration.

// ========= ListCS =========
template<class T>
class ListCS {
    friend class NEcsNode<T>;
    friend class MTcsNode<T>;

private:
    AcsNode<T> *_head;

private:
    ListCS(ListCS<T> const &rhs);
    // Copy constructor disabled.

    ListCS(AcsNode<T> *node);
    // Post: _head points to node with no allocation.

public:
    ListCS();
    // Post: This list is initialized to be empty.

    ~ListCS();
    // Post: This list is deallocated.

    void append(T const &data);
    // Post: data is appended to this list.

    void clear();
    // Post: This list is cleared to the empty list.

    void concat(ListCS<T> &suffix);
    // Post: suffix is appended to this list.
    // suffix is empty (cut concatenate, as opposed to copy concatenate).

    bool contains(T const &data) const;
    // Post: true is returned if data is contained in this list;
    // Otherwise, false is returned.

private:
    AcsNode<T> *copyHead(ListCS<T> const &rhs);
    // Post: A deep copy of the head of rhs is returned.

public:
    bool equals(ListCS<T> const &rhs) const;
    // Post: true is returned if this list equals list rhs; Otherwise, false is returned.
    // Two lists are equal if they contain the same number of equal elements in the same order.

private:
    bool equalsHelper(T const &first, ListCS<T> const &rest) const;
    // Post: true is returned if first equals this->first() and rest equals this->rest();
    // Otherwise, false is returned.

public:
    T &first();
    T const &first() const;
    // Pre: This list is not empty.
    // Post: A reference to the first element of this list is returned.

    bool isEmpty() const;
    // Post: true is returned if this list is empty; otherwise, false is returned.

    int length() const;
    // Post: The length of this list is returned.

    T const &max() const;
    // Pre: This list is not empty.
    // Post: The maximum element of this list is returned.

private:
    T const &maxHelper(T const &val) const;
    // Post: The maximum element of this list and val is returned.

public:
    ListCS &operator=(ListCS<T> const &rhs);
    // Post: A deep copy of rhs is returned with garbage collection.

    void prepend(T const &data);
    // Post: data is prepended to this list.

    T remFirst();
    // Pre: This list is not empty.
    // Post: The first element is removed from this list and returned.

    T remLast();
    // Pre: This list is not empty.
    // Post: The last element is removed from this list and returned.
private:
    T remLastHelper(ListCS<T> &previous);
    // Pre: previous.rest() is this list.
    // Post: The last element of previous is removed and returned.

public:
    void remove(T const &data);
    // Post: If data is in this list, it is removed; Otherwise this list is unchanged.

    ListCS<T> &rest();
    ListCS<T> const &rest() const;
    // Pre: This list is not empty.
    // Post: A reference to the rest of this list is returned.

    void reverse();
    // Post: This list is reversed.

private:
    void reverseHelper(ListCS<T> &revList);
    // Post: This list is prepended to revList in reverse order, and this list is empty.

public:
    void setList(ListCS<T> &list);
    // Post: This list is deallocated and set to list.
    // list is the empty list (cut setList, as opposed to copy setList).

    void toStream(ostream &os) const;
    // Post: A string representation of this list is returned.

    ListCS<T> *unZip();
    // Post: This is every other element of this list starting with the first.
    // A pointer to a list with every other element of this list starting with the second is returned.

    void zip(ListCS<T> &other);
    // Post: This list is a perfect shuffle of this list and other
    // starting with the first element of this.
    // other is the empty list (cut zip, as opposed to copy zip).
};

// ========= AcsNode =========
template<class T>
class AcsNode {
    friend class ListCS<T>;
    friend class MTcsNode<T>;
    friend class NEcsNode<T>;

public:
    virtual ~AcsNode() {
    }
    // Virtual destructor necessary for subclassing.

protected:
    virtual void append(ListCS<T> &owner, T const &data) = 0;
    virtual void clear(ListCS<T> &owner) = 0;
    virtual void concat(ListCS<T> &owner, ListCS<T> &suffix) = 0;
    virtual bool contains(T const &data) const = 0;
private:
    virtual AcsNode *copyHead() = 0;
protected:
    virtual bool equals(ListCS<T> const &rhs) const = 0;
    virtual bool equalsHelper(T const &first, ListCS<T> const &rest) const = 0;
    virtual T &first() = 0;
    virtual T const &first() const = 0;
    virtual bool isEmpty() const = 0;
    virtual int length() const = 0;
    virtual T const &max() const = 0;
    virtual T const &maxHelper(T const &data) const = 0;
    virtual void prepend(ListCS<T> &owner, T const &data) = 0;
    virtual T remFirst(ListCS<T> &owner) = 0;
    virtual T remLast(ListCS<T> &owner) = 0;
    virtual T remLastHelper(ListCS<T> &owner, ListCS<T> &previous) = 0;
    virtual void remove(ListCS<T> &owner, T const &data) = 0;
    virtual ListCS<T> &rest() = 0;
    virtual ListCS<T> const &rest() const = 0;
    virtual void reverse(ListCS<T> &owner) = 0;
    virtual void reverseHelper(ListCS<T> &owner, ListCS<T> &revList) = 0;
    virtual void setList(ListCS<T> &owner, ListCS<T> &list) = 0;
    virtual void toStream(ostream &os) const = 0;
    virtual void toStreamHelper(ostream &os) const = 0;
    // Post: A string representation of this list is returned
    // except for the leading open parenthesis "(", which is omitted.
    virtual ListCS<T> *unZip() = 0;
    virtual void zip(ListCS<T> &owner, ListCS<T> &other) = 0;
};

// ========= MTcsNode =========
template<class T>
class MTcsNode : public AcsNode<T> {
    friend class ListCS<T>;
    friend class NEcsNode<T>;

private:
    MTcsNode() {
    }
    MTcsNode(MTcsNode<T> const &rhs); // Disabled.
    MTcsNode &operator=(MTcsNode const &rhs); // Disabled for node.

protected:
    void append(ListCS<T> &owner, T const &data);
    void clear(ListCS<T> &owner);
    void concat(ListCS<T> &owner, ListCS<T> &suffix);
    bool contains(T const &data) const;
private:
    AcsNode<T> *copyHead();
protected:
    bool equals(ListCS<T> const &rhs) const;
    bool equalsHelper(T const &first, ListCS<T> const &rest) const;
    T &first();
    T const &first() const;
    bool isEmpty() const;
    int length() const;
    T const &max() const;
    T const &maxHelper(T const &data) const;
    void prepend(ListCS<T> &owner, T const &data);
    T remFirst(ListCS<T> &owner);
    T remLast(ListCS<T> &owner);
    T remLastHelper(ListCS<T> &owner, ListCS<T> &previous);
    void remove(ListCS<T> &owner, T const &data);
    ListCS<T> &rest();
    ListCS<T> const &rest() const;
    void reverse(ListCS<T> &owner);
    void reverseHelper(ListCS<T> &owner, ListCS<T> &revList);
    void setList(ListCS<T> &owner, ListCS<T> &list);
    void toStream(ostream &os) const;
    void toStreamHelper(ostream &os) const;
    ListCS<T> *unZip();
    void zip(ListCS<T> &owner, ListCS<T> &other);
};

// ========= NEcsNode =========
template<class T>
class NEcsNode : public AcsNode<T> {
    friend class ListCS<T>;
    friend class MTcsNode<T>;

private:
    T _data;
    ListCS<T> _rest;

private:
    NEcsNode(T const &data);
    // Post: _data is data.

    NEcsNode(T data, AcsNode<T> *node);
    // Post: _data is data and _rest._head points to node.
    // _rest owns node and is responsible for garbage collection.

    NEcsNode(NEcsNode<T> const *rhs);
    // Post: _data is rhs->_data and _rest is rhs->_rest.

    NEcsNode &operator=(NEcsNode<T> const &rhs); // Disabled for node.

protected:
    void append(ListCS<T> &owner, T const &data) override;
    void clear(ListCS<T> &owner) override;
    void concat(ListCS<T> &owner, ListCS<T> &suffix) override;
    bool contains(T const &data) const override;
private:
    AcsNode<T> *copyHead() override;
protected:
    bool equals(ListCS<T> const &rhs) const override;
    bool equalsHelper(T const &first, ListCS<T> const &rest) const override;
    T &first() override;
    T const &first() const override;
    bool isEmpty() const override;
    int length() const override;
    T const &max() const override;
    T const &maxHelper(T const &data) const override;
    void prepend(ListCS<T> &owner, T const &data) override;
    T remFirst(ListCS<T> &owner) override;
    T remLast(ListCS<T> &owner) override;
    T remLastHelper(ListCS<T> &owner, ListCS<T> &previous) override;
    void remove(ListCS<T> &owner, T const &data) override;
    ListCS<T> &rest() override;
    ListCS<T> const &rest() const override;
    void reverse(ListCS<T> &owner) override;
    void reverseHelper(ListCS<T> &owner, ListCS<T> &revList) override;
    void setList(ListCS<T> &owner, ListCS<T> &list) override;
    void toStream(ostream &os) const override;
    void toStreamHelper(ostream &os) const override;
    ListCS<T> *unZip() override;
    void zip(ListCS<T> &owner, ListCS<T> &other) override;
};

// ========= Constructors =========
template<class T>
ListCS<T>::ListCS() :
    _head(new MTcsNode<T>()) {
}

template<class T>
ListCS<T>::ListCS(AcsNode<T> *node) :
    _head(node) {
}

template<class T>
NEcsNode<T>::NEcsNode(T const &data) :
    _data(data) {
}

template<class T>
NEcsNode<T>::NEcsNode(T data, AcsNode<T> *node) :
    _data(data) {
    _rest._head = node;
}

template<class T>
NEcsNode<T>::NEcsNode(NEcsNode<T> const *rhs) :
    _data(rhs->_data), _rest(rhs->_rest) {
}

// ========= Destructor =========
template<class T> // Recursively deletes this list.
ListCS<T>::~ListCS() {
    delete _head;
}

// ========= append =========
template<class T>
void ListCS<T>::append(T const &data) {
    _head->append(*this, data);
}

template<class T>
void MTcsNode<T>::append(ListCS<T> &owner, T const &data) {
    owner._head = new NEcsNode<T>(data, this);
}

template<class T>
void NEcsNode<T>::append(ListCS<T> &owner, T const &data) {
    _rest.append(data);
}

// ========= clear =========
template<class T>
void ListCS<T>::clear() {
    _head->clear(*this);
}

template<class T>
void MTcsNode<T>::clear(ListCS<T> &owner) {
}

template<class T>
void NEcsNode<T>::clear(ListCS<T> &owner) {
    _rest.clear();
    owner._head = new MTcsNode<T>();
    delete this;
}

// ========= concat =========
template<class T>
void ListCS<T>::concat(ListCS<T> &suffix) {
    cerr << "ListCS<T>::concat: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void MTcsNode<T>::concat(ListCS<T> &owner, ListCS<T> &suffix) {
    cerr << "MTcsNode<T>::concat: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::concat(ListCS<T> &owner, ListCS<T> &suffix) {
    cerr << "NEcsNode<T>::concat: Exercise for the student." << endl;
    throw -1;
}

// ========= contains =========
template<class T>
bool ListCS<T>::contains(T const &data) const {
    return _head->contains(data);
}

template<class T>
bool MTcsNode<T>::contains(T const &data) const {
    return false;
}

template<class T>
bool NEcsNode<T>::contains(T const &data) const {
    return data == _data ? true: _rest.contains(data);
}

// ========= copyHead =========
template<class T>
AcsNode<T> *ListCS<T>::copyHead(ListCS<T> const &rhs) {
    return _head->copyHead();
}

template<class T>
AcsNode<T> *MTcsNode<T>::copyHead() {
    return new MTcsNode<T>();
}

template<class T>
AcsNode<T> *NEcsNode<T>::copyHead() {
    return new NEcsNode<T>(_data, _rest._head->copyHead());
}

// ========= equals =========
template<class T>
bool ListCS<T>::equals(ListCS<T> const &rhs) const {
    return rhs._head->equals(rhs);
}

template<class T>
bool MTcsNode<T>::equals(ListCS<T> const &rhs) const {
    return rhs.isEmpty();
}

template<class T>
bool NEcsNode<T>::equals(ListCS<T> const &rhs) const {
    return rhs.equalsHelper(_data , _rest);
}

// --------- equalsHelper ---------
template<class T>
bool ListCS<T>::equalsHelper(T const &first, ListCS<T> const &rest) const {
    return _head->equalsHelper(first, rest);
}

template<class T>
bool MTcsNode<T>::equalsHelper(T const &first, ListCS<T> const &rest) const {
    return false;
}

template<class T>
bool NEcsNode<T>::equalsHelper(T const &first, ListCS<T> const &rest) const {

    return _data == first && rest.equals(_rest);

}

// ========= first =========
template<class T>
T &ListCS<T>::first() {
    return _head->first();
}

template<class T>
T &MTcsNode<T>::first() {
    cerr << "Precondition violated: No first in empty list" << endl;
    throw -1;
}

template<class T>
T &NEcsNode<T>::first() {
    return _data;
}

// ========= first const =========
template<class T>
T const &ListCS<T>::first() const {
    _head->first();
}

template<class T>
T const &MTcsNode<T>::first() const {
    cerr << "Precondition violated: No first in empty list" << endl;
    throw -1;
}

template<class T>
T const &NEcsNode<T>::first() const {
    return _data;
}

// ========= isEmpty =========
template<class T>
bool ListCS<T>::isEmpty() const {
    return _head->isEmpty();
}

template<class T>
bool MTcsNode<T>::isEmpty() const {
    return true;
}

template<class T>
bool NEcsNode<T>::isEmpty() const {
    return false;
}

// ========= length =========
template<class T>
int ListCS<T>::length() const {
    return _head->length();
}

template<class T>
int MTcsNode<T>::length() const {
    return 0;
}

template<class T>
int NEcsNode<T>::length() const {
    return 1 + _rest.length();
}

// ========= max =========
template<class T>
T const &ListCS<T>::max() const {
    return _head->max();
}

template<class T>
T const &MTcsNode<T>::max() const {
    cerr << "max precondition violated: An empty list has no maximum." << endl;
    throw -1;
}

template<class T>
T const &NEcsNode<T>::max() const {
    return _rest.maxHelper(_data);
}

// --------- maxHelper ---------
template<class T>
T const &ListCS<T>::maxHelper(T const &val) const {
    return _head->maxHelper(val);
}

template<class T>
T const &MTcsNode<T>::maxHelper(T const &val) const {
    return val;
}

template<class T>
T const &NEcsNode<T>::maxHelper(T const &val) const {
    return _data > val ? _rest.maxHelper(_data) : _rest.maxHelper(val);
}

// ========= operator= =========
template<class T>
ListCS<T> &ListCS<T>::operator=(const ListCS &rhs) {
    if (this != &rhs) { // In case someone writes myList = myList;
        delete _head;
        _head = copyHead(rhs);
    }
    return *this;
}

// ========= operator== =========
template<class T>
bool operator==(ListCS<T> const &lhs, ListCS<T> const &rhs) {
    return lhs.equals(rhs);
}

// ========= operator<< =========
template<class T>
ostream &operator<<(ostream &os, ListCS<T> const &rhs) {
    rhs.toStream(os);
    return os;
}

// ========= prepend =========
template<class T>
void ListCS<T>::prepend(T const &data) {
    _head->prepend(*this, data);
}

template<class T>
void MTcsNode<T>::prepend(ListCS<T> &owner, T const &data) {
    // Assert: owner._head is this MTcsNode
    // No memory leak as the constructor does not allocate a node.
    owner._head = new NEcsNode<T>(data, this);
}

template<class T>
void NEcsNode<T>::prepend(ListCS<T> &owner, T const &data) {
    owner._head = new NEcsNode<T>(data, this);
}

// ========= remFirst =========
template<class T>
T ListCS<T>::remFirst() {
    return _head->remFirst(*this);

}

template<class T>
T MTcsNode<T>::remFirst(ListCS<T> &owner) {
    cerr << "max precondition violated: An empty list has no first value." << endl;
    throw -1;
}

template<class T>
T NEcsNode<T>::remFirst(ListCS<T> &owner) {
    T result = _data;
    owner._head = _rest._head;
    _rest._head = nullptr;
    delete this;
    return result;
}

// ========= remLast =========
template<class T>
T ListCS<T>::remLast() {
    return _head->remLast(*this);
}

template<class T>
T MTcsNode<T>::remLast(ListCS<T> &owner) {
    cerr << "max precondition violated: An empty list has no last value." << endl;
    throw -1;
}

template<class T>
T NEcsNode<T>::remLast(ListCS<T> &owner) {

    return _rest.remLastHelper(owner);
}

// --------- remLastHelper ---------
template<class T>
T ListCS<T>::remLastHelper(ListCS<T> &previous) {
    return _head->remLastHelper(*this,previous);
}

template<class T>
T MTcsNode<T>::remLastHelper(ListCS<T> &owner, ListCS<T> &previous) {
    return previous.remFirst();
}

template<class T>
T NEcsNode<T>::remLastHelper(ListCS<T> &owner, ListCS<T> &previous) {
    return _rest.remLastHelper(owner);
}

// ========= remove =========
template<class T>
void ListCS<T>::remove(T const &data) {
    if (!isEmpty()) {
        _head->remove(*this, data);
    }
}

template<class T>
void MTcsNode<T>::remove(ListCS<T> &owner, T const &data) {
}

template<class T>
void NEcsNode<T>::remove(ListCS<T> &owner, T const &data) {
    if(data == _data){
        owner.remFirst();
    }
    else{
        _rest.remove(data);
    }
}

// ========= rest =========
template<class T>
ListCS<T> &ListCS<T>::rest() {
    return _head->rest();
}

template<class T>
ListCS<T> &MTcsNode<T>::rest() {
    cerr << "rest precondition violated: An empty list has no rest." << endl;
    throw -1;
}

template<class T>
ListCS<T> &NEcsNode<T>::rest() {
    return _rest;
}

// ========= rest const=========
template<class T>
ListCS<T> const &ListCS<T>::rest() const {
    return _head->rest();
}

template<class T>
ListCS<T> const &MTcsNode<T>::rest() const {
    cerr << "rest precondition violated: An empty list has no rest." << endl;
    throw -1;
}

template<class T>
ListCS<T> const &NEcsNode<T>::rest() const {
    return _rest;
}

// ========= reverse =========
template<class T>
void ListCS<T>::reverse() {
    _head->reverse(*this);
}

template<class T>
void MTcsNode<T>::reverse(ListCS<T> &owner) {
    cerr << "precondition violated: An empty list cannot be reversed." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::reverse(ListCS<T> &owner) {
    ListCS<T> revList;
    owner.reverseHelper(revList);
    owner.setList(revList);
}

// --------- reverseHelper ---------
template<class T>
void ListCS<T>::reverseHelper(ListCS<T> &revList) {
    _head->reverseHelper(*this, revList);
}

template<class T>
void MTcsNode<T>::reverseHelper(ListCS<T> &owner, ListCS<T> &revList) {

}

template<class T>
void NEcsNode<T>::reverseHelper(ListCS<T> &owner, ListCS<T> &revList) {
    revList.prepend(owner.remFirst());
    owner.reverseHelper(revList);
}

// ========= setList =========
template<class T>
void ListCS<T>::setList(ListCS<T> &list) {
    _head->setList(*this, list);
}

template<class T>
void MTcsNode<T>::setList(ListCS<T> &owner, ListCS<T> &list) {
    delete owner._head;
    owner._head = list._head;
    list._head = new MTcsNode<T>();
}

template<class T>
void NEcsNode<T>::setList(ListCS<T> &owner, ListCS<T> &list) {
    delete owner._head;
    owner._head = list._head;
    list._head = new MTcsNode<T>();
}

// ========= toStream =========
template<class T>
void ListCS<T>::toStream(ostream &os) const {
    _head->toStream(os);
}

template<class T>
void MTcsNode<T>::toStream(ostream &os) const {
    os << "()";
}

template<class T>
void NEcsNode<T>::toStream(ostream &os) const {
    os << "(" << _data;
    _rest._head->toStreamHelper(os);
}

// --------- toStreamHelper ---------
template<class T>
void MTcsNode<T>::toStreamHelper(ostream &os) const {
    os << ")";
}

template<class T>
void NEcsNode<T>::toStreamHelper(ostream &os) const {
    os << ", " << _data;
    _rest._head->toStreamHelper(os);
}

// ========= unZip =========
template<class T>
ListCS<T> *ListCS<T>::unZip() {
    cerr << "ListCS<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

template<class T>
ListCS<T> *MTcsNode<T>::unZip() {
    cerr << "MTcsNode<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

template<class T>
ListCS<T> *NEcsNode<T>::unZip() {
    cerr << "NEcsNode<T>::unZip: Exercise for the student." << endl;
    throw -1;
}

// ========= zip =========
template<class T>
void ListCS<T>::zip(ListCS<T> &other) {
    cerr << "ListCS<T>::zip: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void MTcsNode<T>::zip(ListCS<T> &owner, ListCS<T> &other) {
    cerr << "MTcsNode<T>::zip(ListCS: Exercise for the student." << endl;
    throw -1;
}

template<class T>
void NEcsNode<T>::zip(ListCS<T> &owner, ListCS<T> &other) {
    cerr << "NEcsNode<T>::zip: Exercise for the student." << endl;
    throw -1;
}

#endif
