// File: Shape/Circle.cpp
// Number: 16
// Name: Ahmed Najiub
// Date: 08-22-2020
// Assignment: 1
#include "Circle.hpp"
#include "Utilities.hpp" // PI.

Circle::Circle(double radius) {  
    if(radius < 0.0) {
        cerr << "Circle precondition violated: radius cannot be negative." << endl;
        throw -1;
    }
    _radius = radius;
}

double Circle::area() {  
    return PI * _radius * _radius;
}

double Circle::perimeter() {  
    return 2.0 * PI * _radius;
}

void Circle::scale(double factor) {
    if(factor <= 0){
        cerr << "Precondition violated: factor cannot be negative." << endl;
    }
    _radius = _radius*factor;
}

void Circle::display(ostream &os) {  
    os << "Circle\n" << "Radius: " << _radius << endl;
}

void Circle::promptAndSetDimensions() {
    _radius = promptDoubleGE("Radius?", 0.0);
}

