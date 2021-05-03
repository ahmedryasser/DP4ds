// File: ShapeFactory/ShapeFactoryMain.hpp

#ifndef ShapeFactoryMain_hpp
#define ShapeFactoryMain_hpp

#include "AShape.hpp"
#include "ArrayP.hpp"

typedef ArrayP<AShape*> ArrayPShape;

void initialize(ArrayPShape &shapes);
// Post: All elements shapes are initialized as pointers to the null shape.

void cleanUp(ArrayPShape &shapes);
// Post: All elements shapes are deleted and set to nullptr.

void promptLoop(ArrayPShape &shapes);
// Loop to prompt the user with the top-level main prompt.
// Post: User has selected the quit option.

void makeShape(AShape* &sh);
// Prompts user for dimensions.
// Post: Original sh is deleted and new sh is created.

void clearShape(AShape* &sh);
// Post: Original sh is deleted and shape is made the null shape.

void printArea(AShape* sh);
// Post: sh's area is printed to standard ouput.

void printPerimeter(AShape* sh);
// Post: The perimeter of this sh is printed to standard ouput.

void scaleShape(AShape* sh);
// Prompts user for scale factor.
// Post: sh's dimensions are multiplied by the factor.

void displayShape(AShape* sh);
// Post: sh's name and dimensions are printed to standard ouput.

#endif
