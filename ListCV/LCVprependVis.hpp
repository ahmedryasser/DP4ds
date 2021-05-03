// File: ListCV/LCVprependVis.hpp

#ifndef LCVprependVis_hpp
#define LCVprependVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVprependVis : public AListCVVis<T> {
private:
    T _val; // Input parameter.
    AListCV<T> *_result; // Output result.

private:
    LCVprependVis(const LCVprependVis &rhs); // disabled.
    LCVprependVis &operator=(const LCVprependVis &rhs); // disabled.

public:
    LCVprependVis(T val);
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    AListCV<T> *result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list with val prepended is returned.
};

// ========= Constructor =========

template<class T>
LCVprependVis<T>::LCVprependVis(T val) :
    _val(val),
    _result(nullptr) {
    }

// ========= visit =========

template<class T>
void LCVprependVis<T>::visitMTList(const MTListCV<T> &host) {
    _result = new NEListCV<T > (_val, &host);
}

template<class T>
void LCVprependVis<T>::visitNEList(const NEListCV<T> &host) {
    _result = new NEListCV<T > (_val, &host);
}

// ========= result =========

template<class T>
AListCV<T> *LCVprependVis<T>::result() const {
    return _result;
}

#endif
