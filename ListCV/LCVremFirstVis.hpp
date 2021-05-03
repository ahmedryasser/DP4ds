// File: ListCV/LCVremFirstVis.hpp

#ifndef LCVremFirstVis_hpp
#define LCVremFirstVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
#include "LCVcloneVis.hpp" // Using another plugin.
using namespace std;

template<class T>
class LCVremFirstVis : public AListCVVis<T> {
    // Post: A pointer to a copy of this list with with the first element removed
    // is returned. An empty list is returned if this list is empty.
private:
    AListCV<T> *_result; // Output result.

private:
    LCVremFirstVis(const LCVremFirstVis &rhs); // Disabled.
    LCVremFirstVis &operator=(const LCVremFirstVis &rhs); // Disabled.

public:
    LCVremFirstVis();
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    AListCV<T> *result() const;
};

// ========= Constructor =========
template<class T>
LCVremFirstVis<T>::LCVremFirstVis():
    _result(nullptr) {
}

// ========= visit =========
template<class T>
void LCVremFirstVis<T>::visitMTList(const MTListCV<T> &) {
    // Zung, Should I use clone here? If so, why?
    _result = new MTListCV<T>();
}

template<class T>
void LCVremFirstVis<T>::visitNEList(const NEListCV<T> &host) {
    LCVcloneVis<T> cloneVis;
    host.rest()->accept(cloneVis);
    _result = cloneVis.result();
}

// ========= result =========
template<class T>
AListCV<T> *LCVremFirstVis<T>::result() const {
    return _result;
}

#endif
