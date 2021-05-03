// File: ListCV/LCVcloneVis.hpp

#ifndef LCVcloneVis_hpp
#define LCVcloneVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVcloneVis : public AListCVVis<T> {
private:
    AListCV<T> *_result; // Output result.

private:
    LCVcloneVis(LCVcloneVis const &rhs); // disabled.
    LCVcloneVis &operator=(LCVcloneVis const &rhs); // disabled.

public:
    LCVcloneVis();
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
    AListCV<T> *result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list is returned.
    // The caller of result() is responsible for garbage collection.
};

// ========= Constructor =========
template<class T>
LCVcloneVis<T>::LCVcloneVis():
    _result(nullptr) {
}

// ========= visit =========
template<class T>
void LCVcloneVis<T>::visitMTList(MTListCV<T> const &) {
    _result = new MTListCV<T>();
}

template<class T>
void LCVcloneVis<T>::visitNEList(NEListCV<T> const &host) {
    host.rest()->accept(*this);
    _result = new NEListCV<T>(host.first(), _result);
    // _result = new NEListCV<T>(host.first(), host.rest());
}

// ========= result =========
template<class T>
AListCV<T> *LCVcloneVis<T>::result() const {
    return _result;
}

#endif
