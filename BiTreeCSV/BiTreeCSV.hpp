// File: BiTreeCSV/BiTreeCSV.hpp

#ifndef BITREECSV_HPP_
#define BITREECSV_HPP_

#include <iostream> // ostream.
#include "ABiTreeCSVVis.hpp"
#include "BiTCSVisEmptyVis.hpp" // For remRoot.
using namespace std;

template<class T> class AcsvNode; // Forward declaration.
template<class T> class MTcsvNode; // Forward declaration.
template<class T> class NEcsvNode; // Forward declaration.

// ========= BiTreeCSV =========
template<class T>
class BiTreeCSV {
    friend class MTcsvNode<T>;
    friend class NEcsvNode<T>;

private:
    AcsvNode<T> *_root;

private:
    BiTreeCSV(BiTreeCSV<T> const &rhs);
    // Copy constructor disabled.

    BiTreeCSV(AcsvNode<T> *node);
    // Pre: node != nullptr.
    // Post: _root points to node with no allocation.

public:
    BiTreeCSV();
    // Post: This tree is initialized to be empty.

    ~BiTreeCSV();
    // Post: This tree is deallocated.

public:
    void accept(ABiTreeCSVVis<T> &visitor);
    void accept(ABiTreeCSVVis<T> &visitor) const;

private:
    AcsvNode<T> *copyRoot(BiTreeCSV<T> const &rhs);
    // Post: A deep copy of the root of rhs is returned.

public:
    void insertRoot(T const &data);
    // Pre: This tree is empty.
    // Post: This tree has one root node containing data.

    BiTreeCSV<T> &left();
    BiTreeCSV<T> const &left() const;
    // Pre: This tree is not empty.
    // Post: A reference to the left child of this tree is returned.

    BiTreeCSV &operator=(BiTreeCSV const &rhs);
    // Post: A deep copy of rhs is returned with garbage collection.

    T remRoot();
    // Pre: This tree is not empty.
    // Pre: The root of this tree has at least one empty child.
    // Post: The root node is removed from this tree and its element is returned.

    BiTreeCSV<T> &right();
    BiTreeCSV<T> const &right() const;
    // Pre: This tree is not empty.
    // Post: A reference to the left child of this tree is returned.

    T &root();
    T const &root() const;
    // Pre: This tree is not empty.
    // Post: A reference to the root element of this tree is returned.

    void setTree(BiTreeCSV<T> &tree);
    // Post: This tree is deallocated and set to tree.
    // tree is the empty tree (cut setTree, as opposed to copy setTree).
};

// ========= AcsvNode =========
template<class T>
class AcsvNode {
    friend class BiTreeCSV<T>;
    friend class MTcsvNode<T>;
    friend class NEcsvNode<T>;

public:
    virtual ~AcsvNode();

protected:
    virtual void accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) = 0;
    virtual void accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) = 0;
private:
    virtual AcsvNode *copyRoot() = 0;
    // Post: A deep copy of this node is returned.
protected:
    virtual void insertRoot(BiTreeCSV<T> &owner, T const &data) = 0;
    virtual BiTreeCSV<T> &left() = 0;
    virtual BiTreeCSV<T> const &left() const = 0;
    virtual T remRoot(BiTreeCSV<T> &owner) = 0;
    virtual BiTreeCSV<T> &right() = 0;
    virtual BiTreeCSV<T> const &right() const = 0;
    virtual T &root() = 0;
    virtual T const &root() const = 0;
    virtual void setTree(BiTreeCSV<T> &owner, BiTreeCSV<T> &tree) = 0;
};

// ========= MTcsvNode =========
template<class T>
class MTcsvNode : public AcsvNode<T> {
    friend class BiTreeCSV<T>;
    friend class NEcsvNode<T>;

private:
    MTcsvNode();
    MTcsvNode(MTcsvNode<T> const &rhs); // Disabled.
    MTcsvNode &operator=(MTcsvNode const &rhs); // Disabled.

protected:
    void accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) override;
    void accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) override;
private:
    AcsvNode<T> *copyRoot() override;
protected:
    void insertRoot(BiTreeCSV<T> &owner, T const &data) override;
    BiTreeCSV<T> &left() override;
    BiTreeCSV<T> const &left() const override;
    T remRoot(BiTreeCSV<T> &owner) override;
    BiTreeCSV<T> &right() override;
    BiTreeCSV<T> const &right() const override;
    T &root() override;
    T const &root() const override;
    void setTree(BiTreeCSV<T> &owner, BiTreeCSV<T> &tree) override;
};

