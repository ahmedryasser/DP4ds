// File ASorter/MergeSorter.hpp

#ifndef MERGESORTER_HPP_
#define MERGESORTER_HPP_

#include "ASorter.hpp"
#include "ArrayT.hpp"
template<class T>
class MergeSorter :public ASorter<T> {

private:
    ArrayT<T> _tempA;

public:
    MergeSorter(int cap);
    ~MergeSorter() {
    }

protected:
    virtual void split(ASeq<T> &a, int lo, int &mid, int hi) override;
    virtual void join(ASeq<T> &a, int lo, int mid, int hi) override;
};
template<class T>

MergeSorter<T>::MergeSorter(int cap) :
    _tempA(cap) {
}
template<class T>
void MergeSorter<T>::split(ASeq<T> &, int lo, int &mid, int hi) {
    // Post: mid ==(lo + hi + 1) / 2
    mid = (lo + hi + 1) / 2;
}
template<class T>
void MergeSorter<T>::join(ASeq<T> &a, int lo, int mid, int hi) {
    int i = lo;
    int j = mid;
    for (int k =lo; k<=hi;k++){
        if ( i >= mid){
             _tempA[k] = a[j++];
        }
        else if(j> hi){
            _tempA[k] = a[i++];
        }
        else if(a[i] <a[j]){
            _tempA[k] = a[i++];
        }

        else{
            _tempA[k] =a[j++];
        }
    }
    for(int m =lo; m<=hi; m++){
        a[m]=_tempA[m];
    }
}


#endif
