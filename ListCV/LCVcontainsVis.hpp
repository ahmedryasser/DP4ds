// File: ListCV/LCVcontainsVis.hpp

#ifndef LCVcontainsVis_hpp
#define LCVcontainsVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVcontainsVis : public AListCVVis<T> {
private:
    T _val; // Input parameter.
    bool _result; // Output result.

private:
    LCVcontainsVis(LCVcontainsVis const &rhs); // Disabled.
    LCVcontainsVis & operator=(LCVcontainsVis const &rhs); // Disabled.

public:
    LCVcontainsVis(T val);
    void visitMTList(MTListCV<T> const &host) override;
    void visitNEList(NEListCV<T> const &host) override;
    bool result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if val is contained in this list; Otherwise, false is returned.
};

// ========= Constructor =========

template<class T>
LCVcontainsVis<T>::LCVcontainsVis(T val) :
    _val(val) {
}

// ========= visit =========

template<class T>
void LCVcontainsVis<T>::visitMTList(MTListCV<T> const &) {
    _result = false;
}

template<class T>
void LCVcontainsVis<T>::visitNEList(NEListCV<T> const &host) {
    if (_val == host.first()) {
        _result = true;
    } else {
        LCVcontainsVis<T> containsVis(_val);
        host.rest()->accept(containsVis);
        _result = containsVis.result();
    }
}

// ========= result =========

template<class T>
bool LCVcontainsVis<T>::result() const {
    return _result;
}

#endif
