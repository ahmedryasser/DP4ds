// File: ListCV/LCVreverseVis.hpp

#ifndef LCVreverseVis_hpp
#define LCVreverseVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
#include "LCVappendVis.hpp" // Using another plugin.
using namespace std;

// ========= reverse helper =========
template<class T>
class LCVreverseVisHelper : public AListCVVis<T> {
private:
    AListCV<T> *_accumReverse; // Output result.
    AListCV<T> *_result; // Output result.

private:
    LCVreverseVisHelper(const LCVreverseVisHelper &rhs); // Disabled.
    LCVreverseVisHelper &operator=(const LCVreverseVisHelper &rhs); // Disabled.

public:
    LCVreverseVisHelper(AListCV<T> *accumReverse);
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    AListCV<T> *result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list reversed is returned.
};

// ========= Constructor =========
template<class T>
LCVreverseVisHelper<T>::LCVreverseVisHelper(AListCV<T> *accumReverse):
    _accumReverse(accumReverse),
    _result(nullptr) {
    }

// ========= visit =========
template<class T>
void LCVreverseVisHelper<T>::visitMTList(const MTListCV<T> &) {
    _result = _accumReverse;
}

template<class T>
void LCVreverseVisHelper<T>::visitNEList(const NEListCV<T> &host) {
    AListCV<T> *temp = _accumReverse;
    _accumReverse = new NEListCV<T>(host.first(), temp);
    delete temp;
    host.rest()->accept(*this);
}

// ========= result =========
template<class T>
AListCV<T> *LCVreverseVisHelper<T>::result() const {
    return _result;
}

// ========= reverse master =========
template<class T>
class LCVreverseVis : public AListCVVis<T> {
private:
    AListCV<T> *_result; // Output result.

private:
    LCVreverseVis(const LCVreverseVis &rhs); // disabled.
    LCVreverseVis &operator=(const LCVreverseVis &rhs); // disabled.

public:
    LCVreverseVis();
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    AListCV<T> *result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: A pointer to a copy of the host list reversed is returned.
};

// ========= Constructor =========
template<class T>
LCVreverseVis<T>::LCVreverseVis():
    _result(nullptr) {
}

// ========= visit =========
template<class T>
void LCVreverseVis<T>::visitMTList(const MTListCV<T> &) {
    _result = new MTListCV<T>();
}

template<class T>
void LCVreverseVis<T>::visitNEList(const NEListCV<T> &host) {
    LCVreverseVisHelper<T> reverseHelperVis(new NEListCV<T>(host.first()));
    host.rest()->accept(reverseHelperVis);
    _result = reverseHelperVis.result();
}

// ========= result =========
template<class T>
AListCV<T> *LCVreverseVis<T>::result() const {
    return _result;
}

#endif
