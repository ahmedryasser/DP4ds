// File: ShapeFactory/ShapeFactory.hpp

#ifndef ShapeFactory_hpp
#define ShapeFactory_hpp

#include "AShape.hpp"

class ShapeFactory {
public:
    static AShape* makeShape(char shapeType = 'N');
    // Post: A pointer to a shape of type shapeType is returned.

    static char promptShapeType();
    // Prompts user for shape letter, lowercase or uppercase.
    // Post: Uppercase character L, R, C, T, or M is returned.
};

#endif
