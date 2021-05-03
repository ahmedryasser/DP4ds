// File: ListCV/LCVappendVis.hpp

#ifndef LCVappendVis_hpp
#define LCVappendVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVappendVis : public AListCVVis<T> {
private:
    T _val; // Input parameter.
    AListCV<T> *_result; // Output result.

private:
    LCVappendVis(LCVappendVis const &rhs); // disabled.
    LCVappendVis &operator=(LCVappendVis const &rhs); // disabled.

public:
    LCVappendVis(T val);
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
    AListCV<T> *result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list with val appended is returned.
};

// ========= Constructor =========
template<class T>
LCVappendVis<T>::LCVappendVis(T val):
    _val(val),
    _result(nullptr) {
    }

// ========= visit =========
template<class T>
void LCVappendVis<T>::visitMTList(MTListCV<T> const &host) {
    _result = new NEListCV<T>(_val, &host);
}

template<class T>
void LCVappendVis<T>::visitNEList(NEListCV<T> const &host) {
    host.rest()->accept(*this);
    // _result = new NEListCT<T>(nel->first(), _result); would be a memory leak.
    AListCV<T> *temp = _result;
    _result = new NEListCV<T>(host.first(), temp);
    delete temp;
}

// ========= result =========
template<class T>
AListCV<T> *LCVappendVis<T>::result() const {
    return _result;
}

#endif
