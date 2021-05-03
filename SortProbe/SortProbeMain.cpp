// File: SortProbe/SortProbeMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <iostream> // cout.
#include <fstream>  // ifstream.
#include "Utilities.hpp"
#include "ArrayT.hpp" // readStream, writeStream.
#include "ArrProbe.hpp"
#include "InsertSorter.hpp"
#include "QuickSorter.hpp"
#include "HeapSorter.hpp"
#include "MergeSorter.hpp"
#include "SelectSorter.hpp"
using namespace std;

typedef ArrayT<double> ArrayTD;
typedef ASorter<double> ASorterD;

void testSort(const ArrayTD &arr, int len, ASorterD* sorter); // Forward declaration.

typedef InsertSorter<double> InsertSorterD;
typedef SelectSorter<double> SelectSorterD;
typedef MergeSorter<double> MergeSorterD;
typedef QuickSorter<double> QuickSorterD;
typedef MergeSorter<double> MergeSorterD;
typedef HeapSorter<double> HeapSorterD;
typedef ArrProbe<double> ArrProbeD;

int main() {
    ArrayTD array(promptIntGE("Enter array capacity", 1));
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = 0;
        readStream(ifs, array, length);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeStream(cout, array, length);

        cout << "\nInsertion Sort..." << endl;
        ASorterD *sorter = new InsertSorterD;
        testSort(array, length, sorter);
        delete sorter;

        cout << "\nSelection Sort..." << endl;
        sorter = new SelectSorterD;
        testSort(array, length, sorter);
        delete sorter;

        cout << "\nMerge Sort..." << endl;
        sorter = new MergeSorterD(length);
        testSort(array, length, sorter);
        delete sorter;

        cout << "\nHeapSort Sort..." << endl;
        sorter = new HeapSorterD(array, 0, length -1);
        testSort(array, length, sorter);
        delete sorter;

        cout << "\nQuick Sort..." << endl;
        sorter = new QuickSorterD;
        testSort(array, length, sorter);
        delete sorter;
        sorter = nullptr;
    }
    return EXIT_SUCCESS;
}

void testSort(const ArrayTD &arr, int len, ASorterD* sorter) {
    ArrayTD tempArr(len);
    for (int i = 0; i < len; i++) {
        tempArr[i] = arr[i];
    }

    ArrProbeD arrProbe(&tempArr);
    arrProbe.clearProbeCount();
    cout << "\nInitial Performance count:" << endl;
    cout << "Probe count = " << arrProbe.getProbeCount() << endl;
    sorter->sort(arrProbe, 0, len - 1);
    bool sorted = true;
    for (int i = 1; i < len; i++) {
        if (tempArr[i-1] > tempArr[i]) {
            sorted = false;
        }
    }
    if (sorted) {
        cout << "\nSorted postcondition satisfied." << endl;
    }
    else {
        cout << "\nERROR: Sorted postcondition not satisfied." << endl;
    }
    // cout << "\nSorted Array:" << endl;
    // writeStream(cout, tempArr, len);
    cout << "\nFinal Performance count:" << endl;
    cout << "Probe count = " << arrProbe.getProbeCount() << endl;
}
