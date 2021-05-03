// File: ListCV/LCVconcatVis.hpp

#ifndef LCVconcatVis_hpp
#define LCVconcatVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVconcatVis : public AListCVVis<T> {
private:
    AListCV<T> const *_suffix; // Input parameter.
    AListCV<T> *_result; // Output result.

private:
    LCVconcatVis(LCVconcatVis const &rhs); // disabled.
    LCVconcatVis &operator=(LCVconcatVis const &rhs); // disabled.

public:
    LCVconcatVis(AListCV<T> const *suffix);
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
    AListCV<T> *result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list with suffix appended is returned.
};

// ========= Constructor =========
template<class T>
LCVconcatVis<T>::LCVconcatVis(AListCV<T> const *suffix):
    _suffix(suffix),
    _result(nullptr) {
    }

// ========= visit =========
template<class T>
void LCVconcatVis<T>::visitMTList(MTListCV<T> const &) {
    LCVcloneVis<T> cloneVis;
    _suffix->accept(cloneVis);
    _result = cloneVis.result();
}

template<class T>
void LCVconcatVis<T>::visitNEList(NEListCV<T> const &host) {
    host.rest()->accept(*this);
    // _result = new NEListCT<T>(nel->first(), _result); would be a memory leak.
    AListCV<T> *temp = _result;
    _result = new NEListCV<T>(host.first(), temp);
    delete temp;
}

// ========= result =========
template<class T>
AListCV<T> *LCVconcatVis<T>::result() const {
    return _result;
}

#endif
