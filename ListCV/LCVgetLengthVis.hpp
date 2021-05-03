// File: ListCV/LCVgetLength.hpp

#ifndef LCVgetLength_hpp
#define LCVgetLength_hpp

#include <iostream>
#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

/**
 * Calls a helper that accumulates the length of the list,
 * as it traverses down the list.
 */
template<class T>
class LCVgetLength : public AListCVVis<T> {
private:
    int _result;

public:
    LCVgetLength();
    void visitMTList(const MTListCV<T> &mtl) override;
    void visitNEList(const NEListCV<T> &nel) override;
    int result() const;
};

/**
 * Helper class doing forward accumulation.
 */
template<class T>
class LCVgetLengthHelp : public AListCVVis<T> {
private:
    int _result;
    int _acc;

public:
    LCVgetLengthHelp(int acc);
    void visitMTList(const MTListCV<T> &mtl) override;
    void visitNEList(const NEListCV<T> &nel) override;
    int result() const;
};

template<class T>
LCVgetLength<T>::LCVgetLength() : _result(-1) {
}

template<class T>
LCVgetLengthHelp<T>::LCVgetLengthHelp(int acc) : _result(-1), _acc(acc) {
}

template<class T>
void LCVgetLength<T>::visitMTList(const MTListCV<T> &mtl) {
    _result = 0;
}

template<class T>
void LCVgetLengthHelp<T>::visitMTList(const MTListCV<T> &mtl) {
    _result = _acc;
}

template<class T>
void LCVgetLength<T>::visitNEList(const NEListCV<T> &nel) {
    LCVgetLengthHelp<T> glh(1);
    nel.rest()->accept(&glh);
    _result = glh.result();
}

template<class T>
void LCVgetLengthHelp<T>::visitNEList(const NEListCV<T> &nel) {
    ++_acc;
    nel.rest()->accept(this);
    _result = result();
}

template<class T>
int LCVgetLength<T>::result() const {
    return _result;
}

template<class T>
int LCVgetLengthHelp<T>::result() const {
    return _result;
}

#endif
