// File: ListCV/LCVlengthVis.hpp

#ifndef LCVlengthVis_hpp
#define LCVlengthVis_hpp

#include <iostream>
#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVlengthVis : public AListCVVis<T> {
private:
    int _result; // Output result.

private:
    LCVlengthVis(const LCVlengthVis &rhs); // Disabled.
    LCVlengthVis &operator=(const LCVlengthVis &rhs); // Disabled.

public:
    LCVlengthVis();
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    int result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: The length of the host list is returned.
};

// ========= Constructor =========
template<class T>
LCVlengthVis<T>::LCVlengthVis() {
}

// ========= visit =========
template<class T>
void LCVlengthVis<T>::visitMTList(const MTListCV<T> &) {
    _result = 0;
}

template<class T>
void LCVlengthVis<T>::visitNEList(const NEListCV<T> &host) {
    host.rest()->accept(*this);
    _result = 1 + _result;
}

// ========= result =========
template<class T>
int LCVlengthVis<T>::result() const {
    return _result;
}

#endif