// ========= NEcsvNode =========
template<class T>
class NEcsvNode : public AcsvNode<T> {
    friend class BiTreeCSV<T>;
    friend class MTcsvNode<T>;

private:
    BiTreeCSV<T> _left;
    T _data;
    BiTreeCSV<T> _right;

private:
    NEcsvNode(T const &data);
    // Post: _data is data.

    NEcsvNode(AcsvNode<T> *leftNode, T data, AcsvNode<T> *rightNode);
    // Post: _data is data, _left._root points to leftNode,
    // and _right._root points to rightNode.
    // _left and _right own their nodes and are responsible for garbage collection.

    NEcsvNode(NEcsvNode<T> const *rhs);
    // Post: _data is rhs->_data, _left is rhs->_left, and _right is rhs->_right.

    NEcsvNode &operator=(NEcsvNode const &rhs); // Disabled.

protected:
    void accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) override;
    void accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) override;
private:
    AcsvNode<T> *copyRoot() override;
protected:
    void insertRoot(BiTreeCSV<T> &owner, T const &data) override;
    BiTreeCSV<T> &left() override;
    BiTreeCSV<T> const &left() const override;
    T remRoot(BiTreeCSV<T> &owner) override;
    BiTreeCSV<T> &right() override;
    BiTreeCSV<T> const &right() const override;
    T &root() override;
    T const &root() const override;
    void setTree(BiTreeCSV<T> &owner, BiTreeCSV<T> &tree) override;
};

// ========= Constructors =========
template<class T>
BiTreeCSV<T>::BiTreeCSV():
    _root(new MTcsvNode<T>()) {
}

template<class T>
BiTreeCSV<T>::BiTreeCSV(AcsvNode<T> *node):
    _root(node) {
}

template<class T>
MTcsvNode<T>::MTcsvNode() {
}

template<class T>
NEcsvNode<T>::NEcsvNode(T const &data):
    _data(data) {
}

template<class T>
NEcsvNode<T>::NEcsvNode(AcsvNode<T> *leftNode, T data, AcsvNode<T> *rightNode):
    _data(data) {
    _left._root = leftNode;
    _right._root = rightNode;
}

template<class T>
NEcsvNode<T>::NEcsvNode(NEcsvNode<T> const *rhs):
    _left(rhs->_left),
    _data(rhs->_data),
    _right(rhs->_right) {
}

// ========= Destructors =========
template<class T>
BiTreeCSV<T>::~BiTreeCSV() {
    delete _root;
}

template<class T>
AcsvNode<T>::~AcsvNode() {
}

