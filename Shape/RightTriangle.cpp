// File: Shape/RightTriangle.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1
#include <cmath> // sqrt.
#include "RightTriangle.hpp"
#include "Utilities.hpp"

RightTriangle::RightTriangle(double base, double height) {
    if (base < 0.0 || height < 0.0) {
        cerr << "Rectangle precondition violated: length and width cannot be negative." << endl;
        throw -1;
    }
    _base = base;
    _height = height;
}

double RightTriangle::area() {
    return ((0.5)*_height*_base);
}

double RightTriangle::perimeter() {
    return sqrt(_base*_base + _height*_height) + _base + _height;
}

void RightTriangle::scale(double factor) {
    if (factor < 0.0 ) {
        cerr << "precondition violated: factor cannot be negative." << endl;
        throw -1;
    }
    _base = _base*factor;
    _height = _height*factor;
}

void RightTriangle::display(ostream &os) {
    os << " Right angle triangle: "<< endl;
    os << " Base: " << _base << endl;
    os << " Height: "<< _height << endl;
}

void RightTriangle::promptAndSetDimensions() {
    _base = promptDoubleGE("Base?", 0.0);
    _height = promptDoubleGE("Height?", 0.0);
}
