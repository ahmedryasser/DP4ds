// File: VectorT/VectorTMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <fstream> // ifstream.
#include "Utilities.hpp"
#include "VectorT.hpp"
using namespace std;

typedef VectorT<int> VectorInt;

int main() {
    VectorInt v;
    int value, index;
    ifstream ifs;
    char response;
    do {
        cout << "\n(c)ap  (s)ize  (a)ppend  (f)ileAppend  (i)nsert  (r)emove  se(t)  (w)rite  (q)uit: ";
        cin >> response;
        switch (toupper(response)) {
        case 'C':
            cout << "\nThe capacity is " << v.cap() << endl;
            break;
        case 'S':
            cout << "\nThe size is " << v.size() << endl;
            break;
        case 'A':
            cout << "Append what integer value? ";
            cin >> value;
            v.append(value);
            break;
        case 'F':
            promptFileOpen(ifs);
            if (ifs) {
                ifs >> v;
                ifs.close();
            }
            break;
        case 'I':
            cout << "Insert what integer value? ";
            cin >> value;
            cout << "Insert at what location? ";
            cin >> index;
            v.insert(index, value);
            break;
        case 'R':
            cout << "Remove from what location? ";
            cin >> index;
            value = v.remove(index);
            cout << "\n" << value << " removed." << endl;
            break;
        case 'T':
            cout << "Set what integer value? ";
            cin >> value;
            cout << "Set at what location? ";
            cin >> index;
            v[index] = value;
            cout << "\nValue at index " << index << " is now " << v[index] << endl;
            break;
        case 'W':
            cout << "\n" << v << endl;
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    } while (toupper(response) != 'Q');
    return EXIT_SUCCESS;
}
