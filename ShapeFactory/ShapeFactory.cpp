// File: ShapeFactory/ShapeFactory.cpp

#include <cctype>  // toupper.
#include "Line.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "RightTriangle.hpp"
#include "NullShape.hpp"
#include "MysteryShape.hpp"  // Exercise for the student.
#include "ShapeFactory.hpp"

AShape* ShapeFactory::makeShape(char shapeType) {  
    switch (shapeType) {  
    case 'L':
        return new Line;
    case 'R':
        return new Rectangle;
    case 'C':
        return new Circle;
    case 'T':
        return new RightTriangle;
    case 'M':
        // Exercise for the student.
        break;
    default:
        return new NullShape;
    }
}

char ShapeFactory::promptShapeType() {  
    char ch = '\0';
    cout << "(l)ine  (r)ectangle  (c)ircle  right(t)riangle  (m)ystery: ";
    cin >> ch;
    ch = toupper(ch);
    while (ch != 'L' && ch != 'R' && ch != 'C' && ch != 'T' && ch != 'M') {  
        cout << "Must be l, r, c, t, or m.  Which type? ";
        cin >> ch;
        ch = toupper(ch);
    }
    return ch;
}
