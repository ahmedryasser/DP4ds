// File: ListCV/LCVisEmptyVis.hpp

#ifndef LCVisEmptyVis_hpp
#define LCVisEmptyVis_hpp

#include "AListCVVis.hpp"
#include "ListCV.hpp"
using namespace std;

template<class T>
class LCVisEmptyVis : public AListCVVis<T> {
private:
    bool _result; // Output result.

private:
    LCVisEmptyVis(const LCVisEmptyVis &rhs); // disabled.
    LCVisEmptyVis &operator=(const LCVisEmptyVis &rhs); // disabled.

public:
    LCVisEmptyVis();
    void visitMTList(const MTListCV<T> &host) override;
    void visitNEList(const NEListCV<T> &host) override;
    bool result() const;
    // Pre: This visitor has been accepted by a host list.
    // Post: true is returned if the host list is empty; Otherwise, false is returned.
};

// ========= Constructor =========
template<class T>
LCVisEmptyVis<T>::LCVisEmptyVis() {
}

// ========= visit =========
template<class T>
void LCVisEmptyVis<T>::visitMTList(const MTListCV<T> &) {
    _result = true;
}

template<class T>
void LCVisEmptyVis<T>::visitNEList(const NEListCV<T> &) {
    _result = false;
}

// ========= result =========
template<class T>
bool LCVisEmptyVis<T>::result() const {
    return _result;
}

#endif
