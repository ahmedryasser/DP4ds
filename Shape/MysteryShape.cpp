// File: Shape/MysteryShape.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1
#include "MysteryShape.hpp"
#include "Utilities.hpp"

// Square
MysteryShape::MysteryShape(double side) {
    if (side < 0.0 ) {
        cerr << "Rectangle precondition violated: length and width cannot be negative." << endl;
        throw -1;
    }
    _side = side;
}

double MysteryShape::area() {
    return _side * _side;
}

double MysteryShape::perimeter() {
    return 4.0 * _side;
}

void MysteryShape::scale(double factor) {
    if (factor < 0.0 ) {
        cerr << "precondition violated: factor cannot be negative." << endl;
        throw -1;
    }
    _side = _side*factor;
}

void MysteryShape::display(ostream &os) {
    os << "Square" << endl;
    os << "Side: " << _side << endl;
}

void MysteryShape::promptAndSetDimensions() {
    _side = promptDoubleGE("Side?", 0.0);
}

