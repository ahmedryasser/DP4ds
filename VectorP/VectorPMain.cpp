// File: VectorP/VectorPMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <fstream> // ifstream.
#include "Utilities.hpp"
#include "VectorP.hpp"
using namespace std;

typedef int* PInt;
typedef VectorP<PInt> VectorPInt;

int main() {
    VectorPInt v;
    int value, index;
    int *pValue;
    ifstream ifs;
    char response;
    do {
        cout << "\n(c)ap  (s)ize  (a)ppend  (i)nsert  (r)emove  se(t)  (w)rite  (q)uit: ";
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
            pValue = new int(value);
            v.append(pValue);
            break;
        case 'I':
            cout << "Insert what integer value? ";
            cin >> value;
            pValue = new int(value);
            cout << "Insert at what location? ";
            cin >> index;
            v.insert(index, pValue);
            break;
        case 'R':
            cout << "Remove from what location? ";
            cin >> index;
            pValue = v.remove(index);
            cout << "\n" << *pValue << " removed." << endl;
            delete pValue;
            break;
        case 'T':
            cout << "Set what integer value? ";
            cin >> value;
            pValue = new int(value);
            cout << "Set at what location? ";
            cin >> index;
            v[index] = pValue;
            cout << "\nValue at index " << index << " is now " << *v[index] << endl;
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
