// Figure 2.5, Design Patterns for Data Structures
// File: SwapRef/SwapRefMain.cpp

#include <iostream>
using namespace std;

void swapRef(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "a == " << a << "  b == " << b << endl;
}

int main() {
    int i = 4;
    int j = 5;
    swapRef(i, j);
    cout << "i == " << i << "  j == " << j << endl;
    return EXIT_SUCCESS;
}
