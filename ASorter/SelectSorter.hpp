// File ASorter/SelectSorter.hpp

#ifndef SELECTSORTER_HPP_
#define SELECTSORTER_HPP_

#include "ASorter.hpp"

template<class T>
class SelectSorter : public ASorter<T> {
public:

    ~SelectSorter() {
    }

protected:
    virtual void split(ASeq<T> &a, int lo, int &mid, int hi) override;
    virtual void join(ASeq<T> &a, int lo, int mid, int hi) override;
};

template<class T>
void SelectSorter<T>::split(ASeq<T> &a, int lo, int &mid, int hi) {
    // Post: a[hi] == max(a[lo..hi]).
    // Post: mid == hi.
    int indexOfMax = lo;
    for (int i = lo + 1; i <= hi; i++) {
        if (a[indexOfMax] < a[i]) {
            indexOfMax = i;
        }
    }
    T temp = a[hi];
    a[hi] = a[indexOfMax];
    a[indexOfMax] = temp;
    mid = hi;
}

template<class T>
void SelectSorter<T>::join(ASeq<T>&, int lo, int mid, int hi) {
}

#endif
