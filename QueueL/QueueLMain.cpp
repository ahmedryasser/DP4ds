// File: QueueL/QueueLMain.cpp

#include <cstdlib> // EXIT_SUCCESS.
#include <iostream> // cout.
#include <cctype> // toupper.
#include "QueueL.hpp"
using namespace std;

int main() {
    QueueL<double> queueL;
    double value;
    char cResponse;
    do {
        cout << "\n(e)mpty  e(n)queue  (d)equeue  (h)ead  (w)rite  (q)uit: ";
        cin >> cResponse;
        switch (toupper(cResponse)) {
        case 'E':
            if (queueL.isEmpty())
                cout << "\nThe queue is empty." << endl;
            else
                cout << "\nThe queue is not empty." << endl;
            break;
        case 'N':
            cout << "Value to enqueue: ";
            cin >> value;
            queueL.enqueue(value);
            break;
        case 'D':
            cout << "\nValue dequeued: " << queueL.dequeue() << endl;
            break;
        case 'H':
            cout << "\nQueue head: " << queueL.headOf() << endl;
            break;
        case 'W':
            cout << "\nHead --> Tail" << endl;
            cout << queueL;
            break;
        case 'Q':
            break;
        default:
            cout << "\nIllegal command." << endl;
            break;
        }
    }
    while (toupper(cResponse) != 'Q');
    return EXIT_SUCCESS;
}