// ========= accept =========
template<class T>
void BiTreeCSV<T>::accept(ABiTreeCSVVis<T> &visitor) {
    _root->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(BiTreeCSV<T> &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= accept const =========
template<class T>
void BiTreeCSV<T>::accept(ABiTreeCSVVis<T> &visitor) const {
    _root->accept(*this, visitor);
}

template<class T>
void MTcsvNode<T>::accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.emptyCase(owner);
}

template<class T>
void NEcsvNode<T>::accept(BiTreeCSV<T> const &owner, ABiTreeCSVVis<T> &visitor) {
    visitor.nonEmptyCase(owner);
}

// ========= copyRoot =========
template<class T>
AcsvNode<T> *BiTreeCSV<T>::copyRoot(BiTreeCSV<T> const &rhs) {
    return rhs._root->copyRoot();
}

template<class T>
AcsvNode<T> *MTcsvNode<T>::copyRoot() {
    return new MTcsvNode<T>();
}

template<class T>
AcsvNode<T> *NEcsvNode<T>::copyRoot() {
    return new NEcsvNode<T>(_left._root->copyRoot(), _data, _right._root->copyRoot());
}

// ========= insertRoot =========
template<class T>
void BiTreeCSV<T>::insertRoot(T const &data) {
    _root->insertRoot(*this, data);
}

template<class T>
void MTcsvNode<T>::insertRoot(BiTreeCSV<T> &owner, T const &data) {
    owner._root = new NEcsvNode<T>(data);
    delete this;
}

template<class T>
void NEcsvNode<T>::insertRoot(BiTreeCSV<T> &owner, T const &data) {
    cerr << "insertRoot precondition violated: "
         << "Cannot insert root into a non empty tree" << endl;
    throw -1;
}

// ========= left =========
template<class T>
BiTreeCSV<T> &BiTreeCSV<T>::left()  {
    return _root->left();
}

template<class T>
BiTreeCSV<T> &MTcsvNode<T>::left() {
    cerr << "left precondition violated: "
         << "An empty tree has no left subtree." << endl;
    throw -1;
}

template<class T>
BiTreeCSV<T> &NEcsvNode<T>::left() {
    return _left;
}

// ========= left const =========
template<class T>
BiTreeCSV<T> const &BiTreeCSV<T>::left() const {
    return _root->left();
}

template<class T>
BiTreeCSV<T> const &MTcsvNode<T>::left() const {
    cerr << "left precondition violated: "
         << "An empty tree has no left subtree." << endl;
    throw -1;
}

template<class T>
BiTreeCSV<T> const &NEcsvNode<T>::left() const {
    return _left;
}

// ========= operator= =========
template<class T>
BiTreeCSV<T> &BiTreeCSV<T>::operator=(BiTreeCSV const &rhs) {
    if (this != &rhs) { // In case someone writes myTree = myTree;
        delete _root;
        _root = copyRoot(rhs);
    }
    return *this;
}

// ========= remRoot =========
template<class T>
T BiTreeCSV<T>::remRoot() {
    return _root->remRoot(*this);
}

template<class T>
T MTcsvNode<T>::remRoot(BiTreeCSV<T> &owner) {
    cerr << "remRoot precondition violated: "
         << "Cannot remove root from an empty tree." << endl;
    throw -1;
}

template<class T>
T NEcsvNode<T>::remRoot(BiTreeCSV<T> &owner) {
    T temp = _data;
    if ( isEmpty(_left)){
        owner._root = _right._root;
        _right._root = nullptr;
        delete this;
        return temp;
    }
    else if (isEmpty(_right)){
        owner._root = _left._root;
        _left._root = nullptr;
        delete this;
        return temp;
    }
    else{
        cerr << "remRoot precondition violated: Cannot remove from an full tree." << endl;
        throw -1;
    }
}

// ========= right =========
template<class T>
BiTreeCSV<T> &BiTreeCSV<T>::right() {
    return _root->right();
}

template<class T>
BiTreeCSV<T> &MTcsvNode<T>::right() {
    cerr << "right precondition violated: "
         << "An empty tree has no right subtree." << endl;
    throw -1;
}

template<class T>
BiTreeCSV<T> &NEcsvNode<T>::right() {
    return _right;
}

// ========= right const =========
template<class T>
BiTreeCSV<T> const &BiTreeCSV<T>::right() const {
    return _root->right();
}

template<class T>
BiTreeCSV<T> const &MTcsvNode<T>::right() const {
    cerr << "right precondition violated: "
         << "An empty tree has no right subtree." << endl;
    throw -1;
}

template<class T>
BiTreeCSV<T> const &NEcsvNode<T>::right() const {
    return _right;
}

// ========= root =========
template<class T>
T &BiTreeCSV<T>::root() {
    return _root->root();
}

template<class T>
T &MTcsvNode<T>::root() {
    cerr << "precondition violated: An empty tree has no root." << endl;
    throw -1;
}

template<class T>
T &NEcsvNode<T>::root() {
    return _data;
}

// ========= root const =========
template<class T>
T const &BiTreeCSV<T>::root() const {
    return _root->root();
}

template<class T>
T const &MTcsvNode<T>::root() const {
    cerr << "precondition violated: An empty tree has no root." << endl;
    throw -1;
}

template<class T>
T const &NEcsvNode<T>::root() const {
    return _data;
}

// ========= setTree =========
template<class T>
void BiTreeCSV<T>::setTree(BiTreeCSV<T> &tree) {
    _root->setTree(*this, tree);
}

template<class T>
void MTcsvNode<T>::setTree(BiTreeCSV<T> &owner, BiTreeCSV<T> &tree) {
    delete owner._root;
    owner._root = tree._root;
    tree._root = new MTcsvNode<T>();
}

template<class T>
void NEcsvNode<T>::setTree(BiTreeCSV<T> &owner, BiTreeCSV<T> &tree) {
    delete owner._root;
    owner._root = tree._root;
    tree._root = new MTcsvNode<T>();
}

#endif
