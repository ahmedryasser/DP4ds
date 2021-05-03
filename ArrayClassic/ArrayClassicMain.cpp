// File: ArrayClassic/ArrayClassicMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <fstream> // ifstream.
#include "ArrayClassicMain.hpp"
#include "Utilities.hpp" // promptIntGE.
using namespace std;

int main() {
    int cap = promptIntGE("Enter array capacity", 1);
    double *arr = new double[cap]; // Dynamic allocation.
    ifstream ifs;
    promptFileOpen(ifs);
    if (ifs) {
        int length = 0;
        readStream(ifs, arr, cap, length);
        ifs.close();
        cout << "Read count == " << length << endl;
        cout << "Array data:" << endl;
        writeStream(cout, arr, cap, length);
        arr[2 * cap] = 123.54;
        cout << arr[2 * cap] << endl;
    }
    delete [] arr;
    return EXIT_SUCCESS;
}

void readStream(istream &is, double d[], int cap, int &len) {
    len = 0;
    for (int i = 0; i < cap && is >> d[i]; i++) {
        len++;
    }
}

void writeStream(ostream &os, double const d[], int cap, int len) {
    for (int i = 0; i < len && i < cap; i++) {
        os.width(12);
        os << d[i];
        if (i % 6 == 5) {
            os << endl;
        }
    }
    os << endl;
}
