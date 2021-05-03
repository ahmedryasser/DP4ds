// Figure 2.6, Design Patterns for Data Structures
// File: SwapPtr/SwapPtrMain.cpp

#include <iostream>
using namespace std;

void swapPtr(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    cout << "*a == " << *a << "  *b == " << *b << endl;
}

int main() {
    int i = 4;
    int j = 5;
    swapPtr(&i, &j);
    cout << "i == " << i << "  j == " << j << endl;
    return EXIT_SUCCESS;
}
