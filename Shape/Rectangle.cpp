// File: Shape/Rectangle.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1
#include "Rectangle.hpp"
#include "Utilities.hpp"

Rectangle::Rectangle(double length, double width) {
    if (length < 0.0 || width < 0.0) {
        cerr << "Rectangle precondition violated: length and width cannot be negative." << endl;
        throw -1;
    }
    _length = length;
    _width = width;
}

double Rectangle::area() {
    return _length * _width;
}

double Rectangle::perimeter() {
    return 2.0 *(_length + _width);
}

void Rectangle::scale(double factor) {
    if (factor < 0.0 ) {
        cerr << "precondition violated: factor cannot be negative." << endl;
        throw -1;
    }
    _length = _length*factor;
    _width = _width*factor;
}

void Rectangle::display(ostream &os) {
    os << "Rectangle" << endl;
    os << "Length: " << _length << endl;
    os << "Width: " << _width << endl;
}

void Rectangle::promptAndSetDimensions() {
    _length = promptDoubleGE("Length?", 0.0);
    _width = promptDoubleGE("Width?", 0.0);
}
