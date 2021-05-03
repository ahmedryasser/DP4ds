// File: Shape/Line.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1
#include "Line.hpp"
#include "Utilities.hpp"

Line::Line(double length) {  
    if(length < 0.0) {
        cerr << "Line precondition violated: length cannot be negative." << endl;
        throw -1;
    }
    _length = length;
}

double Line::area() {  
    return 0.0;
}

double Line::perimeter() {  
    return _length;
}

void Line::scale(double factor) {
    if (factor < 0.0 ) {
        cerr << "precondition violated: factor cannot be negative." << endl;
        throw -1;
    }
    _length = _length*factor;
}

void Line::display(ostream &os) {
    os << "Line\n" << "Length: " << _length << endl;
}

void Line::promptAndSetDimensions() {
    _length = promptDoubleGE("Length?", 0.0);
}

