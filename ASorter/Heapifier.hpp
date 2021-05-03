// File: ASorter/Heapifier.hpp

#ifndef HEAPIFIER_HPP_
#define HEAPIFIER_HPP_

#include "ASeq.hpp"

// ========= siftUp =========
template<class T>
void siftUp(ASeq<T> &a, int lo, int i) {
    // Pre: maxHeap(a[lo..i - 1]).
    // Post: maxHeap(a[lo..i]).
    T temp = a[i];
    int parent = (i + lo - 1) / 2;
    while (lo < i && a[parent] < temp) {
        cerr << "siftUp: Exercise for the student." << endl;
        throw -1;
    }
    a[i] = temp;
}

// ========= siftDown =========
template<class T>
void siftDown(ASeq<T> &a, int lo, int i, int hi) {
    // Pre: maxHeap(a[i + 1..hi]).
    // Pre: lo <= i <= hi.
    // Post: maxHeap(a[i..hi]).
    bool done = false;
    while (!done) {
        int child = 2 * i - lo + 1; // Index of left child.
        if (child <= hi) {
            if (child < hi && a[child] < a[child + 1]) {
                child++;
            }
            // child is the index of the larger of the two children.
            if (a[i] < a[child]) {
                T temp = a[i];
                a[i] = a[child];
                a[child] = temp;
                i = child;
            }else{
                done=true;
            }
        }
        else{
            done=true;
        }
    }
}
//SortCA-d0050.txt
//
#endif
