// File: ListCV/LCVmaxVis.hpp

#ifndef LCVmaxVis_hpp
#define LCVmaxVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVmaxVis : public AListCVVis<T> {
    // Pre: This list is not empty.
    // Post: The maximum element of this list is returned.
private:
    T _result; // Output result.

private:
    LCVmaxVis(const LCVmaxVis &rhs); // Disabled.
    LCVmaxVis &operator=(const LCVmaxVis &rhs); // Disabled.

public:
    LCVmaxVis();
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    T result() const;
};

// ========= Constructor =========
template<class T>
LCVmaxVis<T>::LCVmaxVis() {
}

// ========= visit =========
template<class T>
void LCVmaxVis<T>::visitMTList(const MTListCV<T> &) {
    assert(false);
}

// Zung, I tried this with a max helper, but could not figure out how to polymorphically dispatch a vistor
template<class T>
void LCVmaxVis<T>::visitNEList(const NEListCV<T> &host) {
    LCVisEmptyVis<T> isEmptyVis;
    host.rest()->accept(isEmptyVis);
    if (isEmptyVis.result()) {
        _result = host.first();
    }
    else {
        host.rest()->accept(*this);
        _result = host.first() <= result() ? result() : host.first();
    }
}

/* Logic
   template<class T>
   T MTListCT<T>::max() const {
   assert(false);
   T junk; return junk; // Dead code, compiler requirement
   }

   template<class T>
   T NEListCT<T>::max() const {
   return _rest->maxHelper(_first);
   }

   template<class T>
   T MTListCT<T>::maxHelper(T m) const {
   return m;
   }

   template<class T>
   T NEListCT<T>::maxHelper(T m) const {
   return _first <= m ? _rest->maxHelper(m) : _rest->maxHelper(_first);
   }
*/

// ========= result =========
template<class T>
T LCVmaxVis<T>::result() const {
    return _result;
}

#endif
