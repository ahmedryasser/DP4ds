// File: ListCV/LCVfirstVis.hpp

#ifndef LCVfirstVis_hpp
#define LCVfirstVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVfirstVis : public AListCVVis<T> {
    // Pre: This list is not empty.
    // Post: The firstimum element of this list is returned.
private:
    T _result; // Output result.

private:
    LCVfirstVis(const LCVfirstVis &rhs); // Disabled.
    LCVfirstVis &operator=(const LCVfirstVis &rhs); // Disabled.

public:
    LCVfirstVis();
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    T result() const;
};

// ========= Constructor =========
template<class T>
LCVfirstVis<T>::LCVfirstVis() {
}

// ========= visit =========
template<class T>
void LCVfirstVis<T>::visitMTList(const MTListCV<T> &) {
    assert(false);
}

template<class T>
void LCVfirstVis<T>::visitNEList(const NEListCV<T> &host) {
    _result = host.first();
}

// ========= result =========
template<class T>
T LCVfirstVis<T>::result() const {
    return _result;
}

#endif
