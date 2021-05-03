// File: SortClassic/SortClassicMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <fstream> // ifstream.
#include <cctype> // toupper.
#include "Utilities.hpp"
#include "ArrayT.hpp" // readStream, writeStream.
using namespace std;

typedef ArrayT<int> Array;

template<class T>
void sort(ASeq<T> &a, int lo, int hi);

int main() {
    Array array(promptIntGE("Enter array capacity", 1));
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = 0;
        readStream(ifs, array, length);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeStream(cout, array, length);
        int low = promptIntBetween("Low index: ", 0, length - 1);
        int high = promptIntBetween("High index: ", 0, length - 1);
        sort(array, low, high);
        cout << "Array data:" << endl;
        writeStream(cout, array, length);
    }
    return EXIT_SUCCESS;
}

template<class T>
void sort(ASeq<T> &a, int lo, int hi) {
    cerr << "sort: Exercise for the student." << endl;
    throw -1;
}
