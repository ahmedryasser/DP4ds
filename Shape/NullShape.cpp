// File: Shape/NullShape.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1
#include "NullShape.hpp"

NullShape::NullShape() {
}

double NullShape::area() {
    return 0.0;
}

double NullShape::perimeter() {
    return 0.0;
}

void NullShape::scale(double factor) {
    if (factor < 0.0 ) {
        cerr << "precondition violated: factor cannot be negative." << endl;
        throw -1;
    }
}

void NullShape::display(ostream &os) {
    os << endl;
}

void NullShape::promptAndSetDimensions() {
}

