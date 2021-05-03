// File: ArrayP/ArrayPMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <fstream> // ifstream.
#include "Utilities.hpp"
#include "ArrayP.hpp"
#include "ArrayT.hpp"
using namespace std;

typedef ArrayP<double *> ArrayPDouble;
typedef ArrayT<double> ArrayTDouble;

int main() {
    int localCap;
    localCap = promptIntGE("Enter array capacity", 1);
    ArrayPDouble arrP(localCap);
    ArrayTDouble arrT(localCap);
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = 0;
        readStream(ifs, arrT, length);
        ifs.close();
        for (int i = 0; i < length; i++) {
            arrP[i] = new double(arrT[i]);
        }
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeStream(cout, arrP, length);
        // arr[2 * arr.cap()] = 123.4;
        // cout << arr[2 * arr.cap()] << endl;
        return EXIT_SUCCESS;
    }
}
