// Figure 2.4, Design Patterns for Data Structures
// File: SwapVal/SwapValMain.cpp

#include <iostream>
using namespace std;

void swapVal(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "a == " << a << "  b == " << b << endl;
}

int main() {
    int i = 4;
    int j = 5;
    swapVal(i, j);
    cout << "i == " << i << "  j == " << j << endl;
    return EXIT_SUCCESS;
}
