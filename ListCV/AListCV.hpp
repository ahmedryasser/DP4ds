// File: ListCV/AListCV.hpp

#ifndef AListCV_hpp
#define AListCV_hpp

#include <iostream> // ostream.
using namespace std;

template<class T> class AListCVVis; // Forward declaration.

template<class T>
class AListCV {
public:
    virtual ~AListCV() = 0;
    // Pre: This list exists.

    virtual void accept(AListCVVis<T> &visitor) const = 0;
};

template<class T>
ostream &operator<< (ostream &os, AListCV<T> const &rhs);
// Output a list to an ostream. See LCVtoStream.

// ========= Destructor =========
template<class T>
AListCV<T>::~AListCV() {
}

#endif
